/* ------------------------------------------------------------------- */
/** @file def_uart.h
 *
 * @brief Helper definitions for UART hardware module.
 *
 * Purpose:
 * Provide register access and register value definitions 
 * for UART hardware module
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
#ifndef _DEF_UART_H_
#define _DEF_UART_H_
//################################################################################
//  Helper defines
//################################################################################


/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include <io_m52417a.h>



#define UART_BAUD_SET(X)     {UART_BAUD_LOW=0XD0;}//UART_BAUD_HIGH=((24000000/X)>>16)&0XF; UART_BAUD_LOW = (uint16_t)(24000000/X);}
#define UART_TX_ENABLE()  {  UART_CTRL  |=E_UART_CTRL_TXEN;}
#define UART_TX_DISABLE()  {  UART_CTRL  &=~E_UART_CTRL_TXEN;}
#define UART_RX_ENABLE()  {  UART_CTRL  |=E_UART_CTRL_RXEN;}
#define UART_RX_DISABLE()  {  UART_CTRL  &=~E_UART_CTRL_RXEN;}
#define UART_TXIRQ_ENABLE()   {  UART_CTRL  |=E_UART_CTRL_TXIRQEN;}
#define UART_TXIRQ_DISABLE()  {  UART_CTRL  &=~E_UART_CTRL_TXIRQEN;}
#define UART_RXIRQ_ENABLE()   {  UART_CTRL  |=E_UART_CTRL_RXIRQEN;}
#define UART_RXIRQ_DISABLE()  {  UART_CTRL  &=~E_UART_CTRL_RXIRQEN;}
#define UART_TXOVRIRQ_ENABLE()   {  UART_CTRL  |=E_UART_CTRL_TXOVRIRQEN;}
#define UART_TXOVRIRQ_DISABLE()  {  UART_CTRL  &=~E_UART_CTRL_TXOVRIRQEN;}
#define UART_RXOVRIRQ_ENABLE()  {  UART_CTRL  |=E_UART_CTRL_RXOVRIRQEN;}
#define UART_RXOVRIRQ_DISABLE()  {  UART_CTRL  &=~E_UART_CTRL_RXOVRIRQEN;}
#define UART_HS_ENABLE()  {  UART_CTRL  |=E_UART_CTRL_HS;}
#define UART_HS_DISABLE()  {  UART_CTRL  &=~E_UART_CTRL_HS;}

#define UART_IRQ_ENABLE(irq)                 (UART_IRQ_MASK                   |= (1u << (0x0FU & (uint16_t)(irq))))
#define UART_IRQ_DISABLE(irq)                (UART_IRQ_MASK                   &= ~(1u << (0x0FU & (uint16_t)(irq))))  

#define  UART_TXINT_CLR()               {UART_INTCLR   |= E_UART_INTCLR_TXINT; }
#define  UART_RXINT_CLR()               {UART_INTCLR   |= E_UART_INTCLR_RXINT; }
#define  UART_TXOVRINT_CLR()            {UART_INTCLR   |= E_UART_INTCLR_TXOVRINT; }
#define  UART_RXOVRINT_CLR()            {UART_INTCLR   |= E_UART_INTCLR_RXOVRINT; }                       
#define  UART_ALLINT_CLR()              {UART_INTCLR   |= 0x0F; }  
#define  UART_NOALLINT_CLR()              {UART_INTCLR    = 0x00; }
#define UART_CTRL_IRQ_CLEAR(irq_n)           (UART_IRQ_VNO                     = (uart_eInterruptVectorNum_t)(irq_n))

#define UART_CTRL_IRQ_GET(irq_n)             (UART_IRQ_STATUS & ((uart_eInterruptVectorNum_t)(1u << (irq_n))))
 


 


#endif