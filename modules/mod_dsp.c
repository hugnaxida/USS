/***************************************************************************//**
  * @file mod_dsp.c
  * @brief DSP configuration and access module
  *
  * Purpose:
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
  * @section history_sec Revision History
  * $Id: mod_dsp.c 394 2019-01-23 15:20:39Z siko $
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
  * @created      2017/07/02
  * 
  * @project      524.17
  * @requested    -
  * @inspector    - 
  * @verification -
  * @version      $Revision: 394 $
  * 
  * 
  * $State: Exp $   
  * $Author: siko $
  * $Date: 2019-01-23 16:20:39 +0100 (Mi, 23 Jan 2019) $

  * $Locker:  $
  * $Url:   $
  *
  * Additional markers:
  *
  *
  *
  */

/*################################################################################
  DSP
  ################################################################################
*/


/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_dsp.h"
#include "dsp_InterruptHandler.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/

static dsp_sInterruptEnvironmentData_t dsp_envData; /* DSP interrupt controller environment data */

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* ************************************************************************//**
 * @implementation
 * DSP initialization
 *
 * @param       none
 * @return
 * ****************************************************************************/
void dsp_Init(void)
{     
  /* Initialize DSP IRQ */  
  dsp_InterruptInitialisation(&nvic_InterfaceFunctions,&dsp_envData, NULL);
  
  /* Set module priority level */
  nvic_InterfaceFunctions.SetModulePriority(nvic_IRQ_DSP, nvic_Priority_Level_1);
}

/* ************************************************************************//**
 * @implementation
 * Register a custom ISR for a specific interrupt
 *
 * @param       irqNum          target irq
 * @param       cb              pointer to custom isr function
 * @return      TRUE            if assignment successful
 * ****************************************************************************/
bool_t dsp_RegisterCustomInterruptCallback(dsp_eInterruptVectorNum_t irqNum,  dsp_InterruptCallback_t cb)
{
  bool_t retVal = FALSE;

  if (dsp_INTERRUPT_VECTOR_CNT > irqNum) 
  {
    dsp_InterruptRegisterCallback((dsp_eInterruptVectorNum_t)irqNum, cb);
    retVal = TRUE;
  }

  return retVal;
}

