/***************************************************************************//**
 * @file		mod_eeprom_access.c
 *
 * @creator		RPY
 * @created		15.10.2015
 * @sdfv                Demo Flow
 *
 * @brief               EEPROM access module handles write and diagnosis operations to EEPROM
 *
 * @purpose
 *
 * TODO: A detailed description of this module
 *
 *******************************************************************************
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
 *******************************************************************************
 *
 * $Id: mod_eeprom_access.c 409 2019-02-11 13:55:27Z poe $
 *
 * $Revision: 409 $
 *
 ******************************************************************************/


/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_eeprom_access.h"
#include "mod_app.h"
#include "mod_eeprom.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define LOC_EE_ACCESS_STEP_BYTES        2u
#define LOC_EE_ACCESS_STEP_WORDS        1u
#define LOC_EE_ACCESS_WORD_COUNT        2u
#define LOC_EE_MARGIN_LOWER_BOUND       0x0000u
#define LOC_EE_MARGIN_UPPER_BOUND       0xFFFFu
#define LOC_EE_PROG_VMIN                182u  /* minimum VSUP before EEPROM programming 7,1V (see Appl.Note 0190): (7,1V*A_{HV})*(2^(10bit))/(40V_{max}*A_{HV}) =^182 */

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ******************** FORWARD DECLARATIONS / PROTOTYPES *********************/
/* ****************************************************************************/

/* *************************************************************************//**
 * @brief
 * checks if address corresponds to eeprom memory area
 *
 * make sure this function is never inlined since this could lead to implicit constant propagation
 *
 * @param    pass             password to set statemachine
 * @param    unlockcnt        unlock counter for eeprom state machine
 * @param    mode             eeprom operation-mode margin_read, program or erase
 * @param    lock_l           Lock (lower) config register
 * @param    lock_u           Lock (upper) config register
 * @param    lock_l_freeze    Lock (lower) freeze register
 * @param    lock_u_freeze    Lock (upper) freeze register
 *
 * @return   none
 * ****************************************************************************/
static void loc_ConfEEStateMachine(eeprom_Password_t pass, uint8_t unlockcnt, uint8_t mode, eeprom_LockBits_t lock_l, eeprom_LockBits_t lock_u, eeprom_LockBits_t lock_l_freeze, eeprom_LockBits_t lock_u_freeze) __attribute__((noinline));

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* *************************************************************************//**
 * @brief
 * checks if address corresponds to eeprom memory area
 *
 * @return    true if address in inside eeprom area
 *            false if not
 * ****************************************************************************/
static inline eeprom_Bool_t loc_isInsideEE(uintptr_t addr)
{
  return ( ( addr >= EE_START ) && ( addr <= EE_END ) ? TRUE : FALSE );
}

/* *************************************************************************//**
 * @brief
 * checks if address corresponds to eeprom memory area
 *
 * @param    pass             password to set statemachine
 * @param    unlockcnt        unlock counter for eeprom state machine
 * @param    mode             eeprom operation-mode margin_read, program or erase
 * @param    lock_l           Lock (lower) config register
 * @param    lock_u           Lock (upper) config register
 * @param    lock_l_freeze    Lock (lower) freeze register
 * @param    lock_u_freeze    Lock (upper) freeze register
 *
 * @return   none
 * ****************************************************************************/
static void loc_ConfEEStateMachine(eeprom_Password_t pass, uint8_t unlockcnt, uint8_t mode, eeprom_LockBits_t lock_l, eeprom_LockBits_t lock_u, eeprom_LockBits_t lock_l_freeze, eeprom_LockBits_t lock_u_freeze)
{
  EEPROM_CTRL_LOCK_CNT = 0;
  
  eeprom_Password_t masked_pass = (pass & 0xff00u);
    
  /* Push EEPROM state machine forward. */
  while (unlockcnt > 0) 
  {  
    EEPROM_CTRL_LOCK_CNT = pass;  // 9x -> ready for LOCK_L/LOCK_U changes (if unlockcnt properly set to 9)
    --unlockcnt;
  }  
  
  EEPROM_CTRL_LOCK_L = lock_l | masked_pass;
  EEPROM_CTRL_LOCK_U = lock_u | masked_pass;
  
  /* Push EEPROM state machine forward. */
  EEPROM_CTRL_LOCK_CNT = pass; // 10
  EEPROM_CTRL_LOCK_CNT = pass; // 11  -> ready for LOCK_U_FREEZE changes 

  EEPROM_CTRL_LOCK_L_FREEZE = lock_l_freeze | masked_pass;
  EEPROM_CTRL_LOCK_U_FREEZE = lock_u_freeze | masked_pass;

  /* Push EEPROM state machine forward. */
  EEPROM_CTRL_LOCK_CNT = pass; // 12  -> ready for MODE changes 
  
  EEPROM_CTRL_MODE = mode | masked_pass; 
  
  /* Push EEPROM state machine forward. */
  EEPROM_CTRL_LOCK_CNT = pass; // 13 ->  ready for access
}

static inline void loc_ResetEEStateMachine()
{
  /* Reset EEPROM HW module state machine */
  EEPROM_CTRL_LOCK_CNT = 0;
}


static bool_t loc_WriteDoubleWord(eeprom_Password_t pass, eeprom_Address_t dptr, uint16_t datalow, uint16_t datahigh, uint8_t mode, eeprom_LockBits_t lock_l, eeprom_LockBits_t lock_u)
{
  /* pass (EE_PASSWORD) handles the eeprom access password (upper byte) and the lock_counter (lower byte) to write on eeprom */
  uint8_t unlockcnt = (uint8_t) (pass & 0x00FFu ) ;   // should be 0x09

  ++pass;                               // should be 0xA50A
  
  /*kick the dog see "SM53 - Program Flow Watchdog" */
  wdg_Trigger();
  
  if ( eeprom_ResetIP() != TRUE ) /* optionally try to reset and reenable MTP IP, if needed */ 
  {
    return FALSE; 
  }
  else {}
  
  loc_ConfEEStateMachine(pass,unlockcnt,mode,lock_l,lock_u,0,0); 
    
  *dptr = datalow;
  __DSB();
  
  /* Wait typically 8ms until EEPROM write access is finished */
  while ( ( EEPROM_CTRL_STATUS & 0x01u ) == 1u  ) { }; /* wait as long as busy, EEPROM_CTRL will timeout automatically, in case of IP failure */
  
  if (mode != E_EEPROM_CTRL_MODE_ERASE) /* if not erasing write second word */ 
  {
    *(dptr+1) = datahigh;
    __DSB();
    
    /* Wait typically 8ms until EEPROM write access is finished */
    while ( ( EEPROM_CTRL_STATUS & 0x01u ) == 1u  ) { };  /* wait as long as busy, EEPROM_CTRL will timeout automatically, in case of IP failure */
  }
  
  /* Reset EEPROM HW module state machine */
  loc_ResetEEStateMachine();
  
  /* Examine programming success */  
  return eeprom_CheckIPState();
}

static bool_t loc_MarginReadDoubleWord(eeprom_Password_t pass, eeprom_Address_t dptr, uint16_t prechargedatalow, uint16_t prechargedatahigh, uint16_t *datalow, uint16_t *datahigh)
{
  /* pass (EE_PASSWORD) handles the eeprom access password (upper byte) and the lock_counter (lower byte) */
  uint8_t unlockcnt = (uint8_t) (pass & 0x00FFu ) ;   // should be 0x09

  ++pass;                               // should be 0xA50A
  
  if ( eeprom_ResetIP() != TRUE ) /* optionally try to reset and reenable MTP IP, if needed */ 
  {
    return FALSE; 
  }
  else {}
  
  loc_ConfEEStateMachine(pass,unlockcnt,E_EEPROM_CTRL_MODE_MARGIN_READ,0,0,0,0);
  
  /* --> 19/02/11, poe: SMA52417-148  
   * Cast dptr to volatile to prevent
   * mtp readback skipping caused by optimization. 
   */
  *dptr = prechargedatalow;       /* IP seams to require some prechage with expected data */ 
  __DSB();
  *datalow  = *(volatile uint16_t*)dptr;              // in case of failure read will time out at some point, so access will not block for ever. (eeprom_CheckIPState() will discover this condition, later)
  __DSB();
    
  *(dptr+1) = prechargedatahigh;  /* IP seams to require some prechage with expected data */ 
  __DSB();
  *datahigh = *((volatile uint16_t*)dptr+1);          // 
  __DSB();
  /* --> 19/02/11, poe: SMA52417-148 */
    
  /* Reset EEPROM HW module state machine */
  loc_ResetEEStateMachine();
      
  /* Examine programming success */  
  return eeprom_CheckIPState();
}

eeprom_Bool_t eeprom_CheckIPState(void)
{
  if ( ( ( EEPROM_CTRL_STATUS & 0x01u ) == 0u ) && ( EEPROM_CTRL_IRQ_STATUS == 0x0000u ) ) // if busy flag is gone, and no errors have occured MTP is up and running. 
  { 
		return TRUE; // IP in a sane state... 
  }
  else
  {
    eeprom_ResetIP(); // try to recover, but report this failure...
		return FALSE;
	}
}

eeprom_Bool_t eeprom_ResetIP(void)
{  
  if ( ( EEPROM_CTRL_STATUS & 0x01u ) == 1 ) /* if status is already "1" some previous access has failed and locked the EEPROM_CTRL, this will likely not change anymore, so try reset IP, if possible */ 
  {
    EEPROM_CTRL_IP_ENABLE = 0xA500u; // disable MTP IP core.		
    EEPROM_CTRL_IP_ENABLE = 0xA501u; // reenable MTP IP core.

    while ( ( EEPROM_CTRL_STATUS & 0x01u ) == 1  ) { }; /* will need some cycles until IP gets ready again ... wait as long as busy set */
  }
    
  /* reset IRQ flags in any case, to be able to use eeprom_CheckIPState() once further access have been performed */
  EEPROM_CTRL_IRQ_MASK   = 0x0000; // disable all EE IRQs
  EEPROM_CTRL_IRQ_STATUS = E_EEPROM_CTRL_IRQ_STATUS_TIMEOUT
                         | E_EEPROM_CTRL_IRQ_STATUS_INVALID_ADDR
                         | E_EEPROM_CTRL_IRQ_STATUS_IP_OFF_ACCESS;  // clear all IRQ status flags.
    
  return TRUE; // MTP should be in a sane state now.     
}


void eeprom_GetLock(eeprom_LockBits_t *lock_l, eeprom_LockBits_t *lock_u)
{
  if (lock_l != NULL)
  {
    *lock_l = (EEPROM_CTRL_LOCK_L & 0xffu);
  }
  else{}

  if (lock_u != NULL)
  {
    *lock_u = (EEPROM_CTRL_LOCK_U & 0xffu);
  }
  else{}
}


void eeprom_SetLock(eeprom_Password_t pass, eeprom_LockBits_t lock_l, eeprom_LockBits_t lock_u,eeprom_LockBits_t lock_l_freeze,eeprom_LockBits_t lock_u_freeze)
{    
  if (pass == EE_PASSWORD ) 
  {
    /* pass (EE_PASSWORD) handles the eeprom access password (upper byte) and the lock_counter (lower byte) */
    uint8_t unlockcnt = (uint8_t)(pass & 0x00FFu);   // should be 0x09  
    ++pass;                               // should be 0xA50A
      
    loc_ConfEEStateMachine(pass,unlockcnt,0,lock_l,lock_u,lock_l_freeze,lock_u_freeze); // stay in normal mode, but configure locks. 

    /* Reset EEPROM HW module state machine */
    loc_ResetEEStateMachine();
  }
}

eeprom_Bool_t eeprom_Write(eeprom_Password_t pass, eeprom_cpData_t sptrbyte, eeprom_Address_t dptr, eeprom_Length_t bytes, eeprom_LockBits_t lock_l, eeprom_LockBits_t lock_u)
{    
  /* initial password check */
  if (pass != EE_PASSWORD ) 
  {
    return(FALSE);
  }
  else {}
  
  /* check length
     - check number of words
     - check even numer of words (double word programming supported only)
  */
  if (bytes == 0 || ((bytes & EE_ALIGNMENT_MASK) != 0))
  {
    return(FALSE);
  }
  else {}

  /* check source pointer
     - check if valid
     - check if source values are not going to be read from EE
  */
  if ( (sptrbyte == NULL) ||
       (loc_isInsideEE((uintptr_t)sptrbyte) != FALSE) ||
       (loc_isInsideEE(((uintptr_t)sptrbyte) + (bytes - 1)) != FALSE))
  {
    return(FALSE);
  }
  else {}
  
  /* check destination pointer
     - check if valid
     - check double word alignment
     - check if value fits EE area
  */
  if ( (dptr == NULL) ||
       (((uintptr_t)dptr & EE_ALIGNMENT_MASK) != 0) ||
       (loc_isInsideEE((uintptr_t)dptr) == FALSE) ||
       (loc_isInsideEE(((uintptr_t)dptr) + (bytes - 1)) == FALSE))
  {
    return(FALSE);
  }
  else {}
  
  while (bytes>0)
  {
    uint16_t srcdatalow   = sptrbyte[0] | (((uint16_t)sptrbyte[1])<<8);
    uint16_t srcdatahigh  = sptrbyte[2] | (((uint16_t)sptrbyte[3])<<8);
        
    uint16_t readbackdatalow = 0u;
    uint16_t readbackdatahigh = 0u;
    
    uint16_t readbackLowerBoundLowWord = 0u;
    uint16_t readbackLowerBoundHighWord = 0u;

    uint8_t  retrycount = EE_RETRY_COUNT;
    
    while( retrycount > 0 )
    {    
      /* margin read before erasing words to check if doubleword is already erased */
      if (loc_MarginReadDoubleWord(pass,dptr,LOC_EE_MARGIN_LOWER_BOUND,LOC_EE_MARGIN_LOWER_BOUND,&readbackLowerBoundLowWord,&readbackLowerBoundHighWord) != TRUE)
      { --retrycount; continue; }
      else {} 
      if (loc_MarginReadDoubleWord(pass,dptr,LOC_EE_MARGIN_UPPER_BOUND,LOC_EE_MARGIN_UPPER_BOUND,&readbackdatalow,&readbackdatahigh) != TRUE)
      { --retrycount; continue; }
      else {} 
      
      /* check vsup before writing on eeprom */
      if (app_CheckVsup() < LOC_EE_PROG_VMIN)
      { 
        --retrycount; continue; 
      }
      else {}
      
      /* check if doubleword is already erased */
	  /* --> 19/02/11, poe: SMA52417-148
	   * Cast to uint32_t will always result in an unsatisfied condition for 0xFFFF readback values, 
           * as the the 16bit compare value will always be missing the upper halfword (defaulted to 0x0000 --> 0x0000FFFF != 0xFFFFFFFF).
           * So an additional cast to uint16_t of the negated readback value will remove the upper halfword (0xFFFFFFFF --> 0xFFFF).
	   */
      if ( (readbackdatalow == ((uint16_t)~(uint32_t)readbackLowerBoundLowWord)) && (readbackdatahigh == ((uint16_t)~(uint32_t)readbackLowerBoundHighWord)) )
	   /* --> 19/02/11, poe: SMA52417-148 */
      { 
        /* doubleword already erased */
      }
      else 
      { 
        /* erase eeprom doubleword */
        if (loc_WriteDoubleWord(pass,dptr,EE_ERASED_VALUE,EE_ERASED_VALUE,E_EEPROM_CTRL_MODE_ERASE,lock_l,lock_u) != TRUE)           
        { --retrycount; continue; }
        else {}
      }              

      /* check vsup before writing on eeprom */
      if (app_CheckVsup() < LOC_EE_PROG_VMIN)
      { 
        --retrycount; continue; 
      }
      else {}
      
      /* write ram-data doubleword to eeprom */
      if (loc_WriteDoubleWord(pass,dptr,srcdatalow,srcdatahigh,E_EEPROM_CTRL_MODE_PROGRAM,lock_l,lock_u) != TRUE)      
      { --retrycount; continue; }
      else {}      
      
      /* check written data is valid */
      if (loc_MarginReadDoubleWord(pass,dptr,srcdatalow,srcdatahigh,&readbackdatalow,&readbackdatahigh) != TRUE)
      { --retrycount; continue; }
      else {}      
      
      /* check if read lead to a failure on MTP-IP level. (checks state of state-machine) */
      if ( eeprom_CheckIPState() == FALSE ) 
      { --retrycount; continue; }
      else {}      
      
      /* make plausibility check of margin read results */
      if (readbackdatalow != srcdatalow || readbackdatahigh != srcdatahigh)
      { --retrycount; continue; }
      else { break; }              
    } 

    if ( retrycount == 0 )    
    { return(FALSE); }
    else {}      
               
    dptr     += LOC_EE_ACCESS_STEP_WORDS * LOC_EE_ACCESS_WORD_COUNT;
    
    sptrbyte += LOC_EE_ACCESS_STEP_BYTES * LOC_EE_ACCESS_WORD_COUNT;
    bytes    -= LOC_EE_ACCESS_STEP_BYTES * LOC_EE_ACCESS_WORD_COUNT;
  }
  
  return(TRUE);
}

eeprom_Bool_t eeprom_Erase(eeprom_Password_t pass, eeprom_Address_t dptr, eeprom_Length_t bytes, eeprom_LockBits_t lock_l, eeprom_LockBits_t lock_u)
{  
  static const uint8_t zero_buf[4] = { EE_ERASED_VALUE, EE_ERASED_VALUE, EE_ERASED_VALUE, EE_ERASED_VALUE };
  
  if (bytes == 0 || ((bytes & EE_ALIGNMENT_MASK) != 0))
  {
    return(FALSE);
  }
  else {}
  
  while(bytes>0)
  {
    if (eeprom_Write(pass, zero_buf, dptr, sizeof(zero_buf), lock_l, lock_u) != TRUE) 
    { return(FALSE); }
    else {}    
    
    dptr     += LOC_EE_ACCESS_STEP_WORDS * LOC_EE_ACCESS_WORD_COUNT; 
    
    bytes    -= LOC_EE_ACCESS_STEP_BYTES * LOC_EE_ACCESS_WORD_COUNT;    
  }
  
  return(TRUE);     
}

eeprom_Bool_t eeprom_Initialize(eeprom_MarginReadTrim_t mrtrim)
{
  if (mrtrim > 8) { return FALSE; }
  else {}
  
  if ( eeprom_ResetIP() != TRUE ) { return FALSE; }
  else {}
    
  EEPROM_CTRL_MARGIN_TRIM = 0xA500u | ( mrtrim & 0x0007u );
      
  return TRUE;    
}

