/* ------------------------------------------------------------------- */
/** @file dsp_InterruptHandler.c
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
 * @version      $Revision: 383 $
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

#include <io_m52417b.h>

#include "nvic_InterruptHandler.h"
#include "dsp_InterruptHandler.h"


/* ****************************************************************************/
/* ***************************** QA-C EXCLUDES ********************************/
/* ****************************************************************************/

/*  
* Exception:
* Msg(2:1503) The function '...' is defined but is not used within this project.
*
* Circumstances and justification:
* The interrupt handling is provided as a hardware support API for all modules
* but may not be used for the actual project for a specific module. 
* 
* Potential consequences:
* None, just don't care about those functions
*
* Alternative safety assurance:
* None
*/
// PRQA S 1503 ++


/*  
* Exception:
* Msg(2:1505) The function '...' is only referenced in the translation unit
              where it is defined.
*
* Circumstances and justification:
* The interrupt handling is provided as a hardware support API for all modules
* but may not be used for the actual project for a specific module. The actual
* function is used within this module, but may or may not be used outside
* this module depending on the current application.
* 
* Potential consequences:
* None
*
* Alternative safety assurance:
* None
*/
// PRQA S 1505 ++

/*  
* Exception:
* Msg(2:0316) [I] Cast from a pointer to void to a pointer to object type.
*
* Circumstances and justification:
* nvic_GetPointerToEnvironmentData() returns a generic pointer to void for
* every module, which is locally casted to the actual module implementation.
* 
* Potential consequences:
* Data structure may not be as expected
*
* Alternative safety assurance:
* Message is only deactivated when accessing IRQ environment data. Correct
* usage has been checked when developing this module.
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
/* ******************** FORWARD DECLARATIONS / PROTOTYPES *********************/
/* ****************************************************************************/

/***************************************************************************//**
 * Handles the DSP related interrupt requests.
 *
 * @param       void
 *
 * @return      void
 *
 * @pre         
 *
 * Interrupt handler for interrupts of DSP module. It gets the modul's
 * interrupt number and calls the corresponding application callback function, 
 * if there is one registered. If there is not application callback function
 * registered, the interrupt is disabled for the corresponding IRQ number.
 * Finally, the interrupt is cleared.
 *
 ******************************************************************************/
 static __irq void loc_InterruptHandler(void);

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ******************************* INTERRUPTS *********************************/
/* ****************************************************************************/

/***************************************************************************//**
 * @implementation
 * Simple word write access to IRQ_VENABLE register, but with the difference
 * to dsp_SetIRQVEnable, that a special enum (dsp_eInterruptVectorNum_t)
 * is passed as parameter, for security reasons and a more concrete interface
 * definition.
 *
 ******************************************************************************/
void dsp_InterruptEnable(dsp_eInterruptVectorNum_t irqsrc)
{
  DSP_IRQ_VENABLE = (uint16_t) irqsrc;
}

/***************************************************************************//**
 * @implementation
 * Simple word write access to IRQ_VDISABLE register, but with the difference
 * to dsp_SetIRQVDisable, that a special enum (dsp_eInterruptVectorNum_t)
 * is passed as parameter, for security reasons and a more concrete interface
 * definition.
 *
 ******************************************************************************/
void dsp_InterruptDisable(dsp_eInterruptVectorNum_t irqsrc)
{
  DSP_IRQ_VDISABLE = (uint16_t) irqsrc;
}

/***************************************************************************//**
 * @implementation
 * At first the module number is looked up in a table, because module number
 * and module instance base address have a logical connection. Then the
 * interrupt callback function pointer is saved in module interrupt vector
 * table.
 *
 ******************************************************************************/
void dsp_InterruptRegisterCallback(dsp_eInterruptVectorNum_t irqsrc, dsp_InterruptCallback_t cbfnc)
{
  // PRQA S 0316 1
  dsp_sInterruptEnvironmentData_t* evironmentData = (dsp_sInterruptEnvironmentData_t*)  nvic_GetPointerToEnvironmentData(nvic_IRQ_DSP);

  if ((irqsrc < dsp_INTERRUPT_VECTOR_CNT) && (evironmentData != NULL))
  {
    evironmentData->InterrupVectorTable[irqsrc] = cbfnc;
  }
  else {}
}

/***************************************************************************//**
 * @implementation
 * Reverse function of "dsp_RegisterInterruptCallback". Sets the corresponding
 * entry in the module interrupt vector table back to NULL. Very imported,for
 * security reasons the corresponding interrupt is disabled. Otherwise the
 * program could possibly call NULL.
 *
 ******************************************************************************/
void dsp_InterruptDeregisterCallback(dsp_eInterruptVectorNum_t irqvecnum)
{
  // PRQA S 0316 1
  dsp_sInterruptEnvironmentData_t* evironmentData = (dsp_sInterruptEnvironmentData_t*)  nvic_GetPointerToEnvironmentData(nvic_IRQ_DSP);

  if ((irqvecnum < dsp_INTERRUPT_VECTOR_CNT) && (evironmentData != NULL)) 
  {
    dsp_InterruptDisable(irqvecnum);
    evironmentData->InterrupVectorTable[irqvecnum] = NULL;
  }
  else {}  
}

/***************************************************************************//**
 * @implementation
 * Every hardware DSP module has it's own interrupt handler, also because each
 * module has it's own interrupt vector. So the module base address is fixed.
 * The interrupt vector table is provided by the user-application from RAM. The
 * module specific vector tables lie behind the VIC interrupt vector table, which
 * address is saved in the "TABLE_BASE". The module interrupt handler
 * gets the address from the function "vic_GetPointerToEviornmentData".
 * The interrupt vector number is saved in a local variable, because the value
 * of IRQ_VNO could possible change during processing of
 * InterruptHandler. Next the registered interrupt callback function
 * (dsp_RegisterInterruptCallback) is copied into a local function pointer,
 * checked if it's not NULL and at least called. At the end the interrupt
 * request flag is cleared, by writing back the interrupt vector number to
 * IRQ_VNO register.
 *
 ******************************************************************************/
 static __irq void loc_InterruptHandler(void)
{
  dsp_eInterruptVectorNum_t irqvecnum = (dsp_eInterruptVectorNum_t) DSP_IRQ_VNO;
  
  if (irqvecnum < dsp_INTERRUPT_VECTOR_CNT) /* ensure the IRQ trigger is not already gone away until processing starts */
  {
    // PRQA S 0316 1
    dsp_sInterruptEnvironmentData_t* evironmentData = (dsp_sInterruptEnvironmentData_t*) nvic_GetPointerToEnvironmentData(nvic_IRQ_DSP);

    dsp_InterruptCallback_t fptr;
  
    fptr = evironmentData->InterrupVectorTable[irqvecnum];
          
    if(fptr != NULL)
    {          
//      __enable_interrupt();
        
      /* Call interrupt callback function */
      fptr(irqvecnum,  (void*) evironmentData->ContextData);      
      
//      __disable_interrupt();
    }
    else 
    {
      /* if there is no handler function for a particular IRQ, disable this IRQ  */ 
      DSP_IRQ_VDISABLE = (uint16_t) irqvecnum;
    }

    /* Clear interrupt request flag */
    DSP_IRQ_VNO = (uint16_t) irqvecnum;
  }
  else {}
  
  /* RETI will reenable IRQs here */ 
} 


/***************************************************************************//**
 * @implementation
 * First check, whether the interface to NVIC is set and the NVIC interface
 * version fits. Additionally, the module's interrupt environment data has to 
 * be set.
 * If the checks are passed, the module's interrupt handler and its environment
 * is registered in the NVIC.
 *
 ******************************************************************************/
void dsp_InterruptInitialisation(nvic_cpInterfaceFunctions_t vicIf, dsp_pInterruptEnvironmentData_t environmentdata, dsp_pInterruptContextData_t contextdata)
{
  if ((vicIf != (const void *) NULL) && (vicIf->InterfaceVersion == NVIC_INTERFACE_VERSION) && (environmentdata != NULL))
  {
    environmentdata->ContextData = contextdata;

    /* Register module at interrupt handler */
    vicIf->RegisterModule(nvic_IRQ_DSP, &loc_InterruptHandler, environmentdata);
    vicIf->EnableModule(nvic_IRQ_DSP);
  }
  else {}

}
