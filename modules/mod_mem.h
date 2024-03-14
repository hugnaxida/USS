/***************************************************************************//**
 * @file      mod_mem.h
 *
 * @author    StSl
 * @date      30.11.2017
 *
 * @brief     RAM check module (header)
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
 * $Id: mod_mem.h 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
 *
 ******************************************************************************/

#ifndef MEM_H_
#define MEM_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "def_app.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/


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
 * Memory initialisation
 *
 * Initialises all memory related variables
 *
 * @param       measParameterInRam  pointer to measurement parameters in ram
 *
 * @return      bool_t              true if init was successful, else false
 * ****************************************************************************/
bool_t mem_Init(Meas_uMeasurementParameters_t* measParameterInRam);

/* **************************************************************************//**
 * @brief
 * Memory Task
 *
 * The main task of the memory module. If triggered it calculates the crc over the
 * measurement parameters in ram and saves the result
 *
 * @return      none
 * ****************************************************************************/
void mem_Task(void);

/* **************************************************************************//**
 * @brief
 * Trigger CRC calculation over ram
 *
 * set a flag, to trigger a crc calculation over the measurement parameters
 * in ram. The result is saved to ram
 *
 * @return      none
 * ****************************************************************************/
void mem_TriggerCrcCalculationOverRam(void);

#endif /* MEM_H_ */


