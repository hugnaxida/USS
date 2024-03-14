 /* ------------------------------------------------------------------- */
/** @file nvic_InterruptHandler.h
 *
 * @brief NVIC Interrupt handler for interrupt controller implementation.
 *
 * Purpose:
 *  NVIC Interrupt handler for interrupt controller implementation
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
#ifndef NVIC_INTERRUPTHANDLER_H_
#define NVIC_INTERRUPTHANDLER_H_

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
/* ****************************************************************************/
extern const nvic_sInterfaceFunctions_t nvic_InterfaceFunctions;

/* ****************************************************************************/
/* ********************* EXTERNAL FUNCTIONS / INTERFACE ***********************/
/* ****************************************************************************/

/***************************************************************************//**
 * Return pointer to interrupt environment for given exception vector number.
 *
 * @param       vno: Exception vector number
 *
 * @return      Pointer to interrupt environment
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Return pointer to interrupt environment for given exception vector number.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
nvic_pInterruptModuleEnvironmentData_t nvic_GetPointerToEnvironmentData(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * Register interrupt handler and interrupt environment
 *
 * @param       Exception vector number
 *              Interrupt handler callback
 *              Module Environment Data
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Register interrupt handler and interrupt environment for module according to 
 * given exception vector number.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_RegisterModule(nvic_eExceptionVectorNum_t vno, nvic_InterruptCallback_t interrupthandler, nvic_pInterruptModuleEnvironmentData_t moduleenvironmentdata);

/***************************************************************************//**
 * De-register interrupt handling in NVIC
 *
 * @param       Exception vector number
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Disable given module in NVIC. Set interrupt handler function to default 
 * exception handler for system IRQs or default interrupt handler for module 
 * interrupts. Invalidate pointer to interrupt environment.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_DeregisterModule(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * Enable interrupts for module
 *
 * @param       Exception vector number
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Clear pending IRQs and enable IRQs for given module.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_EnableModule(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * Disable interrupts for module
 *
 * @param       Exception vector number
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Check exception vector number for valid range. 
 * Disable IRQs for given module.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_DisableModule(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * Clear pending IRQs for given module.
 *
 * @param       Exception vector number
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Clear pending IRQs for given module.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_ClearPending(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * Set pending IRQs for given module.
 *
 * @param       Exception vector number
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Set pending IRQs for given module.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_SetPending(nvic_eExceptionVectorNum_t vno);


/***************************************************************************//**
 * Set IRQ priority for given module.
 *
 * @param       Exception vector number
 *              Interrupt priority
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Set IRQ priority for given module.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_SetModulePriority(nvic_eExceptionVectorNum_t vno, nvic_ePriorityLevels_t prio);

/***************************************************************************//**
 * Globally enable interrupts in NVIC
 *
 * @param       void
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Globally enable interrupts in NVIC
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_EnableMain(void);

/***************************************************************************//**
 * Globally disable interrupts in NVIC
 *
 * @param       void
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Globally disable interrupts in NVIC
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_DisableMain(void);

/***************************************************************************//**
 * @brief Initialize VIC module
 *
 * @param environmentdata  Pointer to Environment data for VIC module in
 *                         user RAM
 *
 * @pre        VIC (vic_VectorInterruptControl) and SYSS (syss_SystemStateModule)
 *             have to present and initialized.
 *
 * @post       VIC module is configured for use.
 *
 * @detaildesc
 *
 ******************************************************************************/
bool_t nvic_IRQInitialisation(nvic_pInterruptEnvironmentData_t penvironmentdata);


#endif /* NVIC_INTERRUPTHANDLER_H_ */
