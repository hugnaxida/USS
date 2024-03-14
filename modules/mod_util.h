/***************************************************************************//**
 * @file      mod_util.h
 *
 * @creator   KeLe
 * @created   22.11.2017
 *
 * @brief     Useful Functions (header)
 *
 * @purpose
 *
 * Useful cross-module functions.
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
 ******************************************************************************/

#ifndef MODUTIL_H_
#define MODUTIL_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "stdint.h"
/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
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
 * Convert Pointer to Memory Address Offset
 *
 * Converts a Pointer, which has to be located in SRAM, to its
 * offset to the SRAM base address
 *
 * @param       pointer          Pointer in SRAM Memory
 * @return      Offset of given pointer to SRAM base address
 * ****************************************************************************/
uint16_t util_calculateDmaMemoryOffset(void* pointer);

/* **************************************************************************//**
 * @brief
 * Calculate the currently set transducer frequency
 *
 * @return      currently set transducer_frequency
 * ****************************************************************************/
uint32_t util_CalcBurstFrequency(void);

#endif /* MODUTIL_H_ */
