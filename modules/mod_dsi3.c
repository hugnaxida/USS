/***************************************************************************//**
 * @file      mod_dsi3.c
 *
 * @creator   StSl
 * @created   21.09.2017
 * @sdfv
 *
 * @brief     Callback functions for DSI3 bus layer
 *
 * @purpose
 *
 * This file provides all DSI3 related callback functions, which handle
 * incoming CRM, PDCM and DM commands.
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
 * $Id: mod_dsi3.c 424 2019-03-15 16:20:34Z siko $
 *
 * $Revision: 424 $
 *
 ******************************************************************************/
/* **************************************************************************//***/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_dsi3.h"
#include "mod_dsi3_cfg.h"
#include "def_dsi3.h"
#include "mod_eeprom.h"
#include "mod_err.h"
#include "mod_app.h"
#include "mod_lab.h"
#include "mod_syss.h"
#include "mod_mem.h"
#include "el_regs_m52417a_IAR.h"
/* ****************************************************************************/
/* ***************************** USER INCLUDES ********************************/
/* ****************************************************************************/
static Dsi3Drv_pApplCtrlData_t loc_pApplRuntimeData; /* pointer to application runtime data environment */

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
static const uint32_t loc_IcRegAccRegMapping[DSI3_IC_REGACCESS_MODNUM_CNT] = {
    0x00000000u,    /**< 0  IMEM Instruction Memory (OTP) */
    0x20000000u,    /**< 1  DMEM Data Memory (SRAM), size is implementation defined */
    0x30000000u,    /**< 2  SYS_ROM System ROM */
    0x40000000u,    /**< 3  WDOG Watchdog Module */
    0x40000100u,    /**< 4  SYS_STATE System State Module */
    0x40000200u,    /**< 5  CRC16 CCITT-CRC-16 Module */
    0x40000300u,    /**< 6  OTP0_CTRL OTP0 Control Module */
    0x40000500u,    /**< 7  EEPROM_CTRL EEPROM Control Module */
    0x48000000u,    /**< 8  EEPROM EEPROM Memory, size is implementation defined */
    0x50000000u,    /**< 9  GPIO General purpose I/O module */
    0x50000100u,    /**< 10 SWTIMER TIMER module */
    0x50000200u,    /**< 11 DSI3 Communication module */
    0x50000300u,    /**< 12 BRG Burst generation module */
    0x50000400u,    /**< 13 DSP Digital signal processing module */
    0x50000500u,    /**< 14 SYSTEM_CTRL System/Power control module */
    0x50000600u,    /**< 15 DAC_CTRL DAC control module */
    0x50000700u,    /**< 16 ADA Analog data acquisition module */
    0x5F000000u,    /**< 17 UART UART module */
    0xE0000000u,    /**< 18 PPB ARMv6-M Private Peripheral Bus Address Space */
    0xE0001000u,    /**< 19 DWT ARMv6-M Data Watchpoint and Trace (debug) */
    0xE0002000u,    /**< 20 BPU ARMv6-M Break Point Unit (debug) */
    0xE000E000u,    /**< 21 SCS ARMv6-M System Control Space */
    0xE00FF000u,    /**< 22 ROM_TABLE ARMv6-M ROM Table (debug) */
                   /**< 23-31 invalid */
}; /* Register Address mapping for direct access from DSI3 */
/*
. 0x00000000u: IMEM Instruction Memory (OTP) - 指令存储器（OTP），通常用于存放不可修改的固件代码，有时也被称为一次性可编程存储器。
2. 0x20000000u: DMEM Data Memory (SRAM) - 数据存储器（SRAM），作为临时存储数据的地方，其大小在具体实现中可能会有所不同。
3. 0x30000000u: SYS_ROM System ROM - 系统只读存储器，通常用于存放启动加载程序、引导代码或其他重要的固定程序。
4. 0x40000000u: WDOG Watchdog Module - 看门狗模块，用于监控系统的运行状况，如果系统在设定时间内未完成特定操作，则看门狗会触发复位以恢复系统。
5. 0x40000100u: SYS_STATE System State Module - 系统状态模块，用于管理系统的运行状态，如睡眠模式、唤醒、复位等。
6. 0x40000200u: CRC16 CCITT-CRC-16 Module - CRC16校验模块，用于生成和验证数据的CRC16校验码。
7. 0x40000300u: OTP0_CTRL OTP0 Control Module - OTP控制器，用于控制OTP存储器的相关操作。
8. 0x40000500u: EEPROM_CTRL EEPROM Control Module - EEPROM控制模块，用于管理EEPROM（电可擦除可编程只读存储器）的读写操作。
9. 0x48000000u: EEPROM EEPROM Memory - EEPROM存储器，用于长期数据存储，其大小取决于具体实现。
10. 0x50000000u: GPIO General purpose I/O module - GPIO通用输入输出模块，提供对外部设备的控制和状态信号。
11. 0x50000100u: SWTIMER TIMER module - 软件定时器模块，用于产生定时事件或延时。
12. 0x50000200u: DSI3 Communication module - DSI3通信模块，处理与DSI3总线的交互。
13. 0x50000300u: BRG Burst generation module - 突发生成模块，可能用于支持数据传输的突发模式。
14. 0x50000400u: DSP Digital signal processing module - 数字信号处理模块，用于处理音频、图像等数字信号。
15. 0x50000500u: SYSTEM_CTRL System/Power control module - 系统/电源控制模块，涉及系统整体管理和电源管理。
16. 0x50000600u: DAC_CTRL DAC control module - 数模转换器（DAC）控制模块，用于模拟信号输出控制。
17. 0x50000700u: ADA Analog data acquisition module - 模拟数据采集模块，用于获取来自传感器等模拟信号源的数据。
18. 0x5F000000u: UART UART module - 通用异步收发传输器（UART）模块，提供串行通信能力。
19. 0xE0000000u: PPB ARMv6-M Private Peripheral Bus Address Space - ARMv6-M私有外设总线地址空间，用于ARM架构中的外设访问。
20. 0xE0001000u: DWT ARMv6-M Data Watchpoint and Trace (debug) - 数据观察点和跟踪模块，用于调试目的，监测特定内存区域的变化。
21. 0xE0002000u: BPU ARMv6-M Break Point Unit (debug) - 断点单元，用于调试时设置代码断点。
22. 0xE000E000u: SCS ARMv6-M System Control Space - 系统控制空间，包含了处理器关键的控制和状态寄存器。
23. 0xE00FF000u: ROM_TABLE ARMv6-M ROM Table (debug) - 
ROM表，用于调试器识别和访问系统的外设组件调试模块通过这个数组，可以根据模块编号快速找到对应的模块基地址，从而有效地访问和控制IC中的各个模块。
*/
/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/** Advanced paths*/
typedef enum
{
  ADVANCED_PATH_NUMBER_NO_DATA      = (0u),             /**< There is no data in any advanced path buffer */
  ADVANCED_PATH_NUMBER_PATH1        = (1u),             /**< There is data in advanced path 1 buffer */
  ADVANCED_PATH_NUMBER_PATH2        = (2u),             /**< There is data in advanced path 2 buffer */
} loc_eAdvPathNum_t;
/*
该枚举类型 loc_eAdvPathNum_t 定义了一个名为“ADVANCED_PATH_NUMBER_XXX”的枚举集合，用于表示高级路径缓冲区的状态。
在软件或硬件设计中，特别是在处理多通道数据流或并行处理机制时，可能会使用到这种类型的枚举来指示某个特定的高级路径（advanced path）是否包含有效数据。
这里的成员包括：1. ADVANCED_PATH_NUMBER_NO_DATA：•值为 (0u)，表示当前没有任何一个高级路径缓冲区包含有效数据。2. ADVANCED_PATH_NUMBER_PATH1：•值为 (1u)，表示高级路径1缓冲区中存在有效数据。
3. ADVANCED_PATH_NUMBER_PATH2：•值为 (2u)，表示高级路径2缓冲区中存在有效数据。
通过这种方式定义枚举类型，开发者可以方便地在代码中以清晰且类型安全的方式来引用不同路径的数据可用性状态，而不是直接使用整数值，从而提高代码的可读性和可维护性。
例如，在函数中检查某条高级路径是否有新数据到达时，可以直接使用 loc_eAdvPathNum_t 枚举变量，并与上述枚举常量进行比较。
*/
/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ******************** FORWARD DECLARATIONS / PROTOTYPES *********************/
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * synchs CRM clock to SNY_CNT
 *
 * @param       genericEnvData              pointer to Bus environment data
 * @return      none
 * ****************************************************************************/
static void loc_SynchCRMClock(Dsi3BusIf_pGenericEnvData_t genericEnvData);

/* **************************************************************************//**
 * @brief
 * synchs PCDM clock to 1ms BRC time distance
 *
 * @param       genericEnvData              pointer to Bus environment data
 * @return      none
 * ****************************************************************************/
static void loc_SynchPDCMClock(Dsi3BusIf_pGenericEnvData_t genericEnvData);


/* **************************************************************************//**
 * @brief
 * Change Mode to PDCM
 *
 * Changes DSI3 to PDCM Mode and prepares configuration data
 *
 * @param       genericEnvData      generic environment data pointer, should point to bus environment data
 * @param       pdcmType            PDCM response type
 * @return      none
 * ****************************************************************************/
static void loc_ChangeModeToPdcm(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3_ePDCMType_t pdcmType);

/* ***************************************************************************
 * @brief
 * Set Last Executed CRM Command
 *
 * Sets the last executed crm command on dsi3 runtime data
 *
 * @param       cmd                 DSI3 CRM command id
 * @return      none
 * ****************************************************************************/
#define loc_SetLastExecutedCrmCmd(cmd) (loc_pApplRuntimeData->DSI3Ctrl->CrmLastCommand = cmd)

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * dsi driver initialization callback
 *
 * @param       applRuntimeData      generic application data, should point to application environment data
 * @return      none
 * ****************************************************************************/
void Dsi3_Callbacks_Init(Dsi3Drv_pApplCtrlData_t applRuntimeData)//初始化DSI驱动回调的函数
{
  if(NULL != applRuntimeData)
  {
    loc_pApplRuntimeData = applRuntimeData;
  }
  else
  {
    /* invalid pointer -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }
}

/* **************************************************************************//**
 * @brief
 * dsi communication task
 *
 * @image html "COMCtrl_Task.png" "Activity Diagram: DSI3 communication task" max-width=640
 * <a href="COMCtrl_Task.png">klick here to enlarge image</a>
 *
 * @param       genericEnvData      generic environment data pointer, should point to bus environment data
 * @return      none
 * ****************************************************************************/
void COMCtrl_Task(Dsi3BusIf_pGenericEnvData_t genericEnvData)//COMCtrl_Task 函数主要作用是作为一个循环执行的任务，监控并处理DSI3的通信同步需求，只有在正确初始化后才会正常执行相应操作。若在未初始化的情况下被调用，则会触发错误处理机制。
{
  if(NULL != loc_pApplRuntimeData)
  {
    if(TRUE == loc_pApplRuntimeData->DSI3Ctrl->SyncFlag)
    {
      loc_pApplRuntimeData->DSI3Ctrl->SyncFlag = FALSE;
      loc_SynchCRMClock(genericEnvData);
    }
    else
    {
      /* nothing to do here */
    }
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }
}
/*
函数内部实现：1. 首先检查局部变量 loc_pApplRuntimeData 是否不为空。如果它不为空，说明之前已经通过 Dsi3_Callbacks_Init 函数成功初始化并保存了应用运行时数据。
2. 如果 loc_pApplRuntimeData 不为空并且其内部结构体成员 DSI3Ctrl->SyncFlag 为真（TRUE），那么将 SyncFlag 设置为假（FALSE），并调用 loc_SynchCRMClock(genericEnvData) 函数来同步时钟。
这一步骤可能涉及到了与DSI总线通信相关的同步操作。3. 如果 DSI3Ctrl->SyncFlag 为假（FALSE），则在此处没有其他操作需要执行。4. 如果 loc_pApplRuntimeData 为空，说明在调用本函数前，尚未正确执行初始化。
此时，函数调用了错误处理函数 err_ErrorHandler，并传入错误代码 ERR_MODLIST_DSI3。这意味着在未完成初始化的情况下就试图执行通信任务，这是一种错误情况，需要触发错误处理流程。
总之，COMCtrl_Task 函数主要作用是作为一个循环执行的任务，监控并处理DSI3的通信同步需求，只有在正确初始化后才会正常执行相应操作。若在未初始化的情况下被调用，则会触发错误处理机制。
*/


/* ****************************************************************************/
/*                               BUS CALLBACKS                                */
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * error callback routine from bus layer
 *
 * The callback routine for error handling from the bus layer.
 *
 * @param       genericEnvData          generic environment data pointer, should point to bus environment data
 * @param       busIfFuns               bus interface function
 * @param       error                   DSI3 bus error code
 * @param       genericBusCbCtxData     generic context data pointer (optional)
 * @return      none
 * ****************************************************************************/
void Dsi3_BusErrorCbFun(Dsi3BusIf_pGenericEnvData_t genericEnvData,       Dsi3BusIf_cpInterfaceFunctions_t busIfFuns,
                              Dsi3BusIf_Error_t error,                          Dsi3BusIf_pGenericCbCtxData_t genericBusCbCtxData)
{
  Dsi3BusIf_ErrorCodes_t err = (Dsi3BusIf_ErrorCodes_t)error;
  switch(err)
  {
  case Dsi3BusIf_ERR_START_ERR_EVT:
    /* Invalid start edge detected */
    err_SetComErrorFlag(ERR_INVALID_START_EDGE_DETECTED);
    break;
  case Dsi3BusIf_ERR_FCC_ERROR:
    /* Receiver reached error state */
    err_SetComErrorFlag(ERR_RECEIVER_RECHED_ERROR_STATE);
    break;
  case Dsi3BusIf_ERR_DISC_ERROR:
    /* Discovery pulse invalid */
    err_SetComErrorFlag(ERR_DISCOVERY_PULSE_INVALID);
    break;
  case Dsi3BusIf_ERR_PDCM_ERROR:
    /* PDCM pulse invalid -> set ComErrFlag */
    err_SetComErrorFlag(ERR_PDCM_PULSE_INVALID);
    break;
  case Dsi3BusIf_ERR_CRC:
    /* invalid CRC received by DSI3 -> set ComErrFlag */
    err_SetComErrorFlag(ERR_CRC_OF_RECEIVED_COMMAND_INVALID);
    break;
  case Dsi3BusIf_ERR_DISC_VERIFY_ERROR:  
    /* Set discovery error verification flag for application */
    err_SetHwErrorFlag(ERR_NO_ERROR1, ERR_DISC_VERIFY_ERROR);
    break;
  default:
    /* unknown error */
    break;
  }
}
/*
•Dsi3BusIf_pGenericEnvData_t genericEnvData：通用环境数据指针，通常指向与总线环境相关的信息。•Dsi3BusIf_cpInterfaceFunctions_t busIfFuns：总线接口函数的指针，可能用于执行底层总线操作。
•Dsi3BusIf_Error_t error：DSI3总线错误代码，用于标识具体发生的错误类型。•Dsi3BusIf_pGenericCbCtxData_t genericBusCbCtxData：通用上下文数据指针，这是一个可选参数，可能包含额外的上下文信息。
函数内部通过switch-case语句遍历不同的错误类型，并根据不同错误类型设置相应的错误标志。例如：•当接收到无效起始边沿信号时，设置ERR_INVALID_START_EDGE_DETECTED错误标志。
•当接收器进入错误状态时，设置ERR_RECEIVER_REACHED_ERROR_STATE错误标志。•对于发现脉冲无效错误，设置ERR_DISCOVERY_PULSE_INVALID错误标志。•对于PDCM脉冲无效错误，设置ERR_PDCM_PULSE_INVALID错误标志。
•接收到无效CRC校验时，设置ERR_CRC_OF_RECEIVED_COMMAND_INVALID错误标志。•在发现错误验证阶段出错时，设置应用层的ERR_DISC_VERIFY_ERROR硬件错误标志。
对于未知错误类型，函数不做特别处理。所有错误标志都会通过err_SetComErrorFlag或err_SetHwErrorFlag函数设置，这些函数可能会触发进一步的错误处理操作，例如通知上层应用、记录日志或采取恢复措施。
*/

/* **************************************************************************//**
 * @brief
 * Dsi3 mode change callback routine from bus layer
 *
 * The callback routine for dsi3 mode change handling from the bus layer.
 *
 * @param   genericEnvData          generic environment data pointer, should point to bus environment data
 * @param   busIfFuns               bus interface function
 * @param   currentMode             current DSI3 mode
 * @param   genericBusCbCtxData     generic context data pointer (optional)
 * @return  none
 * ****************************************************************************/
void Dsi3_BusModeChangedCbFun(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_cpInterfaceFunctions_t busIfFuns,
                                    Dsi3BusIf_eCommunicationMode_t currentMode, Dsi3BusIf_pGenericCbCtxData_t genericBusCbCtxData)
{
  /*
   * do mode change processing here aka. what do we have to do, if our mode has been changed?
   */
#if defined(FPGA_52417B)
  if(currentMode == Dsi3BusIf_eCOMM_DISCOVERYMODE)
  {
    Dsi3_BusIfFuns->UpdateDeviceAddress(genericEnvData, 7u);
  }
#endif
}

/* **************************************************************************//**
 * @brief
 * Auto addressing callback routine from bus layer
 *
 * The callback routine for auto addressing changes the NAD depending on the number of pulses.
 *
 * @param   busEnvData                    bus environment data pointer
 * @param   busIfFuns                     bus interface function
 * @param   pulseNum                      number of Discovery pulses since start of Discovery mode
 * @param   currentDiscoveryModeStatus    current Discovery mode status
 * @param   genericTransCbCtxData          genericCbCtxData generic context data pointer (optional)
 * @return  void
 * ****************************************************************************/
void Dsi3_BusAutoAddrCbFun(Dsi3BusIf_pGenericEnvData_t busEnvData, Dsi3BusIf_cpInterfaceFunctions_t busIfFuns, Dsi3BusIf_CountValue_t pulseNum,
    Dsi3BusIf_DiscoveryModeStatus_t currentDiscoveryModeStatus, Dsi3BusIf_pGenericCbCtxData_t genericTransCbCtxData)
{
  if (Dsi3BusIf_eDISCSTAT_ADDRESSED == currentDiscoveryModeStatus)
  {
    /* Update current DSI3 slave ID  */
    #if !defined(FPGA_52417B) /*< auto-addressing is not available on the FPGA */

    loc_pApplRuntimeData->DSI3Ctrl->CurrentNAD = pulseNum;

    /* Propagate NAD change back to BUS layer */
    if (Dsi3_BusIfFuns->UpdateDeviceAddress(busEnvData, pulseNum))
    {
      /* save id to ram */
      loc_pApplRuntimeData->MeasCtrl->Parameters.data.SlaveId.fields.SlaveId = pulseNum;
      loc_pApplRuntimeData->EepromCtrl->data.SlaveId.fields.SlaveId = pulseNum;

      /* update PDCM response time slot */
      uint16_t myStart;
      switch(pulseNum)
      {
      case 1:
        myStart = loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor1;
        break;
      case 2:
        myStart = loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor2;
        break;
      case 3:
        myStart = loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor3;
        break;
      case 4:
        myStart = loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor4;
        break;
      case 5:
        myStart = loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor5;
        break;
      case 6:
        myStart = loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor6;
        break;
      default:
        myStart = loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor7;
        break;
      }
      myStart = myStart - ((pulseNum - 1) * DSI3_CFG_PDCM_SLOT_TIME);
      (void)Dsi3_BusIfFuns->UpdatePDCMStartSlotOffset(busEnvData, myStart);
      /* Build CRM response */
    }
    else
    {
      /* newNad was not valid! */
    }
    #endif /* END of: (FPGA_52417B) */
  }
  else{/*do nothing */}
}
/*函数的主要功能：1. 首先，判断当前的发现模式状态（currentDiscoveryModeStatus）是否为已寻址状态（Dsi3BusIf_eDISCSTAT_ADDRESSED）。
2. 如果是已寻址状态，则执行以下操作：•在非FPGA_52417B平台上，更新应用运行时数据（loc_pApplRuntimeData）中DSI3控制器（DSI3Ctrl）的当前NAD值为脉冲数量（pulseNum）。
•调用总线接口函数（busIfFuns）中的UpdateDeviceAddress方法，将新的NAD值（pulseNum）通知给总线层。
•将新的NAD值保存到RAM中的测量控制器（MeasCtrl）和EEPROM控制器（EepromCtrl）的相关字段中。•根据NAD值（pulseNum）的不同，更新PDCM响应时间槽（PDCMStartSlotOffset）的开始时间。
3. 如果UpdateDeviceAddress返回成功，即新的NAD值有效，则继续执行上述操作；否则，表示新的NAD值无效。
4. 若当前发现模式状态不是已寻址状态，则不做任何操作。
总结起来，该函数主要用于处理DSI3总线在发现模式下自动分配地址的过程，包括更新当前设备地址、保存设备ID至内存和调整PDCM响应时间槽等相关配置。
而在FPGA_52417B平台上，由于不支持自动寻址，这部分功能将被跳过。*/
/* ****************************************************************************/
/*                          CRM/PDCM CALLBACKS                                */
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * CRM: default handler routine
 * default crm handler to use if for non assigned crm commands.
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 * 
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      never
 *              Dsi3BusIf_eCMDACT_IGNORE        ever
 * ****************************************************************************/
Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_Default (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer,
                                                           Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad,
                                                           Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* 1. if in CRM State -> Ignore */
  /* 2. if in PDCM State -> switch to CRM, stop measurement */
  /* 3. if in Discovery State -> stop discovery mode & switch to CRM */
  if(NULL != loc_pApplRuntimeData)
  {
    loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull = FALSE;

    /* disable EEPROM access */
    Eeprom_Disable();

    /* refresh CRM application data */
    loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull = TRUE;
    loc_SetLastExecutedCrmCmd(dsi3Drv_eCRM_COMMAND_ID_NOP1);

    loc_pApplRuntimeData->DSI3Ctrl->SyncFlag = TRUE;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }

  /* ignore */
  return Dsi3BusIf_eCMDACT_IGNORE;
}
/*•genericEnvData：指向DSI3总线环境数据结构的指针。•commandBuffer：指向CRM命令数据结构的指针（位于缓冲区中）。•responseBuffer：指向CRM响应数据结构的指针（输出缓冲区）。
•currentNad：当前分配的网络地址（NAD）。•genericCbCtxData：指向相关上下文数据的指针。
函数的主要逻辑如下：1. 检查当前是否处于CRM状态，如果是，则忽略该命令。2. 如果处于PDCM（Physical Data Channel Mapping）状态，转换到CRM状态并停止测量。
3. 如果处于发现（Discovery）状态，停止发现模式并切换到CRM状态。接着，如果loc_pApplRuntimeData不为空，则执行以下操作：•清除上次CRM命令执行成功的标志。
•禁用EEPROM访问。•刷新CRM应用数据，标记上次执行成功的CRM命令为NOP1（No Operation）。•设置同步标志（SyncFlag）为TRUE。
如果loc_pApplRuntimeData为空，则意味着在正确初始化之前就调用了该函数，这时调用错误处理函数 err_ErrorHandler 并传入错误码 ERR_MODLIST_DSI3。
最后，无论何种情况，函数都返回 Dsi3BusIf_eCMDACT_IGNORE，表示忽略此次CRM命令。*/
/* **************************************************************************//**
 * @brief
 * CRM: Start a standard measurement
 * initiate an ultrasonic measurement cycle by using the echo detection in the fix frequency signal path
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 * 
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      never
 *              Dsi3BusIf_eCMDACT_IGNORE        ever
 * ****************************************************************************/
Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_MeasExecute (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer,
                                                                      Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad,
                                                                      Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* 1. if in CRM State -> start meas if addressed & switch to PDCM*/
  /* 2. if in PDCM State -> restart meas if addressed & switch to PDCM*/
  /* 3. if in Discovery State -> stop discovery mode & switch to CRM */

  /* Check Data */
  if ((NULL != genericEnvData) && (NULL != commandBuffer) && (NULL != loc_pApplRuntimeData))
  {
    loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull = FALSE;

    /* disable EEPROM access */
    Eeprom_Disable();

    /* only execute if no module is busy */     
    if(false == Eeprom_CheckIfBusy())
    {
      /* prepare received Data */
      Dsi3_uCrmCommand_t rcvData;
      rcvData.rawData = commandBuffer->Fields;

      /* Only execute if Wildcard */
      if (DSI3_NAD_BROADCAST == rcvData.MeasurementExecute.PhysicalAddress)
      {
        bool_t errorFlagActive = FALSE;
        /* check if safe state is active */
        errorFlagActive = err_GetGlobalHwErrFlag();
        errorFlagActive = (bool_t)((uint8_t)errorFlagActive | (uint8_t)err_GetGlobalComErrFlag());
#ifdef DEBUG
        errorFlagActive = FALSE;
#endif
        
        /* only execute if safe state is not active SM60 */
        if(errorFlagActive != TRUE)
        {
          
          /* start meas if addressed & switch to PDCM */
          switch(currentNad)
          {
          case 1:
            meas_StartStandardMeasurement((Meas_eMeasurementConf_t)rcvData.MeasurementExecute.Sensor1, (Meas_eMeasurementMode_t)rcvData.MeasurementExecute.Mode, (Meas_eMeasurementProfile_t)rcvData.MeasurementExecute.Profile);
            break;
          case 2:
            meas_StartStandardMeasurement((Meas_eMeasurementConf_t)rcvData.MeasurementExecute.Sensor2, (Meas_eMeasurementMode_t)rcvData.MeasurementExecute.Mode, (Meas_eMeasurementProfile_t)rcvData.MeasurementExecute.Profile);
            break;
          case 3:
            meas_StartStandardMeasurement((Meas_eMeasurementConf_t)rcvData.MeasurementExecute.Sensor3, (Meas_eMeasurementMode_t)rcvData.MeasurementExecute.Mode, (Meas_eMeasurementProfile_t)rcvData.MeasurementExecute.Profile);
            break;
          case 4:
            meas_StartStandardMeasurement((Meas_eMeasurementConf_t)rcvData.MeasurementExecute.Sensor4, (Meas_eMeasurementMode_t)rcvData.MeasurementExecute.Mode, (Meas_eMeasurementProfile_t)rcvData.MeasurementExecute.Profile);
            break;
          case 5:
            meas_StartStandardMeasurement((Meas_eMeasurementConf_t)rcvData.MeasurementExecute.Sensor5, (Meas_eMeasurementMode_t)rcvData.MeasurementExecute.Mode, (Meas_eMeasurementProfile_t)rcvData.MeasurementExecute.Profile);
            break;
          case 6:
            meas_StartStandardMeasurement((Meas_eMeasurementConf_t)rcvData.MeasurementExecute.Sensor6, (Meas_eMeasurementMode_t)rcvData.MeasurementExecute.Mode, (Meas_eMeasurementProfile_t)rcvData.MeasurementExecute.Profile);
            break;
          default:
            /* Error: no valid current Nad?? */
            break;
          }

          /* check if a measurement has started and switch to pdcm if necessary */
          if (meas_eMeasConf_NONE != meas_GetMeasConf())
          {
            /* switch to PDCM */
            switch((Meas_eMeasurementMode_t)rcvData.MeasurementExecute.Mode)
            {
            case meas_eMeasMode_APPLICATION:
              /* fall through */
            case meas_eMeasMode_APPLICATION2:
              loc_ChangeModeToPdcm(genericEnvData, DSI3_TYPE_MEAS_RESULT_APP_MODE);
              break;
            case meas_eMeasMode_LAB:
              /* fall through */
            case meas_eMeasMode_APPLAB:
              loc_ChangeModeToPdcm(genericEnvData, DSI3_TYPE_MEAS_RESULT_LAB_MODE);
              break;
            default:
              /* this case should be impossible */
              break;
            }
          }
          else
          {
            /* Nothing to do, Mode was ignore, so ignore.. */
          }
        }
        else
        {
          /* set measurement abort flag if safe state is active */
          loc_pApplRuntimeData->MeasCtrl->RuntimeData.MeasAbortFlag = TRUE;
        }
      }
      else
      {
        /* no broadcast -> ignore */
      }
    }
    else
    {
      /* one module is busy -> dont execute cmd and return busy state */
    }

    /* refresh CRM application data */
    loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull = TRUE;
    loc_SetLastExecutedCrmCmd(dsi3Drv_eCRM_COMMAND_ID_MEASUREMENT_EXECUTE);

    loc_pApplRuntimeData->DSI3Ctrl->SyncFlag = TRUE;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }

  /* No response necessary */
  return Dsi3BusIf_eCMDACT_IGNORE;
}
/*
函数 Dsi3_CrmCmdHandler_MeasExecute 处理的是发起标准测量请求的CRM命令。函数首先对输入参数进行有效性检查，并在满足条件时禁用EEPROM访问。
接下来，函数根据接收到的命令中的广播地址判断是否执行操作。当目标地址为广播地址（DSI3_NAD_BROADCAST）且设备处于非故障安全状态时，针对不同的当前网络地址（NAD），
函数调用meas_StartStandardMeasurement函数启动标准测量，该函数接受传感器配置、测量模式和测量配置参数。在启动测量后，函数会检查是否成功启动了测量。
如果确实开始了测量，根据接收到的测量模式参数，函数调用loc_ChangeModeToPdcm函数切换到PDCM（Physical Data Channel Mapping）模式，并设定相应的结果类型。
如果未能启动测量（例如，因为设备处于繁忙状态或安全状态），函数会相应地设置测量终止标志或直接忽略命令。无论测量是否成功执行，函数都会刷新CRM应用数据，记录上次执行成功的CRM命令，并设置同步标志为TRUE。
在整个函数流程结束后，无论哪种情况，函数都将返回 Dsi3BusIf_eCMDACT_IGNORE，表示不会对命令产生响应。此外，当函数在初始化之前就被调用或输入参数无效时，会调用错误处理函数 err_ErrorHandler 报告错误。
switch语句块，它主要根据当前分配的NAD（Network Address Designation）值来启动特定传感器的标准测量。入参是currentNad，它是当前设备在网络中的地址标识符.
这个switch语句的作用是根据接收到的测量模式决定是否将设备切换到PDCM模式，并指定不同类型的结果模式。例如，在应用程序模式或实验室模式下，调用loc_ChangeModeToPdcm函数切换到PDCM模式，并设置结果模式类型。
综上所述，这两个switch语句共同协作，依据接收到的CRM命令内容来确定应该对哪个传感器执行何种类型的测量，并在必要时切换到PDCM模式以准备数据传输。
*/
/* **************************************************************************//**
 * @brief
 * CRM: Start an advanced measurement
 * initiate an ultrasonic measurement cycle by using the echo detection in the advanced signal paths
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      never
 *              Dsi3BusIf_eCMDACT_IGNORE        ever
 * ****************************************************************************/
Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_AdvMeasurementExecute (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer,
                                                                         Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad,
                                                                         Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)//high
{
  /* 1. if in CRM State -> start meas if addressed & switch to PDCM*/
  /* 2. if in PDCM State -> restart meas if addressed & switch to PDCM*/
  /* 3. if in Discovery State -> stop discovery mode & switch to CRM */

  /* Check Data */
  if ((NULL != genericEnvData) && (NULL != commandBuffer) && (NULL != loc_pApplRuntimeData))
  {
    loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull = FALSE;

    /* disable EEPROM access */
    Eeprom_Disable();

    /* only execute if no module is busy */
    if(false == Eeprom_CheckIfBusy())
    {
      /* prepare received Data */
      Dsi3_uCrmCommand_t rcvData;
      rcvData.rawData = commandBuffer->Fields;

      /* Only execute if Wildcard */
      if (DSI3_NAD_BROADCAST == rcvData.AdvMeasurementExecute.PhysicalAddress)
      {
        bool_t errorFlagActive = FALSE;
        /* check if safe state is active */
        errorFlagActive = err_GetGlobalHwErrFlag();
        errorFlagActive = (bool_t)((uint8_t)errorFlagActive | (uint8_t)err_GetGlobalComErrFlag());
#ifdef DEBUG
        errorFlagActive = FALSE;
#endif
        
        /* only execute if safe state is not active SM60 */
        if(errorFlagActive != TRUE)
        {
          /* start meas if addressed & switch to PDCM */
          switch(currentNad)
          {
          case 1:
            meas_StartAdvancedMeasurement((Meas_eMeasurementConf_t)rcvData.AdvMeasurementExecute.Sensor1, (Meas_eMeasurementMode_t)rcvData.AdvMeasurementExecute.Mode, (Meas_eMeasurementProfile_t)rcvData.AdvMeasurementExecute.Profile);
            break;
          case 2:
            meas_StartAdvancedMeasurement((Meas_eMeasurementConf_t)rcvData.AdvMeasurementExecute.Sensor2, (Meas_eMeasurementMode_t)rcvData.AdvMeasurementExecute.Mode, (Meas_eMeasurementProfile_t)rcvData.AdvMeasurementExecute.Profile);
            break;
          case 3:
            meas_StartAdvancedMeasurement((Meas_eMeasurementConf_t)rcvData.AdvMeasurementExecute.Sensor3, (Meas_eMeasurementMode_t)rcvData.AdvMeasurementExecute.Mode, (Meas_eMeasurementProfile_t)rcvData.AdvMeasurementExecute.Profile);
            break;
          case 4:
            meas_StartAdvancedMeasurement((Meas_eMeasurementConf_t)rcvData.AdvMeasurementExecute.Sensor4, (Meas_eMeasurementMode_t)rcvData.AdvMeasurementExecute.Mode, (Meas_eMeasurementProfile_t)rcvData.AdvMeasurementExecute.Profile);
            break;
          case 5:
            meas_StartAdvancedMeasurement((Meas_eMeasurementConf_t)rcvData.AdvMeasurementExecute.Sensor5, (Meas_eMeasurementMode_t)rcvData.AdvMeasurementExecute.Mode, (Meas_eMeasurementProfile_t)rcvData.AdvMeasurementExecute.Profile);
            break;
          case 6:
            meas_StartAdvancedMeasurement((Meas_eMeasurementConf_t)rcvData.AdvMeasurementExecute.Sensor6, (Meas_eMeasurementMode_t)rcvData.AdvMeasurementExecute.Mode, (Meas_eMeasurementProfile_t)rcvData.AdvMeasurementExecute.Profile);
            break;
          default:
            /* Error: no valid current Nad?? */
            break;
          }
          /* check if a measurement has started and switch to pdcm if necessary */
          if (meas_eMeasConf_NONE != meas_GetMeasConf())
          {
            /* switch to PDCM */
            switch((Meas_eMeasurementMode_t)rcvData.AdvMeasurementExecute.Mode)
            {
            case meas_eMeasMode_APPLICATION:
              /* fall through */
            case meas_eMeasMode_APPLICATION2:
              loc_ChangeModeToPdcm(genericEnvData, DSI3_TYPE_MEAS_RESULT_APP_MODE);
              break;
            case meas_eMeasMode_LAB:
              /* fall through */
            case meas_eMeasMode_APPLAB:
              loc_ChangeModeToPdcm(genericEnvData, DSI3_TYPE_MEAS_RESULT_LAB_MODE);
              break;
            default:
              /* this case should be impossible */
              break;
            }
          }
          else
          {
            /* Nothing to do, Mode was ignore, so ignore.. */
          }
        }
        else
        {
          /* set measurement abort flag if safe state is active */
          loc_pApplRuntimeData->MeasCtrl->RuntimeData.MeasAbortFlag = TRUE;
        }    
      }
      else
      {
        /* no broadcast-> ignore */
      }
    }
    else
    {
      /* one module is busy -> dont execute cmd and return busy state */
    }

    /* refresh CRM application data */
    loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull = TRUE;
    loc_SetLastExecutedCrmCmd(dsi3Drv_eCRM_COMMAND_ID_MEASUREMENT_ADVANCED_EXECUTE);

    loc_pApplRuntimeData->DSI3Ctrl->SyncFlag = TRUE;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }

  /* No response necessary */
  return Dsi3BusIf_eCMDACT_IGNORE;
}

/* *************************************************************************//**
 * @brief
 * CRM: Stop a running Measurement
 * stop an ultrasonic measurement cycle
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      never
 *              Dsi3BusIf_eCMDACT_IGNORE        ever
 * ****************************************************************************/
Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_MeasStop (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer,
                                                                   Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad,
                                                                   Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* 1. if in CRM State -> Ignore */
  /* 2. if in PDCM State -> stop meas if addressed & switch to CRM */
  /* 3. if in Discovery State -> stop discovery mode & switch to CRM */

  /* Check Data */
  if ((NULL != genericEnvData) && (NULL != commandBuffer) && (NULL != loc_pApplRuntimeData))
  {
    loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull = FALSE;

    /* disable EEPROM access */
    Eeprom_Disable();

    /* prepare received Data */
    Dsi3_uCrmCommand_t rcvData;
    rcvData.rawData = commandBuffer->Fields;

    /* only execute if no module is busy */
    if(false == Eeprom_CheckIfBusy())
    {
      /* PDCM -> execute command */
      switch(currentNad)
      {
      case 1:
        if(DSI3_MEASSTOP_STOP == rcvData.MeasurementStop.Sensor1)
        {
          meas_AbortMeasurement();
        }
        else
        {
          /* no change in measurement */
        }
        break;
      case 2:
        if(DSI3_MEASSTOP_STOP == rcvData.MeasurementStop.Sensor2)
        {
          meas_AbortMeasurement();
        }
        else
        {
          /* no change in measurement */
        }
        break;
      case 3:
        if(DSI3_MEASSTOP_STOP == rcvData.MeasurementStop.Sensor3)
        {
          meas_AbortMeasurement();
        }
        else
        {
          /* no change in measurement */
        }
        break;
      case 4:
        if(DSI3_MEASSTOP_STOP == rcvData.MeasurementStop.Sensor4)
        {
          meas_AbortMeasurement();
        }
        else
        {
          /* no change in measurement */
        }
        break;
      case 5:
        if(DSI3_MEASSTOP_STOP == rcvData.MeasurementStop.Sensor5)
        {
          meas_AbortMeasurement();
        }
        else
        {
          /* no change in measurement */
        }
        break;
      case 6:
        if(DSI3_MEASSTOP_STOP == rcvData.MeasurementStop.Sensor6)
        {
          meas_AbortMeasurement();
        }
        else
        {
          /* no change in measurement */
        }
        break;
      default:
        /* Error: no valid current Nad */
        break;
      }
    }
    else
    {
      /* one module is busy -> dont execute cmd and return busy state */
    }

    /* refresh CRM application data */
    loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull = TRUE;
    loc_SetLastExecutedCrmCmd(dsi3Drv_eCRM_COMMAND_ID_MEASUREMENT_ADVANCED_EXECUTE);

    loc_pApplRuntimeData->DSI3Ctrl->SyncFlag = TRUE;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }

  /* Ignore */
  return Dsi3BusIf_eCMDACT_IGNORE;
}
/*
1. 函数首先验证输入指针的有效性，如果genericEnvData、commandBuffer 和 loc_pApplRuntimeData 都非空，则继续执行。
2. 禁用EEPROM访问以防止并发操作。3. 解析接收到的命令缓冲区内容到 rcvData 结构体中。4. 检查当前无任何模块处于繁忙状态，若无则执行下一步骤；否则，返回忙状态并不执行停止测量命令。
5. 根据当前节点地址（currentNad）判断哪个传感器应该响应命令：•如果命令要求停止特定传感器的测量（DSI3_MEASSTOP_STOP），则调用 meas_AbortMeasurement() 函数来停止相应传感器的测量过程。
•若命令不是要求停止测量，则保持当前测量状态不变。6. 在成功执行停止测量命令之后，更新应用运行时数据，标记上次执行成功的 CRM 命令类型为“测量停止”，并将同步标志位置为真。
7. 如果在开始函数执行时发现输入指针无效，则调用错误处理程序。
8. 不论命令是否执行，函数都返回 Dsi3BusIf_eCMDACT_IGNORE 表示不对该命令产生响应，这可能是因为处理动作已经由函数内部直接完成，或者由硬件直接响应，不需要通过总线返回确认消息。
总之，这个函数用于处理停止超声波测量请求，根据接收到的命令内容和当前系统状态做出相应操作，并更新相关的上下文数据和状态标志。
*/
/* **************************************************************************//**
 * @brief
 * CRM: Measurement configuration data access
 * transmit or receive measurement configuration data (in combination with a further <command> frame)
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 * 
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      if addressed directly
 *              Dsi3BusIf_eCMDACT_IGNORE        if addressed by wildcard
 * ****************************************************************************/
Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_MeasSettings (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer,
                                                                       Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad,
                                                                       Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* 1. if in CRM State -> execute command */
  /* 2. if in PDCM State -> stop meas & switch to CRM & execute command */
  /* 3. if in Discovery State -> stop discovery mode & switch to CRM */

  Dsi3BusIf_CmdIdAction_t retVal = Dsi3BusIf_eCMDACT_IGNORE;

  /* Check Data */
  if ((NULL != genericEnvData) && (NULL != commandBuffer) && (NULL != responseBuffer) && (NULL != loc_pApplRuntimeData))
  {
    loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull = FALSE;

    /* disable EEPROM access */
    Eeprom_Disable();

    /* prepare received Data */
    Dsi3_uCrmCommand_t rcvData;
    rcvData.rawData = commandBuffer->Fields;
    /* prepare answer buffer */
    Dsi3_sAnswerFrame_t* ansData = (Dsi3_sAnswerFrame_t*)responseBuffer;
    ansData->Status = DSI3_STATUSBITS_OK;


    /* only execute if no module is busy */
    if(false == Eeprom_CheckIfBusy())
    {
      /* Read or write operation */
      if(DSI3_MEASSETTINGS_READ == rcvData.MeasurementSettings.RW)
      {
        /* read operation */
        if(DSI3_NAD_BROADCAST == rcvData.MeasurementSettings.PhysicalAddress)
        {
          /* ignore on wildcard */
        }
        else
        {
          /* execute read */
          if(rcvData.MeasurementSettings.Address > DSI3_MEASSETTINGS_ADRMAX)
          {
            /* wrong address -> set status to error */
            ansData->Status = DSI3_STATUSBITS_ERROR;
          }
          else
          {
            /* correct address -> send data */
            /* divide Address by 2, to convert it from 8bit to 16bit addressing, which is needed for the data array access */
            rcvData.MeasurementSettings.Address = rcvData.MeasurementSettings.Address >> 1;
            /* read meas settings and send them back */
            ansData->Data1 = (loc_pApplRuntimeData->MeasCtrl->Parameters.halfwords[rcvData.MeasurementSettings.Address] & 0xFF00u) >> 8;
            ansData->Data2 = (loc_pApplRuntimeData->MeasCtrl->Parameters.halfwords[rcvData.MeasurementSettings.Address] & 0x00FFu)     ;
              /* set cmd executed successful flag & write back the address*/
              loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull = TRUE;
              loc_pApplRuntimeData->DSI3Ctrl->CrmExtCommandAddress = rcvData.MeasurementSettings.Address;
          }
        }
      }
      else
      {
        /* write operation */
        if(rcvData.MeasurementSettings.Address > DSI3_MEASSETTINGS_ADRMAX)
        {
          /* wrong address -> set status to error */
          ansData->Status = DSI3_STATUSBITS_ERROR;
        }
        else
        {
          /* correct address -> prepare response data*/
          ansData->Data1 = 0;
          ansData->Data2 = rcvData.MeasurementSettings.Address;
          /* divide Address by 2, to convert it from 8bit to 16bit addressing, which is needed for the data array access */
          rcvData.MeasurementSettings.Address = rcvData.MeasurementSettings.Address >> 1;
          /* set cmd executed successful flag & write back the address*/
          loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull = TRUE;
          loc_pApplRuntimeData->DSI3Ctrl->CrmExtCommandAddress = rcvData.MeasurementSettings.Address;
        }
      }
    }
    else
    {
      /* one module is busy -> dont execute cmd and return busy state */
      ansData->Status = DSI3_STATUSBITS_BUSY;
    }
    /* prepare response if no broadcast */
    if(DSI3_NAD_BROADCAST != rcvData.Default.PhysicalAddress)
    {
      ansData->ComErr = err_GetGlobalComErrFlag();
      ansData->HwErr = err_GetGlobalHwErrFlag();
      ansData->PhysicalAddress = currentNad;
      if(DSI3_STATUSBITS_ERROR == ansData->Status)
      {
        /* an error occured -> process it */
        ansData->Data1 = 0;
        ansData->Data2 = 0;
      }
      else
      {
        /* everything ok */
      }
      retVal = Dsi3BusIf_eCMDACT_RESPONSE;
    }
    else
    {
      retVal = Dsi3BusIf_eCMDACT_IGNORE;
    }

    /* refresh CRM application data */
    loc_SetLastExecutedCrmCmd(dsi3Drv_eCRM_COMMAND_ID_MEASUREMENT_SETTINGS);

    loc_pApplRuntimeData->DSI3Ctrl->SyncFlag = TRUE;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }

  return retVal;
}
/*
1. 检查输入参数的有效性。如果所有参数均有效，则继续执行。2. 禁用EEPROM访问以避免冲突。3. 解析接收到的命令缓冲区数据到rcvData结构体，并准备响应缓冲区ansData。
4. 如果没有任何模块处于繁忙状态，则根据命令的读/写指示进行相应的操作：•读取操作：检查物理地址是否合法，如果合法则从loc_pApplRuntimeData中读取测量设置，并将其放入响应缓冲区中。
•写入操作：同样检查物理地址是否合法，如果合法则记录写入地址，但并未立即执行写入操作，因为这里仅是处理命令阶段，真正的写入可能会在后续步骤中执行。
5. 如果模块繁忙，则设置响应状态为“BUSY”。6. 如果命令不是发送给广播地址，则进一步填充响应缓冲区信息（如错误标志、物理地址等），并返回Dsi3BusIf_eCMDACT_RESPONSE以便于通过总线发送响应。
7. 根据命令执行结果更新CRM应用数据，记录最后一次执行的CRM命令类型为测量设置命令，并置位同步标志。8. 如果在函数执行前发现输入指针无效，则调用错误处理程序。
9. 函数最后返回一个指示动作结果的枚举值，可能是Dsi3BusIf_eCMDACT_IGNORE（忽略命令，通常发生在广播地址下的命令）或Dsi3BusIf_eCMDACT_RESPONSE（需要发送响应给命令发送方）。
*/
/* **************************************************************************//**
 * @brief
 * CRM: Measurement configuration data access
 * further "command" frame after "Measurement configuration data access"
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      if addressed directly
 *              Dsi3BusIf_eCMDACT_IGNORE        if addressed by wildcard
 * ****************************************************************************/
Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_MeasSettingsExt (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer,
                                                                          Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad,
                                                                          Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* 1. if in CRM State -> execute command if CMD=0x8 was received before */
  /* 2. if in PDCM State -> stop meas & switch to CRM */
  /* 3. if in Discovery State -> stop discovery mode & switch to CRM */

  Dsi3BusIf_CmdIdAction_t retVal = Dsi3BusIf_eCMDACT_IGNORE;

  /* Check Data */
  if ((NULL != genericEnvData) && (NULL != commandBuffer) && (NULL != responseBuffer) && (NULL != loc_pApplRuntimeData))
  {
    /* disable EEPROM access */
    Eeprom_Disable();

    /* prepare received Data */
    Dsi3_uCrmCommand_t rcvData;
    rcvData.rawData = commandBuffer->Fields;
    /* prepare answer buffer */
    Dsi3_sAnswerFrame_t* ansData = (Dsi3_sAnswerFrame_t*)responseBuffer;
    ansData->Status = DSI3_STATUSBITS_OK;

    /* only execute if no module is busy */
    if(false == Eeprom_CheckIfBusy())
    {
      /* only execute if last cmd was measurement settings & last cmd was executed successfully */
      if((dsi3Drv_eCRM_COMMAND_ID_MEASUREMENT_SETTINGS == loc_pApplRuntimeData->DSI3Ctrl->CrmLastCommand) && (TRUE == loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull))
      {
        /* store received Data in RAM */
        loc_pApplRuntimeData->MeasCtrl->Parameters.halfwords[loc_pApplRuntimeData->DSI3Ctrl->CrmExtCommandAddress] = (((uint16_t)rcvData.Default.Data1) << 8) | (uint16_t)rcvData.Default.Data2;
        /* trigger crc calculation over ram */
        mem_TriggerCrcCalculationOverRam();
        /* prepare data for response */
        ansData->Data1 = rcvData.Default.Data1;
        ansData->Data2 = rcvData.Default.Data2;
      }
      else
      {
        /* last command was not 0xB -> dont execute */
        ansData->Status = DSI3_STATUSBITS_ERROR;
      }
    }
    else
    {
      /* one module is busy -> dont execute cmd and return busy state */
      ansData->Status = DSI3_STATUSBITS_BUSY;
    }
    /* prepare response of no broadcast */
    if(DSI3_NAD_BROADCAST != rcvData.Default.PhysicalAddress)
    {
      ansData->ComErr = err_GetGlobalComErrFlag();
      ansData->HwErr = err_GetGlobalHwErrFlag();
      ansData->PhysicalAddress = currentNad;
      if(DSI3_STATUSBITS_ERROR == ansData->Status)
      {
        /* an error occured -> process it */
        ansData->Data1 = 0;
        ansData->Data2 = 0;
      }
      else
      {
        /* everything ok */
      }
      retVal = Dsi3BusIf_eCMDACT_RESPONSE;
    }
    else
    {
      retVal = Dsi3BusIf_eCMDACT_IGNORE;
    }

    /* refresh CRM application data */
    loc_SetLastExecutedCrmCmd(dsi3Drv_eCRM_COMMAND_ID_MEASUREMENT_SETTINGS_EXTENDED);

    loc_pApplRuntimeData->DSI3Ctrl->SyncFlag = TRUE;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }

  return retVal;
}
/*
1. 函数首先检查输入指针的有效性。如果所有参数有效，则继续执行。2. 禁用EEPROM访问。3. 解析接收到的命令缓冲区数据到rcvData结构体，并准备响应缓冲区ansData，初始化其状态为正常（DSI3_STATUSBITS_OK）。
4. 当模块不处于繁忙状态时，检查最后一个执行的命令是否为“measurement settings”命令并且执行成功。如果是，则将接收到的数据存储到RAM中的测量控制参数数组，并触发RAM上的CRC校验计算。
同时，将接收到的数据填入响应缓冲区。5. 如果不满足上述条件，则设置响应状态为错误（DSI3_STATUSBITS_ERROR）。6. 如果模块处于繁忙状态，则设置响应状态为繁忙（DSI3_STATUSBITS_BUSY）。
7. 根据命令是否发送给特定地址而非广播地址，进一步填充响应缓冲区信息（错误标志、物理地址等），并根据响应状态决定返回Dsi3BusIf_eCMDACT_RESPONSE还是Dsi3BusIf_eCMDACT_IGNORE。
8. 更新CRM应用数据，记录最后一次执行的CRM命令类型为测量配置数据访问扩展命令，并置位同步标志。9. 如果在函数执行前发现输入指针无效，则调用错误处理程序。
总结：此函数主要用于处理测量配置数据的写入操作，确保在正确执行前序命令且模块未处于繁忙状态的情况下，将接收到的数据存储至RAM，并触发必要的CRC校验。如果满足条件，函数将构建适当的响应并通过总线发送回去。
*/
/* **************************************************************************//**
 * @brief
 * CRM: EEPROM access
 * enable EEPROM access and EEPROM copy operations.
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      if addressed directly
 *              Dsi3BusIf_eCMDACT_IGNORE        if addressed by wildcard
 * ****************************************************************************/
Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_EEPROMAccess (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer,
                                                                Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad,
                                                                Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* 1. if in CRM State -> execute command */
  /* 2. if in PDCM State -> stop meas & switch to CRM & execute command */
  /* 3. if in Discovery State -> stop discovery mode & switch to CRM */

  Dsi3BusIf_CmdIdAction_t retVal = Dsi3BusIf_eCMDACT_IGNORE;

  /* Check Data */
  if ((NULL != genericEnvData) && (NULL != commandBuffer) && (NULL != responseBuffer) && (NULL != loc_pApplRuntimeData))
  {
    loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull = FALSE;

    /* prepare received Data */
    Dsi3_uCrmCommand_t rcvData;
    rcvData.rawData = commandBuffer->Fields;
    /* prepare answer buffer */
    Dsi3_sAnswerFrame_t* ansData = (Dsi3_sAnswerFrame_t*)responseBuffer;
    ansData->Status = DSI3_STATUSBITS_OK;
    ansData->Data1 = rcvData.EepromAccess.Operation;
    ansData->Data2 = rcvData.EepromAccess.Password;
    /* only execute if no module is busy */
    if(false == Eeprom_CheckIfBusy())
    {
      switch(Eeprom_SetOperation((Eeprom_eAction_t)rcvData.EepromAccess.Operation, rcvData.EepromAccess.Password))
      {
      case EEPROM_ERR_WRONG_PW:
        err_SetComErrorFlag(ERR_PASSWORD_WRONG);
        ansData->Status = DSI3_STATUSBITS_ERROR;
        break;
      case EEPROM_ERR_UNKNOWN_ERR:
        ansData->Status = DSI3_STATUSBITS_ERROR;
        break;
      case EEPROM_ERR_BUSY:
        ansData->Status = DSI3_STATUSBITS_BUSY;
        break;
      default:
        /* everything ok -> nothing to do here */
        break;
      }
    }
    else
    {
      /* one module is busy -> dont execute cmd and return busy state */
      ansData->Status = DSI3_STATUSBITS_BUSY;
    }
    /* prepare response of no broadcast */
    if(DSI3_NAD_BROADCAST != currentNad)
    {
      ansData->ComErr = err_GetGlobalComErrFlag();
      ansData->HwErr = err_GetGlobalHwErrFlag();
      ansData->PhysicalAddress = currentNad;
      loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull = TRUE;
      retVal = Dsi3BusIf_eCMDACT_RESPONSE;
    }
    else
    {
      /* broadcast -> don't answer */
    }

    /* refresh CRM application data */
    loc_SetLastExecutedCrmCmd(dsi3Drv_eCRM_COMMAND_ID_EEPROM_ACCESS);

    loc_pApplRuntimeData->DSI3Ctrl->SyncFlag = TRUE;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }

  return retVal;
}

/*
函数首先检查输入参数的有效性，如果全部有效，则继续执行。接下来，它将接收到的命令数据解包并准备好响应缓冲区，初始状态设为正常。
当模块未处于繁忙状态时，函数根据接收到的EEPROM操作类型和密码调用Eeprom_SetOperation函数。
根据Eeprom_SetOperation的返回结果，更新响应缓冲区的状态字段：•如果密码错误，则设置通信错误标志并返回错误状态；•如果出现未知错误，也返回错误状态；
•如果EEPROM正在忙，则返回忙状态；•其他情况下，表示一切正常，无需额外操作。如果模块正忙，则响应状态被设置为“busy”。
根据接收到的命令是否指向特定地址（而不是广播地址），函数进一步填充响应缓冲区的其他字段（如通信错误标志、硬件错误标志和物理地址），
并根据响应状态决定返回Dsi3BusIf_eCMDACT_RESPONSE还是Dsi3BusIf_eCMDACT_IGNORE。
最后，函数更新CRM应用数据，记录最近执行的CRM命令类型为EEPROM访问，并设置同步标志为TRUE。如果在执行函数前发现输入参数无效，则调用错误处理程序。
*/

/* **************************************************************************//**
 * @brief
 * CRM: IC register access
 * transmit or receive IC register data (in combination with a further <command> frame)
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      if addressed directly
 *              Dsi3BusIf_eCMDACT_IGNORE        if addressed by wildcard
 * ****************************************************************************/
Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_RegisterAccess (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer,
                                                                  Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad,
                                                                  Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* 1. if in CRM State -> execute command */
  /* 2. if in PDCM State -> stop meas & switch to CRM & execute command */
  /* 3. if in Discovery State -> stop discovery mode & switch to CRM */

  Dsi3BusIf_CmdIdAction_t retVal = Dsi3BusIf_eCMDACT_IGNORE;

  /* Check Data */
  if ((NULL != genericEnvData) && (NULL != commandBuffer) && (NULL != responseBuffer) && (NULL != loc_pApplRuntimeData))
  {
    loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull = FALSE;

    /* disable EEPROM access */
    Eeprom_Disable();

    /* prepare received Data */
    Dsi3_uCrmCommand_t rcvData;
    rcvData.rawData = commandBuffer->Fields;
    /* prepare answer buffer */
    Dsi3_sAnswerFrame_t* ansData = (Dsi3_sAnswerFrame_t*)responseBuffer;
    ansData->Status = DSI3_STATUSBITS_OK;

    /* only execute if no module is busy */
    if(false == Eeprom_CheckIfBusy())
    {
      /* only execute, if address is in valid range */
      if(DSI3_IC_REGACCESS_MODNUM_MAX >= rcvData.RegisterAccess.ModAddr)
      {
        /* is this a read or write operation? */
        if(DSI3_IC_REGACCESS_READ == rcvData.RegisterAccess.RW)
        {
          /* read command */
          if(DSI3_NAD_BROADCAST == rcvData.RegisterAccess.PhysicalAddress)
          {
            /* broadcast -> ignore */
          }
          else
          {
            /* set last Address bit to zero, to prevent 8 bit aligned register access */
            rcvData.RegisterAccess.Address = rcvData.RegisterAccess.Address & (~0x0001u);
            /* no broadcast -> process cmd -> read data from storage and send them */
            loc_pApplRuntimeData->DSI3Ctrl->CrmExtCommandAddress = loc_IcRegAccRegMapping[rcvData.RegisterAccess.ModAddr] + rcvData.RegisterAccess.Address;
            /* read data from memory */
            uint16_t* pDataAtAddr = (uint16_t*)loc_pApplRuntimeData->DSI3Ctrl->CrmExtCommandAddress;
            ansData->Data1 = (*pDataAtAddr & 0xFF00u) >> 8;
            ansData->Data2 = *pDataAtAddr & 0x00FFu;
            /* set cmd executed successful flag */
            loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull = TRUE;
          }
        }
        else
        {
          /* execute write command */
          /* prepare answer */
          ansData->Data1 = rcvData.RegisterAccess.ModAddr;
          ansData->Data2 = rcvData.RegisterAccess.Address;
          /* set last Address bit to zero, to prevent 8 bit aligned register access */
          rcvData.RegisterAccess.Address = rcvData.RegisterAccess.Address & (~0x0001u);
          loc_pApplRuntimeData->DSI3Ctrl->CrmExtCommandAddress = loc_IcRegAccRegMapping[rcvData.RegisterAccess.ModAddr] + rcvData.RegisterAccess.Address;
          /* set cmd executed successful flag */
          loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull = TRUE;
        }
      }
      else
      {
        /* Base address not in valid range -> set answer to zero */
        ansData->Status = DSI3_STATUSBITS_ERROR;
      }
    }
    else
    {
      /* one module is busy -> dont execute cmd and return busy state */
      ansData->Status = DSI3_STATUSBITS_BUSY;
    }
    /* prepare response of no broadcast */
    if(DSI3_NAD_BROADCAST != rcvData.Default.PhysicalAddress)
    {
      ansData->ComErr = err_GetGlobalComErrFlag();
      ansData->HwErr = err_GetGlobalHwErrFlag();
      ansData->PhysicalAddress = currentNad;
      if(DSI3_STATUSBITS_ERROR == ansData->Status)
      {
        /* an error occured -> process it */
        ansData->Data1 = 0;
        ansData->Data2 = 0;
      }
      else
      {
        /* everything ok */
      }
      retVal = Dsi3BusIf_eCMDACT_RESPONSE;
    }
    else
    {
      retVal = Dsi3BusIf_eCMDACT_IGNORE;
    }


    /* refresh CRM application data */
    loc_SetLastExecutedCrmCmd(dsi3Drv_eCRM_COMMAND_ID_REGISTER_ACCESS);

    loc_pApplRuntimeData->DSI3Ctrl->SyncFlag = TRUE;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }

  return retVal;
}
/*
首先，函数检查输入参数的有效性，包括环境数据、命令缓冲区、响应缓冲区以及应用运行时数据。若所有参数有效，则继续执行。2. 禁止EEPROM访问，确保当前操作只针对寄存器而不影响EEPROM。
3. 解析接收到的命令缓冲区内容到rcvData结构体，并初始化响应缓冲区ansData，其中状态字段设置为正常（DSI3_STATUSBITS_OK）。
4. 检查是否有模块正在执行操作。如果没有模块处于繁忙状态，则进入下一步：a. 判断命令中的模块地址是否在有效范围内，如果在有效范围内，则根据命令的读写指示执行对应操作：
•读取操作：•如果命令不是广播地址，则将目标地址调整为16位对齐，并通过映射表找到实际内存地址。•从内存中读取寄存器数据，将高低字节分别填入响应缓冲区，并设置命令执行成功的标志。
•写入操作：•准备响应数据，将模块地址和目标地址填入响应缓冲区的Data1和Data2字段。•调整目标地址为16位对齐，并通过映射表找到实际内存地址。
•设置命令执行成功的标志，但请注意，此处代码并没有实际执行写入操作，只是完成了命令处理的准备工作。b. 如果模块地址不在有效范围内，则将响应状态设置为错误（DSI3_STATUSBITS_ERROR）。
c. 如果有模块处于繁忙状态，则将响应状态设置为繁忙（DSI3_STATUSBITS_BUSY），表明无法执行当前命令。5. 根据命令是否为广播地址来填充响应缓冲区的其他信息，例如通信错误标志、硬件错误标志和物理地址。
如果发生错误，将响应数据的Data1和Data2字段置零，否则保留原始数据。当命令不是广播地址时，返回Dsi3BusIf_eCMDACT_RESPONSE；如果是广播地址，则返回Dsi3BusIf_eCMDACT_IGNORE。
6. 最后，无论命令执行成功与否，函数都会更新CRM应用数据，记录最近执行的CRM命令类型为寄存器访问，并设置同步标志为TRUE。如果在执行函数前发现输入参数无效，则调用错误处理程序。
整个函数的核心功能就是处理对IC模块寄存器的读写请求，确保正确执行命令并反馈执行结果。在执行过程中，还涉及到地址校验、状态管理以及错误处理等多个环节。
*/
/* **************************************************************************//**
 * @brief
 * CRM: IC register access
 * further "command" frame after "IC register access"
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      if addressed directly
 *              Dsi3BusIf_eCMDACT_IGNORE        if addressed by wildcard
 * ****************************************************************************/
Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_RegisterAccessExt (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer,
                                                                     Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad,
                                                                     Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* 1. if in CRM State -> execute command if CMD = 0xB was received before */
  /* 2. if in PDCM State -> stop meas & switch to CRM */
  /* 3. if in Discovery State -> stop discovery mode & switch to CRM */

  Dsi3BusIf_CmdIdAction_t retVal = Dsi3BusIf_eCMDACT_IGNORE;

  /* Check Data */
  if ((NULL != genericEnvData) && (NULL != commandBuffer) && (NULL != responseBuffer) && (NULL != loc_pApplRuntimeData))
  {
    /* disable EEPROM access */
    Eeprom_Disable();

    /* prepare received Data */
    Dsi3_uCrmCommand_t rcvData;
    rcvData.rawData = commandBuffer->Fields;
    /* prepare answer buffer */
    Dsi3_sAnswerFrame_t* ansData = (Dsi3_sAnswerFrame_t*)responseBuffer;
    ansData->Status = DSI3_STATUSBITS_OK;

    /* only execute if last cmd was register access & last cmd was executed successfully */
    if((dsi3Drv_eCRM_COMMAND_ID_REGISTER_ACCESS == loc_pApplRuntimeData->DSI3Ctrl->CrmLastCommand) && (TRUE == loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull))
    {
      /* only execute if no module is busy */
    if(false == Eeprom_CheckIfBusy())
      {
        /* execute command */
        uint16_t* pData = (uint16_t*)loc_pApplRuntimeData->DSI3Ctrl->CrmExtCommandAddress;
        *pData        = (((uint16_t)rcvData.Default.Data1) << 8) | ((uint16_t)rcvData.Default.Data2);
        /* prepare answer */
        ansData->Data1 = rcvData.Default.Data1;
        ansData->Data2 = rcvData.Default.Data2;
      }
      else
      {
        /* one module is busy -> dont execute cmd and return busy state */
        ansData->Status = DSI3_STATUSBITS_BUSY;
      }
    }
    else
    {
      /* last command was not 0xB -> dont execute */
      ansData->Status = DSI3_STATUSBITS_ERROR;
    }
    /* prepare response if no broadcast */
    if(DSI3_NAD_BROADCAST != rcvData.Default.PhysicalAddress)
    {
      ansData->ComErr = err_GetGlobalComErrFlag();
      ansData->HwErr = err_GetGlobalHwErrFlag();
      ansData->PhysicalAddress = currentNad;
      if(DSI3_STATUSBITS_ERROR == ansData->Status)
      {
        /* an error occured -> process it */
        ansData->Data1 = 0;
        ansData->Data2 = 0;
      }
      else
      {
        /* everything ok */
      }
      retVal = Dsi3BusIf_eCMDACT_RESPONSE;
    }
    else
    {
      retVal = Dsi3BusIf_eCMDACT_IGNORE;
    }

    /* refresh CRM application data */
    loc_SetLastExecutedCrmCmd(dsi3Drv_eCRM_COMMAND_ID_REGISTER_ACCESS_EXTENDED);

    loc_pApplRuntimeData->DSI3Ctrl->SyncFlag = TRUE;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }

  return retVal;
}
/*
Dsi3_CrmCmdHandler_RegisterAccessExt 函数是一个用于处理IC寄存器访问扩展命令的回调函数。
这个函数是在收到“IC寄存器访问”命令之后的下一个命令帧时执行的，它的主要目的是根据之前执行的命令及执行结果，安全地对IC寄存器进行读写操作。
1. 函数首先检查输入参数的有效性。只有当所有参数都非空时才继续执行。2. 禁用EEPROM访问以避免与寄存器操作冲突。
3. 解析接收到的命令缓冲区数据到rcvData结构体，并准备响应缓冲区ansData，初始化其状态为正常（DSI3_STATUSBITS_OK）。
4. 只有在满足以下两个条件时才会执行写入操作：•上一次执行的命令是“IC寄存器访问”命令（dsi3Drv_eCRM_COMMAND_ID_REGISTER_ACCESS）。
•上次命令执行成功 (loc_pApplRuntimeData->DSI3Ctrl->CrmCxtCommandLastSuccessfull 为真)。
5. 如果没有模块处于繁忙状态（false == Eeprom_CheckIfBusy()），则根据已保存的地址(CrmExtCommandAddress)，从接收到的命令数据中提取出要写入寄存器的数据，并完成实际的写入操作。
6. 如果模块处于繁忙状态，将响应状态设置为“BUSY”，否则，如果上一条命令不是“IC寄存器访问”，则将响应状态设置为“ERROR”。
7. 根据命令是否是直接发送到特定地址（非广播地址），填充响应缓冲区的其他字段，如通信错误标志、硬件错误标志、物理地址等。如果响应状态为错误，将响应数据的Data1和Data2字段清零，否则保持不变。
如果不是广播地址，则返回 Dsi3BusIf_eCMDACT_RESPONSE，如果是广播地址，则返回 Dsi3BusIf_eCMDACT_IGNORE。
8. 更新CRM应用数据，记录最后执行的CRM命令类型为“IC寄存器访问扩展”，并将同步标志设置为TRUE。9. 若在函数执行前发现输入参数无效，则调用错误处理程序。
总之，这个函数主要是处理对IC寄存器的写入操作，并确保在此操作前后设备状态正确，同时也保证了命令执行的安全性和一致性。如果执行失败或无法执行，会通过响应状态和相关标志给出反馈。*/
/* **************************************************************************//**
 * @brief
 * CRM: Read status in CRM
 * transmit IC Status information in CRM (results of self-test)
 *
 * SM41: Forward Errors (Part 1 of 2)
 * (for details see SafetyManual)
 * 
 * SM106: Error management (Part 1 of 2)
 * (for details see SafetyManual)
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      if addressed directly
 *              Dsi3BusIf_eCMDACT_IGNORE        if addressed by wildcard
 * ****************************************************************************/
Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_ReadStatInCRM (Dsi3BusIf_pGenericEnvData_t   genericEnvData,    const Dsi3Bus_CrmCommand_t* commandBuffer,
                                                          Dsi3Bus_CrmResponse_t*        responseBuffer,    const Dsi3BusIf_SlaveID_t   currentNad,
                                                          Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* 1. if in CRM State -> execute command */
  /* 2. if in PDCM State -> stop meas & switch to CRM & execute command */
  /* 3. if in Discovery State -> stop discovery mode & switch to CRM */

  Dsi3BusIf_CmdIdAction_t retVal = Dsi3BusIf_eCMDACT_IGNORE;

  /* Check Data */
  if ((NULL != genericEnvData) && (NULL != commandBuffer) && (NULL != responseBuffer) && (NULL != loc_pApplRuntimeData))
  {
    /* disable EEPROM access */
    Eeprom_Disable();

    /* prepare received Data */
    Dsi3_uCrmCommand_t rcvData;
    rcvData.rawData = commandBuffer->Fields;
    /* prepare answer buffer */
    Dsi3_sAnswerFrame_t* ansData = (Dsi3_sAnswerFrame_t*)responseBuffer;
    ansData->Status = DSI3_STATUSBITS_OK;

    /* is this a broadcast command? */
    if(DSI3_NAD_BROADCAST == rcvData.ReadStatusInCrm.PhysicalAddress)
    {
      /* broadcast -> ignore */
    }
    else
    {
      /* only execute if no module is busy */
    if(false == Eeprom_CheckIfBusy())
      {
        if(NULL != ansData)
        {
          switch (rcvData.ReadStatusInCrm.Address) /* SMA52417-118 */
          {
          case 0u:  /* PUDIN_H */
            ansData->Data1 = (PUDIN_H_IN_EEPROM & 0xFF00u) >> 8u;
            ansData->Data2 =  PUDIN_H_IN_EEPROM & 0x00FFu;
            break;
          case 1u:  /* PUDIN_L */
            ansData->Data1 = (PUDIN_L_IN_EEPROM & 0xFF00u) >> 8u;
            ansData->Data2 =  PUDIN_L_IN_EEPROM & 0x00FFu;
            break;
          case 2u: /* HWErr status 1 */
            ansData->Data1 = ((err_GetHwErrorFlag1().rawData) & 0xFF00u) >> 8u;
            ansData->Data2 =  (err_GetHwErrorFlag1().rawData) & 0x00FFu;
            break;
          case 3u: /* HWErr status 2 */
            ansData->Data1 = ((err_GetHwErrorFlag2().rawData) & 0xFF00u) >> 8u;
            ansData->Data2 =  (err_GetHwErrorFlag2().rawData) & 0x00FFu;
            break;
          case 4u: /* CommErr status */
            ansData->Data1 = ((err_GetComErrorFlag().rawData) & 0xFF00u) >> 8u;
            ansData->Data2 =  (err_GetComErrorFlag().rawData) & 0x00FFu;
            break;
          case 20u: /* DIS_CLK_1US */
            ansData->Data1 = (DSI3_CLK_1US & 0xFF00u) >> 8u;
            ansData->Data2 =  DSI3_CLK_1US & 0x00FFu;
            break;
          case 21u: /* DSI_SYNC_CONT */
            ansData->Data1 = (DSI3_SYNC_CNT & 0xFF00u) >> 8u;
            ansData->Data2 =  DSI3_SYNC_CNT & 0x00FFu;
            break;
          case 22u: /* PDCM interval */
            ansData->Data1 = (DSI3_TIMER_COMPARE_B & 0xFF00u) >> 8u;
            ansData->Data2 =  DSI3_TIMER_COMPARE_B & 0x00FFu;
            break;
          case 30u: /* HW revision */
            ansData->Data1 = (HardwareVersionNumber & 0xFF00u) >> 8u;
            ansData->Data2 = HardwareVersionNumber & 0x00FFu;
            break;
          case 31u: /* FW revision */
            ansData->Data1 = (FirmwareVersionNumber & 0xFF00u) >> 8u;
            ansData->Data2 = FirmwareVersionNumber & 0x00FFu;
            break;
          default:
            ansData->Data1 = (0x00u & 0xFF00u) >> 8u;
            ansData->Data2 = 0x00u & 0x00FFu;
            break;
          }
        }
        else
        {
          /* do nothing */
        }
      }
      else
      {
        /* one module is busy -> dont execute cmd and return busy state */
        ansData->Status = DSI3_STATUSBITS_BUSY;
      }

      /* prepare response of no broadcast */
      if(DSI3_NAD_BROADCAST != rcvData.Default.PhysicalAddress)
      {
        ansData->ComErr = err_GetGlobalComErrFlag();
        ansData->HwErr = err_GetGlobalHwErrFlag();
        ansData->PhysicalAddress = currentNad;
        if(DSI3_STATUSBITS_ERROR == ansData->Status)
        {
          /* an error occured -> process it */
          ansData->Data1 = 0;
          ansData->Data2 = 0;
        }
        else
        {
          /* everything ok */
        }
        retVal = Dsi3BusIf_eCMDACT_RESPONSE;
      }
      else
      {
        retVal = Dsi3BusIf_eCMDACT_IGNORE;
      }
    }

    /* refresh CRM application data */
    loc_SetLastExecutedCrmCmd(dsi3Drv_eCRM_COMMAND_ID_READ_STATUS_IN_CRM);

    loc_pApplRuntimeData->DSI3Ctrl->SyncFlag = TRUE;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }

  return retVal;
}
/*
Dsi3_CrmCmdHandler_ReadStatInCRM 函数是一个处理读取CRM内部状态的回调函数，它通过DSI3总线接口响应来自主机的读取状态请求。
以下是该函数的主要功能概述：1. 首先检查输入参数的有效性，确认数据结构指针不为空。2. 禁用EEPROM访问以确保不会影响到当前状态读取操作。
3. 将接收到的命令缓冲区解析为rcvData结构，并初始化响应缓冲区ansData，其状态值设置为正常（DSI3_STATUSBITS_OK）。
4. 对于广播命令（即目标地址为DSI3_NAD_BROADCAST），函数选择忽略该命令。5. 在模块未处于繁忙状态时，根据接收到的地址参数读取相应的状态信息，并将其填入响应缓冲区的Data1和Data2字段。
这些状态信息包括但不限于：•输入端口状态（PUDIN_H 和 PUDIN_L）•硬件错误状态•通信错误状态•内部计数器和定时器值•硬件和固件版本号6. 如果模块处于繁忙状态，响应状态会被设置为“BUSY”。
7. 对于非广播地址的命令，函数还会填充响应中的通信错误标志、硬件错误标志、物理地址等信息，并根据响应状态判断是否返回Dsi3BusIf_eCMDACT_RESPONSE。
8. 最后，函数更新CRM应用数据，记录最后执行的CRM命令类型为“读取CRM内部状态”，并将同步标志设置为TRUE。9. 如果在函数执行前发现输入参数无效，则调用错误处理程序。
总体来说，这个函数的作用是响应来自主机对设备内部状态的读取请求，收集并打包所需的状态信息，通过DSI3总线接口返回给主机。在处理过程中，充分考虑了模块状态、错误检测以及不同状态信息的具体获取方式。
*/
/* **************************************************************************//**
 * @brief
 * CRM: Read Status in PDCM
 * transmit IC status information in PDCM. This allows a much higher data rate to transfer all data from the sensor (results of self-test)
 *
 * SM41: Forward Errors (Part 2 of 2)
 * (for details see SafetyManual)
 *
 * SM106: Error management (Part 2 of 2)
 * (for details see SafetyManual)
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      if addressed directly
 *              Dsi3BusIf_eCMDACT_IGNORE        if addressed by wildcard
 * ****************************************************************************/
Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_ReadStatInPDCM (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer,
                                                                    Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad,
                                                                    Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* 1. if in CRM State -> execute command & switch to PDCM */
  /* 2. if in PDCM State -> stop meas & switch to CRM & execute command */
  /* 3. if in Discovery State -> stop discovery mode & switch to CRM */

  Dsi3BusIf_CmdIdAction_t retVal = Dsi3BusIf_eCMDACT_IGNORE;

  /* Check Data */
  if ((NULL != genericEnvData) && (NULL != commandBuffer) && (NULL != responseBuffer) && (NULL != loc_pApplRuntimeData))
  {
    /* disable EEPROM access */
    Eeprom_Disable();

    /* prepare received Data */
    Dsi3_uCrmCommand_t rcvData;
    rcvData.rawData = commandBuffer->Fields;
    /* prepare answer buffer */
    Dsi3_sAnswerFrame_t* ansData = (Dsi3_sAnswerFrame_t*)responseBuffer;
    ansData->Status = DSI3_STATUSBITS_OK;

    /* only execute if no module is busy */
    if(false == Eeprom_CheckIfBusy())
    {
      /* is this a broadcast command? */
      if(DSI3_NAD_BROADCAST == rcvData.ReadStatusInPdcm.PhysicalAddress)
      {
        /* broadcast -> nothing to do here */
      }
      else
      {
        /* no broadcast -> execute cmd -> read IC status */
        ansData->Data1 = rcvData.Default.Data1;
        ansData->Data2 = rcvData.Default.Data2;

        /* prepare response */
        if(DSI3_NAD_BROADCAST != rcvData.Default.PhysicalAddress)
        {
          ansData->ComErr = err_GetGlobalComErrFlag();
          ansData->HwErr = err_GetGlobalHwErrFlag();
          ansData->PhysicalAddress = currentNad;
          if(DSI3_STATUSBITS_ERROR == ansData->Status)
          {
            /* an error occured -> process it */
            ansData->Data1 = 0;
            ansData->Data2 = 0;
          }
          else
          {
            /* everything ok */
          }
          retVal = Dsi3BusIf_eCMDACT_RESPONSE;
        }
        else
        {
          retVal = Dsi3BusIf_eCMDACT_IGNORE;
        }
      }

      /* save requested state */
      /* switch to PDCM */
      loc_ChangeModeToPdcm(genericEnvData, DSI3_TYPE_SELF_TEST);
    }
    else
    {
      /* one module is busy -> dont execute cmd and return busy state */
    }

    /* refresh CRM application data */
    loc_SetLastExecutedCrmCmd(dsi3Drv_eCRM_COMMAND_ID_READ_STATUS_IN_PDCM);

    loc_pApplRuntimeData->DSI3Ctrl->SyncFlag = TRUE;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }
  return retVal;
}
/*
Dsi3_CrmCmdHandler_ReadStatInPDCM 函数负责处理读取PDCM状态下IC状态信息的命令，主要用于在PDCM模式下以更高的数据速率传输来自传感器的所有数据，如自检结果等。
该函数遵循如下逻辑：1. 首先检查输入参数有效性，确保不为空指针。2. 禁用EEPROM访问，确保不影响PDCM状态读取。
3. 解析接收到的命令缓冲区数据到rcvData结构体，并初始化响应缓冲区ansData，其状态值设置为正常（DSI3_STATUSBITS_OK）。
4. 当模块未处于繁忙状态时：•如果接收到的是广播命令，不做任何处理。•否则，执行读取IC状态操作，将接收到的默认数据填入响应缓冲区的Data1和Data2字段。
•准备非广播命令的响应，填充通信错误标志、硬件错误标志、物理地址等信息，并根据响应状态判断是否返回Dsi3BusIf_eCMDACT_RESPONSE。
5. 保存请求的状态，并切换至PDCM模式，具体为执行自检（DSI3_TYPE_SELF_TEST）。6. 如果模块处于繁忙状态，则返回忙碌状态。7. 更新CRM应用数据，记录最后执行的CRM命令类型为“读取PDCM状态”。
8. 将同步标志设置为TRUE。9. 若在函数执行前发现输入参数无效，则调用错误处理程序。总之，该函数实现了从PDCM模式下快速读取IC状态信息，并将这些信息通过DSI3总线接口返回给主机。
同时，支持单个模块状态读取和全局广播状态读取两种场景，并且在必要时能够切换至PDCM模式进行更高效率的数据传输。*/
/* **************************************************************************//**
 * @brief
 * CRM: IC mode
 * configure different IC modes within the IC
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      if addressed directly
 *              Dsi3BusIf_eCMDACT_IGNORE        if addressed by wildcard
 * ****************************************************************************/
Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_IcMode (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer,
                                                          Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad,
                                                          Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* 1. if in CRM State -> execute command */
  /* 2. if in PDCM State -> stop meas & switch to CRM & execute command */
  /* 3. if in Discovery State -> stop discovery mode & switch to CRM */

  Dsi3BusIf_CmdIdAction_t retVal = Dsi3BusIf_eCMDACT_IGNORE;

  /* Check Data */
  if ((NULL != genericEnvData) && (NULL != commandBuffer) && (NULL != responseBuffer) && (NULL != loc_pApplRuntimeData))
  {
    /* disable EEPROM access */
    Eeprom_Disable();

    /* prepare received Data */
    Dsi3_uCrmCommand_t rcvData;
    rcvData.rawData = commandBuffer->Fields;
    /* prepare answer buffer */
    Dsi3_sAnswerFrame_t* ansData = (Dsi3_sAnswerFrame_t*)responseBuffer;
    ansData->Status = DSI3_STATUSBITS_OK;

    /* only execute if no module is busy */
    if(false == Eeprom_CheckIfBusy())
    {
      if(DSI3_ICMODE_PASSWORD == rcvData.IcMode.Password)
      {
        ansData->Data1 = 0;
        ansData->Data2 = rcvData.IcMode.ICMode;
        switch(rcvData.IcMode.ICMode)
        {
        case DSI3_ICMODE_OP1_DISCOVERY_MODE:
          (void)Dsi3_BusIfFuns->ChangeMode(genericEnvData, Dsi3BusIf_eCOMM_DISCOVERYMODE);
          break;
        case DSI3_ICMODE_OP3_SOFTWARE_RESET:
          /* enable software reset */
          SYS_STATE_RESET_ENABLE_bit.software = 1;
          /* execute software reset */
          SYS_STATE_SW_RESET_bit.sw_reset = 1;
          break;
        case DSI3_ICMODE_OP4_STANDBY:
          syss_EnterSleep();
          break;
        case DSI3_ICMODE_OP5_WAKE_UP:
          /* execute wakeup (done by dsi3 interrupt) */
          syss_ExitSleep();
          break;
        case DSI3_ICMODE_OP6_DSP_ON:
          /* switch DSP on */
          DSP_DSP_CTRL_bit.dsp_on = 1;
          break;
        case DSI3_ICMODE_OP7_DSP_OFF:
          /* switch DSP off */
          DSP_DSP_CTRL_bit.dsp_on = 0;
          break;
        case DSI3_ICMODE_OP8_TBD:
          /* reserved */
          break;
        default:
          /* invalid ic mode */
          ansData->Status = DSI3_STATUSBITS_ERROR;
          break;
        }
      }
      else
      {
        /* invalid password -> set answer bits to 0 & send error */
        ansData->Status = DSI3_STATUSBITS_ERROR;
        err_SetComErrorFlag(ERR_PASSWORD_WRONG);
      }
    }
    else
    {
      /* one module is busy -> dont execute cmd and return busy state */
      ansData->Status = DSI3_STATUSBITS_BUSY;
    }
    /* prepare response of no broadcast */
    if(DSI3_NAD_BROADCAST != rcvData.Default.PhysicalAddress)
    {
      ansData->ComErr = err_GetGlobalComErrFlag();
      ansData->HwErr = err_GetGlobalHwErrFlag();
      ansData->PhysicalAddress = currentNad;
      if(DSI3_STATUSBITS_ERROR == ansData->Status)
      {
        /* an error occured -> process it */
        ansData->Data1 = 0;
        ansData->Data2 = 0;
      }
      else
      {
        /* everything ok */
      }
      retVal = Dsi3BusIf_eCMDACT_RESPONSE;
    }
    else
    {
      retVal = Dsi3BusIf_eCMDACT_IGNORE;
    }

    /* refresh CRM application data */
    loc_SetLastExecutedCrmCmd(dsi3Drv_eCRM_COMMAND_ID_IC_MODE);

    loc_pApplRuntimeData->DSI3Ctrl->SyncFlag = TRUE;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }

  return retVal;
}
/*
Dsi3_CrmCmdHandler_IcMode 函数主要用于处理配置IC不同工作模式的命令。该函数的逻辑如下：1. 验证输入参数的有效性，确保它们均不为空指针。
2. 禁用EEPROM访问，以避免在处理IC模式更改期间受到干扰。3. 解析接收到的命令缓冲区数据到rcvData结构体，并初始化响应缓冲区ansData，设置其状态为正常（DSI3_STATUSBITS_OK）。
4. 当模块未处于繁忙状态时：•检查提供的密码是否正确，如果密码匹配（为DSI3_ICMODE_PASSWORD），则根据接收到的IC模式进行相应操作： •DSI3_ICMODE_OP1_DISCOVERY_MODE：切换到发现模式。
•DSI3_ICMODE_OP3_SOFTWARE_RESET：启用软件复位。•DSI3_ICMODE_OP4_STANDBY：进入待机模式。•DSI3_ICMODE_OP5_WAKE_UP：唤醒设备（由DSI3中断触发）。•DSI3_ICMODE_OP6_DSP_ON：开启DSP。
•DSI3_ICMODE_OP7_DSP_OFF：关闭DSP。•DSI3_ICMODE_OP8_TBD：预留的操作，暂未定义。•其他未知或无效的IC模式则返回错误状态。•如果密码不正确，则设置错误状态，并更新通信错误标志。
5. 如果模块处于繁忙状态，则返回忙碌状态（DSI3_STATUSBITS_BUSY）。
6. 根据命令是否为广播地址，准备并填充响应中的通信错误标志、硬件错误标志、物理地址等信息，并根据响应状态决定是否返回Dsi3BusIf_eCMDACT_RESPONSE。
7. 更新CRM应用数据，记录最后执行的CRM命令类型为“IC模式”。8. 设置同步标志为TRUE。9. 若在函数执行前发现输入参数无效，则调用错误处理程序并返回错误状态。
综上所述，该函数允许通过DSI3总线接口控制IC的不同工作模式，包括切换到发现模式、软件复位、待机/唤醒以及开关DSP等操作。同时，该函数也具备错误检测和响应机制，确保命令正确执行。
*/
/* **************************************************************************//**
 * @brief
 * PDCM: Measurement Response PDCM handler routine.
 *
 * Sends 1 (allowed) data packet from the Measurement results pool.
 * On repeated PDCM req, iterates through allowed data packets.
 * If all allowed packets have been sent, continues to send ACK GRA packets.
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       responseBuffer                  pointer to PDCM response buffer for next PDCM pulse
 * @param       bufsize                         max size of PDCM response buffer
 * @param       msgLen                          pointer to PDCM response message size (out)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      always
 * ****************************************************************************/
Dsi3BusIf_CmdIdAction_t Dsi3_PdcmCmdHandler(Dsi3BusIf_pGenericEnvData_t genericEnvData, 
                                                  Dsi3BusIf_ByteData_t* responseBuffer, 
                                                  const Dsi3BusIf_Length_t bufsize, 
                                                  uint8_t *msgLen, 
                                                  const Dsi3BusIf_SlaveID_t currentNad, 
                                                  Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* =============================================================================================
   * This function is called, when mode is changed to pdcm, to prepare the data for sending.
   * When the pdcm pulse is detected, the data is send out by hardware
   * ============================================================================================= */
  if((NULL != responseBuffer) && (NULL != loc_pApplRuntimeData) && (NULL != msgLen))
  {
    Dsi3Drv_uPDCMResponseFrame_t* ansData = (Dsi3Drv_uPDCMResponseFrame_t*)responseBuffer;

    loc_SynchPDCMClock(genericEnvData);

    switch(loc_pApplRuntimeData->DSI3Ctrl->PDCMCurrentType)
    {
    case DSI3_TYPE_MEAS_RESULT_APP_MODE:
      app_PdcmCmdHandler_APP_MODE(ansData);
      break;
    case DSI3_TYPE_MEAS_RESULT_LAB_MODE:
      lab_PdcmCmdHandler_LAB_MODE(ansData);
      break;
    default:
      /* no PDCM answer type has been set. Exit PDCM mode */
      (void)Dsi3_BusIfFuns->ChangeMode(genericEnvData, Dsi3BusIf_eCOMM_COMMANDRESPONSEMODE);
    }

    /* set answer data, that are common for all modes */
    ansData->defaultResponseFrame.HwErr             = err_GetGlobalHwErrFlag();
    ansData->defaultResponseFrame.ComErr            = err_GetGlobalComErrFlag();
    ansData->defaultResponseFrame.FrameCounter      = (loc_pApplRuntimeData->DSI3Ctrl->PDCMFrameCounter & 0x0Fu); /* 4 bits -> mask b0000 1111 */
    ansData->defaultResponseFrame.PhysAddr          = currentNad;

    /* set message length to its default value (8 byte) */
    *msgLen = DSI3_PDCM_ANSWER_FRAME_LENGTH;
    /* increment pcdm frame counter */
    loc_pApplRuntimeData->DSI3Ctrl->PDCMFrameCounter++;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }
  return Dsi3BusIf_eCMDACT_RESPONSE;
}
/*
Dsi3_PdcmCmdHandler 函数是PDCM（Periodic Data Communication Mode）测量响应处理例程，它负责在PDCM模式下发送允许的数据包。每当接收到重复的PDCM请求时，它会遍历允许发送的数据包列表。
一旦所有允许的数据包都已发送完毕，将继续发送ACK GRA数据包。该函数接收若干参数，包括指向DSI3总线环境数据结构的指针、
PDCM响应缓冲区指针、缓冲区最大长度、消息长度指针（传出参数）、当前分配的NAD（网络地址标识符）以及通用上下文数据指针。函数执行过程如下：
1. 检查输入参数的有效性，确保缓冲区指针、应用运行时数据指针以及消息长度指针均非空。
2. 同步PDCM时钟。3. 根据当前的PDCM类型（DSI3_TYPE_MEAS_RESULT_APP_MODE 或 DSI3_TYPE_MEAS_RESULT_LAB_MODE），调用对应的处理函数来填充响应数据。
对于未知类型的PDCM，会退出PDCM模式并切换回命令响应模式。4. 为所有模式设置通用响应数据，包括硬件错误标志、通信错误标志、帧计数器（仅使用低四位）和物理地址（NAD）。
5. 将消息长度设置为默认值（8字节）。6. 增加PDCM帧计数器的值。
7. 如果在执行函数前发现输入参数无效，则调用错误处理程序。函数始终返回Dsi3BusIf_eCMDACT_RESPONSE，表示已准备好响应数据。在PDCM脉冲被硬件检测到时，这些数据将被发送出去。
*/
/* **************************************************************************//**
 * @brief
 * Syncs the CRM clock of the slave to the master.
 *
 * SM103: External Synchronize (Part 1 of 2)
 * (for details see SafetyManual)
 *
 * @param       genericEnvData              The pointer to the Bus-environment-data
 * @return      void                        None.
 * ****************************************************************************/
static void loc_SynchCRMClock(Dsi3BusIf_pGenericEnvData_t genericEnvData)
{
  static uint8_t syncErrorCounter = 0u;
  uint16_t syncVal = 0u;
  uint16_t clkConfig = 0u;
   
  /* only execute if enabled */
  if((DSI3_SYNC_ON_CRM == (dsi3_cfg_status_sync_t)loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.SyncDsi3) ||
     (DSI3_SYNC_ON_CRM_AND_PDCM == (dsi3_cfg_status_sync_t)loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.SyncDsi3))
  {
    /* disable auto sync if it is enabled */
    if ( DSI3_ON == DSI3_CTRL_CONFIG_AUTOSNYC_GET())
    {
      DSI3_CTRL_CONFIG_AUTOSNYC_DISABLE();
    }
    else
    {
      /* everything ok, go on */
    }
    
    /* check if sync was successful */
    if(0u == DSI3_STATUS_bit.sync_cnt_err)
    {
      /* get DSI3 Sync_Count register value */
      syncVal = DSI3_CTRL_SYNC_CNT_GET(); 
      /* get DSI3 Clk 1us config */
      clkConfig = DSI3_CLK_1US_GET();
      
      /* calculate deviation between DSI3 Clk 1us and Expected Chiptime */
      int32_t differenceExpectedVal = clkConfig-DSI3_CRM_CHIPTIME_EXPECTED;
      /* calculate deviation between DSI3 Sync_Count and DSI3 Clk 1us */
      int32_t differenceSyncVal = syncVal-clkConfig;
      
      /* calculate absolute values */
      differenceExpectedVal = differenceExpectedVal * ( (differenceExpectedVal>0) - (differenceExpectedVal<0) );
      differenceSyncVal = differenceSyncVal * ( (differenceSyncVal>0) - (differenceSyncVal<0) );
      
      /* check if deviation between syncval and clk config is smaller 3% */
      if (differenceSyncVal < DSI3_CRM_CHIPTIME_MAX_DEVIATION)
      {
        /* check if deviation of clk config is smaller than 3% */
        if ( (syncVal > clkConfig) && (differenceExpectedVal < DSI3_CRM_CHIPTIME_MAX_DEVIATION) )
        {
          /* increment DSI3 Clk 1us config */
          clkConfig++;
          /* set new clock configuration data. update of register in bus_task */
          (void)Dsi3BusImp_Set1usClockCfg( genericEnvData, (Dsi3BusIf_ClkDiv_t) clkConfig);
        }
        else
        {
          /* check if deviation of clk config is smaller than 3% */
          if ( (syncVal < clkConfig) && (differenceExpectedVal < DSI3_CRM_CHIPTIME_MAX_DEVIATION) )
          {
            /* decrement DSI3 Clk 1us config */
            clkConfig--;
            /* set new clock configuration data. update of register in bus_task */
            (void)Dsi3BusImp_Set1usClockCfg( genericEnvData, (Dsi3BusIf_ClkDiv_t) clkConfig);
          }
          else
          {
            /* Added to satisfy the coding rules. */
          }
        }
        /* reset error counter */
        syncErrorCounter = 0u;
      }
      else
      {
        /* inkrement error counter */ 
        if ( syncErrorCounter < DSI3_SYNC_COUNT_ERROR_MAX )
        {
          syncErrorCounter++;
        }
        else
        {
          /* set error flag */
          err_SetComErrorFlag(ERR_SYNCHRONISATION_COUNTER_ERROR_DETECTED); 
        }
      }
    }
    else
    {
      /* hw correction value couldn't be calculated -> set ComErr Flag */
      err_SetComErrorFlag(ERR_SYNCHRONISATION_COUNTER_ERROR_DETECTED);
    }
  }
  else
  {
    /* sync in CRM is disabled */
    /* enable hardware auto sync if configured (SM103) */
    if(DSI3_SYNC_ON_HARDWARE == (dsi3_cfg_status_sync_t)loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.SyncDsi3)
    {
      DSI3_CTRL_CONFIG_AUTOSNYC_ENABLE();
    }
    else
    {
      /* nothing to do here */
    }
  }
  return;
}
/*
loc_SynchCRMClock 函数的作用是同步从设备的CRM时钟与主设备。此函数主要依据外部同步（Safety Manual中的SM103部分）的要求进行操作。
1. 首先检查同步选项是否启用，即检查loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.SyncDsi3是否设置了同步到CRM或同步到CRM和PDCM。
2. 如果启用了同步，先禁用自动同步功能（如果已启用的话）。3. 检查同步是否成功，通过检查DSI3_STATUS_bit.sync_cnt_err来确定是否有同步计数错误。
4. 如果同步成功，获取DSI3 Sync_Count寄存器的值（syncVal）和DSI3 Clk 1us配置值（clkConfig）。
5. 计算DSI3 Clk 1us与期望芯片时间之间的偏差百分比（differenceExpectedVal），以及DSI3 Sync_Count与DSI3 Clk 1us之间的偏差（differenceSyncVal）。
6. 如果同步计数值与时钟配置值之间的偏差小于3%，则进一步调整时钟配置值：•如果syncVal大于clkConfig且预期时间偏差小于最大允许偏差，则增加clkConfig并更新时钟配置；
•如果syncVal小于clkConfig且预期时间偏差小于最大允许偏差，则减少clkConfig并更新时钟配置。7. 如果同步计数值与时钟配置值之间的偏差超过3%，则递增错误计数器。
若错误计数达到最大次数，设置通信错误标志。8. 如果不能计算硬件修正值，则设置通信错误标志。
9. 如果同步到CRM的功能未启用，而同步到硬件的功能已启用，则启用硬件自动同步。此函数的核心任务是对DSI3时钟进行微调，确保从设备的CRM时钟与主设备保持一致，从而维持整个系统的稳定同步。
*/

/* **************************************************************************//**
 * @brief
 * synchs PCDM clock to 1ms BRC time distance
 *
 * SM103: External Synchronize (Part 2 of 2)
 * (for details see SafetyManual)
 *
 * @param       genericEnvData              pointer to Bus environment data
 * @return      none
 * ****************************************************************************/
static void loc_SynchPDCMClock(Dsi3BusIf_pGenericEnvData_t genericEnvData)
{
  static uint8_t syncErrorCounter = 0u;
  uint16_t clkConfig = 0u;
  uint16_t compB = 0u;
   
  if(NULL != loc_pApplRuntimeData)
  {
    /* only execute if enabled */
    if((DSI3_SYNC_ON_PDCM == (dsi3_cfg_status_sync_t)loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.SyncDsi3) ||
       (DSI3_SYNC_ON_CRM_AND_PDCM == (dsi3_cfg_status_sync_t)loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.SyncDsi3))
    {
      /* disable auto sync if it is enabled */
      if ( DSI3_ON == DSI3_CTRL_CONFIG_AUTOSNYC_GET())
      {
        DSI3_CTRL_CONFIG_AUTOSNYC_DISABLE();
      }
      else
      {
        /* everything ok, go on */
      }
      
      /* get TIMER_COMPARE_B value */
      compB = DSI3_CTRL_TIMER_COMPARE_B_GET();
      /* get DSI3 Clk 1us config */
      clkConfig = DSI3_CLK_1US_GET();
      
      if (compB > loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmPeriod)
      {
        /* check if deviation between TIMER_COMPARE_B and expected time is smaller 3% */
        if(compB <= (loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmPeriod + loc_pApplRuntimeData->MeasCtrl->RuntimeData.preCalcMaxPdcmDeviation))
        {
          /* increment DSI3 Clk 1us config */
          clkConfig++;
          /* set new clock configuration data. update of register in bus_task */
          (void)Dsi3BusImp_Set1usClockCfg( genericEnvData, (Dsi3BusIf_ClkDiv_t) clkConfig);
          /* reset error counter */
          syncErrorCounter = 0u;
        }
        else
        { 
          /* inkrement error counter */ 
          if ( syncErrorCounter < DSI3_SYNC_COUNT_ERROR_MAX )
          {
            syncErrorCounter++;
          }
          else
          {
            /* deviation out of expected range -> set ComErr Flag */
            err_SetComErrorFlag(ERR_TIME_BETWEEN_PDCM_SYNCS_OUT_OF_BOUND);
          }
        }
      }
      else
      {
        if (compB < loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmPeriod)
        {
          /* check if deviation between TIMER_COMPARE_B and expected time is smaller 3% */
          if(compB <= (loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmPeriod - loc_pApplRuntimeData->MeasCtrl->RuntimeData.preCalcMaxPdcmDeviation))
          {
            /* decrement DSI3 Clk 1us config */
            clkConfig--;
            /* set new clock configuration data. update of register in bus_task */
            (void)Dsi3BusImp_Set1usClockCfg( genericEnvData, (Dsi3BusIf_ClkDiv_t) clkConfig);
            /* reset error counter */
            syncErrorCounter = 0u;
          }
          else
          {
            /* inkrement error counter */ 
            if ( syncErrorCounter < DSI3_SYNC_COUNT_ERROR_MAX )
            {
              syncErrorCounter++;
            }
            else
            {
              /* deviation out of expected range -> set ComErr Flag */
              err_SetComErrorFlag(ERR_TIME_BETWEEN_PDCM_SYNCS_OUT_OF_BOUND);
            }
          }
        }
        else
        {
          /* Added to satisfy the coding rules. */
        }
      }
    }
    else
    {
      /* sync in PDCM is disabled */
    }
  }
  else
  {
    /* data struct not initialised -> cant execute function */
  }
  return;
}
/*
loc_SynchPDCMClock 函数用于将PDCM（周期数据通信模式）时钟同步到1毫秒的BRC（基本循环时间）间隔。这个函数是安全手册中关于外部同步描述（SM103 第二部分）的实现。
1. 检查输入参数genericEnvData不为空，并且同步到PDCM或同步到CRM和PDCM的功能已启用。2. 如果自动同步已启用，则禁用它。3. 获取TIMER_COMPARE_B的当前值（compB）和DSI3 Clk 1us配置值（clkConfig）。
4. 根据compB与预设的PDCM周期（loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmPeriod）的关系，检查它们之间的差异是否在允许的3%偏差范围内。
5. 如果compB大于预设PDCM周期但仍在允许偏差内，则增加clkConfig值并更新时钟配置；反之，如果compB小于预设PDCM周期但在允许偏差内，则减小clkConfig值并更新时钟配置。
每次成功调整时钟配置后，重置错误计数器（syncErrorCounter）。
6. 如果compB与预设PDCM周期的偏差超出允许范围，则递增错误计数器。当错误计数器达到上限时，设置通信错误标志（ERR_TIME_BETWEEN_PDCM_SYNCS_OUT_OF_BOUND）。
7. 如果同步到PDCM的功能未启用，函数不做任何操作。8. 如果loc_pApplRuntimeData为空，则无法执行函数，因为数据结构尚未初始化。
总之，该函数通过调整DSI3 Clk 1us配置，确保PDCM时钟与系统预设的BRC时间保持同步，从而保证通信的准确性。
同时，它具有错误检测和处理机制，以应对同步过程中可能出现的问题。
*/


/* **************************************************************************//**
 * @brief
 * Change Mode to PDCM
 *
 * Changes DSI3 to PDCM Mode and prepares configuration data
 *
 * @param       genericEnvData      generic environment data pointer, should point to bus environment data
 * @param       pdcmType            PDCM response type
 * @return      none
 * ****************************************************************************/
static void loc_ChangeModeToPdcm(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3_ePDCMType_t pdcmType)
{
  if((NULL != loc_pApplRuntimeData) && (NULL != genericEnvData))
  {
    /* reset pdcm frame counter */
    loc_pApplRuntimeData->DSI3Ctrl->PDCMFrameCounter = 0;
    /* save the pdcm frame type */
    loc_pApplRuntimeData->DSI3Ctrl->PDCMCurrentType = pdcmType;
    /* change mode to pdcm */
    (void)Dsi3_BusIfFuns->ChangeMode(genericEnvData, Dsi3BusIf_eCOMM_PERIODICDATACOLLECTIONMODE);
  }
  else
  {
    /* call with NULL pointer -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }
}
/*
loc_ChangeModeToPdcm 函数的主要作用是将DSI3切换到PDCM（Periodic Data Collection Mode）模式，并为此模式做相应的配置准备工作。
1. 函数首先检查输入的loc_pApplRuntimeData和genericEnvData指针是否非空。如果两者均非空，则继续执行后续操作。
2. 清零PDCM帧计数器(PDCMFrameCounter)，以便于在新的PDCM模式下重新开始计数。
3. 存储传入的PDCM响应类型(pdcmType)到运行时数据结构(loc_pApplRuntimeData->DSI3Ctrl->PDCMCurrentType)中，这样系统就能知道当前要采用哪种PDCM模式进行数据收集。
4. 调用Dsi3_BusIfFuns->ChangeMode函数，将DSI3的通信模式切换到PDCM模式（Dsi3BusIf_eCOMM_PERIODICDATACOLLECTIONMODE）。
5. 如果输入的任意一个指针为空，则调用错误处理函数err_ErrorHandler，传入错误代码ERR_MODLIST_DSI3，表示出现了非法的NULL指针错误。
综上所述，loc_ChangeModeToPdcm函数是一个内部辅助函数，用来改变DSI3设备的工作模式，并为即将开始的PDCM模式做必要的初始化设置。
*/

#if defined(FPGA_52417B) 
/* **************************************************************************//**
 * @brief
 * CRM: AssignID command.
 *
 * Assigns a new nad to current node. If node is in DISCOVERY mode,
 * AssignID is used for autoaddressing purposes (PA must be 7 then)
 *
 * This function is needed for auto addressing on the fpga development environment.
 * It has a different auto addressing method by using a relay
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command buffer struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response buffer struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       currentMode                     current DSI3 bus operation mode
 * @param       genericCbCtxData                pointer to relevant context data
 * @return      Dsi3BusIf_eCMDACT_IGNORE        msg was either broadcast, not addressed to current node or corrupt.
 *              Dsi3BusIf_eCMDACT_RESPONSE      msg was processed successfully and a response has been built.
 * ****************************************************************************/
Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_IdAssign(Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer,
                                                            Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad,
                                                            Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  Dsi3BusIf_CmdIdAction_t retVal = Dsi3BusIf_eCMDACT_IGNORE;

  if ((NULL != commandBuffer) && (NULL != responseBuffer) && (NULL != genericEnvData))
  {
    /* set default answer values */
    responseBuffer->Fields.PhysicalAddress = currentNad;
    responseBuffer->Fields.ExtendedData    = DSI3_CRM_RESPONSE_NOK_SYMBOL;
    responseBuffer->Fields.RegisterData    = 0xFF;

    /* Check if currently no measurement is running */
    if (meas_eMeas_STATE_IDLE == loc_pApplRuntimeData->MeasCtrl->CurrentState)
    {
      switch((loc_eIDAssign_SubCmd_t)(commandBuffer->Fields.ExtendedData & CRM_ASSIGNID_BITMASK_RD_NAD))
      {
        case (loc_eIDAssign_SubCmd_EnableStore):
        case (loc_eIDAssign_SubCmd_StoreBusAndNad):
        {
          if (currentNad == commandBuffer->Fields.PhysicalAddress)
          {
            /* Build CRM response */
            responseBuffer->Fields.ExtendedData    = DSI3_CRM_RESPONSE_OK_SYMBOL;
            retVal = Dsi3BusIf_eCMDACT_RESPONSE;
          }
          else
          {
             /*Msg was a broadcast */
          }
        }
        break;
        case (loc_eIDAssign_SubCmd_ChangeBusAndNad):
        {
          if (currentNad == commandBuffer->Fields.PhysicalAddress)
          {
            uint8_t newNad = commandBuffer->Fields.RegisterData & CRM_ASSIGNID_BITMASK_RD_NAD;
            if (Dsi3_BusIfFuns->UpdateDeviceAddress(genericEnvData, newNad))
            {
              /* save id to ram */
              loc_pApplRuntimeData->MeasCtrl->Parameters.data.SlaveId.fields.SlaveId = newNad;
              /* update PDCM response time slot */
              uint16_t myStart = 0;
              switch(newNad)
              {
              case 1:
                myStart = loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor1;
                break;
              case 2:
                myStart = loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor2;
                break;
              case 3:
                myStart = loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor3;
                break;
              case 4:
                myStart = loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor4;
                break;
              case 5:
                myStart = loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor5;
                break;
              case 6:
                myStart = loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor6;
                break;
              default:
                myStart = loc_pApplRuntimeData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor7;
                break;
              }
              myStart = myStart - ((newNad - 1) * DSI3_CFG_PDCM_SLOT_TIME);
              (void)Dsi3_BusIfFuns->UpdatePDCMStartSlotOffset(genericEnvData, myStart);
              /* Build CRM response */
              responseBuffer->Fields.PhysicalAddress = newNad;
              responseBuffer->Fields.ExtendedData = DSI3_CRM_RESPONSE_OK_SYMBOL;
              /* Msg was for me, send a response! */
              retVal = Dsi3BusIf_eCMDACT_RESPONSE;
            }
            else
            {
              /* newNad was not valid! */
            }
          }
          else
          {
            /*Msg was a broadcast */
          }
        }
        break;
        default:
        {
          /*Undefined state...*/
          if (currentNad == commandBuffer->Fields.PhysicalAddress)
          {
            /* Msg was for me, send a response! */
            retVal = Dsi3BusIf_eCMDACT_RESPONSE;
          }
          else
          {
            /* newNad was not valid! */
          }
        }
        break;
      }
    }
    else
    {
      /* Currently running a measurement! */
      if (currentNad == commandBuffer->Fields.PhysicalAddress)
      {
        /* Msg was for me, send a response! */
        retVal = Dsi3BusIf_eCMDACT_RESPONSE;
      }
    }
  }
  else
  {
    /*Error: runtimeData not initialized!*/
  }

  return retVal;
}
#endif /* End: #if (FPGA_52417B) */
