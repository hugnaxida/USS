/***************************************************************************//**
 * @file			el_types.h
 *
 * @creator		sbai
 * @created		06.10.2014
 *
 * @brief  		Provides all basic data type definitions
 *
 * @purpose
 *
 * Provides all basic data type definitions for Elmos's CPU APIs and development
 * on ELMOS'S intelligent ICs.
 *
 * $Id: io_m52417a.h 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
 *
 *****************************************************************************
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
 ******************************************************************************/
 
#ifndef IO_M52417A_H_
#define IO_M52417A_H_

#include "el_types.h"

/* ****************************************************************************/
/* ************************ ARCH DEPENDENT INCLUDES ***************************/
/* ****************************************************************************/

#if defined ( EL_COMPILER_KEIL )
  
  /* use Keil package provided headers */
  #include <m52417a.h>
  #include <el_regs_m52417a.h>

#elif defined ( EL_COMPILER_IAR )

  /* use local modified version for IAR */ 
  #include "io_m52417a_IAR.h"
  #include "el_regs_m52417a_IAR.h"

#elif defined ( EL_COMPILER_GCC )

  /* use local modified version for IAR */
  #include "io_m52417a_IAR.h"
  #include "el_regs_m52417a_IAR.h"

#else
  #error "Unsupported compiler type"	

#endif
	

#endif /* IO_M52417A_H_ */






