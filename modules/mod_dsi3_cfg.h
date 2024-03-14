/***************************************************************************//**
 * @file      mod_dsi3_cfg.h
 *
 * @creator   poe
 * @created   24.04.2017
 * @sdfv      Demo Flow
 *
 * @brief     DSI3 configuration module initializes and configures the DSI3 bus layer (header)
 *
 * @purpose
 *
 * TODO: A detailed description of this module
 *
 *******************************************************************************
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
 * $Id: mod_dsi3_cfg.h 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
 *
 ******************************************************************************/

#ifndef DSI3_CONFIG_H_
#define DSI3_CONFIG_H_

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define DSI3_CFG_INITIAL_NAD                  (0x07u)           /**< Slave Address at startup time */
#define DSI3_CFG_MAXIMAL_NAD                  (0x07u)           /**< Maximal numbers of allowed slaves ( 0 < maxNAD <= 15) */
#define DSI3_CFG_HW_CRC                       TRUE              /**< TRUE - hardware adds crc automatically to transmission */
#define DSI3_CFG_HW_AUTOSYNC                  FALSE             /**< FALSE - hardware does not automatically sync dsi3 clock */
#define DSI3_CFG_SW_SLAVEID_PREFILTER         TRUE              /**< TRUE - Enables filtering of crm messages that are not broadcast and not adressed to this node */  
#define DSI3_CFG_PDCM_BUFOUT_SIZE             (8u)              /**< Application definition for desired PDCM response buffer size */
#define DSI3_CFG_SKIP_CRM_ON_PDCM_ERR_EVT     FALSE             /**< Enables to ignore first CRM cmd during PDCM mode */
#define DSI3_CFG_CRM_RESPONSE_TIME_OFFSET     (305u)            /**< Time offset of the crm response msg (default: 300us) */
#define DSI3_CFG_PDCM_SLOT_TIME               (192u + 1u)       /**< time in �s of one pdcm time slot plus empirical evaluated correction value */

/* ****************************************************************************/
/* **************************** INTERFACE OPTIONS *************************** */
/* ****************************************************************************/

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "elmos/DSI3Drv/devices/M52417A/Bus/Dsi3Bus_Implementation.h"
#include "def_app.h"
/* ****************************************************************************/
/* ***************************** USER INCLUDES ********************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************* BASIC DSI CONFIGURATION ************************ */
/* ****************************************************************************/

/* ****************************************************************************/
/*                                  Bus Layer                                 */
/* ****************************************************************************/

/* ****************************************************************************/
/*                               Diagnose Layer                               */
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************* CALLBACK CONFIGURATION ************************* */
/* ****************************************************************************/

/* ****************************************************************************/
/*                                  Bus Layer                                 */
/* ****************************************************************************/

/* ****************************************************************************/
/* ********************** ADVANCED DRIVER CONFIGURATION ********************* */
/* ****************************************************************************/

/* ****************************************************************************/
/*                                  Bus Layer                                 */
/* ****************************************************************************/


/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/
extern Dsi3BusIf_cpInterfaceFunctions_t         Dsi3_BusIfFuns;                         /* Pointer to DSI3 interface functions */
extern Dsi3HwModIf_cpInterfaceFunctions_t       Dsi3DrvImp_HWModIfFuns;                 /* Pointer to DSI3 HW module related interface functions */

#if defined ( EL_COMPILER_KEIL )
  extern uint8_t Dsi3_BusEnvData[DSI3BUSIMP_ENVIRONMENT_DATA_SZE] __attribute__((aligned));
#elif defined ( EL_COMPILER_IAR )
  #pragma data_alignment=4
  extern uint8_t Dsi3_BusEnvData[DSI3BUSIMP_ENVIRONMENT_DATA_SZE];
#elif defined ( EL_COMPILER_GCC )
  extern uint8_t Dsi3DrvImp_BusEnvData[DSI3BUSIMP_ENVIRONMENT_DATA_SZE] __attribute__((aligned));
#else
  #error "Unsupported compiler type"

#endif


/* ****************************************************************************/
/* ********************* EXTERNAL FUNCTIONS / INTERFACE ***********************/
/* ****************************************************************************/

  /* **************************************************************************//**
   * @brief: DSI3 driver initialization.
   *
   * @param       nvicIfFuns      pointer to NVIC interface functions
   * @param       pAppData        pointer to Application control and runtime data
   *
   * @return      TRUE  - DSI3 driver initialization completed successfully
   *              FALSE - else
   * *****************************************************************************/
bool_t Dsi3_Init(nvic_cpInterfaceFunctions_t nvicIfFuns, Dsi3Drv_sApplCtrlData_t* pAppData);

/* **************************************************************************//**
 * @brief DSI3 return controll struct
 *
 * @return      Pointer to DSI3 control data
 * *****************************************************************************/
extern Dsi3Drv_sDSI3Ctrl_t* Dsi3_GetDSI3Ctrl(void);

#endif /* DSI3_CONFIG_H_ */
