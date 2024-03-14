/* *************************************************************************//**
 * \file                mod_wdg.c
 *
 * \creator             siko
 * \created             03.07.2018
 * \sdfv                Demo Flow
 *
 * \brief               Watchdog module initialize and handles the watchdog HW
 *
 * This watchdog module handles the watchdog(WDG) hw functionality. It provides 
 * interface functions for initializing, start and trigger the watchdog.
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
 * $Id: mod_wdg.c 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
 *
 ******************************************************************************/

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_wdg.h"

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
/* ******************** FORWARD DECLARATIONS / PROTOTYPES *********************/
/* ****************************************************************************/


/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* *************************************************************************//**
 * \brief Initialize WDG module
 *
 * \param      none
 *
 * \pre        nvic is initialized
 *
 * \post       Watchdog module is configured for use.
 *
 * \details
 * Initializes the Watchdog software and hardware module
 *
 * ****************************************************************************/
void wdg_Init(void)
{
    WDOG_RELOAD_SET(WDG_RELOAD_VALUE);
    WDOG_PRESCALE_SET(WDG_PRESCALER);
    
    /* No watchdog window set for this demo
    WDOG_WINDOW_SIZE_SET(WDG_WINDOW_SIZE)
    WDOG_WINDOW_ENABLE()  */
    
    SYS_STATE_RESET_ENABLE |= E_SYS_STATE_RESET_ENABLE_WATCHDOG_ZERO;     /*< Set watchdog counted to zero reset enable flag*/
    /* also enables the supervision of the sys_clock see SM102 */
}
    
/* *************************************************************************//**
 * \brief  Triggers (resets) the watchdog.
 *
 * \param      none
 *
 * \pre        Watchdog is started
 *
 * \post       Watchdog counter is reset
 *
 * ****************************************************************************/
void wdg_Trigger(void)
{
  /* Restart the watchdog */
  WDOG_CONTROL_RESTART();
}

/* *************************************************************************//**
 * \brief  Starts the watchdog. This also supervises the System OSC see SM105.
 *
 * \param      none
 *
 * \pre        Watchdog is initialized
 *
 * \post       Watchdog starts working
 *
 * ****************************************************************************/
void wdg_Start(void)
{
  /* Enable the watchdog */
  WDOG_CONTROL_RUN_ENABLE();
  
  /* Restart the watchdog */
  WDOG_CONTROL_RESTART();
}
