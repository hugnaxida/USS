/***************************************************************************//**
  * @file       mod_swt.c
  * @brief      SW_TIMER configuration and access module
  *
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
  * @section history_sec_mod_swt_c Revision History
  * $Id: mod_swt.c 392 2019-01-22 09:59:18Z siko $
  *
  * @verbatim
  * -------------------------------------------------------------------
  * Date     B/F Who Comment
  * ------------------------------------------------------------------- 
  * 17/05/27 (F) POE initial version
  * -------------------------------------------------------------------
  * @endverbatim
  * 
  *
  * @creator      POE
  * @created      2017/05/27
  * 
  * @project      524.17
  * @requested    -
  * @inspector    - 
  * @verification -
  * @version      $Revision: 392 $
  * 
  * 
  * $State: Exp $   
  * $Author: siko $
  * $Date: 2019-01-22 10:59:18 +0100 (Di, 22 Jan 2019) $

  * $Locker:  $
  * $Url:   $
  *
  * Additional markers:
  *
  *
  *
  */

/*################################################################################
  SW Timer
  ################################################################################
*/

/* SW timer is used as a 1 ms time base / tick counter. */


/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_swt.h"
#include "swtimer_InterruptHandler.h"
#include "nvic_InterruptHandler.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

/* timer clock 24MHz / (23+1) -> 1MHz */
#define SWT_TICK_TIMER_PRESCALER_VAL    23
/* timer expected to run at 1MHz (31+1) -> IRQ every 32us */
#define SWT_TICK_TIMER_RELOAD_VAL       31

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/
/* SWT interrupt controller environment data */
static swtimer_sInterruptEnvironmentData_t swtimer_envData;

/* ****************************************************************************/
/* ******************** FORWARD DECLARATIONS / PROTOTYPES *********************/
/* ****************************************************************************/


/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* ****************************************************************************
 * @implementation
 * SWT initialization
 *
 * @param       none
 * @return      none
 * ****************************************************************************/
void swtimer_Init(void)
{
  /* Initialize SWT IRQ */  
  swtimer_InterruptInitialisation(&nvic_InterfaceFunctions,&swtimer_envData, NULL);
  
  nvic_InterfaceFunctions.SetModulePriority(nvic_IRQ_SWTIMER, nvic_Priority_Level_2);
   

  /* Set timer0 reload and divider */
  SWT_CNT_RELOAD_SET(swtimer_eTimer_0, SWT_TICK_TIMER_RELOAD_VAL);
  SWT_DIV_RELOAD_SET(swtimer_eTimer_0, SWT_TICK_TIMER_PRESCALER_VAL);
  SWT_ENABLE(swtimer_eTimer_0);
  
  /* set timer1 divider */
  SWT_DIV_RELOAD_SET(swtimer_eTimer_1, SWT_TICK_TIMER_PRESCALER_VAL);
  SWT_ENABLE(swtimer_eTimer_1);
}

/* ****************************************************************************
 * @implementation
 * Register a custom ISR for a timer count zero interrupt.
 *
 * @param       timer           target timer
 * @param       cb              pointer to custom isr function
 * @return      TRUE            if assignment successful
 * ****************************************************************************/
bool_t swtimer_RegisterCustomZeroCountInterruptCallback(swtimer_Timer_t timer,  swtimer_InterruptCallback_t cb)
{
  bool_t retVal = FALSE;
  switch(timer)
  {
    case swtimer_eTimer_0:
    {
      swtimer_InterruptRegisterCallback(swtimer_IRQ_EVT_CNT_ZERO_0, cb);
      retVal = TRUE;
    }
    break;
    case swtimer_eTimer_1:
    {
      swtimer_InterruptRegisterCallback(swtimer_IRQ_EVT_CNT_ZERO_1, cb);
      retVal = TRUE;
    }
    break;
    default:
    break;
  }
  return retVal;
}

