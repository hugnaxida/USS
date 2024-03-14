/* ------------------------------------------------------------------- */
/** @file def_syss.h
 *
 * @brief Helper definitions for SYS_STATE hardware module.
 *
 * Purpose:
 * Provide register access and register value definitions 
 * for SYS_STATE hardware module
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
#ifndef _DEF_SYSS_H_
#define _DEF_SYSS_H_
//################################################################################
//  Helper defines
//################################################################################


/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "elmos/includes/io_m52417a.h"
/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/* *****************************************************************************
 * System clock enum
 * *****************************************************************************/
enum syss_eSysClockFrequency
{
  syss_CLockSel_4MHZ	= 0u,
  syss_CLockSel_8MHZ	= 1u,
  syss_CLockSel_12MHZ	= 2u,
  syss_CLockSel_24MHZ	= 3u
};

typedef enum  syss_eSysClockFrequency syss_SysClockFrequency_t;


enum syss_eSysResetEnables
{
  aba=0
  
} ;

typedef enum  syss_eSysResetEnables syss_SysResetEnables_t;

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

#define SYSS_SYS_CLK_SET(num)                      (SYS_STATE->CONTROL.bit.sys_clk_sel = (syss_SysClockFrequency_t)(num)) 
#define SYSS_SYS_CLK_GET()                         (SYS_STATE->CONTROL.bit.sys_clk_sel) 
#define SYSS_DEBUG_ENABLE()                        (SYS_STATE->ENABLE_DEBUG.reg = (0xA561u))

#endif
