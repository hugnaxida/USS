/* ------------------------------------------------------------------- */
/** @file dsp_InterruptHandler.h
 *
 * @brief Module interrupt handler for DSP hardware module.
 *
 * Purpose:
 * This module provides functions for handling DSP interrupts
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
 * @version      $Revision: 392 $
 *
 *
 * $State: Exp $
 * $Author: siko $
 *
* Additional markers:
 *
 */

#ifndef DSP_INTERRUPTHANDLER_H_          
#define DSP_INTERRUPTHANDLER_H_


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
 * DSP IRQ vector numbers
 ******************************************************************************/
typedef enum {
  dsp_IRQ_EEVAL_TLH_EVT                 = 0u,
  dsp_IRQ_EEVAL_THL_EVT                 = 1u,
  dsp_IRQ_EEVAL_MAX_EVT                 = 2u,
  dsp_IRQ_EEVAL_MIN_EVT                 = 3u,
  dsp_IRQ_EEVAL1_MAX_EVT                = 4u,
  dsp_IRQ_EEVAL2_MAX_EVT                = 5u,
  dsp_IRQ_RFM_EVT                       = 6u,
  dsp_IRQ_RTM_EVT                       = 7u,
  dsp_IRQ_NFD_EVT                       = 8u,
  dsp_IRQ_EEVAL_DMA_WRAP                = 9u,
  dsp_IRQ_EEVAL1_DMA_WRAP               = 10u,
  dsp_IRQ_EEVAL2_DMA_WRAP               = 11u,
  dsp_IRQ_EDI0_DMA_WRAP                 = 12u,
  dsp_IRQ_EDI1_DMA_WRAP                 = 13u,
  dsp_IRQ_EDI2_DMA_WRAP                 = 14u,
  dsp_IRQ_EDI3_DMA_WRAP                 = 15u,
  
  dsp_INTERRUPT_VECTOR_CNT              = 16u  /**< Number of available interrupt vectors */
         
} dsp_eInterruptVectorNum_t;

/***************************************************************************//**
 * Pointer to DSP context data
 ******************************************************************************/
typedef void * dsp_pInterruptContextData_t;

/***************************************************************************//**
 * Callback function pointer type
 ******************************************************************************/
typedef void (*dsp_InterruptCallback_t) (dsp_eInterruptVectorNum_t irqsrc, dsp_pInterruptContextData_t contextdata);

/***************************************************************************//**
 * DSP environment data
 ******************************************************************************/
typedef struct dsp_sInterruptEnvironmentData
{
    /** Interrupt vector table of this module             */
    dsp_InterruptCallback_t InterrupVectorTable[dsp_INTERRUPT_VECTOR_CNT];
    
    /** DSP module context data */
    dsp_pInterruptContextData_t ContextData;
    
} dsp_sInterruptEnvironmentData_t;

/***************************************************************************//**
 * Pointer to DSP environment data
 ******************************************************************************/
typedef dsp_sInterruptEnvironmentData_t * dsp_pInterruptEnvironmentData_t;

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
 * @param[in] modulBaseAddress  Pointer to DSP module base address
 * @param[in] irqsrc            IRQ to be enabled
 *
 * @pre       A call back function to the related interrupt should have been
 *            registered with dsp_RegisterInterruptCallback().
 *
 * @post      The related call back function will be called if the desired
 *            interrupt occurs.
 *
 * @detaildesc
 * The DSP IRQ_VENABLE register will be set the related IRQ number and therefore
 * the interrupt will be activated.
 *
 ******************************************************************************/
void dsp_InterruptEnable(dsp_eInterruptVectorNum_t irqsrc);

/***************************************************************************//**
 * @brief Disables an IRQ.
 *
 * @param[in] modulBaseAddress  Pointer to DSP module base address
 * @param[in] irqsrc            IRQ to be disable
 *
 * @post      The interrupt will be disabled and the related callback function
 *            will no longer be called from the interrupt handler.
 *
 * @detaildesc
 * The DSP IRQ_VDISABLE register will be set the related IRQ number and therefore
 * the interrupt will be deactivated.
 *
 ******************************************************************************/
void dsp_InterruptDisable(dsp_eInterruptVectorNum_t irqsrc);

/***************************************************************************//**
 * @brief Registers/Adds callback function to the module interrupt vector table.
 *
 * @param modulBaseAddress  Pointer to DSP module base address
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
void dsp_InterruptRegisterCallback(dsp_eInterruptVectorNum_t irqsrc, dsp_InterruptCallback_t cbfnc);

/***************************************************************************//**
 * @brief Deregisters/deletes callback function from module interrupt vector table.
 *
 * @param modulBaseAddress  Pointer to DSP module base address
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
void dsp_InterruptDeregisterCallback(dsp_eInterruptVectorNum_t irqvecnum);

/***************************************************************************//**
 * @brief Initialize DSP module
 *
 * @param environmentdata  Pointer to Environment data for DSP module in
 *                         user RAM
 *
 * @pre        VIC (vic_VectorInterruptControl) and DSP (dsp_SystemStateModule)
 *             have to presented and initialized.
 *
 * @post       DSP module is configured for use.
 *
 * @detaildesc
 * Initializes the DSP software and hardware module, including the module
 * interrupt vector table. Configures if IRQ nesting is active and if IO2 and
 * IO3 are used as DSPs or not.
 *
 ******************************************************************************/
void dsp_InterruptInitialisation(nvic_cpInterfaceFunctions_t vicIf, dsp_pInterruptEnvironmentData_t environmentdata, dsp_pInterruptContextData_t contextdata);


#endif /* DSP_INTERRUPTHANDLER_H_ */

