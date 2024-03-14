/* ------------------------------------------------------------------- */
/** @file eeprom_ctrl_InterruptHandler.h
 *
 * @brief Module interrupt handler for EEPROM hardware module.
 *
 * Purpose:
 * This module provides functions for handling EEPROM interrupts
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

#ifndef EEPROM_CTRL_INTERRUPTHANDLER_H_          
#define EEPROM_CTRL_INTERRUPTHANDLER_H_

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
 * EEPROM_CTRL IRQ vector numbers
 ******************************************************************************/
typedef enum {
  eeprom_ctrl_IRQ_TIMEOUT                 = 0u,
  eeprom_ctrl_IRQ_INVALID_ADDR            = 1u,
  eeprom_ctrl_IRQ_IP_OFF_ACCESS           = 2u,
    
  eeprom_ctrl_INTERRUPT_VECTOR_CNT        = 3u  /**< Number of available interrupt vectors */
         
} eeprom_ctrl_eInterruptVectorNum_t;

/***************************************************************************//**
 * Pointer to context data
 ******************************************************************************/
typedef void * eeprom_ctrl_pInterruptContextData_t;

/***************************************************************************//**
 * Callback function pointer type
 ******************************************************************************/
typedef void (*eeprom_ctrl_InterruptCallback_t) (eeprom_ctrl_eInterruptVectorNum_t irqsrc, eeprom_ctrl_pInterruptContextData_t contextdata);

/***************************************************************************//**
 * Environment data
 ******************************************************************************/
typedef struct eeprom_ctrl_sInterruptEnvironmentData
{
    /** Interrupt vector table of this module             */
    eeprom_ctrl_InterruptCallback_t InterrupVectorTable[eeprom_ctrl_INTERRUPT_VECTOR_CNT];
    
    /** EEPROM_CTRL module context data */
    eeprom_ctrl_pInterruptContextData_t ContextData;
    
} eeprom_ctrl_sInterruptEnvironmentData_t;

/***************************************************************************//**
 * Pointer to EEPROM_CTRL environment data
 ******************************************************************************/
typedef eeprom_ctrl_sInterruptEnvironmentData_t * eeprom_ctrl_pInterruptEnvironmentData_t;

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
 * @param[in] irqsrc            IRQ to be enabled
 *
 * @pre       A call back function to the related interrupt should have been
 *            registered with eeprom_ctrl_RegisterInterruptCallback().
 *
 * @post      The related call back function will be called if the desired
 *            interrupt occurs.
 *
 * @detaildesc
 * The IRQ_VENABLE register will be set the related IRQ number and therefore
 * the interrupt will be activated.
 *
 ******************************************************************************/
void eeprom_ctrl_InterruptEnable(eeprom_ctrl_eInterruptVectorNum_t irqsrc);

/***************************************************************************//**
 * @brief Disables an IRQ.
 *
 * @param[in] irqsrc            IRQ to be disable
 *
 * @post      The interrupt will be disabled and the related callback function
 *            will no longer be called from the interrupt handler.
 *
 * @detaildesc
 * The IRQ_VDISABLE register will be set the related IRQ number and therefore
 * the interrupt will be deactivated.
 *
 ******************************************************************************/
void eeprom_ctrl_InterruptDisable(eeprom_ctrl_eInterruptVectorNum_t irqsrc);

/***************************************************************************//**
 * @brief Registers/Adds callback function to the module interrupt vector table.
 *
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
void eeprom_ctrl_InterruptRegisterCallback(eeprom_ctrl_eInterruptVectorNum_t irqsrc, eeprom_ctrl_InterruptCallback_t cbfnc);

/***************************************************************************//**
 * @brief Deregisters/deletes callback function from module interrupt vector table.
 *
 * @param modulBaseAddress  Pointer to EEPROM_CTRL module base address
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
void eeprom_ctrl_InterruptDeregisterCallback(eeprom_ctrl_eInterruptVectorNum_t irqvecnum);

/***************************************************************************//**
 * @brief Initialize EEPROM_CTRL module
 *
 * @param environmentdata  Pointer to Environment data for EEPROM_CTRL module in
 *                         user RAM
 *
 * @pre        VIC (vic_VectorInterruptControl) and EEPROM_CTRL (sci_SystemStateModule)
 *             have to presented and initialized.
 *
 * @post       Irqs can be used.
 *
 * @detaildesc
 * Initialize IRQ handling.
 *
 ******************************************************************************/
void eeprom_ctrl_InterruptInitialisation(nvic_cpInterfaceFunctions_t vicIf, eeprom_ctrl_pInterruptEnvironmentData_t environmentdata, eeprom_ctrl_pInterruptContextData_t contextdata);


#endif /* EEPROM_CTRL_INTERRUPTHANDLER_H_ */

