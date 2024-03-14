 /* ------------------------------------------------------------------- */
/** @file nvic_Interface.h
 *
 * @brief Interface definitions for NVIC Interrupt control implementation.
 *
 * Purpose:
 * Provided interface functions for NVIC Interrupt control implementation.
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
 * @version      $Revision: 383 $
 *
 *
 * $State: Exp $
 * $Author: siko $
 *
 * Additional markers:
 *
 */
#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

#include "el_types.h"

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* *********************** CORE LEVEL IRQ MANAGEMEN ***************************/
/* ****************************************************************************/
#if defined ( __ICCARM__ )

#elif defined ( __CC_ARM )
  typedef uint32_t istate_t;
  typedef istate_t irqstate_t;
          
  #define __set_interrupt_state(istate) __set_PRIMASK(istate)

  #define __get_interrupt_state() __get_PRIMASK()

  #define __disable_interrupt() __disable_irq()

  #define __enable_interrupt() __enable_irq()

#endif


/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define NVIC_INTERFACE_VERSION           0x0102

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

typedef uint16_t nvic_InterfaceVersion_t;         /**< Data type for interface version representation **/

typedef void * nvic_pInterruptModuleEnvironmentData_t;  /**< Generic pointer type to module specific environment data **/


/***************************************************************************//**
 * @brief NVIC IRQ vector numbers 
 ******************************************************************************/
typedef enum nvic_eExceptionVectorNum
{
  nvic_CEVT_INIT_SP                     = 0u,
  nvic_CEVT_RESET                       = 1u,
  nvic_CEVT_NMI                         = 2u,
  nvic_CEVT_HARD_FAULT                  = 3u,
  /* 4u ... 10u reserved */ 
  nvic_CEVT_SVC                         = 11u,
  /* 12u ... 13u reserved */ 
  nvic_CEVT_PEND_SV                     = 14u,
  nvic_CEVT_SYSTICK                     = 15u,
  
  nvic_CEVT_EXT_IRQ_0                   = 16u,
  nvic_CEVT_EXT_IRQ_1                   = 17u,
  nvic_CEVT_EXT_IRQ_2                   = 18u,
  nvic_CEVT_EXT_IRQ_3                   = 19u,
  nvic_CEVT_EXT_IRQ_4                   = 20u,
  nvic_CEVT_EXT_IRQ_5                   = 21u,
  nvic_CEVT_EXT_IRQ_6                   = 22u,
  nvic_CEVT_EXT_IRQ_7                   = 23u,
  nvic_CEVT_EXT_IRQ_8                   = 24u,
  nvic_CEVT_EXT_IRQ_9                   = 25u,
  nvic_CEVT_EXT_IRQ_10                  = 26u,
  nvic_CEVT_EXT_IRQ_11                  = 27u,
  nvic_CEVT_EXT_IRQ_12                  = 28u,
  nvic_CEVT_EXT_IRQ_13                  = 29u,
  nvic_CEVT_EXT_IRQ_14                  = 30u,
  nvic_CEVT_EXT_IRQ_15                  = 31u,
  
  nvic_CEVT_VECTOR_CNT                  = 32u  /**< Number of available interrupt vectors */
   
} nvic_eExceptionVectorNum_t;


/***************************************************************************//**
 * @brief priority level mapping for ARM architecture
 ******************************************************************************/

typedef enum
{
  nvic_Priority_Level_0                 = 0u,
  nvic_Priority_Level_1                 = 1u,
  nvic_Priority_Level_2                 = 2u,
  nvic_Priority_Level_3                 = 3u
} nvic_ePriorityLevels_t;


/***************************************************************************//**
 * @brief mapping defines for the actual module IRQ assignment
 ******************************************************************************/

#define nvic_IRQ_SYS_STATE             nvic_CEVT_EXT_IRQ_0      
#define nvic_IRQ_EEPROM_CTRL           nvic_CEVT_EXT_IRQ_1

#define nvic_IRQ_DSI3                  nvic_CEVT_EXT_IRQ_2      
#define nvic_IRQ_SWTIMER               nvic_CEVT_EXT_IRQ_3    
#define nvic_IRQ_DSP                   nvic_CEVT_EXT_IRQ_4
#define nvic_IRQ_GPIO                  nvic_CEVT_EXT_IRQ_5
#define nvic_IRQ_UART                  nvic_CEVT_EXT_IRQ_6
#define nvic_IRQ_SYSTEM_CTRL           nvic_CEVT_EXT_IRQ_7	
/***************************************************************************//**
 * @brief Interrupt handler function typedef
 *
 * This function type represents the actual interrupt handler function as 
 * implemented in each module. 
 *
 ******************************************************************************/
#if defined ( EL_COMPILER_IAR )
typedef __irq void (*nvic_InterruptCallback_t) (void); 

#elif defined ( EL_COMPILER_KEIL )
typedef void (*nvic_InterruptCallback_t) (void) __irq; 

#else
#error "Unknown compiler type"
#endif

/***************************************************************************//**
 * @brief VIC environment data type
 ******************************************************************************/
typedef struct nvic_sInterruptEnvironmentData
{
    /** Interrupt vector table to module interrupt handler */
    nvic_InterruptCallback_t InterrupVectorTable[nvic_CEVT_VECTOR_CNT];
    
    /** Pointer to module vector table */
    nvic_pInterruptModuleEnvironmentData_t ModuleEnvironmentData[nvic_CEVT_VECTOR_CNT];
    
} nvic_sInterruptEnvironmentData_t;

/***************************************************************************//**
 * @brief Pointer to VIC environment data.
 ******************************************************************************/
typedef nvic_sInterruptEnvironmentData_t * nvic_pInterruptEnvironmentData_t;

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ********************* EXTERNAL FUNCTIONS / INTERFACE ***********************/
/* ****************************************************************************/

/***************************************************************************//**
 * @brief Returns current module specific environment data
 *
 * @param module  Module number 
 *
 * @return        Pointer to module data (may be NULL)
 *
 ******************************************************************************/
typedef nvic_pInterruptModuleEnvironmentData_t (*nvic_GetPointerToEnvironmentData_t)(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * @brief Introduces a module into the global VIC based IRQ handling
 *
 * @param module                  Module number
 *
 * @param interrupthandler        Pointer to module specific interrupt handler
 *
 * @param moduleenvironmentdata   Pointer to module specific interrupt handler runtime data
 *
 *
 ******************************************************************************/
typedef void (*nvic_RegisterModule_t)(nvic_eExceptionVectorNum_t vno, nvic_InterruptCallback_t interrupthandler,
                                     nvic_pInterruptModuleEnvironmentData_t moduleenvironmentdata);

/***************************************************************************//**
 * @brief Removes module handler for a particular module. 
 *
 * @param module                  Module number
 *
 * A default IRQ handler is installed for the selected module.
 *
 ******************************************************************************/
typedef void (*nvic_DeregisterModule_t)(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * @brief Enables interrupt processing for specified module
 *
 * @param module                  Module number
 *
 ******************************************************************************/
typedef void (*nvic_EnableModule_t)(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * @brief Disables interrupt processing for specified module
 *
 * @param module                  Module number
 *
 ******************************************************************************/
typedef void (*nvic_DisableModule_t)(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * @brief Enables interrupt processing for specified module
 *
 * @param module                  Module number
 *
 ******************************************************************************/
typedef void (*nvic_ClearPending_t)(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * @brief Enables interrupt processing for specified module
 *
 * @param module                  Module number
 *
 ******************************************************************************/
typedef void (*nvic_SetPending_t)(nvic_eExceptionVectorNum_t vno);


/***************************************************************************//**
 * @brief Assign interrupt priority level for specified module
 *
 * @param module                  Module number
 *
 ******************************************************************************/
typedef void (*nvic_SetModulePriority_t)(nvic_eExceptionVectorNum_t vno, nvic_ePriorityLevels_t prio);

/***************************************************************************//**
 * @brief Enables general interrupt processing
 *
 ******************************************************************************/
typedef void (*nvic_EnableMain_t)(void);

/***************************************************************************//**
 * @brief Disables general interrupt processing
 *
 ******************************************************************************/
typedef void (*nvic_DisableMain_t)(void);

/***************************************************************************//**
 * @brief Initializes global interrupt handling
 *
 * @param environmentdata  Pointer to Environment data for VIC module in
 *                         user RAM
 *
 ******************************************************************************/
typedef bool_t (*nvic_IRQInitialisation_t)(nvic_pInterruptEnvironmentData_t penvironmentdata);

/***************************************************************************//**
 * @brief LIN driver interface function pointer
 ******************************************************************************/
struct nvic_sInterfaceFunctions
{
  nvic_InterfaceVersion_t            InterfaceVersion;

  nvic_IRQInitialisation_t           IRQInitialisation;

  nvic_GetPointerToEnvironmentData_t GetPointerToEnvironmentData;

  nvic_RegisterModule_t              RegisterModule;
  nvic_DeregisterModule_t            DeregisterModule;
  nvic_EnableModule_t                EnableModule;
  nvic_DisableModule_t               DisableModule;  
  nvic_ClearPending_t                ClearPending;
  nvic_SetPending_t                  SetPending;
  nvic_SetModulePriority_t           SetModulePriority;
  
  nvic_EnableMain_t                  EnableMain;
  nvic_DisableMain_t                 DisableMain;
};

typedef struct nvic_sInterfaceFunctions    nvic_sInterfaceFunctions_t;
typedef        nvic_sInterfaceFunctions_t* nvic_pInterfaceFunctions_t;
typedef const  nvic_sInterfaceFunctions_t* nvic_cpInterfaceFunctions_t;

#endif /* VIC_INTERFACE_H_ */




