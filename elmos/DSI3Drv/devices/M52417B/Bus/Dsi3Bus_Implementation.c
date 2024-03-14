/** @addtogroup dsi3_Driver
 * @{ */
/***************************************************************************/
/** @file     Dsi3Bus_Implementation.c
 *
 * @brief     DSI3 Bus layer component for managing the DSI3 hardware module.
 *
 * @purpose   Bus layer implementation for the DSI3 hardware module offering
 *            interface & callback functions for enabling and maintaing 
 *            DSI3 communication for CRM, PDCM and DISCOVERY modes
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
 * @section history_sec Revision History
 * $Id: Dsi3Bus_Implementation.c 430 2019-03-26 10:45:58Z poe $
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who  Ver  Comment
 * -------------------------------------------------------------------
 * 19/03/14 (F) POE  1005 Removed lower and upper boundary checks for CRM response offset during bus initialization.
 * 19/03/11 (F) POE  1004 Added DiscMode software proposal 1 support to DISC mode (ESWDSI3-21).
 * 19/02/25 (B) POE  1011 Fixed DSI3 autosync side effect caused by task clk_1us update;
                          CRM BRCs & non targeted CRMs also trigger the CRMProcessedCallback now.
 * 18/12/04 (F) POE  1010 Added manual start of current measurement during discovery mode to TimerA (E524.17A1)
 * 18/11/13 (B) POE  1009 Added fix implementations for ESWDSI3-16,-17,-18.
 * 18/09/24 (B) POE  1008 Added fix implementation for start of current ramping.
 * 18/09/06 (F) POE  1007 Added bugfix for ESWDSI3-12 & -13.
 * 18/08/21 (F) POE  1006 Added doxygen comments.
 * 18/08/06 (F) POE  1005 Added implementation of ESWDSI3-14.
 * 18/04/23 (F) POE	 1004 Replaced DSI3BUSIMP_TIMER_X_MAX_VALUE with DSI3_TIMERX_MAX_VALUE reference
 * 18/04/18 (F) POE  1003 Removed CRMResponseTimeOffset from BlankingTime calculation.
 * 18/04/17 (F) POE  1002 Added force communication mode update if set next mode is 
 *                        same as current mode to enable cfg reset.
 *                        Split Interface functions into 2 tables, 1 for DSI3
 *                        communication and 1 for extended configurations.
 *                        Added GetSubInterface interface function.
 *                        Added a bool return value to a setter functions.
 *                        Added IF fncs for updated CRM & PDCM FCC blanking time.
 *                        Removed IF fncs for updating delayed error processing configuration.
 * 18/04/06 (F) POE  1001 Added check during PDCM irq handling for TimerC configuration value and
 *                        switches blanking off if configured value is < current DSI3 timer value.
 * 18/03/23 (F) POE  1000 initial version
 * -------------------------------------------------------------------
 * @endverbatim
 *
 * @creator      POE
 * @created      2018/03/23
 *
 * @project      524.17
 * @requested    ELMOS
 * @inspector    -
 * @verification -
 * @version      $Revision: 430 $
 *
 *
 * $State: Exp $
 * $Author: poe $
 *
 * Additional markers:
 *
 *******************************************************************************/

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "Dsi3Bus_Implementation.h"
#include "def_dsi3.h"
#include "el_helper.h"
/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

#define BUS_LAYER


/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ****************************************************************************/
/* Internal  structure for DSI3 communication steering */
struct Dsi3Bus_sDsi3Steering
{
  /*
   * Actual and upcoming communication mode
   * The upcoming communication mode may be set while reacting on a command
   * or synchronization signal and will be active when finishing response.
   */
  Dsi3BusIf_eCommunicationMode_t                CurrentCommunicationMode;       /**< Currently active DSI3 communication mode (CRM/PDCM/DISC) */
  Dsi3BusIf_eCommunicationMode_t                NextCommunicationMode;          /**< Next DSI3 communication mode assignment */
  Dsi3BusIf_eCommunicationMode_t                DefaultCommunicationMode;       /**< Default DSI3 communication mode */
  Dsi3BusIf_Bool_t                              ForceCommunicationModeUpdate;   /**< Forces an update to the next communication mode, even it is the same */
  Dsi3BusIf_Bool_t                              HardwareAddsCRC;                /**< TRUE - hardware adds crc automatically to transmission */
  Dsi3BusIf_ClkDiv_t                            Cfg1usClock;                    /**< Register configuration preset for 1us DSI3 clock */
  Dsi3BusIf_ChipTime_t                          ChipTime;                       /**< DSI3 Response communication chip time select */
  Dsi3BusIf_eState_t                            Dsi3State;                      /**< Bus layer state machine */
  Dsi3BusIf_Data_t                              KeepAliveCounter;               /**< KAC - if supported */
  Dsi3BusIf_DWordData_t                         DataCounter;                    /**< Counter for bytes still to be send/received for current data transfer on DSI3 */
  Dsi3BusIf_Bool_t                              BusActivityFlag;                /**< Indicates if there was active communication on the bus */
};

typedef struct  Dsi3Bus_sDsi3Steering           Dsi3Bus_Dsi3Steering_t;         /**<  Typedef to Dsi3Bus_sDsi3Steering. */
typedef         Dsi3Bus_Dsi3Steering_t*         Dsi3Bus_pDsi3Steering_t;        /**<  Typedef of pointer to Dsi3Bus_Dsi3Steering_t. */
typedef const   Dsi3Bus_Dsi3Steering_t*         Dsi3Bus_cpDsi3Steering_t;       /**<  Typedef of pointer to Dsi3Bus_Dsi3Steering_t. */

/* ****************************************************************************
 * Data structure to store information about PDCM data transfer               *
 * ****************************************************************************/
struct Dsi3Bus_sPdcmSteering                                                    /**< PDCM communication flow control */
{
  Dsi3BusIf_DWordData_t                         CommandCount;                   /**< From driver: PDCM command count managed by DSI3 Driver */
  Dsi3BusIf_DWordData_t                         ResponseCount;                  /**< From driver: PDCM response count managed by DSI3 Driver */
  Dsi3BusIf_WordData_t                          TimeSlot;                       /**< To driver: Time slot when to send PDCM data in TDMA mode */
  Dsi3BusIf_WordData_t                          BufferSize;                     /**< From driver: Number of bytes available */
  Dsi3BusIf_ByteData_t                          MsgLen;                         /**< To driver: number of bytes to send */
  Dsi3BusIf_Time_t                              PdcmStartSlotOffset;            /**< Time offset of the first msg slot in pdcm mode (default: 50us) */
  Dsi3BusIf_Time_t                              PdcmResponseDuration;           /**< Overall pdcm response time frame */
  Dsi3BusIf_Time_t                              PdcmSlotDuration;               /**< Time duration of single pdcm slot */
  Dsi3BusIf_Time_t                              PdcmFCCBlankingTimeOffset;      /**< Time offset for fcc blanking after sync has been received */
  Dsi3BusIf_Bool_t                              DelayErrEvtHandling;            /**< If TRUE, next PdcmErrEvt will be buffered in PdcmErrEvtOccurred and
                                                                                     evaluated on the next CRM based error */
  Dsi3BusIf_Bool_t                              ErrEvtOccured;                  /**< Is set to true on PDCM Err evt occurence */
} ;

typedef struct  Dsi3Bus_sPdcmSteering           Dsi3Bus_PdcmSteering_t;         /**<  Typedef for Dsi3Bus_sPdcmSteering. */
typedef         Dsi3Bus_PdcmSteering_t*         Dsi3Bus_pPdcmSteering_t;        /**<  Typedef of pointer to Dsi3Bus_PdcmSteering_t. */
typedef const   Dsi3Bus_PdcmSteering_t*         Dsi3Bus_cpPdcmSteering_t;       /**<  Typedef of pointer to Dsi3Bus_PdcmSteering_t. */


struct Dsi3Bus_sPdcmRuntimeData                                                 /**< PDCM runtime data containing steering and response data buffer */
{
  Dsi3Bus_PdcmSteering_t                        Steering;                       /**< PDCM steering data */
  Dsi3BusIf_Data_t*                             ResponseBuffer;                 /**< PDCM response buffer */
} ;

typedef struct Dsi3Bus_sPdcmRuntimeData         Dsi3Bus_PdcmRuntimeData_t;      /**<  Typedef for Dsi3Bus_sPdcmRuntimeData. */
typedef        Dsi3Bus_PdcmRuntimeData_t*       Dsi3Bus_pPdcmRuntimeData_t;     /**<  Typedef of pointer to Dsi3Bus_PdcmRuntimeData_t. */
typedef const  Dsi3Bus_PdcmRuntimeData_t*       Dsi3Bus_cpPddmRuntimeData_t;    /**<  Typedef of pointer to Dsi3Bus_PdcmRuntimeData_t. */



struct Dsi3Bus_sCrmSteering                                                     /**< CRM communication flow control */
{
  Dsi3BusIf_Time_t                              CrmResponseTimeOffset;          /**< Time offset of the crm response msg */
  Dsi3BusIf_Time_t                              CrmFCCBlankingTimeOffset;       /**< Time offset for fcc blanking after msg has been received */
  Dsi3BusIf_Bool_t                              SkipCurrentCRMCommand;          /**< TRUE - current CRM cmd is ignored */
};

typedef struct  Dsi3Bus_sCrmSteering            Dsi3Bus_CrmSteering_t;          /**<  Typedef for Dsi3Bus_sCrmSteering. */
typedef         Dsi3Bus_CrmSteering_t*          Dsi3Bus_pCrmSteering_t;         /**<  Typedef of pointer to Dsi3Bus_CrmSteering_t. */
typedef const   Dsi3Bus_CrmSteering_t*          Dsi3Bus_cpCrmSteering_t;        /**<  Typedef of pointer to Dsi3Bus_CrmSteering_t. */


struct Dsi3Bus_sCrmRuntimeData                                                  /**< CRM runtime data containing steering and command/response data buffers */
{
  Dsi3Bus_CrmSteering_t                         Steering;                       /**< CRM steering data */
  Dsi3Bus_CrmCommand_t                          CommandBuffer;                  /**< CRM Command buffer */
  Dsi3Bus_CrmResponse_t                         ResponseBuffer;                 /**< CRM Response buffer */
};

typedef struct Dsi3Bus_sCrmRuntimeData          Dsi3Bus_CrmRuntimeData_t;     /**<  Typedef for Dsi3Bus_sCrmRuntimeData. */
typedef        Dsi3Bus_CrmRuntimeData_t*        Dsi3Bus_pCrmRuntimeData_t;    /**<  Typedef of pointer to Dsi3Bus_CrmRuntimeData_t. */
typedef const  Dsi3Bus_CrmRuntimeData_t*        Dsi3Bus_cpCrmRuntimeData_t;   /**<  Typedef of pointer to Dsi3Bus_CrmRuntimeData_t. */


struct Dsi3Bus_sDiscSteering                                                    /**< DISC communication flow control */
{
  Dsi3BusIf_Time_t                              PeriodLength;                   /**< Length of the period between two discovery pulses (us) */
  Dsi3BusIf_Time_t                              RampOnDelay;                    /**< Duration in us before starting the current ramping (us) */
  Dsi3BusIf_Time_t                              RampOnDuration;                 /**< Length of the current ramping on duration (us) */
  Dsi3BusIf_Bool_t                              DelayErrEvtHandling;            /**< If TRUE, next DiscErrEvt will be buffered in DiscErrEvtOccurred and
                                                                                     evaluated on the next CRM based error */
  Dsi3BusIf_Bool_t                              ErrEvtOccured;                  /**< Is set to true on DISC Err evt occurence */
  /* --> 19-01-09, poe: ESWDSI3-21, 
   * Added new status flag for address status tracking */
  Dsi3BusIf_Bool_t                              isAddressed;                    /**< if TRUE, the slave has been addressed during the current discovery mode
	                                                                                     auto-addressing procedure, FALSE else */
  /* --> 19-01-09, poe: ESWDSI3-21 */																						 
  /* --> 2018-08-06, poe: ESWDSI3-14
   * Added to track DiscCurr evt occurences.
   */
  Dsi3BusIf_Bool_t                              DiscCurrEvtOccured;             /**< Is set to true on DISC Curr evt occurence during ramping duration */
  /* --> 2018-08-06, poe: ESWDSI3-14 */
};

typedef struct  Dsi3Bus_sDiscSteering           Dsi3Bus_DiscSteering_t;       /**<  Typedef for Dsi3Bus_sDiscSteering. */
typedef         Dsi3Bus_DiscSteering_t*         Dsi3Bus_pDiscSteering_t;      /**<  Typedef of pointer to Dsi3Bus_DiscSteering_t. */
typedef const   Dsi3Bus_DiscSteering_t*         Dsi3Bus_cpDiscSteering_t;     /**<  Typedef of pointer to Dsi3Bus_DiscSteering_t. */


struct Dsi3Bus_sDiscRuntimeData                                                 /**< DISC runtime data containing steering and command/response data buffers */
{
  Dsi3Bus_DiscSteering_t                        Steering;
  Dsi3BusIf_ByteData_t                          PulseCount;                     /**< Number of discovery pulses since last change to DISC mode */
};

typedef struct Dsi3Bus_sDiscRuntimeData         Dsi3Bus_DiscRuntimeData_t;      /**<  Typedef for Dsi3Bus_sDiscRuntimeData. */
typedef        Dsi3Bus_DiscRuntimeData_t*       Dsi3Bus_pDiscRuntimeData_t;     /**<  Typedef of pointer to Dsi3Bus_DiscRuntimeData_t. */
typedef const  Dsi3Bus_DiscRuntimeData_t*       Dsi3Bus_cpDiscRuntimeData_t;    /**<  Typedef of pointer to Dsi3Bus_DiscRuntimeData_t. */




struct loc_sDsi3EnvironmentData                                                                 /**< DSI3 bus layer environment data */
{
  dsi3_sInterruptEnvironmentData_t      IrqEnvData;                                             /**< DSI3 irq environment data */
  Dsi3BusIf_cpCallbackFunctions_t       Callbacks[DSI3_MAX_NUMBER_OF_CALLBACK_TABLES];          /**< The set of callbacks associated with this genericBusEnvData instance */
  Dsi3BusIf_pGenericCbCtxData_t         CallbackCtxData[DSI3_MAX_NUMBER_OF_CALLBACK_TABLES];
  
  Dsi3BusIf_SlaveID_t                   CurrentSlaveID;                                         /**< Current NAD */ 
  Dsi3BusIf_SlaveID_t                   NewSlaveID;                                             /**< Appointed NAD */
  Dsi3BusIf_SlaveID_t                   MaxSlaveID;                                             /**< Maximal numbers of allowed slaves ( <= 15) */
  
  Dsi3Bus_Dsi3Steering_t                Steering;                                               /**< DSI3 mode control */
  Dsi3Bus_CrmRuntimeData_t              CrmRuntimeData;                                         /**< CRM I/O buffer */
  Dsi3Bus_PdcmRuntimeData_t             PdcmRuntimeData;                                        /**< PDCM In buffer, control data */
  Dsi3Bus_DiscRuntimeData_t             DiscRuntimeData;                                        /**< DISC start NAD offset, AA orientation, pulse count */
  
  Dsi3BusIf_CRMCallbackFun_t            Crm_CmdFrmDescLst[DSI3_CRM_NUMBER_OF_COMMANDS];         /**< Mapping table for CRM cmd ID handler cb functions */
  Dsi3BusIf_pGenericCbCtxData_t         Crm_CmdCbCtxData[DSI3_CRM_NUMBER_OF_COMMANDS];          /**< Mapping table for CRM cmd ID handler specific context data */
  
  Dsi3BusIf_PDCMCallbackFun_t           Pdcm_CmdFrmDesc;                                        /**< Mapping table for PDCM handler cb functions */
  Dsi3BusIf_pGenericCbCtxData_t         Pdcm_CmdCbCtxData;                                      /**< Mapping table for PDCM handler specific context data */
};

typedef struct loc_sDsi3EnvironmentData    loc_sDsi3EnvironmentData_t;                          /**<  Typedef for loc_sDsi3EnvironmentData. */
typedef        loc_sDsi3EnvironmentData_t* loc_pDsi3EnvironmentData_t;                          /**<  Typedef of pointer to loc_sDsi3EnvironmentData_t. */
typedef const  loc_sDsi3EnvironmentData_t* loc_cpDsi3EnvironmentData_t;                         /**<  Typedef of pointer to loc_sDsi3EnvironmentData_t. */

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/
/* Sets the interface functions available to the upper application layers */
/**< @brief DSI3 Bus Interface-Functions mapping */
const Dsi3BusIf_sInterfaceFunctions_t Dsi3BusImp_InterfaceFunctions =                           
{
  .InterfaceVersion             = DSI3BUS_INTERFACE_MODULE_API_VERSION,
  .Initialization               = &Dsi3BusImp_Initialization,
  .GetSubInterface              = &Dsi3BusImp_GetSubInterface,
  .Shutdown                     = &Dsi3BusImp_Shutdown,
  .GetTimestamp                 = &Dsi3BusImp_GetTimestamp,
  .UpdateDeviceAddress          = &Dsi3BusImp_UpdateDeviceAddress,
  .UpdateChipTime               = &Dsi3BusImp_UpdateChipTime,
  .ChangeMode                   = &Dsi3BusImp_ChangeCommunicationMode,
  .UpdateCRMResponseTimeOffset  = &Dsi3BusImp_UpdateCRMResponseTimeOffset,
  .UpdatePDCMStartSlotOffset    = &Dsi3BusImp_UpdatePDCMStartSlotOffset,
  .UpdatePDCMSlotDuration       = &Dsi3BusImp_UpdatePDCMSlotDuration,
  .UpdatePDCMResponseDuration   = &Dsi3BusImp_UpdatePDCMResponseDuration,
  .RegisterCrmCb                = &Dsi3BusImp_RegisterCrmCallbackFunction,
  .RegisterPdcmCb               = &Dsi3BusImp_RegisterPdcmCallbackFunction,
  .Task                         = &Dsi3BusImp_Task,
  .CheckBusActivity             = &Dsi3BusImp_CheckBusActivityFun,
  .AppendCallbackTable          = &Dsi3BusImp_AppendCallbackTableFun,
  .RemoveCallbackTable          = &Dsi3BusImp_RemoveCallbackTableFun,
};

/**< @brief DSI3 hardware module Interface-Functions mapping */       
const Dsi3HwModIf_InterfaceFunctions_t Dsi3HardwareModuleImp_InterfaceFunctions =             
{
  .InterfaceVersion               = DSI3MOD_INTERFACE_MODULE_API_VERSION,
  .Get1usClockCfg                 = &Dsi3BusImp_Get1usClockCfg,
  .Set1usClockCfg                 = &Dsi3BusImp_Set1usClockCfg,
  .UpdateCRMFCCBlankingTimeOffset = &Dsi3BusImp_UpdateCRMFCCBlankingTimeOffset,
  .UpdatePDCMFCCBlankingTimeOffset= &Dsi3BusImp_UpdatePDCMFCCBlankingTimeOffset,
  .GetCRMSyncCount                = &Dsi3BusImp_GetCRMSyncCount,
  .GetPDCMMeasuredPeriodDuration  = &Dsi3BusImp_GetPDCMMeasuredPeriodDuration,
};

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ******************** FORWARD DECLARATIONS / PROTOTYPES *********************/
/* ****************************************************************************/

/* DSI3 valid CMD interrupt service routine - slaveId prefilter inactive. */
BUS_LAYER void Dsi3BusImp_InterruptHandler_CmdEvt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);


/* DSI3 valid CMD interrupt service routine - slaveId prefilter active. */
BUS_LAYER void Dsi3BusImp_InterruptHandler_CmdEvt_Prefiltered(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* DSI3 DISC evt interrupt service routine. */
BUS_LAYER void Dsi3BusImp_InterruptHandler_DiscEvt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);


/* DSI3 CRC error interrupt service routine. */
BUS_LAYER void Dsi3BusImp_InterruptHandler_CrcErrEvt  (dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);


/* DSI3 FCC error interrupt service routine. */
BUS_LAYER void Dsi3BusImp_InterruptHandler_FccErrEvt  (dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);


/* DSI3 Start error interrupt service routine. */
BUS_LAYER void Dsi3BusImp_InterruptHandler_StartErrEvt  (dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);


/* DSI3 PDCM evt interrupt service routine. */
BUS_LAYER void Dsi3BusImp_InterruptHandler_PdcmEvt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);


/* DSI3 PDCM err interrupt service routine. */
BUS_LAYER void Dsi3BusImp_InterruptHandler_PdcmErrEvt  (dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);


/* DSI3 DISC error interrupt service routine. */
BUS_LAYER void Dsi3BusImp_InterruptHandler_DiscErrEvt  (dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);


/*  DSI3 RCC finish interrupt service routine. */
BUS_LAYER void Dsi3BusImp_InterruptHandler_RccFinish  (dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* DSI3 TimerA interrupt service routine. */
BUS_LAYER void Dsi3BusImp_InterruptHandler_TimerA_Evt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* DSI3 TimerB interrupt service routine. */
BUS_LAYER void Dsi3BusImp_InterruptHandler_TimerB_Evt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* --> 2018-08-06, poe: ESWDSI3-14
 * Added to handle DiscCurr irq event.
 */
/* DSI3 Discovery current compare interrupt service routine. */
static BUS_LAYER void Dsi3BusImp_InterruptHandler_DiscCurrEvt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);
/* --> 2018-08-06, poe: ESWDSI3-14 */

/* Enable crm mode */
BUS_LAYER void loc_EnableCrm(loc_pDsi3EnvironmentData_t busEnvData);
/* Enable pdcm mode */
BUS_LAYER void loc_EnablePdcm(loc_pDsi3EnvironmentData_t busEnvData);
/* Enable discovery mode */
BUS_LAYER void loc_EnableDisc(loc_pDsi3EnvironmentData_t busEnvData);

/* Reset CRM mode */
BUS_LAYER void loc_ResetCrm(loc_pDsi3EnvironmentData_t busEnvData);
/* Reset PDCM mode */
BUS_LAYER void loc_ResetPdcm(loc_pDsi3EnvironmentData_t busEnvData);


/* Propagate error to upper application level */
BUS_LAYER void loc_CallBusErrorCallback(const loc_pDsi3EnvironmentData_t busEnvData, Dsi3BusIf_Error_t error);
/* Propagate the receive of an PDCM sync pulse */
//BUS_LAYER void loc_CallPdcmEvtCallback(const loc_pDsi3EnvironmentData_t busEnvData, Dsi3BusIf_Time_t duration);
/* feddback that the dsi3 has been changed */
BUS_LAYER void loc_CallModeChangedCallback(const loc_pDsi3EnvironmentData_t busEnvData, Dsi3BusIf_eCommunicationMode_t currentMode);
/* feedback that the crm cmd has been successfully processed */
BUS_LAYER void loc_CallCrmProcessedCallback(loc_pDsi3EnvironmentData_t busEnvData);
/* feedback that the pdcm response has been successfully processed */
BUS_LAYER void loc_CallPdcmProcessedCallback(loc_pDsi3EnvironmentData_t busEnvData);
/* feedback that the the discovery mode status has changed */
BUS_LAYER void loc_CallDiscProcessedCallback(loc_pDsi3EnvironmentData_t busEnvData, Dsi3BusIf_DiscoveryModeStatus_t currentStatus);


/* Prepares the PDCM buffer for the sync event */
BUS_LAYER void loc_Dsi3BusImp_PreparePDCMBuffer(loc_pDsi3EnvironmentData_t busEnvData);
/* Switch DSI3 commState to NextState and reInit  - call ModeChangeCb if needed */
BUS_LAYER void loc_Dsi3BusImp_PrepareNextCommState(loc_pDsi3EnvironmentData_t busEnvData, bool_t doChangeCallback);


/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/*************************************************************************** 
 ************************** INTERRUPT HANDLER ******************************
 ***************************************************************************/

/* *************************************************************************//**
 * @internal
 * @brief
 * DSI3 valid CMD interrupt service routine
 *
 * This interrupt is triggered on receiving a valid cmd sequence
 * and is currently only used for CRM handling. 
 * The CRM response is built here.
 *
 * @param   sno                 module interrupt number
 * @param   genericCbCtxData    generic context pointer, should point to bus environment data
 * @return  none
 *
 * @image html Dsi3BusImp_InterruptHandler_CmdEvt.png "Activity chart: Interrupt Handler Command Event"
 * @image latex Dsi3BusImp_InterruptHandler_CmdEvt.png "Activity chart: Interrupt Handler Command Event" 
 * ****************************************************************************/
BUS_LAYER void Dsi3BusImp_InterruptHandler_CmdEvt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  Dsi3BusIf_Length_t const loc_Dsi3Drv_CRMResponseBufferSize = sizeof(Dsi3Bus_CrmResponse_t);
  
  /* Casting unused function paramteres to void to prevent compiler warning */
  (void)sno;
      
  if (DSI3_NULL != genericCbCtxData)
  {
    /* Retrieve bus env data */
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericCbCtxData;
      
    /* Retrieve callback function to serve the command */
    Dsi3BusIf_CRMCallbackFun_t crmCallbackFun;
    /* Set default response behaviour: ignore */
    Dsi3BusIf_CmdIdAction_t cbStatus = Dsi3BusIf_eCMDACT_IGNORE;

    /* Read CRM command from hardware */
    /*  
    * Exception:
    * Msg(7:0402) [U] 'busEnvData->CrmRuntimeData.CommandBuffer.Value' is 
    * modified and accessed between sequence points - evaluation order unspecified.
    *
    * Circumstances and justification:
    * The macro DSI3_CTRL_FCC_CMD_READ provides a read and write access to 
    * CrmRuntimeData.CommandBuffer.Value within one statement. If the macro
    * parameter would be an expression this may lead to undefined behaviour. 
    * But with passing a symbol the macros has been proved to work correctly.
    * 
    * Potential consequences:
    * DSI3 communication would not work, as the command would be read out
    * wrongly.
    *
    * Alternative safety assurance:
    * Tesing. A malfunction of this macro would completly block DSI3 
    * communication which will be found out very easily.
    */
    // PRQA S 0402 1
    DSI3_CTRL_FCC_CMD_READ(busEnvData->CrmRuntimeData.CommandBuffer.Value);

    /* Retrieve callback function to serve the command */
    crmCallbackFun 	= busEnvData->Crm_CmdFrmDescLst[busEnvData->CrmRuntimeData.CommandBuffer.Fields.Command];
      
    /* Check if the function pointer is valid */
    if (DSI3_NULL != crmCallbackFun)
    {
      /* Call cmdID handler function  - will determine if a response needs to be send, or not */
       cbStatus = crmCallbackFun(busEnvData, &busEnvData->CrmRuntimeData.CommandBuffer,&busEnvData->CrmRuntimeData.ResponseBuffer, busEnvData->CurrentSlaveID, busEnvData->Crm_CmdCbCtxData[busEnvData->CrmRuntimeData.CommandBuffer.Fields.Command]);
    }
    else
    {
      /* No cb defined -> no response */
      /* Process Error callback */
      loc_CallBusErrorCallback(busEnvData, (Dsi3BusIf_Error_t) Dsi3BusIf_ERR_NO_HANDLER);
        
    }
                  
    /* Check if an error occured during cb fun or if no response is needed  */
    if (Dsi3BusIf_eCMDACT_RESPONSE == cbStatus)
    {          
     /*
      * Prepare DMA for answering
      *
      * CRC will be handled by hardware, thus frame length has to be reduced by one byte
      */
        
      /* 
      * Msg(2:0306) [I] Cast between a pointer to object and an integral type.
      *
      * According to QA-C help "this type of operation is not uncommon in embedded 
      * software applications where memory mapped I/O ports must be addressed."
      */  
      // PRQA S 0306 1 
      DSI3_CTRL_DMA_BASE_ADDR_SET(((uintptr_t)&busEnvData->CrmRuntimeData.ResponseBuffer + ((uintptr_t) loc_Dsi3Drv_CRMResponseBufferSize -(uintptr_t) busEnvData->Steering.HardwareAddsCRC)));
      DSI3_CTRL_BUFFER_LENGTH_SET((uint16_t) ((uint32_t) loc_Dsi3Drv_CRMResponseBufferSize -(uint16_t) busEnvData->Steering.HardwareAddsCRC));
              

      /* Clear rcc finish irq */
      DSI3_CTRL_IRQ_CLEAR(dsi3_IRQ_RCC_FINISH);
      
      /* Enable rcc finish irq */
      DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_RCC_FINISH);
              
      /* Enable dsi auto response */
      DSI3_CTRL_CONFIG_AUTORESP_ENABLE();
              
      /* Switch driver internal state */
      busEnvData->Steering.Dsi3State = Dsi3BusIf_eSTATE_ANSWERING;
                                
      /*
       * Driver is waiting for rcc finish interrupt 
       */
      }
      else
      {
        /* Send no response! */
          /* --> 2019-02-25, poe: ESWDSI3-22
           * Switch to response processed mode, to enable calling of
           * CRMProcessedCallback after receiving a valid CRM -
           * independently whether it was a broadcast or addressed to
           * a different slave.
           */
          busEnvData->Steering.Dsi3State = Dsi3BusIf_eSTATE_RESPONSE_PROCESSED;
          /* --> 2019-02-25, poe: ESWDSI3-22 */
        /* Set bus activity flag */
        busEnvData->Steering.BusActivityFlag = TRUE;
                       
      }

      if (busEnvData->MaxSlaveID < busEnvData->CrmRuntimeData.CommandBuffer.Fields.PhysicalAddress)
      {
        /* Addressed NAD is out of predefined range */
        /* Process Error callback */
        loc_CallBusErrorCallback(busEnvData, (Dsi3BusIf_Error_t) Dsi3BusIf_ERR_SLAVEID_OUT_OF_RANGE);
      }
  
      busEnvData->PdcmRuntimeData.Steering.ErrEvtOccured              = FALSE;
      busEnvData->DiscRuntimeData.Steering.ErrEvtOccured              = FALSE;

  }
  else{/* Error: busEnvData is not initialized!*/}
  
  return;
}

/* *************************************************************************//**
 * @internal
 * @brief
 * DSI3 valid CMD interrupt service routine - slaveId prefilter active.
 *
 * This interrupt is triggered on receiving a valid cmd sequence
 * and is currently only used for CRM handling. It prefilters incoming
 * CRM messages for current assigned slave and/or broadcast id.
 * The CRM response is built here.
 *
 * @param   sno                 module interrupt number
 * @param   genericCbCtxData    generic context pointer, should point to bus environment data
 * @return  none
 *
 * @image html Dsi3BusImp_InterruptHandler_CmdEvt_Prefiltered.png "Activity chart: Interrupt Handler Command Event"
 * @image latex Dsi3BusImp_InterruptHandler_CmdEvt_Prefiltered.png "Activity chart: Interrupt Handler Command Event"
 * ****************************************************************************/
BUS_LAYER void Dsi3BusImp_InterruptHandler_CmdEvt_Prefiltered(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* Casting unused function paramteres to void to prevent compiler warning */
  (void)sno; 
   
  if (DSI3_NULL != genericCbCtxData)
  {
    Dsi3BusIf_Length_t const loc_Dsi3Drv_CRMResponseBufferSize = sizeof(Dsi3Bus_CrmResponse_t);
    
    /* Retrieve bus env data */
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericCbCtxData;
    
    /* Retrieve callback function to serve the command */
    Dsi3BusIf_CRMCallbackFun_t crmCallbackFun;
    /* Set default response behaviour: ignore */
    Dsi3BusIf_CmdIdAction_t cbStatus = Dsi3BusIf_eCMDACT_IGNORE;

    /*  
    * Exception:
    * Msg(7:0402) [U] 'busEnvData->CrmRuntimeData.CommandBuffer.Value' is 
    * modified and accessed between sequence points - evaluation order unspecified.
    *
    * Circumstances and justification:
    * The macro DSI3_CTRL_FCC_CMD_READ provides a read and write access to 
    * CrmRuntimeData.CommandBuffer.Value within one statement. If the macro
    * parameter would be an expression this may lead to undefined behaviour. 
    * But with passing a symbol the macros has been proved to work correctly.
    * 
    * Potential consequences:
    * DSI3 communication would not work, as the command would be read out
    * wrongly.
    *
    * Alternative safety assurance:
    * Tesing. A malfunction of this macro would completly block DSI3 
    * communication which will be found out very easily.
    */
    // PRQA S 0402 1
    DSI3_CTRL_FCC_CMD_READ(busEnvData->CrmRuntimeData.CommandBuffer.Value);
 
    /* Check if received cmd is a broadcast command or if it is addressing this node */
    if ((DSI3_NAD_BROADCAST == busEnvData->CrmRuntimeData.CommandBuffer.Fields.PhysicalAddress) || (busEnvData->CurrentSlaveID == busEnvData->CrmRuntimeData.CommandBuffer.Fields.PhysicalAddress))
    {         
      /* Retrieve callback function to serve the command */
      crmCallbackFun 	= busEnvData->Crm_CmdFrmDescLst[busEnvData->CrmRuntimeData.CommandBuffer.Fields.Command];
        
      /* Check if the function pointer is valid */
      if (DSI3_NULL != crmCallbackFun)
      {
        /* Call cmdID handler function  - will determine if a response needs to be send, or not */
         cbStatus = crmCallbackFun(busEnvData, &busEnvData->CrmRuntimeData.CommandBuffer,&busEnvData->CrmRuntimeData.ResponseBuffer, busEnvData->CurrentSlaveID, busEnvData->Crm_CmdCbCtxData[busEnvData->CrmRuntimeData.CommandBuffer.Fields.Command]);
      }
      else
      {
        /* No cb defined -> no response */
        /* Process Error callback */
        loc_CallBusErrorCallback(busEnvData, (Dsi3BusIf_Error_t) Dsi3BusIf_ERR_NO_HANDLER);  
      }
                  
      /* Check if an error occured during cb fun or if no response is needed  */
      if (Dsi3BusIf_eCMDACT_RESPONSE == cbStatus)
      {   
        /*
        * Prepare DMA for answering
        *
        * CRC will be handled by hardware, thus frame length has to be reduced by one byte
        */
          
        /* 
        * Msg(2:0306) [I] Cast between a pointer to object and an integral type.
        *
        * According to QA-C help "this type of operation is not uncommon in embedded 
        * software applications where memory mapped I/O ports must be addressed."
        */  
        // PRQA S 0306 1 
        DSI3_CTRL_DMA_BASE_ADDR_SET(((uintptr_t)&busEnvData->CrmRuntimeData.ResponseBuffer + ((uintptr_t) loc_Dsi3Drv_CRMResponseBufferSize -(uintptr_t) busEnvData->Steering.HardwareAddsCRC)));
        DSI3_CTRL_BUFFER_LENGTH_SET((uint16_t) ((uint32_t) loc_Dsi3Drv_CRMResponseBufferSize -(uint16_t) busEnvData->Steering.HardwareAddsCRC));
                
        /* Clear rcc finish irq */
        DSI3_CTRL_IRQ_CLEAR(dsi3_IRQ_RCC_FINISH);

        /* Enable rcc finish irq */
        DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_RCC_FINISH);
                
        /* Enable dsi auto response */
        DSI3_CTRL_CONFIG_AUTORESP_ENABLE();
                
        /* Switch driver internal state */
        busEnvData->Steering.Dsi3State = Dsi3BusIf_eSTATE_ANSWERING;
                                
        /*
         * Driver is waiting for rcc finish interrupt 
         */
        }
        else
        {
          /* Send no response! */ 
          /* --> 2019-02-25, poe: ESWDSI3-22
           * Switch to response processed mode, to enable calling of
           * CRMProcessedCallback after receiving a valid CRM -
           * even if not response was triggered.
           */
          busEnvData->Steering.Dsi3State = Dsi3BusIf_eSTATE_RESPONSE_PROCESSED;
          /* --> 2019-02-25, poe: ESWDSI3-22 */
          /* Set bus activity flag */
          busEnvData->Steering.BusActivityFlag = TRUE;
        }
      }
    else
    {
      /* --> 2019-02-25, poe: ESWDSI3-22
       * Switch to response processed mode, to enable calling of
       * CRMProcessedCallback after receiving a valid CRM -
       * if not addressed to current slave.
       */
       busEnvData->Steering.Dsi3State = Dsi3BusIf_eSTATE_RESPONSE_PROCESSED;
       /* --> 2019-02-25, poe: ESWDSI3-22 */
      /* Set bus activity flag */
      busEnvData->Steering.BusActivityFlag = TRUE;
      if (busEnvData->MaxSlaveID < busEnvData->CrmRuntimeData.CommandBuffer.Fields.PhysicalAddress)
      {
        /* Addressed NAD is out of predefined range */
        /* Process Error callback */
        loc_CallBusErrorCallback(busEnvData, (Dsi3BusIf_Error_t) Dsi3BusIf_ERR_SLAVEID_OUT_OF_RANGE);
      }     
    }        
      busEnvData->PdcmRuntimeData.Steering.ErrEvtOccured              = FALSE;
      busEnvData->DiscRuntimeData.Steering.ErrEvtOccured              = FALSE;
  }
  else{/* Error: busEnvData is not initialized!*/}

  return;
}




/* *************************************************************************//**
 * @internal
 * @brief
 * DSI3 DISC evt interrupt service routine
 *
 * @param   sno                 module interrupt number
 * @param   genericCbCtxData    generic context pointer, should point to bus environment data
 * @return  none
 *
 * @image html Dsi3BusImp_InterruptHandler_DiscEvt.png "Activity chart: Interrupt Handler Discovery Event"
 * @image latex Dsi3BusImp_InterruptHandler_DiscEvt.png "Activity chart: Interrupt Handler Discovery Event"
 * ****************************************************************************/
BUS_LAYER void Dsi3BusImp_InterruptHandler_DiscEvt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{    
  /* Casting unused function paramteres to void to prevent compiler warning */
  (void)sno;  
  
  if (DSI3_NULL != genericCbCtxData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericCbCtxData;
    
    /* Set bus activity flag */
    busEnvData->Steering.BusActivityFlag = TRUE;
    
    /* Increment Discovery pulse count */
    busEnvData->DiscRuntimeData.PulseCount++;
    
  }
  else{ /* Error: EnvironmentData not initialized! */ }
  return;
}


/* ***************************************************************************//**
 * @internal
 * @brief
 * DSI3 CRC error interrupt service routine
 *
 * @param   sno                 module interrupt number
 * @param   genericCbCtxData    generic context pointer, should point to bus environment data
 * @return  none
 * @image html Dsi3BusImp_InterruptHandler_CrcErrEvt.png "Activity chart: Interrupt Handler Discovery Event"
 * @image latex Dsi3BusImp_InterruptHandler_CrcErrEvt.png "Activity chart: Interrupt Handler Discovery Event"
 * ****************************************************************************/
BUS_LAYER void Dsi3BusImp_InterruptHandler_CrcErrEvt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* Casting unused function paramteres to void to prevent compiler warning */
  (void)sno;
  
  if (DSI3_NULL != genericCbCtxData)
  {
    /* Abort any ongoing fcc activity */
    DSI3_CTRL_STATUS_FCC_ABORT();
  
    /* Abort any ongoing rcc activity */
    DSI3_CTRL_STATUS_RCC_ABORT();
      
    /* Stop dsi3 timer */
    DSI3_CTRL_STATUS_TIMER_RESET();
    
    /* Stop fcc blanking */
    DSI3_CTRL_STATUS_BLANKING_OFF();
    
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericCbCtxData;
    
    /* Set bus activity flag */
    busEnvData->Steering.BusActivityFlag = TRUE;

    /* Process Error callback */
    loc_CallBusErrorCallback(busEnvData, (Dsi3BusIf_Error_t) Dsi3BusIf_ERR_CRC);
    
    /* Clear buffered error events and delay flags. */      
    busEnvData->PdcmRuntimeData.Steering.ErrEvtOccured              = FALSE;
    busEnvData->DiscRuntimeData.Steering.ErrEvtOccured              = FALSE;
  }
  else{ /* Error: EnvironmentData not initialized! */ }

  return;
}


/* *************************************************************************//**
 * @internal
 * @brief
 * DSI3 FCC error interrupt service routine
 *
 * @param   sno                 module interrupt number
 * @param   genericCbCtxData    generic context pointer, should point to bus environment data
 * @return  none
 *
 * @image html Dsi3BusImp_InterruptHandler_FccErrEvt.png "Activity chart: Interrupt Handler Fcc Error Event"
 * @image latex Dsi3BusImp_InterruptHandler_FccErrEvt.png "Activity chart: Interrupt Handler Fcc Error Event"
 * ****************************************************************************/
BUS_LAYER void Dsi3BusImp_InterruptHandler_FccErrEvt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{ 
  /* Casting unused function paramteres to void to prevent compiler warning */
  (void)sno;
 
  if (DSI3_NULL != genericCbCtxData)
  { 
    /* Abort any ongoing fcc activity */
    DSI3_CTRL_STATUS_FCC_ABORT();
  
    /* Stop dsi3 timer */
    DSI3_CTRL_STATUS_TIMER_RESET();
    
    /* Stop fcc blanking */
    DSI3_CTRL_STATUS_BLANKING_OFF();
     
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericCbCtxData;

    /* Added delayed error cb processing for PDCM & DISC err evt handling. */
    if (TRUE == busEnvData->PdcmRuntimeData.Steering.ErrEvtOccured)
    {
      loc_CallBusErrorCallback(busEnvData, Dsi3BusIf_ERR_PDCM_ERROR);
      busEnvData->PdcmRuntimeData.Steering.ErrEvtOccured = FALSE;
    }
    else{ /* Do nothing. */ }
     
    if (TRUE == busEnvData->DiscRuntimeData.Steering.ErrEvtOccured)
    {
      loc_CallBusErrorCallback(busEnvData, Dsi3BusIf_ERR_DISC_ERROR);
      busEnvData->DiscRuntimeData.Steering.ErrEvtOccured = FALSE;
    }
    else{ /* Do nothing. */}     

    /* Process error callback */
    loc_CallBusErrorCallback(busEnvData, Dsi3BusIf_ERR_FCC_ERROR);
  }
  
  return;
}

/* *************************************************************************//**
 * @internal
 * @brief
 * DSI3 Start error interrupt service routine
 *
 * @param   sno                 module interrupt number
 * @param   genericCbCtxData    generic context pointer, should point to bus environment data
 * @return  none
 *
 * @image html Dsi3BusImp_InterruptHandler_StartErrEvt.png "Activity chart: Interrupt Handler Start Error Event"
 * @image latex Dsi3BusImp_InterruptHandler_StartErrEvt.png "Activity chart: Interrupt Handler Start Error Event"
 * ****************************************************************************/
BUS_LAYER void Dsi3BusImp_InterruptHandler_StartErrEvt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* Casting unused function paramteres to void to prevent compiler warning */
  (void)sno;

  if (DSI3_NULL != genericCbCtxData)
  { 
    /* Abort any ongoing fcc activity */
    DSI3_CTRL_STATUS_FCC_ABORT();

    /* Stop dsi3 timer */
    DSI3_CTRL_STATUS_TIMER_RESET();
  
    /* Stop fcc blanking */
    DSI3_CTRL_STATUS_BLANKING_OFF();
    
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericCbCtxData;
       
    /* Process error callback */
    loc_CallBusErrorCallback(busEnvData, (Dsi3BusIf_Error_t)Dsi3BusIf_ERR_START_ERR_EVT);
  }
  
  return;
}


/* *************************************************************************//**
 * @internal
 * @brief
 * DSI3 PDCM err interrupt service routine.
 *
 * This interrupt may be raised after receiving a CRM packet, while still 
 * being in PDCM internally. The DSI3 bus master may force a mode change
 * by sending a CRM packet. In this case, the DSI3 interface has been raised
 * a PDCM_ERR_EVT. Thus, if this IRQ is raised and PDCM_ERR_EVT is set, the 
 * driver has to switch to CRM.
 *
 * @param   sno                 module interrupt number
 * @param   genericCbCtxData    generic context pointer, should point to bus environment data
 * @return  none
 *
 * @image html Dsi3BusImp_InterruptHandler_PdcmErrEvt.png "Activity chart: Interrupt Handler PDCM Error Event"
 * @image latex Dsi3BusImp_InterruptHandler_PdcmErrEvt.png "Activity chart: Interrupt Handler PDCM Error Event"
 * ****************************************************************************/
BUS_LAYER void Dsi3BusImp_InterruptHandler_PdcmErrEvt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* Casting unused function paramteres to void to prevent compiler warning */
  (void)sno;
      
  if (DSI3_NULL != genericCbCtxData)
  { 
    /* Deactivate auto response */
    DSI3_CTRL_CONFIG_AUTORESP_DISABLE();         

    /* Abort any ongoing rcc activity */
    DSI3_CTRL_STATUS_RCC_ABORT();
    
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericCbCtxData;
 
    busEnvData->Steering.NextCommunicationMode = busEnvData->Steering.DefaultCommunicationMode;

    //busEnvData->Steering.Dsi3State = Dsi3BusIf_eSTATE_IDLE;
	
	  /* --> 2018-08-01, poe: ESWDSI3-12
	   * To ensure communication and bus state safety in case normal bus task execution
	   * is not possible due to application duty cycle.Enables IRQs and sets mode timings.
	   */
	  /* --> 2018-11-13, poe: ESWDSI3-16
	   * Enable ModeChange callback execution, otherwise 
	   * the application will never know that the mode has 
	   * actually changed.
	   */ 
	  loc_Dsi3BusImp_PrepareNextCommState(busEnvData, TRUE);
	   /* --> 2018-11-13, poe: ESWDSI3-16 */
	  /* --> 2018-08-01, poe: ESWDSI3-12 */

    if (TRUE == busEnvData->PdcmRuntimeData.Steering.DelayErrEvtHandling)
    {
      busEnvData->PdcmRuntimeData.Steering.ErrEvtOccured = TRUE;
    }
    else
    {
      /* Process error callback */
      loc_CallBusErrorCallback(busEnvData, (Dsi3BusIf_Error_t)Dsi3BusIf_ERR_PDCM_ERROR);
    }
  }

  return;
}

/* *************************************************************************//**
 * @internal
 * @brief
 * DSI3 DISC error interrupt service routine
 *
 * @param   sno                 module interrupt number
 * @param   genericCbCtxData    generic context pointer, should point to bus environment data
 * @return  none
 *
 * @image html Dsi3BusImp_InterruptHandler_DiscErrEvt.png "Activity chart: Interrupt Handler Discovery Error Event"
 * @image latex Dsi3BusImp_InterruptHandler_DiscErrEvt.png "Activity chart: Interrupt Handler Discovery Error Event"
 * ****************************************************************************/
BUS_LAYER void Dsi3BusImp_InterruptHandler_DiscErrEvt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* Casting unused function paramteres to void to prevent compiler warning */
  (void)sno;
  
  if (DSI3_NULL != genericCbCtxData)
  {
	/* --> 2018-11-20, poe: ESWDSI3-16
	 * Removed as in executed in the loc_Dsi3BusImp_PrepareNextCommState() call.
	 */
//    /* Disable timer_b_evt interrupt */
//    DSI3_CTRL_IRQ_DISABLE(dsi3_IRQ_TIMER_B_EVT);    
    
//    /* Disable auto ramping */
//    DSI3_DISC_CTRL_AUTO_DISC_ACCEPT_DISABLE();
//    DSI3_DISC_CTRL_AUTO_DISC_RESP_DISABLE();
	/* --> 2018-11-20, poe: ESWDSI3-16 */
    
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericCbCtxData;

    busEnvData->Steering.NextCommunicationMode =  busEnvData->Steering.DefaultCommunicationMode;
    
    // busEnvData->Steering.Dsi3State = Dsi3BusIf_eSTATE_IDLE;
    
     /* --> 2018-08-01, poe: ESWDSI3-13
	   * To ensure communication and bus state safety in case normal bus task execution
	   * is not possible due to application duty cycle.Enables IRQs and sets mode timings.
	   */
	  /* --> 2018-11-13, poe: ESWDSI3-16
	   * Enable ModeChange callback execution, otherwise 
	   * the application will never know that the mode has 
	   * actually changed.
	   */ 
	  loc_Dsi3BusImp_PrepareNextCommState(busEnvData, TRUE);
	   /* --> 2018-11-13, poe: ESWDSI3-16 */ 
	  /* --> 2018-08-01, poe: ESWDSI3-13 */

    #if (1u == ENABLE_FPGA_AUTOADDRESSING)
      /* Propagate that Discovery addressing has been finished */
      loc_CallDiscProcessedCallback(busEnvData, Dsi3BusIf_eDISCSTAT_ADDRESSED);
    #endif
    
    /* Propagate that the Discovery mode has been terminated */
    loc_CallDiscProcessedCallback(busEnvData, Dsi3BusIf_eDISCSTAT_TERMINATED);
        
    /* Reset Discovery pulse count */
    busEnvData->DiscRuntimeData.PulseCount = 0u;
    
    
    if (TRUE == busEnvData->DiscRuntimeData.Steering.DelayErrEvtHandling)
    {
      busEnvData->DiscRuntimeData.Steering.ErrEvtOccured = TRUE;
    }
    else
    {
      /* Process error callback */
      loc_CallBusErrorCallback(busEnvData, (Dsi3BusIf_Error_t)Dsi3BusIf_ERR_DISC_ERROR);
    }
  }
  return;
}


/* *************************************************************************//**
 * @internal
 * @brief
 * DSI3 PDCM event interrupt service routine
 *
 * @param   sno                 module interrupt number
 * @param   genericCbCtxData    generic context pointer, should point to bus environment data
 * @return  none
 *
 * @image html Dsi3BusImp_InterruptHandler_PdcmEvt.png "Activity chart: Interrupt Handler PDCM Event"
 * @image latex Dsi3BusImp_InterruptHandler_PdcmEvt.png "Activity chart: Interrupt Handler PDCM Event"
 * ****************************************************************************/
BUS_LAYER void Dsi3BusImp_InterruptHandler_PdcmEvt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
 /* Casting unused function paramteres to void to prevent compiler warning */
  (void)sno;
    
 if (DSI3_NULL != genericCbCtxData)
 { 
    DSI3_CTRL_IRQ_DISABLE(dsi3_IRQ_PDCM_EVT);
    DSI3_CTRL_CONFIG_AUTORESP_ENABLE();
    
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericCbCtxData;
    
    /* Prepare timer C for PDCM auto blanking */
    DSI3_CTRL_TIMER_COMPARE_C_SET((uint16_t) (busEnvData->PdcmRuntimeData.Steering.PdcmFCCBlankingTimeOffset));
   
   /* Check if DSI3 timer has already reached auto blank off time */
    if (DSI3_CTRL_TIMER_COUNTER() >= ((uint16_t) (busEnvData->PdcmRuntimeData.Steering.PdcmFCCBlankingTimeOffset)))
    {
      /* Switch off blanking */
      DSI3_CTRL_STATUS_BLANKING_OFF();
    }
    else { /* Do nothing */ }
 }
 else{ /* Bus environment data invalid! */ }
  
  return;
}


/* *************************************************************************//**
 * @internal
 * @brief
 * DSI3 RCC finish interrupt service routine
 *
 * @param   sno                 module interrupt number
 * @param   genericCbCtxData    generic context pointer, should point to bus environment data
 * @return  none
 *
 * @image html Dsi3BusImp_InterruptHandler_RccFinish.png "Activity chart: Interrupt Handler RCC Finish"
 * @image latex Dsi3BusImp_InterruptHandler_RccFinish.png "Activity chart: Interrupt Handler RCC Finish"
 * ****************************************************************************/
BUS_LAYER void Dsi3BusImp_InterruptHandler_RccFinish(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* Casting unused function paramteres to void to prevent compiler warning */
  (void)sno;

  if (DSI3_NULL != genericCbCtxData)
  {   
    /* Disable rcc_finish interrupt */
    DSI3_CTRL_IRQ_DISABLE(dsi3_IRQ_RCC_FINISH);
   
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericCbCtxData;
    /* Set bus activity flag */
    busEnvData->Steering.BusActivityFlag = TRUE;
    
    /* Check if the last msg task has been processed */
    if (Dsi3BusIf_eSTATE_RESPONSE_PROCESSED == busEnvData->Steering.Dsi3State)
    {   
      loc_CallBusErrorCallback((loc_pDsi3EnvironmentData_t) busEnvData, Dsi3BusIf_ERR_TASK_TOO_SLOW);       
    }
    else{ /* Do nothing. */ }
    
    /* Increment KAC field for successful sent message */
    busEnvData->Steering.KeepAliveCounter++;
     
    if (Dsi3BusIf_eCOMM_PERIODICDATACOLLECTIONMODE == busEnvData->Steering.CurrentCommunicationMode)
    {
      /* Prepare pdcm buffer */
      busEnvData->Steering.Dsi3State = Dsi3BusIf_eSTATE_RESPONSE_PROCESSED;
    }
    else
    {      
      /* Switch back to the default communication mode */
      busEnvData->Steering.NextCommunicationMode = busEnvData->Steering.DefaultCommunicationMode;
        
      /* Reset bus fsm */
      busEnvData->Steering.Dsi3State = Dsi3BusIf_eSTATE_RESPONSE_PROCESSED;
	  /* --> 18-07-20, poe: ESWDSI3-11
       * Moved from Task to ensure execution if Task 
       * cannot be run on time.       
       */
      /* Deactivate auto response */
      DSI3_CTRL_CONFIG_AUTORESP_DISABLE();
      /* --> 18-07-20, poe: ESWDSI3-11 */
    }    
  }
  else{/* Error: bus environment data not initialized! */}

  return;
}

#define TIMERA_MEAS_START_OFFSET_SHIFT (2u) /* 2us for set-bit operation */
/**************************************************************************//**
 * @internal
 * @brief
 * DSI3 TimerA interrupt service routine
 *
 * @param   sno         module interrupt number
 * @param   genericCbCtxData     generic context pointer, should point to bus environment data
 * @return  none
 *
 * @image html Dsi3BusImp_InterruptHandler_TimerA_Evt.png "Activity chart: Interrupt Handler Timer A Event"
 * @image latex Dsi3BusImp_InterruptHandler_TimerA_Evt.png "Activity chart: Interrupt Handler Timer A Event"
 * ****************************************************************************/
static BUS_LAYER void Dsi3BusImp_InterruptHandler_TimerA_Evt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* Casting unused function paramteres to void to prevent compiler warning */
  (void)sno;
  (void)genericCbCtxData;
  
  /* --> 18/12/04, poe: ESWDSI3-19
   * Adapted the TimerA IRQ to E52417A1 hardware changes regarding
   * the manual start of the current measurement.
   * The measurement needs to start early enough that clock asynchronities
   * between multiple slaves don't endanger the auto-addressing process.
   */ 
   
  /* Check if DSI3 timer is running */
  if (DSI3_CTRL_STATUS_TIMER_STATUS())
  {    
    /* Check environment data pointer */
    if (DSI3_NULL != genericCbCtxData)
    {
      /* In disc mode: this sets res_n=1, activate current comparator */
      DSI3_DISC_START_CURR_MEAS(); 
     
      loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericCbCtxData;
     
      /* Check current DSI3 timer value and wait until ramp-on time offset is reached */ 
      while (DSI3_CTRL_TIMER_COUNTER() < (busEnvData->DiscRuntimeData.Steering.RampOnDelay-TIMERA_MEAS_START_OFFSET_SHIFT))
      {  
        __NOP(); 
      }
	
     
      /* --> 2019-01-09, poe: ESWDSI3-21,
       * Check if slave has already been addressed during this discovery run,
	   * if not, proceed normally, otherwise do not start the current ramp.
       */
      if (FALSE == busEnvData->DiscRuntimeData.Steering.isAddressed)
      {
        /* --> 18/09/19, poe
         * Re-enabled ramp start - with ~1us offset between starts 
         */
        DSI3_DISC_CTRL_RAMP_ON_ENABLE();
        __NOP(); //8xNOP  ~ 1us
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        DSI3_DISC_CTRL_RAMP_ON_ENABLE();
        /* --> 18/09/19, poe */
      }
      else{ /* Don't start the current ramp. */ }
      /* --> 2019-01-09, poe: ESWDSI3-21 */
     
      /* Clear the curr evt IRQ */
      DSI3_CTRL_IRQ_CLEAR(dsi3_IRQ_DISC_CURR_EVT);
  
  
      /* --> 18/12/04, poe: ESWDSI3-19 */
    
      /* Check current compare output */
      if (0u != DSI3_DISC_CTRL_CURR_CMP_OUT_GET())
      {
        /* Set DiscCurr occurence flag - as it must have been set validly */
        busEnvData->DiscRuntimeData.Steering.DiscCurrEvtOccured = TRUE;
        /* --> 18/09/19, poe: Bugfix
         * If not addressed, disable ramp 
         */
        DSI3_DISC_CTRL_RAMP_ON_DISABLE();
        /* --> 18/09/19, poe: Bugfix */
      }
      else
      {
        /* Reset DiscCurr occurence flag */
        busEnvData->DiscRuntimeData.Steering.DiscCurrEvtOccured = FALSE;
     
        /* Enable CurrCmp IRQ */
        DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_DISC_CURR_EVT);
      }
    }
    else{/* Error: bus environment data not initialized! */}
  }
  else{ /* DSI3 timer is not running - so do nothing. */}

  
  return;
}  


/**************************************************************************//**
 * @internal
 * @brief
 * DSI3 TimerB interrupt service routine
 *
 * @param   sno                 module interrupt number
 * @param   genericCbCtxData    generic context pointer, should point to bus environment data
 * @return  none
 *
 * @image html Dsi3BusImp_InterruptHandler_TimerB_Evt.png "Activity chart: Interrupt Handler Timer B Event"
 * @image latex Dsi3BusImp_InterruptHandler_TimerB_Evt.png "Activity chart: Interrupt Handler Timer B Event"
 * ****************************************************************************/
BUS_LAYER void Dsi3BusImp_InterruptHandler_TimerB_Evt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* Casting unused function paramteres to void to prevent compiler warning */
  (void)sno;
  /* --> 18/09/19, poe: Bugfix
   * Always disable CurrCmp evt at timerB event.
   * Was kept enabled if slave was not addressed.
   */
  /* Disable CurrCmp IRQ */
  DSI3_CTRL_IRQ_DISABLE(dsi3_IRQ_DISC_CURR_EVT);
  /* --> 18/09/19, poe: Bugfix */
  
  if (DSI3_NULL != genericCbCtxData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericCbCtxData;

    /* Check if really in Discovery mode */
    if (Dsi3BusIf_eCOMM_DISCOVERYMODE == busEnvData->Steering.CurrentCommunicationMode)
    {
      /* Threshold flag set? */
      /* --> 2018-08-06, poe: ESWDSI3-14	  
       * Evaluating the occurence of the DiscCurr evt instead of the 
       * hardware register */
      if (FALSE == busEnvData->DiscRuntimeData.Steering.DiscCurrEvtOccured)
      /* --> 2018-08-06, poe: ESWDSI3-14 */
      {        
	/* --> 2019-01-09, poe: ESWDSI3-21,
      	 * Added check for auto addressing id fault detection
      	 */ 
         /* Check if slave has already been addressed... */
         if (FALSE == busEnvData->DiscRuntimeData.Steering.isAddressed)
         {       
           /* TimerA and TimerB irqs are _not_ to be disabled here as to 
	    * continue the auto-addressing process in passive verification mode! */
          
            /* Propagate that Discovery addressing has been finished */
            loc_CallDiscProcessedCallback(busEnvData, Dsi3BusIf_eDISCSTAT_ADDRESSED);
          
            /* Set the isAddressed flag to TRUE */
            busEnvData->DiscRuntimeData.Steering.isAddressed = TRUE;
         }
         else{ /* The current threshold was not breached, so do nothing. */ }
      }
      else /* The CurrCmp measurement returned that the bus current was above the threshold... */
      {  
        /* Check if already adressed. If it is, stop the auto addressing verification and
		 * throw an error, as  the addressee order is not as intended!
         */
        if (TRUE == busEnvData->DiscRuntimeData.Steering.isAddressed)
        {          
          /* Stop auto addressing participation */
            
          /* Disable auto ramping */
          DSI3_DISC_CTRL_AUTO_DISC_ACCEPT_DISABLE();
          DSI3_DISC_CTRL_AUTO_DISC_RESP_DISABLE();
            
          /* Disable TimerB IRQ */
          DSI3_CTRL_IRQ_DISABLE(dsi3_IRQ_TIMER_B_EVT);
            
          /* Disable TimerA IRQ */
          DSI3_CTRL_IRQ_DISABLE(dsi3_IRQ_TIMER_A_EVT);
		  /* As the threshold was breached despite being addressed already -> exec the error callback */
          loc_CallBusErrorCallback(busEnvData, (Dsi3BusIf_Error_t)Dsi3BusIf_ERR_DISC_VERIFY_ERROR);    
          
        } 
        else{ /* Do nothing */ }
          /* --> 2019-01-09, poe: ESWDSI3-21 */
      }
        
      /* --> 2018-09-18, poe:  Bugfix
       * Moved outside the if/else block, flag should always
       * be cleared during timerB evt handling.
       */
       /* Reset DiscCurr occurence flag */
       busEnvData->DiscRuntimeData.Steering.DiscCurrEvtOccured = FALSE;
       /* --> 2018-09-18, poe:  Bugfix */
    }
    else{/* ... */}      
   
  }
  else{/* Error: bus environment data not initialized! */}
  return;
}


/* --> 2018-08-06, poe: ESWDSI3-14
 * Added to track occurence of being not addressed during
 * discovey mode.
 */
/**************************************************************************//**
 * @internal
 * @brief
 * DSI3 Discovery current compare interrupt service routine
 *
 * @param   sno                 module interrupt number
 * @param   genericCbCtxData    generic context pointer, should point to bus environment data
 * @return  none
 *
 * @image html Dsi3BusImp_InterruptHandler_DiscCurrEvt.png "Activity chart: Interrupt Handler Disc curr"
 * @image latex Dsi3BusImp_InterruptHandler_DiscCurrEvt.png "Activity chart: Interrupt Handler Disc curr"
 * ****************************************************************************/
static BUS_LAYER void Dsi3BusImp_InterruptHandler_DiscCurrEvt(dsi3_eInterruptVectorNum_t sno, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  /* Casting unused function paramteres to void to prevent compiler warning */
  (void)sno;
  
  /* Read current DSI3 timer value */
  uint16_t loc_currDSI3Timer = DSI3_CTRL_TIMER_COUNTER();
  /* --> 2018-09-18, poe:  Bugfix
   * If CurrCmp irq occurs, disable it.
   */
  /* Disable CurrCmpEvt IRQ */
  DSI3_CTRL_IRQ_DISABLE(dsi3_IRQ_DISC_CURR_EVT);
  /* --> 2018-09-18, poe:  Bugfix */
  
  if (DSI3_NULL != genericCbCtxData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericCbCtxData;
    
    /* Check if DSI3 timer is still inside the ramp on duration time frame */
    if (loc_currDSI3Timer <= DSI3_CTRL_TIMER_COMPARE_B_GET())
    {
      /* If yes, set occurence flag */
      busEnvData->DiscRuntimeData.Steering.DiscCurrEvtOccured = TRUE;
    }
    else{ /* Do nothing. */ }
   
  }
  else{/* Error: bus environment data not initialized! */}

  return;
}
/* --> 2018-08-06, poe: ESWDSI3-14 */


/*************************************************************************** 
 ************************** HELPER FUNCTIONS *******************************
 ***************************************************************************/

/**************************************************************************//**
 * @internal
 * @brief
 * Local error callback routine to propagate error code to the upper layer
 *
 * @param   busEnvData       bus environment data
 * @param   error            error code for specific error case
 * @return  none
 *
 * @image html loc_CallBusErrorCallback.png "Activity chart: Call Bus Error Callback"
 * @image latex loc_CallBusErrorCallback.png "Activity chart: Call Bus Error Callback"
 * ****************************************************************************/
BUS_LAYER void loc_CallBusErrorCallback(loc_pDsi3EnvironmentData_t busEnvData, Dsi3BusIf_Error_t error)
{
  Dsi3BusIf_ByteData_t i;
  
  for(i = 0; i < DSI3_MAX_NUMBER_OF_CALLBACK_TABLES; i++)
  {
    const Dsi3BusIf_cpCallbackFunctions_t callbacks = busEnvData->Callbacks[i];
    if(DSI3_NULL != callbacks)
    {
      const Dsi3BusIf_ErrorCbFun_t fun = callbacks->Error;
      if (DSI3_NULL != fun)
      {
        fun(busEnvData, &Dsi3BusImp_InterfaceFunctions, error, busEnvData->CallbackCtxData[i]);
      }
      else{ /* No error callback configured. */}
    }
    else{ /* No callback table configured! */}
  }
}


/**************************************************************************//**
 * @internal
 * @brief
 * Local callback routine to propagate dsi3 mode change to the upper layer
 *
 * @param   busEnvData       bus environment data
 * @param   currentMode      currently active dsi3 mode
 * @return  none
 *
 * @image html loc_CallModeChangedCallback.png "Activity chart: Call Mode Changed Callback"
 * @image latex loc_CallModeChangedCallback.png "Activity chart: Call Mode Changed Callback"
 * ****************************************************************************/
BUS_LAYER void loc_CallModeChangedCallback(loc_pDsi3EnvironmentData_t busEnvData, Dsi3BusIf_eCommunicationMode_t currentMode)
{
  Dsi3BusIf_ByteData_t i;
  
  for(i = 0; i < DSI3_MAX_NUMBER_OF_CALLBACK_TABLES; i++)
  {
    const Dsi3BusIf_cpCallbackFunctions_t callbacks = busEnvData->Callbacks[i];
    if(DSI3_NULL != callbacks)
    {
      const Dsi3BusIf_ModeChangedCbFun_t fun = callbacks->ModeChanged;
      if (DSI3_NULL != fun)
      {
        fun(busEnvData, &Dsi3BusImp_InterfaceFunctions, currentMode, busEnvData->CallbackCtxData[i]);
      }
      else{ /* No change mode callback configured */ }
    }
    else{ /* No callback table configured! */ }
  }
}


/**************************************************************************//**
 * @internal
 * @brief
 * Local callback routine to propagate dsi3 crm cmd processed status to the upper layer
 *
 * @param   busEnvData       bus environment data
 * @return  none
 *
 * @image html loc_CallCrmProcessedCallback.png "Activity chart: Call CRM Processed Callback"
 * @image latex loc_CallCrmProcessedCallback.png "Activity chart: Call CRM Processed Callback"
 * ****************************************************************************/
BUS_LAYER void loc_CallCrmProcessedCallback(loc_pDsi3EnvironmentData_t busEnvData)
{
  Dsi3BusIf_ByteData_t i;
  
  for(i = 0; i < DSI3_MAX_NUMBER_OF_CALLBACK_TABLES; i++)
  {
    const Dsi3BusIf_cpCallbackFunctions_t callbacks = busEnvData->Callbacks[i];
    if(DSI3_NULL != callbacks)
    {
      const Dsi3BusIf_CrmProcessedCbFun_t fun = callbacks->CrmProcessed;
      if (DSI3_NULL != fun)
      {
        fun(busEnvData, &Dsi3BusImp_InterfaceFunctions, busEnvData->Steering.Dsi3State, busEnvData->CallbackCtxData[i]);
      }
      else{ /* No CRM processed callback configured. */ }
    }
    else{ /* No callback table configured! */ }
  }
}


/**************************************************************************//**
 * @internal
 * @brief
 * Local callback routine to propagate dsi3 pdcm cmd processed status to the upper layer
 *
 * @param   busEnvData       bus environment data
 * @return  none
 *
 * @image html loc_CallPdcmProcessedCallback.png "Activity chart: Call PDCM Processed Callback"
 * @image latex loc_CallPdcmProcessedCallback.png "Activity chart: Call PDCM Processed Callback"
 * ****************************************************************************/
BUS_LAYER void loc_CallPdcmProcessedCallback(loc_pDsi3EnvironmentData_t busEnvData)
{
  Dsi3BusIf_ByteData_t i;
  
  for(i = 0; i < DSI3_MAX_NUMBER_OF_CALLBACK_TABLES; i++)
  {
    const Dsi3BusIf_cpCallbackFunctions_t callbacks = busEnvData->Callbacks[i];
    if(DSI3_NULL != callbacks)
    {
      const Dsi3BusIf_PdcmProcessedCbFun_t fun = callbacks->PdcmProcessed;
      if (DSI3_NULL != fun)
      {
        fun(busEnvData, &Dsi3BusImp_InterfaceFunctions, busEnvData->CallbackCtxData[i]);
      }
      else{ /* No PDCM processed callback configured. */ }
    }
    else{ /* No callback table configured! */ }
  }
}



/**************************************************************************//**
 * @internal
 * @brief
 * Local callback routine to propagate dsi3 disc mode status to the upper layer
 *
 * @param   busEnvData       bus environment data
 * @param   currentStatus    currently discovery mode status
 * @return  none
 *
 * @image html loc_CallDiscProcessedCallback.png "Activity chart: Call Disc Processed Callback"
 * @image latex loc_CallDiscProcessedCallback.png "Activity chart: Call Disc Processed Callback"
 * ****************************************************************************/
BUS_LAYER void loc_CallDiscProcessedCallback(loc_pDsi3EnvironmentData_t busEnvData, Dsi3BusIf_DiscoveryModeStatus_t currentStatus)
{
  Dsi3BusIf_ByteData_t i;
  
  for(i = 0; i < DSI3_MAX_NUMBER_OF_CALLBACK_TABLES; i++)
  {
    const Dsi3BusIf_cpCallbackFunctions_t callbacks = busEnvData->Callbacks[i];
    if(DSI3_NULL != callbacks)
    {
      const Dsi3BusIf_DiscProcessedCbFun_t fun = callbacks->DiscProcessed;
      if (DSI3_NULL != fun)
      {
        fun(busEnvData, &Dsi3BusImp_InterfaceFunctions, busEnvData->DiscRuntimeData.PulseCount, currentStatus, busEnvData->CallbackCtxData[i]);
      }
      else{ /* No discovery processed callback configured */ }
    }
    else{ /* No callback table configured! */ }
  }
}


/**************************************************************************//**
 * @internal
 * @brief Light-weight DSI3 CRM mode reset to full enable.
 *
 * Just resets IRQ, cmd & resp buffers, autoblanking and autoresponse.
 *
 * @param   busEnvData        bus environment data
 * @return  none
 *
 * @image html loc_ResetCrm.png "Activity chart: Reset CRM Mode"
 * @image latex loc_ResetCrm.png "Activity chart: Reset CRM Mode"
 * ****************************************************************************/
BUS_LAYER void loc_ResetCrm(loc_pDsi3EnvironmentData_t busEnvData)
{
  /* --> 18-07-18, poe: ESWDSI3-11
   * Moved to RCC_FINISH irq handler 
   */
  /* Deactivate auto response */
  // DSI3_CTRL_CONFIG_AUTORESP_DISABLE();
  /* --> 18-07-18, poe: ESWDSI3-11 */
  busEnvData->CrmRuntimeData.CommandBuffer.Value   = 0u;
  /* --> 18-08-01, poe: ESWDSI3-12
   * Removed, as there is no actual benefit of the response buffer reset.
   */	 
  //busEnvData->CrmRuntimeData.ResponseBuffer.Value  = 0u;
  /* --> 18-08-01, poe: ESWDSI3-12 */
  /* Clear cmd evt irq */
  DSI3_CTRL_IRQ_CLEAR(dsi3_IRQ_CMD_EVT);
  
  /* Clear cmd crc err irq */
  DSI3_CTRL_IRQ_CLEAR(dsi3_IRQ_CRC_ERR_EVT);
  
  /* Clear fcc err irq */
  DSI3_CTRL_IRQ_CLEAR(dsi3_IRQ_FCC_ERROR);
  
  /* Clear start err irq */
  DSI3_CTRL_IRQ_CLEAR(dsi3_IRQ_START_ERR_EVT);
  
  return;
}


/**************************************************************************//**
 * @internal
 * @brief
 * Enables DSI3 CRM mode 
 *
 * Configures DSI3 module for CRM mode, sets bus state machine
 * and reinitializes buffer and timer values.
 *
 * @param   busEnvData      bus environment data
 * @return  none
 *
 * @image html loc_EnableCrm.png "Activity chart: Enable CRM"
 * @image latex loc_EnableCrm.png "Activity chart: Enable CRM"
 * ****************************************************************************/
BUS_LAYER void loc_EnableCrm(loc_pDsi3EnvironmentData_t busEnvData)
{ 
  /* Disable and clear all interrupts */
  DSI3_CTRL_IRQ_DISABLE_ALL();
  DSI3_CTRL_IRQ_CLEAR_ALL();
  
  /* Enable crm mode exclusive */
  DSI3_CTRL_STATUS_CRM_ENABLE();

  /* Deactivate auto response */
  DSI3_CTRL_CONFIG_AUTORESP_DISABLE();
          
  /* Stop fcc blanking */
  DSI3_CTRL_STATUS_BLANKING_OFF();
  
  /* Update current communication mode indicator */
  busEnvData->Steering.CurrentCommunicationMode         = Dsi3BusIf_eCOMM_COMMANDRESPONSEMODE;
  
  /* Switch state to waiting idle */
  busEnvData->Steering.Dsi3State                        = Dsi3BusIf_eSTATE_IDLE;

  busEnvData->CrmRuntimeData.CommandBuffer.Value        = 0u;
  busEnvData->CrmRuntimeData.ResponseBuffer.Value       = 0u;
  
  /* Prepare timer A for CRM response */
  DSI3_CTRL_TIMER_COMPARE_A_SET((uint16_t) busEnvData->CrmRuntimeData.Steering.CrmResponseTimeOffset);
   
  /* Prepare timer C for auto blanking */
  DSI3_CTRL_TIMER_COMPARE_C_SET((uint16_t) (busEnvData->CrmRuntimeData.Steering.CrmFCCBlankingTimeOffset));
  
  /* Enable cmd evt irq */
  DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_CMD_EVT);
  
  /* Enable cmd crc err irq */
  DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_CRC_ERR_EVT); 

  /* Enable fcc err irq */
  DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_FCC_ERROR);
  
  /* Enable start err irq */
  DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_START_ERR_EVT);

  return;
}

/**************************************************************************//**
 * @internal
 * @brief
 * Light-weight DSI3 PDCM mode reset to full enable. 
 *
 * Just resets IRQ, autoblanking and autoresponse.
 *
 * @param   busEnvData      bus environment data
 * @return  none
 *
 * @image html loc_ResetPdcm.png "Activity chart: Reset PDCM Mode"
 * @image latex loc_ResetPdcm.png "Activity chart: Reset PDCM Mode"
 * ****************************************************************************/
BUS_LAYER void loc_ResetPdcm(loc_pDsi3EnvironmentData_t busEnvData)
{
  /* Enable pdcm err interrupt */
  DSI3_CTRL_IRQ_CLEAR(dsi3_IRQ_PDCM_ERR_EVT);
  DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_PDCM_ERR_EVT);

  busEnvData->PdcmRuntimeData.Steering.TimeSlot = (busEnvData->CurrentSlaveID-1);

  /* Clar StartErr evt irq */
  DSI3_CTRL_IRQ_CLEAR(dsi3_IRQ_START_ERR_EVT);
  
  /* Clearing FCCErr evt irq */
  DSI3_CTRL_IRQ_CLEAR(dsi3_IRQ_FCC_ERROR);
  
  /* Clearing PDCM evt irq */
  DSI3_CTRL_IRQ_CLEAR(dsi3_IRQ_PDCM_EVT);
}


/**************************************************************************//**
 * @internal
 * @brief
 * Enables DSI3 PDCM mode 
 *
 * Configures DSI3 module for PDCM  mode, sets bus state machine
 * and reinitializes buffer and timer values.
 *
 * @param   busEnvData      bus environment data
 * @return  none
 *
 * @image html loc_EnablePdcm.png "Activity chart: Enable PDCM Mode"
 * @image latex loc_EnablePdcm.png "Activity chart: Enable PDCM Mode"
 * ****************************************************************************/
BUS_LAYER void loc_EnablePdcm(loc_pDsi3EnvironmentData_t busEnvData)
{
  /* Disable and clear all interrupts */
  DSI3_CTRL_IRQ_DISABLE_ALL();
  DSI3_CTRL_IRQ_CLEAR_ALL();
  
  /* Enable pdcm mode exclusive */
  DSI3_CTRL_STATUS_PDCM_ENABLE();

  /* Deactivate auto response - if somehow active */
  DSI3_CTRL_CONFIG_AUTORESP_DISABLE();

  /* Stop fcc blanking */
  DSI3_CTRL_STATUS_BLANKING_OFF();
  
  /* Update current communication mode indicator */
  busEnvData->Steering.CurrentCommunicationMode         = Dsi3BusIf_eCOMM_PERIODICDATACOLLECTIONMODE;

  /* Switch state to preparing pdcm response buffer */
  busEnvData->Steering.Dsi3State = Dsi3BusIf_eSTATE_PDCMPREPAREBUFFER;
  
  /* Reset runtime data */
  busEnvData->PdcmRuntimeData.Steering.CommandCount     = 0u;
  busEnvData->PdcmRuntimeData.Steering.ResponseCount    = 0u;

  busEnvData->PdcmRuntimeData.Steering.TimeSlot         = (busEnvData->CurrentSlaveID-1);
   
  /* Prepare timer B for PDCM period */
  DSI3_CTRL_TIMER_COMPARE_B_SET((uint16_t) busEnvData->PdcmRuntimeData.Steering.PdcmResponseDuration);
  
  /* Prepare timer A for PDCM */
  DSI3_CTRL_TIMER_COMPARE_A_SET((uint16_t) DSI3_DRV_PDCM_SLOT_START( busEnvData->PdcmRuntimeData.Steering.PdcmStartSlotOffset, busEnvData->PdcmRuntimeData.Steering.TimeSlot, busEnvData->PdcmRuntimeData.Steering.PdcmSlotDuration));
 
  /* Enable pdcm err interrupt */
  DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_PDCM_ERR_EVT);  

  /* Enable fcc err interrupt */
  DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_FCC_ERROR);
  
  /* Enable start err interrupt */
  DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_START_ERR_EVT);
  
  /* Enable PDCM evt interrupt */
  DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_PDCM_EVT);
  return;
}

/* --> 18/12/04, poe: ESWDSI3-19
 * Re-defined TimerA offset for manual comparator startup.
 */
#define DSI3BUSIMP_RAMPON_TRIGGER_DELAY 15u
/* --> 18/12/04, poe: ESWDSI3-19 */
/**************************************************************************//**
 * @internal
 * @brief
 * Enables DISC mode 
 *
 * Configures DSI3 module for Discovery mode, sets bus state machine
 * and reinitializes buffer and timer values.
 *
 * @param   busEnvData      bus environment data
 * @return  none
 *
 * @image html loc_EnableDisc.png "Activity chart: Enable Discovery Mode"
 * @image latex loc_EnableDisc.png "Activity chart: Enable Discovery Mode"
 * ****************************************************************************/
BUS_LAYER void loc_EnableDisc(loc_pDsi3EnvironmentData_t busEnvData)
{
  /* --> 2018-11-15, poe: ESWDSI3-18
   * Halt the DSI3 Timer to prevent TimerX trigger.
   */
  /* Halt DSI3 Timer */
  DSI3_CTRL_STATUS_TIMER_RESET();
  /* --> 2018-11-15, poe: ESWDSI3-18 */
  
  /* Disable and clear all interrupts */
  DSI3_CTRL_IRQ_DISABLE_ALL();
  
  /* Enable disc mode exclusive */
  DSI3_CTRL_STATUS_DISC_ENABLE();

  /* Deactivate auto response */
  DSI3_CTRL_CONFIG_AUTORESP_DISABLE();
  

  
  /* Stop fcc blanking */
  DSI3_CTRL_STATUS_BLANKING_OFF();
  
  /* Prepare timer C for auto blanking */
  DSI3_CTRL_TIMER_COMPARE_C_SET((uint16_t) busEnvData->DiscRuntimeData.Steering.PeriodLength-DSI3_DRV_DISC_BLANK_OFFSET);

  /* Update current communication mode indicator */
  busEnvData->Steering.CurrentCommunicationMode = Dsi3BusIf_eCOMM_DISCOVERYMODE;
  
  /* Switch state to waiting for disc pulse */
  busEnvData->Steering.Dsi3State = Dsi3BusIf_eSTATE_WAIT_FOR_DISC_PULSE;
  
  /* --> 19-01-09, poe: ESWDSI3-21, 
   * Initialise isAddressed status with false.
   */
  /* Reset the isAddressed status, as this is a new discovery mode run */
  busEnvData->DiscRuntimeData.Steering.isAddressed  = FALSE;
  /* --> 19-01-09, poe: ESWDSI3-21 */

  
  /* Prepare timer A for auto start current ramp on */
  DSI3_CTRL_TIMER_COMPARE_A_SET((uint16_t) (busEnvData->DiscRuntimeData.Steering.RampOnDelay-DSI3BUSIMP_RAMPON_TRIGGER_DELAY));
      
  /* Prepare timer B for auto stop current ramp on */
  DSI3_CTRL_TIMER_COMPARE_B_SET((uint16_t) busEnvData->DiscRuntimeData.Steering.RampOnDuration);
   
  /* Enable auto current ramp off */
  DSI3_DISC_CTRL_AUTO_DISC_ACCEPT_ENABLE();
  
  /* --> 2018-11-13, poe: ESWDSI3-17
   * Auto-Ramp-on should be disabled for 
   * the AA hardware fix to work.
   */
  /* Disable auto current ramp on */
  DSI3_DISC_CTRL_AUTO_DISC_RESP_DISABLE();
  /* --> 2018/11/13, poe: ESWDSI3-17 */
  /* --> 2018-11-13, poe: ESWDSI3-18
   * IRQs need to be cleared after reconfiguration,
   * otherwise a race-condition can occur and trigger
   * an unwanted interrupt handler execution.
   */
   /* Clear all interrupts */
   DSI3_CTRL_IRQ_CLEAR_ALL();
  /* --> 2018/11/13, poe: ESWDSI3-18 */   
  
  /* Enable timer_a evt irq */
  DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_TIMER_A_EVT);
  
  /* Enable timer_b evt irq */
  DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_TIMER_B_EVT);
  /* --> 2018-08-06, poe: ESWDSI3-14 */
  /* --> 18/09/18, poe: Bugfix
   * Is now activated during TimerA evt handler.
   */  
//  /* Enabled curr_cmp evt irq */
//  DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_DISC_CURR_EVT);
  /* --> 18/09/18, poe: Bugfix */
  /* --> 2018-08-06, poe: ESWDSI3-14 */

  /* Enable disc err interrupt */
  DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_DISC_ERR_EVT);
  
  /* Enable disc evt interrupt */
  DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_DISC_EVT);
      
  /* Enable FCC err evt interrupt */
  DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_FCC_ERROR);
       
  return;
}



/*************************************************************************** 
 ************************** INTERFACE FUNCTIONS ****************************
 ***************************************************************************/

/***************************************************************************//**
 * @brief
 * Initializes DSI3 module and bus environment data.
 *
 * @param       genericBusEnvData   pointer to bus environment data
 * @param       busEnvDataSze       bus environment data size
 * @param       genericImpCfgData   pointer init parameters for the bus layer from the appl layer
 * @return      TRUE                if the initialization process was successful,
 *              FALSE               else
 *
 * @image html Dsi3BusImp_Initialization.png "Activity chart: Initialization"
 * @image latex Dsi3BusImp_Initialization.png "Activity chart: Initialization"
 * ****************************************************************************/
BUS_LAYER Dsi3BusIf_Bool_t Dsi3BusImp_Initialization( Dsi3BusIf_pGenericEnvData_t       genericBusEnvData, 
                                                      Dsi3BusIf_EnvDataSze_t            busEnvDataSze,
                                                      Dsi3BusIf_cpGenericImpCfgData_t   genericImpCfgData)
{
  Dsi3BusIf_Bool_t retVal = FALSE;
  Dsi3BusIf_Length_t tmpBufSize = (busEnvDataSze - sizeof(loc_sDsi3EnvironmentData_t));
  Dsi3BusImp_cpCfgData_t dsi3Cfg = (Dsi3BusImp_cpCfgData_t)genericImpCfgData;
  
  if (DSI3_NULL != (void *) genericBusEnvData)
  {
    if ((DSI3_NULL != (void *) dsi3Cfg) 
      && (dsi3Cfg->Version == DSI3_IMPL_CFG_DATA_VERSION)
      && (DSI3_NULL != (void *) dsi3Cfg->NvicInterfaceFunctions)
      && (busEnvDataSze >= (sizeof(loc_sDsi3EnvironmentData_t)+DSI3BUSIMP_MSG_BUF_SZE_MIN))
      && ((tmpBufSize & 0x01) == 0)
      && (DSI3_IMPL_TARGET_HARDWARE_VERSION == DSI3_HW_VERSION))
    {
      loc_pDsi3EnvironmentData_t busEnvData       = (loc_pDsi3EnvironmentData_t)genericBusEnvData;   

      /* Initialize envData area */
      el_FillBytes(0x00u, (uint8_t*)busEnvData, busEnvDataSze);
	       
      /* Set initial chip time environment parameter */
      busEnvData->Steering.ChipTime               = dsi3Cfg->RCC_ChipTime;
   
      busEnvData->Steering.HardwareAddsCRC        = dsi3Cfg->HardwareAddsCRC;
      
      /* Configure dsi3 module */
      DSI3_CONFIG                                 = 0u;
	  DSI3_CONFIG                                 = (uint16_t) (E_DSI3_CONFIG_CRC_CHECK
                                                  | (uint16_t)((uint16_t) dsi3Cfg->HardwareAddsCRC * E_DSI3_CONFIG_CRC_ADD)
                                  //              | E_DSI3_CONFIG_AUTO_RESP
                                                  | E_DSI3_CONFIG_AUTO_TIMER
                                                  | (uint16_t)((uint16_t) dsi3Cfg->EnableAutoSync * E_DSI3_CONFIG_AUTO_SYNC)
                                    //            | E_DSI3_CONFIG_DISABLE_SYNC_VALI
                                                  | E_DSI3_CONFIG_AUTO_BLANK_ON
                                                  | E_DSI3_CONFIG_AUTO_BLANK_OFF
                                                  | (uint16_t)(busEnvData->Steering.ChipTime<<SFT_DSI3_CONFIG_T_CHIP)
                                                  | (uint16_t)(dsi3_ePDCM_Seed_ID<<SFT_DSI3_CONFIG_PDCM_SEED_SEL)
                                               // | (uint16_t)(dsi3Cfg->Dsi3DebounceValue<<SFT_DSI3_CONFIG_DEBOUNCE)
                                                  | (uint16_t)(DSI3_TIMER_ST_EDGE<<SFT_DSI3_CONFIG_TIMER_START_SEL)
						                          | (uint16_t)(dsi3Cfg->FCC_BitTime<<SFT_DSI3_CONFIG_T_BIT_FCC));
      
    
      DSI3_ANALOG_CTRL                            = (uint16_t)(E_DSI3_ANALOG_CTRL_DSI3_ENABLE
                                                  | E_DSI3_ANALOG_CTRL_RCC_ENABLE
                                                  | (uint16_t)(dsi3Cfg->RCC_SlopeSel<<SFT_DSI3_ANALOGCTRL_RCC_SLOPE)
                                                  | (uint16_t)(dsi3Cfg->RCC_CurveSel<<SFT_DSI3_ANALOGCTRL_RCC_CURVE)
                                                  | (uint16_t)(dsi3Cfg->RCC_CurrentOffset<<SFT_DSI3_ANALOGCTRL_RCC_CURROFFSET)
                                                  | (uint16_t)(dsi3Cfg->Dsi3DebounceValue<<SFT_DSI3_ANALOGCTRL_FCC_DEBOUNCE));
      
 	/* --> 2018-09-18, poe: Bugfix
  	 * Set DISC mode debounce value.
  	 */   
  	/* Set DSI3 DISC debounce value */
  	DSI3_DISC_CTRL_DEBOUNCE_SET(DSI3_DRV_DISC_DEBOUNCE_VAL);
  	/* --> 2018-09-18, poe: Bugfix */
	  
	  
      /* 
      * Use slave's Physical Address as seed for PDCM checksum calculation 
      * Make sure, BIT_DSI3_CONFIG_PDCM_SEED_SEL is cleared!
      */
      /* Set node address */
      busEnvData->CurrentSlaveID                               = dsi3Cfg->SlaveID;
      busEnvData->NewSlaveID                                   = dsi3Cfg->SlaveID;
      /* Set node address in dsi3 module */
      DSI3_CTRL_SOURCE_ID_SET(busEnvData->CurrentSlaveID);    //  Dsi3Bus_DeviceAddress;
      
      busEnvData->MaxSlaveID                                   = (dsi3Cfg->MaximalSlaveID > DSI3_NAD_BROADCAST) ? ((dsi3Cfg->MaximalSlaveID  <= DSI3_NAD_MAX_DEFAULT) ? dsi3Cfg->MaximalSlaveID : DSI3_NAD_MAX_DEFAULT) : DSI3_NAD_MAX_DEFAULT;
      
      
      
      
      /* Initialize driver steering */
      busEnvData->Steering.CurrentCommunicationMode            = dsi3Cfg->DefaultCommunicationMode;
      busEnvData->Steering.NextCommunicationMode               = dsi3Cfg->DefaultCommunicationMode;
      busEnvData->Steering.Dsi3State                           = Dsi3BusIf_eSTATE_IDLE;
      busEnvData->Steering.DataCounter                         = 0u;
      busEnvData->Steering.DefaultCommunicationMode            = dsi3Cfg->DefaultCommunicationMode;
      
      
      
      /* Initialize crm steering */
      /* --> 2019-03-14, poe: Improvement
       * Removed boundary check as it causes a problem
       * if the offset has to be set larger > 310us for
       * increased Fcc bit time configurations. */
      busEnvData->CrmRuntimeData.Steering.CrmResponseTimeOffset           = dsi3Cfg->CRMResponseTimeOffset;
      /* --> 2019-03-14, poe: Improvement */
      busEnvData->CrmRuntimeData.Steering.CrmFCCBlankingTimeOffset        = dsi3Cfg->CRMFCCBlankingTimeOffset;
      
      
      /* Initialize pdcm steering */
      busEnvData->PdcmRuntimeData.Steering.PdcmStartSlotOffset            = dsi3Cfg->PDCMStartSlotOffset;
      busEnvData->PdcmRuntimeData.Steering.PdcmResponseDuration           = dsi3Cfg->PDCMResponseDuration;
      busEnvData->PdcmRuntimeData.Steering.PdcmSlotDuration               = dsi3Cfg->PDCMSlotDuration;
      busEnvData->PdcmRuntimeData.Steering.PdcmFCCBlankingTimeOffset      = dsi3Cfg->PDCMFCCBlankingTimeOffset;
      busEnvData->PdcmRuntimeData.Steering.DelayErrEvtHandling            = dsi3Cfg->PDCMDelayErrEvtHandling;
      
      /* 
      * Msg(2:0306) [I] Cast between a pointer to object and an integral type.
      *
      * According to QA-C help "this type of operation is not uncommon in embedded 
      * software applications where memory mapped I/O ports must be addressed."
      */  
      // PRQA S 0306 1 
      busEnvData->PdcmRuntimeData.ResponseBuffer                          = (Dsi3BusIf_Data_t*) ((uint32_t)genericBusEnvData + sizeof(loc_sDsi3EnvironmentData_t));
      
      /* Set pdcm response buffer length - must be at least 1 byte and maximal 63 bytes (hw limited) - must also be within bounds of allocated memory */
      busEnvData->PdcmRuntimeData.Steering.BufferSize                     = ((dsi3Cfg->PDCMOutBufferSize >= DSI3BUSIMP_MSG_BUF_SZE_MIN) && (DSI3BUSIMP_MSG_BUF_SZE_MIN <= tmpBufSize)) ? (((dsi3Cfg->PDCMOutBufferSize < DSI3BUSIMP_MSG_BUF_SZE_MAX) && (DSI3BUSIMP_MSG_BUF_SZE_MAX <= tmpBufSize)) ? dsi3Cfg->PDCMOutBufferSize : DSI3BUSIMP_MSG_BUF_SZE_MAX) : 1;
      
      /* Initialize disc steering */
      if (dsi3Cfg->DISCRampOnDelay > 0u)
      {
        busEnvData->DiscRuntimeData.Steering.RampOnDelay                  =  dsi3Cfg->DISCRampOnDelay; 
      }
      else
      {
        busEnvData->DiscRuntimeData.Steering.RampOnDelay                  =  DSI3_DRV_DISC_RAMPON_DELAY_DEFAULT; 
      }

      if (dsi3Cfg->DISCRampOnDuration > 0u)
      {
        busEnvData->DiscRuntimeData.Steering.RampOnDuration               = busEnvData->DiscRuntimeData.Steering.RampOnDelay + dsi3Cfg->DISCRampOnDuration;
      }
      else
      {
       
        busEnvData->DiscRuntimeData.Steering.RampOnDuration               = busEnvData->DiscRuntimeData.Steering.RampOnDelay + DSI3_DRV_DISC_RAMPON_DURATION_DEFAULT;
      }

      if (dsi3Cfg->DISCPeriodLength > DSI3_DRV_DISC_BLANK_OFFSET)
      {  
        busEnvData->DiscRuntimeData.Steering.PeriodLength                 =  dsi3Cfg->DISCPeriodLength;
      }
      else
      {
      busEnvData->DiscRuntimeData.Steering.PeriodLength                   = DSI3_DRV_DISC_PERIOD_LENGTH_DEFAULT;
      }
      
      busEnvData->DiscRuntimeData.Steering.DelayErrEvtHandling            = dsi3Cfg->DISCDelayErrEvtHandling;
      
      /* --> 19-02-25, poe: Bugfix ESWDSI3-23
       * Start DSI3 Cfg1usClock value with 0u to prevent
       * unneeded synching effects. 
       */
      /* Set current DSI3 Clock Cfg */
      busEnvData->Steering.Cfg1usClock = 0u;
      /* --> 19-02-25, poe: Bugfix ESWDSI3-23 */
      
      /* Configure DSI3 interrupts */        
      dsi3_InterruptInitialisation(dsi3Cfg->NvicInterfaceFunctions, &busEnvData->IrqEnvData, busEnvData);
      
      
      /* Set module priority level */
      dsi3Cfg->NvicInterfaceFunctions->SetModulePriority(nvic_IRQ_DSI3, nvic_Priority_Level_0);
      
//    dsi3_InterruptRegisterCallback(dsi3_IRQ_SYNC_EVT      , (dsi3_InterruptCallback_t)Dsi3BusImp_InterruptHandler_SyncEvt);
      
      if (TRUE == dsi3Cfg->CRMEnableSlaveIdPrefilter)
      {
        dsi3_InterruptRegisterCallback(dsi3_IRQ_CMD_EVT     , (dsi3_InterruptCallback_t)Dsi3BusImp_InterruptHandler_CmdEvt_Prefiltered);
      }
      else
      {
        dsi3_InterruptRegisterCallback(dsi3_IRQ_CMD_EVT     , (dsi3_InterruptCallback_t)Dsi3BusImp_InterruptHandler_CmdEvt);
      }
     
      dsi3_InterruptRegisterCallback(dsi3_IRQ_PDCM_EVT      , (dsi3_InterruptCallback_t)Dsi3BusImp_InterruptHandler_PdcmEvt);
      dsi3_InterruptRegisterCallback(dsi3_IRQ_DISC_EVT      , (dsi3_InterruptCallback_t)Dsi3BusImp_InterruptHandler_DiscEvt);
      dsi3_InterruptRegisterCallback(dsi3_IRQ_CRC_ERR_EVT   , (dsi3_InterruptCallback_t)Dsi3BusImp_InterruptHandler_CrcErrEvt);
      dsi3_InterruptRegisterCallback(dsi3_IRQ_PDCM_ERR_EVT  , (dsi3_InterruptCallback_t)Dsi3BusImp_InterruptHandler_PdcmErrEvt);
      dsi3_InterruptRegisterCallback(dsi3_IRQ_DISC_ERR_EVT  , (dsi3_InterruptCallback_t)Dsi3BusImp_InterruptHandler_DiscErrEvt);
      dsi3_InterruptRegisterCallback(dsi3_IRQ_FCC_ERROR     , (dsi3_InterruptCallback_t)Dsi3BusImp_InterruptHandler_FccErrEvt);
      dsi3_InterruptRegisterCallback(dsi3_IRQ_START_ERR_EVT , (dsi3_InterruptCallback_t)Dsi3BusImp_InterruptHandler_StartErrEvt);
      dsi3_InterruptRegisterCallback(dsi3_IRQ_TIMER_A_EVT   , (dsi3_InterruptCallback_t)Dsi3BusImp_InterruptHandler_TimerA_Evt);
      dsi3_InterruptRegisterCallback(dsi3_IRQ_TIMER_B_EVT   , (dsi3_InterruptCallback_t)Dsi3BusImp_InterruptHandler_TimerB_Evt);
//    dsi3_InterruptRegisterCallback(dsi3_IRQ_TIMER_C_EVT   , (dsi3_InterruptCallback_t)Dsi3BusImp_InterruptHandler_TimerC_Evt);
      dsi3_InterruptRegisterCallback(dsi3_IRQ_RCC_FINISH    , (dsi3_InterruptCallback_t)Dsi3BusImp_InterruptHandler_RccFinish);
//    dsi3_InterruptRegisterCallback(dsi3_IRQ_RCC_READY     , (dsi3_InterruptCallback_t)Dsi3BusImp_InterruptHandler_RccReady);
//    dsi3_InterruptRegisterCallback(dsi3_IRQ_SYNC_CNT_EVT  , (dsi3_InterruptCallback_t)Dsi3BusImp_InterruptHandler_SyncCntEvt);
/* --> 2018-08-06, poe: ESWDSI3-14 */  
      dsi3_InterruptRegisterCallback(dsi3_IRQ_DISC_CURR_EVT  	, (dsi3_InterruptCallback_t)&Dsi3BusImp_InterruptHandler_DiscCurrEvt);
/* --> 2018-08-06, poe: ESWDSI3-14 */
            
      /* Setup default communication mode */
      switch(busEnvData->Steering.CurrentCommunicationMode)
      {
        case Dsi3BusIf_eCOMM_PERIODICDATACOLLECTIONMODE:
        {
          /* ...PDCM. */
          loc_EnablePdcm(busEnvData);
        }
        break;
        case Dsi3BusIf_eCOMM_DISCOVERYMODE:
        {
          /* ...DISCOVERY.  */
          loc_EnableDisc(busEnvData);
          /* Propagate that the Discovery addressing has been started */
          loc_CallDiscProcessedCallback(busEnvData, Dsi3BusIf_eDISCSTAT_STARTED);
        }
        break;
        default:
        case Dsi3BusIf_eCOMM_COMMANDRESPONSEMODE:
        {
          /* ...CRM. */
          loc_EnableCrm(busEnvData);
        }
        break;
      }
      
      loc_CallModeChangedCallback(busEnvData, busEnvData->Steering.CurrentCommunicationMode);
      
      retVal = TRUE;
    }
    else{ /* Configuration data is invalid! */ }
  }
  else
  {
    /* Unable to perform error handling, as EnvData is not available */
  }
  return retVal;
}



/***************************************************************************//**
 * @brief Returns a selected sub interface, if available.
 *
 * @param        genericBusEnvData    bus environment data
 * @param        interfaceId          ID of target sub interface
 * @param        ifThisPtr            target this pointer to write the if pointer to
 *
 * @return         Error status
 *                 TRUE:  Callback function successfully registered
 *                 FALSE: Unable to register callback function, because command
 *                 index is out of allowed range
 *
 * The function expects a pointer to a callback function for handling a given CRM
 * command. If the corresponding command index is within the allowed range of [0, 15]
 * the function return value signals success. An error is signaled otherwise. A
 * given function pointer will overwrite a function callback, which has already
 * been registered for a given command index. Instead of passing a valid function
 * pointer, the NULL pointer may be passed to unregister a possibly registered function.
 *
 *
 * @image html Dsi3BusImp_GetSubInterface.png "Activity chart: Get Sub Interface"
 * @image latex Dsi3BusImp_GetSubInterface.png "Activity chart: Get Sub Interface"
 ******************************************************************************/
BUS_LAYER Dsi3BusIf_Bool_t Dsi3BusImp_GetSubInterface(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_InterfaceIds_t interfaceId, Dsi3BusIf_pThis_t ifThisPtr)
{  
  Dsi3BusIf_Bool_t retVal = FALSE;

  if(genericBusEnvData != DSI3_NULL && interfaceId == Dsi3_IfId_HWMODULE)
  {
    if (ifThisPtr != DSI3_NULL)
    {
      ifThisPtr->IfFunsTbl = (Dsi3BusIf_cpGenericInterfaceFunctions_t) &Dsi3HardwareModuleImp_InterfaceFunctions;
      ifThisPtr->EnvData = genericBusEnvData;
    }
    else{}

    retVal = TRUE;
  }
  else{}

  
  return(retVal);
}


/***************************************************************************//**
 * @brief Register single callback functions for CRM handling
 *
 * @param        genericEnvData       bus environment data
 * @param        callbackFun          Pointer to callback function which handles CRM command and
 *                                    prepares response data. NULL may be passed to unregister
 *                                    a callback function for a given CommandIndex.
 * @param        commandId            Command ID
 * @param        genericBusCbCtxData  Bus Callback Context Data
 *
 * @return         Error status
 *                 TRUE:  Callback function successfully registered
 *                 FALSE: Unable to register callback function, because command
 *                 index is out of allowed range
 *
 * Precondition:   none
 *
 * Postcondition:  none
 *
 * The function expects a pointer to a callback function for handling a given CRM
 * command. If the corresponding command index is within the allowed range of [0, 15]
 * the function return value signals success. An error is signaled otherwise. A
 * given function pointer will overwrite a function callback, which has already
 * been registered for a given command index. Instead of passing a valid function
 * pointer, the NULL pointer may be passed to unregister a possibly registered function.
 *
 *
 * @image html Dsi3BusImp_RegisterCrmCallbackFunction.png "Activity chart: Register CRM Callback Function"
 * @image latex Dsi3BusImp_RegisterCrmCallbackFunction.png "Activity chart: Register CRM Callback Function"
 ******************************************************************************/
BUS_LAYER Dsi3BusIf_Bool_t Dsi3BusImp_RegisterCrmCallbackFunction(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_CRMCallbackFun_t callbackFun, Dsi3BusIf_CmdID_t commandId, Dsi3BusIf_pGenericCbCtxData_t genericBusCbCtxData)
{
  Dsi3BusIf_Bool_t retVal = FALSE;
  
  if (DSI3_NULL != genericEnvData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t) genericEnvData;
    
    if (commandId < DSI3_CRM_NUMBER_OF_COMMANDS)
    {
      /* Command index within expected range -> register callback function */
      /* Boundary check not necessary, as commandID is limited to 0..15 */
      busEnvData->Crm_CmdFrmDescLst[commandId]    = callbackFun;
      busEnvData->Crm_CmdCbCtxData[commandId]     = genericBusCbCtxData;

      /* Successfully registered callback function -> Change return value */
      retVal = TRUE;
    }
    else
    {
      /* Index for callback function out of range -> keep return error flag */
    }  
  }
  else{ /* Error: EnvironmentData not initialized! */ }
  
  return retVal;
}


/***************************************************************************//**
 * @brief
 * Register callback functions for PDCM handling
 *
 * The function expects a pointer to a callback function for  handling a SYNC
 * pulse in PDCM. If the corresponding command index is within the allowed range [0]
 * the function return value signals success. An error is signaled otherwise. A
 * given function pointer will overwrite a function callback, which has already
 * been registered for a given command index. Instead of passing a valid function
 * pointer, the NULL pointer may be passed to unregister a possibly registered function.
 *
 * @param       genericEnvData      pointer to Bus environment data
 * @param       CallbackFun         pointer to callback function which handles PDCM sync pulse
 *                                  and prepares response data. NULL may be passed to unregister
 *                                  the callback function.
 * @param       genericBusCbCtxData pointer to generic callback context data 
 * @return      TRUE           if the Callback function was successfully registered,
 *                             FALSE     else
 *
 * @image html Dsi3BusImp_RegisterPdcmCallbackFunction.png "Activity chart: Register PDCM Callback Function"
 * @image latex Dsi3BusImp_RegisterPdcmCallbackFunction.png "Activity chart: Register PDCM Callback Function"
 ******************************************************************************/
BUS_LAYER Dsi3BusIf_Bool_t Dsi3BusImp_RegisterPdcmCallbackFunction(Dsi3BusIf_pGenericEnvData_t genericEnvData,Dsi3BusIf_PDCMCallbackFun_t CallbackFun, Dsi3BusIf_pGenericCbCtxData_t genericBusCbCtxData)
{
  Dsi3BusIf_Bool_t retVal = FALSE;
  
  if (DSI3_NULL != genericEnvData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t) genericEnvData;
    
      /* Register callback function */
      busEnvData->Pdcm_CmdFrmDesc     = CallbackFun;
      busEnvData->Pdcm_CmdCbCtxData   = genericBusCbCtxData;

      /* Successfully registered callback function -> Change return value */
      retVal = TRUE; 
  }
  else{ /* Error: EnvironmentData not initialized! */ }
  
  

  return retVal;
}





/**************************************************************************//**
 * @internal
 * @brief
 * (re)initializes DSI3 communication state 
 *
 * @param       busEnvData              pointer to Bus environment data
 * @param       doChangeCallback        TRUE - ModeChangedCallback to upper layer is called if mode has been changed
 * @return      n/a
 *
 * @image html loc_Dsi3BusImp_PrepareNextCommState.png "Activity chart: Prepare Next Communication State"
 * @image latex loc_Dsi3BusImp_PrepareNextCommState.png "Activity chart: Prepare Next Communication State"
 * ****************************************************************************/
BUS_LAYER void loc_Dsi3BusImp_PrepareNextCommState(loc_pDsi3EnvironmentData_t busEnvData, bool_t doChangeCallback)
{
  bool_t modeChanged = busEnvData->Steering.NextCommunicationMode != busEnvData->Steering.CurrentCommunicationMode;
  
  /* Clear force update flag */
  busEnvData->Steering.ForceCommunicationModeUpdate = FALSE;
  
  /* Next communication mode is... */
  switch(busEnvData->Steering.NextCommunicationMode)
  {
    case Dsi3BusIf_eCOMM_PERIODICDATACOLLECTIONMODE:
    {
      /* ...PDCM. */
      loc_EnablePdcm(busEnvData);
    }
    break;
    case Dsi3BusIf_eCOMM_DISCOVERYMODE:
    {
      /* ...DISCOVERY.  */
      loc_EnableDisc(busEnvData);
      /* Propagate that the Discovery addressing has been started */
      loc_CallDiscProcessedCallback(busEnvData, Dsi3BusIf_eDISCSTAT_STARTED);
    }
    break;
    default:
    case Dsi3BusIf_eCOMM_COMMANDRESPONSEMODE:
    {
      /*
       * ...CRM.
       * If loc_NextCommunicationMode is set to some undefined value, CRM is
       * enabled to still provide a communication channel to the sensor.
       */
      loc_EnableCrm(busEnvData);
    }
    break;
  }
  
  if (doChangeCallback && modeChanged)
  {
    loc_CallModeChangedCallback(busEnvData, busEnvData->Steering.CurrentCommunicationMode);
  }
  else{/* do nothing */}
  
}


/***************************************************************************//**
 * @brief returns the CRM Sync Count
 *
 * @return      CRMSyncCount      register value
 *
 * @image html Dsi3BusImp_GetCRMSyncCount.png "Activity chart: Get CRM Sync Count"
 * @image latex Dsi3BusImp_GetCRMSyncCount.png "Activity chart: Get CRM Sync Count"
 * ****************************************************************************/
BUS_LAYER Dsi3BufIf_SyncCountValue_t Dsi3BusImp_GetCRMSyncCount(void)
{
  return DSI3_SYNC_CNT_GET();
}


/***************************************************************************//**
 * @brief returns the last measured PDCM period length.
 *
 * @return      TimerCaptureValue      register value
 *
 * @image html Dsi3BusImp_GetPDCMMeasuredPeriodDuration.png "Activity chart: Get PDCM Measured Period Duration"
 * @image latex Dsi3BusImp_GetPDCMMeasuredPeriodDuration.png "Activity chart: Get PDCM Measured Period Duration"
 * ****************************************************************************/
BUS_LAYER Dsi3BufIf_TimerCaptureValue_t Dsi3BusImp_GetPDCMMeasuredPeriodDuration(void)
{
  return DSI3_TIMER_CAPTURE_GET();
}


/***************************************************************************//**
 * @brief returns the current hardware DSI3 configuration of the 1us clock.
 *
 * @return      ClockConfiguration      register value
 *
 * @image html Dsi3BusImp_Get1usClockCfg.png "Activity chart: Get 1us Clock Configuration"
 * @image latex Dsi3BusImp_Get1usClockCfg.png "Activity chart: Get 1us Clock Configuration"
 * ****************************************************************************/
BUS_LAYER Dsi3BusIf_ClkDiv_t Dsi3BusImp_Get1usClockCfg(void)
{
  return DSI3_CLK_1US_GET();
}


/**************************************************************************//**
 * @brief
 * updates the current bus configuration of the 1us clock.
 *
 * @param       genericBusEnvData       pointer to Bus environment data
 * @param       newClkCfg               16 bit cfg data for the 1us clock.
 * @return      none
 *
 * @image html Dsi3BusImp_Set1usClockCfg.png "Activity chart: Set 1us Clock Configuration"
 * @image latex Dsi3BusImp_Set1usClockCfg.png "Activity chart: Set 1us Clock Configuration"
 * ****************************************************************************/
BUS_LAYER Dsi3BusIf_Bool_t Dsi3BusImp_Set1usClockCfg(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_ClkDiv_t newClkCfg)
{
  Dsi3BusIf_Bool_t retVal = FALSE;
  
  if (DSI3_NULL != genericBusEnvData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t) genericBusEnvData;
    
    busEnvData->Steering.Cfg1usClock = newClkCfg;
    
    retVal = TRUE;
  }
  else{ /* Error: EnvironmentData not initialized! */ }

  return retVal;
}


/**************************************************************************//**
 * @brief
 * updates the current configuration of the CRM response offset.
 *
 * @param       genericBusEnvData             pointer to Bus environment data
 * @param       newCRMResponseTimeOffset      new crm response offset value
 * @return      TRUE                          if the CRM response time offset was tasked for change
 *              FALSE                         if the CRM response time offset was out of range
 *
 * @image html Dsi3BusImp_UpdateCRMResponseTimeOffset.png "Activity chart: Update CRM Response Time Offset"
 * @image latex Dsi3BusImp_UpdateCRMResponseTimeOffset.png "Activity chart: Update CRM Response Time Offset"
 * ****************************************************************************/
BUS_LAYER Dsi3BusIf_Bool_t Dsi3BusImp_UpdateCRMResponseTimeOffset(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_WordData_t newCRMResponseTimeOffset)
{
  Dsi3BusIf_Bool_t retVal = FALSE;
  
  if (DSI3_NULL != genericBusEnvData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t) genericBusEnvData;
    
    if (newCRMResponseTimeOffset <= DSI3_TIMERX_MAX_VALUE)
    {
      busEnvData->CrmRuntimeData.Steering.CrmResponseTimeOffset = newCRMResponseTimeOffset;
      
      retVal = TRUE;
    }
    else{ /* Target value exceeds 12 bits */ }
  }
  else{ /* Error: EnvironmentData not initialized! */ }

  return retVal;
}


/**************************************************************************//**
 * @brief
 * updates the current configuration of the PDCM 1st slot offset (us).
 *
 * @param       genericBusEnvData       pointer to Bus environment data
 * @param       newPDCMStartSlotOffset  new PDCM 1st slot offset (us)
 * @return      TRUE                    if the PDCM slot duration was tasked for change
 *              FALSE                   if the PDCM slot duration was out of range
 *
 * @image html Dsi3BusImp_UpdatePDCMStartSlotOffset.png "Activity chart: Update PDCM Start Slot Offset"
 * @image latex Dsi3BusImp_UpdatePDCMStartSlotOffset.png "Activity chart: Update PDCM Start Slot Offset"
 * ****************************************************************************/
BUS_LAYER Dsi3BusIf_Bool_t Dsi3BusImp_UpdatePDCMStartSlotOffset(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_WordData_t newPDCMStartSlotOffset)
{
  Dsi3BusIf_Bool_t retVal = FALSE;
  
  if (DSI3_NULL != genericBusEnvData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t) genericBusEnvData;
    
    if (newPDCMStartSlotOffset <= DSI3_TIMERX_MAX_VALUE)
    {
      busEnvData->PdcmRuntimeData.Steering.PdcmStartSlotOffset = newPDCMStartSlotOffset;
      
      retVal = TRUE;
    }
    else { /* Target value exceeds 12 bits */}
  }
   else{ /* Error: EnvironmentData not initialized! */ }

  return retVal;
}


/**************************************************************************//**
 * @brief
 * updates the current configuration of the PDCM single slot duration.
 *
 * @param       genericBusEnvData       pointer to Bus environment data
 * @param       newPDCMSlotDuration     new single slot duration (us)
 * @return      TRUE                    if the PDCM slot duration was tasked for change
 *              FALSE                   if the PDCM slot duration time was out of range
 *
 * @image html Dsi3BusImp_UpdatePDCMSlotDuration.png "Activity chart: Update PDCM Slot Duration"
 * @image latex Dsi3BusImp_UpdatePDCMSlotDuration.png "Activity chart: Update PDCM Slot Duration"
 * ****************************************************************************/
BUS_LAYER Dsi3BusIf_Bool_t Dsi3BusImp_UpdatePDCMSlotDuration(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_WordData_t newPDCMSlotDuration)
{
  Dsi3BusIf_Bool_t retVal = FALSE;
  
  if (DSI3_NULL != genericBusEnvData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t) genericBusEnvData;
    
    if (newPDCMSlotDuration <= DSI3_TIMERX_MAX_VALUE)
    {
      busEnvData->PdcmRuntimeData.Steering.PdcmSlotDuration = newPDCMSlotDuration;
      
      retVal = TRUE;
    }
    else{}
  }
   else{ /* Error: EnvironmentData not initialized! */ }
 
  return retVal;
}


/**************************************************************************//**
 * @brief
 * updates the current configuration of the PDCM period duration.
 *
 * @param       genericBusEnvData         pointer to Bus environment data
 * @param       newPDCMResponseDuration   new duration value for the PDCM period.
 * @return      TRUE                      if the PDCM period duration was tasked for change
 *              FALSE                     if the PDCM period duration was out of range
 *
 * @image html Dsi3BusImp_UpdatePDCMResponseDuration.png "Activity chart: Update PDCM Response Duration"
 * @image latex Dsi3BusImp_UpdatePDCMResponseDuration.png "Activity chart: Update PDCM Response Duration"
 * ****************************************************************************/
BUS_LAYER Dsi3BusIf_Bool_t Dsi3BusImp_UpdatePDCMResponseDuration(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_WordData_t newPDCMResponseDuration)
{
  Dsi3BusIf_Bool_t retVal = FALSE;
  
  if (DSI3_NULL != genericBusEnvData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t) genericBusEnvData;
    
    if (newPDCMResponseDuration <= DSI3_TIMERX_MAX_VALUE)
    {
      busEnvData->PdcmRuntimeData.Steering.PdcmResponseDuration = newPDCMResponseDuration;
      
      retVal = TRUE;
    }
    else{}
  }
   else{ /* Error: EnvironmentData not initialized! */ }
  
  return retVal;
}



/* --> 2018-03-05/JNAU: JIRA ESWDSI3-6, Additional interface function */
/**************************************************************************//**
 * @brief
 * updates the current configuration of the CRM blanking time offset.
 *
 * @param       genericBusEnvData             pointer to Bus environment data
 * @param       newCrmFCCBlankingTimeOffset   new crm blanking time offset value
 * @return      TRUE                          if the CRM FCC blanking time was tasked for change
 *              FALSE                         if the CRM FCC blanking time was out of range
 *
 * @image html Dsi3BusImp_UpdateCRMFCCBlankingTimeOffset.png "Activity chart: Update CRM Blanking Time Offset"
 * @image latex Dsi3BusImp_UpdateCRMFCCBlankingTimeOffset.png "Activity chart: Update CRM Blanking Time Offset"
 * ****************************************************************************/
BUS_LAYER Dsi3BusIf_Bool_t Dsi3BusImp_UpdateCRMFCCBlankingTimeOffset(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_Tick_t newCRMFCCBlankingTimeOffset)
{
  Dsi3BusIf_Bool_t retVal = FALSE;
  
  if (DSI3_NULL != genericBusEnvData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t) genericBusEnvData;
    
    if (newCRMFCCBlankingTimeOffset <= DSI3_TIMERX_MAX_VALUE)
    {
      busEnvData->CrmRuntimeData.Steering.CrmFCCBlankingTimeOffset = newCRMFCCBlankingTimeOffset;
      
      retVal = TRUE;
    }
    else{}
  }
  else{}

  return retVal;
}
/* <-- 2018-03-05/JNAU: JIRA ESWDSI3-6 */


/* --> 2018-03-05/JNAU: JIRA ESWDSI3-6, Additional interface function */
/**************************************************************************//**
 * @brief
 * updates the current configuration of the PDCM blanking time duration. 
 *
 * @param       genericBusEnvData             pointer to Bus environment data
 * @param       newPDCMFCCBlankingTimeOffset  new duration value for the PDCM blanking time.
 * @return      TRUE                          if the PDCM FCC blanking time was tasked for change
 *              FALSE                         if the PDCM FCC blanking time was out of range
 *
 * @image html Dsi3BusImp_UpdatePDCMFCCBlankingTimeOffset.png "Activity chart: Update PDCM Blanking Time"
 * @image latex Dsi3BusImp_UpdatePDCMFCCBlankingTimeOffset.png "Activity chart: Update PDCM Blanking Time"
 * ****************************************************************************/
BUS_LAYER Dsi3BusIf_Bool_t Dsi3BusImp_UpdatePDCMFCCBlankingTimeOffset(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_Tick_t newPDCMFCCBlankingTimeOffset)
{
  Dsi3BusIf_Bool_t retVal = FALSE; 
  
  if (DSI3_NULL != genericBusEnvData) 
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t) genericBusEnvData;
    
    if (newPDCMFCCBlankingTimeOffset <= DSI3_TIMERX_MAX_VALUE)
    {
      /* Update PDCM blanking time to new value */
      busEnvData->PdcmRuntimeData.Steering.PdcmFCCBlankingTimeOffset = newPDCMFCCBlankingTimeOffset;
      
      retVal = TRUE;
    }
    else {}
        
  }
  else{}
  
  return retVal;
}
/* <-- 2018-03-05/JNAU: JIRA ESWDSI3-6 */


/**************************************************************************//**
 * @internal
 * @brief
 * refills PDCM response buffer 
 *
 * @param       busEnvData     pointer to Bus environment data
 *                             PDCM sync pulse and prepare response data.
 * @return      n/a
 *
 * @image html loc_Dsi3BusImp_PreparePDCMBuffer.png "Activity chart: Prepare PDCM Buffer"
 * @image latex loc_Dsi3BusImp_PreparePDCMBuffer.png "Activity chart: Prepare PDCM Buffer"
 * ****************************************************************************/
BUS_LAYER void loc_Dsi3BusImp_PreparePDCMBuffer(loc_pDsi3EnvironmentData_t busEnvData)
{  
  /* Set default response mode action */
  Dsi3BusIf_CmdIdAction_t cbStatus = Dsi3BusIf_eCMDACT_IGNORE;

  /* Execute callback function to handle PDCM communication */
  if (DSI3_NULL != busEnvData->Pdcm_CmdFrmDesc)
  {
    cbStatus = busEnvData->Pdcm_CmdFrmDesc(busEnvData, busEnvData->PdcmRuntimeData.ResponseBuffer, busEnvData->PdcmRuntimeData.Steering.BufferSize, &busEnvData->PdcmRuntimeData.Steering.MsgLen, busEnvData->CurrentSlaveID, busEnvData->Pdcm_CmdCbCtxData);
    
     /* check if callback processing went ok..*/
    if (Dsi3BusIf_eCMDACT_RESPONSE == cbStatus)
    {
      /* Set buffer address */
      
      /* 
      * Msg(2:0306) [I] Cast between a pointer to object and an integral type.
      *
      * According to QA-C help "this type of operation is not uncommon in embedded 
      * software applications where memory mapped I/O ports must be addressed."
      */  
      // PRQA S 0306 1 
      DSI3_CTRL_DMA_BASE_ADDR_SET((uint32_t) ((uint32_t)((uint32_t) busEnvData->PdcmRuntimeData.ResponseBuffer + busEnvData->PdcmRuntimeData.Steering.MsgLen) - (uint32_t) busEnvData->Steering.HardwareAddsCRC));
      
      /* Set buffer length */
      DSI3_CTRL_BUFFER_LENGTH_SET((Dsi3BusIf_ByteData_t)(busEnvData->PdcmRuntimeData.Steering.MsgLen - (Dsi3BusIf_ByteData_t) busEnvData->Steering.HardwareAddsCRC));


	  /* --> 18-09-06, poe: ESWDSI3-13
	   * Added global irq disable and state check to prevent preemptive switching to idle
	   * state if error irq occurs shortly before.
	   */
	  istate_t istate = __get_interrupt_state();
      __disable_interrupt();

	  if (Dsi3BusIf_eSTATE_PDCMPREPAREBUFFER == busEnvData->Steering.Dsi3State)
      {
	  	/* --> 18-07-18, poe: ESWDSI3-12
       	* To prevent race condition on bus state caused by RCC_FINISH irq handler,
	   	* dsi3 state is updated before enabling RCC_FINISH irq.
       	*/
      	/* Switch driver internal state */
      	busEnvData->Steering.Dsi3State = Dsi3BusIf_eSTATE_ANSWERING;
	  	/* --> 18-07-18, poe: ESWDSI3-12 */
	  
      	/* Clear rcc finish irq */
      	DSI3_CTRL_IRQ_CLEAR(dsi3_IRQ_RCC_FINISH);
      
      	/* Enable rcc finish irq */
      	DSI3_CTRL_IRQ_ENABLE(dsi3_IRQ_RCC_FINISH);
	}
	else
	{
		/* Switch driver internal state */
      	busEnvData->Steering.Dsi3State = Dsi3BusIf_eSTATE_IDLE;	
	}
      /* Re-enable irqs */
	  __set_interrupt_state(istate);
      /* --> 18-09-06, poe: ESWDSI3-13 */
      /*
       * Driver is waiting for rcc finish interrupt now
       */
    }
    else
    {
      /* No Response to send. */
    }
  }
  else
  {
    /* Return to default communication mode */
    busEnvData->Steering.NextCommunicationMode = busEnvData->Steering.DefaultCommunicationMode;
    loc_Dsi3BusImp_PrepareNextCommState(busEnvData, TRUE);
  }
}




/**************************************************************************//**
 * @brief
 * Handles non time critical task operations
 *
 * The bus task is responsible for the reinitializing of the DSI3 module 
 * after communication mode change and for the preparation of the PDCM response
 * buffer after switching to PDCM mode.
 * It also updates the device address if a new address value has been set.
 *
 * @param       genericEnvData    Pointer to bus environment data
 * @return      none
 *
 * @image html Dsi3BusImp_Task.png "Activity chart: Task"
 * @image latex Dsi3BusImp_Task.png "Activity chart: Task"
 * ****************************************************************************/
BUS_LAYER void Dsi3BusImp_Task(Dsi3BusIf_pGenericEnvData_t genericEnvData)
{
  if (DSI3_NULL != genericEnvData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericEnvData;

    /* Act according to bus state */
    switch (busEnvData->Steering.Dsi3State)
    {
      case (Dsi3BusIf_eSTATE_PDCMPREPAREBUFFER): /* set first pdcm msg */
      {
        /* 
         * State is entered after switching to pdcm mode 
         * and prepares the response buffer for next pdcm sync
         */
        
        loc_Dsi3BusImp_PreparePDCMBuffer(busEnvData);
      }
      break;
      case (Dsi3BusIf_eSTATE_WAIT_FOR_DISC_PULSE):
      {
        /* 
         * State is handled in DSI3 DiscPulse interrupt 
         */
      }
      break;
      case Dsi3BusIf_eSTATE_RESPONSE_PROCESSED:
      {
        if (Dsi3BusIf_eCOMM_PERIODICDATACOLLECTIONMODE == busEnvData->Steering.CurrentCommunicationMode)
        {
          loc_CallPdcmProcessedCallback(busEnvData);
          /* Update the DSI3 communication state */
       
          /* Reset PDCM mode */
          loc_ResetPdcm(busEnvData);
        
          /* Switch state to preparing pdcm response buffer */
          busEnvData->Steering.Dsi3State = Dsi3BusIf_eSTATE_PDCMPREPAREBUFFER;   
        }
        else
        {
          if  (Dsi3BusIf_eCOMM_COMMANDRESPONSEMODE == busEnvData->Steering.CurrentCommunicationMode)
          {
            loc_CallCrmProcessedCallback(busEnvData);
    
            /* Update the DSI3 communication state */
            loc_ResetCrm(busEnvData);            
          }
          else{ /* Do nothing */ }
          
          /* Return to idle state */
          busEnvData->Steering.Dsi3State = Dsi3BusIf_eSTATE_IDLE;
        }        
      }
      break;
      case (Dsi3BusIf_eSTATE_ANSWERING):
      {
       /* 
        * State is handled in DSI3 RCC_Finish interrupt 
        */
      }
      break;
      default:
      case (Dsi3BusIf_eSTATE_IDLE):
      {
        /* 
         * State is entered as default valid state if currently nothing is to do
         */
        /* Check if NAD has been changed and update accordingly */
        if (busEnvData->NewSlaveID != busEnvData->CurrentSlaveID)
        {
          busEnvData->CurrentSlaveID = busEnvData->NewSlaveID;
          DSI3_CTRL_SOURCE_ID_SET(busEnvData->CurrentSlaveID);
        }
        else{ /* Do nothing. */ }
        
        /* If chip time was changed, update chip time in the DSI3 module */
        if (((Dsi3BusIf_ChipTime_t) DSI3->CONFIG.bit.t_chip) != busEnvData->Steering.ChipTime)
        {
          /* Update register value */
          DSI3_CTRL_CONFIG_T_CHIP_SET(busEnvData->Steering.ChipTime);
          
          /* Reinitialize */
          loc_Dsi3BusImp_PrepareNextCommState(busEnvData, TRUE);
        }
        else{ /* Do nothing. */ }       

        if ((TRUE == busEnvData->Steering.ForceCommunicationModeUpdate) || (busEnvData->Steering.NextCommunicationMode != busEnvData->Steering.CurrentCommunicationMode))
        {
          loc_Dsi3BusImp_PrepareNextCommState(busEnvData, TRUE);
        }
        else{ /* Do nothing. */ }
      }
      break;
    }
      /* Check if DSI3 clock needs to be updated */
      if ((0u < busEnvData->Steering.Cfg1usClock) && (DSI3_CLK_1US_GET() != busEnvData->Steering.Cfg1usClock))
      {
        /* Update DSI3 1us clock cfg with new provided config value. */
        DSI3_CLK_1US_SET(busEnvData->Steering.Cfg1usClock);
        /* --> 19-02-25, poe: Bugfix ESWDSI3-23
         * Reset Cfg1usClock value to 0 after updating to prevent unwanted clock updates.
         */
        busEnvData->Steering.Cfg1usClock = 0u;
        /* --> 19-02-25, poe: Bugfix ESWDSI3-23 */
      }
      else{ /* Do nothing. */ }     
    }
  else{/* Error: EnvironmentData not initialized! */}
  return;
}



/**************************************************************************//**
 * @brief
 * Disables DSI3 module and interrupt processing and
 * switches bus state machine to idle CRM.
 *
 * @param       genericEnvData    Pointer to bus environment data
 * @return      none
 *
 * @image html Dsi3BusImp_Shutdown.png "Activity chart: Shutdown"
 * @image latex Dsi3BusImp_Shutdown.png "Activity chart: Shutdown"
 * ****************************************************************************/
BUS_LAYER void Dsi3BusImp_Shutdown(Dsi3BusIf_pGenericEnvData_t genericEnvData)
{
  /* Disable all dsi3 interrupts */
  DSI3_CTRL_IRQ_DISABLE_ALL();
   
  /* Disable dsi3 module */
  DSI3->ANALOG_CTRL.bit.dsi3_enable = 0u;
  
  if (DSI3_NULL != genericEnvData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericEnvData;
    
    /* Remove all registered callback tables */
    for(uint8_t i = 0; i < DSI3_MAX_NUMBER_OF_CALLBACK_TABLES; i++)
    {
      busEnvData->Callbacks[i] = DSI3_NULL;
      busEnvData->CallbackCtxData[i] = DSI3_NULL;
    }
    
    busEnvData->Steering.CurrentCommunicationMode = busEnvData->Steering.DefaultCommunicationMode;
    busEnvData->Steering.NextCommunicationMode = busEnvData->Steering.DefaultCommunicationMode;
    busEnvData->Steering.Dsi3State = Dsi3BusIf_eSTATE_IDLE;
  }
  else{ /* Error: EnvironmentData not initialized! */ }
  
  return;
}


/***************************************************************************//**
 * @brief Returns the current DSI3 status timer counter value
 *
 * @return      TimerCounterValue
 *
 * @image html Dsi3BusImp_GetTimestamp.png "Activity chart: Get Timestamp"
 * @image latex Dsi3BusImp_GetTimestamp.png "Activity chart: Get Timestamp"
 * ****************************************************************************/
BUS_LAYER Dsi3BusIf_Time_t Dsi3BusImp_GetTimestamp(void)
{
  return DSI3_CTRL_TIMER_COUNTER();
}

/**************************************************************************//**
 * @brief
 * Set the new device address.
 *
 * The device address will be updated to the new value during the next bus task
 * execution.
 *
 * @param       genericEnvData  Pointer to bus environment data
 * @param       deviceID        new device address
 * @return      TRUE            if the device address was tasked for change
 *              FALSE           if the device address was out of range
 *
 * @image html Dsi3BusImp_UpdateDeviceAddress.png "Activity chart: Update Device Address"
 * @image latex Dsi3BusImp_UpdateDeviceAddress.png "Activity chart: Update Device Address"
 * ****************************************************************************/
BUS_LAYER Dsi3BusIf_Bool_t Dsi3BusImp_UpdateDeviceAddress(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_SlaveID_t deviceID)
{
  Dsi3BusIf_SlaveID_t retVal = FALSE;
  
  if (DSI3_NULL != genericEnvData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericEnvData;
     
    if ((busEnvData->MaxSlaveID >= deviceID) && (DSI3_NAD_BROADCAST < deviceID))
    {
      busEnvData->NewSlaveID = deviceID;

      retVal = TRUE;
    }
    else{ /* Error: nad value out of range */ }
  }
  else{ /* Error: EnvironmentData not initialized! */  }
  
  return retVal;
}


/**************************************************************************//**
 * @brief
 * Set the new device chiptime.
 *
 * The device chiptime will be updated to the new value during the next bus task
 * execution.
 *
 * @param       genericEnvData  Pointer to bus environment data
 * @param       chiptime        new chiptime
 * @return      TRUE            if the device chiptime was tasked for change
 *              FALSE           if the chiptime was out of range
 *
 * @image html Dsi3BusImp_UpdateChipTime.png "Activity chart: Update Chip Time"
 * @image latex Dsi3BusImp_UpdateChipTime.png "Activity chart: Update Chip Time"
 * ****************************************************************************/
BUS_LAYER Dsi3BusIf_Bool_t Dsi3BusImp_UpdateChipTime(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_ChipTime_t chiptime)
{
  Dsi3BusIf_SlaveID_t retVal = FALSE;

  if (DSI3_NULL != genericEnvData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericEnvData;

    busEnvData->Steering.ChipTime = chiptime;

    retVal = TRUE;
  }
  else{ /* Error: EnvironmentData not initialized! */ }
  
  return retVal;
}


/***************************************************************************//**
 * @brief sets the next communication mode to be assigned in the next bus task execution and
 *        returns the next communication mode for validation.
 *
 * @param       genericBusEnvData                           Pointer to bus environment data
 * @param       Dsi3Bus_eNextCommunicationMode              communication mode to be set
 * @return      Dsi3BusIf_eCOMM_COMMANDRESPONSEMODE         if the next mode is CRM \n
 *              Dsi3BusIf_eCOMM_PERIODICDATACOLLECTIONMODE  if the next mode is PDCM \n
 *              Dsi3BusIf_eCOMM_DISCOVERYMODE               if the next mode is DISC
 *
 * @image html Dsi3BusImp_ChangeCommunicationMode.png "Activity chart: Change Communication Mode"
 * @image latex Dsi3BusImp_ChangeCommunicationMode.png "Activity chart: Change Communication Mode"
 * ****************************************************************************/
Dsi3BusIf_eCommunicationMode_t Dsi3BusImp_ChangeCommunicationMode(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_eCommunicationMode_t dsi3Bus_eNextCommunicationMode)
{
  Dsi3BusIf_eCommunicationMode_t retVal = Dsi3BusIf_eCOMM_COMMANDRESPONSEMODE;
  
  if (DSI3_NULL != genericBusEnvData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericBusEnvData;
    
    busEnvData->Steering.ForceCommunicationModeUpdate = (busEnvData->Steering.NextCommunicationMode == dsi3Bus_eNextCommunicationMode ? TRUE : FALSE);
    
    /* Set followup comm mode */
    busEnvData->Steering.NextCommunicationMode = dsi3Bus_eNextCommunicationMode;

    /* Set retVal to follow up comm mode */
    retVal = busEnvData->Steering.NextCommunicationMode;
  }
  else{ /* Error: EnvironmentData not initialized! */ }
   
  return retVal;
}


/***************************************************************************//**
 * Transport Layer interface function.
 * @param   genericEnvData          pointer to bus layer environment data
 
 * @return  Dsi3BusIf_Bool_t      TRUE  - low signal occured since last check,
 *                                FALSE - else
 *
 * Checks for communication idle state.
 *
 * @image html Dsi3BusImp_CheckBusActivityFun.png "Activity char: Check Bus Activity"
 * @image latex Dsi3BusImp_CheckBusActivityFun.png "Activity char: Check Bus Activity"
 ******************************************************************************/
BUS_LAYER Dsi3BusIf_Bool_t Dsi3BusImp_CheckBusActivityFun(Dsi3BusIf_pGenericEnvData_t genericEnvData)
{
  Dsi3BusIf_Bool_t retVal = FALSE;
  
  if (DSI3_NULL != genericEnvData)
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t)genericEnvData;
    
    /* Save registers */
    istate_t istate = __get_interrupt_state();
    __disable_interrupt();   
       
    /* Get activity flag register */
    retVal = busEnvData->Steering.BusActivityFlag;
    /* Clear activity flag register */
    busEnvData->Steering.BusActivityFlag = FALSE;
    
    /* Restore registers */
    __set_interrupt_state (istate);
  }
  else{ /* Error: EnvironmentData not initialized! */ }

  return retVal;
}
 

/***************************************************************************//**
 *@brief 
 * Appends a callback table to the callback table pool if there is a
 * free slot available.
 *
 * @param   genericEnvData        pointer to bus environment data
 * @param   callbackFunctions   	const pointer to target callback table
 * @param   genericCbCtxData      pointer to generic callback context data  
 *
 * @return  Dsi3BusIf_Bool_t      TRUE  - The callback table was added successfully
 *                                FALSE - else
 *
 * @image html Dsi3BusImp_AppendCallbackTableFun.png "Activity chart: Append Callback Table Function"
 * @image latex Dsi3BusImp_AppendCallbackTableFun.png "Activity chart: Append Callback Table Function"
 ******************************************************************************/
BUS_LAYER Dsi3BusIf_Bool_t Dsi3BusImp_AppendCallbackTableFun(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_cpCallbackFunctions_t callbackFunctions, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  Dsi3BusIf_Bool_t retVal = FALSE;
  
  if ((DSI3_NULL != genericEnvData) &&
      (DSI3_NULL != callbackFunctions) &&
      (DSI3BUS_INTERFACE_MODULE_API_VERSION == callbackFunctions->CallbackVersion))
  {
    loc_pDsi3EnvironmentData_t busEnvData = (loc_pDsi3EnvironmentData_t) genericEnvData;
    Dsi3BusIf_ByteData_t idx;

    /* Append callback table if there is free space */
    for(idx = 0; idx < DSI3_MAX_NUMBER_OF_CALLBACK_TABLES; idx++)
    {
      if(callbackFunctions == busEnvData->Callbacks[idx])
      {
        break;
      }
      else if(DSI3_NULL == busEnvData->Callbacks[idx])
      {
        busEnvData->Callbacks[idx]       = callbackFunctions;
        busEnvData->CallbackCtxData[idx] = genericCbCtxData;
        retVal = TRUE;
        break;
      }
      else{ /* No callback configured. */ }
    }
  }

  return(retVal);
}

/***************************************************************************//**
 *@brief 
 * Removes a callback table from the callback table pool if it is stored there.
 *
 * @param   genericEnvData          pointer to bus environment data
 * @param   callbackFunctions				const pointer to target callback table
 * @param   genericCbCtxData        pointer to generic callback context data  
 *
 * @return  Dsi3BusIf_Bool_t        TRUE  - The callback table was removed successfully
 *                                  FALSE - else
 *
 * @image html Dsi3BusImp_RemoveCallbackTableFun.png "Activity chart: Remove Callback Table Function"
 * @image latex Dsi3BusImp_RemoveCallbackTableFun.png "Activity chart: Remove Callback Table Function"
 ******************************************************************************/
BUS_LAYER Dsi3BusIf_Bool_t Dsi3BusImp_RemoveCallbackTableFun(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_cpCallbackFunctions_t callbackFunctions, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData)
{
  Dsi3BusIf_Bool_t retVal = FALSE;

  if(DSI3_NULL != genericEnvData)
  {
    loc_pDsi3EnvironmentData_t protoEnvData = (loc_pDsi3EnvironmentData_t) genericEnvData;
    Dsi3BusIf_ByteData_t i;

    /* Search for callback table address and delete it */
    for(i = 0; i < DSI3_MAX_NUMBER_OF_CALLBACK_TABLES; i++)
    {
      if(protoEnvData->Callbacks[i] == callbackFunctions)
      {
#if ( DSI3_MAX_NUMBER_OF_CALLBACK_TABLES != 1u )

	Dsi3BusIf_ByteData_t j;
        
	for(j = i; j < (Dsi3BusIf_ByteData_t)(DSI3_MAX_NUMBER_OF_CALLBACK_TABLES - 1u); j++)
        {
          protoEnvData->Callbacks[j] = protoEnvData->Callbacks[j + 1u];
        }
#endif

        protoEnvData->Callbacks[DSI3_MAX_NUMBER_OF_CALLBACK_TABLES - 1u]       = DSI3_NULL;
        protoEnvData->CallbackCtxData[DSI3_MAX_NUMBER_OF_CALLBACK_TABLES - 1u] = DSI3_NULL;
        retVal = TRUE;
        break;
      }
      else{ /* Currently selected callback table is not the target */ }
    }
  }
  else{ /* Error: EnvironmentData is invalid */ }

  return(retVal);
}
/** @} dsi3_Driver */
