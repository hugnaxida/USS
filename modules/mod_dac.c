/** @file mod_dac.c
 * @brief DAC configuration and access module
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
 * @section history_sec_mod_dac_c Revision History
 * $Id: mod_dac.c 394 2019-01-23 15:20:39Z siko $
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who  Comment
 * -------------------------------------------------------------------
 * 17/06/13 (F) JNAU initial version
 * -------------------------------------------------------------------
 * @endverbatim
 *
 *
 * @creator      JNAU
 * @created      2017/06/13
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

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_dac.h"

//################################################################################
// DAC

// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/



/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* *************************************************************************//**
 * @implementation
 * Initializes the two DAC modules
 *
 * @return
 * ****************************************************************************/
void dac_Init(void)
{
  /***************************************************************************
   * option 1: show register values, which are set by:
   * DAC_REG0_SET(val) and DAC_REG1_SET(val) with the commands:
   * dac_SetDACFunction(dac_DAC0, dac_eDacCtrl_REG) and dac_SetDACFunction(dac_DAC1, dac_eDacCtrl_REG)
   *
   * option 2: show the contents of the threshold and envelope register with the command:
   * dac_SetDACFunction(dac_DAC0, dac_eDacCtrl_ENV) and dac_SetDACFunction(dac_DAC1, dac_eDacCtrl_TH)
   ****************************************************************************/

  /* Set DAC0 to show the content of the envelope register */
  dac_SetDACFunction(dac_DAC0, dac_eDacCtrl_ENV);
  
  /* Set DAC1 to show the content of the threshold register */
  dac_SetDACFunction(dac_DAC1, dac_eDacCtrl_TH);
}

/* *************************************************************************//**
 * @implementation
 * set the functionality of the chosen DAC module
 *
 * @param       dac                    DAC module whose functionality should be set
 * @param       func                   functionality the chosen DAC should be set to
 * @return      
 * ****************************************************************************/
void dac_SetDACFunction(dac_DAC_t dac, dac_DacCtrl_t func)
{
  if (dac_DAC0 == dac)
  {
    DAC_CTRL_DAC0_SET(func);
  }
  else
  {
    DAC_CTRL_DAC1_SET(func);
  }
}
