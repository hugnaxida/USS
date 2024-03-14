/* **************************************************************************//**
  * @file       mod_swt.h
  * @brief      SW_TIMER configuration and access module (header)
  *
  * TODO: A detailed description of this module
  *    
  * ****************************************************************************
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
  * @section history_sec_mod_swt_h Revision History
  * $Id: mod_swt.h 392 2019-01-22 09:59:18Z siko $
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
  *
  * $Locker:  $
  * $Url:   $
  *
  * Additional markers:
  *
  *
  *
 ******************************************************************************/

/*################################################################################
  SW Timer
  ################################################################################
*/

#ifndef MOD_swtimer_H_
#define MOD_swtimer_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "def_swtimer.h"
#include "swtimer_InterruptHandler.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
                                       
/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* ****************************************************************************
   * @implementation
   * SWT initialization
   * @return ---
   **************************************************************************** */
void swtimer_Init(void);

/* ****************************************************************************
 * @implementation
 * Register a custom ISR for a timer count zero interrupt.
 * @param       none,
 * @return      none
 * ****************************************************************************/
bool_t swtimer_RegisterCustomZeroCountInterruptCallback(swtimer_Timer_t timer, swtimer_InterruptCallback_t cb);


#endif /*MOD_swtimer_H_*/

