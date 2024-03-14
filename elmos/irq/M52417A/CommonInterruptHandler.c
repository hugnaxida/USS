/* ------------------------------------------------------------------- */
/** @file CommonInterruptHandler.c
 *
 * @brief Common Interrupt handler for interrupt controller implementation.
 *
 * Purpose:
 * Common Interrupt handler for interrupt controller implementation.
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
 * @section history_sec Revision History
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who Ver  Comment
 * -------------------------------------------------------------------
 * 15/13/01 (F) rpy 1001 first creation
 * -------------------------------------------------------------------
 * @endverbatim
 *
 * @creator      rpy
 * @created      2015/13/01
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

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "el_helper.h"
#include "CommonInterruptHandler.h"

#include "nvic_InterruptHandler.h"

#include <stdint.h>
#include <stddef.h>

/* ****************************************************************************/
/* ***************************** QA-C EXCLUDES ********************************/
/* ****************************************************************************/

/*** locally ***/

/*  
* Exception:
* Msg(2:0310) Casting to different object pointer type.
*
* Circumstances and justification:
* -> see local suppression comment
* 
* Potential consequences:
* Underlying data structures of the two pointer types do not fit. Uncontrolled
* memory access may occure.
*
* Alternative safety assurance:
* Check consistency by code review or during tests
*
*/


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

/*  
* Exception:
* Msg(2:3218) File scope static, '...', is only accessed in one function.
*
* Circumstances and justification:
* loc_NvicEnvironmentData is the environment data for interrupt handling. It is
* provided by this module for "cross-module" use. Therefore it is more natural
* to define it as a symbol belonging to this module, than define it as a 
* static symbol in the function, where it is passed to other modules. 
* 
* Potential consequences:
* None, it is a symbol located in RAM in either cases
*
* Alternative safety assurance:
* None
*/
// PRQA S 3218 1
static nvic_sInterruptEnvironmentData_t loc_NvicEnvironmentData;

/* ****************************************************************************/
/* ******************** FORWARD DECLARATIONS / PROTOTYPES *********************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/***************************************************************************//**
 * @implementation
 * First check, whether the interface to NVIC is set and the NVIC interface
 * version fits.
 * If the checks are passed, the interrupt environment is initialized to 0x0,
 * the global IRQ handling is initialized and interrupts are enabled 
 * at NVIC level.
 *
 ******************************************************************************/
void InterruptHandlerInitialize(nvic_cpInterfaceFunctions_t nvicIf)
{
  if ((nvicIf != (const void *) NULL) && (nvicIf->InterfaceVersion == NVIC_INTERFACE_VERSION))
  {    
    /* 
    *Initialize environment data with 0
    *
    * Cast to uint8_t * is needed to call generic function for filling memory 
    * location. Cast to smallest possible memory unit will work as expected.
    */
    // PRQA S 0310 1
    el_FillBytes(0u, (uint8_t*) &loc_NvicEnvironmentData, sizeof(nvic_sInterruptEnvironmentData_t));

    /* Init global IRQ handling */ 
    (void) nvicIf->IRQInitialisation(&loc_NvicEnvironmentData);
  
    /* Enable all IRQs at VIC level */
    nvicIf->EnableMain();
  }
  else { }
}

