/** @addtogroup dsi3_Driver_interfaces
 * @{ */
/***************************************************************************/
/** @file       Dsi3Bus_Types.h
 *
 * @brief       Definitions of basic data types for the DSI3 bus layer implementation.
 *
 * @purpose   Definitions of data types and structs used in the DSI3 bus layer 
 *            implementation.
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
 *
 * @section history_sec_Dsi3Bus_Types_h Revision History
 * $Id: Dsi3Bus_Types.h 422 2019-03-14 14:55:33Z poe $
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who Ver  Comment
 * -------------------------------------------------------------------
 * 19/03/11 (F) POE 1008 Added error code for disc mode current detection error.
 * 18/11/20 (F) POE 1007 Changed #pragma declaration for compiler compatibility.
 * 18/08/21 (F) POE 1006 Added doxygen comments.
 * 18/08/17 (F) POE 1005 Renamed Dsi3BusIf_eInterfaceIds Lin_IfId_Count to Dsi3_IfId_Count.
 * 18/03/23 (F) POE 1004 Added 524.17B configuration parameters.
 * 18/02/26 (F) POE 1003 removed unused internal state enums.
 * 18/01/17 (F) POE 1002 updated header and demo usage disclaimer.
 * ...
 * 17/06/19 (F) POE 1000 initial version
 * -------------------------------------------------------------------
 * @endverbatim
 *
 * @creator      POE
 * @created      2017/06/19
 *
 * @project      524.17
 * @requested    ELMOS
 * @inspector    -
 * @verification -
 * @version      $Revision: 422 $
 *
 *
 * $State: Exp $
 * $Author: poe $
 *
 * Additional markers:
 *
 */
#ifndef DSI3_TYPES_H_
#define DSI3_TYPES_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "dsi3_InterruptHandler.h"
#include "def_dsi3.h"
/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define DSI3_NULL                                       ((void*)(0UL))                    /**<  An internal definition of "NULL" */

#define DSI3_DRV_CRM_FRAME_LENGTH                       (4u)                              /**<  CRM frame length (bytes) */
/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

typedef void *                                    Dsi3BusIf_pvoid_t;                      /**<  Void-pointer data type. */
typedef const   void *                            Dsi3BusIf_cpvoid_t;                     /**<  Constant void-pointer data type. */

typedef         Dsi3BusIf_pvoid_t                 Dsi3BusIf_pGenericEnvData_t;            /**<  Generic pointer to environment data of the BUS layer module */
typedef         Dsi3BusIf_cpvoid_t                Dsi3BusIf_cpGenericImpCfgData_t;        /**<  Generic pointer to configuration parameter of the specific BUS layer implementation */
typedef         Dsi3BusIf_pvoid_t                 Dsi3BusIf_pGenericCbCtxData_t;          /**<  Pointer to BUS callback context data */

typedef         Dsi3BusIf_pvoid_t                 Dsi3BusIf_pGenericRuntimeData_t;        /**<  Pointer to Runtime Data */
typedef const   Dsi3BusIf_pGenericRuntimeData_t   Dsi3BusIf_cpGenericRuntimeData_t;       /**<  Constant Pointer to Runtime Data */

typedef Dsi3BusIf_pvoid_t                         Dsi3BusIf_pGenericInterfaceFunctions_t; /**< Generic pointer to interface functions structure */
typedef Dsi3BusIf_cpvoid_t                        Dsi3BusIf_cpGenericInterfaceFunctions_t;/**< Generic pointer to interface functions structure (const) */

typedef         uint8_t                           Dsi3BusIf_Error_t;                      /**<  Mapping for bus error codes to generic error type */

typedef         bool_t                            Dsi3BusIf_Bool_t;                       /**<  generic bool type */

typedef         uint8_t                           Dsi3BusIf_Data_t;                       /**<  Basic BUS data type */
typedef         Dsi3BusIf_Data_t*                 Dsi3BusIf_pData_t;                      /**<  Pointer to Dsi3BusIf_Data_t */
typedef         Dsi3BusIf_Data_t**                Dsi3BusIf_ppData_t;                     /**<  Pointer-Pointer to Dsi3BusIf_Data_t */
typedef const   Dsi3BusIf_Data_t*                 Dsi3BusIf_cpData_t;                     /**<  Constant Pointer to Dsi3BusIf_Data_t */

typedef         uint8_t                           Dsi3BusIf_CountValue_t;                 /**<  CountValue data type */

typedef         uintptr_t                         Dsi3BusIf_Length_t;                     /**<  BUS layer data type of length values */
typedef         Dsi3BusIf_Length_t*               Dsi3BusIf_pLength_t;                    /**<  Pointer to Dsi3BusIf_Length_t */

typedef         Dsi3BusIf_Length_t                Dsi3BusIf_EnvDataSze_t;                 /**<  Type for bus layer environment data */

typedef         uint8_t                           Dsi3BusIf_ByteData_t;                   /**<  Byte sized data */
typedef         Dsi3BusIf_ByteData_t *            Dsi3BusIf_pByteData_t;                  /**<  Byte sized data pointer */
typedef const   Dsi3BusIf_ByteData_t *            Dsi3BusIf_cpByteData_t;                 /**<  Byte sized data constant pointer */

typedef         uint16_t                          Dsi3BusIf_WordData_t;                   /**<  Word sized data */
typedef         Dsi3BusIf_WordData_t *            Dsi3BusIf_pWordData_t;                  /**<  Word sized data pointer */
typedef  const   Dsi3BusIf_WordData_t *           Dsi3BusIf_cpWordData_t;                 /**<  Word sized data constant pointer */

typedef         uint16_t                          Dsi3BusIf_ClkDiv_t;                     /**<  Data type for clock divider */

typedef         uint16_t                          Dsi3BufIf_SyncCountValue_t;             /**<  Data type for Sync Count Value */
typedef         uint16_t                          Dsi3BufIf_TimerCaptureValue_t;          /**<  Data type for Timer Capture Value */

typedef         uint32_t                          Dsi3BusIf_DWordData_t;                  /**<  Double Word sized data */
typedef         Dsi3BusIf_DWordData_t *           Dsi3BusIf_pDWordData_t;                 /**<  Double Word sized data pointer */
typedef const   Dsi3BusIf_DWordData_t *           Dsi3BusIf_cpDWordData_t;                /**<  Double Word sized data constant pointer */

typedef         uint8_t                           Dsi3BusIf_SlaveID_t;                    /**<  Data type for SlaveID */
typedef         uint32_t                          Dsi3BusIf_Serial_t;                     /**<  Data type for Serial Number */

typedef         uint8_t                           Dsi3BusIf_CmdID_t;                      /**<  Data type for PID representation */

typedef         uint16_t                          Dsi3BusIf_InterfaceVersion_t;           /**<  Data type for interface versioning */
typedef         uint16_t                          Dsi3BusIf_Version_t;                    /**<  Data type for versioning */

typedef         uint16_t                          Dsi3BusIf_Time_t;                       /**<  Data type for register time values */
typedef         uint32_t                          Dsi3BusIf_Tick_t;                       /**<  Data type for tick count representation */
typedef         Dsi3BusIf_Tick_t                  Dsi3BusIf_TimeOut_t;                    /**<  Data type for timeout values */

struct          Dsi3BusIf_sThis;                                                          /**<  Forward declaration of Dsi3 BUS layer This-Pointer. */
typedef struct  Dsi3BusIf_sThis                   Dsi3BusIf_sThis_t;                      /**<  Typedef for Dsi3BusIf_sThis. */
typedef         Dsi3BusIf_sThis_t*                Dsi3BusIf_pThis_t;                      /**<  Typedef of pointer to Dsi3BusIf_sThis. */
typedef const   Dsi3BusIf_sThis_t*                Dsi3BusIf_cpThis_t;                     /**<  Typedef of pointer to Dsi3BusIf_sThis. */

/*
Dsi3BusIf_pvoid_t 和 Dsi3BusIf_cpvoid_t：•Dsi3BusIf_pvoid_t：定义为指向void类型的指针，用于表示通用的指针数据类型。
•Dsi3BusIf_cpvoid_t：定义为指向常量void类型的指针，用于表示通用的常量指针数据类型。
2. Dsi3BusIf_pGenericEnvData_t 和 Dsi3BusIf_cpGenericImpCfgData_t 以及其他与之类似的类型：
•这些类型是基于上面的通用指针类型定义的，用于具体表示DSI3总线层的各种数据指针，如环境数据、配置参数、回调上下文数据、运行时数据及其常量版本等。
3. Dsi3BusIf_pGenericInterfaceFunctions_t 和其const版本：•定义为指向通用接口函数结构体的指针，用于访问总线接口层提供的各种功能函数。
4. Dsi3BusIf_Error_t：•表示DSI3总线错误代码的映射类型，用于表示总线错误。
5. Dsi3BusIf_Bool_t：•定义为一个通用布尔类型，用于在DSI3总线接口层中表示布尔值。
6. Dsi3BusIf_Data_t 及其指针类型：•Dsi3BusIf_Data_t 是DSI3总线的基本数据类型，通常是一个8位无符号整数。
•Dsi3BusIf_pData_t、Dsi3BusIf_ppData_t 和 Dsi3BusIf_cpData_t 分别表示指向该基本数据类型的指针、指针的指针和常量指针。
7. Dsi3BusIf_CountValue_t：•表示计数值的数据类型，这里也是8位无符号整数。
8. Dsi3BusIf_Length_t 及其指针类型：•Dsi3BusIf_Length_t 定义为一个表示总线层长度值的数据类型，通常是无符号整数类型。•Dsi3BusIf_pLength_t 是指向Dsi3BusIf_Length_t类型的指针。
9. Dsi3BusIf_EnvDataSze_t：•定义为一种类型，用于表示DSI3总线层环境数据的大小，其实质上与Dsi3BusIf_Length_t相同。
Dsi3BusIf_ByteData_t 和其指针类型：•Dsi3BusIf_ByteData_t 定义了一个8位无符号整数类型，用于表示单字节大小的数据。
•Dsi3BusIf_pByteData_t 是指向 Dsi3BusIf_ByteData_t 类型的指针。•Dsi3BusIf_cpByteData_t 是指向 Dsi3BusIf_ByteData_t 类型的常量指针。
2. Dsi3BusIf_WordData_t 和其指针类型：•Dsi3BusIf_WordData_t 定义了一个16位无符号整数类型，用于表示双字节（word）大小的数据。•Dsi3BusIf_pWordData_t 是指向 Dsi3BusIf_WordData_t 类型的指针。
•Dsi3BusIf_cpWordData_t 是指向 Dsi3BusIf_WordData_t 类型的常量指针。
3. Dsi3BusIf_ClkDiv_t：•定义了一个16位无符号整数类型，用于表示时钟分频器的值。
4. Dsi3BufIf_SyncCountValue_t 和 Dsi3BufIf_TimerCaptureValue_t：•Dsi3BufIf_SyncCountValue_t 定义了一个16位无符号整数类型，用于表示同步计数值。
•Dsi3BufIf_TimerCaptureValue_t 定义了一个16位无符号整数类型，用于表示定时器捕获值。
5. Dsi3BusIf_DWordData_t 和其指针类型：•Dsi3BusIf_DWordData_t 定义了一个32位无符号整数类型，用于表示双字（double word）大小的数据。
•Dsi3BusIf_pDWordData_t 是指向 Dsi3BusIf_DWordData_t 类型的指针。•Dsi3BusIf_cpDWordData_t 是指向 Dsi3BusIf_DWordData_t 类型的常量指针。
6. Dsi3BusIf_SlaveID_t 和 Dsi3BusIf_Serial_t：•Dsi3BusIf_SlaveID_t 定义了一个8位无符号整数类型，用于表示从设备ID。
•Dsi3BusIf_Serial_t 定义了一个32位无符号整数类型，用于表示序列号。
7. Dsi3BusIf_CmdID_t：•定义了一个8位无符号整数类型，用于表示命令ID（PID）。
8. Dsi3BusIf_InterfaceVersion_t 和 Dsi3BusIf_Version_t：•Dsi3BusIf_InterfaceVersion_t 定义了一个16位无符号整数类型，用于表示接口版本信息。
•Dsi3BusIf_Version_t 同样定义了一个16位无符号整数类型，用于表示版本信息。
9. Dsi3BusIf_Time_t 和 Dsi3BusIf_Tick_t：•Dsi3BusIf_Time_t 定义了一个16位无符号整数类型，用于表示寄存器中的时间值。
•Dsi3BusIf_Tick_t 定义了一个32位无符号整数类型，用于表示滴答计数表示的时间戳。•Dsi3BusIf_TimeOut_t 也使用 Dsi3BusIf_Tick_t 类型，表示超时值。
10. Dsi3BusIf_sThis_t 和其指针类型：•结构体 Dsi3BusIf_sThis 是DSI3总线层的“this”指针的前置声明。
•Dsi3BusIf_sThis_t 是对 Dsi3BusIf_sThis 结构体的类型定义。•Dsi3BusIf_pThis_t 是指向 Dsi3BusIf_sThis_t 结构体的指针。•Dsi3BusIf_cpThis_t 是指向 Dsi3BusIf_sThis_t 结构体的常量指针。
*/


/***************************************************************************//**
 * @brief Enumeration for DSI3 Driver interfaces.
 ******************************************************************************/
enum Dsi3BusIf_eInterfaceIds
{
  Dsi3_IfId_BUS         = 0,  /**< BUS Layer Interface ID. */
  Dsi3_IfId_HWMODULE    = 1,  /**< BUS Layer hardware module Interface ID. */
  Dsi3_IfId_Count       = 2   /**< Actual count of available interfaces ID. */
};

typedef enum Dsi3BusIf_eInterfaceIds Dsi3BusIf_InterfaceIds_t; /**< Typedef of Dsi3_eInterfaceIds. */


/* **************************************************************************//**
 *
 * @brief Command and Response Mode - Command Format  
 * *****************************************************************************/
#pragma pack(push, 4)
struct Dsi3Bus_CrmCommandFields
{
    Dsi3BusIf_ByteData_t                                CRC;                                            /**<  CRM CRC */
    Dsi3BusIf_ByteData_t                                RegisterData;                                   /**<  CRM RegisterData */
    Dsi3BusIf_ByteData_t                                ExtendedData;                                   /**<  CRM Extended Data */
    Dsi3BusIf_ByteData_t                                Command                 : 4;                    /**<  CRM Command */
    Dsi3BusIf_ByteData_t                                PhysicalAddress         : 4;                    /**<  CRM NAD */
};    
#pragma pack(pop)

typedef struct  Dsi3Bus_CrmCommandFields     Dsi3Bus_CrmCommandFields_t;
typedef         Dsi3Bus_CrmCommandFields_t*  Dsi3Bus_pCrmCommandFields_t;
typedef const	Dsi3Bus_CrmCommandFields_t*	Dsi3Bus_cpCrmCommandFields_t;


#pragma pack(push, 4)
union Dsi3Bus_uCrmCommand                                                                               /**<  Union of CRM Command Buffer*/
{
    Dsi3Bus_CrmCommandFields_t                          Fields;                                         /**<  CRM Command Fields */
    Dsi3BusIf_ByteData_t                                Bytes[DSI3_DRV_CRM_FRAME_LENGTH];               /**<  CRM Command Bytes */
    Dsi3BusIf_DWordData_t                               Value;                                          /**<  CRM Command Value */
};
#pragma pack(pop)
typedef union   Dsi3Bus_uCrmCommand            Dsi3Bus_CrmCommand_t;                                    /**< Typedef of Dsi3Bus_uCrmCommand */
typedef         Dsi3Bus_CrmCommand_t*          Dsi3Bus_pCrmCommand_t;                                   /**< Typedef of pointer to Dsi3Bus_CrmCommand_t */
typedef const   Dsi3Bus_CrmCommand_t*          Dsi3Bus_cpCrmCommand_t;                                  /**< Typedef of pointer to Dsi3Bus_CrmCommand_t */

/* Command and Response Mode - Response Format */
#pragma pack(push, 4)
union Dsi3Bus_uCrmResponse                                                                              /**<  Union of CRM Response Buffer */
{
  #pragma pack(push, 4)
  struct
  {
    Dsi3BusIf_ByteData_t                  CRC;                                            /**<  CRM CRC */
    Dsi3BusIf_ByteData_t                  RegisterData;                                   /**<  CRM RegisterData */
    Dsi3BusIf_ByteData_t                  ExtendedData;                                   /**<  CRM Extended Data */
    Dsi3BusIf_ByteData_t                  Status                  : 4;                    /**<  CRM Command */
    Dsi3BusIf_ByteData_t                  PhysicalAddress         : 4;                    /**<  CRM SlaveID */
  } Fields;
  #pragma pack(pop)
  Dsi3BusIf_ByteData_t                    Bytes[DSI3_DRV_CRM_FRAME_LENGTH];               /**<  CRM Response Bytes */
  Dsi3BusIf_DWordData_t                   Value;                                          /**<  CRM Response Value */
};
#pragma pack(pop)
typedef union  Dsi3Bus_uCrmResponse            Dsi3Bus_CrmResponse_t;                      /**< Typedef of Dsi3Bus_uCrmResponse */
typedef        Dsi3Bus_CrmResponse_t*          Dsi3Bus_pCrmResponse_t;                     /**< Typedef of pointer to Dsi3Bus_CrmResponse_t */
typedef const  Dsi3Bus_CrmResponse_t*          Dsi3Bus_cpCrmResponse_t;                    /**< Typedef of pointer to Dsi3Bus_CrmResponse_t */

/*
此段代码定义了DSI3驱动接口相关的枚举类型、结构体和联合体。1. Dsi3BusIf_eInterfaceIds:•枚举类型，定义了DSI3总线接口的ID，包括BUS层接口ID（Dsi3_IfId_BUS）和硬件模块接口ID（Dsi3_IfId_HWMODULE）。
2. Dsi3Bus_CrmCommandFields_t:•结构体，用于表示DSI3命令模式（Command and Response Mode, CRM）的命令格式。包含CRC校验、寄存器数据、扩展数据、命令标识和物理地址（NAD）等字段。
3. Dsi3Bus_uCrmCommand:•联合体，包含了CRM命令缓冲区的多种表示形式，包括命令字段（Fields）、字节数组（Bytes）和双字数据（Value）。可以通过选择不同的成员访问CRM命令的不同方面。
4. Dsi3Bus_CrmResponse_t:•联合体，类似于命令格式，用于表示CRM响应缓冲区。它同样包含了CRC校验、寄存器数据、扩展数据、状态标识和从设备ID（SlaveID）等字段，并提供了字节数组和双字数据两种访问方式。
以上定义的结构体和联合体主要用于构建和解析DSI3总线上的命令和响应消息，确保数据传输的正确性和完整性。
通过定义指针类型（如Dsi3Bus_pCrmCommandFields_t、Dsi3Bus_cpCrmCommandFields_t、Dsi3Bus_pCrmCommand_t、Dsi3Bus_cpCrmCommand_t等），可以在程序中方便地操作这些命令和响应结构。
同时，使用#pragma pack(push, 4)和#pragma pack(pop)来控制结构体和联合体的内存对齐，确保数据按4字节边界对齐，避免因编译器默认对齐策略
*/
/* **************************************************************************//**
 * @brief DSI3 communication modes enumeration
 * *****************************************************************************/
enum Dsi3BusIf_eCommunicationMode
{
  Dsi3BusIf_eCOMM_COMMANDRESPONSEMODE         = 0u,                                       /**<  Communication Mode CRM */
  Dsi3BusIf_eCOMM_PERIODICDATACOLLECTIONMODE  = 1u,                                       /**<  Communication Mode PDCM */
  Dsi3BusIf_eCOMM_DISCOVERYMODE               = 2u                                        /**<  Communication Mode Discovery Mode */
};

typedef enum   Dsi3BusIf_eCommunicationMode   Dsi3BusIf_eCommunicationMode_t;             /**<  Typedef of Dsi3If_eState. */


/* **************************************************************************//**
 * @brief DSI3 mode state enumeration
 * *****************************************************************************/
enum Dsi3BusIf_eState
{
  Dsi3BusIf_eSTATE_IDLE                                 = 0u,                             /**<  Bus is receiving data */
  Dsi3BusIf_eSTATE_ANSWERING                            = 1u,                             /**<  Bus is transmiting data. */
  Dsi3BusIf_eSTATE_WAIT_FOR_DISC_PULSE                  = 2u,                             /**<  Bus waits for Discovery Pulse. */
  Dsi3BusIf_eSTATE_PDCMPREPAREBUFFER                    = 3u,                             /**<  PDCM response needs to be set up */
  Dsi3BusIf_eSTATE_RESPONSE_PROCESSED                   = 4u                              /**<  Current master request has been processed but not notified to the upper layers  - processing another master request while in this state will result in TaskToSlow error */
};

typedef enum Dsi3BusIf_eState Dsi3BusIf_eState_t;                                         /**<  Typedef of Dsi3If_eState. */


/* **************************************************************************//**
 * @brief DSI3 RCC chip time enumeration
 * *****************************************************************************/
enum Dsi3BusIf_eRCC_Chiptime
{
  Dsi3BusIf_eRCC_Chiptime_3US = 0u,                                                       /**< RCC Chiptime 3us */
  Dsi3BusIf_eRCC_Chiptime_4US = 1u,                                                       /**< RCC Chiptime 4us */
  Dsi3BusIf_eRCC_Chiptime_5US = 2u,                                                       /**< RCC Chiptime 5us */
  Dsi3BusIf_eRCC_Chiptime_6US = 3u                                                        /**< RCC Chiptime 6us */
};

typedef enum  Dsi3BusIf_eRCC_Chiptime   Dsi3BusIf_ChipTime_t;                             /**<  Data type configured RCC chiptime */


/* **************************************************************************//**
 * @brief DSI3 RCC slope selection enumeration
 * *****************************************************************************/
enum Dsi3BusIf_eRCC_Slope 
{
  Dsi3BusIf_eRCC_Slope_1us          = 0u,
  Dsi3BusIf_eRCC_Slope_2us          = 1u,
  Dsi3BusIf_eRCC_Slope_3us          = 2u,
  Dsi3BusIf_eRCC_Slope_4us          = 3u,
  Dsi3BusIf_eRCC_Slope_6us          = 4u
};

typedef enum Dsi3BusIf_eRCC_Slope Dsi3BusIf_RCC_Slope_t;                                  /**<  Data type configured RCC slope selection */


/* **************************************************************************//**
 * @brief DSI3 RCC current waveform enumeration
 * *****************************************************************************/
enum Dsi3BusIf_eRCC_Curve 
{
  Dsi3BusIf_eRCC_Curve_Rounded      = 0u,
  Dsi3BusIf_eRCC_Curve_Linear       = 1u
};

typedef enum Dsi3BusIf_eRCC_Curve Dsi3BusIf_RCC_Curve_t;                                  /**<  Data type configured RCC current waveform selection */

/*
这段代码定义了DSI3总线接口相关的枚举类型：1. Dsi3BusIf_eCommunicationMode:•该枚举描述了DSI3通信模式，包括命令响应模式（CRM）、周期数据采集模式（PDCM）和发现模式（Discovery Mode）。
2. Dsi3BusIf_eCommunicationMode_t:•将 Dsi3BusIf_eCommunicationMode 枚举类型做了typedef，方便后续引用。
3. Dsi3BusIf_eState:•该枚举列举了DSI3总线接口可能的状态，包括空闲（idle）、响应中（answering）、等待发现脉冲（wait_for_disc_pulse）、PDCM响应准备（pdcmpreparebuffer）和响应已处理但未通知上层（response_processed）。
4. Dsi3BusIf_eState_t:•类似于前面的通信模式，此处对 Dsi3BusIf_eState 枚举进行了typedef，简化后续引用。
5. Dsi3BusIf_eRCC_Chiptime:•此枚举列举了DSI3 RCC芯片时间的几种可能值，分别是3us、4us、5us和6us。
6. Dsi3BusIf_ChipTime_t:•对 Dsi3BusIf_eRCC_Chiptime 枚举类型进行了typedef，定义为配置好的RCC芯片时间的数据类型。
这些枚举类型和typedef为DSI3总线接口的通信模式、状态和RCC芯片时间提供了统一的、易于理解和使用的类型定义，便于在实际编程过程中进行状态判断、模式切换和时间配置等工作。
*/
/* **************************************************************************//**
 * @brief DSI3 RCC current offset value enumeration
 * *****************************************************************************/
enum Dsi3BusIf_eRCC_CurrentOffset 
{
  Dsi3BusIf_eRCC_CurrentOffset_0uA = 0u,
  Dsi3BusIf_eRCC_CurrentOffset_1uA = 1u,
  Dsi3BusIf_eRCC_CurrentOffset_2uA = 2u,
  Dsi3BusIf_eRCC_CurrentOffset_3uA = 3u,
  Dsi3BusIf_eRCC_CurrentOffset_4uA = 4u,
  Dsi3BusIf_eRCC_CurrentOffset_5uA = 5u,
  Dsi3BusIf_eRCC_CurrentOffset_6uA = 6u,
  Dsi3BusIf_eRCC_CurrentOffset_7uA = 7u
};

typedef enum Dsi3BusIf_eRCC_CurrentOffset Dsi3BusIf_RCC_CurrentOffset_t;                  /**<  Data type configured RCC current offset value */

/* **************************************************************************//**
 * @brief DSI3 FCC bit timing enumeration
 * *****************************************************************************/
enum Dsi3BusIf_eFCC_TBit 
{
  Dsi3BusIf_eFCC_TBit_08us = 0u,
  Dsi3BusIf_eFCC_TBit_16us = 1u,
  Dsi3BusIf_eFCC_TBit_32us = 2u,
  Dsi3BusIf_eFCC_TBit_8us  = 3u
};

typedef enum Dsi3BusIf_eFCC_TBit Dsi3BusIf_FCC_TBit_t;                                    /**<  Data type configured FCC bit time selection */

/* **************************************************************************//**
 * @brief DSI3 debounce value
 * *****************************************************************************/

typedef      dsi3_DebounceValue_t      Dsi3BusIf_DebounceValue_t;                         /**<  Data type configured debounce value */

/***************************************************************************//**
 * @brief An enumeration indicating how to proceed according to a received CMD
 ******************************************************************************/
enum Dsi3BusIf_eCmdIdAction
{
  Dsi3BusIf_eCMDACT_IGNORE                               = 0u,                            /**<  Invalid or unknown cmd ID. (Bus driver continues to wait for next break) */
  Dsi3BusIf_eCMDACT_RESPONSE                             = 1u                             /**<  This cmd ID indicates the cmd can be processed normally. */
} ;

typedef enum Dsi3BusIf_eCmdIdAction Dsi3BusIf_CmdIdAction_t;

/* **************************************************************************//**
 * @brief DSI3 DISCOVERY mode status enumeration
 * *****************************************************************************/
enum Dsi3BusIf_eDiscoveryModeStatus
{
  Dsi3BusIf_eDISCSTAT_STARTED                           = 0u,                             /**< State Discovery Mode has started */
  Dsi3BusIf_eDISCSTAT_ADDRESSED                         = 1u,                             /**< State Discovery Mode Slave addressed */
  Dsi3BusIf_eDISCSTAT_TERMINATED                        = 2u                              /**< State Discovery Mode has terminated */
};
typedef enum  Dsi3BusIf_eDiscoveryModeStatus          Dsi3BusIf_eDiscoveryModeStatus_t;
typedef       Dsi3BusIf_eDiscoveryModeStatus_t        Dsi3BusIf_DiscoveryModeStatus_t;    /**<  Data type discovery mode status */
/* *****************************************************************************
 * @brief DSI3 BUS layer error enumerator
 * *****************************************************************************/
#define DSI3BUS_ERROR_AREA_BUS             100u                                            /**< DSI3 bus error area range offset */
#define DSI3BUS_NO_ERROR                     0u                                            /**< DSI3 bus no error value */
#define DSI3_ERROR_AREA_SIZE                32u                                            /**< DSI3 bus error code area size */

/**
 * @brief Error Codes
 */
enum Dsi3BusIf_eErrorCodes
{
  Dsi3BusIf_ERR_STATUS_OK                               = DSI3BUS_NO_ERROR,                     /**<  No error at all. */

  Dsi3BusIf_ERR_INIT                                    = DSI3BUS_ERROR_AREA_BUS + 0,           /**<  Initialization error */
  Dsi3BusIf_ERR_HW_FAIL                                 = DSI3BUS_ERROR_AREA_BUS + 1,           /**<  Hardware failure */
  Dsi3BusIf_ERR_NO_HANDLER                              = DSI3BUS_ERROR_AREA_BUS + 2,           /**<  Missing handler callback */

  Dsi3BusIf_ERR_START_ERR_EVT                           = DSI3BUS_ERROR_AREA_BUS + 3,           /**<  Corrupted or invalid sync byte received */
  
  Dsi3BusIf_ERR_PDCM_ERROR                              = DSI3BUS_ERROR_AREA_BUS + 4,           /**<  Non sync during pdcm detected */
  Dsi3BusIf_ERR_FCC_ERROR                               = DSI3BUS_ERROR_AREA_BUS + 5,           /**<  Received data expose framing error */
  Dsi3BusIf_ERR_DISC_ERROR                              = DSI3BUS_ERROR_AREA_BUS + 6,
  Dsi3BusIf_ERR_BUFFER_ERROR                            = DSI3BUS_ERROR_AREA_BUS + 7,           /**<  Data buffer setup incorrectly */

  Dsi3BusIf_ERR_CRC                                     = DSI3BUS_ERROR_AREA_BUS + 8,           /**<  DSI3 CRC error */
  
  Dsi3BusIf_ERR_TASK_TOO_SLOW                           = DSI3BUS_ERROR_AREA_BUS + 9,           /**<  DSI3 Task error */
  Dsi3BusIf_ERR_SLAVEID_OUT_OF_RANGE                    = DSI3BUS_ERROR_AREA_BUS + 10,          /**<  DSI3 NAD error */
  Dsi3BusIf_ERR_DISC_VERIFY_ERROR                       = DSI3BUS_ERROR_AREA_BUS + 11,          /**< DSI3 DISCovery mode unexpected current detected */
  Dsi3BusIf_ERR_IMPL_ERROR_AREA                         = DSI3BUS_ERROR_AREA_BUS + (DSI3_ERROR_AREA_SIZE/2) /**<  Any additional implementation specific errors start here. */
  
};

typedef enum Dsi3BusIf_eErrorCodes Dsi3BusIf_ErrorCodes_t;

/* ****************************************************************************/
/* **************************** GLOBAL VARIABLES ******************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ********************* EXTERNAL FUNCTIONS / INTERFACE ***********************/
/* ****************************************************************************/

#endif /* DSI3_TYPES_H_ */

/** @} dsi3_Driver_interfaces */
