/***************************************************************************//**
 * @file      mod_err.h
 *
 * @creator   StSl
 * @created   10.11.2017
 *
 * @brief     Error module (header)
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
 * $Id: mod_err.h 424 2019-03-15 16:20:34Z siko $
 *
 * $Revision: 424 $
 *
 ******************************************************************************/

#ifndef MOD_ERR_H_
#define MOD_ERR_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "def_app.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define err_ErrorHandler(FILE)        err_ErrorHandlerExt(__LINE__, FILE);    /**< global error handler macro */

/** Hardware error register mask */
typedef enum
{
  ERR_RESET_WATCHDOG                  = 0,          /**< HwErr Register1 bit -> Reset has been triggered by Watchdog (HW) */
  ERR_OTP_ECC_ERROR                   = 1,          /**< HwErr Register1 bit -> ORP ECC error occurred (HW) */
  ERR_TRIM_REGISTER_PARITY_ERROR      = 2,          /**< HwErr Register1 bit -> Trim register parity error occurred (HW) */
  ERR_SRAM_PARITY_ERROR               = 3,          /**< HwErr Register1 bit -> SRAM parity error occurred (HW) */
  ERR_CRC_MISMATCH_IN_OTP             = 4,          /**< HwErr Register1 bit -> CRC on OTP mismatched (SW) */
  ERR_CRC_MISMATCH_IN_SYSROM          = 5,          /**< HwErr Register1 bit -> CRC on SysROM mismatched (SW) */
  ERR_CRC_MISMATCH_IN_EEPROM          = 6,          /**< HwErr Register1 bit -> CRC on EEPROM mismatched (SW) */
  ERR_CAP_LOSS_VDDD_OUT_OF_RANGE      = 7,          /**< HwErr Register1 bit -> Cap loss of Vddd out of expected range (SW) */
  ERR_CAP_LOSS_VDDA_OUT_OF_RANGE      = 9,          /**< HwErr Register1 bit -> Cap loss of Vdda out of expected range (SW) */
  ERR_REFERENCE_VOLTAGE_OUT_OF_RANGE  = 10,         /**< HwErr Register1 bit -> Reference voltage out of range (SW) */
  ERR_VDDD_VOLTAGE_OUT_OF_RANGE       = 11,         /**< HwErr Register1 bit -> Vddd voltage out of expected range (SW) */
  ERR_VREF_OTP_OUT_OF_RANGE           = 12,         /**< HwErr Register1 bit -> VrefOTP voltage out of expected range (SW) */
  ERR_EEPROM_PROGRAMMING_FAILURE      = 13,         /**< HwErr Register1 bit -> EEPROM programming failure (SW) */
  ERR_EEPROM_PROGRAMMING_BUSY         = 14,         /**< HwErr Register1 bit -> EEPROM programming busy (HW) */
  ERR_NO_ERROR1                       = 15,         /**< HwErr Register1 bit -> no error occurred */
}err_eHwErr1_t;

/** Hardware Error flags*/
typedef enum
{
  ERR_VSUP_VOLTAGE_OUT_OF_RANGE               = 0,  /**< HwErr Register2 bit -> VSUP voltage out of expected range (SW) */
  ERR_TEMPERATURE_SESNOR_VOLTAGE_OUT_OF_RANGE = 1,  /**< HwErr Register2 bit -> Temperature sensor voltage out of expected range (SW) */
  ERR_UNDER_VOLTAGE_AT_VTANK_DURING_BURST     = 2,  /**< HwErr Register2 bit -> Under voltage at VTANK during burst (HW) */
  ERR_OVER_VOLTAGE_AT_VTANK_DURING_BURST      = 3,  /**< HwErr Register2 bit -> Over voltage at VTANK during burst (HW) */
  ERR_DRVS_FAILURE_DURING_BURST               = 4,  /**< HwErr Register2 bit -> DRVS failure during burst (HW) */
  ERR_DRV1_FAILURE_DURING_BURST               = 5,  /**< HwErr Register2 bit -> DRV1 failure during burst (HW) */
  ERR_DRV2_FAILURE_DURING_BURST               = 6,  /**< HwErr Register2 bit -> DRV2 failure during burst (HW) */
  ERR_DSP_OFF                                 = 7,  /**< HwErr Register2 bit -> DSP off while measurement is initiated (SW) */
  ERR_CRC_MISMATCH_IN_RAM                     = 8,  /**< HwErr Register2 bit -> CRC on RAM mismatched (SW) */
  ERR_VERIFICATION_OF_CONF_FAILED             = 9,  /**< HwErr Register2 bit -> Verification of configuration and calculated parameters failed (SW) */
  ERR_WDG_CLOCK_FREQ_OUT_OF_RANGE             = 10, /**< HwErr Register2 bit -> Watchdog clock frequency out of expected range (SW) */
  ERR_ATG_NOISE_OUT_OF_RANGE                  = 11, /**< HwErr Register2 bit -> ATG_NoiseValue above NoiseAtgThreshold(SW) */
  ERR_DISC_VERIFY_ERROR                       = 12, /**< HwErr Register2 bit -> Auto Adressing Error. Measured ramp ON even the adressing is completed */
  ERR_NO_ERROR2                               = 15, /**< HwErr Register2 bit -> no error occurred */
}err_eHwErr2_t;

/** Communication Error flags */
typedef enum
{
  ERR_SYNCHRONISATION_COUNTER_ERROR_DETECTED  = 0,  /**< ComErr Register Bit -> Synchronisation counter error detected (HW) */
  ERR_INVALID_START_EDGE_DETECTED             = 1,  /**< ComErr Register Bit -> Invalid start edge detected (HW) */
  ERR_RECEIVER_RECHED_ERROR_STATE             = 2,  /**< ComErr Register Bit -> Receiver reached error state (HW) */
  ERR_DISCOVERY_PULSE_INVALID                 = 3,  /**< ComErr Register Bit -> Discovery pulse invalid (HW) */
  ERR_PDCM_PULSE_INVALID                      = 4,  /**< ComErr Register Bit -> PDCM pulse invalid (HW) */
  ERR_CRC_OF_RECEIVED_COMMAND_INVALID         = 5,  /**< ComErr Register Bit -> CRC of received command invalid (HW) */
  ERR_PASSWORD_WRONG                          = 9,  /**< ComErr Register Bit -> Password for CRM cmd invalid (SW) */
  ERR_TIME_BETWEEN_PDCM_SYNCS_OUT_OF_BOUND    = 10, /**< ComErr Register Bit -> Time interval between 2 PDCM pulses out of expected range (+- 5%) (SW) */
}err_eComErr_t;

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/** Hardware Error Status 1 */
typedef struct
{
  uint16_t      resetWatchdog                       :1;     /**< Reset has been triggered by Watchdog (HW) */
  uint16_t      OtpEccError                         :1;     /**< ORP ECC error occurred (HW) */
  uint16_t      TrimRegisterParityError             :1;     /**< Trim register parity error occurred (HW) */
  uint16_t      SramParityError                     :1;     /**< SRAM parity error occurred (HW) */
  uint16_t      CrcMismatchInOtp                    :1;     /**< CRC on OTP mismatched (SW) */
  uint16_t      CrcMismatchInSysRom                 :1;     /**< CRC on SysROM mismatched (SW) */
  uint16_t      CrcMismatchInEeprom                 :1;     /**< CRC on EEPROM mismatched (SW) */
  uint16_t      CapLossVdddOutOfRange               :1;     /**< Cap loss of Vddd out of expected range (SW) */
  uint16_t      reserved8                           :1;     /**< unused status bit */
  uint16_t      CapLossVddaOutOfRange               :1;     /**< Cap loss of Vdda out of expected range (SW) */
  uint16_t      ReferenceVoltageOutOfRange          :1;     /**< Reference voltage out of range (SW) */
  uint16_t      VdddVoltageOutOfRange               :1;     /**< Vddd voltage out of expected range (SW) */
  uint16_t      VrefOtpOutOfRange                   :1;     /**< VrefOTP voltage out of expected range (SW) */
  uint16_t      EepromProgrammingFailure            :1;     /**< EEPROM programming failure (SW) */
  uint16_t      EepromProgrammingBusy               :1;     /**< EEPROM programming busy (HW) */
  uint16_t      reserved15                          :1;     /**< unused status bit */
} err_sHwErrStatusInf1_t;

/** Hardware Error Status 2 */
typedef struct
{
  uint16_t      VsupVoltageOutOfRange               :1;     /**< VSUP voltage out of expected range (SW) */
  uint16_t      TemperatureSensorVoltageOutOfRange  :1;     /**< Temperature sensor voltage out of expected range (SW) */
  uint16_t      UnderVoltageAtVtankDuringBurst      :1;     /**< Under voltage at VTANK during burst (HW) */
  uint16_t      OverVoltageAtVtankDuringBurst       :1;     /**< Over voltage at VTANK during burst (HW) */
  uint16_t      DrvsFailureDuringBurst              :1;     /**< DRVS failure during burst (HW) */
  uint16_t      Drv1FailureDuringBurst              :1;     /**< DRV1 failure during burst (HW) */
  uint16_t      Drv2FailureDuringBurst              :1;     /**< DRV2 failure during burst (HW) */
  uint16_t      DspOff                              :1;     /**< DSP off while measurement is initiated (SW) */
  uint16_t      CrcMismatchInRam                    :1;     /**< CRC on RAM mismatched (SW) */
  uint16_t      VerificationOfConfFailed            :1;     /**< Verification of configuration and calculated parameters failed (SW) */
  uint16_t      WdgClockFreqOutOfRange              :1;     /**< Watchdog clock frequency out of expected range (SW) */
  uint16_t      AtgNoiseOutOfRange                  :1;     /**< The ATG Noise Level is out of defined range */
  uint16_t      reserved12                          :1;     /**< unused status bit */
  uint16_t      reserved13                          :1;     /**< unused status bit */
  uint16_t      reserved14                          :1;     /**< unused status bit */
  uint16_t      reserved15                          :1;     /**< unused status bit */
} err_sHwErrStatusInf2_t;

/** Communication Error Status */
typedef struct
{
  uint16_t      SynCounterErrorDetected             :1;     /**< Synchronisation counter error detected (HW) */
  uint16_t      InvaildStartEdgeDetected            :1;     /**< Invalid start edge detected (HW) */
  uint16_t      ReceiverRechedErrorState            :1;     /**< Receiver reached error state (HW) */
  uint16_t      DiscoveryPulseInvalid               :1;     /**< Discovery pulse invalid (HW) */
  uint16_t      PdcmPulseInvalid                    :1;     /**< PDCM pulse invalid (HW) */
  uint16_t      CrcOfReceivedCommandInvalid         :1;     /**< CRC of received command invalid (HW) */
  uint16_t      reserved6                           :1;     /**< unused status bit */
  uint16_t      reserved7                           :1;     /**< unused status bit */
  uint16_t      reserved8                           :1;     /**< unused status bit */
  uint16_t      PasswordWrong                       :1;     /**< Password for CRM cmd invalid (SW) */
  uint16_t      TimeBetweenPdcmSyncPulsesOutOfRange :1;     /**< Time interval between 2 PDCM pulses out of expected range (+- 5%) (SW) */
  uint16_t      reserved11                          :1;     /**< unused status bit */
  uint16_t      reserved12                          :1;     /**< unused status bit */
  uint16_t      reserved13                          :1;     /**< unused status bit */
  uint16_t      reserved14                          :1;     /**< unused status bit */
  uint16_t      reserved15                          :1;     /**< unused status bit */
} err_sComErrStatus_t;

typedef union
{
  err_sHwErrStatusInf1_t    errorFlags1;                    /**< HwErr status information 1 */
  uint16_t                  rawData;                        /**< raw data */
} err_uHwErrStatusInf1_t;

typedef union
{
  err_sHwErrStatusInf2_t    errorFlags2;                    /**< HwErr status information 2 */
  uint16_t                  rawData;                        /**< raw data */
} err_uHwErrStatusInf2_t;

typedef union
{
  err_sComErrStatus_t       errorFlags;                     /**< ComErr status information */
  uint16_t                  rawData;                        /**< raw data */
} err_uComErrStatus_t;

/** Module identification*/
typedef enum
{
  ERR_MODLIST_MAIN      = 0,      /**< error handler modlist entry for main.c */
  ERR_MODLIST_DSI3      = 1,      /**< error handler modlist entry for mod_dsi3.c */
  ERR_MODLIST_MEAS      = 2,      /**< error handler modlist entry for mod_meas.c */
  ERR_MODLIST_APP       = 3,      /**< error handler modlist entry for mod_app.c */
  ERR_MODLIST_UTIL      = 4,      /**< error handler modlist entry for mod_util.c */
  ERR_MODLIST_LAB       = 5,      /**< error handler modlist entry for mod_lab.c */
  ERR_MODLIST_EEPROM    = 6,      /**< error handler modlist entry for mod_eeprom.c */
  ERR_MODLIST_RESERVED  = 7,      /**< not used error handler modlist entry */
  ERR_MODLIST_MEM       = 8,      /**< error handler modlist entry for mod_mem.c */
} err_eModuleList;

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
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
void err_SetHwErrorFlag(err_eHwErr1_t err1, err_eHwErr2_t err2);

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
void err_SetComErrorFlag(err_eComErr_t err);

/* ***************************************************************************
 * @brief
 * Get Hardware Error Flag 1
 *
 * Returns the whole HwErr Register 1 and resets it
 *
 * @return      err_uHwErrStatusInf1_t        HwErr Register 1
 * ****************************************************************************/
err_uHwErrStatusInf1_t err_GetHwErrorFlag1(void);

///* ***************************************************************************
// * @brief
// * Get Hardware Error Flag 1 without reset (for selftest)
// *
// * Returns the whole HwErr Register 1
// *
// * @return      err_uHwErrStatusInf1_t        HwErr Register 1
// * ****************************************************************************/
//uint16_t err_HwErrorFlag1Info(void);

/* ***************************************************************************
 * @brief
 * Get Hardware Error Flag 2
 *
 * Returns the whole HwErr Register 2 and resets it
 *
 * @return      err_uHwErrStatusInf2_t        HwErr Register 2
 * ****************************************************************************/
err_uHwErrStatusInf2_t err_GetHwErrorFlag2(void);

///* ***************************************************************************
// * @brief
// * Get Hardware Error Flag 2 without reset (for selftest)
// *
// * Returns the whole HwErr Register 2
// *
// * @return      err_uHwErrStatusInf2_t        HwErr Register 2
// * ****************************************************************************/
//uint16_t err_HwErrorFlag2Info(void);

/* ***************************************************************************
 * @brief
 * Get Communication Error Flag
 *
 * Returns the whole ComErr Register and resets it
 *
 * @return      err_uComErrStatus_t        ComErr Register
 * ****************************************************************************/
err_uComErrStatus_t err_GetComErrorFlag(void);

///* ***************************************************************************
// * @brief
// * Get Communication Error Flag without reset (for selftest)
// *
// * Returns the whole ComErr Register
// *
// * @return      err_uComErrStatus_t        ComErr Register
// * ****************************************************************************/
//uint16_t err_ComErrorFlagInfo(void);

/* ***************************************************************************
 * @brief
 * Get Global Hardware Error Flag
 *
 * Indicates if one of the error flags in HwErr Register 1 or 2 is set
 *
 * @return      bool_t        true if any error flag was set
 *                            false if no error flag was set
 * ****************************************************************************/
bool_t err_GetGlobalHwErrFlag(void);

/* ***************************************************************************
 * @brief
 * Get Global Communication Error Flag
 *
 * Indicates if one of the error flags in ComErr Register is set
 *
 * @return      bool_t        true if any error flag was set
 *                            false if no error flag was set
 * ****************************************************************************/
bool_t err_GetGlobalComErrFlag(void);

/* ***************************************************************************
 * @brief
 * Error Handler
 *
 * Can be called if unexpected situations occurres
 * Gets called by the err_ErrorHandler() macro
 *
 * @param       line            The line if the source code file in which the error occurred
 * @param       file            The file in which the error occurred
 * @return      none
 * ****************************************************************************/
void err_ErrorHandlerExt(uint32_t line, err_eModuleList file);

/* *****************************************************************************
 * for description and detailed informations see function implementation header
 * ****************************************************************************/
bool_t err_getVsupErrorFlag(void);

#endif /* MOD_ERR_H_ */
