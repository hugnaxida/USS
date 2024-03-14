/* ------------------------------------------------------------------- */
/** @file dsi3_InterruptHandler.h
 *
 * @brief Module interrupt handler for DSI3 hardware module.
 *
 * Purpose:
 * This module provides functions for handling DSI3 interrupts
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
#ifndef DSI3_INTERRUPTHANDLER_H_
#define DSI3_INTERRUPTHANDLER_H_

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

/* *****************************************************************************
 * DSI3_IRQ vector numbers
 * *****************************************************************************/
    
typedef enum {
    dsi3_IRQ_SYNC_EVT                   =  0u,
    dsi3_IRQ_CMD_EVT                    =  1u,
    dsi3_IRQ_PDCM_EVT                   =  2u,
    dsi3_IRQ_DISC_EVT			=  3u,
    dsi3_IRQ_CRC_ERR_EVT                =  4u,
    dsi3_IRQ_PDCM_ERR_EVT               =  5u,
    dsi3_IRQ_DISC_ERR_EVT		=  6u,				
    dsi3_IRQ_FCC_ERROR                  =  7u,
    dsi3_IRQ_START_ERR_EVT              =  8u,
    dsi3_IRQ_TIMER_A_EVT                =  9u,
    dsi3_IRQ_TIMER_B_EVT                = 10u,
    dsi3_IRQ_TIMER_C_EVT		= 11u,
    dsi3_IRQ_RCC_FINISH                 = 12u,
    dsi3_IRQ_RCC_READY                  = 13u,
    dsi3_IRQ_SYNC_CNT_EVT               = 14u,
    dsi3_IRQ_DISC_CURR_EVT		= 15u,
    
    dsi3_INTERRUPT_VECTOR_CNT           = 16u  /**< Number of available interrupt vectors */    
} dsi3_eInterruptVectorNum_t;


/***************************************************************************//**
 * Pointer to context data
 ******************************************************************************/
typedef void * dsi3_pInterruptContextData_t;

/***************************************************************************//**
 * Callback function pointer type
 ******************************************************************************/

typedef void (*dsi3_InterruptCallback_t) (dsi3_eInterruptVectorNum_t sno, dsi3_pInterruptContextData_t genericCbCtxData);

/***************************************************************************//**
 * DSI3 environment data
 ******************************************************************************/
typedef struct dsi3_sInterruptEnvironmentData
{
    /** Interrupt vector table of this module             */
    dsi3_InterruptCallback_t InterrupVectorTable[dsi3_INTERRUPT_VECTOR_CNT];
    
    /** DSI3 module context data */
    dsi3_pInterruptContextData_t ContextData;
    
} dsi3_sInterruptEnvironmentData_t;

/***************************************************************************//**
 * Pointer to DSI3 environment data
 ******************************************************************************/
typedef dsi3_sInterruptEnvironmentData_t * dsi3_pInterruptEnvironmentData_t;

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
 * @param[in] modulBaseAddress  Pointer to DSI3 module base address
 * @param[in] irqsrc            IRQ to be enabled
 *
 * @pre       A call back function to the related interrupt should have been
 *            registered with dsi3_RegisterInterruptCallback().
 *
 * @post      The related call back function will be called if the desired
 *            interrupt occurs.
 *
 * @detaildesc
 * The DSI3_IRQ_VENABLE register will be set the related IRQ number and therefore
 * the interrupt will be activated.
 *
 ******************************************************************************/
void dsi3_InterruptEnable(dsi3_eInterruptVectorNum_t irqsrc);

/***************************************************************************//**
 * @brief Disables an IRQ.
 *
 * @param[in] modulBaseAddress  Pointer to DSI3 module base address
 * @param[in] irqsrc            IRQ to be disable
 *
 * @post      The interrupt will be disabled and the related callback function
 *            will no longer be called from the interrupt handler.
 *
 * @detaildesc
 * The DSI3_IRQ_VDISABLE register will be set the related IRQ number and therefore
 * the interrupt will be deactivated.
 *
 ******************************************************************************/
void dsi3_InterruptDisable(dsi3_eInterruptVectorNum_t irqsrc);

/***************************************************************************//**
 * @brief Registers/Adds callback function to the module interrupt vector table.
 *
 * @param modulBaseAddress  Pointer to DSI3 module base address
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
void dsi3_InterruptRegisterCallback(dsi3_eInterruptVectorNum_t irqsrc, dsi3_InterruptCallback_t cbfnc);

/***************************************************************************//**
 * @brief Deregisters/deletes callback function from module interrupt vector table.
 *
 * @param modulBaseAddress  Pointer to DSI3 module base address
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
void dsi3_InterruptDeregisterCallback(dsi3_eInterruptVectorNum_t irqvecnum);

/***************************************************************************//**
 * @brief Initialize DSI3 module
 *
 * @param environmentdata  Pointer to Environment data for DSI3 module in
 *                         user RAM
 *
 * @pre        VIC (vic_VectorInterruptControl) and DSI3 (dsi3_SystemStateModule)
 *             have to presented and initialized.
 *
 * @post       DSI3 module is configured for use.
 *
 * @detaildesc
 * Initializes the DSI3 software and hardware module, including the module
 * interrupt vector table. Configures if IRQ nesting is active and if IO2 and
 * IO3 are used as DSI3s or not.
 *
 ******************************************************************************/
void dsi3_InterruptInitialisation(nvic_cpInterfaceFunctions_t vicIf, dsi3_pInterruptEnvironmentData_t environmentdata, dsi3_pInterruptContextData_t contextdata);


#endif /* DSI3_INTERRUPTHANDLER_H_ */

