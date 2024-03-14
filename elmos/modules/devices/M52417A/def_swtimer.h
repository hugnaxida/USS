/* ------------------------------------------------------------------- */
/** @file def_swtimer.h
 *
 * @brief Helper definitions for SWTIMER hardware module.
 *
 * Purpose:
 * Provide register access and register value definitions 
 * for SWTIMER hardware module
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
 * 18/08/28 (B) poe 1003 fixed wrong bit mask application for disabling autocycle
 * 18/08/07 (B) poe 1002 fixed shift position error and added timer count macro
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
#ifndef _DEF_SWTIMER_H_
#define _DEF_SWTIMER_H_
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

enum swtimer_eTimer
{
  swtimer_eTimer_0  = 0u,
  swtimer_eTimer_1  = 1u
};

typedef enum swtimer_eTimer swtimer_Timer_t;

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

#define SWT_ON                              ( 1u)
#define SWT_OFF                             ( 0u)
#define SWT_ENABLE(num)                     (SWTIMER_CONFIG                     |=  (1u << (0x03U & (uint16_t)(num))))
#define SWT_DISABLE(num)                    (SWTIMER_CONFIG                     &= ~(1u << (0x03U & (uint16_t)(num))))

#define SWT_CLK_SRC_1US()                   (SWTIMER_CONFIG_bit.ext_strb_src    = SWT_ON)
#define SWT_CLK_SRC_SYS()                   (SWTIMER_CONFIG_bit.ext_strb_src    = SWT_OFF)
#define SWT_AUTOCYCLE_ENABLE(num)           (SWTIMER_CONFIG                     |=  (uint16_t)(1L<<(num))<<2u)
#define SWT_AUTOCYCLE_DISABLE(num)          (SWTIMER_CONFIG                     &= ~(0x0CU & (uint16_t)((1L<<(num))<<2u)))
  
#define SWT_CNT_RELOAD_SET(num,rld)         (*(&SWTIMER_CNT0_RELOAD + (num))    = (uint16_t)(rld))
#define SWT_DIV_RELOAD_SET(num, rld)        (*(&SWTIMER_DIV0_RELOAD + (num))    = (uint16_t)(rld))

#define SWT_RESTART_CNT(num)                (SWTIMER_COMMAND                    |= (1u << (num)))
#define SWT_RESTART_DIV(num)                (SWTIMER_COMMAND                    |= (1u << ((num)+2u)))

#define SWT_RESTART_TIMER(num)              (SWTIMER_COMMAND                    =  (1u << (num)) | (1u << ((num) + 2u)))

#define SWT_IRQ_ENABLE(irq)                 (SWTIMER_IRQ_MASK                   |= (1u << (0x0FU & (uint16_t)(irq))))
#define SWT_IRQ_DISABLE(irq)                (SWTIMER_IRQ_MASK                   &= ~(1u << (0x0FU & (uint16_t)(irq))))
#define SWT_CTRL_IRQ_GET(irq_n)             (SWTIMER_IRQ_STATUS & ((swtimer_eInterruptVectorNum_t)(1u << (irq_n))))
#define SWT_CTRL_IRQ_CLEAR(irq_n)           (SWTIMER_IRQ_VNO                     = (swtimer_eInterruptVectorNum_t)(irq_n))
#define SWT_CTRL_IRQ_CLEAR_ALL()            (SWTIMER_IRQ_STATUS                  = 0x0Fu)

#define SWT_CNT0_VALUE()                    (SWTIMER_CNT0_VALUE)
#define SWT_CNT1_VALUE()                    (SWTIMER_CNT1_VALUE)

#endif
