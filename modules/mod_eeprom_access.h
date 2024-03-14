/***************************************************************************//**
 * @file			mod_eeprom_access.h
 *
 * @creator		RPY
 * @created		15.10.2015
 * @sdfv                Demo Flow
 *
 * @brief               EEPROM access module handles write and diagnosis operations to EEPROM (header)
 *
 * @purpose
 *
 * : A detailed description of this module
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
 * $Id: mod_eeprom_access.h 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
 *
 ******************************************************************************/

#ifndef EEPROM_ACCESS_H_
#define EEPROM_ACCESS_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "el_types.h"
#include "mod_wdg.h"
/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
typedef bool_t               eeprom_Bool_t;
typedef uint16_t *           eeprom_Address_t;
typedef uint32_t             eeprom_Length_t;

typedef uint8_t *            eeprom_pData_t;
typedef const uint8_t *      eeprom_cpData_t;

typedef uint8_t              eeprom_LockBits_t;

typedef uint16_t             eeprom_Password_t;

typedef uint8_t              eeprom_MarginReadTrim_t;

#define EE_ERASED_VALUE      0x0000u

#define EE_PASSWORD          0xA509u    // password used to access EEPROM_CTRL registers and statemachine count.

#define EE_ALIGNMENT         4u         // erase works on double words only, therefore programming as well. 
#define EE_ALIGNMENT_MASK    3u         // 

#define EE_SIZE              0x0100u

#define EE_START             0x48000000u
#define EE_END               ( (EE_START) + (EE_SIZE) - 1 )

#define EE_RETRY_COUNT       3 

/* ****************************************************************************/
/* ********************************* FUNCTIONS ********************************/
/* ****************************************************************************/

/***************************************************************************//**
 * Write block on EEPROM
 *
 * @param     pass    EEPROM hardware password (see .h file)
 * @param     sptr    pointer to source (absolute)
 * @param     dptr    pointer to destination (absolute)
 * @param     bytes   number of byte to write to EEPROM
 * @param     lock_l  set this to 0
 * @param     lock_u  set this to 0
 *
 * @return    bool_t  true if write was successful
 ******************************************************************************/
eeprom_Bool_t eeprom_Write(eeprom_Password_t pass, eeprom_cpData_t sptr, eeprom_Address_t dptr, eeprom_Length_t bytes, eeprom_LockBits_t lock_l, eeprom_LockBits_t lock_u);


/***************************************************************************//**
 * Erase block on EEPROM
 *
 * @param     pass    EEPROM hardware password (see .h file)
 * @param     dptr    pointer to destination (absolute)
 * @param     bytes   number of byte to write to EEPROM
 * @param     lock_l  set this to 0
 * @param     lock_u  set this to 0
 *
 * @return    bool_t  true if erase was successful
 ******************************************************************************/
eeprom_Bool_t eeprom_Erase(eeprom_Password_t pass, eeprom_Address_t dptr, eeprom_Length_t bytes, eeprom_LockBits_t lock_l, eeprom_LockBits_t lock_u);

/***************************************************************************//**
 * Reset EEPROM hardware if it got stuck
 ******************************************************************************/
eeprom_Bool_t eeprom_ResetIP(void);

/***************************************************************************//**
 * Checks if EEPROM hardware got stuck and resets it if needed
 *
 * @return    eeprom_Bool_t     false if hw got stuck
 ******************************************************************************/
eeprom_Bool_t eeprom_CheckIPState(void);



/** unneeded **/
eeprom_Bool_t eeprom_Initialize(eeprom_MarginReadTrim_t mrtrim);
/** unneeded **/
void eeprom_SetLock(eeprom_Password_t pass, eeprom_LockBits_t lock_l, eeprom_LockBits_t lock_u,eeprom_LockBits_t lock_l_freeze,eeprom_LockBits_t lock_u_freeze);
/** unneeded **/
void eeprom_GetLock(eeprom_LockBits_t *lock_l, eeprom_LockBits_t *lock_u);

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ********************* EXTERNAL FUNCTIONS / INTERFACE ***********************/
/* ****************************************************************************/

#endif /* FLASH_ACCESS_H_ */
