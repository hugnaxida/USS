/* ------------------------------------------------------------------- */
/** @file def_dsi3.h
 *
 * @brief Helper definitions for DSI3 hardware module.
 *
 * Purpose:
 * Provide register access and register value definitions 
 * for DSI3 hardware module
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
 * 19/03/11 (F) poe 1006 added macro to read sync cnt err flag.
 * 19/01/11 (F) poe 1005 fixed name typo in typedef for dsi3_eRCC_Curve and dsi3_eRCC_Slope
 * 18/11/30 (F) poe 1004 added macro definition for manual current measurement start (E524.17A1)
 * 18/04/23 (F) poe 1003 added TimerX max value define
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
 * @version      $Revision: 424 $
 *
 *
 * $State: Exp $
 * $Author: siko $
 *
 * Additional markers:
 *
 */
#ifndef _DEF_DSI3_H_
#define _DEF_DSI3_H_
//################################################################################
//  Helper defines
//################################################################################


/* *************************************************************************** */
/* ******************************** INCLUDES ********************************* */
/* *************************************************************************** */
#include <io_m52417b.h>
#include "dsi3_InterruptHandler.h"
/* *************************************************************************** */
/* *********************** STRUCTS, ENUMS AND TYPEDEFS *********************** */
/* *************************************************************************** */
enum dsi3_eRCC_Chiptime
{
  dsi3_eRCC_Chiptime_3US = 0u,
  dsi3_eRCC_Chiptime_4US = 1u,
  dsi3_eRCC_Chiptime_5US = 2u,
  dsi3_eRCC_Chiptime_6US = 3u
};

typedef enum dsi3_eRCC_Chiptime dsi3_RCC_Chiptime_t;

enum dsi3_eRCC_Cur 
{

  dsi3_eRCC_Cur_STD     = 0u,
  dsi3_eRCC_Cur_HLF     = 1u
};

typedef enum dsi3_eRCC_Cur dsi3_RCC_Cur_t;

enum dsi3_ePdcmSeed
{
  dsi3_ePDCM_Seed_ID    = 0u,
  dsi3_ePDCM_Seed_FF    = 1u
};

typedef enum dsi3_ePdcmSeed dsi3_PdcmSeed_t;

enum dsi3_etimer_start_sel
{

  DSI3_TIMER_ST_EDGE   = 0u,
  DSI3_TIMER_ST_SYNC   = 1u
};

typedef enum dsi3_etimer_start_sel dsi3_timer_start_sel_t;

enum dsi3_eDebounceValue
{

  dsi3_eDebounceValue_OFF      = 0u,
  dsi3_eDebounceValue_83NS     = 1u,
  dsi3_eDebounceValue_166NS    = 2u,
  dsi3_eDebounceValue_333NS    = 3u,
  dsi3_eDebounceValue_666NS    = 4u,
  dsi3_eDebounceValue_1333NS   = 5u,
  dsi3_eDebounceValue_2666NS   = 6u,
  dsi3_eDebounceValue_5333NS   = 7u
};

typedef enum dsi3_eDebounceValue dsi3_DebounceValue_t;


union dsi3_uClk1US
{
  struct
  {
    uint16_t  frac       :  5;               /*!< frac bitfield                                                         */
    uint16_t  div        :  5;               /*!< div bitfield                                                          */
  }                     Fields;
  uint16_t              Value;
};

typedef union dsi3_uClk1US dsi3_Clk1US_t;



enum dsi3_eRCC_Slope /**< Reverse communication channel current slope selection */
{
  dsi3_eRCC_Slope_1us          = 0u,
  dsi3_eRCC_Slope_2us          = 1u,
  dsi3_eRCC_Slope_3us          = 2u,
  dsi3_eRCC_Slope_4us          = 3u,
  dsi3_eRCC_Slope_6us          = 4u
};

typedef enum dsi3_eRCC_Slope dsi3_RCCSlope_t;


enum dsi3_eRCC_Curve /**< Reverse communication channel current waveform */
{
  dsi3_eRCC_Curve_Rounded      = 0u,
  dsi3_eRCC_Curve_Linear       = 1u
};

typedef enum dsi3_eRCC_Curve dsi3_RCC_Curve_t;


enum dsi3_eRCC_CurrentOffset /**< Reverse communication channel current offset value */
{
  dsi3_eRCC_CurrentOffset_0uA = 0u,
  dsi3_eRCC_CurrentOffset_1uA = 1u,
  dsi3_eRCC_CurrentOffset_2uA = 2u,
  dsi3_eRCC_CurrentOffset_3uA = 3u,
  dsi3_eRCC_CurrentOffset_4uA = 4u,
  dsi3_eRCC_CurrentOffset_5uA = 5u,
  dsi3_eRCC_CurrentOffset_6uA = 6u,
  dsi3_eRCC_CurrentOffset_7uA = 7u
};

typedef enum dsi3_eRCC_CurrentOffset dsi3_RCC_CurrentOffset_t;


enum dsi3_eFCC_TBit /**< Bit timing FCC */
{
  dsi3_eFCC_TBit_08us 		= 0u,
  dsi3_eFCC_TBit_16us 		= 1u,
  dsi3_eFCC_TBit_32us 		= 2u,
  dsi3_eFCC_TBit_reserved  	= 3u
};

typedef enum dsi3_eFCC_TBit dsi3_FCC_TBit_t;

/* *************************************************************************** */
/* *************************** DEFINES AND MACROS **************************** */
/* *************************************************************************** */

#define DSI3_ON                                                 (1u)
#define DSI3_OFF                                                (0u)
#define DSI3_TIMERX_MAX_VALUE                                   (0x1FFFu)   /**< Max. register value of the TimerX registers @13 bits */

/* DSI3_CONFIG */

#define SFT_DSI3_CONFIG_T_CHIP                                  (6u)
#define SFT_DSI3_CONFIG_PDCM_SEED_SEL                           (10u)
#define SFT_DSI3_CONFIG_TIMER_START_SEL                         (11u)
#define SFT_DSI3_CONFIG_T_BIT_FCC                               (12u)

/* DSI3_ANALOG_CTRL */
#define SFT_DSI3_ANALOGCTRL_RCC_SLOPE                           ( 3u)
#define SFT_DSI3_ANALOGCTRL_RCC_CURVE                           ( 6u)
#define SFT_DSI3_ANALOGCTRL_RCC_CURROFFSET                      ( 7u)
#define SFT_DSI3_ANALOGCTRL_FCC_DEBOUNCE                        (13u)


/* DSI3_CTRL */
#define DSI3_CTRL_SET_MODE_VALUE_CRM_MODE		                    (1u)
#define DSI3_CTRL_SET_MODE_VALUE_PDCM_MODE			                (2u)
#define DSI3_CTRL_SET_MODE_VALUE_DISC_MODE			                (3u)



#define DSI3_CTRL_DMA_BASE_ADDR_SET(address)                    do {\
                                                                      (DSI3_RCC_DMA_ADDR_LOW = ((uint16_t)((address) & 0xFFFFu)));\
                                                                      (DSI3_RCC_DMA_ADDR_HIGH = ((uint16_t)((address) >> 16u)));\
                                                                } while(0)
#define DSI3_CTRL_BUFFER_LENGTH_SET(length)                     (DSI3_RCC_BUFFER_LENGTH                         = (length))
#define DSI3_CTRL_BUFFER_LENGTH_GET()                           (DSI3_RCC_BUFFER_LENGTH)

/* --> 18-01-22/POE: r4083, Improvement
 * Replaced macro with parameterized version to prevent
 * compiler warning 
 */
#define DSI3_CTRL_FCC_CMD_READ(val)                             do {\
                                                                     (val) = (uint32_t) DSI3_FCC_COMMAND_HIGH;\
                                                                     (val) = (uint32_t) (((val) << 16u) | (DSI3_FCC_COMMAND_LOW));\
                                                                } while(0)
/* --> 18-01-22/POE: r4083, Improvement */
#define DSI3_CTRL_FCC_CMD_READ_HI()                             (DSI3_FCC_COMMAND_HIGH << 16)
#define DSI3_CTRL_FCC_CMD_READ_LO()                             (DSI3_FCC_COMMAND_LOW)

/* *************************************************************************** */
/* ******************************* DSI3 CONFIG ******************************* */
/* *************************************************************************** */

#define DSI3_CTRL_CONFIG_FCC_ENABLE()                           (DSI3->CONFIG.bit.fcc_enable 			= DSI3_ON)
#define DSI3_CTRL_CONFIG_FCC_DISABLE()                          (DSI3->CONFIG.bit.fcc_enable 			= DSI3_OFF)

#define DSI3_CTRL_CONFIG_RCC_ENABLE()                           (DSI3->CONFIG.bit.rcc_enable 			= DSI3_ON)
#define DSI3_CTRL_CONFIG_RCC_DISABLE()                          (DSI3->CONFIG.bit.rcc_enable 			= DSI3_OFF)

#define DSI3_CTRL_CONFIG_CRC_CHECK_ENABLE()                     (DSI3->CONFIG.bit.crc_check 			= DSI3_ON)
#define DSI3_CTRL_CONFIG_CRC_CHECK_DISABLE()                    (DSI3->CONFIG.bit.crc_check 			= DSI3_OFF)

#define DSI3_CTRL_CONFIG_CRC_ADD_ENABLE()                       (DSI3->CONFIG.bit.crc_add 			    = DSI3_ON)
#define DSI3_CTRL_CONFIG_CRC_ADD_DISABLE()                      (DSI3->CONFIG.bit.crc_add 			    = DSI3_OFF)

#define DSI3_CTRL_CONFIG_AUTORESP_ENABLE()                      (DSI3->CONFIG.bit.auto_resp 			= DSI3_ON)
#define DSI3_CTRL_CONFIG_AUTORESP_DISABLE()                     (DSI3->CONFIG.bit.auto_resp 			= DSI3_OFF)

#define DSI3_CTRL_CONFIG_AUTOTIMER_ENABLE()                     (DSI3->CONFIG.bit.auto_timer 			= DSI3_ON)
#define DSI3_CTRL_CONFIG_AUTOTIMER_DISABLE()                    (DSI3->CONFIG.bit.auto_timer 			= DSI3_OFF)

#define DSI3_CTRL_CONFIG_AUTOSNYC_ENABLE()                      (DSI3->CONFIG.bit.auto_sync 			= DSI3_ON)
#define DSI3_CTRL_CONFIG_AUTOSNYC_DISABLE()                     (DSI3->CONFIG.bit.auto_sync 			= DSI3_OFF)
#define DSI3_CTRL_CONFIG_AUTOSNYC_GET()                         (DSI3->CONFIG.bit.auto_sync)

#define DSI3_CTRL_CONFIG_SYNC_VALI_ENABLE()                     (DSI3->CONFIG.bit.auto_sync 			= DSI3_OFF)
#define DSI3_CTRL_CONFIG_SYNC_VALI_DISABLE()                    (DSI3->CONFIG.bit.auto_sync 			= DSI3_ON)

#define DSI3_CTRL_CONFIG_T_CHIP_SET(val)                        (DSI3->CONFIG.bit.t_chip 			    = (val))
#define DSI3_CTRL_CONFIG_T_CHIP_GET()                           (DSI3->CONFIG.bit.t_chip)

#define DSI3_CTRL_CONFIG_PDCM_SEED_SEL_SOURCEID()               (DSI3->CONFIG.bit.pdcm_seed_sel 	    = DSI3_OFF)
#define DSI3_CTRL_CONFIG_PDCM_SEED_SEL_0xFF()                   (DSI3->CONFIG.bit.pdcm_seed_sel 	    = DSI3_ON)

#define DSI3_CTRL_CONFIG_RCC_CURR_STANDARD()                    (DSI3->CONFIG.bit.rcc_curr_sel 		    = DSI3_OFF)
#define DSI3_CTRL_CONFIG_RCC_CURR_HALF()                        (DSI3->CONFIG.bit.rcc_curr_sel 		    = DSI3_ON)

#define DSI3_CTRL_CONFIG_DEBOUNCE_SET(val)                      (DSI3->CONFIG.bit.debounce 		     	= (val))
#define DSI3_CTRL_CONFIG_DEBOUNCE_GET()                         (DSI3->CONFIG.bit.debounce)

/* *************************************************************************** */
/* ********************************* DSI3 STATUS ***************************** */
/* *************************************************************************** */
#define DSI3_CTRL_STATUS_FCC_ABORT()                            (DSI3->CTRL.bit.abort_fcc 			= DSI3_ON)
#define DSI3_CTRL_STATUS_RCC_ABORT()                            (DSI3->CTRL.bit.abort_rcc 			= DSI3_ON)
#define DSI3_DISC_START_CURR_MEAS()                             (DSI3->CTRL.bit.abort_rcc 			= DSI3_ON)  /* Only valid during DISC mode for device E524.17A1 */
#define DSI3_CTRL_STATUS_RCC_START()                            (DSI3->CTRL.bit.start_rcc 			= DSI3_ON)

#define DSI3_CTRL_STATUS_CRM_ENABLE()                           (DSI3->CTRL.bit.set_mode 			= DSI3_CTRL_SET_MODE_VALUE_CRM_MODE)
#define DSI3_CTRL_STATUS_PDCM_ENABLE()                          (DSI3->CTRL.bit.set_mode 			= DSI3_CTRL_SET_MODE_VALUE_PDCM_MODE)
#define DSI3_CTRL_STATUS_DISC_ENABLE()                          (DSI3->CTRL.bit.set_mode 			= DSI3_CTRL_SET_MODE_VALUE_DISC_MODE)

#define DSI3_CTRL_STATUS_BLANKING_OFF()                         (DSI3->CTRL.bit.set_blanking_off 	        = DSI3_ON)
#define DSI3_CTRL_STATUS_BLANKING_ON()                          (DSI3->CTRL.bit.set_blanking_on 	        = DSI3_ON)

#define DSI3_CTRL_SYNC_CNT_GET()                                (DSI3->SYNC_CNT.reg)

#define DSI3_CTRL_STATUS_TIMER_START()                          (DSI3->CTRL.bit.start_timer 			= DSI3_ON)
#define DSI3_CTRL_STATUS_TIMER_STOP()                           (DSI3->CTRL.bit.start_timer 			= DSI3_OFF)
#define DSI3_CTRL_STATUS_TIMER_RESET()                          (DSI3->CTRL.bit.reset_timer 			= DSI3_ON)
#define DSI3_CTRL_STATUS_TIMER_STATUS()                         (DSI3->STATUS.bit.timer_status)
/*--> 2018-02-23/POE: revision R4346, Improvement
 * Added defines for fcc_low_flag access
 */
#define DSI3_CTRL_STATUS_FCCLOW_FLAG()                          (DSI3->STATUS.bit.fcc_low_flag)
#define DSI3_CTRL_STATUS_FCCLOW_FLAG_CLEAR()                    (DSI3->CTRL.bit.clr_fcc_low_flag = TRUE)
/*--> 2018-02-23/POE: revision R4346, Improvement */

#define DSI3_CTRL_STATUS_SYNC_CNT_ERR_GET()                     (DSI3_STATUS_bit.sync_cnt_err)
  
#define DSI3_CLK_1US_GET()                                      (DSI3_CLK_1US)
#define DSI3_CLK_1US_SET(newDiv)                                (DSI3_CLK_1US                                   = (newDiv))

#define DSI3_TIMER_CAPTURE_GET()                                (DSI3_TIMER_CAPTURE)
#define DSI3_SYNC_CNT_GET()                                     (DSI3_SYNC_CNT)

/* *************************************************************************** */
/* ************************** DSI3 DISCOVERY CTRL **************************** */
/* *************************************************************************** */

#define DSI3_DISC_CTRL_DEBOUNCE_SET(val)                        (DSI3->DISCOVERY_CTRL.bit.debounce 		= (val))
#define DSI3_DISC_CTRL_DEBOUNCE_GET()                           (DSI3->DISCOVERY_CTRL.bit.debounce)

#define DSI3_DISC_CTRL_AUTO_DISC_ACCEPT_ENABLE()                (DSI3->DISCOVERY_CTRL.bit.auto_disc_accept      = DSI3_ON)
#define DSI3_DISC_CTRL_AUTO_DISC_ACCEPT_DISABLE()               (DSI3->DISCOVERY_CTRL.bit.auto_disc_accept      = DSI3_OFF)
#define DSI3_DISC_CTRL_AUTO_DISC_ACCEPT_GET()                   (DSI3->DISCOVERY_CTRL.bit.auto_disc_accept)

#define DSI3_DISC_CTRL_AUTO_DISC_RESP_ENABLE()                  (DSI3->DISCOVERY_CTRL.bit.auto_disc_resp        = DSI3_ON)
#define DSI3_DISC_CTRL_AUTO_DISC_RESP_DISABLE()                 (DSI3->DISCOVERY_CTRL.bit.auto_disc_resp        = DSI3_OFF)
#define DSI3_DISC_CTRL_AUTO_DISC_RESP_GET()                     (DSI3->DISCOVERY_CTRL.bit.auto_disc_resp)

#define DSI3_DISC_CTRL_CURR_CMP_OUT_CAP_GET()                   (DSI3->DISCOVERY_CTRL.bit.curr_cmp_cap)
#define DSI3_DISC_CTRL_CURR_CMP_OUT_GET()                       (DSI3->DISCOVERY_CTRL.bit.curr_cmp_out)

#define DSI3_DISC_CTRL_RAMP_ON_ENABLE()                         (DSI3->DISCOVERY_CTRL.bit.disc_ramp_on        = DSI3_ON)
#define DSI3_DISC_CTRL_RAMP_ON_DISABLE()                        (DSI3->DISCOVERY_CTRL.bit.disc_ramp_on        = DSI3_OFF)
#define DSI3_DISC_CTRL_RAMP_ON_GET()                            (DSI3->DISCOVERY_CTRL.bit.disc_ramp_on)  
  
/* *************************************************************************** */
/* ************************* DSI3 TIMER_COMPARE_A **************************** */
/* *************************************************************************** */

#define DSI3_CTRL_TIMER_COMPARE_A_SET(val)                      (DSI3_TIMER_COMPARE_A 				= (val)) 
#define DSI3_CTRL_TIMER_COMPARE_A_GET()                         (DSI3_TIMER_COMPARE_A) 

/* *************************************************************************** */
/* ************************* DSI3 TIMER_COMPARE_B **************************** */
/* *************************************************************************** */

#define DSI3_CTRL_TIMER_COMPARE_B_SET(val)                      (DSI3_TIMER_COMPARE_B 				= (val)) 
#define DSI3_CTRL_TIMER_COMPARE_B_GET()                         (DSI3_TIMER_COMPARE_B) 

/* *************************************************************************** */
/* ************************* DSI3 TIMER_COMPARE_C **************************** */
/* *************************************************************************** */

#define DSI3_CTRL_TIMER_COMPARE_C_SET(val)                      (DSI3_TIMER_COMPARE_C 				= (val)) 
#define DSI3_CTRL_TIMER_COMPARE_C_GET()                         (DSI3_TIMER_COMPARE_C) 

#define DSI3_CTRL_TIMER_COUNTER()                               (DSI3_TIMER_COUNTER)
/* *************************************************************************** */
/* ************************** DSI3 SOURCE ID ********************************* */
/* *************************************************************************** */

#define DSI3_CTRL_SOURCE_ID_SET(val)                            (DSI3_SOURCE_ID 				= (val))
#define DSI3_CTRL_SOURCE_ID_GET()                               (DSI3_SOURCE_ID)


/* *************************************************************************** */
/* *************************** DSI3 Interrupts ******************************* */
/* *************************************************************************** */

#define DSI3_CTRL_IRQ_ENABLE(irq_n)                             (DSI3_IRQ_VENABLE                               = (dsi3_eInterruptVectorNum_t)(irq_n))
#define DSI3_CTRL_IRQ_DISABLE(irq_n)                            (DSI3_IRQ_VDISABLE                              = (dsi3_eInterruptVectorNum_t)(irq_n))
#define DSI3_CTRL_IRQ_DISABLE_ALL()                             (DSI3_IRQ_MASK                                  = (uint16_t)0x0000u)
#define DSI3_CTRL_IRQ_GET(irq_n)                                (DSI3_STATUS & ((dsi3_eInterruptVectorNum_t)(1 << (irq_n))))
#define DSI3_CTRL_IRQ_CLEAR(irq_n)                              (DSI3_IRQ_VNO                                   = (dsi3_eInterruptVectorNum_t)(irq_n))
#define DSI3_CTRL_IRQ_CLEAR_ALL()                               (DSI3_IRQ_STATUS                                = (uint16_t)0x0FFFu)


#endif
