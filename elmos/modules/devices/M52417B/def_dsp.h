/* ------------------------------------------------------------------- */
/** @file def_dsp.h
 *
 * @brief Helper definitions for DSP hardware module.
 *
 * Purpose:
 * Provide register access and register value definitions 
 * for DSP hardware module
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
 * @section history_sec Revision History
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who Ver  Comment
 * -------------------------------------------------------------------
 * 18/03/23 (F) poe 1001 first creation
 * -------------------------------------------------------------------
 * @endverbatim
 *
 * @creator      poe
 * @created      2018/03/23
 *
 * @project      524.17
 * @requested    ELMOS
 * @inspector    -
 * @verification -
 * @version      $Revision: 383 $
 *
 *
 * $State: Exp $
 * $Author: siko $
 *
 * Additional markers:
 *
 */
#ifndef _DEF_DSP_H_
#define _DEF_DSP_H_
//################################################################################
//  Helper defines
//################################################################################
/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include <io_m52417b.h>
/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/
enum dsp_eRTMStatus
{
  dsp_eRTM_ONGOING      = 0u,
  dsp_eRTM_FINISHED     = 1u
};

typedef enum dsp_eRTMStatus dsp_RTMStatus_t;

struct dsp_sEevalDmaCtrl
{
  __IO uint16_t  length     :  8;               
  __IO uint16_t  wrap_off   :  1;               
};  

typedef struct dsp_sEevalDmaCtrl dsp_EevalDmaCtrl_t;

struct dsp_sEdiDmaCtrl
{
  __IO uint16_t  length     :  8;               
  __IO uint16_t  wrap_off   :  1;               
} ;      

typedef struct dsp_sEdiDmaCtrl dsp_EdiDmaCtrl_t;


enum dsp_eEDI_CH
{
  dsp_eEDI_CH_0                 = 0u,
  dsp_eEDI_CH_1                 = 1u,
  dsp_eEDI_CH_2                 = 2u,
  dsp_eEDI_CH_3                 = 3u
};

typedef enum dsp_eEDI_CH dsp_EDI_CH_t;

enum dsp_eEDISEL_CH0
{
  dsp_eEDISEL_CH0_AMPD_ENV      = 0u,
  dsp_eEDISEL_CH0_ENVP_ENV_RAW  = 1u,
  dsp_eEDISEL_CH0_FILT1         = 2u,
  dsp_eEDISEL_CH0_AATG2_TH      = 3u
};

typedef enum dsp_eEDISEL_CH0 dsp_EDISEL_CH0_t;

enum dsp_eEDISEL_CH1
{
  dsp_eEDISEL_CH1_AMPD_ENV      = 0u,
  dsp_eEDISEL_CH1_ENVD_RAW      = 1u,
  dsp_eEDISEL_CH1_ENVD_PHI      = 2u,
  dsp_eEDISEL_CH1_CONF1         = 3u
};

typedef enum dsp_eEDISEL_CH1 dsp_EDISEL_CH1_t;

enum dsp_eEDISEL_CH2
{
  dsp_eEDISEL_CH2_ENV_I         = 0u,
  dsp_eEDISEL_CH2_ENVD_PHID     = 1u,
  dsp_eEDISEL_CH2_FILT2         = 2u,
  dsp_eEDISEL_CH2_AATG_TH       = 3u
};

typedef enum dsp_eEDISEL_CH2 dsp_EDISEL_CH2_t;

enum dsp_eEDISEL_CH3
{
  dsp_eEDISEL_CH3_ENV_Q         = 0u,
  dsp_eEDISEL_CH3_ATG_TH        = 1u,
  dsp_eEDISEL_CH3_STG_TH        = 2u,
  dsp_eEDISEL_CH3_CONF2         = 3u
};

typedef enum dsp_eEDISEL_CH3 dsp_EDISEL_CH3_t;

enum dsp_eEEVAL_PacketFormat
{
  dsp_eEEVAL_32BIT              = 0u,
  dsp_eEEVAL_26BIT              = 1u
};

typedef enum dsp_eEEVAL_PacketFormat dsp_EEVAL_PacketFormat_t;


struct dsp_sEEVAL_Packet_32Bit
{
  uint16_t Timestamp            : 16;
  uint16_t ENVP_ENV_RAW         : 14;
  uint8_t  TypeIdentifier       :  2;
} ;

typedef struct dsp_sEEVAL_Packet_32Bit dsp_EEVAL_Packet_32Bit_t;


struct dsp_sEEVAL_Packet_26Bit
{
  uint16_t Timestamp            : 15;
  uint16_t ENVP_ENV_RAW         :  8;
  uint8_t  TypeIdentifier       :  2;
} ;

typedef struct dsp_sEEVAL_Packet_26Bit dsp_EEVAL_Packet_26Bit_t;


enum dsp_eFTC_ConfigSet
{
  dsp_eFTC_FastFiltering0       = 0u,
  dsp_eFTC_FastFiltering1       = 1u,
  dsp_eFTC_FastFiltering2       = 2u,
  dsp_eFTC_ForNPulses_4         = 3u,
  dsp_eFTC_ForNPulses_8         = 4u,
  dsp_eFTC_ForNPulses_12_20     = 5u,
  dsp_eFTC_ForNPulses_24_32     = 6u
};

typedef enum dsp_eFTC_ConfigSet dsp_FTC_ConfigSet_t;


enum dsp_eNFDIRQ_Echos
{
  dsp_eNFDIRQ_2_ECHOS           = 0u,
  dsp_eNFDIRQ_3_ECHOS           = 1u,
  dsp_eNFDIRQ_4_ECHOS           = 2u,
  dsp_eNFDIRQ_5_ECHOS           = 3u
};

typedef enum dsp_eNFDIRQ_Echos dsp_NFDIRQ_Echos_t;


/* *************************************************************************** */
/* *************************** DEFINES AND MACROS **************************** */
/* *************************************************************************** */


#define DSP_ON          (1u)
#define DSP_OFF         (0u)

/* *************************************************************************** */
/* ****************************** DSP CONTROL ******************************** */
/* *************************************************************************** */

#define DSP_CTRL_SIGNAL_PATH_GET()                              (DSP_DSP_CTRL_bit.dsp_on_state)

#define DSP_CTRL_DSP_PWR_DOWN_ENABLE()                          (DSP_DSP_CTRL_bit.dsp_pwr_dwn                   = DSP_ON)
#define DSP_CTRL_DSP_PWR_DOWN_DISABLE()                         (DSP_DSP_CTRL_bit.dsp_pwr_dwn                   = DSP_OFF)

#define DSP_CTRL_DSP_ON()                                       (DSP_DSP_CTRL_bit.dsp_on                        = DSP_ON)
#define DSP_CTRL_DSP_OFF()                                      (DSP_DSP_CTRL_bit.dsp_on                        = DSP_OFF)



/* *************************************************************************** */
/* ****************************** RFM CONTROL ******************************** */
/* *************************************************************************** */


#define DSP_RFM_CTRL_STATUS()                                   (DSP_RFM_CTRL_bit.rfm_status)

#define DSP_RFM_CTRL_WINDOW_WIDTH_SET(num)                      (DSP_RFM_CTRL_bit.rfm_width                     = (num))
#define DSP_RFM_CTRL_WINDOW_WIDTH_GET()                         (DSP_RFM_CTRL_bit.rfm_width)

#define DSP_RFM_CTRL_WINDOW_START_SET(num)                      (DSP_RFM_CTRL_bit.rfm_start                     = (num))
#define DSP_RFM_CTRL_WINDOW_START_GET(num)                      (DSP_RFM_CTRL_bit.rfm_start)

#define DSP_RFM_CTRL_CROSS_COUNT()                              (DSP_RFM_CROSS_COUNT)
#define DSP_RFM_CTRL_COUNTS()                                   (DSP_RFM_COUNTS)
#define DSP_RFM_CTRL_SAMPLES()                                  (DSP_RFM_SAMPLES)



/* *************************************************************************** */
/* ****************************** RTM/MT CONTROL ***************************** */
/* *************************************************************************** */


#define DSP_RTM_STATUS()                                        ((dsp_RTMStatus_t)DSP_RTM_bit.rtm_rt_end)
#define DSP_RTM_RT()                                            (DSP_RTM_bit.rtm_rt)

#define DSP_MT_TIME()                                           (DSP_MT)



/* *************************************************************************** */
/* **************************** ENVELOPE CONTROL ***************************** */
/* *************************************************************************** */

#define DSP_ENVP_CFG_ASPI_SEL_RAW()                             (DSP_ENVP_CFG_bit.aspi_sel                      = DSP_OFF)
#define DSP_ENVP_CFG_ASPI_SEL_FILTERED()                        (DSP_ENVP_CFG_bit.aspi_sel                      = DSP_ON)
#define DSP_ENVP_CFG_FSPI_SEL_RAW()                             (DSP_ENVP_CFG_bit.fspi_sel                      = DSP_OFF)
#define DSP_ENVP_CFG_FSPI_SEL_FILTERED()                        (DSP_ENVP_CFG_bit.fspi_sel                      = DSP_ON)
#define DSP_ENVP_CFG_FSPI_SEL_RAW()                             (DSP_ENVP_CFG_bit.fspi_sel                      = DSP_OFF)
#define DSP_ENVP_CFG_DSR_SEL_FC_HALF()                          (DSP_ENVP_CFG_bit.dsr_sel                       = DSP_ON)
#define DSP_ENVP_CFG_DSR_SEL_FC()                               (DSP_ENVP_CFG_bit.dsr_sel                       = DSP_OFF)

#define DSP_ENVP_CFG_GCAL(num)                                  (DSP_ENVP_CFG_bit.g_cal                         = (num))

#define DSP_ENVP_CFG_AFC_ENABLE()                               (DSP_ENVP_CFG_bit.envp_afc                      = DSP_ON)
#define DSP_ENVP_CFG_AFC_DISABLE()                              (DSP_ENVP_CFG_bit.envp_afc                      = DSP_OFF)
#define DSP_ENVP_CFG_SET(num)                                   (DSP_ENVP_CFG_bit.envp_cfg                      = (num))
#define DSP_ENVP_CFG_GET                                        (DSP_ENVP_CFG_bit.envp_cfg)

#define DSP_ENVP_CTRL_RESTART()                                 (DSP_ENVP_CTRL_bit.envp_restart                 = DSP_ON)
#define DSP_ENVP_CTRL_FORCE_AFC_ENABLED()                       (DSP_ENVP_CTRL_bit.envp_afc_brk                 = DSP_ON)
#define DSP_ENVP_CTRL_FORCE_AFC_DISABLED()                      (DSP_ENVP_CTRL_bit.envp_afc_brk                 = DSP_OFF)

#define DSP_ENVP_ENV_RAW_GET()                                  (DSP_ENVP_ENV_RAW)

#define DSP_ENVP_FILT_CFG_F2_USE_ENV_COEFF_REG()                (DSP_ENVP_FILT_CFG_bit.f2_coeff_sel             = DSP_OFF)
#define DSP_ENVP_FILT_CFG_F2_USE_FIXFREQ()                      (DSP_ENVP_FILT_CFG_bit.f2_coeff_sel             = DSP_ON)
#define DSP_ENVP_FILT_CFG_F2_GET()                              (DSP_ENVP_FILT_CFG_bit.f2_coeff_sel)

#define DSP_ENVP_FILT_CFG_F1_USE_ENV_COEFF_REG()                (DSP_ENVP_FILT_CFG_bit.f1_coeff_sel             = DSP_OFF)
#define DSP_ENVP_FILT_CFG_F1_USE_FIXFREQ()                      (DSP_ENVP_FILT_CFG_bit.f1_coeff_sel             = DSP_ON)
#define DSP_ENVP_FILT_CFG_F1_GET()                              (DSP_ENVP_FILT_CFG_bit.f1_coeff_sel)

#define DSP_ENVP_FILT_CFG_LEN_CODE_SET(num)                     (DSP_ENVP_FILT_CFG_bit.filt_len_code            = (num))
#define DSP_ENVP_FILT_CFG_LEN_CODE_GET()                        (DSP_ENVP_FILT_CFG_bit.filt_len_code)

#define DSP_ENVP_FILT_CFG_LEN_FIX_SET(num)                      (DSP_ENVP_FILT_CFG_bit.filt_len_fix             = (num))
#define DSP_ENVP_FILT_CFG_LEN_FIX_GET()                         (DSP_ENVP_FILT_CFG_bit.filt_len_fix)


/* *************************************************************************** */
/* ****************************** FTC CONTROL ******************************** */
/* *************************************************************************** */

#define DSP_FTC_CTRL_ENABLE()                                   (DSP_FTC_CTRL_bit.ftc_en                        = DSP_ON)
#define DSP_FTC_CTRL_DISABLE()                                  (DSP_FTC_CTRL_bit.ftc_en                        = DSP_OFF)

#define DSP_FTC_CFG_FOR_NPULSES_4()                             (DSP_FTC_CTRL_bit.ftc_cfg                       = dsp_eFTC_ForNPulses_4)
#define DSP_FTC_CFG_FOR_NPULSES_8()                             (DSP_FTC_CTRL_bit.ftc_cfg                       = dsp_eFTC_ForNPulses_8)
#define DSP_FTC_CFG_FOR_NPULSES_12_20()                         (DSP_FTC_CTRL_bit.ftc_cfg                       = dsp_eFTC_ForNPulses_12_20)
#define DSP_FTC_CFG_FOR_NPULSES_24_32()                         (DSP_FTC_CTRL_bit.ftc_cfg                       = dsp_eFTC_ForNPulses_24_32)

#define DSP_FTC_ENV()                                           (DSP_ENV_FTC)



/* *************************************************************************** */
/* ********************* DIGITAL AMPLIFIER CONTROL *************************** */
/* *************************************************************************** */


#define DSP_AMPD_CTRL_GAIN_CONFIG_SET(num)                      (DSP_AMPD_CTRL_bit.ampd_g_dig                   = (num))
#define DSP_AMPD_CTRL_GAIN_CONFIG_GET()                         (DSP_AMPD_CTRL_bit.ampd_g_dig)

#define DSP_AMPD_ENV_VALUE()                                    (DSP_AMPD_ENV_bit.ampd_env)



/* *************************************************************************** */
/* ***************************** STC CONTROL ********************************* */
/* *************************************************************************** */

#define DSP_STC_CTRL_AUTOINCR_LOG()                             (DSP_STC_CTRL_bit.ampd_stc_mod                  = DSP_ON)
#define DSP_STC_CTRL_AUTOINCR_LIN()                             (DSP_STC_CTRL_bit.ampd_stc_mod                  = DSP_OFF)

#define DSP_STC_CTRL_TARGETVAL_SET(num)                         (DSP_STC_CTRL_bit.ampd_g_dig_target             = (num))
#define DSP_STC_CTRL_TARGETVAL_GET()                            (DSP_STC_CTRL_bit.ampd_g_dig_target)

#define DSP_STC_CTRL_STC_TB_SET(num)                            (DSP_STC_TB_bit.ampd_stc_tb                     = (num))
#define DSP_STC_CTRL_STC_TB_GET()                               (DSP_STC_TB_bit.ampd_stc_tb)

/* *************************************************************************** */
/* ********************* STATIC THRESHOLD GENERATION ************************* */
/* *************************************************************************** */

#define DSP_STG_TH_SET(num)                                     (DSP_STG_TH_bit.stg_th                          = (num))
#define DSP_STG_TH_GET()                                        (DSP_STG_TH_bit.stg_th)

#define DSP_STG_TB_SET(num)                                     (DSP_STG_TB_bit.stg_tb                          = (num))
#define DSP_STG_TB_GET()                                        (DSP_STG_TB_bit.stg_tb)

#define DSP_STG_STEP_SET(num)                                   (DSP_STG_STEP_bit.stg_step                      = (num))
#define DSP_STG_STEP_GET()                                      (DSP_STG_STEP_bit.stg_step)


/* *************************************************************************** */
/* ************************** ANALOG GAIN CONTROL **************************** */
/* *************************************************************************** */


#define DSP_ASP_CTRL_GAIN_ENABLE()                              (DSP_ASP_CTRL_bit.g_ana_diag                    = DSP_ON)
#define DSP_ASP_CTRL_GAIN_DISABLE()                             (DSP_ASP_CTRL_bit.g_ana_diag                    = DSP_OFF)

#define DSP_ASP_CTRL_LOWPASS_FILTER_HIGH()                      (DSP_ASP_CTRL_bit.fc_x2                         = DSP_ON)
#define DSP_ASP_CTRL_LOWPASS_FILTER_NORMAL()                    (DSP_ASP_CTRL_bit.fc_x2                         = DSP_OFF)

#define DSP_ASP_CTRL_GAIN_SET(num)                              (DSP_ASP_CTRL_bit.g_ana                         = (num))
#define DSP_ASP_CTRL_GAIN_GET()                                 (DSP_ASP_CTRL_bit.g_ana)


/* *************************************************************************** */
/* ************************ ECHO EVALUATION CONTROL ************************** */
/* *************************************************************************** */

#define DSP_EEVAL_CTRL_PACKET_FORMAT_SET_32BIT()                (DSP_EEVAL_CTRL_bit.eeval_dma_val  = dsp_eEEVAL_32BIT)
#define DSP_EEVAL_CTRL_PACKET_FORMAT_SET_26BIT()                (DSP_EEVAL_CTRL_bit.eeval_dma_val  = dsp_eEEVAL_26BIT)
#define DSP_EEVAL_CTRL_PACKET_FORMAT_GET()                      ((dsp_EEVAL_PacketFormat_t)DSP_EEVAL_CTRL_bit.eeval_dma_val)

#define DSP_EEVAL_CTRL_SENSITIVITY_SET(num)                     (DSP_EEVAL_CTRL_bit.eeval_sens                  = (uint8_t)(num))
#define DSP_EEVAL_CTRL_SENSITIVITY_GET()                        ((uint8_t)DSP_EEVAL_CTRL_bit.eeval_sens)

#define DSP_EEVAL_CTRL_SOURCE_SELECT_TLH()                      (DSP_EEVAL_CTRL_bit.eeval_sel                  |=  DSP_ON)
#define DSP_EEVAL_CTRL_SOURCE_SELECT_THL()                      (DSP_EEVAL_CTRL_bit.eeval_sel                  |= (DSP_ON << 1u))
#define DSP_EEVAL_CTRL_SOURCE_SELECT_MAX()                      (DSP_EEVAL_CTRL_bit.eeval_sel                  |= (DSP_ON << 2u))
#define DSP_EEVAL_CTRL_SOURCE_SELECT_MIN()                      (DSP_EEVAL_CTRL_bit.eeval_sel                  |= (DSP_ON << 3u))
#define DSP_EEVAL_CTRL_SOURCE_SELECT_ALL()                      (DSP_EEVAL_CTRL_bit.eeval_sel                   = 0x0Fu)
#define DSP_EEVAL_CTRL_SOURCE_SELECT_NONE()                     (DSP_EEVAL_CTRL_bit.eeval_sel                   = 0u)
#define DSP_EEVAL_CTRL_SOURCE_SELECT_SET(num)                   (DSP_EEVAL_CTRL_bit.eeval_sel                   = (num))
#define DSP_EEVAL_CTRL_SOURCE_SELECT_GET()                      (DSP_EEVAL_CTRL_bit.eeval_sel)
#define DSP_EEVAL_CTRL_SOURCE_SEL_BITMASK_TLH                   (1u)
#define DSP_EEVAL_CTRL_SOURCE_SEL_BITMASK_THL                   (2u)
#define DSP_EEVAL_CTRL_SOURCE_SEL_BITMASK_MAX                   (4u)
#define DSP_EEVAL_CTRL_SOURCE_SEL_BITMASK_MIN                   (8u)

#define DSP_EEVAL_CTRL_DMA_WRAP_OFF                             (DSP_EEVAL_DMA_CTRL_bit.wrap_off                = DSP_ON)
#define DSP_EEVAL_CTRL_DMA_WRAP_ON                              (DSP_EEVAL_DMA_CTRL_bit.wrap_off                = DSP_OFF)
#define DSP_EEVAL_CTRL_DMA_NEXT_ADDR()                          (DSP_EEVAL_DMA_NEXT_ADDR)
#define DSP_EEVAL_CTRL_DMA_NEXT_WORD()                          (DSP_EEVAL_DMA_NEXT_WORD)
#define DSP_EEVAL_CTRL_DMA_BUFFER_LENGTH_SET(num)               (DSP_EEVAL_DMA_CTRL_bit.length                  = (uint8_t)(num))
#define DSP_EEVAL_CTRL_DMA_BUFFER_LENGTH_GET()                  (DSP_EEVAL_DMA_CTRL_bit.length)
#define DSP_EEVAL_CTRL_DMA_ADDR_SET(num)                        (DSP_EEVAL_DMA_ADDR                             = (uint16_t)(num))
#define DSP_EEVAL_CTRL_DMA_ADDR_GET()                           (DSP_EEVAL_DMA_ADDR)

#define DSP_EEVAL1_CTRL_DMA_WRAP_OFF                            (DSP_EEVAL1_DMA_CTRL_bit.wrap_off               = DSP_ON)
#define DSP_EEVAL1_CTRL_DMA_WRAP_ON                             (DSP_EEVAL1_DMA_CTRL_bit.wrap_off               = DSP_OFF)
#define DSP_EEVAL1_CTRL_DMA_ADDR_SET(num)                       (DSP_EEVAL1_DMA_ADDR                            = (uint16_t)(num))
#define DSP_EEVAL1_CTRL_DMA_ADDR_GET()                          (DSP_EEVAL1_DMA_ADDR)
#define DSP_EEVAL1_CTRL_DMA_BUFFER_LENGTH_SET(num)              (DSP_EEVAL1_DMA_CTRL_bit.length                 = (uint8_t)(num))
#define DSP_EEVAL1_CTRL_DMA_BUFFER_LENGTH_GET()                 (DSP_EEVAL1_DMA_CTRL_bit.length)

#define DSP_EEVAL2_CTRL_DMA_WRAP_OFF                            (DSP_EEVAL2_DMA_CTRL_bit.wrap_off               = DSP_ON)
#define DSP_EEVAL2_CTRL_DMA_WRAP_ON                             (DSP_EEVAL2_DMA_CTRL_bit.wrap_off               = DSP_OFF)
#define DSP_EEVAL2_CTRL_DMA_ADDR_SET(num)                       (DSP_EEVAL2_DMA_ADDR                            = (uint16_t)(num))
#define DSP_EEVAL2_CTRL_DMA_ADDR_GET()                          (DSP_EEVAL2_DMA_ADDR)
#define DSP_EEVAL2_CTRL_DMA_BUFFER_LENGTH_SET(num)              (DSP_EEVAL2_DMA_CTRL_bit.length                 = (uint8_t)(num))
#define DSP_EEVAL2_CTRL_DMA_BUFFER_LENGTH_GET()                 (DSP_EEVAL2_DMA_CTRL_bit.length)

/* *************************************************************************** */
/* ************************** ENVELOPE DATA INTERFACE ************************ */
/* *************************************************************************** */


#define DSP_EDI_DMA_CH_SEL(ch, cfg)                              (DSP_EDI_DMA_CHANNEL_SEL               = (DSP_EDI_DMA_CHANNEL_SEL & ((0xFF<<(2<<(ch))) | (2<<(2*(ch)-((ch) > 0 ? 1 : 0 )))-((ch) > 0 ? 1 : 2))) | (cfg)<<(2*(ch)))
#define DSP_EDI_DMA_CH0_SEL(cfg)                                 (DSP_EDI_DMA_CHANNEL_SEL_bit.ch0_sel   = (dsp_EDISEL_CH0_t)(cfg))
#define DSP_EDI_DMA_CH1_SEL(cfg)                                 (DSP_EDI_DMA_CHANNEL_SEL_bit.ch1_sel   = (dsp_EDISEL_CH1_t)(cfg))
#define DSP_EDI_DMA_CH2_SEL(cfg)                                 (DSP_EDI_DMA_CHANNEL_SEL_bit.ch2_sel   = (dsp_EDISEL_CH2_t)(cfg))
#define DSP_EDI_DMA_CH3_SEL(cfg)                                 (DSP_EDI_DMA_CHANNEL_SEL_bit.ch3_sel   = (dsp_EDISEL_CH3_t)(cfg))


#define DSP_EDI_DMA_CTRL(ch, cfg)                                (*(&DSP_EDI0_DMA_CTRL + (dsp_eEDI_CH_t)(ch))                                           = (uint16_t)(cfg))
#define DSP_EDI_DMA_CTRL_WRAP_OFF_SET(ch, on)                    ((*(volatile dsp_EdiDmaCtrl_t*)(&DSP_EDI0_DMA_CTRL + (dsp_EDI_CH_t)(ch))).wrap_off        = (bool_t)(on))
#define DSP_EDI_DMA_CTRL_WRAP_OFF_GET(ch)                        ((*(volatile dsp_EdiDmaCtrl_t*)(&DSP_EDI0_DMA_CTRL + (dsp_EDI_CH_t)(ch))).wrap_off)
#define DSP_EDI_DMA_CTRL_LENGTH_SET(ch, len)                     ((*(volatile dsp_EdiDmaCtrl_t*)(&DSP_EDI0_DMA_CTRL + (dsp_EDI_CH_t)(ch))).length          = (uint8_t)(len))
#define DSP_EDI_DMA_CTRL_LENGTH_GET(ch)                          ((*(volatile dsp_EdiDmaCtrl_t*)(&DSP_EDI0_DMA_CTRL + (dsp_EDI_CH_t)(ch))).length)

#define DSP_EDI_DMA_ADDR(ch, addr)                               (*(&DSP_EDI0_DMA_ADDR      + (dsp_EDI_CH_t)(ch))                                       = (uint16_t)(addr))
#define DSP_EDI_DMA_NEXT_ADDR(ch)                                (*(&DSP_EDI0_DMA_NEXT_ADDR + (dsp_EDI_CH_t)(ch)))
#define DSP_EDI_DMA_NEXT_WORD(ch)                                (*(&DSP_EDI0_DMA_NEXT_WORD + (dsp_EDI_CH_t)(ch)))


/* *************************************************************************** */
/* ********************** NEAR FIELD DETECTION CONTROL *********************** */
/* *************************************************************************** */

#define DSP_NFD_CTRL_MAX_NUMS()                                 (DSP_NFD_CTRL_bit.nfd_max_num)
#define DSP_NFD_CTRL_IRQ_SET(num)                               (DSP_NFD_CTRL_bit.nfd_irq_cfg                   = (dsp_NFDIRQ_Echos_t)(num))
#define DSP_NFD_CTRL_IRQ_E2()                                   (DSP_NFD_CTRL_bit.nfd_irq_cfg                   = dsp_eNFDIRQ_2_ECHOS)
#define DSP_NFD_CTRL_IRQ_E3()                                   (DSP_NFD_CTRL_bit.nfd_irq_cfg                   = dsp_eNFDIRQ_3_ECHOS)
#define DSP_NFD_CTRL_IRQ_E4()                                   (DSP_NFD_CTRL_bit.nfd_irq_cfg                   = dsp_eNFDIRQ_4_ECHOS)
#define DSP_NFD_CTRL_IRQ_E5()                                   (DSP_NFD_CTRL_bit.nfd_irq_cfg                   = dsp_eNFDIRQ_5_ECHOS)
#define DSP_NFD_CTRL_IRQ_GET()                                  ((dsp_NFDIRQ_Echos_t)DSP_NFD_CTRL_bit.nfd_irq_cfg)

#define DSP_NFD_CTRL_EVALSENS_SET(num)                          (DSP_NFD_CTRL_bit.nfd_sens                      = (num))
#define DSP_NFD_CTRL_EVALSENS_GET()                             (DSP_NFD_CTRL_bit.nfd_sens)

#define DSP_NFD_TH_SET(num)                                     (DSP_NFD_TH                                     = (num))
#define DSP_NFD_TH_GET()                                        (DSP_NFD_TH)

#define DSP_NFD_ECHO1_GET()                                     (DSP_NFD_ECHO1)
#define DSP_NFD_TS1_GET()                                       (DSP_NFD_TS1)

#define DSP_NFD_ECHO2_GET()                                     (DSP_NFD_ECHO2)
#define DSP_NFD_TS2_GET()                                       (DSP_NFD_TS2)

#define DSP_NFD_ECHO3_GET()                                     (DSP_NFD_ECHO3)
#define DSP_NFD_TS3_GET()                                       (DSP_NFD_TS3)

#define DSP_NFD_ECHO4_GET()                                     (DSP_NFD_ECHO4)
#define DSP_NFD_TS4_GET()                                       (DSP_NFD_TS4)

#define DSP_NFD_ECHO5_GET()                                     (DSP_NFD_ECHO5)
#define DSP_NFD_TS5_GET()                                       (DSP_NFD_TS5)


/* *************************************************************************** */
/* **************************** DSP Interrupts ******************************* */
/* *************************************************************************** */

#define DSP_IRQ_SET(num)

#define DSP_CTRL_IRQ_ENABLE(irq_n)                             (DSP_IRQ_MASK                                   |=  (1u << (dsp_eInterruptVectorNum_t)(irq_n)))
#define DSP_CTRL_IRQ_DISABLE(irq_n)                            (DSP_IRQ_MASK                                   &= ~(1u << (dsp_eInterruptVectorNum_t)(irq_n)))
#define DSP_CTRL_IRQ_GET(irq_n)                                (DSP_STATUS & ((dsi3_eInterruptVectorNum_t)(1 << (irq_n))))
#define DSP_CTRL_IRQ_CLEAR(irq_n)                              (DSP_IRQ_VNO                                     = (dsp_eInterruptVectorNum_t)(irq_n))
#define DSP_CTRL_IRQ_CLEAR_ALL()                               (DSP_STATUS                                      = 0xFFFFu)



#endif
