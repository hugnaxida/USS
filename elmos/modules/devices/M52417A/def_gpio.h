/* ------------------------------------------------------------------- */
/** @file def_gpio.h
 *
 * @brief Helper definitions for GPIO hardware module.
 *
 * Purpose:
 * Provide register access and register value definitions 
 * for GPIO hardware module
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
#ifndef _DEF_GPIO_H_
#define _DEF_GPIO_H_
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
enum gpio_eIO
{
  gpio_eIO_0  = 0x0001u,
  gpio_eIO_1  = 0x0002u,
  gpio_eIO_2  = 0x0004u,
  gpio_eIO_3  = 0x0008u
};

typedef enum gpio_eIO gpio_IO_t;

enum gpio_eIO_n
{
  gpio_eIO_N_0  = 0x0000u,
  gpio_eIO_N_1  = 0x0001u,
  gpio_eIO_N_2  = 0x0002u,
  gpio_eIO_N_3  = 0x0003u
};

typedef enum gpio_eIO_n gpio_IO_n_t;

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define GPIO_COUNT 4u

#define GPIO_DATA_OE_SET(gpio_n)        (GPIO_DATA_OE           |= (1u << (gpio_n)))
#define GPIO_DATA_OE_SET_ALL()          (GPIO_DATA_OE           = 0x0Fu)
#define GPIO_DATA_OE_CLEAR(gpio_n)      (GPIO_DATA_OE           &= ~(1u << (gpio_n)))
#define GPIO_DATA_OE_CLEAR_ALL          (GPIO_DATA_OE           = 0x00u)
#define GPIO_DATA_OE_TOGGLE(gpio_n)     (GPIO_DATA_OE           ^= (0x01u << (gpio_n)))

#define GPIO_DATA_OUT_SET(gpio_n)       (GPIO_DATA_OUT          |= (1u << (gpio_n)))
#define GPIO_DATA_OUT_SET_ALL()        (GPIO_DATA_OUT           = 0x0Fu)
#define GPIO_DATA_OUT_CLEAR(gpio_n)     (GPIO_DATA_OUT          &= ~(1u << (gpio_n)))
#define GPIO_DATA_OUT_CLEAR_ALL()       (GPIO_DATA_OUT           = 0x00u)
#define GPIO_DATA_OUT_TOGGLE(gpio_n)    (GPIO_DATA_OUT          ^= (0x01u << (gpio_n)))

#define GPIO_DATA_IE_SET(gpio_n)        (GPIO_DATA_IE           |= (1u << (gpio_n)))
#define GPIO_DATA_IE_SET_ALL()          (GPIO_DATA_IE            = 0x0Fu)
#define GPIO_DATA_IE_CLEAR(gpio_n)      (GPIO_DATA_IE           &= ~(1u << (gpio_n)))
#define GPIO_DATA_IE_CLEAR_ALL()        (GPIO_DATA_IE            = 0x00u)
#define GPIO_DATA_IE_TOGGLE(gpio_n)     (GPIO_DATA_IE           ^= (0x01u << (gpio_n)))

#define GPIO_DATA_PUE_SET(gpio_n)       (GPIO_DATA_PUE          |= (1u << (gpio_n)))
#define GPIO_DATA_PUE_SET_ALL()         (GPIO_DATA_PUE          = 0x0Fu)
#define GPIO_DATA_PUE_CLEAR(gpio_n)     (GPIO_DATA_PUE          &= ~(1u << (gpio_n)))
#define GPIO_DATA_PUE_CLEAR_ALL()       (GPIO_DATA_PUE          = 0x00u)
#define GPIO_DATA_PUE_TOGGLE(gpio_n)    (GPIO_DATA_PUE          ^= (0x01u << (gpio_n)))

#define GPIO_IRQ_ENABLE(irq)            (GPIO_IRQ_MASK          |= (1u << (0x0FU & (uint16_t)(irq))))
#define GPIO_IRQ_DISABLE(irq)           (GPIO_IRQ_MASK          &= ~(1u << (0x0FU & (uint16_t)(irq))))
#define GPIO_CTRL_IRQ_GET(irq_n)        (GPIO_STATUS & ((swtimer_eInterruptVectorNum_t)(1 << (irq_n))))
#define GPIO_CTRL_IRQ_CLEAR(irq_n)      (GPIO_IRQ_VNO            = (swtimer_eInterruptVectorNum_t)(irq_n))
#define GPIO_CTRL_IRQ_CLEAR_ALL()       (GPIO_STATUS             = 0xFFu)

#define GPIO3_SET() 		        GPIO_DATA_OUT_SET(gpio_eIO_N_3)
#define GPIO3_CLEAR() 		        GPIO_DATA_OUT_CLEAR(gpio_eIO_N_3)
#define GPIO3_TOGGLE()		        GPIO_DATA_OUT_TOGGLE(gpio_eIO_N_3)

#define GPIO2_SET() 		        GPIO_DATA_OUT_SET(gpio_eIO_N_2)
#define GPIO2_CLEAR()		        GPIO_DATA_OUT_CLEAR(gpio_eIO_N_2)
#define GPIO2_TOGGLE()		        GPIO_DATA_OUT_TOGGLE(gpio_eIO_N_2)

#define GPIO1_SET() 		        GPIO_DATA_OUT_SET(gpio_eIO_N_1)
#define GPIO1_CLEAR()		        GPIO_DATA_OUT_CLEAR(gpio_eIO_N_1)
#define GPIO1_TOGGLE()		        GPIO_DATA_OUT_TOGGLE(gpio_eIO_N_1)

#define GPIO0_SET() 		        GPIO_DATA_OUT_SET(gpio_eIO_N_0)
#define GPIO0_CLEAR()		        GPIO_DATA_OUT_CLEAR(gpio_eIO_N_0)
#define GPIO0_TOGGLE()		        GPIO_DATA_OUT_TOGGLE(gpio_eIO_N_0)



#endif
