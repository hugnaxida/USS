/* ------------------------------------------------------------------- */
/** @file gpio_InterruptHandler.h
 *
 * @brief Module interrupt handler for GPIO hardware module.
 *
 * Purpose:
 * This module provides functions for handling GPIO interrupts
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

#ifndef GPIO_INTERRUPTHANDLER_H_          
#define GPIO_INTERRUPTHANDLER_H_

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
 * uart IRQ vector numbers
 ******************************************************************************/
typedef enum {
  uart_IRQ_TX               = 0u,
  uart_IRQ_RX               = 1u,
  uart_IRQ_TXOVR              = 2u,
  uart_IRQ_RXOVR               = 3u,
  
  uart_INTERRUPT_VECTOR_CNT             = 4u  /**< Number of available interrupt vectors */
         
} uart_eInterruptVectorNum_t;

/***************************************************************************//**
 * Pointer to context data
 ******************************************************************************/
 typedef void * uart_pInterruptContextData_t;
 

/***************************************************************************//**
 * Callback function pointer type
 ******************************************************************************/
typedef void (*uart_InterruptCallback_t) (uart_eInterruptVectorNum_t irqsrc, uart_pInterruptContextData_t contextdata);
 
  /***************************************************************************//**
 * Environment data
 ******************************************************************************/
typedef struct uart_sInterruptEnvironmentData
{
    /** Interrupt vector table of this module             */
    uart_InterruptCallback_t InterrupVectorTable[uart_INTERRUPT_VECTOR_CNT];
    
    /** SYS_CTRL module context data */
    uart_pInterruptContextData_t ContextData;
    
} uart_sInterruptEnvironmentData_t;
 
/***************************************************************************//**
 * Pointer to UART environment data
 ******************************************************************************/
typedef uart_sInterruptEnvironmentData_t * uart_pInterruptEnvironmentData_t;

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
 * @param[in] modulBaseAddress  Pointer to UART module base address
 * @param[in] irqsrc            IRQ to be enabled
 *
 * @pre       A call back function to the related interrupt should have been
 *            registered with sys_state_RegisterInterruptCallback().
 *
 * @post      The related call back function will be called if the desired
 *            interrupt occurs.
 *
 * @detaildesc
 * The UART IRQ_VENABLE register will be set the related IRQ number and therefore
 * the interrupt will be activated.
 *
 ******************************************************************************/
void uart_InterruptEnable(uart_eInterruptVectorNum_t irqsrc);

/***************************************************************************//**
 * @brief Disables an IRQ.
 *
 * @param[in] modulBaseAddress  Pointer to UART module base address
 * @param[in] irqsrc            IRQ to be disable
 *
 * @post      The interrupt will be disabled and the related callback function
 *            will no longer be called from the interrupt handler.
 *
 * @detaildesc
 * The UART IRQ_VDISABLE register will be set the related IRQ number and therefore
 * the interrupt will be deactivated.
 *
 ******************************************************************************/
void uart_InterruptDisable(uart_eInterruptVectorNum_t irqsrc);

/***************************************************************************//**
 * @brief Registers/Adds callback function to the module interrupt vector table.
 *
 * @param modulBaseAddress  Pointer to UART module base address
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
void uart_InterruptRegisterCallback(uart_eInterruptVectorNum_t irqsrc, uart_InterruptCallback_t cbfnc);

/***************************************************************************//**
 * @brief Deregisters/deletes callback function from module interrupt vector table.
 *
 * @param modulBaseAddress  Pointer to UART module base address
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
void uart_InterruptDeregisterCallback(uart_eInterruptVectorNum_t irqvecnum);

/***************************************************************************//**
 * @brief Initialize UART module
 *
 * @param environmentdata  Pointer to Environment data for UART module in
 *                         user RAM
 *
 * @pre        VIC (vic_VectorInterruptControl) and UART (sys_state_SystemStateModule)
 *             have to presented and initialized.
 *
 * @post       UART irqs can be used.
 *
 * @detaildesc
 * Initialize UART IRQ handling.
 *
 ******************************************************************************/
void uart_InterruptInitialisation(nvic_cpInterfaceFunctions_t vicIf, uart_pInterruptEnvironmentData_t environmentdata, uart_pInterruptContextData_t contextdata);
 

#endif /* UART_INTERRUPTHANDLER_H_ */

