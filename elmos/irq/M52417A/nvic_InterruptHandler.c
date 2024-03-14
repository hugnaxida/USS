 /* ------------------------------------------------------------------- */
/** @file nvic_InterruptHandler.c
 *
 * @brief NVIC Interrupt handler for interrupt controller implementation.
 *
 * Purpose:
 * NVIC Interrupt handler for interrupt controller implementation
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
#include <io_m52417a.h>
#include "el_helper.h"

#include "nvic_InterruptHandler.h"


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

/* ****************************************************************************/
/* ******************** FORWARD DECLARATIONS / PROTOTYPES *********************/
/* ****************************************************************************/

static __irq void loc_DefaultExceptionHandler(void);
static void loc_CommonDefaultInterruptHandler(IRQn_Type irqno);
static __irq void loc_DefaultInterruptHandler_IRQ_0(void);
static __irq void loc_DefaultInterruptHandler_IRQ_1(void);
static __irq void loc_DefaultInterruptHandler_IRQ_2(void);
static __irq void loc_DefaultInterruptHandler_IRQ_3(void);
static __irq void loc_DefaultInterruptHandler_IRQ_4(void);
static __irq void loc_DefaultInterruptHandler_IRQ_5(void);
static __irq void loc_DefaultInterruptHandler_IRQ_6(void);
static __irq void loc_DefaultInterruptHandler_IRQ_7(void);
static __irq void loc_DefaultInterruptHandler_IRQ_8(void);
static __irq void loc_DefaultInterruptHandler_IRQ_9(void);
static __irq void loc_DefaultInterruptHandler_IRQ_10(void);
static __irq void loc_DefaultInterruptHandler_IRQ_11(void);
static __irq void loc_DefaultInterruptHandler_IRQ_12(void);
static __irq void loc_DefaultInterruptHandler_IRQ_13(void);
static __irq void loc_DefaultInterruptHandler_IRQ_14(void);
static __irq void loc_DefaultInterruptHandler_IRQ_15(void);


const nvic_sInterfaceFunctions_t nvic_InterfaceFunctions =
{
  .InterfaceVersion            = NVIC_INTERFACE_VERSION,

  .IRQInitialisation           = &nvic_IRQInitialisation,

  .GetPointerToEnvironmentData = &nvic_GetPointerToEnvironmentData,

  .RegisterModule              = &nvic_RegisterModule,
  .DeregisterModule            = &nvic_DeregisterModule,
  .EnableModule                = &nvic_EnableModule,
  .DisableModule               = &nvic_DisableModule,
  .ClearPending                = &nvic_ClearPending,
  .SetPending                  = &nvic_SetPending,
  .SetModulePriority           = &nvic_SetModulePriority,

  .EnableMain                  = &nvic_EnableMain,
  .DisableMain                 = &nvic_DisableMain
};

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/***************************************************************************//**
 * @implementation
 * TODO: Concrete implementation description.
 *
 ******************************************************************************/
static __irq void loc_DefaultExceptionHandler(void)  
{ 
  __disable_interrupt();
  
  while(TRUE)
  { 
  }
  ; /* can't help ... */
}

/***************************************************************************//**
 * @implementation
 * The common default interrupt handler clears and disabled the pending 
 * interrupt, synchronizes all data and returns.
 *
 ******************************************************************************/
_Pragma("inline = forced") static void loc_CommonDefaultInterruptHandler(IRQn_Type irqno)
{
  NVIC_ClearPendingIRQ(irqno);
  NVIC_DisableIRQ(irqno);
  __DSB();  
}

/***************************************************************************//**
 * @implementation
 * Initialize the default interrupt handlers for an interrupt with the
 * common default interrupt handler
 *
 ******************************************************************************/
static __irq void loc_DefaultInterruptHandler_IRQ_0(void)  { loc_CommonDefaultInterruptHandler((IRQn_Type)0); }
static __irq void loc_DefaultInterruptHandler_IRQ_1(void)  { loc_CommonDefaultInterruptHandler((IRQn_Type)1); }
static __irq void loc_DefaultInterruptHandler_IRQ_2(void)  { loc_CommonDefaultInterruptHandler((IRQn_Type)2); }
static __irq void loc_DefaultInterruptHandler_IRQ_3(void)  { loc_CommonDefaultInterruptHandler((IRQn_Type)3); }
static __irq void loc_DefaultInterruptHandler_IRQ_4(void)  { loc_CommonDefaultInterruptHandler((IRQn_Type)4); }
static __irq void loc_DefaultInterruptHandler_IRQ_5(void)  { loc_CommonDefaultInterruptHandler((IRQn_Type)5); }
static __irq void loc_DefaultInterruptHandler_IRQ_6(void)  { loc_CommonDefaultInterruptHandler((IRQn_Type)6); }
static __irq void loc_DefaultInterruptHandler_IRQ_7(void)  { loc_CommonDefaultInterruptHandler((IRQn_Type)7); }
static __irq void loc_DefaultInterruptHandler_IRQ_8(void)  { loc_CommonDefaultInterruptHandler((IRQn_Type)8); }
static __irq void loc_DefaultInterruptHandler_IRQ_9(void)  { loc_CommonDefaultInterruptHandler((IRQn_Type)9); }
static __irq void loc_DefaultInterruptHandler_IRQ_10(void) { loc_CommonDefaultInterruptHandler((IRQn_Type)10); }
static __irq void loc_DefaultInterruptHandler_IRQ_11(void) { loc_CommonDefaultInterruptHandler((IRQn_Type)11); }
static __irq void loc_DefaultInterruptHandler_IRQ_12(void) { loc_CommonDefaultInterruptHandler((IRQn_Type)12); }
static __irq void loc_DefaultInterruptHandler_IRQ_13(void) { loc_CommonDefaultInterruptHandler((IRQn_Type)13); }
static __irq void loc_DefaultInterruptHandler_IRQ_14(void) { loc_CommonDefaultInterruptHandler((IRQn_Type)14); }
static __irq void loc_DefaultInterruptHandler_IRQ_15(void) { loc_CommonDefaultInterruptHandler((IRQn_Type)15); }

/***************************************************************************//**
 * @implementation
 * Structure of default interrupt handler functions
 *
 ******************************************************************************/
static const nvic_InterruptCallback_t loc_DefaultInterruptHandler[16] = {
  & loc_DefaultInterruptHandler_IRQ_0,
  & loc_DefaultInterruptHandler_IRQ_1,
  & loc_DefaultInterruptHandler_IRQ_2,
  & loc_DefaultInterruptHandler_IRQ_3,
  & loc_DefaultInterruptHandler_IRQ_4,
  & loc_DefaultInterruptHandler_IRQ_5,
  & loc_DefaultInterruptHandler_IRQ_6,
  & loc_DefaultInterruptHandler_IRQ_7,
  & loc_DefaultInterruptHandler_IRQ_8,
  & loc_DefaultInterruptHandler_IRQ_9,
  & loc_DefaultInterruptHandler_IRQ_10,
  & loc_DefaultInterruptHandler_IRQ_11,
  & loc_DefaultInterruptHandler_IRQ_12,
  & loc_DefaultInterruptHandler_IRQ_13,
  & loc_DefaultInterruptHandler_IRQ_14,
  & loc_DefaultInterruptHandler_IRQ_15
};

/***************************************************************************//**
 * @implementation
 * Check exception vector number for valid range. Return pointer to 
 * interrupt environment for given exception vector number.
 *
 ******************************************************************************/
nvic_pInterruptModuleEnvironmentData_t nvic_GetPointerToEnvironmentData(nvic_eExceptionVectorNum_t vno)
{
  // PRQA S 0310 1
  volatile nvic_pInterruptEnvironmentData_t penvironmentdata = *((volatile nvic_pInterruptEnvironmentData_t *) &SYS_STATE_VECTOR_TABLE_BASE0); // + SYS_STATE_VECTOR_TABLE_BASE1  // PRQA S 0306 1
  nvic_pInterruptModuleEnvironmentData_t rv = NULL;

  if ((vno >= nvic_CEVT_NMI) && (vno < nvic_CEVT_VECTOR_CNT)) // reset vector and initial stack pointer will never have an environment set.
  { 
    rv = penvironmentdata->ModuleEnvironmentData[vno];
  }
  else {}
  
  return rv;
}

/***************************************************************************//**
 * @implementation
 * Check exception vector number for valid range. Register interrupt handler
 * and interrupt environment for module according to given exception vector 
 * number.
 *
 ******************************************************************************/
void nvic_RegisterModule(nvic_eExceptionVectorNum_t vno, nvic_InterruptCallback_t interrupthandler, nvic_pInterruptModuleEnvironmentData_t moduleenvironmentdata)
{
  // PRQA S 0310 1
  volatile nvic_pInterruptEnvironmentData_t penvironmentdata = *((volatile nvic_pInterruptEnvironmentData_t *) &SYS_STATE_VECTOR_TABLE_BASE0); // + SYS_STATE_VECTOR_TABLE_BASE1  // PRQA S 0306 
  
  if ((vno >= nvic_CEVT_NMI) && (vno < nvic_CEVT_VECTOR_CNT)) // reset vector and initial stack pointer may not be used
  {
    penvironmentdata->InterrupVectorTable[vno] = interrupthandler;  
    penvironmentdata->ModuleEnvironmentData[vno] = moduleenvironmentdata;
  }
  else {}
}

/***************************************************************************//**
 * @implementation
 * Check exception vector number for valid range. 
 * Disable given module in NVIC. Set interrupt handler function to default 
 * exception handler for system IRQs or default interrupt handler for module 
 * interrupts. Invalidate pointer to interrupt environment.
 *
 ******************************************************************************/
void nvic_DeregisterModule(nvic_eExceptionVectorNum_t vno)
{
  // PRQA S 0310 1
  volatile nvic_pInterruptEnvironmentData_t penvironmentdata = *((volatile nvic_pInterruptEnvironmentData_t *) &SYS_STATE_VECTOR_TABLE_BASE0); // + SYS_STATE_VECTOR_TABLE_BASE1  // PRQA S 0306 
  
  if ((vno >= nvic_CEVT_NMI) && (vno < nvic_CEVT_VECTOR_CNT)) // reset vector and initial stack pointer may not be used
  {
    nvic_DisableModule(vno);
    
    if (vno >= nvic_CEVT_EXT_IRQ_0)
    {
      penvironmentdata->InterrupVectorTable[vno] = loc_DefaultInterruptHandler[vno - nvic_CEVT_EXT_IRQ_0]; // TODO: eventually patch pointer to make it a THUMB ISA vector! (if not done by compiler)
    }
    else
    {
      penvironmentdata->InterrupVectorTable[vno] = & loc_DefaultExceptionHandler; // TODO: eventually patch pointer to make it a THUMB ISA vector! (if not done by compiler)
    }
    
    penvironmentdata->ModuleEnvironmentData[vno] = NULL;
  }
  else {}
}

/***************************************************************************//**
 * @implementation
 * Check exception vector number for valid range. 
 * Clear pending IRQs and enable IRQs for given module.
 *
 ******************************************************************************/
void nvic_EnableModule(nvic_eExceptionVectorNum_t vno)
{
  if ((vno >= nvic_CEVT_EXT_IRQ_0) && (vno < nvic_CEVT_VECTOR_CNT))
  {
    NVIC_ClearPendingIRQ((IRQn_Type)(vno - nvic_CEVT_EXT_IRQ_0));
    NVIC_EnableIRQ((IRQn_Type)(vno - nvic_CEVT_EXT_IRQ_0));
    __DSB();
  }
  else {}
}

/***************************************************************************//**
 * @implementation
 * Check exception vector number for valid range. 
 * Disable IRQs for given module.
 *
 ******************************************************************************/
void nvic_DisableModule(nvic_eExceptionVectorNum_t vno)
{
  if ((vno >= nvic_CEVT_EXT_IRQ_0) && (vno < nvic_CEVT_VECTOR_CNT))
  {
    NVIC_DisableIRQ((IRQn_Type)(vno - nvic_CEVT_EXT_IRQ_0));
    __DSB();
  }
  else {}
}

/***************************************************************************//**
 * @implementation
 * Check exception vector number for valid range. 
 * Clear pending IRQs for given module.
 *
 ******************************************************************************/
void nvic_ClearPending(nvic_eExceptionVectorNum_t vno)
{
  if ((vno >= nvic_CEVT_EXT_IRQ_0) && (vno < nvic_CEVT_VECTOR_CNT))
  {
    NVIC_ClearPendingIRQ((IRQn_Type)(vno - nvic_CEVT_EXT_IRQ_0));
    __DSB();
  }
  else {}
}

/***************************************************************************//**
 * @implementation
 * Check exception vector number for valid range. 
 * Set pending IRQs for given module.
 *
 ******************************************************************************/
void nvic_SetPending(nvic_eExceptionVectorNum_t vno)
{
  if ((vno >= nvic_CEVT_EXT_IRQ_0) && (vno < nvic_CEVT_VECTOR_CNT))
  {
    NVIC_SetPendingIRQ((IRQn_Type)(vno - nvic_CEVT_EXT_IRQ_0));
    __DSB();
  }
  else {}
}


/***************************************************************************//**
 * @implementation
 * Check exception vector number for valid range. 
 * Set IRQ priority for given module.
 *
 ******************************************************************************/
void nvic_SetModulePriority(nvic_eExceptionVectorNum_t vno, nvic_ePriorityLevels_t prio)
{
  if ((vno >= nvic_CEVT_EXT_IRQ_0) && (vno < nvic_CEVT_VECTOR_CNT))
  {
    NVIC_SetPriority((IRQn_Type)(vno-nvic_CEVT_EXT_IRQ_0), (int32_t) prio);
  }
  else {}
}


/***************************************************************************//**
 * @implementation
 * Nothing to be done by software
 *
 ******************************************************************************/
void nvic_EnableMain(void)
{
  
  // No global enable?
}

/***************************************************************************//**
 * @implementation
 * Nothing to be done by software
 *
 ******************************************************************************/
void nvic_DisableMain(void)
{
  // No global enable?
}

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
bool_t nvic_IRQInitialisation(nvic_pInterruptEnvironmentData_t penvironmentdata)
{
  bool_t rv = FALSE;
    
  if ((penvironmentdata != NULL) && (SYS_STATE_VECTOR_TABLE_REMAP_bit.lock == 0)) // check if remaping is possible at all.
  {
    uint8_t i;
    const uint32_t *preinit_exception_table = (const uint32_t *)(0x00000000u);
    
    irqstate_t saveIstate;

    saveIstate = __get_interrupt_state();
    __disable_interrupt();

    SYS_STATE_VECTOR_TABLE_REMAP = 0xA500u | E_SYS_STATE_VECTOR_TABLE_REMAP_SEL | 0x0u ; // force application mode settings to copy data from begining of appl. area
    __DSB();
    __ISB();

    /* Copy current exception vectors from 0x00000000 */
    for(i = 0u; i < (uint8_t) nvic_CEVT_EXT_IRQ_0; i++ )
    {
      /* 
       * Accessing exception table at 0x0 and maping data structure of 
       * interrupt vector table to it causes QA-C warnings, although
       * the code is working well.
       */
      // PRQA S 0305 2
      // PRQA S 0491 1
      penvironmentdata->InterrupVectorTable[i] = (nvic_InterruptCallback_t)preinit_exception_table[i];
      penvironmentdata->ModuleEnvironmentData[i] = NULL;
    }
  
    /* Initialize module IRQ table with dummy functions */
    for(i = nvic_CEVT_EXT_IRQ_0; i < (uint8_t) nvic_CEVT_VECTOR_CNT; i++ )
    {
      penvironmentdata->InterrupVectorTable[i] = loc_DefaultInterruptHandler[i-nvic_CEVT_EXT_IRQ_0]; // make sure 'loc_DefaultInterruptHandler[]' has sufficient entries if changing 'nvic_CEVT_VECTOR_CNT'!
      penvironmentdata->ModuleEnvironmentData[i] = NULL;
      
      nvic_DisableModule((nvic_eExceptionVectorNum_t)(i));
    }
    
    // PRQA S 0310 1
    *((volatile nvic_pInterruptEnvironmentData_t *) &SYS_STATE_VECTOR_TABLE_BASE0) = penvironmentdata;
  
    SYS_STATE_VECTOR_TABLE_REMAP = 0xA500u | E_SYS_STATE_VECTOR_TABLE_REMAP_SEL | 0x1u ; // select mode with reset vector pointing to appl code, while other exceptions being remapable vie TABLE_BASE    
    // TODO: eventually lock remaping settings here?
    
    __DSB();
    __ISB();

    __set_interrupt_state(saveIstate);
    
    rv = TRUE;

  }
  else {}
  
  return rv;

}

