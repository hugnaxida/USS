/* ------------------------------------------------------------------- */
/** @file def_ada.h
 *
 * @brief Helper definitions for ADA hardware module.
 *
 * Purpose:
 * Provide register access and register value definitions 
 * for ADA hardware module
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
 * 17/05/23 (F) poe 1001 first creation
 * -------------------------------------------------------------------
 * @endverbatim
 *
 * @creator      poe
 * @created      2017/05/23
 *
 * @project      524.17
 * @requested    ELMOS
 * @inspector    -
 * @verification -
 * @version      $Revision: 392 $
 *
 *
 * $State: Exp $
 * $Author: siko $
 *
 * Additional markers:
 *
 */
#ifndef _DEF_ADA_H_
#define _DEF_ADA_H_
//################################################################################
//  Helper defines
//################################################################################
/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include <io_m52417a.h>
/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

enum ada_eClockDiv
{
  ada_eClockDiv_f_1      = 0u,
  ada_eClockDiv_f_2      = 1u,
  ada_eClockDiv_f_4      = 2u,
  ada_eClockDiv_f_8      = 3u
};

typedef enum ada_eClockDiv ada_ClockDiv_t;

enum ada_eSamplingPeriod
{
  ada_eSamplingPeriod_32 = 0u,
  ada_eSamplingPeriod_16 = 1u,
  ada_eSamplingPeriod_08 = 2u,
  ada_eSamplingPeriod_04 = 3u
};

typedef enum ada_eSamplingPeriod ada_SamplingPeriod_t;

enum ada_eChannelSelect
{       
  ada_eChannel_GPI          = 0u,
  ada_eChannel_SUP          = 1u,
  ada_eChannel_ASP          = 2u,
  ada_eChannel_TDR_OTP_DSI  = 3u
} ;

typedef enum ada_eChannelSelect ada_ChannelSelect_t;

enum ada_eSignalSelect_GPI
{       
  ada_eSignal_GPI_GND            = 0u,
  ada_eSignal_GPI_GPIO0          = 1u,
  ada_eSignal_GPI_GPIO1          = 2u,
  ada_eSignal_GPI_GPIO2          = 3u,
  ada_eSignal_GPI_GPIO3          = 4u,
  ada_eSignal_GPI_DAC0           = 5u,
  ada_eSignal_GPI_DAC1           = 6u,
  ada_eSignal_GPI_RESERVED       = 7u
};

typedef enum ada_eSignalSelect_GPI ada_SignalSelect_GPI_t;

enum ada_eSignalSelect_SUP
{       
  ada_eSignal_SUP_GND            = 0u,
  ada_eSignal_SUP_VSUP_DIV8      = 1u,
  ada_eSignal_SUP_VTANK_DIV8     = 2u,
  ada_eSignal_SUP_VGB            = 3u,
  ada_eSignal_SUP_VDDD           = 4u,
  ada_eSignal_SUP_V_TSENSE       = 5u,
  ada_eSignal_SUP_IB             = 6u,
  ada_eSignal_SUP_IC             = 7u
};

typedef enum ada_eSignalSelect_SUP ada_SignalSelect_SUP_t;
  
enum ada_eSignalSelect_ASP
{       
  ada_eSignal_ASP_GND            = 0u,
  ada_eSignal_ASP_AMP_LP         = 1u,
  ada_eSignal_ASP_AMP            = 2u,
  ada_eSignal_ASP_AMP0           = 3u,
  ada_eSignal_ASP_COMP_REF       = 4u,
  ada_eSignal_ASP_VMID           = 5u,
  ada_eSignal_ASP_IB_AMP         = 6u,
  ada_eSignal_ASP_RESERVED       = 7u
};  
  
typedef enum ada_eSignalSelect_ASP ada_SignalSelect_ASP_t;
 
enum ada_eSignalSelect_TOD
{       
  ada_eSignal_TOD_GND            = 0u,
  ada_eSignal_TOD_TDR_ICONST     = 1u,
  ada_eSignal_OTP_VRR            = 2u,
  ada_eSignal_DSI_IN             = 3u,
  ada_eSignal_RESERVED1          = 4u,
  ada_eSignal_RESERVED2          = 5u,
  ada_eSignal_RESERVED3          = 6u,
  ada_eSignal_RESERVED4          = 7u
};
 
typedef enum ada_eSignalSelect_TOD ada_SignalSelect_TOD_t;

enum ada_eSignalSelect
{       
  ada_eSignal_0                  = 0u,
  ada_eSignal_1                  = 1u,
  ada_eSignal_2                  = 2u,
  ada_eSignal_3                  = 3u,
  ada_eSignal_4                  = 4u,
  ada_eSignal_5                  = 5u,
  ada_eSignal_6                  = 6u,
  ada_eSignal_7                  = 7u
};  
  
typedef enum ada_eSignalSelect ada_SignalSelect_t;
   
enum ada_eStartStatus
{
  ada_eConversion_STARTED      = 0u,
  ada_eConversion_NOT_STARTED  = 1u
};

typedef enum ada_eStartStatus ada_StartStatus_t;


enum ada_eProgressStatus
{
  ada_eConversion_RUNNING      = 0u,
  ada_eConversion_FINISHED     = 1u
};

typedef enum ada_eProgressStatus ada_ProgressStatus_t;
/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
  
#define ADA_RESOLUTION_BIT                      (10u)
#define ADA_INVALID_VALUE                       (0x3FFu)

#define ADA_ON                                  (1u)
#define ADA_OFF                                 (0u)


/* ADA_CFG */

#define ADC_CFG_CDIV_SET(num)                   (ADA_ADA_CFG_bit.adc_cdiv   = (ada_ClockDiv_t)(num))
#define ADC_CFG_CDIV_GET()                      ((ada_ClockDiv_t)ADA_ADA_CFG_bit.adc_cdiv)
#define ADA_CFG_TSAMP_SET(num)                  (ADA_ADA_CFG_bit.adc_tsamp  = (ada_SamplingPeriod_t)(num))
#define ADA_CFG_TSAMP_GET()                     ((ada_SamplingPeriod_t)ADA_ADA_CFG_bit.adc_tsamp)
#define ADA_CFG_100K_ENABLE()                   (ADA_ADA_CFG_bit.en_100k    = ADA_ON)
#define ADA_CFG_100K_DISABLE()                  (ADA_ADA_CFG_bit.en_100k    = ADA_OFF)
#define ADA_CFG_CH_SEL(num)                     (ADA_ADA_CFG_bit.chsel      = (ada_ChannelSelect_t)(num))
#define ADA_CFG_SIG_SEL(num)                    (ADA_ADA_CFG_bit.sigsel     = (ada_SignalSelect_t)(num))


/* ADA_CTRL */
#define ADA_CTRL_START()                        (ADA_ADA_CTRL_bit.soc       = ADA_ON)
#define ADA_CTRL_STATUS_START()                 ((ada_StartStatus_t)ADA_ADA_CTRL_bit.soc)        
#define ADA_CTRL_STATUS_PROGRESS()              ((ada_ProgressStatus_t)ADA_ADA_CTRL_bit.eoc)

#define ADA_DTA_RESULT()                        (ADA_ADC_DTA_bit.adc_dta)

#endif
