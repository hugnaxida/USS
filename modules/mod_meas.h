/***************************************************************************//**
 * @file      mod_meas.h
 *
 * @creator   poe
 * @created   16.05.2017
 * @sdfv      Demo Flow
 *
 * @brief     Measurement Control software module (header)
 *
 * @purpose
 *
 * Software module for managing and controlling echo related measurement processes.
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
 * $Id: mod_meas.h 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
 *
 ******************************************************************************/

#ifndef MEASCTRL_H_
#define MEASCTRL_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "def_app.h"
#include "mod_swt.h"
#include "def_brg.h"
/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define SYSTEM_TIMER_PERIOD                       (32u)       /**< Timer period, on which most time constants in the config are based */
#define swtimer_eSyncTimer                            swtimer_eTimer_1
#define swtimer_eTickPeriodTimer                      swtimer_eTimer_0

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * Initialization
 *
 * Initialization function for the measurement module
 *
 * @return      TRUE  always
 * ****************************************************************************/
bool_t meas_init(void);

/* **************************************************************************//**
 * @brief
 * Get Control
 *
 * Makes measurement related application data accessible by a pointer
 *
 * @return      pointer to measurement related application data
 * ****************************************************************************/
Dsi3Drv_pMeasCtrl_t meas_GetCtrl(void);

/* **************************************************************************//**
 * @brief
 * Main Task
 *
 * Handles the measurement state machine of the measurement module
 *
 * @return      none
 * ****************************************************************************/
void meas_Task(void);

/* **************************************************************************//**
 * @brief
 * Start a Standard Measurement
 *
 * Initiates a standard measurement cycle by setting all given
 * parameters & starting the synchronization timer
 *
 * @param       conf         Selected direct or indirect measurement
 * @param       mode         Selected measurement mode
 * @param       profile      Selected measurement profile
 * @return      none
 * ****************************************************************************/
void meas_StartStandardMeasurement(Meas_eMeasurementConf_t conf, Meas_eMeasurementMode_t mode, Meas_eMeasurementProfile_t profile);

/* **************************************************************************//**
 * @brief
 * Start an Advanced Measurement
 *
 * Initiates an advanced measurement cycle by setting all given
 * parameters & starting the synchronization timer
 *
 * @param       conf         Selected direct or indirect measurement
 * @param       mode         Selected measurement mode
 * @param       profile      Selected measurement profile
 * @return      none
 * ****************************************************************************/
void meas_StartAdvancedMeasurement(Meas_eMeasurementConf_t conf, Meas_eMeasurementMode_t mode, Meas_eMeasurementProfile_t profile);

/* **************************************************************************//**
 * @brief
 * Abort Measurement
 *
 * Sets the measurement abort flag, to stop the active measurement cycle
 *
 * @return      none
 * ****************************************************************************/
void meas_AbortMeasurement(void);

/* **************************************************************************//**
 * @brief
 * Get Measurement Configuration
 *
 * Returns the measurement configuration of the active measurement, which indicates if a
 * direct, indirect or none measurement is executed
 *
 * @return      Measurement Configuration of active measurement
 * ****************************************************************************/
Meas_eMeasurementConf_t meas_GetMeasConf(void);

/* *****************************************************************************
 * for description and detailed informations see function implementation header
 * *****************************************************************************/
void meas_StartTickTimerForNoiseMeas(void);

/* **************************************************************************//**
 * @brief
 * Synchronization Timer Interrupt Service Routine
 *
 * Triggers measurement state changes synchronously to the CRM sync pulse
 *
 * @param       sno             Triggered interrupt event number
 * @param       contextdata     Pointer to SCI context data
 * @return      none
 * ****************************************************************************/
void meas_SyncTimer_ISR(swtimer_eInterruptVectorNum_t sno,  swtimer_pInterruptContextData_t contextdata);

/* **************************************************************************//**
 * @brief
 * Noise Measurement Timer Interrupt Service Routine
 *
 * Is triggered with a period of 32µs to acquire a new noise sample
 *
 * @param       sno             Triggered interrupt event number
 * @param       contextdata     Pointer to SCI context data
 * @return      none
 * ****************************************************************************/
void meas_TickTimer_ISR(swtimer_eInterruptVectorNum_t sno,  swtimer_pInterruptContextData_t contextdata);

#endif
