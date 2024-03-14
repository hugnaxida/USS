/* *************************************************************************//**
 * @file                main.c
 *
 * @creator             POE
 * @created             15.04.2017
 * @sdfv
 *
 * @brief               main program entry
 *
 * @purpose
 * This file contains the main function of the project, which initiates all modules
 * and loops through all module specific tasks
 *
 * *****************************************************************************
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
 * *****************************************************************************
 *
 * Revision: $Revision: 424 $
 *
 * ****************************************************************************/

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/

#include "version.h"
#include "modules/mod_syss.h"
#include "mod_wdg.h"
#include "mod_gpio.h"
#include "mod_dac.h"
#include "mod_ada.h"
#include "mod_dsi3_cfg.h"
#include "mod_dsp.h"
#include "mod_err.h"
#include "mod_eeprom.h"
#include "mod_app.h"
#include "mod_lab.h"
#include "mod_mem.h"
#include "mod_crc16.h"
#include "mod_dsi3.h"
#include "mod_eeprom_access.h"
#include "mod_uart.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

#define SYS_STATE_ENABLE_DEBUG_ENABLE_DEBUG (0xA561)                            /* Register enables debugging on hardware */
#define EE_TRIM_VALUE                       (3u)                                /* Init value for EEPROM MARGIN_TRIM Register */

/*Disable following rule to be able to write to specific adress with @ symbol */
/*PRQA S 289 1*/
#define SET_FIRMWARE_VERSION_NUMBER(num)    __root const uint16_t FirmwareVersionNumber @ 0x80 = (uint16_t)num; /* Address 0x0000 0080 is in ROM! Identifier __root will prohibit removing by linker optimization */
#define SET_FW_VERSION_PROJECT(num)         __root const char ProjectName[11] @ 0x82 = num; /* Address 0x0000 0082 is in ROM! Identifier __root will prohibit removing by linker optimization */
/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/

static Dsi3Drv_sApplCtrlData_t applRuntimeData;                                 /* application runtime data environment */
uint16_t HardwareVersionNumber = 0u;                                            /* global variable for hw-revision */

static UART_RX_Data rx_data;

#ifdef DEBUG
#warning (ATTENTION DEBUG FLAG IS ACTIVE)                                       /* if DEBUG flag is set in preprocessor defines, no safe state is activated */
#endif

#ifdef FPGA_52417B
#warning (ATTENTION YOU ARE COMPILING FOR FPGA BOARD)
#endif

/* set the firmware version number to OTP address 0x0000 0080 */
SET_FIRMWARE_VERSION_NUMBER((FW_VERSION_NUMBER))
/* set the firmware project name to OTP address 0x0000 0082 */
SET_FW_VERSION_PROJECT((FW_VERSION_PROJECT))
/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/


/* *************************************************************************//**
 * @implementation
 * system startup init after POR
 *
 * Sets system clock and configures gpio. 
 * 
 * @param   none
 * @return  none
 * ****************************************************************************/
static void loc_StartupInit(void)
{
  bool_t initSuccess = FALSE;

  /* Set CPU clock, initialize nvic */
  syss_Init();
  
  /* enable global interrupt flag */
  __enable_interrupt();
  
  /* Initialize watchdog module WDG */
  wdg_Init();
  
  /* Set GPIO outs */
  gpio_Init();
  
  /* Initialize DACs */
  dac_Init();
  
  /* Initialize ADA */
  ada_Init();

  /* Init SWTimer module */
  swtimer_Init();

  /* Init DSP module */
  dsp_Init();
  
  /* Init Eeprom */
  initSuccess = eeprom_Initialize(EE_TRIM_VALUE);
  if (FALSE == initSuccess)
  {
    /* error handling */
    err_ErrorHandler(ERR_MODLIST_MAIN);
  }
  
  /* Init CRC16 module */
  crc16_Init();
}

/* *************************************************************************//**
 * @implementation
 * init application environment
 *
 * Initializes and configures the application related environments.
 * 
 * @param   none
 * @return  none
 * ****************************************************************************/
void main_Appl_Init(void)
{
  bool_t configSuccessful = true;
  /*
   *    2.1 All configuration values stored in EEPROM are read to RAM/Register.
   */

  /* Get pointer to module control data */
  applRuntimeData.DSI3Ctrl      = Dsi3_GetDSI3Ctrl();
  applRuntimeData.MeasCtrl      = meas_GetCtrl();
  applRuntimeData.EepromCtrl    = Eeprom_GetDataPointer();


  /* initialize callback related runtime data */
  Dsi3_Callbacks_Init(&applRuntimeData);
  /* Initialize eeprom module */
  configSuccessful = configSuccessful && Eeprom_Init(&(applRuntimeData.MeasCtrl->Parameters));
  /* initialize the memory module */
  configSuccessful = configSuccessful &&  mem_Init(&(applRuntimeData.MeasCtrl->Parameters));
  /* initialize measurement control module */
  configSuccessful = configSuccessful && meas_init();
  /* initialize appmode module */
  configSuccessful = configSuccessful && app_Init(&applRuntimeData);
  /* initialize the lab mode module */
  lab_init_module();
  
  /* goto error handler if initialization failed */
  if(false == configSuccessful)
  {
    err_ErrorHandler(ERR_MODLIST_MAIN);
  }
  else
  {
    /* everything ok */
  }
}

void main_uart_rx_data(){
  Uart_Init();

  Uart_Receive_interrupt(rx_data);

  parse_and_handle_data(rx_data);
}
/***************************************************************************//**
 * Main
 ******************************************************************************/

/* *************************************************************************//**
 * @implementation
 * Main routine
 *
 * main entry point after startup.
 *
 * @image html "main.png" "Activity Diagram: main" max-width=640
 * <a href="main.png">klick here to enlarge image</a>
 * 
 * @param   none
 * @return  int
 * ****************************************************************************/
int main(void)
{ 
  /* activate debugging */
  SYS_STATE_ENABLE_DEBUG = SYS_STATE_ENABLE_DEBUG_ENABLE_DEBUG;

  /* sys init */
  loc_StartupInit();

  /* initialize application environment */		
  main_Appl_Init();

  /*receive UART data*/
  main_uart_rx_data();

  /* initialize DSI3 driver */
  if (!Dsi3_Init(nvic_IfFuns, &applRuntimeData))
  {
    while(1)
    {
      /* e.g. if dsi3 driver is not compatible to hw-revision */
    }
  }
  else{}

  /* Start the watchdog */
  wdg_Start();
  
  /* enable interrupt for RAM parity error event SM51 */
  sys_state_InterruptEnable(sys_state_IRQ_SRAM_PARITY);
  
  /* readout HW revision */
  HardwareVersionNumber = DSI3_HW_VERSION;

  while(1)
  {	
    /* do DSI3 bus tasks */
    Dsi3_BusIfFuns->Task((Dsi3BusIf_pGenericEnvData_t) Dsi3_BusEnvData);

    /* check for a requested standby mode */
    syss_ProcessStandbyRequests();

    /** do application task(s) **/
    COMCtrl_Task((Dsi3BusIf_pGenericEnvData_t) Dsi3_BusEnvData);

    /* execute measurement task */
    meas_Task();

    /* execute EEPROM task */
    Eeprom_Task();

    /* execute crc task */
    mem_Task();

    
    /* process lab mode data */
    lab_Task();

    
    /*kick the dog see "SM53 - Program Flow Watchdog" */
    wdg_Trigger();
  }
}
