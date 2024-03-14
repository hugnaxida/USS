/***************************************************************************//**
 * @file      mod_crc16.h
 *
 * @author    StSl
 * @date      30.11.2017
 *
 * @brief     CRC16 module initialize and handles the CRC HW (header)
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
 * $Id: mod_crc16.h 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
 *
 ******************************************************************************/

#ifndef CRC16_H_
#define CRC16_H_

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
 * CRC16 initialisation
 *
 * Initialises all CRC16 related hardware registers
 *
 * @return      none
 * ****************************************************************************/
void crc16_Init(void);

/* **************************************************************************//**
 * @brief
 * Check crc
 *
 * Calculates the crc16 value over the given memory area and compares
 * it with the given expected crc value.
 *
 * @param       startAddress  Address of memory on which to calculate the crc
 * @param       numBytes      Number of bytes to use for the crc calculation
 * @param       expectedCrc   Expected crc, the calculated crc will be checked against
 * @param       returnCrc     Pointer to buffer, where the crc result should be saved. Ignored if NULL
 *
 * @return      bool_t        true if expectedCrc matched calculated crc, else false
 * ****************************************************************************/
bool_t crc16_checkCrc(uint32_t startAddress, uint32_t numBytes, uint16_t expectedCrc, uint16_t* returnCrc);

#endif /* CRC16_H_ */


