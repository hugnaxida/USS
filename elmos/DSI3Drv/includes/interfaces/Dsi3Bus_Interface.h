/** @addtogroup dsi3_Driver_interfaces
 * @{ */
/***************************************************************************/
/** @file      Dsi3Bus_Interface.h
 *
 * @brief      DSI3 Bus layer interface definitions
 *
 * @purpose   Interface and callback definitions for the DSI3 Bus layer implementation.
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
 * @section history_sec_Interface_h Revision History
 * $Id: Dsi3Bus_Interface.h 417 2019-02-25 15:19:13Z poe $
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who Ver  Comment
 * -------------------------------------------------------------------
 * 18/08/21 (F) POE 1007 Added doxygen comments.
 * 18/02/26 (F) POE 1006 removed unused internal states;added DSI3_MAX_NUMBER_OF_CALLBACK_TABLES;inc API version
 * 18/02/23 (F) POE	1005 added IF CheckBusActivity; removed PDCMSync PdcmSyncReceived;inc API version
 * 18/02/14 (F) POE 1004 updated function header descriptions
 * 18/02/08 (F) POE 1003 added IF functions for en/disabling delayed PDCM/DISCErr 
 *                       handling
 * 18/01/17 (F) POE 1002 updated header and demo usage disclaimer
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
 * @version      $Revision: 417 $
 *
 *
 * $State: Exp $
 * $Author: poe $
 *
 * Additional markers:
 *
 */

#ifndef _DSI3BUS_INTERFACE_H_
#define _DSI3BUS_INTERFACE_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/

#include "el_types.h"
#include "Dsi3Bus_Types.h"


/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define DSI3BUS_INTERFACE_MODULE_API_VERSION      (0x0104u)                                 /**< DSI3 BUS interface version */
#define DSI3MOD_INTERFACE_MODULE_API_VERSION      (0x0100u)                                 /**< DSI3 HWMODULE interface version */
    
/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/***************************************************************************//**
 * @brief DSI3 BUS layer callback functions struct.
 *
 * The set of callbacks which should be invoked from the bus layer.
 ******************************************************************************/
struct         Dsi3BusIf_sCallbackFunctions;                                              /**< Forward declaration of DSI3 BUS layer callback functions. */
typedef struct Dsi3BusIf_sCallbackFunctions       Dsi3BusIf_sCallbackFunctions_t;         /**< Typedef for Dsi3BusIf_sCallbackFunctions. */
typedef        Dsi3BusIf_sCallbackFunctions_t*    Dsi3BusIf_pCallbackFunctions_t;         /**< Typedef of pointer to Dsi3BusIf_sCallbackFunctions. */
typedef const  Dsi3BusIf_sCallbackFunctions_t*    Dsi3BusIf_cpCallbackFunctions_t;        /**< Typedef of constant pointer to dsi3BusIf_sCallbackFunctions. */


/***************************************************************************//**
 * @brief DSI3 BUS layer interface functions struct.
 *
 * The set of interface functions which should be invoked in the higher layers.
 ******************************************************************************/
struct         Dsi3BusIf_sInterfaceFunctions;                                             /**< Forward declaration of DSI3 BUS layer interface functions. */
typedef struct Dsi3BusIf_sInterfaceFunctions      Dsi3BusIf_sInterfaceFunctions_t;        /**< Typedef for Dsi3BusIf_sInterfaceFunctions. */
typedef        Dsi3BusIf_sInterfaceFunctions_t*   Dsi3BusIf_pInterfaceFunctions_t;        /**< Typedef of pointer to Dsi3BusIf_sInterfaceFunctions. */
typedef const  Dsi3BusIf_sInterfaceFunctions_t*   Dsi3BusIf_cpInterfaceFunctions_t;       /**< Typedef of constant pointer to Dsi3BusIf_sInterfaceFunctions. */

/***************************************************************************//**
 * @brief DSI3 hardware module interface functions struct.
 *
 * The set of interface functions which should be invoked in the higher layers.
 ******************************************************************************/
struct         Dsi3HwModIf_sInterfaceFunctions;                                          /**< Forward declaration of DSI3 Module layer interface functions. */
typedef struct Dsi3HwModIf_sInterfaceFunctions    Dsi3HwModIf_InterfaceFunctions_t;      /**< Typedef for Dsi3ModuleIf_sInterfaceFunctions. */
typedef        Dsi3HwModIf_InterfaceFunctions_t*  Dsi3HwModIf_pInterfaceFunctions_t;     /**< Typedef of pointer to Dsi3ModuleIf_sInterfaceFunctions. */
typedef const  Dsi3HwModIf_InterfaceFunctions_t*  Dsi3HwModIf_cpInterfaceFunctions_t;    /**< Typedef of constant pointer to Dsi3ModuleIf_sInterfaceFunctions. */



/***************************************************************************//**
 * @brief  Object-like This-pointer to connect the BUS layer to higher layers
 *         or application.
 ******************************************************************************/
struct Dsi3BusIf_sThis
{
    Dsi3BusIf_cpInterfaceFunctions_t              IfFunsTbl;                              /**< Typedef of constant pointer to Dsi3BusIf_sInterfaceFunctions. */
    Dsi3BusIf_pGenericEnvData_t                   EnvData;                                /**< Generic pointer to environment data of the BUS layer module */
};

/***************************************************************************//**
 * @brief DSI3 BUS layer interface configuration parameter.
 *
 * Data needed for initialization of the BUS layer.
 ******************************************************************************/
struct Dsi3BusIf_sInitParam
{
    Dsi3BusIf_cpInterfaceFunctions_t IfFunsTbl;   /**< Typedef of constant pointer to Dsi3BusIf_sInterfaceFunctions. */
    Dsi3BusIf_pGenericEnvData_t      EnvData;     /**< Generic pointer to environment data of the BUS layer module */
    Dsi3BusIf_Length_t               EnvDataLen;  /**< Length of the available memory for BUS environment data */
    Dsi3BusIf_cpGenericImpCfgData_t  ImpCfgData;  /**< Generic pointer to configuration parameter of the specific BUS layer implementation */
};

struct         Dsi3BusIf_sInitParam;                                                      /**< Forward declaration of DSI3 BUS layer initialization parameter struct. */
typedef struct Dsi3BusIf_sInitParam               Dsi3BusIf_sInitParam_t;                 /**< Typedef forDsi3BusIf_sInitParam */
typedef        Dsi3BusIf_sInitParam_t*            Dsi3BusIf_pInitParam_t;                 /**< Typedef of pointer to Dsi3BusIf_sInitParam */

/* ****************************************************************************/
/* ********************************* FUNCTIONS ********************************/
/* ****************************************************************************/

/***************************************************************************//**
 * @brief
 * error callback routine from bus layer
 *
 * The callback routine for error handling from the bus layer.
 * 
 * @param       genericEnvData      generic environment data pointer, should point to bus environment data
 * @param       error               DSI3 bus error code
 * @param       genericCbCtxData    generic context data pointer (optional)
 * @return      none
 * ****************************************************************************/
typedef void (*Dsi3BusIf_ErrorCbFun_t)(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_cpInterfaceFunctions_t busIfFuns, Dsi3BusIf_Error_t error, Dsi3BusIf_pGenericCbCtxData_t genericTransCbCtxData);


/***************************************************************************//**
 * @brief
 * Dsi3 mode change callback routine from bus layer
 *
 * The callback routine for dsi3 mode change handling from the bus layer.
 * 
 * @param   genericEnvData      generic environment data pointer, should point to bus environment data
 * @param   currentMode         current DSI3 mode
 * @param   genericCbCtxData    generic context data pointer (optional)
 * @return  none
 * ****************************************************************************/
typedef void (*Dsi3BusIf_ModeChangedCbFun_t)(Dsi3BusIf_pGenericEnvData_t busEnvData,  Dsi3BusIf_cpInterfaceFunctions_t busIfFuns, Dsi3BusIf_eCommunicationMode_t currentMode, Dsi3BusIf_pGenericCbCtxData_t genericTransCbCtxData);


/***************************************************************************//**
 * @brief
 * Dsi3 CRM response processed callback routine from bus layer
 *
 * The callback routine if a CRM response has been processed successfully.
 * 
 * @param   genericEnvData      generic environment data pointer, should point to bus environment data
 * @param   genericCbCtxData    generic context data pointer (optional)
 * @return  none
 * ****************************************************************************/
typedef void (*Dsi3BusIf_CrmProcessedCbFun_t)      (Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_cpInterfaceFunctions_t busIfFuns, Dsi3BusIf_CmdID_t cmd, Dsi3BusIf_pGenericCbCtxData_t genericTransCbCtxData);


/***************************************************************************//**
 * @brief
 * Dsi3 PDCM response processed callback routine from bus layer
 *
 * The callback routine if a PDCM response has been processed successfully.
 * 
 * @param   genericEnvData      generic environment data pointer, should point to bus environment data
 * @param   genericCbCtxData    generic context data pointer (optional)
 * @return  none
 * ****************************************************************************/
typedef void (*Dsi3BusIf_PdcmProcessedCbFun_t)    (Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_cpInterfaceFunctions_t busIfFuns, Dsi3BusIf_pGenericCbCtxData_t genericTransCbCtxData);


/***************************************************************************//**
 * @brief
 * error callback routine from bus layer
 *
 * The callback routine for pdcm sync handling from the bus layer.
 * 
 * @param       genericEnvData      generic environment data pointer, should point to bus environment data
 * @param       error               DSI3 bus error code
 * @param       genericCbCtxData    generic context data pointer (optional)
 * @return      none
 * ****************************************************************************/
typedef void (*Dsi3BusIf_PdcmSyncReceivedCbFun_t)               (Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_cpInterfaceFunctions_t busIfFuns, Dsi3BusIf_Time_t periodLength, Dsi3BusIf_pGenericCbCtxData_t genericTransCbCtxData);


/***************************************************************************//**
 * @brief
 * Dsi3 discovery mode status update callback routine from bus layer
 *
 * The callback routine for dsi3 discovery mode status updates.
 * 
 * @param   genericEnvData              generic environment data pointer, should point to bus environment data
 * @param   pulseNum                    number of Discovery pulses since start of Discovery mode
 * @param   currentDiscoveryModeStatus  current Discovery mode status
 * @param   genericCbCtxData            generic context data pointer (optional)
 * @return  none
 * ****************************************************************************/   
typedef void (*Dsi3BusIf_DiscProcessedCbFun_t)           (Dsi3BusIf_pGenericEnvData_t busEnvData, Dsi3BusIf_cpInterfaceFunctions_t busIfFuns, Dsi3BusIf_CountValue_t pulseNum, Dsi3BusIf_DiscoveryModeStatus_t currentDiscoveryModeStatus, Dsi3BusIf_pGenericCbCtxData_t genericTransCbCtxData);


/***************************************************************************//**
 * @brief
 * Initializes DSI3 module and bus environment data.
 *
 * @param       genericBusEnvData     pointer to bus environment data
 * @param       busEnvDataSze         bus environment data size
 * @param       busCbFuns             pointer bus callback functions
 * @param       genericBusCbCtxData   pointer to optional bus context data
 * @param       genericImpCfgData     pointer init parameters for the bus layer from the appl layer
 * @return      TRUE                  if the initialization process was successful,
 *              FALSE                 else
 * ****************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusIf_InitializationFun_t)(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_EnvDataSze_t busEnvDataSze, Dsi3BusIf_cpGenericImpCfgData_t genericImpCfgData);


/***************************************************************************//**
 * @brief
 * Disables DSI3 communication and corresponding IRQ sources.
 *
 * @param       genericBusEnvData  pointer to bus environment data
 * @return      none
 * ****************************************************************************/
typedef void (*Dsi3BusIf_ShutdownFun_t)(Dsi3BusIf_pGenericEnvData_t genericEnvData);


/***************************************************************************//**
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
typedef void (*Dsi3BusIf_TaskFun_t)(Dsi3BusIf_pGenericEnvData_t genericEnvData);


/***************************************************************************//**
 * @brief Typedef of BUS layer 'Get Sub Interface' interface function.
 *
 * @param genericBusEnvData
 * @param interfaceId
 * @param ifThisPtr
 *
 * @return
 *
 ******************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusIf_GetSubInterfaceIfFun_t) (Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_InterfaceIds_t interfaceId, Dsi3BusIf_pThis_t ifThisPtr);


/***************************************************************************//**
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
typedef Dsi3BusIf_Bool_t (*Dsi3BusIf_UpdateDeviceAddressFun_t)(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_SlaveID_t deviceID);


/***************************************************************************//**
 * @brief
 * Set the new device chiptime.
 *
 * The device chiptime will be updated to the new value during the next bus task
 * execution.
 *
 * @param       genericEnvData  Pointer to bus environment data
 * @param       deviceID        new chiptime
 * @return      TRUE            if the device chiptime was tasked for change
 *              FALSE           if the chiptime was out of range
 * ****************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusIf_UpdateChipTimeFun_t)(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_ChipTime_t chiptime);


/***************************************************************************//**
 * @brief
 * sets the next communication mode to be assigned in the next bus task execution and
 * returns the next communication mode for validation.
 *
 * @param       genericEnvData                              Pointer to bus environment data
 * @param       Dsi3BusIf_eCommunicationMode_t              communication mode to be set
 * @return      Dsi3BusIf_eCOMM_COMMANDRESPONSEMODE         if the next mode is CRM
 *              Dsi3BusIf_eCOMM_PERIODICDATACOLLECTIONMODE  if the next mode is PDCM
 *              Dsi3BusIf_eCOMM_DISCOVERYMODE               if the next mode is DISC
 * ****************************************************************************/
typedef Dsi3BusIf_eCommunicationMode_t (*Dsi3BusIf_ChangeCommunicationModeFun_t)(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_eCommunicationMode_t dsi3Bus_eNextCommunicationMode);


/***************************************************************************//**
 * @brief
 * Returns the current DSI3 status timer counter value
 *
 * @param       genericEnvData  Pointer to bus environment data
 * @return      none
 * ****************************************************************************/
typedef Dsi3BusIf_Time_t (*Dsi3BusIf_TimestampFun_t)(void);


/***************************************************************************//**
 * @brief
 * updates the current bus configuration of the 1us clock.
 *
 * 
 *
 * @param       busEnvData              pointer to Bus environment data
 * @param       newClkCfg               16 bit cfg data for the 1us clock.
 * @return      none
 * ****************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusIf_Set1usClockFun_t)(Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_ClkDiv_t newClkCfg);


/***************************************************************************//**
 * @brief
 * returns the current hardware DSI3 configuration of the 1us clock.
 *
 * 
 *
 * @param       busEnvData              pointer to Bus environment data
 * @return      Dsi3BusIf_ClkDiv_t      register value
 * ****************************************************************************/
typedef Dsi3BusIf_ClkDiv_t (*Dsi3BusIf_Get1usClockFun_t)(void);   


/* --> 2018-03-05/JNAU: JIRA ESWDSI3-6, Additional interface function */
/* *************************************************************************//**
 * @brief
 * updates the current configuration of the CRM blanking time offset.
 *
 *
 *
 * @param       busEnvData                      pointer to Bus environment data
 * @param       newCRMFCCBlankingTimeOffset     new crm blanking time offset value
 * @return      none
 * ****************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusIf_UpdateCRMFCCBlankingTimeOffset_t) (Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_Tick_t newCRMFCCBlankingTimeOffset);
/* <-- 2018-03-05/JNAU: JIRA ESWDSI3-6 */   


/* --> 2018-03-05/JNAU: JIRA ESWDSI3-6, Additional interface function */
/* *************************************************************************//**
 * @brief
 * updates the current configuration of the PDCM blanking time duration.
 *
 *
 *
 * @param       genericBusEnvData              pointer to Bus environment data
 * @param       newPDCMFCCBlankingTimeOffset   new duration value for the PDCM blanking time.
 * @return      none
 * ****************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusIf_UpdatePDCMFCCBlankingTimeOffset_t) (Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_Tick_t newPDCMFCCBlankingTimeOffset);
/* <-- 2018-03-05/JNAU: JIRA ESWDSI3-6 */


/***************************************************************************//**
 * @brief
 * updates the current configuration of the CRM response offset.
 *
 * 
 *
 * @param       busEnvData                      pointer to Bus environment data
 * @param       newCRMResponseTimeOffset        new crm response offset value
 * @return      none
 * ****************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusIf_UpdateCRMResponseTimeOffset_t) (Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_WordData_t newCRMResponseTimeOffset);


/***************************************************************************//**
 * @brief
 * Updates the current configuration of the PDCM 1st slot offset (us).
 *
 * 
 *
 * @param       busEnvData              pointer to Bus environment data
 * @param       newPDCMStartSlotOffset  new PDCM 1st slot offset (us)
 * @return      none
 * ****************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusIf_UpdatePDCMStartSlotOffset_t)   (Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_WordData_t newPDCMStartSlotOffset);


/***************************************************************************//**
 * @brief
 * Updates the current configuration of the PDCM single slot duration.
 *
 * 
 *
 * @param       busEnvData              pointer to Bus environment data
 * @param       newPDCMSlotDuration     new single slot duration (us)
 * @return      none
 * ****************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusIf_UpdatePDCMSlotDuration_t)      (Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_WordData_t newPDCMSlotDuration);


/***************************************************************************//**
 * @brief
 * Updates the current configuration of the PDCM period duration.
 *
 * 
 *
 * @param       busEnvData              pointer to Bus environment data
 * @param       newPDCMResponseDuration new duration value for the PDCM period.
 * @return      none
 * ****************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusIf_UpdatePDCMResponseDuration_t)  (Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_WordData_t newPDCMResponseDuration);


/***************************************************************************//**
 * @brief
 * Returns the last measured pdcm period length.
 *
 * 
 *
 * @param       busEnvData              pointer to Bus environment data
 * @return      Dsi3BusIf_ClkDiv_t      16 bit register value
 * ****************************************************************************/
typedef Dsi3BufIf_TimerCaptureValue_t (*Dsi3BusIf_GetPDCMPeriodDurationFun_t) (void);


/***************************************************************************//**
 * @brief
 * Returns the last measured pdcm period length.
 *
 * 
 *
 * @param       busEnvData              pointer to Bus environment data
 * @return      Dsi3BusIf_ClkDiv_t      16 bit register value
 * ****************************************************************************/
typedef Dsi3BufIf_SyncCountValue_t (*Dsi3BusIf_GetCRMSyncCntFun_t) (void);


   
/* Type for callback functions */


/***************************************************************************//**
 * @brief
 * CRM: cmd id handler prototype.
 *
 * Prototype for a crm message handler.
 * 
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       genericRunData                  pointer to CRM runtime data struct (in/out buffer)
 * @param       const currentSlaveId            the currently assigned SlaveId
 * @param       genericCtxCbData                pointer to relevant context data
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      if writing to register was successful
 *              Dsi3BusIf_eCMDACT_IGNORE        if the cmd msg format was invalid or the processing conditions were not met
 * ****************************************************************************/ 
typedef Dsi3BusIf_CmdIdAction_t (*Dsi3BusIf_CRMCallbackFun_t)  (Dsi3BusIf_pGenericEnvData_t genericBusEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer, Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentSlaveId, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);


/***************************************************************************//**
 * @brief
 * PDCM: response buffer prepare handler prototype.
 *
 * Prototype for a PDCM response preparation handler.
 * 
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       genericRunData                  pointer to CRM runtime data struct (in/out buffer)
 * @param       const currentSlaveId            the currently assigned SlaveId
 * @param       genericCtxCbData                pointer to relevant context data
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      if writing to register was successful
 *              Dsi3BusIf_eCMDACT_IGNORE        if the cmd msg format was invalid or the processing conditions were not met
 * ****************************************************************************/ 
typedef Dsi3BusIf_CmdIdAction_t (*Dsi3BusIf_PDCMCallbackFun_t) (Dsi3BusIf_pGenericEnvData_t genericBusEnvData, Dsi3BusIf_ByteData_t* responseBuffer, const Dsi3BusIf_Length_t bufsize, uint8_t *msgLen, const Dsi3BusIf_SlaveID_t currentSlaveId, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/***************************************************************************//**
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
 * @param       CallbackFcn      Pointer to callback function which handles CRM command and
 *                               prepares response data. NULL may be passed to unregister
 *                               a callback function for a given CommandIndex.
 * @param       CommandIndex     CRM command to be handled by callback function in the range [0, 15]
 * @return      TRUE             if the Callback function was successfully registered,
 *              FALSE            else
 * ****************************************************************************/
/***************************************************************************//**
 * Register single callback functions for CRM handling
 *
 * @param[in]      Dsi3Bus_CrmCallbackFcn_t CallbackFcn
 *                 Pointer to callback function which handles CRM command and
 *                 prepares response data. NULL may be passed to unregister
 *                 a callback function for a given CommandIndex.
 *
 *                 uint32_t CommandIndex
 *                 CRM command to be handled by callback function in the range [0, 15]
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
 * @see            (optional) Crossreference
 *
 ******************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusImp_RegisterCRMCbFun_t) (Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_CRMCallbackFun_t callbackFun, Dsi3BusIf_CmdID_t commandId, Dsi3BusIf_pGenericCbCtxData_t genericBusCbCtxData);


/***************************************************************************//**
 * @brief
 * Register callback function for PDCM handling.
 *
 * @param[in]      Dsi3Bus_PdcmCallbackFcn_t CallbackFcn
 *                 Pointer to callback function which handles PDCM sync pulse
 *                 and prepares response data. NULL may be passed to unregister
 *                 the callback function.
 *
 *
 * @return         Error status
 *                 TRUE:    Callback function successfully registered
 *                 FALSE:   Not used
 *
 * Precondition:   none
 *
 * Postcondition:  none
 *
 * The function expects a pointer to a callback function for handling a SYNC
 * pulse in PDCM. A given function pointer will overwrite a function callback,
 * which has already been registered. Instead of passing a valid function
 * pointer, the NULL pointer may be passed to unregister a possibly registered
 * function.
 *
 *
 * @see            (optional) Crossreference
 *
 ******************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusImp_RegisterPDCMCbFun_t)(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_PDCMCallbackFun_t CallbackFun, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);


/* --> 18-02-08/POE: version r4199, ESWDSI3-1 
 * Added toggle IF function for delayed PDCM/DISC err evt processing. 
 */
/***************************************************************************//**
 * @brief
 * The next occuring PDCM error evt will be withheld until a CRM based
 * error occurs or discarded if valid CRM msg was received.
 *
 * @param       genericEnvData      Pointer to bus environment data
 * @return      none
 * ****************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusIf_DelayNextPDCMErrHandlingFun_t)(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_Bool_t delayOn);


/***************************************************************************//**
 * @brief
 * The next occuring DISC error evt will be withheld until a CRM based
 * error occurs or discarded if valid CRM msg was received.
 *
 * @param       genericEnvData      Pointer to bus environment data
 * @return      none
 * ****************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusIf_DelayNextDISCErrHandlingFun_t)(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_Bool_t delayOn);

/* --> 18-02-23/POE: version r4340, Improvement
 * Added IF function to check for bus activity.
 */
/***************************************************************************//**
 *@brief 
 * Checks for communication bus activity.
 *
 * @param   genericEnvData          pointer to bus environment data
 * @param   active   								target discovery mode availability
 *
 * @return  Dsi3BusIf_Bool_t        TRUE  - Setting of DiscoveryEnableStatus was successful
 *                                  FALSE - else
 *
 * @see        (optional) Crossreference
 ******************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusIf_CheckBusActivityFun_t)(Dsi3BusIf_pGenericEnvData_t genericEnvData);
/* --> 18-02-23/POE: version r4340, Improvement */

/* --> 18-02-08/POE: version r4199, ESWDSI3-1 */


/* --> 18-02-26/POE: version r4357, Improvement
 * Added IF function Append & Remove callback table.
 */  
/***************************************************************************//**
 *@brief 
 * Appends a callback table to the callback table pool if there is a
 * free slot available.
 *
 * @param   genericEnvData          pointer to bus environment data
 * @param   callbacks   						const pointer to target callback table
 *
 * @return  Dsi3BusIf_Bool_t        TRUE  - The callback table was added successfully
 *                                  FALSE - else
 *
 * @see        (optional) Crossreference
 ******************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusIf_AppendCallbackTableFun_t)(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_cpCallbackFunctions_t callbackFunctions, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);
/***************************************************************************//**
 *@brief 
 * Removes a callback table from the callback table pool if it is stored there.
 *
 * @param   genericEnvData          pointer to bus environment data
 * @param   callbacks   						const pointer to target callback table
 *
 * @return  Dsi3BusIf_Bool_t        TRUE  - The callback table was removed successfully
 *                                  FALSE - else
 *
 * @see        (optional) Crossreference
 ******************************************************************************/
typedef Dsi3BusIf_Bool_t (*Dsi3BusIf_RemoveCallbackTableFun_t)(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_cpCallbackFunctions_t callbackFunctions, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);
/* --> 18-02-26/POE: version r4357, Improvement */
/*****************************************************************************/
/********************************** INTERFACE ********************************/
/*****************************************************************************/
/***************************************************************************//**
 * @brief DSI3 BUS layer callback functions struct.
 *
 * The set of callbacks which should be invoked from the bus layer.
 ******************************************************************************/
struct Dsi3BusIf_sCallbackFunctions
{
  Dsi3BusIf_Version_t                   CallbackVersion;       /**< @brief Callback Version */
  Dsi3BusIf_ErrorCbFun_t                Error;                 /**< @brief Pointer to DSI3 BUS Layer 'Error' function as member of DSI3 BUS Layer callback function struct. @see Dsi3BusIf_ErrorCbFun_t */
  Dsi3BusIf_ModeChangedCbFun_t          ModeChanged;           /**< @brief Pointer to DSI3 BUS Layer 'ModeChanged' function as member of DSI3 BUS Layer callback function struct. @see Dsi3BusIf_ModeChangedCbFun_t */
  Dsi3BusIf_DiscProcessedCbFun_t        DiscProcessed;         /**< @brief Pointer to DSI3 BUS Layer 'DiscProcessed' function as member of DSI3 BUS Layer callback function struct. @see Dsi3BusIf_DiscProcessedCbFun_t */
  Dsi3BusIf_CrmProcessedCbFun_t         CrmProcessed;          /**< @brief Pointer to DSI3 BUS Layer 'CrmProcessed' function as member of DSI3 BUS Layer callback function struct. @see Dsi3BusIf_CrmProcessedCbFun_t */
  Dsi3BusIf_PdcmProcessedCbFun_t        PdcmProcessed;         /**< @brief Pointer to DSI3 BUS Layer 'PdcmProcessed' function as member of DSI3 BUS Layer callback function struct. @see Dsi3BusIf_PdcmProcessedCbFun_t */
 /* --> 18-02-23/POE: version r4340, Improvement
  * Removed because not supported anymore.
  */  
//  Dsi3BusIf_PdcmSyncReceivedCbFun_t     PdcmSyncReceived;      /**< @brief Pointer to DSI3 Bus Layer 'PdcmSyncReceived' function as member of DSI3 BUS Layer callback function struct. @see Dsi3BusIf_PdcmSyncReceivedCbFun_t */
  /* --> 18-02-23/POE: version r4340, Improvement */
};



/***************************************************************************//**
 * @brief DSI3 BUS layer interface functions struct.
 *
 * The set of interface functions which should be invoked in the higher layers.
 ******************************************************************************/
struct Dsi3BusIf_sInterfaceFunctions                        
{
  Dsi3BusIf_Version_t                           InterfaceVersion;             /**< @brief Interface version */
  Dsi3BusIf_InitializationFun_t                 Initialization;               /**< @copydoc Dsi3BusIf_InitializationFun_t */
  Dsi3BusIf_ShutdownFun_t                       Shutdown;                     /**< @copydoc Dsi3BusIf_ShutdownFun_t */
  Dsi3BusIf_GetSubInterfaceIfFun_t              GetSubInterface;              /**< @copydoc Dsi3BusIf_GetSubInterfaceIfFun_t */
  Dsi3BusIf_TimestampFun_t                      GetTimestamp;                 /**< @copydoc Dsi3BusIf_TimestampFun_t */
  Dsi3BusIf_UpdateDeviceAddressFun_t            UpdateDeviceAddress;          /**< @copydoc Dsi3BusIf_UpdateDeviceAddressFun_t */
  Dsi3BusIf_ChangeCommunicationModeFun_t        ChangeMode;                   /**< @copydoc Dsi3BusIf_ChangeCommunicationModeFun_t */
  Dsi3BusIf_UpdateChipTimeFun_t                 UpdateChipTime;               /**< @copydoc Dsi3BusIf_UpdateChipTimeFun_t */
  Dsi3BusIf_UpdateCRMResponseTimeOffset_t       UpdateCRMResponseTimeOffset;  /**< @copydoc Dsi3BusIf_UpdateCRMResponseTimeOffset_t */
  Dsi3BusIf_UpdatePDCMStartSlotOffset_t         UpdatePDCMStartSlotOffset;    /**< @copydoc Dsi3BusIf_UpdatePDCMStartSlotOffset_t */
  Dsi3BusIf_UpdatePDCMSlotDuration_t            UpdatePDCMSlotDuration;       /**< @copydoc Dsi3BusIf_UpdatePDCMSlotDuration_t */
  Dsi3BusIf_UpdatePDCMResponseDuration_t        UpdatePDCMResponseDuration;   /**< @copydoc Dsi3BusIf_UpdatePDCMResponseDuration_t */
  Dsi3BusImp_RegisterCRMCbFun_t                 RegisterCrmCb;                /**< @copydoc Dsi3BusImp_RegisterCRMCbFun_t */
  Dsi3BusImp_RegisterPDCMCbFun_t                RegisterPdcmCb;               /**< @copydoc Dsi3BusImp_RegisterPDCMCbFun_t */
  Dsi3BusIf_TaskFun_t                           Task;                         /**< @copydoc Dsi3BusIf_TaskFun_t*/
  Dsi3BusIf_CheckBusActivityFun_t               CheckBusActivity;             /**< @copydoc Dsi3BusIf_CheckBusActivityFun_t */
  Dsi3BusIf_AppendCallbackTableFun_t            AppendCallbackTable;          /**< @copydoc Dsi3BusIf_AppendCallbackTableFun_t */
  Dsi3BusIf_RemoveCallbackTableFun_t            RemoveCallbackTable;          /**< @copydoc Dsi3BusIf_RemoveCallbackTableFun_t */
};



/* --> 18-04-17/POE: Improvement
 * Moved module specific configurations to sub interface.
 */
/***************************************************************************//**
 * @brief DSI3 hardware module interface functions struct.
 *
 * The set of interface functions which should be invoked in the higher layers.
 ******************************************************************************/
struct Dsi3HwModIf_sInterfaceFunctions                                            
{
  Dsi3BusIf_Version_t                           InterfaceVersion;                 /**< @brief Interface version */
  Dsi3BusIf_Get1usClockFun_t                    Get1usClockCfg;                   /**< @copydoc Dsi3BusIf_Get1usClockFun_t */
  Dsi3BusIf_Set1usClockFun_t                    Set1usClockCfg;                   /**< @copydoc Dsi3BusIf_Set1usClockFun_t */
  Dsi3BusIf_UpdateCRMFCCBlankingTimeOffset_t    UpdateCRMFCCBlankingTimeOffset;   /**< @copydoc Dsi3BusIf_UpdateCRMFCCBlankingTimeOffset_t */
  Dsi3BusIf_UpdatePDCMFCCBlankingTimeOffset_t   UpdatePDCMFCCBlankingTimeOffset;  /**< @copydoc Dsi3BusIf_UpdatePDCMFCCBlankingTimeOffset_t */
  Dsi3BusIf_GetCRMSyncCntFun_t                  GetCRMSyncCount;                  /**< @copydoc Dsi3BusIf_GetCRMSyncCntFun_t */
  Dsi3BusIf_GetPDCMPeriodDurationFun_t          GetPDCMMeasuredPeriodDuration;    /**< @copydoc Dsi3BusIf_GetPDCMPeriodDurationFun_t */
};
/* --> 18-04-17/POE: Improvement */

/*****************************************************************************/
/**************************** DEFINES AND MACROS *****************************/
/*****************************************************************************/

/*****************************************************************************/



/*****************************************************************************/


/*****************************************************************************/

/*****************************************************************************/

/*****************************************************************************/


/* *************************************************************************** */
/* **************************** GLOBALE VARIABLES **************************** */
/* *************************************************************************** */
#endif /* _Dsi3BusIFACE_H_ */

/** @} dsi3_Driver_interfaces */
