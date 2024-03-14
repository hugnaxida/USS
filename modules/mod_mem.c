/***************************************************************************//**
 * @file      mod_mem.c
 *
 * @author    StSl
 * @date      30.11.2017
 *
 * @brief     RAM check module
 *
 * Functionality: Init, MemTask, set do-check-flag
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
 * $Id: mod_mem.c 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
 *
 *
 * ###########################################################################*/

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_mem.h"
#include "mod_crc16.h"
#include "mod_err.h"

/* ****************************************************************************/
/* **************************** CUSTOM INCLUDES *******************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ***************************** GLOBAL VARIABLES *****************************/
/* ****************************************************************************/
bool_t calcCrcOverRamParam; /* Flag to trigger CRC calculation in main task */
Meas_uMeasurementParameters_t* loc_pAppDataMem;/* pointer to application runtime data environment*/

/* ****************************************************************************/
/* ************************** FUNCTION PROTOTYPES *****************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * Memory initialisation
 *
 * Initialises all memory related variables
 *
 * @param       measParameterInRam  pointer to measurement parameters in ram
 *
 * @return      bool_t              true if init was successful, else false
 * ****************************************************************************/
bool_t mem_Init(Meas_uMeasurementParameters_t* measParameterInRam)
{
  bool_t retval = true;

  if(NULL != measParameterInRam)
  {
    /* save pointer to measurement parameters in ram */
    loc_pAppDataMem = measParameterInRam;
    /* initialise module flags */
    calcCrcOverRamParam = false;
  }
  else
  {
    /* init not successful -> goto error handler */
    retval = false;
    err_ErrorHandler(ERR_MODLIST_MEM);
  }
  return retval;
}

/* **************************************************************************//**
 * @brief
 * Memory Task
 *
 * The main task of the memory module. If triggered it calculates the CRC over the
 * measurement parameters in RAM and saves the result
 *
 * @image html "mem_Task.png" "Activity Diagram: RAM task" max-width=640
 * <a href="mem_Task.png">klick here to enlarge image</a>
 *
 * @return      none
 * ****************************************************************************/
void mem_Task(void)
{
  if(NULL != loc_pAppDataMem)
  {
    if(true == calcCrcOverRamParam)
    {
      /* Calculate the CRC over the RAM area, which contains the copy of the EEPROM config data */
      (void)crc16_checkCrc((uint32_t)loc_pAppDataMem , EEPROM_LENGTH_WITHOUT_CRC_AREA, 0, &(loc_pAppDataMem->data.CrcCalculation.fields.CrcEepromOrRam));
      calcCrcOverRamParam = false;
    }
    else
    {
      /* nothing to do here */
    }
  }
  else
  {
    /* init not successful -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_MEM);
  }
}

/* **************************************************************************//**
 * @brief
 * Trigger CRC calculation over ram
 *
 * Set a flag, to trigger a CRC calculation over the measurement parameters
 * in the RAM. The CRC calculation takes place when the mem_Task() is called the next time.
 * The result is saved to the RAM.
 *
 * @return      void       None.
 * ****************************************************************************/
void mem_TriggerCrcCalculationOverRam(void)
{
  calcCrcOverRamParam = true;
}
