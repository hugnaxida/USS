/** @addtogroup dsi3_Driver_interfaces
 * @{ */
/***************************************************************************/
/** @file      Dsi3Bus_Defaults.h
 *
 * @brief      Definitions of default values for DSI3 communication.
 *
 * @purpose   Definitions of default values for DSI3 communication as specified in
 *            the DSI3 Bus Standard Revision 1.00 February 16, 2011.
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
 *
 * @section history_sec_Dsi3Bus_Default_h Revision History
 * $Id: Dsi3Bus_Defaults.h 392 2019-01-22 09:59:18Z siko $
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who Ver  Comment
 * -------------------------------------------------------------------
 * 18/01/17 (F) POE 1002 updated header and demo usage disclaimer
 * ...
 * 17/06/19 (F) POE 1000 initial version
 * -------------------------------------------------------------------
 * @endverbatim
 *
 * @creator      POE
 * @created      2017/06/19
 *
 * @project      524.17
 * @requested    ELMOS
 * @inspector    -
 * @verification -
 * @version      $Revision: 392 $
 *
 *
 * $State: Exp $
 * $Author: siko $
 *
 * Additional markers:
 *
 */
#ifndef __DSI3_DEFAULT_H__
#define __DSI3_DEFAULT_H__

  #define DSI3_NAD_BROADCAST                            (    0u)        /**< CRM NAD address reserverd for broadcast messages */
  #define DSI3_NAD_MAX_DEFAULT                          (   15u)        /**< Default: number of slave hardcap as defined by DSI3 spec */

  #define DSI3_CRM_NUMBER_OF_COMMANDS                   (   16u)        /**< Number of different command assignment in Command and Response Mode */
  #define DSI3_PDCM_NUMBER_OF_COMMANDS                  (    1u)        /**< Number of  pdcm command assignments (technically, only 1 is ever allowed) */

  /* Response time relative to start of crm signal */
  #define DSI3_CRM_RESPONSE_TIME_MIN                    (  280u)        /**< Default: minimal response time offset (us) as defined by DSI3 spec */
  #define DSI3_CRM_RESPONSE_TIME_MAX                    (  310u)        /**< Default: maximal response time offset (us) as defined by DSI3 spec */
  #define DSI3_CRM_RESPONSE_TIME_TYP                    (  295u)        /**< Default: response time offset (us) as defined by DSI3 spec */
  #define DSI3_CRM_RESPONSE_DURATION_3US                (   96u)        /**< Default: CRM response duration (us) @3us chiptime */
  #define DSI3_CRM_RESPONSE_DURATION_4US                (  128u)
  #define DSI3_CRM_RESPONSE_DURATION_5US                (  160u)
  #define DSI3_CRM_RESPONSE_DURATION_6US                (  192u)


  /* Response time relative to start of pdcm signal */
  #define DSI3_PDCM_RESPONSE_START_TIME_DEFAULT         (   15u)        /**< PDCM minimal response start time (us) as defined by DSI3 spec */
  #define DSI3_PDCM_PERIOD_MIN                          (  100u)        /**< PDCM minimal period duration (us) as defined by DSI3 spec */
  #define DSI3_PDCM_PERIOD_MAX                          ( 5000u)        /**< PDCM maximal period duration (us) as defined by DSI3 spec */

  #define DSI3_DRV_DISC_PERIOD_LENGTH_DEFAULT           (  125u)        /**< DISCOVERY mode default period duration (us) as defined by DSI3 spec */
#endif
/** @} dsi3_Driver_interfaces */
