/***************************************************************************//**
 * @file      mod_eeprom.h
 *
 * @author    StSl
 * @date      10.10.2017
 * @sdfv      Demo Flow
 *
 * @brief     EEPROM module initializes and handles the EEPROM operations (header)
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
 * $Id: mod_eeprom.h 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
 *
 ******************************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "def_app.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define PUDIN_L_IN_EEPROM ( *( (uint16_t*)(EEPROM_BASE_ADDRESS + 0xF4u) ) )              /**< Low word of elmos chip id from eeprom */
#define PUDIN_H_IN_EEPROM ( *( (uint16_t*)(EEPROM_BASE_ADDRESS + 0xF6u) ) )              /**< High word of elmos chip id from eeprom */
#define TSENS_OFF         ((*((uint16_t*)(EEPROM_BASE_ADDRESS + 0xF8u)))&0x03FFu)        /**< Reference temperature in digits */
#define TSENS_GAIN        (((*((uint16_t*)(EEPROM_BASE_ADDRESS + 0xF8u)))&0xFC00u)>>10u) /**< Temperature gradient correction value */

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/** EEPROM FSM states */
typedef enum
{
  EEPROM_STATE_IDLE = 0,                  /**< EEPROM state machine is in idle state */
  EEPROM_STATE_ENABLE = 1,                /**< EEPROM state machine is enabled and ready to execute an operation */
  EEPROM_STATE_PROGRAM = 2,               /**< EEPROM state machine is programming aka. busy */
} Eeprom_eStates_t;

/** Error flags */
typedef enum
{
  EEPROM_ERR_OK = 0,                      /**< Function call was successful */
  EEPROM_ERR_WRONG_PW = -1,               /**< Function rejected command based on a false password */
  EEPROM_ERR_BUSY = -2,                   /**< Function rejected command because EEPROM is busy */
  EEPROM_ERR_UNKNOWN_ERR = -200,          /**< An unknown error occurred */
} Eeprom_eError_t;

/** EEPROM actions*/
typedef enum
{
  EEPROM_ACTION_NONE          = 0x0,      /**< EEPROM should do nothing */
  EEPROM_ACTION_EEPROM_TO_RAM = 0x1,      /**< EEPROM should save its content to ram */
  EEPROM_ACTION_ENABLE        = 0x2,      /**< EEPROM should get enabled */
  EEPROM_ACTION_RAM_TO_EEPROM = 0x4,      /**< EEPROM should save the ram content */
  EEPROM_ACTION_SAVE_SLAVEID  = 0x8,      /**< EEPROM should save the current slave id */
} Eeprom_eAction_t;

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * Eeprom initialisation
 *
 * Initialises the eeprom module
 *
 * @param       measParameter   Pointer to the measurement parameter struct in ram
 *
 * @return      bool_t          true if init was successful, else false
 * ****************************************************************************/
bool_t Eeprom_Init(Meas_uMeasurementParameters_t* measParameter);

/* **************************************************************************//**
 * @brief
 * Get data pointer
 *
 * Returns a pointer to the measurement parameter struct in eeprom
 *
 * @return      Meas_uMeasurementParameters_t   Pointer to measurement paramter strcut in eeprom
 * ****************************************************************************/
Meas_uMeasurementParameters_t* Eeprom_GetDataPointer(void);

/* **************************************************************************//**
 * @brief
 * Eeprom task
 *
 * Executes the eeprom state machine and needs to be called in the main loop
 *
 * @return      none
 * ****************************************************************************/
void Eeprom_Task(void);

/* **************************************************************************//**
 * @brief
 * Set operation
 *
 * If the correct password is given to this function and the eeprom is
 * not busy, this function changes the mode of the eeprom state machine
 *
 * @param       operation           The operation to execute on the eeprom state machine
 * @param       password            Password for eeprom access
 *
 * @return      Eeprom_eError_t     eeprom error code
 * ****************************************************************************/
Eeprom_eError_t Eeprom_SetOperation(Eeprom_eAction_t operation, uint8_t password);

/* **************************************************************************//**
 * @brief
 * Check if busy
 *
 * Checks if the EEPROM module is busy
 *
 * @return      bool_t      true if busy, else false
 * ****************************************************************************/
bool_t Eeprom_CheckIfBusy(void);

/* **************************************************************************//**
 * @brief
 * Disable eeprom
 *
 * Disables the access to eeprom, so it needs to be reenabled
 * to get access
 *
 * @return      none
 * ****************************************************************************/
void Eeprom_Disable(void);

#endif /* EEPROM_H_ */


