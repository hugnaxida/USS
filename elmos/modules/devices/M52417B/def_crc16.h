/* ------------------------------------------------------------------- */
/** @file def_crc16.h
 *
 * @brief Helper definitions for CRC16 hardware module.
 *
 * Purpose:
 * Provide register access and register value definitions 
 * for CRC16 hardware module
 *
 * Demo Code Usage Restrictions:
 * Elmos Semiconductor AG provides this source code file simply and solely for
 * IC evaluation purposes in laboratory and this file must not be used for other 
 * purposes or within non laboratory environments. Especially, the use or the
 * integration in production systems, appliances or other installations is
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
 * @section history_sec_crc16mod Revision History
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date      B/F Who  Ver  Comment
 * -------------------------------------------------------------------
 * 18/10/22 (F)  siko 1000 first creation
 * -------------------------------------------------------------------
 * @endverbatim
 *
 * @creator      siko   
 * @created      2018/10/22
 *
 * @project      524.17
 * @requested    ELMOS
 * @inspector    -
 * @verification -
 * @version      $Revision: 1.0 $
 *
 *
 * $State: Exp $
 * $Author: siko $
 *
 * Additional markers:
 *
 */
#ifndef _DEF_CRC16_H_
#define _DEF_CRC16_H_
//################################################################################
//  Helper defines
//################################################################################
/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include <io_m52417b.h>
/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
  
/* CRC16_CONFIG */
#define CRC16_CFG_CLEARSUM                  (CRC16_CONFIG_bit.keep_sum = 0u)
#define CRC16_CFG_KEEPSUM                   (CRC16_CONFIG_bit.keep_sum = 1u)
#define CRC16_CFG_TIMING(num)                 (CRC16_CONFIG_bit.timing   = ((uint16_t)num && 0x07u))

/*   
#define    CRC16_STATUS_bit
     CRC16_EXPECTED_CRC_bit
       CRC16_LENGTH1_bit.bytes
         CRC16_LENGTH0_bit.bytes
           CRC16_START0_bit.addr
             CRC16_START1_bit.addr
               CRC16_CRC_SUM_bit.crc
*/

#endif /* _DEF_CRC16_H */
