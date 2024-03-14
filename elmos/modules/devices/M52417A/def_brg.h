/* ------------------------------------------------------------------- */
/** @file def_brg.h
 *
 * @brief Helper definitions for BRG hardware module.
 *
 * Purpose:
 * Provide register access and register value definitions 
 * for BRG hardware module
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
#ifndef _DEF_BRG_H_
#define _DEF_BRG_H_
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

enum brg_eIncrementSelect
{
  brg_eIncrementSelect_LinPeriod        = 0u,
  brg_eIncrementSelect_LinFreq          = 1u
};

typedef enum brg_eIncrementSelect brg_IncrementSelect_t;

enum brg_eBurstStatus
{
  brg_eBurstStatus_Finished             = 0u,
  brg_eBurstStatus_Running              = 1u,
  brg_eBurstStatus_Aborted              = 2u 
};

typedef enum brg_eBurstStatus brg_BurstStatus_t;

enum brg_eBurstType
{
  brg_eBurstType_FixedFreqBrst          = 0u,
  brg_eBurstType_FreqChirp              = 1u,             
  brg_eBurstType_FSKBrst                = 2u,
  brg_eBurstType_MSKBrst                = 3u
};

typedef enum brg_eBurstType brg_BurstType_t;


enum brg_eTDRSourceSelectMode
{
  brg_eTDRSourceSelectMode_Normal       = 0u,
  brg_eTDRSourceSelectMode_Reduced      = 1u
};

typedef enum brg_eTDRSourceSelectMode brg_TDRSourceSelectMode_t;

enum brg_eTDRStatus
{
  brg_eTDRStatus_Normal                 = 0u,
  brg_eTDRStatus_Error                  = 1u
};

typedef enum brg_eTDRStatus brg_TDRStatus_t;

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

#define BRG_ON                          (1u)
#define BRG_OFF                         (0u)

/* ****************************************************************************/
/* ***************************** BURST CONTROL ********************************/
/* ****************************************************************************/


#define BRG_CTRL_DIAG_START()          (BRG_BRG_CTRL_bit.burst_en_diag  = BRG_ON)
#define BRG_CTRL_DIAG_HALT()           (BRG_BRG_CTRL_bit.burst_en_diag  = BRG_OFF)
#define BRG_CTRL_HALT()                (BRG_BRG_CTRL_bit.burst_brk      = BRG_ON)
#define BRG_CTRL_START()               (BRG_BRG_CTRL_bit.burst_en       = BRG_ON)

#define BRG_STATUS_GET()                ((brg_BurstStatus_t)BRG_BRG_CTRL_bit.burst_sta)


/* ****************************************************************************/
/* ***************************** BURST CONFIG *********************************/
/* ****************************************************************************/


#define BRG_CFG_INC_SELECT_SET_LFRQ()   (BRG_BRG_CFG_bit.sel_inc        = brg_eIncrementSelect_LinFreq)
#define BRG_CFG_INC_SELECT_SET_LPER()   (BRG_BRG_CFG_bit.sel_inc        = brg_eIncrementSelect_LinPeriod)
#define BRG_CFG_INC_SELECT_GET()        ((brg_IncrementSelect_t)BRG_BRG_CFG_bit.sel_inc)

#define BRG_CFG_CODE_LEN_SET(num)       (BRG_BRG_CFG_bit.code_len       = (num))
#define BRG_CFG_CODE_LEN_GET()          (BRG_BRG_CFG_bit.code_len)

#define BRG_CFG_BURST_TYPE_SET(num)     (BRG_BRG_CFG_bit.burst_type     = (brg_BurstType_t)(num))
#define BRG_CFG_BURST_TYPE_GET()        ((brg_BurstType_t)BRG_BRG_CFG_bit.burst_type)

#define BRG_CFG_NPULSES_SET(num)        (BRG_BRG_CFG_bit.n_pulses        = (num))
#define BRG_CFG_NPULSES_GET()           (BRG_BRG_CFG_bit.n_pulses)

#define BRG_FC_SET(num)                 (BRG_BRG_FC_bit.f_c             = (num))
#define BRG_FC_GET()                    (BRG_BRG_FC_bit.f_c)

#define BRG_F0_SET(num)                 (BRG_BRG_F0_bit.f_0             = (num))
#define BRG_F0_GET()                    (BRG_BRG_F0_bit.f_0)

#define BRG_F1_SET(num)                 (BRG_BRG_F1_bit.f_1             = (num))
#define BRG_F1_GET()                    (BRG_BRG_F1_bit.f_1)

#define BRG_FDELTA_SET(num)             (BRG_BRG_FDELTA_bit.f_delta     = (num))
#define BRG_FDELTA_GET()                (BRG_BRG_FDELTA_bit.f_delta)

#define BRG_CODE_SET(num)               (BRG_BRG_CODE                   = (num))
#define BRG_CODE_GET()                  (BRG_BRG_CODE)



/* ****************************************************************************/
/* ******************** TRANS DRIVER CURRENT CONTROL **************************/
/* ****************************************************************************/


#define BRG_TDR_CTRL_SEL_INORMAL()         (BRG_TDR_CTRL_bit.sel_isrc       = brg_eTDRSourceSelectMode_Normal)
#define BRG_TDR_CTRL_SEL_IREDUCED()        (BRG_TDR_CTRL_bit.sel_isrc       = brg_eTDRSourceSelectMode_Reduced)
#define BRG_TDR_CTRL_SEL_GET()             ((brg_TDRSourceSelectMode_t)BRG_TDR_CTRL_bit.sel_isrc)

#define BRG_TDR_CTRL_DRV_CURR_SET(num)     (BRG_TDR_CTRL_bit.i_drv         = (num))
#define BRG_TDR_CTRL_DRV_CURR_GET()        (BRG_TDR_CTRL_bit.i_drv)

#define BRG_TDR_STATUS_VTANKOV_GET()       (BRG_TDR_STATUS_bit.vtank_ov) 
#define BRG_TDR_STATUS_DRVS_GET()          ((brg_TDRStatus_t)BRG_TDR_STATUS_bit.drvs_sta) 
#define BRG_TDR_STATUS_DRV2_GET()          ((brg_TDRStatus_t)BRG_TDR_STATUS_bit.drv2_sta) 
#define BRG_TDR_STATUS_DRV1_GET()          ((brg_TDRStatus_t)BRG_TDR_STATUS_bit.drv1_sta) 



#endif
