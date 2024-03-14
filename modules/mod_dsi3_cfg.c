/***************************************************************************//**
 * @file      mod_dsi3_cfg.c
 *
 * @author    StSl
 * @date      24.04.2017
 *
 * @brief     DSI3 configuration module initializes and configures the DSI3 bus layer
 *
 * TODO: A detailed description of this module
 *
 *******************************************************************************
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
 *******************************************************************************
 *
 * $Id: mod_dsi3_cfg.c 432 2019-03-26 11:50:03Z siko $
 *
 * $Revision: 432 $
 *
 ******************************************************************************/

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_dsi3_cfg.h"
#include "mod_dsi3.h"
#include "dsi3_InterruptHandler.h"
#include "def_dsi3.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define DRI3DRVIMP_BUS_USED_IF_VERSION      (DSI3BUS_INTERFACE_MODULE_API_VERSION)      /**< DSI3 callbacks version number */
#define DSI3_BUS_ERROR_CALLBACK                  &Dsi3_BusErrorCbFun                    /**< DRI3 bus error callback function */
#define DSI3_BUS_MODECHANGED_CALLBACK            &Dsi3_BusModeChangedCbFun              /**< DSI3 mode has changed callback function */
#define DSI3_BUS_AUTOADDRESSING_CALLBACK         &Dsi3_BusAutoAddrCbFun                 /**< DSI3 auto addressing function */
#define DSI3_BUS_CALLBACK_CTX_DATA               DSI3_NULL                              /**< DSI3 pointer to optional bus context data  */
#define DSI3DRV_PDCM_COMMAND_ID                  (0u)                                   /**< DSI3 id for pdcm response frames */

/* ****************************************************************************/
/* ************************** FORWARD DECLARATIONS ****************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/
Dsi3BusIf_cpInterfaceFunctions_t Dsi3_BusIfFuns = &Dsi3BusImp_InterfaceFunctions;    /* Pointer to DSI3 interface functions */
Dsi3HwModIf_cpInterfaceFunctions_t      Dsi3DrvImp_HWModIfFuns;                      /* points to a struct of the dsi3 hw interface functions */


#if defined ( EL_COMPILER_KEIL )
  uint8_t Dsi3_BusEnvData[DSI3BUSIMP_ENVIRONMENT_DATA_SZE] __attribute__((aligned)); /* Bus environment data container */
#elif defined ( EL_COMPILER_IAR )
  #pragma data_alignment=4
  uint8_t Dsi3_BusEnvData[DSI3BUSIMP_ENVIRONMENT_DATA_SZE];                          /* Bus environment data container3 */
#else
  #error "Unsupported compiler type"

#endif

Dsi3Drv_sDSI3Ctrl_t       DSI3Ctrl;     /* DSI3 control structure */
/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/
static const Dsi3BusIf_sCallbackFunctions_t Dsi3_BusCallbacks = {
    .CallbackVersion            = DRI3DRVIMP_BUS_USED_IF_VERSION,                       /**< DSI3 callbacks version number */
    .Error                      = DSI3_BUS_ERROR_CALLBACK,                              /**< DRI3 bus error callback function */
    .ModeChanged                = DSI3_BUS_MODECHANGED_CALLBACK,                        /**< DSI3 mode has changed callback function */
    .DiscProcessed              = DSI3_BUS_AUTOADDRESSING_CALLBACK,                     /**< DSI3 auto addressing function */
    .CrmProcessed               = NULL,                                                 /**< undefined by bus layer */
    .PdcmProcessed              = NULL,                                                 /**< undefined by bus layer */
}; /* Callback Table to be registerd in Bus-Layer */

/* TODO: description of following arrays */
static const uint16_t TBIT_CRM_RESPOFFSET[4]    = {305u, 590u, 1180u, 305u};
static const uint16_t TBIT_DISC_PERIODLEN[4]    = {125u, 189u,  317u, 125u};
static const uint16_t TBIT_DISC_RAMPONDELAY[4]  = { 64u, 128u,  256u,  64u}; 
static const uint16_t TCHP_PDCM_SLOTDUR[4]      = {145u, 192u,  241u, 289u};
/* ****************************************************************************/
/* ******************** FORWARD DECLARATIONS / PROTOTYPES *********************/
/* ****************************************************************************/


/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/



/* **************************************************************************//**
 * @brief: DSI3 driver initialization.
 *
 * @param       nvicIfFuns      pointer to NVIC interface functions
 * @param       pAppData        pointer to Application control and runtime data
 *
 * @return      TRUE  - DSI3 driver initialization completed successfully
 *              FALSE - else
 * *****************************************************************************/
bool_t Dsi3_Init(nvic_cpInterfaceFunctions_t nvicIfFuns, Dsi3Drv_sApplCtrlData_t* pAppData)
{
  bool_t retVal = TRUE;
/* Retrieve IF pointer from DSI3 IF */
  Dsi3BusIf_sThis_t loc_This;
  retVal = Dsi3_BusIfFuns->GetSubInterface(Dsi3_BusEnvData, Dsi3_IfId_HWMODULE, &loc_This);
  if (TRUE == retVal)
  {
    Dsi3DrvImp_HWModIfFuns = (Dsi3BusIf_cpGenericInterfaceFunctions_t)loc_This.IfFunsTbl;
  }

  /* get NAD to use as initial NAD */
  uint8_t initialNad;
  if((pAppData->MeasCtrl->Parameters.data.SlaveId.fields.SlaveId > 0) &&
      pAppData->MeasCtrl->Parameters.data.SlaveId.fields.SlaveId <= DSI3_CFG_MAXIMAL_NAD)
  {
    /* valid NAD in RAM available. Use as initial NAD */
    initialNad = pAppData->MeasCtrl->Parameters.data.SlaveId.fields.SlaveId;
  }
  else
  {
    /* invalid NAD in RAM. Use default NAD */
    initialNad = DSI3_CFG_INITIAL_NAD;
  }
  
  /* precalc max deviation of configured PdmcPeriod ca. 3% */
  pAppData->MeasCtrl->RuntimeData.preCalcMaxPdcmDeviation = pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmPeriod >> 5;
    
  /* calculate PDCM start time offset */
  uint16_t myStart = 0;
  switch(initialNad)
  {
  case 1:
    myStart = pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor1;
    break;
  case 2:
    myStart = pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor2;
    break;
  case 3:
    myStart = pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor3;
    break;
  case 4:
    myStart = pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor4;
    break;
  case 5:
    myStart = pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor5;
    break;
  case 6:
    myStart = pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor6;
    break;
  default:
    myStart = pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmRespSensor7;
    break;
  }
  myStart = myStart - ((initialNad - 1) * DSI3_CFG_PDCM_SLOT_TIME);
  
  uint8_t loc_fccTBitSelect     = pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.FCC_t_bit;
  uint8_t loc_chipTSelect       = pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.ChipTime;

  /* fill dsi3 bus config data struct */
  const Dsi3BusImp_CfgData_t dsi3BusImpCfgData =
  {
    .Version                    = DSI3_IMPL_CFG_DATA_VERSION,
    .SlaveID                    = initialNad,
    .MaximalSlaveID             = DSI3_CFG_MAXIMAL_NAD,
    .NvicInterfaceFunctions     = nvicIfFuns,
    .HardwareAddsCRC            = DSI3_CFG_HW_CRC,
    .EnableAutoSync             = DSI3_CFG_HW_AUTOSYNC,
    .RCC_ChipTime               = (Dsi3BusIf_ChipTime_t)loc_chipTSelect,
    .RCC_SlopeSel               = (Dsi3BusIf_RCC_Slope_t)pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.RCCSlopeSel,
    .RCC_CurveSel               = (Dsi3BusIf_RCC_Curve_t)pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.RCCCurveSel,
    .RCC_CurrentOffset          = (Dsi3BusIf_RCC_CurrentOffset_t)pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.RCCCurrentOffset,
    .Dsi3DebounceValue          = (dsi3_DebounceValue_t)pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.Dsi3Debounce,
    .FCC_BitTime                = (Dsi3BusIf_FCC_TBit_t)loc_fccTBitSelect,
    
    .CRMResponseTimeOffset      = TBIT_CRM_RESPOFFSET[loc_fccTBitSelect],
    .CRMFCCBlankingTimeOffset   = pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.CrmFccBlankTime,
    .CRMEnableSlaveIdPrefilter  = DSI3_CFG_SW_SLAVEID_PREFILTER,
    
    .PDCMOutBufferSize          = DSI3_CFG_PDCM_BUFOUT_SIZE,
    .PDCMStartSlotOffset        = myStart,
    .PDCMFCCBlankingTimeOffset  = pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmFccBlankTime,
    .PDCMResponseDuration       = pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.PdcmPeriod,
    .PDCMSlotDuration           = TCHP_PDCM_SLOTDUR[loc_chipTSelect],
    .PDCMDelayErrEvtHandling    = TRUE,

    .DISCRampOnDelay            = TBIT_DISC_RAMPONDELAY[loc_fccTBitSelect],
    .DISCRampOnDuration         = 28u,
    .DISCPeriodLength           = TBIT_DISC_PERIODLEN[loc_fccTBitSelect], 
    .DISCDelayErrEvtHandling    = TRUE, 
     
    .DefaultCommunicationMode   = DSI3BUSIMP_DEFAULT_COMMUNICATIONMODE_DEFAULT
  };

  retVal = Dsi3_BusIfFuns->Initialization((Dsi3BusIf_pGenericEnvData_t) Dsi3_BusEnvData, sizeof(Dsi3_BusEnvData), &dsi3BusImpCfgData);
  
  if (retVal)
  {
    retVal = Dsi3_BusIfFuns->AppendCallbackTable((Dsi3BusIf_pGenericEnvData_t) Dsi3_BusEnvData, &Dsi3_BusCallbacks,DSI3_BUS_CALLBACK_CTX_DATA);
  }
  
  if (retVal)
  {
    /* Register DSI3 callback functions for register and memory manipulation */
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_Default                , dsi3Drv_eCRM_COMMAND_ID_NOP1                          , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_MeasExecute            , dsi3Drv_eCRM_COMMAND_ID_MEASUREMENT_EXECUTE           , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_AdvMeasurementExecute  , dsi3Drv_eCRM_COMMAND_ID_MEASUREMENT_ADVANCED_EXECUTE  , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_Default                , dsi3Drv_eCRM_COMMAND_ID_NOP2                          , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_MeasStop               , dsi3Drv_eCRM_COMMAND_ID_MEASUREMENT_STOP              , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_Default                , dsi3Drv_eCRM_COMMAND_ID_NOP3                          , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_Default                , dsi3Drv_eCRM_COMMAND_ID_NOP4                          , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
#if !defined(FPGA_52417B)
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_Default                , dsi3Drv_eCRM_COMMAND_ID_NOP5                          , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
#else
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_IdAssign               , dsi3Drv_eCRM_COMMAND_ID_NOP5                          , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
#endif
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_MeasSettings           , dsi3Drv_eCRM_COMMAND_ID_MEASUREMENT_SETTINGS          , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_MeasSettingsExt        , dsi3Drv_eCRM_COMMAND_ID_MEASUREMENT_SETTINGS_EXTENDED , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_EEPROMAccess           , dsi3Drv_eCRM_COMMAND_ID_EEPROM_ACCESS                 , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_RegisterAccess         , dsi3Drv_eCRM_COMMAND_ID_REGISTER_ACCESS               , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_RegisterAccessExt      , dsi3Drv_eCRM_COMMAND_ID_REGISTER_ACCESS_EXTENDED      , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_ReadStatInCRM        , dsi3Drv_eCRM_COMMAND_ID_READ_STATUS_IN_CRM            , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_ReadStatInPDCM       , dsi3Drv_eCRM_COMMAND_ID_READ_STATUS_IN_PDCM           , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
    (void)Dsi3_BusIfFuns->RegisterCrmCb(Dsi3_BusEnvData, &Dsi3_CrmCmdHandler_IcMode                 , dsi3Drv_eCRM_COMMAND_ID_IC_MODE                       , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);

    (void)Dsi3_BusIfFuns->RegisterPdcmCb(Dsi3_BusEnvData,&Dsi3_PdcmCmdHandler                      , (Dsi3BusIf_pGenericCbCtxData_t)DSI3_BUS_CALLBACK_CTX_DATA);
  }


  /* enable hardware ato sync if configured (SM103)*/
  if(DSI3_SYNC_ON_HARDWARE == (dsi3_cfg_status_sync_t)pAppData->MeasCtrl->Parameters.data.DsiSettings.fields.SyncDsi3)
  {
    DSI3_CTRL_CONFIG_AUTOSNYC_ENABLE();
  }
  else
  {
    DSI3_CTRL_CONFIG_AUTOSNYC_DISABLE();
  }

  return(retVal);
}

/* **************************************************************************//**
 * @brief DSI3 return controll struct
 * @param       none
 * @return      Pointer to DSI3 control data
 * *****************************************************************************/
Dsi3Drv_sDSI3Ctrl_t* Dsi3_GetDSI3Ctrl(void)
{
  return &DSI3Ctrl;
}

