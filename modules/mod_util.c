/***************************************************************************//**
 * @file      mod_util.c
 *
 * @creator   KeLe
 * @created   22.11.2017
 *
 * @brief     Useful Functions
 *
 * @purpose
 *
 * Useful cross-module functions.
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
 ******************************************************************************/

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_util.h"
#include "def_app.h"
#include "mod_err.h"
#include "def_brg.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define BRG_FC_STEP_SIZE                  (5722u)                   /**< Adjustment step size in Hz */

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

uint16_t util_calculateDmaMemoryOffset(void* pointer)
{
  uint32_t tmp  = (uint32_t)(uint32_t*)pointer;          /* get value of pointer */
  /* check if the pointer is located in SRAM memory */
  if((tmp >= SRAM_BASE_ADDRESS) && (tmp < SYSROM_BASE_ADDRESS))
  {
    tmp   = tmp & 0x0000FFFFu;               /* Get memory offset */
  }
  else
  {
    /* the pointer was not in range. set to default ... */
    tmp   = 0u;
    /* ... and call the ErrorHandler */
    err_ErrorHandler(ERR_MODLIST_UTIL);
  }
  return (uint16_t)tmp;
}


/* **************************************************************************//**
 * @brief
 * Calculate the currently set transducer frequency
 *
 * @return      currently set transducer_frequency
 * ****************************************************************************/
uint32_t util_CalcBurstFrequency(void)
{
  /* calculate burst frequency
   *
   * formula:
   * fc= BRG_FC* f_STEP
   * */
  
  /*-> 18/04/09/frk: (JIRA SMA52417-87) corrected calculation (division by 1000 was missing) */
  return (BRG_BRG_FC_bit.f_c * BRG_FC_STEP_SIZE) / 1000;
  /*<- 18/04/09/frk */
}


