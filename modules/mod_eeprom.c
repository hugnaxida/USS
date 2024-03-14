/***************************************************************************//**
 * @file      mod_eeprom.c
 *
 * @author    StSl
 * @date      10.10.2017
 * @sdfv      Demo Flow
 *
 * @brief     EEPROM module initializes and handles the EEPROM operations
 *
 *  ******************************************************************************
 *
 * Demo Code Usage Restrictions:
 * Elmos Semiconductor AG provides this source code file simply and solely for
 * IC evaluation purposes in laboratory and this file must not be used
 * for other purposes or within non laboratory environments. Especially, the use
 * or the integration in production systems, appliances or other installations is
 * prohibited.
 *
 * Disclaimer:
 * Elmos Semiconductor AG shall not be liable for any damages arising out of
 * defects resulting from
 * (1) delivered hardware or software,
 * (2) non observance of instructions contained in this document, or
 * (3) misuse, abuse, use under abnormal conditions or alteration by anyone
 * other than Elmos Semiconductor AG. To the extend permitted by law
 * Elmos Semiconductor AG hereby expressively disclaims and user expressively
 * waives any and all warranties of merchantability and of fitness for a
 * particular purpose, statutory warranty of non-infringement and any other
 * warranty or product liability that may arise by reason of usage of trade,
 * custom or course of dealing.
 *
 ******************************************************************************
 *
 * $Id: mod_eeprom.c 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
 *
 *
 *******************************************************************************/
/* ****************************************************************************/
/* **************************** CUSTOM INCLUDES *******************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_eeprom.h"
#include "mod_eeprom_access.h"
#include "mod_err.h"
#include "mod_crc16.h"



/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define EEPROM_PW_ACTION_EEPROM_TO_RAM  (0xAAu)             /**< Eeprom password to be allowed to execute action: copy eeprom to ram */
#define EEPROM_PW_ACTION_ENABLE         (0x66u)             /**< Eeprom password to be allowed to execute action: enable eeprom access */
#define EEPROM_PW_ACTION_RAM_TO_EEPROM  (0x33u)             /**< Eeprom password to be allowed to execute action: copy ram to eeprom */
#define EEPROM_PW_ACTION_SAVE_SLAVEID   (0x55u)             /**< Eeprom password to be allowed to execute action: copy slave id to eeprom */

/* ****************************************************************************/
/* ***************************** GLOBAL VARIABLES *****************************/
/* ****************************************************************************/
static Meas_uMeasurementParameters_t* loc_pEepromAppData;   /**< application runtime data environment */
static Meas_uMeasurementParameters_t* loc_pAppData;         /**< pointer to application runtime data environment*/
static Eeprom_eStates_t loc_State;                          /**< current state of the eeprom state machine */
static Eeprom_eAction_t loc_Action;                         /**< action to be executed by eeprom module */


/* ****************************************************************************/
/* ************************** FUNCTION PROTOTYPES *****************************/
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * Copy eeprom to ram
 *
 * Copys the current measurement parameters from eeprom to ram
 * and compares the result data
 *
 * @return      none
 * ****************************************************************************/
void loc_CopyEepromToRam(void);

/* **************************************************************************//**
 * @brief
 * Copy RAM to eeprom
 *
 * Copys the current measurement parameters from RAM to eeprom
 * and compares the result data
 *
 * @return      none
 * ****************************************************************************/
void loc_CopyRamToEeprom(void);

/* **************************************************************************//**
 * @brief
 * Copy slave id to eeprom
 *
 * Copys the current slave id from RAM to eeprom
 *
 * @return      none
 * ****************************************************************************/
void loc_CopySlaveIdToEeprom(void);


/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * EEPROM initialisation
 *
 * Initialises the EEPROM State-machine and copy EEPROM values to the RAM.
 *
 * @param       measParameter   Pointer to the measurement parameter struct in RAM
 *
 * @return      bool_t          true if init was successful, else false
 * ****************************************************************************/
bool_t Eeprom_Init(Meas_uMeasurementParameters_t* measParameter)
{
  bool_t retval = true;

  if(NULL != measParameter)
  {
    /* Init state machine to default-state */
    loc_State = EEPROM_STATE_IDLE;
    loc_Action = EEPROM_ACTION_NONE;
    /* Save the pointer of the RAM-located-parameter-structure */
    loc_pAppData = measParameter;
    /* Set EEPROM data pointer to the base-address of the measurement parameters */
    loc_pEepromAppData = (Meas_uMeasurementParameters_t*)EEPROM_BASE_ADDRESS;
    /* Copy persistent data from EEPROM to RAM at startup */
    loc_CopyEepromToRam();
  }
  else
  {
    /* wrong parameter -> can't work with this */
    retval = false;
    err_ErrorHandler(ERR_MODLIST_EEPROM);
  }
  return retval;
}

/* **************************************************************************//**
 * @brief
 * Get data pointer
 *
 * Returns a pointer to the measurement parameter struct in EEPROM
 *
 * @return      Meas_uMeasurementParameters_t   Pointer to measurement paramter strcut in EEPROM
 * ****************************************************************************/
Meas_uMeasurementParameters_t* Eeprom_GetDataPointer(void)
{
  return (Meas_uMeasurementParameters_t*)EEPROM_BASE_ADDRESS;
}

/* **************************************************************************//**
 * @brief
 * EEPROM task.
 *
 * The switch-case is controlled by the State-machine.
 * Executes the Action, which is granted by the state machine.
 * Puts the State-machine back to default afterwards.
 *
 * @image html "Eeprom_Task.png" "Activity Diagram: EEPROM task" max-width=640
 * <a href="Eeprom_Task.png">klick here to enlarge image</a>
 *
 * @image html "StateMachineEEPROM.png" "State-machine: EEPROM" max-width=640
 * <a href="StateMachineEEPROM.png">klick here to enlarge image</a>
 *
 * @return      none
 * ****************************************************************************/
void Eeprom_Task(void)
{
  if((NULL != loc_pAppData) && (NULL != loc_pEepromAppData))
  {
    switch(loc_Action)
    {
    case EEPROM_ACTION_EEPROM_TO_RAM:
      /* Copy EEPROM content to RAM */
      loc_CopyEepromToRam();
      loc_State = EEPROM_STATE_IDLE;
      loc_Action = EEPROM_ACTION_NONE;
      break;
    case EEPROM_ACTION_RAM_TO_EEPROM:
      /* Copy RAM content to EEPROM */
      loc_CopyRamToEeprom();
      loc_State = EEPROM_STATE_IDLE;
      loc_Action = EEPROM_ACTION_NONE;
      break;
    case EEPROM_ACTION_SAVE_SLAVEID:
      /* Copy current slave id to EEPROM */
      loc_CopySlaveIdToEeprom();
      loc_State = EEPROM_STATE_IDLE;
      loc_Action = EEPROM_ACTION_NONE;
      break;
    default:
      /* idle mode -> nothing to do here */
      break;
    }
  }
  else
  {
    /* init incomplete -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_EEPROM);
  }
}

/* **************************************************************************//**
 * @brief
 * Set operation controlls the State-machine.
 * (see also SM57)
 * After the State-machine is put to the "EEPROM_STATE_ENABLE"-state, an action for the
 * "Eeprom_Task()"-method can be chosen when switching to the "EEPROM_STATE_PROGRAM"-state.
 * Any wrong transition request will reset the State-machine to "EEPROM_STATE_IDLE".
 *
 * A transition towards EEPROM_ACTION_ENABLE and then to EEPROM_STATE_PROGRAM is only possible when
 * the transition code is provided together with the correct password.
 * Any wrong password will reset the State-machine.
 *
 * @param       operation           The operation to execute on the EEPROM state machine
 * @param       password            Password for EEPROM access
 *
 * @return      Eeprom_eError_t     EEPROM error code
 * ****************************************************************************/
Eeprom_eError_t Eeprom_SetOperation(Eeprom_eAction_t operation, uint8_t password)
{
  Eeprom_eError_t retval = EEPROM_ERR_OK;

  /* Check if EEPROM is currently busy */
  if(EEPROM_STATE_PROGRAM == loc_State)
  {
    /* EEPROM is busy -> dont change state machine */
    retval = EEPROM_ERR_BUSY;
  }
  else
  { /* State-machine ready for commands. */

    /* Bring State-machine to state "Enable EEPROM" or... */
    if(EEPROM_ACTION_ENABLE == operation)
    {
      if(EEPROM_PW_ACTION_ENABLE == password)
      {
        if(EEPROM_STATE_ENABLE != loc_State)
        {
          /* password correct -> enable eeprom */
          loc_State = EEPROM_STATE_ENABLE;
        }
        else
        {
          /* EEPROM already enabled -> disable eeprom */
          retval = EEPROM_ERR_UNKNOWN_ERR;
        }
      }
      else
      {
        /* wrong password -> dont execute operation */
        retval = EEPROM_ERR_WRONG_PW;
      }
    }
    else
    { /* ...access if operation is set and password is correct */
      /* check if eeprom has been enabled before -> change state machine */
      if(EEPROM_STATE_ENABLE == loc_State)
      {
        switch(operation)
        {
        case EEPROM_ACTION_EEPROM_TO_RAM:
          /* operation is copy eeprom content to ram -> check the password */
          if(EEPROM_PW_ACTION_EEPROM_TO_RAM == password)
          {
            /* correct password -> change state machine to execute operation */
            loc_State = EEPROM_STATE_PROGRAM;
            loc_Action = EEPROM_ACTION_EEPROM_TO_RAM;
          }
          else
          {
            /* wrong password -> dont execute operation */
            retval = EEPROM_ERR_WRONG_PW;
          }
          break;
        case EEPROM_ACTION_RAM_TO_EEPROM:
          /* operation is copy ram content to eeprom -> check the password */
          if(EEPROM_PW_ACTION_RAM_TO_EEPROM == password)
          {
            /* correct password -> change state machine to execute operation */
            loc_State = EEPROM_STATE_PROGRAM;
            loc_Action = EEPROM_ACTION_RAM_TO_EEPROM;
          }
          else
          {
            /* wrong password -> dont execute operation */
            retval = EEPROM_ERR_WRONG_PW;
          }
          break;
        case EEPROM_ACTION_SAVE_SLAVEID:
          /* operation is copy current salve id content to eeprom -> check the password */
          if(EEPROM_PW_ACTION_SAVE_SLAVEID == password)
          {
            /* correct password -> change state machine to execute operation */
            loc_State = EEPROM_STATE_PROGRAM;
            loc_Action = EEPROM_ACTION_SAVE_SLAVEID;
          }
          else
          {
            /* wrong password -> dont execute operation */
            retval = EEPROM_ERR_WRONG_PW;
          }
          break;
        case EEPROM_ACTION_ENABLE:
        default:
          /* idle mode -> reset state machine */
          loc_State = EEPROM_STATE_IDLE;
          loc_Action = EEPROM_ACTION_NONE;
          break;
        }
      }
      else
      {
        /* eeprom hasnt been enabled before -> dont execute operation */
        retval = EEPROM_ERR_UNKNOWN_ERR;
      }
    }

    /* lock eeprom access if operation or password was invalid */
    if(EEPROM_ERR_OK != retval)
    {
      loc_State = EEPROM_STATE_IDLE;
      loc_Action = EEPROM_ACTION_NONE;
    }
    else
    {
      /* everything ok -> nothing to do here */
    }
  }

  return retval;
}

/* **************************************************************************//**
 * @brief
 * Check if busy
 *
 * Checks if the EEPROM module is busy
 *
 * @return      bool_t      true if busy, else false
 * ****************************************************************************/
bool_t Eeprom_CheckIfBusy(void)
{
  return (loc_State == EEPROM_STATE_PROGRAM);
}

/* **************************************************************************//**
 * @brief
 * Disable EEPROM
 *
 * Disables the access to EEPROM, so it needs to be reenabled
 * to get access
 *
 * @return      none
 * ****************************************************************************/
void Eeprom_Disable(void)
{
  loc_State = EEPROM_STATE_IDLE;
}

/* **************************************************************************//**
 * @brief
 * Copy EEPROM to RAM
 *
 * Copys the current measurement parameters from EEPROM to RAM
 * and compares the result data
 *
 * @return      none
 * ****************************************************************************/
void loc_CopyEepromToRam(void)
{
  if((NULL != loc_pAppData) && (NULL != loc_pEepromAppData))
  {
    /* copy halfword by halfword from EEPROM to ram */
    for(uint32_t i = 0; i < MEAS_SETTINGS_SIZE; i++)
    {
      loc_pAppData->halfwords[i] = loc_pEepromAppData->halfwords[i];
    }
    /* calculate crc over ram and compare to crc saved in ram */
    bool_t retval = crc16_checkCrc((uint32_t)loc_pAppData, EEPROM_LENGTH_WITHOUT_CRC_AREA, loc_pAppData->data.CrcCalculation.fields.CrcEepromOrRam, NULL);
    if(true == retval)
    {
      /* everything ok */
    }
    else
    {
      /* copy not successful -> set HwErrFlag */
      err_SetHwErrorFlag(ERR_NO_ERROR1, ERR_CRC_MISMATCH_IN_RAM);
    }
  }
  else
  {
    /* init not completed -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_EEPROM);
  }
}

/* **************************************************************************//**
 * @brief
 * Copy RAM to EEPROM
 *
 * Copys the current measurement parameters from RAM to EEPROM
 * and compares the result data
 *
 * @return      none
 * ****************************************************************************/
void loc_CopyRamToEeprom(void)
{
  if((NULL != loc_pAppData) && (NULL != loc_pEepromAppData))
  {
    bool_t ret;
    
    ret = eeprom_Write(EE_PASSWORD, (eeprom_cpData_t)loc_pAppData, (eeprom_Address_t)loc_pEepromAppData, EEPROM_LENGTH, 0, 0);
    if(ret != true)
    {
      /* eeprom write failed -> set HwErrFlag */
      err_SetHwErrorFlag(ERR_EEPROM_PROGRAMMING_FAILURE, ERR_NO_ERROR2);
    }
    else
    {
      /* everything ok -> calculate crc over eeprom and compare to crc saved in eeprom */
      ret = crc16_checkCrc((uint32_t)loc_pEepromAppData, EEPROM_LENGTH_WITHOUT_CRC_AREA, loc_pEepromAppData->data.CrcCalculation.fields.CrcEepromOrRam, NULL);
      if(true == ret)
      {
        /* everything ok */
      }
      else
      {
        /* copy not successful -> set HwErrFlag */
        err_SetHwErrorFlag(ERR_CRC_MISMATCH_IN_EEPROM, ERR_NO_ERROR2);
      }
    }
  }
  else
  {
    /* init not completed -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_EEPROM);
  }
}

/* **************************************************************************//**
 * @brief
 * Copy slave id to EEPROM
 *
 * Copys the current slave id from RAM to EEPROM
 *
 * @return      none
 * ****************************************************************************/
void loc_CopySlaveIdToEeprom(void)
{
  if((NULL != loc_pAppData) && (NULL != loc_pEepromAppData))
  {
    bool_t ret;

    ret = eeprom_Write(EE_PASSWORD, (eeprom_cpData_t)(&(loc_pAppData->data.SlaveId.halfwords[0])), (eeprom_Address_t)(&(loc_pEepromAppData->data.SlaveId.halfwords[0])), 4, 0, 0);
    if(ret != true)
    {
      /* eeprom write failed -> set HwErrFlag */
      err_SetHwErrorFlag(ERR_EEPROM_PROGRAMMING_FAILURE, ERR_NO_ERROR2);
    }
    else
    {
      /* everything ok */
    }
  }
  else
  {
    /* init not completed -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_EEPROM);
  }
}
