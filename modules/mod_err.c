/***************************************************************************//**
 * @file    mod_err.c
 *
 * @creator   StSl
 * @created   10.11.2017
 *
 * @brief     Error module
 *
 * @purpose
 *
 * This module contains the error memory and provides interfaces to set and get
 * error information
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
 * $Id: mod_err.c 396 2019-01-24 15:15:06Z siko $
 *
 * $Revision: 396 $
 *
 * SM25: Indicate errors (Part 2 of 2)
 * (for details see SafetyManual)
 *
 ******************************************************************************/


/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_err.h"
/* ****************************************************************************/
/* **************************** CUSTOM INCLUDES *******************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/
typedef struct
{
  err_uHwErrStatusInf1_t      hwErr1;         /**< HwErr status information 1 */
  err_uHwErrStatusInf2_t      hwErr2;         /**< HwErr status information 2 */
  err_uComErrStatus_t         comErr;         /**< ComErr status information */
} err_sErrorData_t;

/* ****************************************************************************/
/* ***************************** GLOBAL VARIABLES *****************************/
/* ****************************************************************************/
err_sErrorData_t loc_errStatus;
uint16_t error_line;

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* ************************** FUNCTION PROTOTYPES *****************************/
/* ****************************************************************************/

/* ***************************************************************************
 * @brief
 * Set Hardware Error Flag
 *
 * Sets the given Hardware Error Flag in HwErr Register 1 and 2
 *
 * @param       err1              Hardware Error Flag in HwErr Register 1 to be set
 * @param       err2              Hardware Error Flag in HwErr Register 2 to be set
 *
 * @return      none
 * ****************************************************************************/
void err_SetHwErrorFlag(err_eHwErr1_t err1, err_eHwErr2_t err2)
{
  if(ERR_NO_ERROR1 != err1)
  {
    loc_errStatus.hwErr1.rawData |= (1 << err1);
  }
  else
  {
    /* nothing to do here */
  }

  if(ERR_NO_ERROR2 != err2)
  {
    loc_errStatus.hwErr2.rawData |= (1 << err2);
  }
  else
  {
    /* nothing to do here */
  }
}

/* ***************************************************************************
 * @brief
 * Set Communication Error Flag
 *
 * Sets the given Communication Error Flag in ComErr Register
 *
 * @param       err              Communication Error Flag in ComErr Register
 *
 * @return      none
 * ****************************************************************************/
void err_SetComErrorFlag(err_eComErr_t err)
{
  loc_errStatus.comErr.rawData |= (1 << err);
}

/* ***************************************************************************
 * @brief
 * Get Hardware Error Flag 1
 *
 * Returns the whole HwErr Register 1 and resets it
 *
 * @return      err_uHwErrStatusInf1_t        HwErr Register 1
 * ****************************************************************************/
err_uHwErrStatusInf1_t err_GetHwErrorFlag1(void)
{
  err_uHwErrStatusInf1_t err = loc_errStatus.hwErr1;
  loc_errStatus.hwErr1.rawData = 0;
  return err;
}

///* ***************************************************************************
// * @brief
// * Get Hardware Error Flag 1 without reset (for selftest)
// *
// * Returns the whole HwErr Register 1
// *
// * @return      err_uHwErrStatusInf1_t        HwErr Register 1
// * ****************************************************************************/
//uint16_t err_HwErrorFlag1Info(void)
//{
//  uint16_t err = loc_errStatus.hwErr1.rawData;
//  return err;
//}

/* ***************************************************************************
 * @brief
 * Get Hardware Error Flag 2
 *
 * Returns the whole HwErr Register 2 and resets it
 *
 * @return      err_uHwErrStatusInf2_t        HwErr Register 2
 * ****************************************************************************/
err_uHwErrStatusInf2_t err_GetHwErrorFlag2(void)
{
  err_uHwErrStatusInf2_t err = loc_errStatus.hwErr2;
  loc_errStatus.hwErr2.rawData = 0;
  return err;
}

///* ***************************************************************************
// * @brief
// * Get Hardware Error Flag 2 without reset (for selftest)
// *
// * Returns the whole HwErr Register 2
// *
// * @return      err_uHwErrStatusInf2_t        HwErr Register 2
// * ****************************************************************************/
//uint16_t err_HwErrorFlag2Info(void)
//{
//  uint16_t err = loc_errStatus.hwErr2.rawData;
//  return err;
//}

/* ***************************************************************************
 * @brief
 * Get Communication Error Flag
 *
 * Returns the whole ComErr Register and resets it
 *
 * @return      err_uComErrStatus_t        ComErr Register
 * ****************************************************************************/
err_uComErrStatus_t err_GetComErrorFlag(void)
{
  err_uComErrStatus_t err = loc_errStatus.comErr;
  loc_errStatus.comErr.rawData = 0;
  return err;
}

///* ***************************************************************************
// * @brief
// * Get Communication Error Flag without reset (for selftest)
// *
// * Returns the whole ComErr Register
// *
// * @return      err_uComErrStatus_t        ComErr Register
// * ****************************************************************************/
//uint16_t err_ComErrorFlagInfo(void)
//{
//  uint16_t err = loc_errStatus.comErr.rawData;
//  return err;
//}

/* ***************************************************************************
 * @brief
 * Get Global Error Flag
 *
 * Indicates if one of the error flags in HwErr Register 1 or 2 is set
 *
 * @return      bool_t        true if any error flag was set
 *                            false if no error flag was set
 * ****************************************************************************/
bool_t err_GetGlobalHwErrFlag(void)
{
  bool_t retval = FALSE;
  retval = ((loc_errStatus.hwErr1.rawData > 0) || (loc_errStatus.hwErr2.rawData > 0));
  return retval;
}

/* ***************************************************************************
 * @brief
 * Get Global Communication Error Flag
 *
 * Indicates if one of the error flags in ComErr Register is set
 *
 * @return      bool_t        true if any error flag was set
 *                            false if no error flag was set
 * ****************************************************************************/
bool_t err_GetGlobalComErrFlag(void)
{
  bool_t retval = false;
  retval = loc_errStatus.comErr.rawData > 0;
  return retval;
}

/* ***************************************************************************
 * @brief
 * Error Handler
 *
 * Can be called if unexpected situations occurre
 * Gets called by the err_ErrorHandler() macro
 *
 * @param       line            The line if the source code file in which the error occurred
 * @param       file            The file in which the error occurred
 * @return      none
 * ****************************************************************************/
void err_ErrorHandlerExt(uint32_t line, err_eModuleList file)
{
  /* a critical error occurred. Handle it */
  uint32_t i = 1u;
  do
  {
    i = (line + file) % 0xFFu;
  }while(i < 0xFFFFFFFFu);
}

/* ***************************************************************************
 * @brief
 * Getter function for VSUP error flag
 *
 * @param       
 * @return      bool_t          VSUP Error flag
 * ****************************************************************************/
bool_t err_getVsupErrorFlag(void)
{
  bool_t ret = true;
  ret = loc_errStatus.hwErr2.errorFlags2.VsupVoltageOutOfRange;
  return ret;
}
