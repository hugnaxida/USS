/* *************************************************************************//**
 * @file                version.h
 *
 * @creator             
 * @created             
 * @sdfv
 *
 * @brief               SET the FW-Version in Format. 
 *
 * @purpose
 * Numbering suggestion:
 * ++Major: Redesign / Major changes
 * ++Minor: Backward incompatible API changes
 * ++Build: Any change, small/internal bugfixes etc.
 *
 * To define the Minor_FW-Version Number use defines in version_build.h
 *
 * *****************************************************************************
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
 * *****************************************************************************
 *
 * @section history_sec_version_h Revision History
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who  Ver    Comment
 * -------------------------------------------------------------------
 * 18/05/23 F   FRK  1.x    changed to major plus SVN build no. (only 16 bit available)
 * 17/05/18 F   POE  1.0.0  Initial project release
 * -------------------------------------------------------------------
 * @endverbatim
 *
 * Revision: $Revision: 424 $
 *
 * ****************************************************************************/
#ifndef VERSION_H_
#define VERSION_H_

#include "version_build.h"


#define FW_VERSION_MAJOR         (0u)
#define FW_VERSION_MAJOR_STR     "0" 



#define FW_VERSION_BUILD         SOFTWAREVERSION
#define FW_VERSION_BUILD_STR     SOFTWAREVERSION_STRING

#define FW_VERSION_PROJECT       "52417DemoFW"
#define FW_VERSION_AUTHOR        "ELMOS Semiconductor AG"

#define FW_VERSION_YEAR          "2019"


#define FW_VERSION_NUMBER        (((uint16_t)(FW_VERSION_MAJOR & 0x000Fu) <<12)|(uint16_t)(FW_VERSION_BUILD & 0x0FFFu)) // Bit: 15-12: Major, 11-0 Build

#define FW_VERSION_STRING        "v"  FW_VERSION_MAJOR_STR "." FW_VERSION_BUILD_STR
#define FW_VERSION_STRING_LONG   FW_VERSION_PROJECT " " FW_VERSION_STRING " (c)" FW_VERSION_YEAR " " FW_VERSION_AUTHOR

#endif
