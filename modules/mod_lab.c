/***************************************************************************//**
 * @file      mod_lab.c
 *
 * @creator   KeLe
 * @created   22.11.2017
 *
 * @brief     Labmode software module
 *
 * @purpose
 *
 * Software module for managing and controlling lab mode processes.
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
 ******************************************************************************/

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_lab.h"
#include "mod_dsp.h"
#include "mod_app.h"
#include "mod_dsi3_cfg.h"
#include "mod_err.h"
#include "stdint.h"
#include "string.h"
#include "stdbool.h"
#include "mod_util.h"
#include "mod_ada.h"
#include "mod_dac.h"

/* ****************************************************************************/
/* **************************** CUSTOM INCLUDES *******************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define     MON_DS_MAX          5u               /* Maximum allowed value for MonDs */
#define     MON_CH_MAX          4u               /* Maximum allowed value for MonCh */
#define     MON_STARTMON_MAX    0x07FFu          /* Maximum allowed start monitor delay value */

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ***************************** GLOBAL VARIABLES *****************************/
/* ****************************************************************************/
uint16_t window_counter; /* Counter for already processed DMA buffer windows */

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/

extern Dsi3Drv_sMeasCtrl_t loc_AppRtData;

/* ****************************************************************************/
/* ********************   LOCAL FUNCTIONS    **********************************/
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * Wrap Around Event for Lab Mode Channels
 *
 * Interrupt service routine, that is triggered by EDI DMA, if all samples of a single channel are stored.
 *
 * @return      none
 * ****************************************************************************/
static void loc_EdiEventWrapAround(dsp_eInterruptVectorNum_t irqsrc, dsp_pInterruptContextData_t contextdata);

/* **************************************************************************//**
 * @brief
 * Prepares the type specific data for the lab mode
 * If no data is available 0 will be returned.
 *
 * @param       ansData               pointer to PDCM response buffer for next PDCM pulse
 * @param       type                  Labmode frame subtype
 * @return      none
 * ****************************************************************************/
static void loc_PrepLabFrame(Dsi3Drv_uPDCMResponseFrame_t* ansData, Dsi3_eLabmodeSubType_t type);

/* **************************************************************************//**
 * @brief
 * Returns the tail position of the next buffer sector
 *
 * The lab mode result buffer is related to the active channels split into up to 4 sections.
 * In order to prevent overwriting data of the next section the start of the next section can be read.
 *
 * @param       current_position    Current channel position in tails array
 *
 * @return      Tail position pointer for the next sector
 * ****************************************************************************/
static uint16_t* loc_ReturnNextBufferTailAddr(uint8_t current_position);

/* **************************************************************************//**
 * @brief
 * Switches next and current buffer for the channel data
 *
 * @param       ChData    Pointer to channel data structure
 * ****************************************************************************/
inline static void loc_switchBuffer(Lab_sChData* ChData);

inline static void loc_switchBuffer(Lab_sChData* ChData)
{
  uint16_t* temp_ptr;
  uint16_t temp_offset;

  temp_offset = ChData->NextBufferOffset;
  ChData->NextBufferOffset = ChData->CurrentBufferOffset;
  ChData->CurrentBufferOffset = temp_offset;

  temp_ptr = ChData->NextBuffer_ptr;
  ChData->NextBuffer_ptr = ChData->CurrentBuffer_ptr;
  ChData->CurrentBuffer_ptr = temp_ptr;
}

static void loc_EdiEventWrapAround(dsp_eInterruptVectorNum_t irqsrc, dsp_pInterruptContextData_t contextdata)/*-?|AP4|wladimir.pauls|c6|?*/
{
  /* Deactivate DMA_Channels before reconfigure new base addresses */
//  DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_3,0u);
//  DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_2,0u);
//  DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_1,0u);
//  DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_0,0u);
   /* Because DSP_EDI_DMA_CTRL_WRAP_OFF is set zero, speed up and write complete register */
    DSP_EDI0_DMA_CTRL = 0u;
    DSP_EDI1_DMA_CTRL = 0u;
    DSP_EDI2_DMA_CTRL = 0u;
    DSP_EDI3_DMA_CTRL = 0u;
  
  /* Alternate two in memory fixed DMA buffer */
  if(false == loc_AppRtData.Results.LabModeRuntimeData.Speedmode)
  {    
    DSP_EDI_DMA_ADDR(dsp_eEDI_CH_3, loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].NextBufferOffset);
    DSP_EDI_DMA_ADDR(dsp_eEDI_CH_2, loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].NextBufferOffset);
    DSP_EDI_DMA_ADDR(dsp_eEDI_CH_1, loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].NextBufferOffset);
    DSP_EDI_DMA_ADDR(dsp_eEDI_CH_0, loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].NextBufferOffset);
    
    /* Activate DMA_Channels with new base addresses */
//    DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_3,MEAS_EDI_DMA_SAMPLES_TOTAL);
//    DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_2,MEAS_EDI_DMA_SAMPLES_TOTAL);
//    DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_1,MEAS_EDI_DMA_SAMPLES_TOTAL);
//    DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_0,MEAS_EDI_DMA_SAMPLES_TOTAL);
       /* Because DSP_EDI_DMA_CTRL_WRAP_OFF is set zero, speed up and write complete register */
    DSP_EDI0_DMA_CTRL = MEAS_EDI_DMA_SAMPLES_TOTAL;
    DSP_EDI1_DMA_CTRL = MEAS_EDI_DMA_SAMPLES_TOTAL;
    DSP_EDI2_DMA_CTRL = MEAS_EDI_DMA_SAMPLES_TOTAL;
    DSP_EDI3_DMA_CTRL = MEAS_EDI_DMA_SAMPLES_TOTAL;
      
    loc_AppRtData.Results.LabModeRuntimeData.DmaBuffersPendingData = true;
  }
  /* Fastest possible mode. No down sampling, no calculations. DMA writes directly into the result buffer. */
  else
  {
    /* fast mode -switch to buffer 2 */
    if(buffer1 == loc_AppRtData.Results.LabModeRuntimeData.DmaBufferBlocked)
    {
      loc_AppRtData.Results.LabModeRuntimeData.DmaBufferBlocked = buffer2;
      
      loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch1].DmaBuffer2_ptr = loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch1].DmaBuffer2_ptr + 2*MEAS_EDI_DMA_SAMPLES_TOTAL;
      DSP_EDI_DMA_ADDR(dsp_eEDI_CH_0,  (uint16_t) ( (uintptr_t)loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch1].DmaBuffer2_ptr & 0x0000FFFFu ));
      
      loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch2].DmaBuffer2_ptr = loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch2].DmaBuffer2_ptr + 2*MEAS_EDI_DMA_SAMPLES_TOTAL;
      DSP_EDI_DMA_ADDR(dsp_eEDI_CH_1,  (uint16_t) ( (uintptr_t)loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch2].DmaBuffer2_ptr & 0x0000FFFFu ));
      
      loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch3].DmaBuffer2_ptr = loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch3].DmaBuffer2_ptr + 2*MEAS_EDI_DMA_SAMPLES_TOTAL;
      DSP_EDI_DMA_ADDR(dsp_eEDI_CH_2,  (uint16_t) ( (uintptr_t)loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch3].DmaBuffer2_ptr & 0x0000FFFFu ));
      
      loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch4].DmaBuffer2_ptr = loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch4].DmaBuffer2_ptr + 2*MEAS_EDI_DMA_SAMPLES_TOTAL;
      DSP_EDI_DMA_ADDR(dsp_eEDI_CH_3,  (uint16_t) ( (uintptr_t)loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch4].DmaBuffer2_ptr & 0x0000FFFFu ));
    }
    /* fast mode -switch to buffer 1 */
    else
    { 
      loc_AppRtData.Results.LabModeRuntimeData.DmaBufferBlocked = buffer1;
      
      loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch1].DmaBuffer1_ptr = loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch1].DmaBuffer1_ptr + 2*MEAS_EDI_DMA_SAMPLES_TOTAL;
      DSP_EDI_DMA_ADDR(dsp_eEDI_CH_0,  (uint16_t) ( (uintptr_t)loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch1].DmaBuffer1_ptr & 0x0000FFFFu ));
      
      loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch2].DmaBuffer1_ptr = loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch2].DmaBuffer1_ptr + 2*MEAS_EDI_DMA_SAMPLES_TOTAL;
      DSP_EDI_DMA_ADDR(dsp_eEDI_CH_1,  (uint16_t) ( (uintptr_t)loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch2].DmaBuffer1_ptr & 0x0000FFFFu ));
      
      loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch3].DmaBuffer1_ptr = loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch3].DmaBuffer1_ptr + 2*MEAS_EDI_DMA_SAMPLES_TOTAL;
      DSP_EDI_DMA_ADDR(dsp_eEDI_CH_2,  (uint16_t) ( (uintptr_t)loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch3].DmaBuffer1_ptr & 0x0000FFFFu ));
      
      loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch4].DmaBuffer1_ptr = loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch4].DmaBuffer1_ptr + 2*MEAS_EDI_DMA_SAMPLES_TOTAL;
      DSP_EDI_DMA_ADDR(dsp_eEDI_CH_3,  (uint16_t) ( (uintptr_t)loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[Ch4].DmaBuffer1_ptr & 0x0000FFFFu ));
    }
    
    loc_AppRtData.Results.LabModeRuntimeData.SampleCounter++;
    
    /* section buffer is full - disable interrupt */
    if(loc_AppRtData.Results.LabModeRuntimeData.Speedmode_samples_max ==  loc_AppRtData.Results.LabModeRuntimeData.SampleCounter)
    {
      DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EDI3_DMA_WRAP);
      
      /* DMA is not needed anymore, do not set length */
      
      loc_AppRtData.Results.LabModeRuntimeData.IsFinished = true;
      loc_AppRtData.Results.LabModeRuntimeData.IsRunning = false;
      
      uint16_t speedmode_recorded_values = loc_AppRtData.Results.LabModeRuntimeData.Speedmode_samples_max * MEAS_EDI_DMA_SAMPLES_TOTAL;
      
      /* indicate data to be ready to read out */
      if(loc_AppRtData.Parameters.data.Monitoring.fields.MonCh0 > 0)
      {
        loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].ChannelHeads_ptr = loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].ChannelTails_ptr + speedmode_recorded_values;
        loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].ChannelNextReadOut_ptr = loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].ChannelTails_ptr;
      }
      else
      {
        loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].ChannelHeads_ptr       = loc_AppRtData.Results.LabModeRuntimeData.DummyBuffer;
        /* read out pointer behind head avoids readout */
        loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].ChannelNextReadOut_ptr = loc_AppRtData.Results.LabModeRuntimeData.DummyBuffer+1;
      }
      if(loc_AppRtData.Parameters.data.Monitoring.fields.MonCh1 > 0)
      {
        loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].ChannelHeads_ptr = loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].ChannelTails_ptr + speedmode_recorded_values;
        loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].ChannelNextReadOut_ptr = loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].ChannelTails_ptr;
      }
      else
      {
        loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].ChannelHeads_ptr       = loc_AppRtData.Results.LabModeRuntimeData.DummyBuffer;
        /* read out pointer behind head avoids readout */
        loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].ChannelNextReadOut_ptr = loc_AppRtData.Results.LabModeRuntimeData.DummyBuffer+1;
      }
      if(loc_AppRtData.Parameters.data.Monitoring.fields.MonCh2 > 0)
      {
        loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].ChannelHeads_ptr = loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].ChannelTails_ptr + speedmode_recorded_values;
        loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].ChannelNextReadOut_ptr = loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].ChannelTails_ptr;
      }
      else
      {
        loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].ChannelHeads_ptr       = loc_AppRtData.Results.LabModeRuntimeData.DummyBuffer;
        /* read out pointer behind head avoids readout */
        loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].ChannelNextReadOut_ptr = loc_AppRtData.Results.LabModeRuntimeData.DummyBuffer+1;
      }
      if(loc_AppRtData.Parameters.data.Monitoring.fields.MonCh3 > 0)
      {
        loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].ChannelHeads_ptr = loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].ChannelTails_ptr + speedmode_recorded_values;
        loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].ChannelNextReadOut_ptr = loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].ChannelTails_ptr;
      }
      else
      {
        loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].ChannelHeads_ptr       = loc_AppRtData.Results.LabModeRuntimeData.DummyBuffer;
        /* read out pointer behind head avoids readout */
        loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].ChannelNextReadOut_ptr = loc_AppRtData.Results.LabModeRuntimeData.DummyBuffer+1;
      }
    }
    else
    {
      /* Activate DMA_Channels with new base addresses */
      DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_3,MEAS_EDI_DMA_SAMPLES_TOTAL);
      DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_2,MEAS_EDI_DMA_SAMPLES_TOTAL);
      DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_1,MEAS_EDI_DMA_SAMPLES_TOTAL);
      DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_0,MEAS_EDI_DMA_SAMPLES_TOTAL);
    }
  }
}

static void loc_PrepLabFrame(Dsi3Drv_uPDCMResponseFrame_t* ansData, Dsi3_eLabmodeSubType_t type)/*-?|AP4|wladimir.pauls|c7|?*//*-?|AP4|wladimir.pauls|c15|?*/
{
  if(NULL != ansData)
  {
    /* safe last frame type for alternating the frames if necessary */
    loc_AppRtData.Results.LabModeRuntimeData.LastSentFrameType = type;

    ansData->standardResponseFrame.Type = (Dsi3_ePDCMType_t)DSI3_TYPE_MEAS_RESULT_LAB_MODE;

      uint16_t next_byte = 0;

      if(DSI3_SUBTYPE_FRAME_1 == type)
          {
            ansData->labModeResponseFrame1.SubType = DSI3_SUBTYPE_FRAME_1;
            ansData->labModeResponseFrame1.MonChannel4_15_8 = 0;/*-?|AP4|wladimir.pauls|c8|*/
            ansData->labModeResponseFrame1.MonChannel4_7_0 = 0;
            ansData->labModeResponseFrame1.MonChannel3_15_8 = 0;
            ansData->labModeResponseFrame1.MonChannel3_7_0 = 0;/*-|AP4|wladimir.pauls|c8|?*/

            /* channel 4*/
            if( (true == loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].IsActive) &&
                (loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].ChannelNextReadOut_ptr <= loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].ChannelHeads_ptr) &&
                (loc_AppRtData.Parameters.data.Monitoring.fields.MonCh3 > 0))
            {
              next_byte = *loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].ChannelNextReadOut_ptr;
              ansData->labModeResponseFrame1.MonChannel4_15_8 = (uint8_t) ((next_byte & 0xFF00u) >> 8);
              ansData->labModeResponseFrame1.MonChannel4_7_0 = (uint8_t) (next_byte & 0x00FFu);
              loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].ChannelNextReadOut_ptr++;
            }
            else
            {
              ansData->labModeResponseFrame1.MonChannel4_15_8 = 0;
              ansData->labModeResponseFrame1.MonChannel4_7_0 = 0;
            }

            /* channel 3*/
            if( (true == loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].IsActive) &&
                (loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].ChannelNextReadOut_ptr <= loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].ChannelHeads_ptr) &&
                (loc_AppRtData.Parameters.data.Monitoring.fields.MonCh2 > 0))
            {
              next_byte = *loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].ChannelNextReadOut_ptr;
              ansData->labModeResponseFrame1.MonChannel3_15_8 = (uint8_t) ((next_byte & 0xFF00u) >> 8);
              ansData->labModeResponseFrame1.MonChannel3_7_0 =  (uint8_t) (next_byte & 0x00FFu);
              loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].ChannelNextReadOut_ptr++;
            }
            else
            {
               ansData->labModeResponseFrame1.MonChannel3_15_8 = 0;
               ansData->labModeResponseFrame1.MonChannel3_7_0 = 0;
            }
          }
      if(DSI3_SUBTYPE_FRAME_2 == type)
      {
        ansData->labModeResponseFrame2.SubType = DSI3_SUBTYPE_FRAME_2;/*-?|AP4|wladimir.pauls|c9|*/
        ansData->labModeResponseFrame2.MonChannel2_15_8 = 0;
        ansData->labModeResponseFrame2.MonChannel2_7_0 = 0;
        ansData->labModeResponseFrame2.MonChannel1_15_8 = 0;
        ansData->labModeResponseFrame2.MonChannel1_7_0 = 0;/*-|AP4|wladimir.pauls|c9|?*/

        /* channel 2*/
        if( (true == loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].IsActive) &&
            (loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].ChannelNextReadOut_ptr <= loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].ChannelHeads_ptr) &&
            (loc_AppRtData.Parameters.data.Monitoring.fields.MonCh1 > 0))
        {
          next_byte = *loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].ChannelNextReadOut_ptr;
          ansData->labModeResponseFrame2.MonChannel2_15_8 = (uint8_t) ((next_byte & 0xFF00u) >> 8);
          ansData->labModeResponseFrame2.MonChannel2_7_0 = (uint8_t) (next_byte & 0x00FFu);
          loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].ChannelNextReadOut_ptr++;
        }
        else
        {
           ansData->labModeResponseFrame2.MonChannel2_15_8 = 0;
           ansData->labModeResponseFrame2.MonChannel2_7_0 = 0;
        }
        /* channel 1*/
        if( (true == loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].IsActive) &&
            (loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].ChannelNextReadOut_ptr <= loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].ChannelHeads_ptr) &&
            (loc_AppRtData.Parameters.data.Monitoring.fields.MonCh0 > 0u))
        {
          next_byte = *loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].ChannelNextReadOut_ptr;
          ansData->labModeResponseFrame2.MonChannel1_15_8 = (uint8_t) ((next_byte & 0xFF00u) >> 8);
          ansData->labModeResponseFrame2.MonChannel1_7_0 = (uint8_t) (next_byte & 0x00FFu);
          loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].ChannelNextReadOut_ptr++;
        }
        else
        {
          ansData->labModeResponseFrame2.MonChannel1_15_8 = 0;
          ansData->labModeResponseFrame2.MonChannel1_7_0 = 0;
        }
      }
  }
  else
  {
    err_ErrorHandler(ERR_MODLIST_LAB);
  }
}

static uint16_t* loc_ReturnNextBufferTailAddr(uint8_t current_position)/*-?|AP4|wladimir.pauls|c10|?*/
{
  bool_t tail_not_found = true;
  uint16_t* next_tail_pos = NULL;
  uint8_t u8_indedx;/*-?|AP2|wladimir.pauls|c103|?*/
  
  for (u8_indedx=current_position; u8_indedx<(MEAS_EDI_DMA_CHANNELS-1) && tail_not_found; u8_indedx++)/*-?|AP4|wladimir.pauls|c11|?*/
  {
    /*looking for the next tail address*/
    if(loc_AppRtData.Results.LabModeRuntimeData.ChData[u8_indedx+1].ChannelTails_ptr != NULL)
    {
      next_tail_pos = loc_AppRtData.Results.LabModeRuntimeData.ChData[u8_indedx+1].ChannelTails_ptr; /* position in result buffer of the next tail */
      tail_not_found = false;
    }
  }

  /*if no tail has been found the tail is set to buffer max*/
  if(NULL == next_tail_pos)
  {
    next_tail_pos = &loc_AppRtData.Results.resultBuf.lab[MEAS_GLOBAL_BUFFER_SIZE-1];
  }

  return next_tail_pos;
}


/* ****************************************************************************/
/* ************************** GLOBAL FUNCTIONS ********************************/
/* ****************************************************************************/
void lab_init_module(void)
{
  /* register ISR - one ISR processes all channels */
  (void)dsp_RegisterCustomInterruptCallback(dsp_IRQ_EDI3_DMA_WRAP, loc_EdiEventWrapAround);
}

void lab_TaskState_INIT_Lab(void)
{
  /* Configure dma channels*/
  /**< Disable wrap around -  wrap interrupt will be generated */
  DSP_EDI_DMA_CTRL_WRAP_OFF_SET(dsp_eEDI_CH_3, false);
  DSP_EDI_DMA_CTRL_WRAP_OFF_SET(dsp_eEDI_CH_2, false);
  DSP_EDI_DMA_CTRL_WRAP_OFF_SET(dsp_eEDI_CH_1, false);
  DSP_EDI_DMA_CTRL_WRAP_OFF_SET(dsp_eEDI_CH_0, false);

  /**< Disable and resets the dma channels */
  DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_3,0u);
  DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_2,0u);
  DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_1,0u);
  DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_0,0u);

  /* init runtime data to 0 */
  /*suppress following rule because sizeof is same data area that is written to*/
  /*PRQA S 2840 1*/
  memset(&loc_AppRtData.Results.LabModeRuntimeData,0,sizeof(loc_AppRtData.Results.LabModeRuntimeData));

  loc_AppRtData.Results.LabModeRuntimeData.IsFinished = false;
  loc_AppRtData.Results.LabModeRuntimeData.IsRunning = false;

  /* MeasurementTimer has 32us steps, MonStart is in 32us steps and tof_comp in 1us steps  */
  uint32_t MonStartHelper = loc_AppRtData.Parameters.data.Monitoring.fields.MonStart+(loc_AppRtData.RuntimeData.TOF_Compensation>>5u); /* SMA52417-106 */
  
  if (MonStartHelper < MON_STARTMON_MAX)
  {
    loc_AppRtData.Results.LabModeRuntimeData.MonStart = MonStartHelper;
  }
  else
  {
    loc_AppRtData.Results.LabModeRuntimeData.MonStart = MON_STARTMON_MAX;
  }

  /* calculate the number of samples to be monitored */
  if(loc_AppRtData.Parameters.data.Monitoring.fields.MonDs <= MON_DS_MAX)
  {
    loc_AppRtData.Results.LabModeRuntimeData.MonitoringSamples = (uint16_t)1u << loc_AppRtData.Parameters.data.Monitoring.fields.MonDs;
  }
  else
  {
    loc_AppRtData.Results.LabModeRuntimeData.MonitoringSamples = 1u;
  }

  /* set data extraction mode depending on DMA buffer size an down sampling value */
  if(MEAS_EDI_DMA_SAMPLES_TOTAL > loc_AppRtData.Results.LabModeRuntimeData.MonitoringSamples) /* MonitorSamples represent the DownsamplingFactor */
  {
    window_counter = 0;
    loc_AppRtData.Results.LabModeRuntimeData.dma_buffer_bigger_than_downsampling = true;
  }
  else
  {
    loc_AppRtData.Results.LabModeRuntimeData.dma_buffer_bigger_than_downsampling = false;
  }

  bool_t channel_used[MEAS_EDI_DMA_CHANNELS];       /* Holds the information which channel is active */
  channel_used[Ch1] = false;
  channel_used[Ch2] = false;
  channel_used[Ch3] = false;
  channel_used[Ch4] = false;
  loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].IsActive = false;
  loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].IsActive = false;
  loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].IsActive = false;
  loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].IsActive = false;

  uint16_t activeLabModeChannels = 0;

  /**< Configure and count the number of selected channels */
  if((loc_AppRtData.Parameters.data.Monitoring.fields.MonCh0 > 0u) && (loc_AppRtData.Parameters.data.Monitoring.fields.MonCh0 <= MON_CH_MAX))
  {
    /* subtract one to fit the register description */
    DSP_EDI_DMA_CH0_SEL(loc_AppRtData.Parameters.data.Monitoring.fields.MonCh0-1);
    activeLabModeChannels++;
    channel_used[Ch1] = true;
    loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].IsActive = true;
  }

  if((loc_AppRtData.Parameters.data.Monitoring.fields.MonCh1 > 0u) && (loc_AppRtData.Parameters.data.Monitoring.fields.MonCh1 <= MON_CH_MAX))
  {
    /* subtract one to fit the register description */
    DSP_EDI_DMA_CH1_SEL(loc_AppRtData.Parameters.data.Monitoring.fields.MonCh1-1);
    activeLabModeChannels++;
    channel_used[Ch2] = true;
    loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].IsActive = true;
  }

  if((loc_AppRtData.Parameters.data.Monitoring.fields.MonCh2 > 0u) && (loc_AppRtData.Parameters.data.Monitoring.fields.MonCh2 <= MON_CH_MAX))
  {
    /* subtract one to fit the register description */
    DSP_EDI_DMA_CH2_SEL(loc_AppRtData.Parameters.data.Monitoring.fields.MonCh2-1);
    activeLabModeChannels++;
    channel_used[Ch3] = true;
    loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].IsActive = true;
  }

  if((loc_AppRtData.Parameters.data.Monitoring.fields.MonCh3 > 0u) && (loc_AppRtData.Parameters.data.Monitoring.fields.MonCh3 <= MON_CH_MAX))
  {
    /* subtract one to fit the register description */
    DSP_EDI_DMA_CH3_SEL(loc_AppRtData.Parameters.data.Monitoring.fields.MonCh3-1);
    activeLabModeChannels++;
    channel_used[Ch4] = true;
    loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].IsActive = true;
  }

  /* check for speed mode: downsampling must be 1 (no downsamping)*/
  if (1u == loc_AppRtData.Results.LabModeRuntimeData.MonitoringSamples)
  {
    loc_AppRtData.Results.LabModeRuntimeData.Speedmode = true;
    loc_AppRtData.Results.LabModeRuntimeData.Speedmode_samples_max = ((MEAS_LABMODE_BUFFER_SIZE/activeLabModeChannels)/MEAS_EDI_DMA_SAMPLES_TOTAL);
  }
  else
  {
    loc_AppRtData.Results.LabModeRuntimeData.Speedmode = false;
  }

  /* Calculate the free buffer memory depending on the current measurement (eg. Std. or Adv.) and the required memory by it.
   * The free memory can be used to store lab mode data.
   */
  uint8_t data_buffer_offset = 0;                                                         /**< identifies the first unused buffer element in global buffer that is usable for labmode data */
  if(meas_eMeasKind_STANDARD == loc_AppRtData.RuntimeData.MeasurementKind)
  {
    data_buffer_offset = MEAS_STANDARDPATH_BUFFER_SIZE;
  }
  else if (meas_eMeasKind_ADVANCED == loc_AppRtData.RuntimeData.MeasurementKind)
  {
    data_buffer_offset = MEAS_ADVANCEDPATH_BUFFER_SIZE;
  }
  else
  {
    // not used
  }

  /* divide data buffer according to the number of used channels */
  uint16_t buffer_entries_free = MEAS_GLOBAL_BUFFER_SIZE - data_buffer_offset;                  /**< available buffer size for labmode data */
  uint16_t buffer_entries_per_channel = 0;                                                      /**< available buffer size per active channel */
  uint16_t buffer_areas[MEAS_EDI_DMA_CHANNELS];                                                 /**< Holds the start addresses of the split result buffer for each EDI channel */
  memset(buffer_areas,0,sizeof(buffer_areas));
  switch(activeLabModeChannels)
  {
  case 1:
    buffer_areas[0] = data_buffer_offset;
    break;

  case 2:
    buffer_areas[0] = data_buffer_offset;
    buffer_entries_per_channel = buffer_entries_free >> 1;  /* divide available memory by two */
    buffer_areas[1] = buffer_areas[0] + buffer_entries_per_channel;
    break;

  case 3:
    /* as specified no memory optimization is applied - same memory usage as 4 channels */
    /* fall through */
  case 4:
    buffer_areas[0] = data_buffer_offset;
    buffer_entries_per_channel = buffer_entries_free >> 2;  /* divide available memory by four */
    buffer_areas[1] = buffer_areas[0] + buffer_entries_per_channel;
    buffer_areas[2] = buffer_areas[1] + buffer_entries_per_channel;
    buffer_areas[3] = buffer_areas[2] + buffer_entries_per_channel;
    break;

  default:
    /* no change */
    break;
  }

  /**< assign active channels to split buffer areas */
  uint8_t channel_assigned_counter = 0;

  uint8_t i;
  for(i=0u; i<MEAS_EDI_DMA_CHANNELS; i++)/*-?|AP4|wladimir.pauls|c12|?*/
  {
    if(true == channel_used[i])
    {
      /* set buffer ptr 1 to the start of the section*/
      loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[i].DmaBuffer1_ptr = &loc_AppRtData.Results.resultBuf.lab[buffer_areas[channel_assigned_counter]];
      loc_AppRtData.Results.LabModeRuntimeData.ChData[i].CurrentBufferOffset = (uint16_t) ( (uintptr_t)loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[i].DmaBuffer1_ptr & 0x0000FFFFu );
      loc_AppRtData.Results.LabModeRuntimeData.ChData[i].CurrentBuffer_ptr = loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[i].DmaBuffer1_ptr;

      if(true == loc_AppRtData.Results.LabModeRuntimeData.Speedmode)
      {
        /* set buffer ptr 2 to start one sample length earlier to reduce the needed logic in ISR to increase the pointer */
        loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[i].DmaBuffer2_ptr = &loc_AppRtData.Results.resultBuf.lab[buffer_areas[channel_assigned_counter]-MEAS_EDI_DMA_SAMPLES_TOTAL];
      }
      else
      {
        loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[i].DmaBuffer2_ptr = &loc_AppRtData.Results.resultBuf.lab[buffer_areas[channel_assigned_counter]+MEAS_EDI_DMA_SAMPLES_TOTAL];
        loc_AppRtData.Results.LabModeRuntimeData.ChData[i].NextBufferOffset = (uint16_t) ( (uintptr_t)loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[i].DmaBuffer2_ptr & 0x0000FFFFu );
        loc_AppRtData.Results.LabModeRuntimeData.ChData[i].NextBuffer_ptr = loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[i].DmaBuffer2_ptr;
      }

      loc_AppRtData.Results.LabModeRuntimeData.ChData[i].ChannelHeads_ptr = &(loc_AppRtData.Results.resultBuf.lab[buffer_areas[channel_assigned_counter]]) + (2*MEAS_EDI_DMA_SAMPLES_TOTAL);
      loc_AppRtData.Results.LabModeRuntimeData.ChData[i].ChannelNextReadOut_ptr = &(loc_AppRtData.Results.resultBuf.lab[buffer_areas[channel_assigned_counter]]) + (2*MEAS_EDI_DMA_SAMPLES_TOTAL);
      loc_AppRtData.Results.LabModeRuntimeData.ChData[i].ChannelTails_ptr = &(loc_AppRtData.Results.resultBuf.lab[buffer_areas[channel_assigned_counter]]);
      channel_assigned_counter++;
    }
    else
    {
      /* channel are not in use */

      /* set default values in case channels are not in use */
      loc_AppRtData.Results.LabModeRuntimeData.ChData[i].CurrentBuffer_ptr = &loc_AppRtData.Results.resultBuf.lab[buffer_areas[channel_assigned_counter]];
      loc_AppRtData.Results.LabModeRuntimeData.ChData[i].NextBuffer_ptr = &loc_AppRtData.Results.resultBuf.lab[buffer_areas[channel_assigned_counter]];
      loc_AppRtData.Results.LabModeRuntimeData.ChData[i].CurrentBufferOffset = (uint16_t) ( (uintptr_t)&loc_AppRtData.Results.LabModeRuntimeData.DummyBuffer[0] & 0x0000FFFFu );
      loc_AppRtData.Results.LabModeRuntimeData.ChData[i].NextBufferOffset = (uint16_t) ( (uintptr_t)&loc_AppRtData.Results.LabModeRuntimeData.DummyBuffer[0] & 0x0000FFFFu );

      loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[i].DmaBuffer1_ptr = &loc_AppRtData.Results.LabModeRuntimeData.DummyBuffer[0];
      loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[i].DmaBuffer2_ptr = &loc_AppRtData.Results.LabModeRuntimeData.DummyBuffer[0];
    }
  }

  /* store the tails of the next section */
  bool_t first_channel = true;            /* first channel is used to control the  section filling level */

  for(i=0; i<MEAS_EDI_DMA_CHANNELS; i++)
  {
    loc_AppRtData.Results.LabModeRuntimeData.ChData[i].NextSectionTails_ptr = loc_ReturnNextBufferTailAddr(i);

    /* store first section boundaries to control the section level filling */
    if((true == channel_used[i]) && (true == first_channel))
    {
      first_channel = false;

      loc_AppRtData.Results.LabModeRuntimeData.FillingLevelHead = &loc_AppRtData.Results.LabModeRuntimeData.ChData[i].ChannelHeads_ptr;
      loc_AppRtData.Results.LabModeRuntimeData.FillingLevelNextSection = &loc_AppRtData.Results.LabModeRuntimeData.ChData[i].NextSectionTails_ptr;
    }
  }

  /* set DMA to the first buffer */ 
  loc_AppRtData.Results.LabModeRuntimeData.DmaBufferBlocked = buffer1;

  DSP_EDI_DMA_ADDR(dsp_eEDI_CH_0, (uint16_t) ( (uintptr_t)loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[0].DmaBuffer1_ptr & 0x0000FFFFu ));
  DSP_EDI_DMA_ADDR(dsp_eEDI_CH_1, (uint16_t) ( (uintptr_t)loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[1].DmaBuffer1_ptr & 0x0000FFFFu ));
  DSP_EDI_DMA_ADDR(dsp_eEDI_CH_2, (uint16_t) ( (uintptr_t)loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[2].DmaBuffer1_ptr & 0x0000FFFFu ));
  DSP_EDI_DMA_ADDR(dsp_eEDI_CH_3, (uint16_t) ( (uintptr_t)loc_AppRtData.Results.LabModeRuntimeData.DmaBuffer_ptrs[3].DmaBuffer1_ptr & 0x0000FFFFu ));
  loc_AppRtData.Results.LabModeRuntimeData.IsInitialised = true;

  /* enable DMA Interrupts - all channels are processed within this ISR */
  DSP_CTRL_IRQ_ENABLE(dsp_IRQ_EDI3_DMA_WRAP);
}

/* *************************************************************************//**
 * @brief
 * Laboratory mode task
 *
 * @image html "lab_Task.png" "Activity Diagram: Laboratory mode task" max-width=640
 * <a href="lab_Task.png">klick here to enlarge image</a>
 *
 * @image html "Scenario2 downsampling using a distinct DMA buffer.png" "Scenario: normal lab-mode: downsampling active" max-width=640
 * <a href="Scenario2 downsampling using a distinct DMA buffer.png">klick here to enlarge image</a>
 *
 * @image html "Szenario1 no compression or Downsampling.png" "Scenario: speed lab-mode: no downsampling, dma writes directly to result-buffer" max-width=640
 * <a href="Szenario1 no compression or Downsampling.png">klick here to enlarge image</a>
 *
 * @param       none
 * @return      none
 * ****************************************************************************/
void lab_Task(void)
{
  if(true == loc_AppRtData.Results.LabModeRuntimeData.IsInitialised &&
     (true == loc_AppRtData.Results.LabModeRuntimeData.IsRunning) &&
       (false == loc_AppRtData.Results.LabModeRuntimeData.IsFinished))
  {
    if(true == loc_AppRtData.Results.LabModeRuntimeData.DmaBuffersPendingData)
    {
      loc_AppRtData.Results.LabModeRuntimeData.DmaBuffersPendingData = false;
      
      uint16_t loc_MonSamples = loc_AppRtData.Results.LabModeRuntimeData.MonitoringSamples;
      
      if(false == loc_AppRtData.Results.LabModeRuntimeData.Speedmode)
      {
        Lab_sChData* ChData_ptr_1 = &loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1];
        Lab_sChData* ChData_ptr_2 = &loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2];
        Lab_sChData* ChData_ptr_3 = &loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3];
        Lab_sChData* ChData_ptr_4 = &loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4];
        
        if(true == loc_AppRtData.Results.LabModeRuntimeData.dma_buffer_bigger_than_downsampling)
        {
          /* switch buffer ptr - DMA is not switched here */
          loc_switchBuffer(ChData_ptr_4);
          loc_switchBuffer(ChData_ptr_3);
          loc_switchBuffer(ChData_ptr_2);
          loc_switchBuffer(ChData_ptr_1);
          /*############# case 2###################*/
          /* iterate samples of the DMA buffer in configurable step size
          *
          * The pointer are already switched. The stored values are now accessible through
          * the Nextbuffer_ptr instead of CurrentBuffer_ptr
          * */
         /*
         uint16_t arrayWriteIndex = 0;

        for(smpl=0; smpl<MEAS_EDI_DMA_SAMPLES_TOTAL; smpl=smpl+loc_MonSamples)
        {
            if(ChData_ptr_1->IsActive)
            {
                global_data_array[0][arrayWriteIndex] = *(ChData_ptr_1->NextBuffer_ptr + smpl);
            }
            if(ChData_ptr_2->IsActive)
            {
                global_data_array[1][arrayWriteIndex] = *(ChData_ptr_2->NextBuffer_ptr + smpl);
            }
            if(ChData_ptr_3->IsActive)
            {
                global_data_array[2][arrayWriteIndex] = *(ChData_ptr_3->NextBuffer_ptr + smpl);
            }
            if(ChData_ptr_4->IsActive)
            {
                global_data_array[3][arrayWriteIndex] = *(ChData_ptr_4->NextBuffer_ptr + smpl);
            }

            // 增加全局数组的写入索引
            arrayWriteIndex++;
         */
          uint16_t smpl;
          for(smpl=0; smpl<MEAS_EDI_DMA_SAMPLES_TOTAL; smpl=smpl+loc_MonSamples)
          {
            /*
            DMA缓冲区的数据最终会被转移到应用程序所维护的特定数据结构中，具体位置体现在 Lab_sChData 结构体的 ChannelHeads_ptr 成员所指向的内存区域。
            当 loc_switchBuffer 函数被调用后，NextBuffer_ptr 成为了当前有效的缓冲区指针，随后在循环中，通过 ChannelHeads_ptr 将 NextBuffer_ptr 指向的数据逐个复制到应用程序的其他数据存储区域。
            */
            if(ChData_ptr_1->IsActive)
            {
              *ChData_ptr_1->ChannelHeads_ptr = *(ChData_ptr_1->NextBuffer_ptr + smpl);
              ChData_ptr_1->ChannelHeads_ptr++;
            }
            if(ChData_ptr_2->IsActive)
            {
              *ChData_ptr_2->ChannelHeads_ptr = *(ChData_ptr_2->NextBuffer_ptr + smpl);
              ChData_ptr_2->ChannelHeads_ptr++;
            }
            if(ChData_ptr_3->IsActive)
            {
              *ChData_ptr_3->ChannelHeads_ptr = *(ChData_ptr_3->NextBuffer_ptr + smpl);
              ChData_ptr_3->ChannelHeads_ptr++;
            }
            if(ChData_ptr_4->IsActive)
            {
              *ChData_ptr_4->ChannelHeads_ptr = *(ChData_ptr_4->NextBuffer_ptr + smpl);
              ChData_ptr_4->ChannelHeads_ptr++;
            }
            
            /* next section tail is reached or Lab-mode ended */
            if( (*loc_AppRtData.Results.LabModeRuntimeData.FillingLevelHead >= (*loc_AppRtData.Results.LabModeRuntimeData.FillingLevelNextSection-1)) || 
               (loc_AppRtData.CurrentState == meas_eMeas_STATE_POST_MEAS) || 
                 (loc_AppRtData.CurrentState == meas_eMeas_STATE_POST_LAB) || 
                   (loc_AppRtData.CurrentState == meas_eMeas_STATE_IDLE) ) 
            {
              DSP_CTRL_IRQ_DISABLE(dsp_IRQ_EDI3_DMA_WRAP);
              
              /* deactivate ISR and DMA */
              if(true == loc_AppRtData.Results.LabModeRuntimeData.IsRunning)
              {
                loc_AppRtData.Results.LabModeRuntimeData.IsFinished = true;
                loc_AppRtData.Results.LabModeRuntimeData.IsRunning = false;
                
                
                /* DMA is not needed anymore */
                /**< Disable and resets the dma channels */
                DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_3,0u);
                DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_2,0u);
                DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_1,0u);
                DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_0,0u);
              }
              
              /* leave the for loop to avoid overriding the next section */
              break;
            }
            
          } /*end for iterate samples*/
        }
        else
        {
        }/* end if dma_buffer_bigger_than_downsampling */
      }/* end if speedmode */
    }/* end if DmaBuffersPendingData check */
  }/* end if initialized check */
}


void lab_StartLabMode(void)
{ 
  DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_3,MEAS_EDI_DMA_SAMPLES_TOTAL);   /**< Set DMA buffer length. Starts the DMA FSM. */
  DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_2,MEAS_EDI_DMA_SAMPLES_TOTAL);   /**< Set DMA buffer length. Starts the DMA FSM. */
  DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_1,MEAS_EDI_DMA_SAMPLES_TOTAL);   /**< Set DMA buffer length. Starts the DMA FSM. */
  DSP_EDI_DMA_CTRL_LENGTH_SET(dsp_eEDI_CH_0,MEAS_EDI_DMA_SAMPLES_TOTAL);   /**< Set DMA buffer length. Starts the DMA FSM. */ 

  DSP_CTRL_IRQ_CLEAR(dsp_IRQ_EDI3_DMA_WRAP);

  /* set lab mode to active */
  loc_AppRtData.Results.LabModeRuntimeData.IsRunning = true;
}

void lab_PdcmCmdHandler_LAB_MODE(Dsi3Drv_uPDCMResponseFrame_t* ansData)/*-?|AP4|wladimir.pauls|c14|?*/
{
  if(NULL != ansData)
  {
    /* set default data */
    ansData->defaultResponseFrame.Data2   = 0;
    ansData->defaultResponseFrame.Data3   = 0;
    ansData->defaultResponseFrame.Data4   = 0;
    ansData->defaultResponseFrame.Data5   = 0;
    ansData->defaultResponseFrame.Data6   = 0;
    ansData->standardResponseFrame.Type = DSI3_TYPE_MEAS_RESULT_LAB_MODE;
    ansData->standardResponseFrame.SubType = DSI3_SUBTYPE_NO_DATA_AVAILABLE;

    /* ensure lab mode is finished */
    if(true == loc_AppRtData.Results.LabModeRuntimeData.IsFinished)
    {
      bool_t diagnostic_finished = loc_AppRtData.Results.DiagnosticMeasurement.ResultsReadout;
      bool_t burst_finished = loc_AppRtData.Results.BurstMonitoring.ResultsReadout;
      bool_t ringing_finished = loc_AppRtData.Results.RingingBehaviour.ResultsReadout;

      /* Process AppLabmode
       * In AppLabmode the Appmode data is sent before the Labmode data
       *
       * Execution conditions are OR-ed:
       * - Applab mode is active
       * - Diagnostic Frame is not sent
       * - BurstMonitor Frame is not sent AND not indirect Mode
       * - RingingBehaviour Frame is not sent AND not indirect Mode
       * - standard measurement AND still data available
       * - advanced measurement AND still data available
       */
      if(meas_eMeasMode_APPLAB == loc_AppRtData.RuntimeData.MeasurementMode)
      {
        app_PdcmCmdHandler_APP_MODE(ansData);

        if( (DSI3_SUBTYPE_NO_DATA_AVAILABLE == ansData->standardResponseFrame.SubType) &&
            (true == diagnostic_finished) &&
            (((true == burst_finished) && (true == ringing_finished)) || (meas_eMeasConf_INDIRECT == loc_AppRtData.RuntimeData.MeasurementConf)))
        {
          loc_AppRtData.RuntimeData.MeasurementMode = meas_eMeasMode_LAB;
        }
      }
      else if(true == loc_AppRtData.Results.LabModeRuntimeData.IsInitialised)  /* make sure the lab mode init has been called */
      {
        /* Process Labmode */
        bool_t Ch4_data_available = false;
        bool_t Ch3_data_available = false;
        bool_t Ch2_data_available = false;
        bool_t Ch1_data_available = false;

        /* Check in which channel data is available*/
        if(true == loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].IsActive)
        {
          if((loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].ChannelNextReadOut_ptr < loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].ChannelHeads_ptr) &&
              (loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].ChannelTails_ptr != loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch4].ChannelHeads_ptr))
          {
            Ch4_data_available = true;
          }
        }
        if(true == loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].IsActive)
        {
          if((loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].ChannelNextReadOut_ptr < loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].ChannelHeads_ptr) &&
              (loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].ChannelTails_ptr != loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch3].ChannelHeads_ptr))
          {
            Ch3_data_available = true;
          }
        }
        if(true == loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].IsActive)
        {
          if((loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].ChannelNextReadOut_ptr < loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].ChannelHeads_ptr) &&
              (loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].ChannelTails_ptr != loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch2].ChannelHeads_ptr))
          {
            Ch2_data_available = true;
          }
        }
        if(true == loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].IsActive)
        {
          if((loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].ChannelNextReadOut_ptr < loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].ChannelHeads_ptr) &&
              (loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].ChannelTails_ptr != loc_AppRtData.Results.LabModeRuntimeData.ChData[Ch1].ChannelHeads_ptr))
          {
            Ch1_data_available = true;
          }
        }

        /* If data for both frames are available send frame 1 and 2 alternately. Otherwise the appropriate channel will be send */
        if((Ch4_data_available || Ch3_data_available) && (Ch2_data_available || Ch1_data_available))
        {
          if(loc_AppRtData.Results.LabModeRuntimeData.LastSentFrameType == DSI3_SUBTYPE_FRAME_1)
          {
            loc_PrepLabFrame(ansData, DSI3_SUBTYPE_FRAME_2);
          }
          else
          {
            loc_PrepLabFrame(ansData, DSI3_SUBTYPE_FRAME_1);
          }
        }
        /* data for frame type 1 is available */
        else if((Ch4_data_available || Ch3_data_available))
        {
          loc_PrepLabFrame(ansData, DSI3_SUBTYPE_FRAME_1);
        }
        /* data for frame type 2 is available */
        else if((Ch2_data_available || Ch1_data_available))
        {
          loc_PrepLabFrame(ansData, DSI3_SUBTYPE_FRAME_2);
        }
        else
        {
          /* no data available */
          ansData->defaultResponseFrame.Data2   = 0;
          ansData->defaultResponseFrame.Data3   = 0;
          ansData->defaultResponseFrame.Data4   = 0;
          ansData->defaultResponseFrame.Data5   = 0;
          ansData->defaultResponseFrame.Data6   = 0;
          ansData->standardResponseFrame.Type = DSI3_TYPE_MEAS_RESULT_LAB_MODE;

          loc_AppRtData.Results.LabModeRuntimeData.IsFinished = false;
          loc_AppRtData.Results.LabModeRuntimeData.IsRunning  = false;
          loc_AppRtData.Results.LabModeRuntimeData.IsInitialised = false;
        }
      }
    }
    else
    {
      /* lab mode is not finished */
    }
  }
  else
  {
    /* called before init was executed correctly -> goto error handler */
    err_ErrorHandler(ERR_MODLIST_DSI3);
  }
}


