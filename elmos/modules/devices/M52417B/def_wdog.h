/* ------------------------------------------------------------------- */
/** @file def_wdog.h
 *
 * @brief Helper definitions for WDOG hardware module.
 *
 * Purpose:
 * Provide register access and register value definitions 
 * for DSP hardware module
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
 * 18/07/03 (B) poe 1002 fixed failed password setting
 * 18/03/23 (F) poe 1001 first creation
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
#ifndef _DEF_WDOG_H_
#define _DEF_WDOG_H_
//################################################################################
//  Helper defines
//################################################################################


/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include <io_m52417b.h>
/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define WDOG_PWD                        (0xA500u)

#define WDOG_CONTROL_RUN_ENABLE_BITMASK (0x01u)

#define WDOG_CONTROL_RESTART_BITMASK    (0x02u)
#define WDOG_CONTROL_RESTART_VALUE      (0x02u)

#define WDOG_WINDOW_SIZE_BITMASK        (0x0Fu)

#define WDOG_CONTROL_RUN_ENABLE()       (WDOG_CONTROL = WDOG_PWD | E_WDOG_CONTROL_RUN_ENABLE)
#define WDOG_CONTROL_RUN_ENABLE_GET()   (WDOG_CONTROL & WDOG_CONTROL_RUN_ENABLE_BITMASK)
#define WDOG_CONTROL_RESTART()          (WDOG_CONTROL = WDOG_PWD | E_WDOG_CONTROL_RESTART)


#define WDOG_WINDOW_SIZE_SET(num)       (WDOG_WINDOW_bit.size = (num))
#define WDOG_WINDOW_SIZE_GET()          (WDOG_WINDOW_bit.size)
#define WDOG_WINDOW_ENABLE()            (WDOG_WINDOW_bit.enable = 0x01u)
#define WDOG_WINDOW_DISABLE()           (WDOG_WINDOW_bit.enable = 0x00u)

#define WDOG_PRESCALE_SET(num)          (WDOG_PRESCALER_bit.val = (uint8_t)(num))
#define WDOG_PRESCALE_GET()             (WDOG_PRESCALER_bit.val)

#define WDOG_RELOAD_SET(num)            (WDOG_RELOAD_bit.val = (uint16_t)(num))
#define WDOG_RELOAD_GET()               (WDOG_RELOAD_bit.val)

#define WDOG_COUNTER_GET()              (WDOG_COUNTER)
#endif
