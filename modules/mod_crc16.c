/***************************************************************************//**
 * @file      mod_crc16.c
 *
 * @author    StSl
 * @date      30.11.2017
 *
 * @brief     CRC16 module initialize and handles the CRC HW
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
 * $Id: mod_crc16.c 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
 *
 ******************************************************************************/

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_crc16.h"
#include "mod_err.h"

/* ****************************************************************************/
/* **************************** CUSTOM INCLUDES *******************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define CRC16_STATUS_CALCULATION_RUNNING  (0u)                      /**< CRC16 - Status indicates running measurement */
#define CRC16_STATUS_PASS                 (1u)                      /**< CRC16 - Status indicates successful measurement */
#define CRC16_STATUS_FAIL                 (2u)                      /**< CRC16 - Status indicates failed measurement */

/* ****************************************************************************/
/* ***************************** GLOBAL VARIABLES *****************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* ************************** FUNCTION PROTOTYPES *****************************/
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
void crc16_Init(void)
{
  /* reset CRC sum register on calculation start */
  CRC16_CONFIG_bit.keep_sum = 0u;
  /* divide clock for CRC hardware by 2^timing, to not block the memory */
  CRC16_CONFIG_bit.timing = 0u;
}

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
bool_t crc16_checkCrc(uint32_t startAddress, uint32_t numBytes, uint16_t expectedCrc, uint16_t* returnCrc)
{
  bool_t retval = false;

  /* if crc16 hardware is already running, wait for it to finish */
  uint16_t crcState = 0u;
  do
  {
    crcState = CRC16_STATUS_bit.state;
  }
  while(CRC16_STATUS_CALCULATION_RUNNING == crcState);

  /* write expected CRC to crc16 register */
  CRC16_EXPECTED_CRC_bit.crc = expectedCrc;
  /* write number of bytes which have to be controlled into crc16 register */
  CRC16_LENGTH1_bit.bytes = (numBytes & 0xFFFF0000u) >> 16u;  /* msb */
  CRC16_LENGTH0_bit.bytes = numBytes & 0x0000FFFFu;          /* lsb */
  /* write lsb of memory address for crc checking to crc16 register */
  CRC16_START0_bit.addr = ((uint32_t)startAddress) & 0x0000FFFFu;
  /* write msb of memory address for crc checking to crc16 register, which starts the crc calculation */
  CRC16_START1_bit.addr = (((uint32_t)startAddress) & 0xFFFF0000u) >> 16u;

  /* wait for crc calculation to be finished */
  do
  {
    crcState = CRC16_STATUS_bit.state;
  }
  while(CRC16_STATUS_CALCULATION_RUNNING == crcState);

  /* save the crc result if requested */
  if(NULL != returnCrc)
  {
    *returnCrc = CRC16_CRC_SUM_bit.crc;
  }
  else
  {
    /* nothing to do here */
  }

  /* check if crc was correct */
  if(CRC16_STATUS_FAIL == crcState)
  {
    /* CRC mismatch -> return false */
    retval = false;
  }
  else
  {
    /* everything ok -> return true */
    retval = true;
  }

  return retval;
}
