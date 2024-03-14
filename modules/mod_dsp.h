/* *************************************************************************//**
 * @file		mod_dsp.h
 *
 * @creator		poe
 * @created		07.02.2017
 * @sdfv      Elmos Flow
 *
 * @brief  		DSP configuration and access module (header)
 *
 * @purpose
 *
 * The DSP module 
 *
 *  ******************************************************************************
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
 * $Id: mod_dsp.h 394 2019-01-23 15:20:39Z siko $
 *
 * $Revision: 394 $
 *
 * *****************************************************************************/

#ifndef MOD_DSP_H_
#define MOD_DSP_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "elmos/modules/devices/M52417A/def_dsp.h"
#include "nvic_InterruptHandler.h"
#include "dsp_InterruptHandler.h"   
/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

#define EEVAL_RINGBUFFER_SIZE   (10)      // 30 * 32 bit
#define EEVAL1_RINGBUFFER_SIZE  (10*3) // 30 * 3 * 16 bit
#define EEVAL2_RINGBUFFER_SIZE  (10*3) // 30 * 3 * 16 bit

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/
extern nvic_cpInterfaceFunctions_t nvic_IfFuns;

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* *****************************************************************************
 * @brief Initialize DSP module
 *
 * @param none
 *
 * @pre        NVIC (nvic_VectorInterruptControl) has to presented and initialized
 *
 * @post       DSP module is configured for use.
 *
 * @detaildesc
 * Initializes the DSP software and hardware module, including the module
 * interrupt vector table. 
 *
 * *****************************************************************************/
void dsp_Init(void);

/* ****************************************************************************
 * @implementation
 * Register a custom ISR for a specific interrupt
 *
 * @param       irq             target irq
 * @param       cb              pointer to custom isr function
 * @return      TRUE            if assignment successful
 * ****************************************************************************/
bool_t dsp_RegisterCustomInterruptCallback(dsp_eInterruptVectorNum_t irqNum, dsp_InterruptCallback_t cb);


#endif /* MOD_DSP_H_ */
