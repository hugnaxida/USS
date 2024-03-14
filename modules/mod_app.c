/***************************************************************************//**
 * @file      mod_app.c
 *
 * @creator   StSl
 * @created   22.11.2017
 * @sdfv      Demo Flow
 *
 * @brief     Application control module
 *
 * @purpose
 * The APP mdule handles all measurement and diagnostic applications
 *
 *  ******************************************************************************
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
 * $Id: mod_app.c 396 2019-01-24 15:15:06Z siko $
 *
 * $Revision: 396 $
 *
 ******************************************************************************/

/* **************************************************************************//***/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_app.h"
#include "mod_err.h"
#include "mod_util.h"
#include "mod_ada.h"
#include "mod_dsp.h"
#include "string.h"
#include "mod_eeprom.h"

/* ****************************************************************************/
/* ***************************** USER INCLUDES ********************************/
/* ****************************************************************************/
static Dsi3Drv_pApplCtrlData_t loc_pApplRuntimeData; /* pointer to application runtime data environment */

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define NOISEMEAS_NOISECNT_MAX                    (255u)      /**< max value of noise counter */
#define NOISEMEAS_NOISESUM_MAX                    (4095u)     /**< max value of noise sum */
#define NOISE_MEASUREMENT_MAX_SAMPLES             (255u)      /**< maximum number of noise samples to be taken in a measurement cycle */
#define NFD1_MAX_TIME_TO_THIRD_ECHO   (6000u / ECHO_MEASUREMENT_MONITORING_PERIOD) /**< NFD algorithm 1 max time to wait for the third echo times 32us */
#define NFD1_MAX_TIME_BETWENN_TWO_ECHOS           (2000u)     /**< NFD algorithm 1 max time between two echo events */
#define RFM_STATUS_FINISHED                       (1u)        /**< RFM status indicates the completion of the RFM measurement */
#define RTM_STATUS_FINISHED                       (1u)        /**< RTM status indicates the completion of the RTM measurement */

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/** 
 * Enums advanced paths
 */
typedef enum
{
  ADVANCED_PATH_NUMBER_NO_DATA      = (0u),             /**< There is no data in any advanced path buffer */
  ADVANCED_PATH_NUMBER_PATH1        = (1u),             /**< There is data in advanced path 1 buffer */
  ADVANCED_PATH_NUMBER_PATH2        = (2u),             /**< There is data in advanced path 2 buffer */
} loc_eAdvPathNum_t;

/* ****************************************************************************/
/* ***************************** GLOBAL VARIABLES *****************************/
/* ****************************************************************************/

int32_t tsense_calib_eff = 0;                          /* calibration value for temperature measurement */

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ******************** FORWARD DECLARATIONS / PROTOTYPES *********************/
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * Set pdcm frame for default data
 *
 * initiates all data in the answer buffer to zero
 *
 * @param       ansData                         pointer to PDCM response buffer for next PDCM pulse
 * @return      n.a.
 * ****************************************************************************/
void loc_SetPdcmAnswerFrameDefault(Dsi3Drv_uPDCMResponseFrame_t* ansData);

/* **************************************************************************//**
 * @brief
 * Set pdcm frame for diagnostic data
 *
 * Copy data from diagnostic measurement into pdcm answer buffer
 *
 * @param       ansData                         pointer to PDCM response buffer for next PDCM pulse
 * @return      n.a.
 * ****************************************************************************/
void loc_SetPdcmAnswerFrameDiagnostic(Dsi3Drv_uPDCMResponseFrame_t* ansData);

/* **************************************************************************//**
 * @brief
 * Set pdcm frame for burst data
 *
 * Copy data from burst monitoring into pdcm answer buffer
 *
 * @param       ansData                         pointer to PDCM response buffer for next PDCM pulse
 * @return      n.a.
 * ****************************************************************************/
void loc_SetPdcmAnswerFrameBurst(Dsi3Drv_uPDCMResponseFrame_t* ansData);

/* **************************************************************************//**
 * @brief
 * Set pdcm frame for ringing data
 *
 * Copy data from ringing measurement into pdcm answer buffer
 *
 * @param       ansData                         pointer to PDCM response buffer for next PDCM pulse
 * @return      n.a.
 * ****************************************************************************/
void loc_SetPdcmAnswerFrameRinging(Dsi3Drv_uPDCMResponseFrame_t* ansData);

/* **************************************************************************//**
 * @brief
 * Set pdcm frame for nfd data
 *
 * Copy data from near field detection into pdcm answer buffer
 *
 * @param       ansData                         pointer to PDCM response buffer for next PDCM pulse
 * @return      n.a.
 * ****************************************************************************/
void loc_SetPdcmAnswerFrameNfd(Dsi3Drv_uPDCMResponseFrame_t* ansData);

/* **************************************************************************//**
 * @brief
 * Set pdcm frame for standard measurement data format 0
 *
 * Copy data from standard measurement with format 0 into pdcm answer buffer
 *
 * @param       ansData                         pointer to PDCM response buffer for next PDCM pulse
 * @param       loc_BufStd0                     pointer to buffer
 * @return      n.a.
 * ****************************************************************************/
void loc_SetPdcmAnswerFrameStd0(Dsi3Drv_uPDCMResponseFrame_t* ansData, Meas_sEevalStdDataPacketFormat0* loc_BufStd0);

/* **************************************************************************//**
 * @brief
 * Set pdcm frame for standard measurement data format 1
 *
 * Copy data from standard measurement with format 1 into pdcm answer buffer
 *
 * @param       ansData                         pointer to PDCM response buffer for next PDCM pulse
 * @param       loc_BufStd1                     pointer to buffer
 * @return      n.a.
 * ****************************************************************************/
void loc_SetPdcmAnswerFrameStd1(Dsi3Drv_uPDCMResponseFrame_t* ansData, Meas_sEevalStdDataPacketFormat1*  loc_BufStd1);

/* **************************************************************************//**
 * @brief
 * Set advanced pdcm frame
 *
 * Copys the given data from the advanced path buffer to the pdcm answer buffer
 *
 * @param       ansData                         pointer to PDCM response buffer for next PDCM pulse
 * @param       frameSelect                     Frame select of given data
 * @param       buffer                          pointer to advanced meas result buffer
 * @param       tail                            Pointer to Tail counter of given buffer
 * @return      n.a.
 * ****************************************************************************/
void loc_SetPdcmAnswerFrameAdv(Dsi3Drv_uPDCMResponseFrame_t* ansData, uint8_t frameSelect, Meas_sEevalAdvDataPacketFormat* buffer, uint16_t* tail);

/* **************************************************************************//**
 * @brief
 * Get remaining result count
 *
 * Returns the number of remaining results in the given buffer.
 * In case of results from an advanced measurement, results with low confidence level will be skipped
 *
 * @param       buffer                          Pointer to measurement result buffer
 * @param       head                            Head counter of given buffer
 * @param       tail                            Pointer to Tail counter of given buffer
 * @param       minConf                         Minimum confidence level for adavnced meas results
 * @param       kind                            Standard ord Advanced Measurement results
 * @return      uint16_t      Number of remaining results in given buffer
 * ****************************************************************************/
uint16_t loc_GetRemainingResultCount(Meas_uEevalDataPacket* buffer, uint16_t head, uint16_t* tail, uint16_t minConf, Meas_eMeasurementKind_t kind);

/* **************************************************************************//**
 * @brief
 * Measurement Event Occurred in Path 1
 *
 * Interrupt service routine, that is triggered, if an measurement event in path1 occurred
 *
 * @return      none
 * ****************************************************************************/
void loc_MeasEvtOccuredInPath1(dsp_eInterruptVectorNum_t irqsrc, dsp_pInterruptContextData_t contextdata);

/* **************************************************************************//**
 * @brief
 * Measurement Event Occurred in Path 2
 *
 * Interrupt service routine, that is triggered, if an measurement event in path2 occurred
 *
 * @return      none
 * ****************************************************************************/
void loc_MeasEvtOccuredInPath2(dsp_eInterruptVectorNum_t irqsrc, dsp_pInterruptContextData_t contextdata);

void loc_EevalDmaWrapEventOccured(dsp_eInterruptVectorNum_t irqsrc, dsp_pInterruptContextData_t contextdata);
void loc_Eeval1DmaWrapEventOccured(dsp_eInterruptVectorNum_t irqsrc, dsp_pInterruptContextData_t contextdata);
void loc_Eeval2DmaWrapEventOccured(dsp_eInterruptVectorNum_t irqsrc, dsp_pInterruptContextData_t contextdata);

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * Initialize Application Module
 *
 * This function initializes the application module specific data structures
 *
 * @param       pApplRuntimeData        generic application data, should point to application environment data
 * @return      bool_t                  true if init was successful
 * ****************************************************************************/
bool_t app_Init(Dsi3Drv_pApplCtrlData_t pApplRuntimeData)
{
  bool_t retval = true;
  if(NULL != pApplRuntimeData)
  {
    /* save pointer to runtime data */
    loc_pApplRuntimeData = pApplRuntimeData;

    /* initialize dma interface */
    /* DMA for standard measurement */
    DSP_EEVAL_CTRL_DMA_WRAP_OFF;                        /* disable wrap around */
    DSP_EEVAL_CTRL_DMA_BUFFER_LENGTH_SET(0u);           /* set buffer size to zero, to disable dma until it is needed */
    DSP_EEVAL_CTRL_DMA_ADDR_SET(util_calculateDmaMemoryOffset((void*)pApplRuntimeData->MeasCtrl->Results.resultBuf.raw)); /* set pointer to standard measurement ringbuffer */
    /* DMA for advanced measurement */
    DSP_EEVAL1_CTRL_DMA_WRAP_OFF;                       /* disable wrap around */
    DSP_EEVAL1_CTRL_DMA_BUFFER_LENGTH_SET(0u);          /* set buffer size to zero, to disable dma until it is needed */
    DSP_EEVAL1_CTRL_DMA_ADDR_SET(util_calculateDmaMemoryOffset((void*)pApplRuntimeData->MeasCtrl->Results.resultBuf.raw)); /* set pointer to standard measurement ringbuffer */
    DSP_EEVAL2_CTRL_DMA_WRAP_OFF;                       /* disable wrap around */
    DSP_EEVAL2_CTRL_DMA_BUFFER_LENGTH_SET(0u);          /* set buffer size to zero, to disable dma until it is needed */
    DSP_EEVAL2_CTRL_DMA_ADDR_SET(util_calculateDmaMemoryOffset((void*)(&pApplRuntimeData->MeasCtrl->Results.resultBuf.adv[MEAS_ADVRESULTBUF_SINGLE_PATH_MAX])) ); /* set pointer to standard measurement ringbuffer */
    /* Register event callbacks */
//    retval = retval && dsp_RegisterCustomInterruptCallback(dsp_IRQ_EEVAL_TLH_EVT, loc_MeasEvtOccuredInPath1);
//    retval = retval && dsp_RegisterCustomInterruptCallback(dsp_IRQ_EEVAL_THL_EVT, loc_MeasEvtOccuredInPath1);
//    retval = retval && dsp_RegisterCustomInterruptCallback(dsp_IRQ_EEVAL_MAX_EVT, loc_MeasEvtOccuredInPath1);
//    retval = retval && dsp_RegisterCustomInterruptCallback(dsp_IRQ_EEVAL_MIN_EVT, loc_MeasEvtOccuredInPath1);
    retval = retval && dsp_RegisterCustomInterruptCallback(dsp_IRQ_EEVAL1_MAX_EVT, loc_MeasEvtOccuredInPath1);
    retval = retval && dsp_RegisterCustomInterruptCallback(dsp_IRQ_EEVAL2_MAX_EVT, loc_MeasEvtOccuredInPath2);
    retval = retval && dsp_RegisterCustomInterruptCallback(dsp_IRQ_EEVAL_DMA_WRAP, loc_EevalDmaWrapEventOccured);
    retval = retval && dsp_RegisterCustomInterruptCallback(dsp_IRQ_EEVAL1_DMA_WRAP, loc_Eeval1DmaWrapEventOccured);
    retval = retval && dsp_RegisterCustomInterruptCallback(dsp_IRQ_EEVAL2_DMA_WRAP, loc_Eeval2DmaWrapEventOccured);
    DSP_CTRL_IRQ_ENABLE(dsp_IRQ_EEVAL_DMA_WRAP);
    DSP_CTRL_IRQ_ENABLE(dsp_IRQ_EEVAL1_DMA_WRAP);
    DSP_CTRL_IRQ_ENABLE(dsp_IRQ_EEVAL2_DMA_WRAP);
    
    /* Calculate slope of temperature sensor curve with calibration value with 0,01*1024 = 10*/
    tsense_calib_eff = ((TSENS_SLOPE_EFF * (1024 + ((int32_t)(TSENS_GAIN - TSENS_GAIN_REF) *10))) >> 10);
  }
  else
  {
    retval = false;
    err_ErrorHandler(ERR_MODLIST_APP);
  }
  return retval;
}

/* **************************************************************************//**
 * @brief
 * PDCM: Measurement Response PDCM handler routine in Application Mode
 *
 * Sends 1 (allowed) data packet from the Measurement results pool.
 * On repeated PDCM req, iterates through allowed data packets.
 * If all allowed packets have been sent, continues to send ACK GRA packets.
 * Is called if in application mode
 *
 * @param       ansData                 pointer to PDCM response buffer for next PDCM pulse
 * @return      n/a
 * ****************************************************************************/
void app_PdcmCmdHandler_APP_MODE(Dsi3Drv_uPDCMResponseFrame_t* ansData)//数据写入函数
{
  if((NULL != ansData) && (NULL != loc_pApplRuntimeData))
  {
    /* store buffer pointer, to make them accessible easier */
    Meas_sEevalStdDataPacketFormat0*  loc_BufStd0 = &loc_pApplRuntimeData->MeasCtrl->Results.resultBuf.std_type0[0];
    Meas_sEevalStdDataPacketFormat1*  loc_BufStd1 = &loc_pApplRuntimeData->MeasCtrl->Results.resultBuf.std_type1[0];
    Meas_sEevalAdvDataPacketFormat*   loc_BufAdv1 = &loc_pApplRuntimeData->MeasCtrl->Results.resultBuf.adv[0];
    Meas_sEevalAdvDataPacketFormat*   loc_BufAdv2 = &loc_pApplRuntimeData->MeasCtrl->Results.resultBuf.adv[MEAS_ADVRESULTBUF_SINGLE_PATH_MAX];

    /* set default data */
    loc_SetPdcmAnswerFrameDefault(ansData);

    /* check if diagnostic measurement has finished */
    if(TRUE == loc_pApplRuntimeData->MeasCtrl->Results.DiagnosticMeasurement.AccquisitionFinished)
    {
      /* only send diagnostic measurement results of not already send */
      if(FALSE == loc_pApplRuntimeData->MeasCtrl->Results.DiagnosticMeasurement.ResultsReadout)
      {
        /* send result of <Diagnostic Measurement> (Supply, Temperature, Noise) */
        loc_SetPdcmAnswerFrameDiagnostic(ansData);
        /* indicate, that this data has been readout */
        loc_pApplRuntimeData->MeasCtrl->Results.DiagnosticMeasurement.ResultsReadout = TRUE;
      }
      else
      {
        /* only send burst and ringing monitoring, if in direct mode AND the results have not been send out already */
        if((meas_eMeasConf_INDIRECT != loc_pApplRuntimeData->MeasCtrl->RuntimeData.MeasurementConf) &&
           ((FALSE == loc_pApplRuntimeData->MeasCtrl->Results.BurstMonitoring.ResultsReadout) || (FALSE == loc_pApplRuntimeData->MeasCtrl->Results.RingingBehaviour.ResultsReadout)))
        {
          /* check if burst monitoring has finished */
          if(TRUE == loc_pApplRuntimeData->MeasCtrl->Results.BurstMonitoring.AccquisitionFinished)
          {
            /* only send burst monitoring results of not already send */
            if(FALSE == loc_pApplRuntimeData->MeasCtrl->Results.BurstMonitoring.ResultsReadout)
            {
              /* send result of <Burst monitoring> */
              loc_SetPdcmAnswerFrameBurst(ansData);
              /* indicate, that this data has been readout */
              loc_pApplRuntimeData->MeasCtrl->Results.BurstMonitoring.ResultsReadout = TRUE;
            }
            else
            {
              /* check if ringing behavior measurement has finished */
              if(TRUE == loc_pApplRuntimeData->MeasCtrl->Results.RingingBehaviour.AccquisitionFinished)
              {
                /* only send ringing behavior measurement results of not already send */
                if(FALSE == loc_pApplRuntimeData->MeasCtrl->Results.RingingBehaviour.ResultsReadout)
                {
                  /* send result of <Ringing behavior> */
                  loc_SetPdcmAnswerFrameRinging(ansData);
                  /* indicate, that this data has been readout */
                  loc_pApplRuntimeData->MeasCtrl->Results.RingingBehaviour.ResultsReadout = TRUE;
                }
                else
                {
                  /* this case should be impossible to reach*/
                  err_ErrorHandler(ERR_MODLIST_APP);
                }
              }
              else
              {
                /* Ringing Behavior measurement hasn't finished yet -> send empty packet */
                ansData->ringingResponseFrame.SubType           = DSI3_SUBTYPE_NO_DATA_AVAILABLE;
              }
            }
          }
          else
          {
            /* Burst Monitorung hasn't finished yet -> send empty packet */
            ansData->burstResponseFrame.SubType           = DSI3_SUBTYPE_NO_DATA_AVAILABLE;
          }
        }
        else
        {
          /* Status Frames have been send -> send any other frame e.g. measurement result or no information */
          /* send NFD results if available */
          if((TRUE == loc_pApplRuntimeData->MeasCtrl->Results.NearFieldDetection.Nfd1Finished) && (TRUE == loc_pApplRuntimeData->MeasCtrl->Results.NearFieldDetection.Nfd2Finished))
          {
            /* prepare answer buffer */
            loc_SetPdcmAnswerFrameNfd(ansData);
            /* prevent NFD from been send again */
            loc_pApplRuntimeData->MeasCtrl->Results.NearFieldDetection.Nfd1Finished = FALSE;
            loc_pApplRuntimeData->MeasCtrl->Results.NearFieldDetection.Nfd2Finished = FALSE;
          }
          else
          {
            /* check if standard or advanced */
            if(meas_eMeasKind_STANDARD == loc_pApplRuntimeData->MeasCtrl->RuntimeData.MeasurementKind)
            {
              /* standard measurement */
              /* are there any information to be send? */
              while ((0u != loc_pApplRuntimeData->MeasCtrl->Results.resultBuf.std_type1[loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufHead].timestamp)
                              && (loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufHead < loc_pApplRuntimeData->MeasCtrl->Results.MaxMeasurementSamples))
              {
                loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufHead++;
              }
  
              if(loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail < loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufHead)
              {
                /* check which format has been used */
                if(MEAS_EEVAL_STDDATAPACKET_FORMAT0 == DSP_EEVAL_CTRL_bit.eeval_dma_val)
                {
                  /* Standard Data Packet Format 0 */
                  loc_SetPdcmAnswerFrameStd0(ansData, loc_BufStd0);
                }
                else
                {
                  /* Standard Data Packet Format 1 */
                  loc_SetPdcmAnswerFrameStd1(ansData, loc_BufStd1);
                }
                /* increment Ringbuf Readout Pointer */
                loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail++;
              }
              else
              {
                /* no information -> send empty ack */
                ansData->standardResponseFrame.SubType = DSI3_SUBTYPE_NO_DATA_AVAILABLE;
              }
            }
            else
            {
              /* advanced measurement */
              /* ignore packets whose confidence level is to small */
              uint16_t resultsInPath1 = loc_GetRemainingResultCount((Meas_uEevalDataPacket*)loc_BufAdv1,
                                                           loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufHead,
                                                           &(loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail),
                                                           loc_pApplRuntimeData->MeasCtrl->RuntimeData.MinConf,
                                                           meas_eMeasKind_ADVANCED);
              uint16_t resultsInPath2 = loc_GetRemainingResultCount((Meas_uEevalDataPacket*)loc_BufAdv2,
                                                          loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufHead2,
                                                          &(loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail2),
                                                          loc_pApplRuntimeData->MeasCtrl->RuntimeData.MinConf,
                                                          meas_eMeasKind_ADVANCED);

              loc_eAdvPathNum_t returnFromPath = ADVANCED_PATH_NUMBER_NO_DATA;
              /* are there results in path 1? */
              if(resultsInPath1 > 0)
              {
                /* are there results in path 2 that have a smaller timestamp? */
                if( (resultsInPath2 > 0) &&
                    (loc_BufAdv2[loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail2].timestamp < loc_BufAdv1[loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail].timestamp) )
                {
                  /* there are data in path 1 and path 2 and path 2 data has a smaller timestamp and has to be send */
                  returnFromPath = ADVANCED_PATH_NUMBER_PATH2;
                }
                else
                {
                  /* there are data in path 1 and path 2 and path 1 data has a smaller timestamp and has to be send */
                  returnFromPath = ADVANCED_PATH_NUMBER_PATH1;
                }
              }
              else
              {
                /* are there results in path 2? */
                if(resultsInPath2 > 0)
                {
                  /* there are only data in path 2 -> send them */
                  returnFromPath = ADVANCED_PATH_NUMBER_PATH2;
                }
                else
                {
                  /* there are no data to send -> send empty frame */
                }
              }

              switch(returnFromPath)
              {
              case ADVANCED_PATH_NUMBER_PATH1:
                /* send data from path 1 */
                loc_SetPdcmAnswerFrameAdv(ansData, 0, loc_BufAdv1, &(loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail));

                /* check if results are still available */
                resultsInPath1 = loc_GetRemainingResultCount((Meas_uEevalDataPacket*)loc_BufAdv1,
                                                              loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufHead,
                                                              &(loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail),
                                                              loc_pApplRuntimeData->MeasCtrl->RuntimeData.MinConf,
                                                              meas_eMeasKind_ADVANCED);
                ansData->advancedResponseFrame.Buffer = ((resultsInPath1 + resultsInPath2) > 0);
                break;

              case ADVANCED_PATH_NUMBER_PATH2:
                /* send data from path 2 */
                loc_SetPdcmAnswerFrameAdv(ansData, 1, loc_BufAdv2, &(loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail2));

                /* check if results are still available */
                resultsInPath1 = loc_GetRemainingResultCount((Meas_uEevalDataPacket*)loc_BufAdv2,
                                                              loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufHead2,
                                                              &(loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail2),
                                                              loc_pApplRuntimeData->MeasCtrl->RuntimeData.MinConf,
                                                              meas_eMeasKind_ADVANCED);
                ansData->advancedResponseFrame.Buffer = ((resultsInPath1 + resultsInPath2) > 0);
                break;

              default:
                /* no information -> send empty ack */
                ansData->defaultResponseFrame.SubType = DSI3_SUBTYPE_NO_DATA_AVAILABLE;
                break;
              }
            }
          }
        }
      }
    }
    else
    {
      /* Diagnostic Measurement hasn't finished yet -> send empty packet */
      ansData->diagnosticResponseFrame.SubType        = DSI3_SUBTYPE_NO_DATA_AVAILABLE;
    }
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @brief
 * Reset measurement flags
 *
 * Resets all measurement related flags, like the measurement finished flag
 * This function needs to be called directly when a measurement is initated by the
 * dsi3 layer
 *
 * @param       pResultBuf            Pointer to measurement result buffer struct
 * @return      n.a.
 * ****************************************************************************/
void app_ResetMeasurementFlagsCritical(Meas_sMeasurementResults_t* pResultBuf)
{
  if(NULL != pResultBuf)
  {
    pResultBuf->BurstMonitoring.AccquisitionFinished = FALSE;
    pResultBuf->BurstMonitoring.ResultsReadout = FALSE;
    pResultBuf->DiagnosticMeasurement.AccquisitionFinished = FALSE;
    pResultBuf->DiagnosticMeasurement.ResultsReadout = FALSE;
    pResultBuf->RingingBehaviour.AccquisitionFinished = FALSE;
    pResultBuf->RingingBehaviour.ResultsReadout = FALSE;
    pResultBuf->NearFieldDetection.Nfd1Finished = FALSE;
    pResultBuf->NearFieldDetection.Nfd2Finished = FALSE;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @brief
 * Measurement Initiation
 *
 * Resets all measurement buffer and disables the dma
 *
 * @param       pResultBuf            Pointer to measurement result buffer struct
 * @return      n.a.
 * ****************************************************************************/
void app_MeasurementInit(Meas_sMeasurementResults_t* pResultBuf)
{
  if(NULL != pResultBuf)
  {
    /* deselect all eeval events */
    DSP_EEVAL_CTRL_SOURCE_SELECT_NONE();
    
    /* disable dma interface until its needed */
    DSP_EEVAL_CTRL_DMA_BUFFER_LENGTH_SET(0u);      /* set buffer size to zero, to disable dma until it is needed */
    DSP_EEVAL1_CTRL_DMA_BUFFER_LENGTH_SET(0u);     /* set buffer size to zero, to disable dma until it is needed */
    DSP_EEVAL2_CTRL_DMA_BUFFER_LENGTH_SET(0u);     /* set buffer size to zero, to disable dma until it is needed */

    /* reset result buffer */
    pResultBuf->MeasRingbufTail   = 0;
    pResultBuf->MeasRingbufTail2  = 0;
    pResultBuf->MeasRingbufHead   = 0;
    pResultBuf->MeasRingbufHead2  = 0;

    /* reset monitoring buffer */
    pResultBuf->MeasurementTime = 0;
    pResultBuf->BurstMonitoring.BurstLength = 0u;
    pResultBuf->BurstMonitoring.VoltageVTANK1 = 0;
    pResultBuf->BurstMonitoring.VoltageVTANK2 = 0;
    pResultBuf->RingingBehaviour.RingCount = 0;
    pResultBuf->RingingBehaviour.RingSamples = 0;
    pResultBuf->RingingBehaviour.RingTime = 0;
    pResultBuf->DiagnosticMeasurement.NoiseMeasNoiseCount = 0;
    pResultBuf->DiagnosticMeasurement.NoiseMeasNoiseSum = 0;
    pResultBuf->DiagnosticMeasurement.NoiseMeasSamplesTaken = 0;
    pResultBuf->NearFieldDetection.Nfd1DeltaEcho2 = 0;
    pResultBuf->NearFieldDetection.Nfd1DeltaEcho3 = 0;
    pResultBuf->NearFieldDetection.Nfd1Echo1 = 0;
    pResultBuf->NearFieldDetection.Nfd2Result = 0;
    pResultBuf->NearFieldDetection.Nfd1Flag = FALSE;
    pResultBuf->NearFieldDetection.Nfd2Flag = FALSE;

    /* reset result buffer */
    memset(pResultBuf->resultBuf.raw, 0, sizeof(pResultBuf->resultBuf.raw));
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @implementation
 * Diagnostic measurement
 *
 * Executes and saves supply voltage and temperature measurement
 * 
 * SM21: VSUP Monitor (Part 1 of 2)
 * (for details see SafetyManual)

 * SM110: Temperature measurement (Part 1 of 2)
 * (for details see SafetyManual)
 *
 *
 * @param       pResultBuf            Pointer to measurement result buffer structMeas_sMeasurementResults_t* pResultBuf
 * @return      void                  None
 * ****************************************************************************/
void app_DiagnosticMeasurement(Meas_sMeasurementResults_t* pResultBuf)
{
  if(NULL != pResultBuf)
  {
    /* Save the average of the supply voltage to result buffer.*/
    pResultBuf->DiagnosticMeasurement.VSUP = app_CheckVsup();  
    
    /* Measure temperature voltage */
    uint16_t tsense  = ada_TriggerSample(ada_eChannel_SUP, (ada_SignalSelect_t)ada_eSignal_SUP_V_TSENSE);
    
    /* Calculate the temperature in degree */
    tsense = (uint16_t)app_calculate_temperature(tsense);

    /* save result */
    pResultBuf->DiagnosticMeasurement.Temperature = (uint8_t)tsense;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @implementation
 * Noise measurement
 *
 * Executes and saves noise measurement data
 *
 * SM30: Noise Measurement (before) (Part 1 of 1)
 * (for details see SafetyManual)
 *
 * @param       pMeasCtrl             Pointer to measurement struct
 * @return      bool_t                true if measurement finished
 * ****************************************************************************/
bool_t app_NoiseMeasurement(Dsi3Drv_pMeasCtrl_t pMeasCtrl)
{
  bool_t retval = false;

  if(NULL != pMeasCtrl)
  {
    /* get sample */
    uint32_t loc_envSample = DSP_AMPD_ENV_VALUE();

    /* Collect all sample values for the Master (12 bit resolution)*/
    if((pMeasCtrl->Results.DiagnosticMeasurement.NoiseMeasNoiseSum + loc_envSample) > NOISEMEAS_NOISESUM_MAX)
    {
      /* Maximum value is reached. Keep the maximum. */
      pMeasCtrl->Results.DiagnosticMeasurement.NoiseMeasNoiseSum = NOISEMEAS_NOISESUM_MAX;
    }
    else
    {
      /* Sum-up all incomming values */
      pMeasCtrl->Results.DiagnosticMeasurement.NoiseMeasNoiseSum += loc_envSample;
    }

    /* count the samples, that overrun the threshold value (8 bit resolution) */
    if(loc_envSample > pMeasCtrl->Parameters.data.NoiseMeasurement.fields.NoiseMeasThreshold)
    {
      /* check if NoiseCount would exceed it's maximum value... */
      if(pMeasCtrl->Results.DiagnosticMeasurement.NoiseMeasNoiseCount < NOISEMEAS_NOISECNT_MAX)
      {
        /* ... and count if smaller ... */
        pMeasCtrl->Results.DiagnosticMeasurement.NoiseMeasNoiseCount++;
      }
      else
      {
        /* ... or limit it to it's maximum value */
        pMeasCtrl->Results.DiagnosticMeasurement.NoiseMeasNoiseCount = NOISEMEAS_NOISECNT_MAX;
      }
    }
    else
    {
      /* The envelope sample is smaller than the threshold value -> dont count it*/
    }

    /* Check if the end of the measurement is reached. */

    /* Count the amount of taken noise samples. */
    pMeasCtrl->Results.DiagnosticMeasurement.NoiseMeasSamplesTaken++;

    /* did we finish the noise measurement? */
    if((pMeasCtrl->Results.DiagnosticMeasurement.NoiseMeasSamplesTaken >= pMeasCtrl->Parameters.data.NoiseMeasurement.fields.NoiseMeasTime) ||
       (pMeasCtrl->Results.DiagnosticMeasurement.NoiseMeasSamplesTaken >= NOISE_MEASUREMENT_MAX_SAMPLES))
    {
      /* indicate, that diagnostic measurement has finished */
      pMeasCtrl->Results.DiagnosticMeasurement.AccquisitionFinished = TRUE;
      /* indicate, that measurement finished */
      retval = true;
    }
    else
    {
      /* Added to satisfy the coding rules. */
    }
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
  return retval;
}

/* **************************************************************************//**
 * @brief
 * Activate DMA for echo measurement
 *
 * Activates all dma channels that are needed for this measurement
 *
 * @param       measMode            Indicates if measuring in Standard or Advanced Mode
 * @return      n.a.
 * ****************************************************************************/
void app_ActivateDmaForEchoMeas(Meas_eMeasurementKind_t measMode)
{
  if(NULL != loc_pApplRuntimeData)
  {
    if(meas_eMeasKind_STANDARD == measMode)
    {
      /* standard measurement */
      /* activate the dma controller for data acquisition */
      uint16_t measurementLength = MEAS_STANDARDPATH_BUFFER_SIZE / 2;     /* set buffer size (in 32bit) to enable dma for standard measurement */
      
#if defined(FPGA_52417B)
      /* readout eeval_sel register to recover value */
      uint16_t eeval_sel = DSP_EEVAL_CTRL_SOURCE_SELECT_GET();
      
      /* Workaround eeval_sel */
      DSP_EEVAL_CTRL_SOURCE_SELECT_NONE();
#endif
      /* Set EEVAL_DMA_Buffer length */
      DSP_EEVAL_CTRL_DMA_BUFFER_LENGTH_SET(measurementLength);
      
#if defined(FPGA_52417B)     
      /* recover eeval_sel value */
      DSP_EEVAL_CTRL_SOURCE_SELECT_SET(eeval_sel);
#else
      /* Activate WRAP event see P52417-374 */
      DSP_EEVAL_CTRL_DMA_WRAP_ON;
#endif
      
      loc_pApplRuntimeData->MeasCtrl->Results.MaxMeasurementSamples = measurementLength;
      DSP_CTRL_IRQ_CLEAR(dsp_IRQ_EEVAL_TLH_EVT);
      DSP_CTRL_IRQ_CLEAR(dsp_IRQ_EEVAL_THL_EVT);
      DSP_CTRL_IRQ_CLEAR(dsp_IRQ_EEVAL_MAX_EVT);
      DSP_CTRL_IRQ_CLEAR(dsp_IRQ_EEVAL_MIN_EVT);
    }
    else
    {
      if(meas_eMeasKind_ADVANCED == measMode)
      {
        /* advanced measurement */
        /* activate the dma controller for data acquisition */
        uint16_t measurementLength = MEAS_ADVANCEDPATH_BUFFER_SIZE / 2;   /* set buffer size (in 32bit) to enable dma for advanced measurement */
        DSP_EEVAL2_CTRL_DMA_BUFFER_LENGTH_SET(measurementLength);
        DSP_EEVAL1_CTRL_DMA_BUFFER_LENGTH_SET(measurementLength);
        loc_pApplRuntimeData->MeasCtrl->Results.MaxMeasurementSamples = measurementLength;

        DSP_CTRL_IRQ_CLEAR(dsp_IRQ_EEVAL1_MAX_EVT);
        DSP_CTRL_IRQ_CLEAR(dsp_IRQ_EEVAL2_MAX_EVT);
        DSP_CTRL_IRQ_ENABLE(dsp_IRQ_EEVAL1_MAX_EVT);
        DSP_CTRL_IRQ_ENABLE(dsp_IRQ_EEVAL2_MAX_EVT);
      }
      else
      {
        /* this case should be impossible */
      }
    }
  }
  else
  {
    /* this case should be impossible */
  }
}

/* **************************************************************************//**
 * @brief
 * Check Vsup
 *
 * Measures Vsup and returns its value 
 *
 * SM23: Ringing behavior (Part 2 of 4)
 * (for details see SafetyManual)
 *
 * SM83: Measurement VSupply (Part 1 of 2)
 * (for details see SafetyManual)
 *
 * @return      uint16_t          Result of Vsup measurement
 * ****************************************************************************/
/*
app_CheckVsup 函数的主要功能是测量并返回供电电压(Vsup)的值，并进行了合理性和有效性的检查。以下是函数的详细步骤：
1. 通过调用 ada_TriggerSample 函数测量 Vsup 电压，这里选择的是 SUP 通道，并指定要测量的信号为 SUP_VSUP_DIV8，这意味着实际测量的是 Vsup 电压除以8后的值，存储在16位变量 retval 中。
2. 对测量得到的 Vsup 值进行合理性检查，即判断其是否在预定的操作范围内（VSUP_OP_MIN 至 VSUP_OP_MAX）。
如果 Vsup 值超出范围，则表明 Vsup 电压存在异常，此时：•设置硬件错误标志，具体为 ERR_NO_ERROR1 错误码，并关联上 ERR_VSUP_VOLTAGE_OUT_OF_RANGE 错误原因。
3. 如果 Vsup 值在合理范围内，则无需执行额外的操作。4. 最终返回测量得到的 Vsup 电压值（16位无符号整数形式）。
注意：•函数文档提到的 "SM23: Ringing behavior" 和 "SM83: Measurement VSupply" 可能是安全手册中关于如何处理电压测量时可能出现的振铃现象和如何准确测量供电电压的相关章节。
在实际应用中，开发者应参考对应的安全手册了解具体实施细节。
*/
uint16_t app_CheckVsup(void)
{
  /* measure Vsup four times and calculate the mean value */
  uint16_t retval = ada_TriggerSample(ada_eChannel_SUP, (ada_SignalSelect_t)ada_eSignal_SUP_VSUP_DIV8);
  /* Check VSUP for plausibility */
  if( (retval < VSUP_OP_MIN) || (retval > VSUP_OP_MAX) )
  {
    /* VSUP_Operation out of bound -> set error flag */
    err_SetHwErrorFlag(ERR_NO_ERROR1, ERR_VSUP_VOLTAGE_OUT_OF_RANGE);
  }
  else
  {
    /* nothing to be done */
  }    
  /* return Vsup */
  return retval;
}

/* **************************************************************************//**
 * @brief
 * Check Vtank
 *
 * Measures Vtank and returns its value
 * SM21: VSUP Monitor
 * (for details see SafetyManual)
 *
 * SM23: Ringing behavior (Part 3 of 4) (For Part 1 see: mod_app.c)
 * (for details see SafetyManual)
 *
 * SM83: Measurement VSupply (Part 2 of 2)
 * (for details see SafetyManual)
 *
 * @return      uint16_t          Result of Vtank measurement
 * ****************************************************************************/
uint16_t app_CheckVtank(void)
{
  /* measure Vtank four times and calculate the mean value */
  uint16_t retval = ada_TriggerSample(ada_eChannel_SUP, (ada_SignalSelect_t)ada_eSignal_SUP_VTANK_DIV8);
  
  /* boundary check in Vtank_Monitoring () during burst */  
  
  /* return Vtank */
  return retval;
}

/* **************************************************************************//**
 * @brief
 * Vsup monitoring
 *
 * Measures Vsup and compares the result to a threshold
 *
 * SM21: VSUP Monitor (Part 2 of 2)
 * (for details see SafetyManual)
 *
 * @param       pMeasCtrl             Pointer to measurement structure
 * @return      none
 * ****************************************************************************/
void app_VtankMonitoring(Dsi3Drv_pMeasCtrl_t pMeasCtrl)
{
  if(NULL != pMeasCtrl)
  {
    /* measure vtank 4 times and average results */
    uint16_t vtank = app_CheckVtank();

    /* Check if it is the first value of the test sequence.*/ 
    if(0 == pMeasCtrl->Results.BurstMonitoring.VoltageVTANK1)
    {
      /* save first sample */
      pMeasCtrl->Results.BurstMonitoring.VoltageVTANK1 = vtank;
    }
    else
    {
      /* Safe all further samples, to send the last sample at the end */
      pMeasCtrl->Results.BurstMonitoring.VoltageVTANK2 = vtank;
    }
    
    if(vtank < pMeasCtrl->Parameters.data.GeneralSettings.fields.UnderVoltageThreshold)
    {
      /* stop burst */
      BRG_CTRL_HALT();
      /* switch burst pulses to zero, to prevent pulse generation on accident (see SM13) done in loc_TaskState_POST_MEAS */
      
      /* VTANK to low -> set HwErr Flag */
      err_SetHwErrorFlag(ERR_NO_ERROR1, ERR_UNDER_VOLTAGE_AT_VTANK_DURING_BURST);
    }
    else if (  vtank > VTANK_OP_MAX )
    {
      /* set error flag */
      err_SetHwErrorFlag(ERR_NO_ERROR1, ERR_OVER_VOLTAGE_AT_VTANK_DURING_BURST);
    }
    else
    {
      /* everything ok -> nothing to do here */
    }
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @brief
 * Ringing Behavior
 *
 * Acquires and saves results from ringing time and frequency measurement
 *
 * SM11: Ringing frequency measurement (Part 1 of 2)
 * (for details see SafetyManual)
 *
 * SM23: Ringing behavior (Part 1 of 4) (For Parts 2 to 4 see: mod_self_test.c)
 * (for details see SafetyManual)
 *
 * SM24: Ringing time measurement (Part 1 of 2) (For Part 2 see: mod_self_test.c)
 * (for details see SafetyManual)
 *
 * @param       pMeasCtrl             Pointer to measurement struct
 * @return      void                  None.
 * ****************************************************************************/
void app_RingingBehaviour(Dsi3Drv_pMeasCtrl_t pMeasCtrl)
{
  if(NULL != pMeasCtrl)
  {
    /* ringing frequency measurement */
    if((RFM_STATUS_FINISHED == DSP_RFM_CTRL_bit.rfm_status) && (0 == pMeasCtrl->Results.RingingBehaviour.RingSamples))
    {
      pMeasCtrl->Results.RingingBehaviour.RingCount  = DSP_RFM_COUNTS_bit.rfm_counts;
      pMeasCtrl->Results.RingingBehaviour.RingSamples= DSP_RFM_SAMPLES_bit.rfm_samples;
    }
    else
    {
      /* ringing frequency measurement hasn't finished yet -> don't save results */
    }

    /* ringing time measurement */
    if((RTM_STATUS_FINISHED == DSP_RTM_bit.rtm_rt_end) && (0 == pMeasCtrl->Results.RingingBehaviour.RingTime))
    {
      pMeasCtrl->Results.RingingBehaviour.RingTime   = DSP_RTM_bit.rtm_rt;
      /* Indicate, that ringing behavior measurement has finished */
      pMeasCtrl->Results.RingingBehaviour.AccquisitionFinished = TRUE;
    }
    else
    {
      /* ringing time measurement hasn't finished yet -> don't save results */
    }
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @brief
 * Near field detection
 *
 * Runs near field detection algorithm
 *
 * @param       pMeasCtrl             Pointer to measurement struct
 * @param       measurementTime       Expired time of the current measurement
 * @return      none
 * ****************************************************************************/
void app_NearFieldDetection(Dsi3Drv_pMeasCtrl_t pMeasCtrl, uint16_t measurementTime)
{
  if(NULL != pMeasCtrl)
  {
    /* evaluate nfd results with algorithm 1 */
    if(NFD1_MAX_TIME_TO_THIRD_ECHO == measurementTime)
    {
      /* prefetch register values */
      uint16_t loc_DspEcho1 = DSP_NFD_ECHO1_GET();
      uint16_t loc_DspEcho2 = DSP_NFD_ECHO2_GET();
      uint16_t loc_DspEcho3 = DSP_NFD_ECHO3_GET();
      uint16_t loc_DspEchoTime1 = DSP_NFD_TS1_GET();
      uint16_t loc_DspEchoTime2 = DSP_NFD_TS2_GET();
      uint16_t loc_DspEchoTime3 = DSP_NFD_TS3_GET();

      uint16_t nfd_max_num = DSP_NFD_CTRL_bit.nfd_max_num;

      /* check if first echo has been recorded in time (2ms) */
      if((nfd_max_num > 0) && (loc_DspEcho1 > 0) && (loc_DspEchoTime1 < NFD1_MAX_TIME_BETWENN_TWO_ECHOS))
      {
        /* valid echo detected -> save data with a 8us resolution (divide by 8) */
        pMeasCtrl->Results.NearFieldDetection.Nfd1Echo1 = loc_DspEchoTime1 >> 3;

        /* check if second echo has been recorded in time (4ms) */
        if((nfd_max_num > 1u) && (loc_DspEcho2 < loc_DspEcho1) && ((uint16_t)(loc_DspEchoTime2 - loc_DspEchoTime1) < NFD1_MAX_TIME_BETWENN_TWO_ECHOS))
        {
          /* set NFD1 Flag if NFD_CTRL.nfd_irq_cfg = 0 */
          if ( dsp_eNFDIRQ_2_ECHOS == DSP_NFD_CTRL_IRQ_GET() )
          {
            pMeasCtrl->Results.NearFieldDetection.Nfd1Flag = TRUE;
          }
          else
          {
            /* check next echo */
          }
          /* safe delta between echo event 1 and echo event 2 with a 8us resolution (divide by 8)*/
          pMeasCtrl->Results.NearFieldDetection.Nfd1DeltaEcho2 = (loc_DspEchoTime2 - loc_DspEchoTime1) >> 3;

          /* check if third echo has been recorded in time (6ms) */
          if((loc_DspEcho3 < loc_DspEcho2) && ((uint16_t)(loc_DspEchoTime3 - loc_DspEchoTime2) < NFD1_MAX_TIME_BETWENN_TWO_ECHOS))
          {
            /* set NFD1 Flag */
            pMeasCtrl->Results.NearFieldDetection.Nfd1Flag = TRUE;
            /* safe delta between echo event 2 and echo event 3 with a 8us resolution (divide by 8)*/
            pMeasCtrl->Results.NearFieldDetection.Nfd1DeltaEcho3 = (loc_DspEchoTime3 - loc_DspEchoTime2) >> 3;
          }
          else
          {
            /* nothing to do here */
          }
        }
        else
        {
          /* nothing to do here */
        }
      }
      else
      {
        /* nothing to do here */
      }

      /* NFD algorithm 1 finished */
      pMeasCtrl->Results.NearFieldDetection.Nfd1Finished = TRUE;
    }
    else
    {
      /* nothing to do here */
    }

  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @brief
 * Deactivate DMA for echo measurement
 *
 * Deactivates all dma channels for echo measurement
 *
 * @return      n.a.
 * ****************************************************************************/
void app_DeactivateDmaForEchoMeas(void)
{
  /* disable dma interrupts */
  DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL_TLH_EVT);
  DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL_THL_EVT);
  DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL_MAX_EVT);
  DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL_MIN_EVT);
  DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL1_MAX_EVT);
  DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL2_MAX_EVT);
    
  /* disable dma interface */
  DSP_EEVAL_CTRL_DMA_BUFFER_LENGTH_SET(0u);      /* set buffer size to zero, to disable dma */
  DSP_EEVAL1_CTRL_DMA_BUFFER_LENGTH_SET(0u);     /* set buffer size to zero, to disable dma */
  DSP_EEVAL2_CTRL_DMA_BUFFER_LENGTH_SET(0u);     /* set buffer size to zero, to disable dma */
}
/* ****************************************************************************/
/* ******************** LOCAL FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * Set pdcm frame for default data
 *
 * initiates all data in the answer buffer to zero
 *
 * @param       ansData                         pointer to PDCM response buffer for next PDCM pulse
 * @return      n.a.
 * ****************************************************************************/
void loc_SetPdcmAnswerFrameDefault(Dsi3Drv_uPDCMResponseFrame_t* ansData)
{
  if(NULL != ansData)
  {
    ansData->defaultResponseFrame.Data2   = 0;
    ansData->defaultResponseFrame.Data3   = 0;
    ansData->defaultResponseFrame.Data4   = 0;
    ansData->defaultResponseFrame.Data5   = 0;
    ansData->defaultResponseFrame.Data6   = 0;
    ansData->standardResponseFrame.Type = DSI3_TYPE_MEAS_RESULT_APP_MODE;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @brief
 * Set pdcm frame for diagnostic data
 *
 * Copy data from diagnostic measurement into pdcm answer buffer
 *
 * @param       ansData                         pointer to PDCM response buffer for next PDCM pulse
 * @return      n.a.
 * ****************************************************************************/
void loc_SetPdcmAnswerFrameDiagnostic(Dsi3Drv_uPDCMResponseFrame_t* ansData)
{
  if(NULL != ansData)
  {
    ansData->diagnosticResponseFrame.NoiseCount     = loc_pApplRuntimeData->MeasCtrl->Results.DiagnosticMeasurement.NoiseMeasNoiseCount;
    ansData->diagnosticResponseFrame.NoiseSum7_0    = loc_pApplRuntimeData->MeasCtrl->Results.DiagnosticMeasurement.NoiseMeasNoiseSum & 0x00FFu;
    ansData->diagnosticResponseFrame.NoiseSum11_8   = (loc_pApplRuntimeData->MeasCtrl->Results.DiagnosticMeasurement.NoiseMeasNoiseSum & 0x0F00u) >> 8;
    ansData->diagnosticResponseFrame.VoltageVSUP3_0 = loc_pApplRuntimeData->MeasCtrl->Results.DiagnosticMeasurement.VSUP & 0x000Fu;
    ansData->diagnosticResponseFrame.VoltageVSUP9_4 = (loc_pApplRuntimeData->MeasCtrl->Results.DiagnosticMeasurement.VSUP & 0x03F0u) >> 4;
    ansData->diagnosticResponseFrame.reserved       = 0;
    ansData->diagnosticResponseFrame.Temperature    = loc_pApplRuntimeData->MeasCtrl->Results.DiagnosticMeasurement.Temperature;
    ansData->diagnosticResponseFrame.SubType        = DSI3_SUBTYPE_DIAGNOSTIC_DATA;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @brief
 * Set pdcm frame for burst data
 *
 * Copy data from burst monitoring into pdcm answer buffer
 *
 * @param       ansData                         pointer to PDCM response buffer for next PDCM pulse
 * @return      n.a.
 * ****************************************************************************/
void loc_SetPdcmAnswerFrameBurst(Dsi3Drv_uPDCMResponseFrame_t* ansData)
{
  if(NULL != ansData)
  {
    ansData->burstResponseFrame.VoltageVTANK1_7_0   = loc_pApplRuntimeData->MeasCtrl->Results.BurstMonitoring.VoltageVTANK1 & 0x00FFu;
    ansData->burstResponseFrame.VoltageVTANK1_9_8   = (loc_pApplRuntimeData->MeasCtrl->Results.BurstMonitoring.VoltageVTANK1 & 0x0300u) >> 8;
    ansData->burstResponseFrame.VoltageVTANK2_5_0   = loc_pApplRuntimeData->MeasCtrl->Results.BurstMonitoring.VoltageVTANK2 & 0x003Fu;
    ansData->burstResponseFrame.VoltageVTANK2_9_6   = (loc_pApplRuntimeData->MeasCtrl->Results.BurstMonitoring.VoltageVTANK2 & 0x03C0u) >> 6;
    ansData->burstResponseFrame.zeroes1             = 0;
    ansData->burstResponseFrame.BurstLength         = loc_pApplRuntimeData->MeasCtrl->Results.BurstMonitoring.BurstLength;
    ansData->burstResponseFrame.zeroes2             = 0;
    ansData->burstResponseFrame.SubType             = DSI3_SUBTYPE_BURST_DATA;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @brief
 * Set pdcm frame for ringing data
 *
 * Copy data from ringing measurement into pdcm answer buffer
 *
 * @param       ansData                         pointer to PDCM response buffer for next PDCM pulse
 * @return      n.a.
 * ****************************************************************************/
void loc_SetPdcmAnswerFrameRinging(Dsi3Drv_uPDCMResponseFrame_t* ansData)
{
  if(NULL != ansData)
  {
    ansData->ringingResponseFrame.RingTime7_0       = loc_pApplRuntimeData->MeasCtrl->Results.RingingBehaviour.RingTime & 0x00FFu;
    ansData->ringingResponseFrame.RingTime15_8      = (loc_pApplRuntimeData->MeasCtrl->Results.RingingBehaviour.RingTime & 0xFF00u) >> 8;
    ansData->ringingResponseFrame.RingSamples7_0    = loc_pApplRuntimeData->MeasCtrl->Results.RingingBehaviour.RingSamples & 0x00FFu;
    ansData->ringingResponseFrame.RingSamples9_8    = (loc_pApplRuntimeData->MeasCtrl->Results.RingingBehaviour.RingSamples & 0x0300u) >> 8;
    ansData->ringingResponseFrame.RingCount         = loc_pApplRuntimeData->MeasCtrl->Results.RingingBehaviour.RingCount;
    ansData->ringingResponseFrame.tbd               = 0;
    ansData->ringingResponseFrame.SubType           = DSI3_SUBTYPE_RINGING_DATA;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @brief
 * Set pdcm frame for nfd data
 *
 * Copy data from near field detection into pdcm answer buffer
 *
 * @param       ansData                         pointer to PDCM response buffer for next PDCM pulse
 * @return      n.a.
 * ****************************************************************************/
void loc_SetPdcmAnswerFrameNfd(Dsi3Drv_uPDCMResponseFrame_t* ansData)
{
  if(NULL != ansData)
  {
    ansData->nearFieldDetection.Nfd1Flag        = loc_pApplRuntimeData->MeasCtrl->Results.NearFieldDetection.Nfd1Flag;
    ansData->nearFieldDetection.Nfd2Flag        = loc_pApplRuntimeData->MeasCtrl->Results.NearFieldDetection.Nfd2Flag;
    ansData->nearFieldDetection.Nfd1_Echo1      = loc_pApplRuntimeData->MeasCtrl->Results.NearFieldDetection.Nfd1Echo1;
    ansData->nearFieldDetection.Nfd1DeltaEcho2  = loc_pApplRuntimeData->MeasCtrl->Results.NearFieldDetection.Nfd1DeltaEcho2;
    ansData->nearFieldDetection.Nfd1DeltaEcho3  = loc_pApplRuntimeData->MeasCtrl->Results.NearFieldDetection.Nfd1DeltaEcho3;
    ansData->nearFieldDetection.Nfd2Result      = loc_pApplRuntimeData->MeasCtrl->Results.NearFieldDetection.Nfd2Result;
    ansData->nearFieldDetection.SubType         = DSI3_SUBTYPE_NFD_DATA;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @brief
 * Set pdcm frame for standard measurement data format 0
 *
 * Copy data from standard measurement with format 0 into pdcm answer buffer
 *
 * @param       ansData                         pointer to PDCM response buffer for next PDCM pulse
 * @param       loc_BufStd0                     pointer to buffer
 * @return      n.a.
 * ****************************************************************************/
void loc_SetPdcmAnswerFrameStd0(Dsi3Drv_uPDCMResponseFrame_t* ansData, Meas_sEevalStdDataPacketFormat0* loc_BufStd0)
{
  uint16_t u16_correctedTimestamp = 0u;
   
  if((NULL != ansData) && (NULL != loc_BufStd0))
  {
     if (loc_BufStd0[loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail].timestamp >= loc_pApplRuntimeData->MeasCtrl->RuntimeData.TOF_Compensation )
    {
      u16_correctedTimestamp = loc_BufStd0[loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail].timestamp - loc_pApplRuntimeData->MeasCtrl->RuntimeData.TOF_Compensation;
    }
    else
    {
      /* corrected timestamp would be < 0,... so do not correct */
    }
            
    ansData->standardResponseFrame.TimeStamp7_0       = u16_correctedTimestamp & 0x00FFu;
    ansData->standardResponseFrame.TimeStamp15_8      = (u16_correctedTimestamp & 0xFF00u) >> 8;
    ansData->standardResponseFrame.EchoHeight_Raw7_0  = loc_BufStd0[loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail].envpEnvRaw & 0x00FFu;
    ansData->standardResponseFrame.EchoHeight_Raw13_8 = (loc_BufStd0[loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail].envpEnvRaw & 0x3F00u) >> 8;
    ansData->standardResponseFrame.EchoEvent          = loc_BufStd0[loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail].eventType;
    ansData->standardResponseFrame.Buffer             = ((0 != loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufHead) && (loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail < (loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufHead - 1)));
    ansData->standardResponseFrame.zeroes             = 0;
    ansData->standardResponseFrame.SubType            = DSI3_SUBTYPE_STD_ECHO_DATA;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @brief
 * Set pdcm frame for standard measurement data format 1
 *
 * Copy data from standard measurement with format 1 into pdcm answer buffer
 *
 * @param       ansData                         pointer to PDCM response buffer for next PDCM pulse
 * @param       loc_BufStd1                     pointer to buffer
 * @return      n.a.
 * ****************************************************************************/
void loc_SetPdcmAnswerFrameStd1(Dsi3Drv_uPDCMResponseFrame_t* ansData, Meas_sEevalStdDataPacketFormat1*  loc_BufStd1)
{
  uint16_t u16_correctedTimestamp = 0u;
   
  if((NULL != ansData) && (NULL != loc_BufStd1))
  {
    if (loc_BufStd1[loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail].timestamp >= loc_pApplRuntimeData->MeasCtrl->RuntimeData.TOF_Compensation )
    {
      u16_correctedTimestamp = loc_BufStd1[loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail].timestamp - loc_pApplRuntimeData->MeasCtrl->RuntimeData.TOF_Compensation;
    }
    else
    {
      /* corrected timestamp would be < 0,... so do not correct */
    }
        
    ansData->standardResponseFrame.TimeStamp7_0       = u16_correctedTimestamp & 0x00FFu;
    ansData->standardResponseFrame.TimeStamp15_8      = (u16_correctedTimestamp & 0xFF00u) >> 8;
    ansData->standardResponseFrame.EchoHeight_Raw7_0  = loc_BufStd1[loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail].ampdEnv & 0x00FFu;
    ansData->standardResponseFrame.EchoHeight_Raw13_8 = 0;
    ansData->standardResponseFrame.EchoEvent          = loc_BufStd1[loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail].eventType;
    ansData->standardResponseFrame.Buffer             = ((0 != loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufHead) && (loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufTail < (loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufHead - 1)));
    ansData->standardResponseFrame.zeroes             = 0;
    ansData->standardResponseFrame.SubType            = DSI3_SUBTYPE_STD_ECHO_DATA_SELECTED;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @brief
 * Set pdcm frame fro advanced measurement data
 *
 * Copys the given data from the advanced path buffer to the pdcm answer buffer
 *
 * @param       ansData                         pointer to PDCM response buffer for next PDCM pulse
 * @param       frameSelect                     Frame select of given data
 * @param       buffer                          pointer to advanced meas result buffer
 * @param       tail                            Pointer to Tail counter of given buffer
 * @return      n.a.
 * ****************************************************************************/
void loc_SetPdcmAnswerFrameAdv(Dsi3Drv_uPDCMResponseFrame_t* ansData, uint8_t frameSelect, Meas_sEevalAdvDataPacketFormat* buffer, uint16_t* tail)
{
  uint16_t u16_correctedTimestamp = 0u;
 
  if((NULL != ansData) && (NULL != buffer) && (NULL != tail)) /* TOF Compensation? siko */
  {

    if (buffer[*tail].timestamp >= loc_pApplRuntimeData->MeasCtrl->RuntimeData.TOF_Compensation )
    {
      u16_correctedTimestamp = buffer[*tail].timestamp - loc_pApplRuntimeData->MeasCtrl->RuntimeData.TOF_Compensation;
    }
    else
    {
      /* corrected timestamp would be < 0,... so do not correct */
    }

    ansData->advancedResponseFrame.TimeStamp7_0         = u16_correctedTimestamp & 0x00FFu;
    ansData->advancedResponseFrame.TimeStamp15_8        = ( u16_correctedTimestamp & 0xFF00u ) >> 8;
    ansData->advancedResponseFrame.EchoHeight7_0        = buffer[*tail].envData & 0x00FFu;
    ansData->advancedResponseFrame.EchoHeight15_8       = (buffer[*tail].envData & 0xFF00u) >> 8;
    ansData->advancedResponseFrame.Confidence           = buffer[*tail].confLvl;
    ansData->advancedResponseFrame.FrameSelect          = frameSelect;
    ansData->advancedResponseFrame.zeroes               = 0;
    ansData->advancedResponseFrame.SubType              = DSI3_SUBTYPE_ADV_ECHO_DATA;
    /* increment Ringbuf Readout Pointer */
    (*tail)++;
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @brief
 * Get remaining result count
 *
 * Returns the number of remaining results in the given buffer.
 * In case of results from an advanced measurement, results with low confidence level will be skipped
 *
 * @param       buffer                          Pointer to measurement result buffer
 * @param       head                            Head counter of given buffer
 * @param       tail                            Pointer to Tail counter of given buffer
 * @param       minConf                         Minimum confidence level for adavnced meas results
 * @param       kind                            Standard ord Advanced Measurement results
 * @return      uint16_t      Number of remaining results in given buffer
 * ****************************************************************************/
uint16_t loc_GetRemainingResultCount(Meas_uEevalDataPacket* buffer, uint16_t head, uint16_t* tail, uint16_t minConf, Meas_eMeasurementKind_t kind)
{
  uint16_t retval = 0;

  if((NULL != buffer) && (NULL != tail))
  {
    if((head > (*tail)))
    {
      if(meas_eMeasKind_ADVANCED == kind)
      {
        /* skip results in advanced result buffer, if below min confidence lvl */
        while((buffer->adv[(*tail)].confLvl < minConf) && ((*tail) < head))/*-?|AP2|wladimir.pauls|c98|?*/
        {
          (*tail)++;
        }
      }
      else
      {
        /* no use atm */
      }

      /* calculate number of possibly valid remaining results in given buffer */
      retval = head - (*tail);
    }
    else
    {
      /* no data in buffer -> return 0 */
    }
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }

  return retval;
}

/* **************************************************************************//**
 * @brief
 * Measurement Event Occurred in Path 1
 *
 * Interrupt service routine, that is triggered, if an measurement event in path1 occurred
 *
 * @param       irqsrc           DSP triggered interrupt number
 * @param       contextdata      pointer to DSP interrupt context data
 * @return      none
 * ****************************************************************************/
void loc_MeasEvtOccuredInPath1(dsp_eInterruptVectorNum_t irqsrc, dsp_pInterruptContextData_t contextdata)
{
  if(NULL != loc_pApplRuntimeData)
  {
    if(loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufHead != loc_pApplRuntimeData->MeasCtrl->Results.MaxMeasurementSamples)
    {
      loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufHead++;
    }
    else
    {
      /* deactivate DMA for STD and ADV mode */
//      DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL_TLH_EVT);
//      DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL_THL_EVT);
//      DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL_MAX_EVT);
//      DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL_MIN_EVT);
      DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL1_MAX_EVT);
    }
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @brief
 * Measurement Event Occurred in Path 2
 *
 * Interrupt service routine, that is triggered, if an measurement event in path2 occurred
 *
 * @param       irqsrc           DSP triggered interrupt number
 * @param       contextdata      pointer to DSP interrupt context data
 * @return      none
 * ****************************************************************************/
void loc_MeasEvtOccuredInPath2(dsp_eInterruptVectorNum_t irqsrc, dsp_pInterruptContextData_t contextdata)
{
  if(NULL != loc_pApplRuntimeData)
  {
    if(loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufHead2 != loc_pApplRuntimeData->MeasCtrl->Results.MaxMeasurementSamples)
    {
      loc_pApplRuntimeData->MeasCtrl->Results.MeasRingbufHead2++;
      DSP_CTRL_IRQ_CLEAR(irqsrc);
    }
    else
    {
      /* deactivate DMA for ADV mode */
      DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL2_MAX_EVT);
    }
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_APP);
  }
}

/* **************************************************************************//**
 * @brief
 * Wrap event in Eeval DMA occurred
 *
 * Interrupt service routine, that is triggered, if an wrap event in DMA EEval occurred
 *  (Echo evaluation DMA event for standart signal path)
 *
 * @param       irqsrc           DSP triggered interrupt number
 * @param       contextdata      pointer to DSP interrupt context data
 * @return      none
 * ****************************************************************************/
void loc_EevalDmaWrapEventOccured(dsp_eInterruptVectorNum_t irqsrc, dsp_pInterruptContextData_t contextdata)
{
  DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL_TLH_EVT);
  DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL_THL_EVT);
  DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL_MAX_EVT);
  DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL_MIN_EVT);
  
#if !defined(FPGA_52417B)  
  /* Set EEVAL_Sel to zero see P52417-374 */
  DSP_EEVAL_CTRL_SOURCE_SELECT_NONE();
#endif
}

/* **************************************************************************//**
 * @brief
 * Wrap event in Eeval1 DMA occurred
 *
 * Interrupt service routine, that is triggered, if an wrap event in DMA EEval1 occurred
 *  (Echo evaluation DMA event for advanced signal path 1) 
 *
 * @param       irqsrc           DSP triggered interrupt number
 * @param       contextdata      pointer to DSP interrupt context data
 * @return      none
 * ****************************************************************************/
void loc_Eeval1DmaWrapEventOccured(dsp_eInterruptVectorNum_t irqsrc, dsp_pInterruptContextData_t contextdata)
{
  DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL1_MAX_EVT);
}

/* **************************************************************************//**
 * @brief
 * Wrap event in Eeval2 DMA occurred
 *
 * Interrupt service routine, that is triggered, if an wrap event in DMA EEval2 occurred
 *  (Echo evaluation DMA event for advanced signal path 2)
 *
 * @param       irqsrc           DSP triggered interrupt number
 * @param       contextdata      pointer to DSP interrupt context data
 * @return      none
 * ****************************************************************************/
void loc_Eeval2DmaWrapEventOccured(dsp_eInterruptVectorNum_t irqsrc, dsp_pInterruptContextData_t contextdata)
{
  DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EEVAL2_MAX_EVT);
}

/* **************************************************************************//**
 * @brief
 * calculate temperature in degree with offset T_OFFSET. So no negative values are
 * needed
 *
 * @param       ada_val_temp    ada value of temp measurement
 * @return      tsens           Temperature in degree with offset T_OFFSET
 * ****************************************************************************/
uint8_t app_calculate_temperature(uint16_t ada_val_temp)
{
  int16_t tsens;

  tsens = T_OFFSET + TSENS_25D + (( (int16_t)(ada_val_temp - TSENS_OFF) * tsense_calib_eff)>>10);
 
  /* limit value to unsigned 8 bit value */
  if(tsens > 165) /* 125gradC + T_OFFSET */
  {
    tsens = 255;
    /* Temperature above 125gradC -> set HwErrFlag */
    err_SetHwErrorFlag(ERR_NO_ERROR1, ERR_TEMPERATURE_SESNOR_VOLTAGE_OUT_OF_RANGE);
  }
  else if(tsens < 0)
  {
    /* Temperature below -40gradC -> set HwErrFlag */
    tsens = 0;
    err_SetHwErrorFlag(ERR_NO_ERROR1, ERR_TEMPERATURE_SESNOR_VOLTAGE_OUT_OF_RANGE);
  }
 
  return (uint8_t)tsens;
}

