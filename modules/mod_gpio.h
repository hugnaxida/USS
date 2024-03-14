/* *************************************************************************//**
 * @file		mod_gpio.h
 *
 * @creator		poe
 * @created		27.04.2017
 * @sdfv                Elmos Flow
 *
 * @brief  		GPIO module initialsizes GPIOs (header)
 *
 * @purpose
 *
 * The GPIO Module handling the GPIO configurations.
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
 * $Id: mod_gpio.h 394 2019-01-23 15:20:39Z siko $
 *
 * $Revision: 394 $
 *
 * *****************************************************************************/

#ifndef MOD_GPIO_H_
#define MOD_GPIO_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/

#include "el_types.h"
#include "elmos/modules/devices/M52417A/def_gpio.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* *************************************************************************//**
 * @brief Initialize GPIO module
 *
 * @pre        NVIC (nvic_VectorInterruptControl) and SYSS (syss_SystemState)
 *             have to presented and initialized.n
 *
 * @post       GPIO module is configured for use.
 *
 * @detaildesc
 * Initializes the GPIO hardware module and sets initial I/O configuration.
 * @return     
 * *****************************************************************************/
void gpio_Init(void);

#endif 

