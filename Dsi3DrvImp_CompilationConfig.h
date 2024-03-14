/***************************************************************************//**
 * @file      Dsi3DrvImp_CompilationConfig.h
 *
 * @creator   poe
 * @created   23.03.2018
 *
 * @brief     Compilation-changing settings of the Elmos DSI3 Driver.
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
 *
 * @section history_sec_Dsi3DrvImp_CompilationConfig_h Revision History
 * $Id: Dsi3DrvImp_CompilationConfig.h 392 2019-01-22 09:59:18Z siko $
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who  Ver  Comment
 * -------------------------------------------------------------------
 * 18/03/23 (F) POE  1000 initial version
 * -------------------------------------------------------------------
 * @endverbatim
 *
 * @creator      POE
 * @created      2018/03/23
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
 *******************************************************************************/

#ifndef DSI3DRVIMP_COMPILATIONCONFIG_H_
#define DSI3DRVIMP_COMPILATIONCONFIG_H_

#include "el_types.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

#if defined (USE_FPGA)
/**< use compiler flags for FPGA target (DAC & GPIO2|3 separated, DSI3-AA workaround */
  #pragma message("***>> Compiling for FPGA (USE_FPGA = 1) - DAC & DSI3 bus are configured for FPGA use.")
#else
  #pragma message("***>> Compiling for real chip (USE_FPGA = 0) - DAC & DSI3 bus are configured for IC use.")
#endif
/***************************************************************************//**
 * Control access to DSI3 Driver modules via the global interface functions
 * structs.
 ******************************************************************************/
#define DSI3BUSIMP_EXT_IFFUN_STRCT_ACCESS               1u


/* ****************************************************************************/
/*                               DSI3 BUS LAYER                               */
/* ****************************************************************************/

/* Option for substitute AA approach */
#if defined (USE_FPGA)
  #define ENABLE_FPGA_AUTOADDRESSING      1u      /**< 1 - use AutoAddressing for relais based fpga boards */
#else
 #define ENABLE_FPGA_AUTOADDRESSING       0u      /**< 1 - use AutoAddressing for relais based fpga boards */
#endif

#define DSI3_MAX_NUMBER_OF_CALLBACK_TABLES                      (    1u)        /**< Maximal allowed count of callback tables which can be added to the DSI3 bus. */
  
/* Response time relative to start of sync signal */
#define DSI3BUSIMP_PDCM_RESPONSE_DURATION_DEFAULT               ( 1000u)        /**< Default: overall PDCM response time for _all_ nodes (us) */
#define DSI3BUSIMP_PDCM_SLOT_DURATION_DEFAULT	                (  122u)        /**< Default: PDCM response time of a single slot (us) */
#define DSI3BUSIMP_PDCM_START_OFFSET_DEFAULT	                (   50u)        /**< Default: PDCM first response slot time offset (us) */   
#define DSI3BUSIMP_DEBOUNCE                                     (dsi3_eDebounceValue_166NS)


/*******************************************************************************************/
#ifdef DEVICE_52417A 
#define DSI3_BUSIMP_ENABLE_TIMERA_RAMP 1u
//#warning !!!COMPILING FOR M524.17A!!!
#endif


#endif /* LINDRVIMP_COMPILATIONCONFIG_H_ */
