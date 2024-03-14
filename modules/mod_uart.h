/* **************************************************************************//**
  * @file        
  * @brief       
  *
  * TODO: A detailed description of this module
  *    
  * ****************************************************************************
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
  * @section history_sec_mod_swt_h Revision History
  * $Id: mod_swt.h 392 2019-01-22 09:59:18Z siko $
  *
  * @verbatim
  * -------------------------------------------------------------------
  * Date     B/F Who Comment
  * ------------------------------------------------------------------- 
  * 17/05/27 (F) POE initial version
  * -------------------------------------------------------------------
  * @endverbatim
  *
  *
  * @creator      POE
  * @created      2017/05/27
  * 
  * @project      524.17
  * @requested    -
  * @inspector    - 
  * @verification -
  * @version      $Revision: 392 $
  * 
  * 
  * $State: Exp $   
  * $Author: siko $
  * $Date: 2019-01-22 10:59:18 +0100 (Di, 22 Jan 2019) $
  *
  * $Locker:  $
  * $Url:   $
  *
  * Additional markers:
  *
  *
  *
 ******************************************************************************/

/*################################################################################
  SW Timer
  ################################################################################
*/

#ifndef MOD_UART_H_
#define MOD_UART_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "def_uart.h"
#include "mod_swt.h"
#include "uart_InterruptHandler.h"


/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/


#define E_GPIO_IOMUX_UART_PORT                    (0x0003u)

#define GPIO_MUXUART_SET()             {GPIO_IOMUX=E_GPIO_IOMUX_UART_PORT;}

#define m_CurtRecPoint_ui8     136u

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

typedef struct {
    uint8_t uartRXbuffer[m_CurtRecPoint_ui8]; // 定义一个包含135个uint8_t元素的数组
    bool_t flog; // 定义一个布尔型标志位
    uint8_t last_value;//定义一个标志位，代表接收到的数据
} UART_RX_Data;

void Uart_Init(void);

/* ****************************************************************************/



#endif /*MOD_uart_H_*/
