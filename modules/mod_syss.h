/* *************************************************************************//**
 * @file			mod_syss.h
 *
 * @creator		poe
 * @created		02.07.2017
 * @sdfv                Demo Flow
 *
 * @brief  		Initialization of system-state module and sys-state IRQ handler
 *
 * @purpose
 *
 * The System State Module handling CPU clock frequency configurations,
 * ADC clock settings, Reset source status and configurations and
 * it can enable/disable some hardware modules.
 *
 * ******************************************************************************
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
 * $Id: mod_syss.h 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
 *
 * *****************************************************************************/

#ifndef SYSS_SYSTEMSTATE_H_
#define SYSS_SYSTEMSTATE_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "elmos/modules/devices/M52417A/def_syss.h"
#include "elmos/irq/M52417A/nvic_InterruptHandler.h"
#include "elmos/irq/M52417A/sys_state_InterruptHandler.h"
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
extern nvic_cpInterfaceFunctions_t nvic_IfFuns;

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* *****************************************************************************
 * @brief Initialize SYSS module
 *
 * @param environmentdata  Pointer to Environment data for SYSS module in
 *                         user RAM
 *
 * @pre        NVIC (nvic_VectorInterruptControl) and SYSS (syss_SystemState)
 *             have to presented and initialized.n
 *
 * @post       SYSS module is configured for use.
 *
 * @detaildesc
 * Initializes the SYSS software and hardware module, including the module
 * interrupt vector table. 
 *
 * *****************************************************************************/
void syss_Init(void);

/* **************************************************************************//**
 * @brief
 * Enter Sleep
 *
 * Initializes and enters standby mode
 *
 * @return      none
 * ****************************************************************************/
void syss_EnterSleep(void);

/* **************************************************************************//**
 * @brief
 * Exit Sleep
 *
 * Exits and Deinitializes standby mode
 *
 * @return      none
 * ****************************************************************************/
void syss_ExitSleep(void);


/* **************************************************************************//**
 * @brief
 * Processes requests to change the standby mode
 *
 * @return      none
 * ****************************************************************************/
void syss_ProcessStandbyRequests(void);
#endif /* SYSS_SYSTEMSTATE_H_ */
