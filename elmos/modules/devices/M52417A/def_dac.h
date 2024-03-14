/* ------------------------------------------------------------------- */
/** @file def_dac.h
 *
 * @brief Helper definitions for DAC hardware module.
 *
 * Purpose:
 * Provide register access and register value definitions 
 * for DAC hardware module
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
 * 18/08/07 (B) poe 1002 renamed dac_sTsens_cfg struct items.
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
#ifndef _DEF_DAC_H_
#define _DEF_DAC_H_
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
   
enum dac_eDacCtrl
{
  dac_eDacCtrl_Off        = 0u,
  dac_eDacCtrl_REG        = 1u,
  dac_eDacCtrl_ENV        = 2u,
  dac_eDacCtrl_TH         = 3u
};

typedef enum dac_eDacCtrl dac_DacCtrl_t;

enum dac_eDAC
{
  dac_DAC0                = 0u,
  dac_DAC1                = 1u
};

typedef enum dac_eDAC dac_DAC_t;

typedef struct 
{
  uint16_t              dac_TSENS_OFF       : 10;
  uint16_t              dac_TSENS_GAIN      :  6;
} dac_sTsens_cfg;

union dac_uTsens_cfg
{
  dac_sTsens_cfg        tsens_cfg;
  uint16_t              value;
};

typedef union dac_uTsens_cfg dac_Tsens_cfg_t;

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/


/* DAC_CTRL */

#define DAC_CTRL_DAC0_SET(num)                  (DAC_CTRL_CTRL_bit.dac0_cfg  = (dac_DacCtrl_t)(num))
#define DAC_CTRL_DAC0_GET()                     ((dac_DacCtrl_t)DAC_CTRL_CTRL_bit.dac0_cfg)
#define DAC_CTRL_DAC1_SET(num)                  (DAC_CTRL_CTRL_bit.dac1_cfg  = (dac_DacCtrl_t)(num))
#define DAC_CTRL_DAC1_GET()                     ((dac_DacCtrl_t)DAC_CTRL_CTRL_bit.dac1_cfg)

#define DAC_REG0_SET(num)                       (DAC_CTRL_REG0 = (num))
#define DAC_REG1_SET(num)                       (DAC_CTRL_REG1 = (num))



#endif
