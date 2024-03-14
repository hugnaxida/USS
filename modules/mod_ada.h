/***************************************************************************//**
  * @file mod_ada.h
  * @brief ADA configuration and access module (header)
  *
  * Purpose:
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
  * @section history_sec_mod_ada_h Revision History
  * $Id: mod_ada.h 394 2019-01-23 15:20:39Z siko $
  *
  * @verbatim
  * -------------------------------------------------------------------
  * Date     B/F Who Comment
  * ------------------------------------------------------------------- 
  * 17/05/29 (F) POE initial version
  * -------------------------------------------------------------------
  * @endverbatim
  * 
  *
  * @creator      POE
  * @created      2017/05/29
  * 
  * @project      524.17
  * @requested    -
  * @inspector    - 
  * @verification -
  * @version      $Revision: 394 $
  * 
  * 
  * $State: Exp $   
  * $Author: siko $
  * $Date: 2019-01-23 16:20:39 +0100 (Mi, 23 Jan 2019) $

  * $Locker:  $
  * $Url:   $
  *
  * Additional markers:
  *
  *
  *
  */


#ifndef MOD_ADC_H_
#define MOD_ADC_H_

#include "el_types.h"
#include "elmos/modules/devices/M52417A/def_ada.h"

//################################################################################
// ADC

    
  
    
    
//! Initialzation
void ada_Init(void);

uint16_t ada_TriggerSample(ada_ChannelSelect_t ch, ada_SignalSelect_t sig);

#endif
