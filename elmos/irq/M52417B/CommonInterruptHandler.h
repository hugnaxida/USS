/* ------------------------------------------------------------------- */
/** @file CommonInterruptHandler.h
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
 * 15/13/01 (F) poe 1001 first creation
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
 * @version      $Revision: 383 $
 *
 *
 * $State: Exp $
 * $Author: siko $
 *
 * Additional markers:
 *
 */
#ifndef COMMONINTERRUPTHANDLER_H_
#define COMMONINTERRUPTHANDLER_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "nvic_Interface.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ******************************************** ********************************/

/* ****************************************************************************/
/* ********************* EXTERNAL FUNCTIONS / INTERFACE ***********************/
/* ****************************************************************************/

/***************************************************************************//**
 * Initialize interrupt handler in NVIC
 *
 * @param       nvicIf: Interface to function calls for NVIC handling
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * The interrupt environment is initialized to 0x0, global IRQ handling is 
 * initialized and interrupts are enabled at NVIC level.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void InterruptHandlerInitialize(nvic_cpInterfaceFunctions_t nvicIf);

#endif /* COMMONINTERRUPTHANDLER_H_ */
