/** @file mod_uart.c
 * @brief Uart configuration and access module
 *
 * Purpose:
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
 * @section history_sec_mod_dac_c Revision History
 * $Id: mod_Uart.c 394 2019-01-23 15:20:39Z siko $
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who  Comment
 * -------------------------------------------------------------------
 * 17/06/13 (F) JNAU initial version
 * -------------------------------------------------------------------
 * @endverbatim
 *
 *
 * @creator      JNAU
 * @created      2017/06/13
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


#include "mod_uart.h"
#include "mod_dsi3.h"
#include "uart_InterruptHandler.h"
#include "nvic_InterruptHandler.h"
#include "elmos\includes\el_types_ACM0_IAR.h"
#include "elmos\includes\el_regs_m52417a_IAR.h"
#include "dbc.h"


// ------------------------------------------------------------------------------
/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define swtimer_IRQ_EVT_CNT_ZERO_UartPeriodTimer      swtimer_IRQ_EVT_CNT_ZERO_0
#define m_CurtRecPoint_ui8     136u
#define UART_FRAME_LENGTH      15u
#define FRAME_BK0         0X0B
#define FRAME_FAULT       0X0C
#define FRAME_OTHER       0X0D
#define mul(a,b)          (a*b)



static UART_RX_Data rxData;
bool_t uart_RegisterCustomInterruptCallback(uart_eInterruptVectorNum_t irqsrc,  uart_InterruptCallback_t cb);
void Uart_Receive_interrupt(uart_eInterruptVectorNum_t sno,  uart_pInterruptContextData_t contextdata);
void Uart_Send_data(uint8_t Send_data);
bool_t calculate_checksum(uint8_t data);
void parse_and_handle_data(UART_RX_Data rxData );



/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/

static uart_sInterruptEnvironmentData_t uart_envData;

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* *************************************************************************//**
 * @implementation
 * Initializes the Uart modules
 *
 * @return
 * ****************************************************************************/
void Uart_Init(void)
{
	uart_InterruptInitialisation(&nvic_InterfaceFunctions,&uart_envData, NULL);

	nvic_InterfaceFunctions.SetModulePriority(nvic_IRQ_UART, nvic_Priority_Level_2);
	UART_BAUD_SET(115200);
	UART_TX_ENABLE();
	UART_RX_ENABLE();
	UART_TXIRQ_ENABLE();
	UART_RXIRQ_ENABLE(); 
	UART_IRQ_ENABLE(uart_IRQ_RX);
	UART_IRQ_ENABLE(uart_IRQ_TX);

	uart_RegisterCustomInterruptCallback(uart_IRQ_RX,Uart_Receive_interrupt);
}
/* *************************************************************************//**
 * @implementation
 *  Send  Data
 * @param       Send_data                  
 * @return      
 * ****************************************************************************/
void Uart_Send_data(uint8_t Send_data)
{
    UART_DATA = Send_data; 
    while(!UART_CTRL_IRQ_GET(uart_IRQ_TX));
    UART_TXINT_CLR(); 
}
/* *************************************************************************//**
 * @implementation
 *  Send  Data
 * @param       str                    
 * @param       Stringlen              
 * @return      
 * ****************************************************************************/

void Uart_Send_Longdata(uint8_t *f_str_pui8, uint8_t f_len_ui8)
{
    uint8_t i=0; 
    do { 
    Uart_Send_data(*(f_str_pui8+i)); 
    i++; 
    } 
    while (i<f_len_ui8); 

}

/* *************************************************************************//**
 * @implementation
 *  a custom ISR for a uart interrupt.
 *
 * @return      
 * ****************************************************************************/
void Uart_Receive_interrupt(uart_eInterruptVectorNum_t sno,  uart_pInterruptContextData_t contextdata)
{
  uint8_t last_uart_value=0;
  while (UART_CTRL_IRQ_GET(uart_IRQ_RX) && last_uart_value<m_CurtRecPoint_ui8)
  {
     UART_RXINT_CLR();  
     rxData.uartRXbuffer[last_uart_value] = UART_DATA; 
     last_uart_value++;
  } 
  rxData.last_value=last_uart_value;
  rxData.flog=TRUE;
}


/* *************************************************************************//**
 * @implementation
 *  Register a custom ISR for a uart interrupt.
 *
 * @param       irqsrc                    uart module source Irq
 * @param       cb                        pointer to custom isr function
 * @return      TRUE            if assignment successful
 * ****************************************************************************/
bool_t uart_RegisterCustomInterruptCallback(uart_eInterruptVectorNum_t irqsrc,  uart_InterruptCallback_t cb)
{
  bool_t retVal = FALSE;
  uart_InterruptRegisterCallback(irqsrc, cb);
  retVal = TRUE;
  return retVal;
}

bool_t calculate_checksum(uint8_t CRC_data) {
  bool_t retVal=FALSE;
  if(CRC_data!=0X00){
    //do nothing
  }
  else{
    retVal=TRUE;
  }
  return retVal;

}

void parse_and_handle_data(UART_RX_Data rxData) {
    uint8_t index = 0;
    uint8_t frameCounter = 0;
    
    while (index < rxData.last_value) {
        // Check the frame header
        if (rxData.uartRXbuffer[index] == 0XFF &&
            rxData.uartRXbuffer[index + 1] == 0XFF ) {

            // Get the data length
            uint8_t Data_Length = rxData.uartRXbuffer[index + 3];

            // Check if there is sufficient data to form a frame
            if (index + 5 + Data_Length + 3 <= rxData.last_value) {  // Frame header (3 bytes) + Data length (1 byte) + Data (Data_Length bytes) + Checksum (reserved) + Frame tail (3 bytes)
                
                // Get the frame ID
                uint8_t frameID = rxData.uartRXbuffer[index + 2];

                switch (frameID) {
                    case FRAME_BK0:
                        {
                            static bk0_dbc bk0_frame;
                            // Assuming the frame data immediately follows the frame ID
                            memcpy((void *)&bk0_frame.sMsg, &rxData.uartRXbuffer[index + 4], sizeof(bk0_frame.sMsg));
                            break;
                        }
                    case FRAME_FAULT:
                        {
                            static bk0_fault_dbc fault_frame;
                            memcpy((void *)&fault_frame.sMsg, &rxData.uartRXbuffer[index + 4], sizeof(fault_frame.sMsg));
                            break;
                        }
                    case FRAME_OTHER:
                        {
                            static bk0_other_dbc other_frame;
                            memcpy((void *)&other_frame.sMsg, &rxData.uartRXbuffer[index + 4], sizeof(other_frame.sMsg));
                            break;
                        }
                    default:
                        // Handle unknown frame types...
                        break;
                }

                // Move to the starting position of the next frame
                index += 5 + Data_Length + 3;  
                frameCounter++;
            }
            else {
                // The amount of data is insufficient to constitute a complete frame, which may indicate an error and requires handling exceptional cases.
                break;
            }
        }
        else {
            // Non-header data detected, which might indicate an issue and requires handling exceptional circumstances.
            break;
        }
    }
}






