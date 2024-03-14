/** @addtogroup dsi3_Driver
 * @{ */
/***************************************************************************/
/** @file      Dsi3Bus_Implementation.h
 *
 * @brief      DSI3 Bus layer component for managing the DSI3 hardware module.
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
 * @section history_sec_Implementation_h Revision History
 * $Id: Dsi3Bus_Implementation.h 422 2019-03-14 14:55:33Z poe $
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who  Ver  Comment
 * -------------------------------------------------------------------
 * 19/02/25 (F) POE  1005 Updated Get1usClkCfg and Set1usClkCfg description
 * 19/01/11 (F) POE  1004 Updated default RampOn duration
 * 18/09/24 (F) POE  1003 Added define for discovery mode debounce value.
 * 18/04/17 (F) POE  1002 Added GetSubInterface, UpdateCRMFCCBlankingTimeOffset &
 *                        UpdatePDCMFCCBlankingTimeOffset IF funs, 
 *                        Removed DelayPDCMErrHandlingFun and DelayDISCErrHandlingFun IF funs
 *                        Added bool return value to all setter IF functions.
 * 18/04/06 (F) POE  1001 Removed min blanking time define
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
 * @version      $Revision: 422 $
 *
 *
 * $State: Exp $
 * $Author: poe $
 *
 * Additional markers:
 *
 */

#ifndef DSI3_DRIVER_H_
#define DSI3_DRIVER_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "Dsi3DrvImp_CompilationConfig.h"
#include "Dsi3Bus_Interface.h"
#include "Dsi3Bus_Defaults.h"
/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define DSI3_IMPL_CFG_DATA_VERSION                                        (0x0103u)       /**< @brief Expected config data version */
#define DSI3_IMPL_TARGET_HARDWARE_VERSION                                 (0x0001u)       /**< @brief Designated compatible hardware version */
   
/* TODO: finalize */   
#define DSI3BUSIMP_ENVIRONMENT_DATA_SZE                                   (   340u)       /**< @brief Bus environment data byte size */

#define DSI3BUSIMP_PDCM_SYNC_TIME                                         (     4u)       /**< @internal PDCM sync hardware delay */

#define DSI3_DRV_DISC_RAMPON_DELAY_DEFAULT                                (    64u)       /**< @internal Default: time offset for DISCOVERY mode ramp on start (us) */
#define DSI3_DRV_DISC_RAMPON_DURATION_DEFAULT                             (    28u)       /**< @internal Default: time offset for DISCOVERY mode ramp on duration (us) */
#define DSI3_DRV_DISC_BLANK_OFFSET                                        (     5u)       /**< @internal: offset for the blanking time during discovery mode: DISC period - offset = blanking time */
#define DSI3_DRV_DISC_DEBOUNCE_VAL                                        (    1u)        /**< @internal: debounce value for DISC mode signal evaluation */
#define DSI3BUSIMP_MSG_BUF_SZE_MIN                                        (     3u)       /**< @internal Minimal msg length definition for a DSI3 response msg */
#define DSI3BUSIMP_MSG_BUF_SZE_MAX                                        (    63u)       /**< @internal Maximal msg length definition for a DSI3 response msg */

#define DSI3BUSIMP_DEFAULT_COMMUNICATIONMODE_DEFAULT                      (Dsi3BusIf_eCOMM_COMMANDRESPONSEMODE)           /**< @internal Default DSI3 communication mode default */

#define DSI3_DRV_PDCM_SLOT_START(start_offset, slot_num, slot_duration)    ((start_offset) + ((slot_num)*(slot_duration))) /**< @internal Calculate slot time offset, slot_num: 0 .. 15 */
/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/***************************************************************************//**
 * @brief Struct for BUS layer implementation specific configuration data.
 ******************************************************************************/
struct Dsi3BusImp_sCfgData
{
  Dsi3BusIf_InterfaceVersion_t                          Version;                        /**< Config data struct version */ 
  Dsi3BusIf_SlaveID_t                                   SlaveID;                        /**< Initial NAD */
  Dsi3BusIf_SlaveID_t                                   MaximalSlaveID;                 /**< Maximal numbers of allowed slaves ( 0 < maxNAD <= 15)*/
  nvic_cpInterfaceFunctions_t                           NvicInterfaceFunctions;         /**< Pointer to NVIC IF */
  Dsi3BusIf_ByteData_t                                  PDCMOutBufferSize;              /**< Application definition for desired PDCM response buffer size */
  Dsi3BusIf_Bool_t                                      HardwareAddsCRC;                /**< Application configuration if response CRC is added by hardware */
  Dsi3BusIf_Bool_t                                      EnableAutoSync;                 /**< Application configuration if hardware should autosync */
  Dsi3BusIf_ChipTime_t                                  RCC_ChipTime;                   /**< Application configured chiptime */
  Dsi3BusIf_RCC_Slope_t                                 RCC_SlopeSel;                   /**< Application configured RCC slope selection */
  Dsi3BusIf_RCC_Curve_t                                 RCC_CurveSel;                   /**< Application configured RCC current waveform selection */
  Dsi3BusIf_RCC_CurrentOffset_t                         RCC_CurrentOffset;              /**< Application configured RCC current offset value */ 
  Dsi3BusIf_DebounceValue_t                             Dsi3DebounceValue;              /**< Application configured debounce value */
  Dsi3BusIf_FCC_TBit_t                                  FCC_BitTime;                    /**< Application configured FCC bit time */
  Dsi3BusIf_Time_t                                      CRMResponseTimeOffset;          /**< Time offset of the crm response msg */
  Dsi3BusIf_Time_t                                      CRMFCCBlankingTimeOffset;       /**< Time offset for FCC blanking after CRM cmd receive (default: 96us) */    
  Dsi3BusIf_Bool_t                                      CRMEnableSlaveIdPrefilter;      /**< 1 - Enable filtering of crm messages that are not broadcast and not adressed to this node; 
                                                                                             0 - CRM addressing is verified by application */
  Dsi3BusIf_Time_t                                      PDCMStartSlotOffset;            /**< Time offset of the first msg slot in pdcm mode (default: 50us) */
  Dsi3BusIf_Time_t                                      PDCMFCCBlankingTimeOffset;      /**< Time offset for FCC blanking after sync receive (us)*/    
  Dsi3BusIf_Time_t                                      PDCMResponseDuration;           /**< Overall pdcm response time frame */
  Dsi3BusIf_Time_t                                      PDCMSlotDuration;               /**< Time duration of single pdcm slot */
  Dsi3BusIf_Bool_t                                      PDCMDelayErrEvtHandling;        /**< Enable delayed processing of PDCM err event handling */
  Dsi3BusIf_Time_t                                      DISCRampOnDelay;                /**< Duration in us before starting the current ramping (default: 64us) */
  Dsi3BusIf_Time_t                                      DISCRampOnDuration;             /**< Length of the current ramping on duration */
  Dsi3BusIf_Time_t                                      DISCPeriodLength;               /**< Length of the period between two discovery pulses (us) */
  Dsi3BusIf_Bool_t                                      DISCDelayErrEvtHandling;        /**< Enable delayed processing of DISC err event handling */
  Dsi3BusIf_eCommunicationMode_t                        DefaultCommunicationMode;       /**< Default DSI3 communication mode */
};

typedef struct Dsi3BusImp_sCfgData                      Dsi3BusImp_CfgData_t;           /**< @brief typedef for Dsi3BusImp_sCfgData */
typedef        Dsi3BusImp_CfgData_t*                    Dsi3BusImp_pCfgData_t;          /**< @brief pointer for Dsi3BusImp_CfgData_t */
typedef const  Dsi3BusImp_CfgData_t*                    Dsi3BusImp_cpCfgData_t;         /**< @brief const pointer for Dsi3BusImp_CfgData_t */

#if (1u == DSI3BUSIMP_EXT_IFFUN_STRCT_ACCESS)
  extern const Dsi3BusIf_sInterfaceFunctions_t          Dsi3BusImp_InterfaceFunctions;  /**< @brief external interface declaration */
#endif
//


/* ****************************************************************************/
/* **************************** GLOBAL VARIABLES ******************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ********************* EXTERNAL FUNCTIONS / INTERFACE ***********************/
/* ****************************************************************************/

/****************************************************************************//**
 * @brief
 * Initializes DSI3 module and bus environment data.
 *
 * @param       genericBusEnvData   pointer to bus environment data
 * @param       busEnvDataSze       bus environment data size
 * @param       genericImpCfgData   pointer init parameters for the bus layer from the appl layer
 * @return      TRUE                if the initialization process was successful,
 *              FALSE               else
 * ****************************************************************************/
Dsi3BusIf_Bool_t Dsi3BusImp_Initialization( Dsi3BusIf_pGenericEnvData_t       genericBusEnvData, 
                                            Dsi3BusIf_EnvDataSze_t            busEnvDataSze,
                                            Dsi3BusIf_cpGenericImpCfgData_t   genericImpCfgData);



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
 ******************************************************************************/
Dsi3BusIf_Bool_t Dsi3BusImp_GetSubInterface(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_InterfaceIds_t interfaceId, Dsi3BusIf_pThis_t ifThisPtr);

/****************************************************************************//**
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
 * ****************************************************************************/
Dsi3BusIf_Bool_t Dsi3BusImp_UpdateDeviceAddress(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_SlaveID_t deviceID);


/****************************************************************************//**
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
 * ****************************************************************************/
Dsi3BusIf_Bool_t Dsi3BusImp_UpdateChipTime(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_ChipTime_t chiptime);


/****************************************************************************//**
 * @brief
 * Handles non time critical task operations
 *
 * The bus task is responsible for the reinitializing of the DSI3 module 
 * after communication mode change and for the preparation of the PDCM response
 * buffer after switching to PDCM mode.
 * It also updates the device address if a new address value has been set.
 *
 * @param       genericEnvData          Pointer to bus environment data
 * @return      none
 * ****************************************************************************/
void Dsi3BusImp_Task (Dsi3BusIf_pGenericEnvData_t genericEnvData);


/****************************************************************************//**
 * @brief sets the next communication mode to be assigned in the next bus task execution and
 *        returns the next communication mode for validation.
 *
 * @param       genericBusEnvData                           Pointer to bus environment data
 * @param       Dsi3Bus_eNextCommunicationMode              communication mode to be set
 * @return      Dsi3BusIf_eCOMM_COMMANDRESPONSEMODE         if the next mode is CRM \n
 *              Dsi3BusIf_eCOMM_PERIODICDATACOLLECTIONMODE  if the next mode is PDCM \n
 *              Dsi3BusIf_eCOMM_DISCOVERYMODE               if the next mode is DISC
 * ****************************************************************************/
Dsi3BusIf_eCommunicationMode_t Dsi3BusImp_ChangeCommunicationMode(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_eCommunicationMode_t dsi3Bus_eNextCommunicationMode);


/****************************************************************************//**
 * @brief
 * Disables DSI3 module and interrupt processing and
 * switches bus state machine to idle CRM.
 *
 * @param       genericEnvData  Pointer to bus environment data
 * @return      none
 * ****************************************************************************/
void  Dsi3BusImp_Shutdown(Dsi3BusIf_pGenericEnvData_t genericEnvData);  


/***************************************************************************//**
 * @brief Returns the current DSI3 status timer counter value
 *
 * @return      TimerCounterValue
 * ****************************************************************************/
Dsi3BusIf_Time_t Dsi3BusImp_GetTimestamp(void);


/****************************************************************************//**
 * @brief
 * returns the current hardware DSI3 configuration value of the 1us clock.
 *
 * @return      Dsi3BusIf_ClkDiv_t      16 bit register value
 * ****************************************************************************/
Dsi3BusIf_ClkDiv_t Dsi3BusImp_Get1usClockCfg(void);


/****************************************************************************//**
 * @brief
 * returns the last crm sync cnt measured by the hardware.
 *
 * @return      Dsi3BufIf_SyncCountValue_t      16 bit register value 
 * ****************************************************************************/
Dsi3BufIf_SyncCountValue_t Dsi3BusImp_GetCRMSyncCount(void);


/****************************************************************************//**
 * @brief
 * returns the last pdcm duration measured by the hardware.
 *
 * @return      Dsi3BufIf_TimerCaptureValue_t   16 bit register value 
 * ****************************************************************************/
Dsi3BufIf_TimerCaptureValue_t Dsi3BusImp_GetPDCMMeasuredPeriodDuration(void);   



/****************************************************************************//**
 * @brief
 * updates the current configuration of the CRM response offset.
 *
 * @param       genericBusEnvData             pointer to Bus environment data
 * @param       newCRMResponseTimeOffset      new crm response offset value
 * @return      TRUE                          if the CRM response time offset was tasked for change
 *              FALSE                         if the CRM response time offset was out of range
 * ****************************************************************************/
Dsi3BusIf_Bool_t Dsi3BusImp_UpdateCRMResponseTimeOffset(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_WordData_t newCRMResponseTimeOffset);


/****************************************************************************//**
 * @brief
 * updates the current configuration of the PDCM 1st slot offset (us).
 *
 * @param       genericBusEnvData       pointer to Bus environment data
 * @param       newPDCMStartSlotOffset  new PDCM 1st slot offset (us)
 * @return      TRUE                    if the PDCM slot duration was tasked for change
 *              FALSE                   if the PDCM slot duration was out of range
 * ****************************************************************************/
Dsi3BusIf_Bool_t Dsi3BusImp_UpdatePDCMStartSlotOffset(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_WordData_t newPDCMStartSlotOffset);



/****************************************************************************//**
 * @brief
 * updates the current configuration of the PDCM single slot duration.
 *
 * @param       genericBusEnvData       pointer to Bus environment data
 * @param       newPDCMSlotDuration     new single slot duration (us)
 * @return      TRUE                    if the PDCM slot duration was tasked for change
 *              FALSE                   if the PDCM slot duration time was out of range
 * ****************************************************************************/
Dsi3BusIf_Bool_t Dsi3BusImp_UpdatePDCMSlotDuration(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_WordData_t newPDCMSlotDuration);


/****************************************************************************//**
 * @brief
 * updates the current configuration of the PDCM period duration.
 *
 * @param       genericBusEnvData         pointer to Bus environment data
 * @param       newPDCMResponseDuration   new duration value for the PDCM period.
 * @return      TRUE                      if the PDCM period duration was tasked for change
 *              FALSE                     if the PDCM period duration was out of range
 * ****************************************************************************/
Dsi3BusIf_Bool_t Dsi3BusImp_UpdatePDCMResponseDuration(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_WordData_t newPDCMResponseDuration);


/**************************************************************************//**
 * @brief
 * updates the current configuration of the CRM blanking time offset.
 *
 * @param       genericBusEnvData               pointer to Bus environment data
 * @param       newCrmFCCBlankingTimeOffset     new crm blanking time offset value
 * @return      TRUE                            if the CRM FCC blanking time was tasked for change
 *              FALSE                           if the CRM FCC blanking time was out of range
 *
 * @image html Dsi3BusImp_UpdateCRMFCCBlankingTimeOffset.png "Activity chart: Update CRM Blanking Time Offset"
 * ****************************************************************************/
Dsi3BusIf_Bool_t Dsi3BusImp_UpdateCRMFCCBlankingTimeOffset(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_Tick_t newCRMFCCBlankingTimeOffset);


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
 * ****************************************************************************/
Dsi3BusIf_Bool_t Dsi3BusImp_UpdatePDCMFCCBlankingTimeOffset(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_Tick_t newPDCMFCCBlankingTimeOffset);


/****************************************************************************//**
 * @brief
 * updates the current bus configuration of the 1us clock.
 *
 * 
 *
 * @param       genericBusEnvData      pointer to Bus environment data
 * @param       newClkCfg              16 bit cfg data for the 1us clock.
 * @return      Dsi3BusIf_Bool_t       TRUE , update was successful,
 *                                     FALSE, else
 * ****************************************************************************/
Dsi3BusIf_Bool_t Dsi3BusImp_Set1usClockCfg(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_ClkDiv_t newClkCfg);

/****************************************************************************//**
 * @brief
 * Register single callback functions for CRM handling
 *
 * The function expects a pointer to a callback function for handling a given CRM
 * command. If the corresponding command index is within the allowed range of [0, 15]
 * the function return value signals success. An error is signaled otherwise. A
 * given function pointer will overwrite a function callback, which has already
 * been registered for a given command index. Instead of passing a valid function
 * pointer, the NULL pointer may be passed to unregister a possibly registered function.
 *
 * @param       genericEnvData      pointer to Bus environment data
 * @param       callbackFun         pointer to callback function which handles CRM command and
 *                                  prepares response data. NULL may be passed to unregister
 *                                  a callback function for a given CommandIndex.
 * @param       commandId           CRM command to be handled by callback function in the range [0, 15]
 * @param       genericBusCbCtxData pointer to generic callback context data
 * @return      TRUE                if the Callback function was successfully registered,
 *              FALSE               else
 * ****************************************************************************/
Dsi3BusIf_Bool_t Dsi3BusImp_RegisterCrmCallbackFunction(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_CRMCallbackFun_t callbackFun, Dsi3BusIf_CmdID_t commandId, Dsi3BusIf_pGenericCbCtxData_t genericBusCbCtxData);

/****************************************************************************//**
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
 * ****************************************************************************/
Dsi3BusIf_Bool_t Dsi3BusImp_RegisterPdcmCallbackFunction(Dsi3BusIf_pGenericEnvData_t genericEnvData,Dsi3BusIf_PDCMCallbackFun_t CallbackFun, Dsi3BusIf_pGenericCbCtxData_t genericBusCbCtxData);


/***************************************************************************//**
 * Transport Layer interface function.
 * @param   genericEnvData          pointer to bus layer environment data
 
 * @return  Dsi3BusIf_Bool_t        TRUE  - low signal occured since last check,
 *                                  FALSE - else
 *
 * Checks for communication idle state.
 ******************************************************************************/
Dsi3BusIf_Bool_t Dsi3BusImp_CheckBusActivityFun(Dsi3BusIf_pGenericEnvData_t genericEnvData);

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
 ******************************************************************************/
Dsi3BusIf_Bool_t Dsi3BusImp_AppendCallbackTableFun(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_cpCallbackFunctions_t callbackFunctions, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);


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
 ******************************************************************************/
Dsi3BusIf_Bool_t Dsi3BusImp_RemoveCallbackTableFun(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_cpCallbackFunctions_t callbackFunctions, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);
#endif /* DSI3_DRIVER_H_ */
/** @} dsi_Driver */









