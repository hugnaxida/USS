/***************************************************************************//**
 * @file mod_ada.c
 * @brief ADA configuration and access module
 *
 * Purpose:
 *    
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
 * @section history_sec_mod_ada_c Revision History
 * $Id: mod_ada.c 394 2019-01-23 15:20:39Z siko $
 *
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who Comment
 * ------------------------------------------------------------------- 
 * 17/05/29 (F) POE initial version
 * -------------------------------------------------------------------
 * @endverbatim
 * 
 *
 * @creator      POE
 * @created      2017/05/29
 * 
 * @project      524.17
 * @requested    -
 * @inspector    - 
 * @verification -
 * @version      $Revision: 394 $
 * 
 * 
 * $State: Exp $   
 * $Author: siko $
 * $Date: 2019-01-23 16:20:39 +0100 (Mi, 23 Jan 2019) $
 * $Locker:  $
 * $Url:   $
 *
 * Additional markers:
 *
 *
 *
 */

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_ada.h"

//################################################################################
// ADA

// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

#define ADA_ADC_CDIV            (1u)
#define ADA_ADC_TSAMP           (1u)

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* ************************************************************************//**
 * @implementation
 * ADA initialization
 * @return
 * ****************************************************************************/
void ada_Init(void)
{ 
  ADC_CFG_CDIV_SET(ADA_ADC_CDIV);
  ADA_CFG_TSAMP_SET(ADA_ADC_TSAMP);
}


/* ************************************************************************//**
 * @brief   Returns the average of the taken samples.
 *
 * @implementation
 * Starts ADC sampling with a given amount of samples
 * and returns arithmetic mean.
 * @param        ch              ada channel select
 * @param        sig             ada signal select
 * @return      uint16_t        arithmetic mean value
 * ***************************************************************************/
/*
ada_TriggerSample 函数的主要功能是启动ADC（模拟数字转换器）对指定通道（ada_ChannelSelect_t ch）和信号源（ada_SignalSelect_t sig）进行采样，并返回采样结果的算术平均值。
1. 定义常量 sampleCount 为 4，表示需要采集的样本数量。2. 初始化返回值 retVal 为0，这个变量将用于累计所有样本的数值。3. 根据传入的参数配置ADC的通道选择（ADA_CFG_CH_SEL(ch)）和信号选择（ADA_CFG_SIG_SEL(sig)）。
4. 进行一个循环，循环次数等于 sampleCount，在循环内部：•检查ADC转换是否正在进行，如果没有，则启动一次新的ADC转换（ADA_CTRL_START()）。
•等待ADC转换完成（通过不断检查 ADA_CTRL_STATUS_PROGRESS() 直到其返回 ada_eConversion_FINISHED）。•一旦ADC转换完成，将获取此次转换结果（ADA_DTA_RESULT()），并将结果累加到 retVal 上。
5. 循环结束后，为了计算算术平均值，将累积的结果右移两位（相当于除以4，因为样本数量为4），这样就得到了所有样本的平均值。
6. 返回最终计算得到的平均值。这个函数适用于需要多次采样并求平均以提高精度的场合，它确保了在获取每个样本时ADC转换已完成，且返回的是所采集样本的平均数值。
*/
uint16_t ada_TriggerSample(ada_ChannelSelect_t ch, ada_SignalSelect_t sig)
{
  const uint16_t sampleCount = 4u; /*< The number of samples */

  uint16_t retVal = 0u;
  
  ADA_CFG_CH_SEL(ch);
  ADA_CFG_SIG_SEL(sig);

  for (uint8_t i=0; i < sampleCount;++i)
  {
    if (ada_eConversion_RUNNING != ADA_CTRL_STATUS_PROGRESS())
    {
      ADA_CTRL_START();
      
      /* wait for analog data aquisition finished */
      while(ada_eConversion_FINISHED != ADA_CTRL_STATUS_PROGRESS())
      {};
      retVal += ADA_DTA_RESULT(); 
    }
  }
  /* Calculate median by dividing by (2^log2OfSampleCount). E.g. 2^2 -> Divide by 4 */
  retVal = retVal >> 2u;

  return retVal;
}
/*
uint16_t ada_TriggerSample(ada_ChannelSelect_t ch, ada_SignalSelect_t sig)
{
    // 设置采样次数为4次
    const uint16_t sampleCount = 4u;

    // 初始化结果变量为0
    uint16_t retVal = 0u;

    // 配置ADC的通道选择
    ADA_CFG_CH_SEL(ch);

    // 配置ADC的信号选择
    ADA_CFG_SIG_SEL(sig);

    // 采样循环
    for (uint8_t i = 0; i < sampleCount; ++i)
    {
        // 如果ADC转换不在进行中
        if (ada_eConversion_RUNNING != ADA_CTRL_STATUS_PROGRESS())
        {
            // 启动ADC转换
            ADA_CTRL_START();

            // 等待模拟数据采集完成
            while (ada_eConversion_FINISHED != ADA_CTRL_STATUS_PROGRESS()) {}
            
            // 获取并累加ADC转换结果
            retVal += ADA_DTA_RESULT();
        }
    }

    // 计算均值，由于采样次数为4，所以右移2位（相当于除以4）
    retVal = retVal >> 2u;

    // 返回平均值
    return retVal;
}

// 宏定义，用于配置ADC的通道选择
#define ADA_CFG_CH_SEL(num)                     (ADA_ADA_CFG_bit.chsel      = (ada_ChannelSelect_t)(num))

// 宏定义，用于配置ADC的信号选择
#define ADA_CFG_SIG_SEL(num)                    (ADA_ADA_CFG_bit.sigsel     = (ada_SignalSelect_t)(num))

// 宏定义，启动ADC转换
#define ADA_CTRL_START()                        (ADA_ADA_CTRL_bit.soc       = ADA_ON)

// 宏定义，获取ADC启动状态
#define ADA_CTRL_STATUS_START()                 ((ada_StartStatus_t)ADA_ADA_CTRL_bit.soc)

// 宏定义，获取ADC转换进度状态
#define ADA_CTRL_STATUS_PROGRESS()              ((ada_ProgressStatus_t)ADA_ADA_CTRL_bit.eoc)

// 宏定义，获取ADC转换结果
#define ADA_DTA_RESULT()                        (ADA_ADC_DTA_bit.adc_dta)
*/