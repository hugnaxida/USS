/* *************************************************************************//**
 * @file		mod_gpio.c
 *
 * @creator		poe
 * @created		27.04.2017
 * @sdfv                Demo Flow
 *
 * @brief  		GPIO module initialsizes GPIOs
 *
 * @purpose
 *
 * TODO: A detailed description of this module
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
 * $Id: mod_gpio.c 394 2019-01-23 15:20:39Z siko $
 *
 * $Revision: 394 $
 *
 ******************************************************************************/


/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_gpio.h"
#include "def_app.h"
/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ******************** FORWARD DECLARATIONS / PROTOTYPES *********************/
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
 *
 * @pre        NVIC (nvic_VectorInterruptControl) and SYSS (syss_SystemState)
 *             have to presented and initialized.n
 *
 * @post       GPIO module is configured for use. GPIOs are configured as Output.
 *
 * @detaildesc
 * Initializes the GPIO hardware module and sets initial I/O configuration.
 * @return     
 * *****************************************************************************/
void gpio_Init(void)
{ 
  GPIO_DATA_OE_SET(0);
  GPIO_DATA_OE_SET(1);

#if defined(FPGA_52417B)
  GPIO_DATA_OE_SET(2);
  GPIO_DATA_OE_SET(3);
#endif
}
