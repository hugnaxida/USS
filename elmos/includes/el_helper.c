/***************************************************************************//**
 * @file			el_helper.c
 *
 * @creator		sbai
 * @created		17.06.2015
 *
 * @brief  		TODO: Short description of this module
 *
 * @purpose
 *
 * TODO: A detailed description of this module
 *
 * $Id: el_helper.c 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
 *
 ******************************************************************************
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

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "el_helper.h"

#if defined ( __ICC430__ )
  #include "el_helper_H430_IAR.c"
  
#elif defined ( __ICCARM__ )
  #include "el_helper_ACM0_IAR.c"
  
#elif defined ( __CC_ARM )
  #include "el_helper_ACM0_Keil.c"
  
#else
  #error "Unsupported compiler type"	

#endif

