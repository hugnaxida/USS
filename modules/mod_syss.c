/* *************************************************************************//**
 * @file		mod_syss.c
 *
 * @creator		poe
 * @created		02.07.2017
 * @sdfv                Demo Flow
 *
 * @brief  		Initialization of system-state module and sys-state IRQ handler
 *
 * @purpose
 *
 * TODO: A detailed description of this module
 *
 * ******************************************************************************
 *
 * Demo Code Usage Restrictions:
 * Elmos Semiconductor AG provides this source code file simply and solely for
 * IC evaluation purposes in laboratory and this file must not be used
 * for other purposes or within non laboratory environments. Especially, the use
 * or the integration in production systems, appliances or other installations is
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
 ******************************************************************************
 *
 * $Id: mod_syss.c 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
 *
 ******************************************************************************/

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_syss.h"
#include "CommonInterruptHandler.h"
#include "system_ctrl_InterruptHandler.h"
#include "mod_err.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define VIC_USE_ROMIF 0
/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/
#if VIC_USE_ROMIF == 1
  nvic_cpInterfaceFunctions_t nvic_IfFuns;
#else
  nvic_cpInterfaceFunctions_t nvic_IfFuns = &nvic_InterfaceFunctions;
#endif

static system_ctrl_sInterruptEnvironmentData_t sysctrl_envData; /**< system controll interrupt environment data */
static sys_state_sInterruptEnvironmentData_t sysstate_envData; /**< system state interrupt environment data */

bool_t ChangeStandbyState;    /* True if a change of the standby mode is requested but not yet executed */

/* ****************************************************************************/
/* ******************** FORWARD DECLARATIONS / PROTOTYPES *********************/
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * DSI3 wake up event
 *
 * Is triggered when a wake up event occured on dsi3
 *
 * @param       irqsrc          Triggered interrupt event number
 * @param       contextdata     Pointer to SCI context data
 * @return      none
 * ****************************************************************************/
void loc_Dsi3WakeUpEvent(system_ctrl_eInterruptVectorNum_t irqsrc, system_ctrl_pInterruptContextData_t contextdata);

/* **************************************************************************//**
 * @brief
 * RAM parity error event
 *
 * Is triggered when a parity bit error occured in ram
 *
 * @param       irqsrc          Triggered interrupt event number
 * @param       contextdata     Pointer to SCI context data
 * @return      none
 * ****************************************************************************/
void loc_RAMparityErrorEvent(sys_state_eInterruptVectorNum_t irqsrc, sys_state_pInterruptContextData_t contextdata);

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* *****************************************************************************
 * @brief Initialize SYSS module
 *
 * @param environmentdata  Pointer to Environment data for SYSS module in
 *                         user RAM
 *
 * @pre        NVIC (nvic_VectorInterruptControl) and SYSS (syss_SystemState)
 *             have to presented and initialized.n
 *
 * @post       SYSS module is configured for use.
 *
 * @detaildesc
 * Initializes the SYSS software and hardware module, including the module
 * interrupt vector table. 
 *
 * *****************************************************************************/
void syss_Init(void)
{
  /* Select a clock of 24MHz */
  SYSS_SYS_CLK_SET(syss_CLockSel_24MHZ);  
  
  /* Initialize VIC */
   #if VIC_USE_ROMIF == 1
    if(romIf_MainInterface.Interface_Get(ROMIF_API_VIC, (romIf_cpGenericInterface_t *) &vic_IfFuns, LIN_NULL) != TRUE)
    {
      while(1);
    }
    InterruptHandlerInitialize(nvic_IfFuns);  
  #else
    InterruptHandlerInitialize(&nvic_InterfaceFunctions);
  #endif

  /* Set module priority level */
  nvic_InterfaceFunctions.SetModulePriority(nvic_IRQ_SYS_STATE, nvic_Priority_Level_0);
  
  /* Initialize SWT IRQ */
  system_ctrl_InterruptInitialisation(&nvic_InterfaceFunctions, &sysctrl_envData, NULL);
  
  /* standby request flag */
  ChangeStandbyState = false;

  /* register callback function for dsi3 wakeup interrupt */
  system_ctrl_InterruptRegisterCallback(system_ctrl_IRQ_DSI3_WAKE_UP, loc_Dsi3WakeUpEvent);
  
  /* Initialize SYS_STATE IRQ and enable module sys_state in nvic SM51*/
  sys_state_InterruptInitialisation(&nvic_InterfaceFunctions, &sysstate_envData, NULL);
  
  /* register callback function for RAM parity error event SM51*/
  sys_state_InterruptRegisterCallback(sys_state_IRQ_SRAM_PARITY, loc_RAMparityErrorEvent);
}   

/* **************************************************************************//**
 * @brief
 * Enter Sleep
 *
 * Initializes and enters standby mode
 *
 * @return      none
 * ****************************************************************************/
void syss_EnterSleep(void)
{
  /* set request flag so we can leave the DSI interrupt properly */
  ChangeStandbyState = true;
}

/* **************************************************************************//**
 * @brief
 * Exit Sleep
 *
 * Exits and Deinitializes standby mode
 *
 * @return      none
 * ****************************************************************************/
void syss_ExitSleep(void)
{
  /* Deinitials standby mode */
  SYSTEM_CTRL_POWER_bit.standby = 0u;
  /* disable dsi3 wake up event interrupt */
  system_ctrl_InterruptDisable(system_ctrl_IRQ_DSI3_WAKE_UP);
  /* switch DSP on */
  DSP_DSP_CTRL_bit.dsp_on = 1u; /*SMA52417-142*/
}

/* **************************************************************************//**
 * @brief
 * Processes requests to change the standby mode
 *
 * @image html "syss_ProcessStandbyRequests.png" "Activity Diagram: Check for standby request" max-width=640
 * <a href="syss_ProcessStandbyRequests.png">klick here to enlarge image</a>
 *
 * @return      none
 * ****************************************************************************/
void syss_ProcessStandbyRequests(void)
{
  if(true == ChangeStandbyState)
  {
    /* go into standby mode */

    /* enable dsi3 wake up event interrupt */
    system_ctrl_InterruptEnable(system_ctrl_IRQ_DSI3_WAKE_UP);

    DSP_DSP_CTRL_bit.dsp_on = 0;
    DSP_DSP_CTRL_bit.dsp_pwr_dwn = 1;

    while(1  == DSP_DSP_CTRL_bit.dsp_on_state)
    {
      /* wait...*/
    }

    SYSTEM_CTRL_POWER_bit.standby = 1;

    __WFI();

    ChangeStandbyState = false;
  }
}

/* **************************************************************************//**
 * @brief
 * DSI3 wake up event
 *
 * Is triggered when a wake up event occured on dsi3
 *
 * @param       irqsrc          Triggered interrupt event number
 * @param       contextdata     Pointer to SCI context data
 * @return      none
 * ****************************************************************************/
void loc_Dsi3WakeUpEvent(system_ctrl_eInterruptVectorNum_t irqsrc, system_ctrl_pInterruptContextData_t contextdata)
{
  /* empty function -> used to wakeup */
}

/* **************************************************************************//**
 * @brief
 * RAM parity error event
 *
 * Is triggered when a parity bit error occured in ram
 *
 * SM51: RAM Check
 * (for details see SafetyManual)
 *
 * @param       irqsrc          Triggered interrupt event number
 * @param       contextdata     Pointer to SCI context data
 * @return      none
 * ****************************************************************************/
void loc_RAMparityErrorEvent(sys_state_eInterruptVectorNum_t irqsrc, sys_state_pInterruptContextData_t contextdata)
{
  err_SetHwErrorFlag(ERR_SRAM_PARITY_ERROR, ERR_NO_ERROR2);
}
