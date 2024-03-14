/* ------------------------------------------------------------------- */
/** @file sys_ctrl_InterruptHandler.h
 *
 * @brief Module interrupt handler for SYS_CTRL hardware module.
 *
 * Purpose:
 * This module provides functions for handling SYS_CTRL interrupts
 * - Interrupt initialization
 * - Interrupt enabling
 * - Interrupt disabling
 * - Registering user callback function for interrupt handling
 * - De-registering user callback function for interrupt handling
 * - The interrupt handler itself, which provides the interrupt handling
 *   in hardware and calls the user callback function for functional 
 *   interrupt handling
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
 * 17/05/23 (F) poe 1001 first creation
 * -------------------------------------------------------------------
 * @endverbatim
 *
 * @creator      poe
 * @created      2017/05/23
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
#ifndef SYS_CTRL_INTERRUPTHANDLER_H_          
#define SYS_CTRL_INTERRUPTHANDLER_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "el_types.h"
#include "nvic_Interface.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/***************************************************************************//**
 * SYS_CTRL IRQ vector numbers
 ******************************************************************************/
typedef enum {
  system_ctrl_IRQ_POR_WAKE_UP             = 0u,
  system_ctrl_IRQ_DSI3_WAKE_UP            = 1u,
  system_ctrl_IRQ_IRQ_ABORT_WAKE_UP       = 2u,
  system_ctrl_IRQ_DEBUG_WAKE_UP           = 3u,
  system_ctrl_IRQ_BIST_ON                 = 4u,
  system_ctrl_IRQ_ENVP_PARITY_ERR_EVT     = 5u,
  system_ctrl_IRQ_AATG1_PARITY_ERR_EVT    = 6u,
  system_ctrl_IRQ_AATG2_PARITY_ERR_EVT    = 7u,
  system_ctrl_IRQ_CAP_MEAS_READY          = 8u,
    
  system_ctrl_INTERRUPT_VECTOR_CNT        = 9u  /**< Number of available interrupt vectors */
         
} system_ctrl_eInterruptVectorNum_t;

/***************************************************************************//**
 * Pointer to context data
 ******************************************************************************/
typedef void * system_ctrl_pInterruptContextData_t;

/***************************************************************************//**
 * Callback function pointer type
 ******************************************************************************/
typedef void (*system_ctrl_InterruptCallback_t) (system_ctrl_eInterruptVectorNum_t irqsrc, system_ctrl_pInterruptContextData_t contextdata);

/***************************************************************************//**
 * Environment data
 ******************************************************************************/
typedef struct system_ctrl_sInterruptEnvironmentData
{
    /** Interrupt vector table of this module             */
    system_ctrl_InterruptCallback_t InterrupVectorTable[system_ctrl_INTERRUPT_VECTOR_CNT];
    
    /** SYS_CTRL module context data */
    system_ctrl_pInterruptContextData_t ContextData;
    
} system_ctrl_sInterruptEnvironmentData_t;

/***************************************************************************//**
 * Pointer to SYSTEM_CTRL environment data
 ******************************************************************************/
typedef system_ctrl_sInterruptEnvironmentData_t * system_ctrl_pInterruptEnvironmentData_t;

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ********************* EXTERNAL FUNCTIONS / INTERFACE ***********************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ******************************* INTERRUPTS *********************************/
/* ****************************************************************************/

/***************************************************************************//**
 * @brief     Enables an IRQ.
 *
 * @param[in] modulBaseAddress  Pointer to SYS_CTRL module base address
 * @param[in] irqsrc            IRQ to be enabled
 *
 * @pre       A call back function to the related interrupt should have been
 *            registered with sys_ctrl_RegisterInterruptCallback().
 *
 * @post      The related call back function will be called if the desired
 *            interrupt occurs.
 *
 * @detaildesc
 * The SYS_CTRL IRQ_VENABLE register will be set the related IRQ number and therefore
 * the interrupt will be activated.
 *
 ******************************************************************************/
void system_ctrl_InterruptEnable(system_ctrl_eInterruptVectorNum_t irqsrc);

/***************************************************************************//**
 * @brief Disables an IRQ.
 *
 * @param[in] modulBaseAddress  Pointer to SYS_CTRL module base address
 * @param[in] irqsrc            IRQ to be disable
 *
 * @post      The interrupt will be disabled and the related callback function
 *            will no longer be called from the interrupt handler.
 *
 * @detaildesc
 * The SYS_CTRL IRQ_VDISABLE register will be set the related IRQ number and therefore
 * the interrupt will be deactivated.
 *
 ******************************************************************************/
void system_ctrl_InterruptDisable(system_ctrl_eInterruptVectorNum_t irqsrc);

/***************************************************************************//**
 * @brief Registers/Adds callback function to the module interrupt vector table.
 *
 * @param modulBaseAddress  Pointer to SYS_CTRL module base address
 * @param irqsrc            IRQ number
 * @param cbfnc             Pointer to desired callback function
 *
 * @pre     (optional) Which are the conditions to call this function? i.e. none
 *
 * @post    If the interrupt will be activated the registered callback function
 *          will be called if the IRQ occurs.
 *
 * @detaildesc
 * Registers the callback function at interrupt vector handling. It sets the
 * entry in the interrupt vector table to passed function pointer.
 *
 ******************************************************************************/
void system_ctrl_InterruptRegisterCallback(system_ctrl_eInterruptVectorNum_t irqsrc, system_ctrl_InterruptCallback_t cbfnc);

/***************************************************************************//**
 * @brief Deregisters/deletes callback function from module interrupt vector table.
 *
 * @param modulBaseAddress  Pointer to SYS_CTRL module base address
 * @param irqvecnum         IRQ number
 * @param cbfnc             Pointer to desired callback function
 *
 * @pre   The related IRQ should be disabled.
 *
 * @post  The entry in the module interrupt vector table will point to NULL and
 *        the related IRQ will be disabled.
 *
 * @detaildesc
 * Deregisters the callback function from interrupt vector handling. It sets the
 * entry in the interrupt vector table to NULL and disables the related interrupt.
 *
 ******************************************************************************/
void system_ctrl_InterruptDeregisterCallback(system_ctrl_eInterruptVectorNum_t irqvecnum);

/***************************************************************************//**
 * @brief Initialize SYS_CTRL module
 *
 * @param environmentdata  Pointer to Environment data for SYS_CTRL module in
 *                         user RAM
 *
 * @pre        VIC (vic_VectorInterruptControl) and SYS_CTRL (sys_ctrl_SystemStateModule)
 *             have to presented and initialized.
 *
 * @post       SYS_CTRL irqs can be used.
 *
 * @detaildesc
 * Initialize SYS_CTRL IRQ handling.
 *
 ******************************************************************************/
void system_ctrl_InterruptInitialisation(nvic_cpInterfaceFunctions_t vicIf, system_ctrl_pInterruptEnvironmentData_t environmentdata, system_ctrl_pInterruptContextData_t contextdata);


#endif /* SYS_CTRL_INTERRUPTHANDLER_H_ */

