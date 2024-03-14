/***************************************************************************//**
 * @file      mod_app.h
 *
 * @creator   StSl
 * @created   22.11.2017
 * @sdfv      Demo Flow
 *
 * @brief     Application control module (header)
 *
 * @purpose
 *
 *  ******************************************************************************
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
 * $Id: mod_app.h 406 2019-02-08 15:49:42Z siko $
 *
 * $Revision: 406 $
 *
 ******************************************************************************/


#ifndef MOD_APP_H_
#define MOD_APP_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "def_app.h"
#include "mod_dsi3.h"
#include "mod_meas.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define ECHO_MEASUREMENT_MONITORING_PERIOD        (32u)       /**< Period in µs in which the echo measurement cycle is monitored */
#define T_REF                                     (25u)       /**< Reference temperature */
#define T_OFFSET                                  (40)       /**< Temperature offset to acquire a temperature range from -40 to 215°C */
#define TSENS_GAIN_REF                            (32u)       /**< Reference value for temperature gradient correction value */
#define TSENS_SLOPE                               (-0.576)    /**< Temperature curve gradient */
#define VSUP_OP_MAX                               (614u)      /**< Maximal VSUP operating voltage for operational condition : 24V: (24V*A_{HV})*(2^(10bit))/(40V_{max}*A_{HV})  614*/
#define VSUP_OP_MIN                               (154u)      /**< Minimal VSUP operating voltage for operational condition : 6V :  6V*(2^(10bit))/40V_max   154*/
#define VTANK_OP_MAX                              VSUP_OP_MAX /**< Maximal VTANK operating voltage for operational condition : 24V: 24V*(2^(10bit))/40V_max   614*/

#define TSENS_25D                                 (25)    /**< ( 25°C ) for efficient calculation of TSENS */
#define TSENS_SLOPE_EFF                           (-589)      /**< ( TSENS_SLOPE * 1024) for efficient calculation of TSENS */

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
 * Initialize Application Module
 *
 * This function initializes the application module specific data structures
 *
 * @param       pApplRuntimeData        generic application data, should point to application environment data
 * @return      bool_t                  true if init was successful
 * ****************************************************************************/
bool_t app_Init(Dsi3Drv_pApplCtrlData_t pApplRuntimeData);

/* **************************************************************************//**
 * @brief
 * PDCM: Measurement Response PDCM handler routine in Application Mode
 *
 * Sends 1 (allowed) data packet from the Measurement results pool.
 * On repeated PDCM req, iterates through allowed data packets.
 * If all allowed packets have been sent, continues to send ACK GRA packets.
 * Is called if in application mode
 *
 * @param       ansData                 pointer to PDCM response buffer for next PDCM pulse
 * @return      none
 * ****************************************************************************/
void app_PdcmCmdHandler_APP_MODE(Dsi3Drv_uPDCMResponseFrame_t* ansData);

/* **************************************************************************//**
 * @brief
 * Reset measurement flags
 *
 * Resets all measurement related flags, like the measurement finished flag
 * This function needs to be called directly when a measurement is initated by the
 * dsi3 layer
 *
 * @param       pResultBuf            Pointer to measurement result buffer struct
 * @return      n.a.
 * ****************************************************************************/
void app_ResetMeasurementFlagsCritical(Meas_sMeasurementResults_t* pResultBuf);

/* **************************************************************************//**
 * @brief
 * Measurement Initiation
 *
 * Resets all measurement buffer and disables the dma
 *
 * @param       pResultBuf            Pointer to measurement result buffer struct
 * @return      n.a.
 * ****************************************************************************/
void app_MeasurementInit(Meas_sMeasurementResults_t* pResultBuf);

/* **************************************************************************//**
 * @implementation
 * Diagnostic measurement
 *
 * Executes and saves supply voltage and temperature measurement
 *
 * @param       pResultBuf            Pointer to measurement result buffer struct
 * @return      n.a.
 * ****************************************************************************/
void app_DiagnosticMeasurement(Meas_sMeasurementResults_t* pResultBuf);

/* **************************************************************************//**
 * @implementation
 * Noise measurement
 *
 * Executes and saves noise measurement data
 *
 * @param       pMeasCtrl             Pointer to measurement struct
 * @return      bool_t                true if measurement finished
 * ****************************************************************************/
bool_t app_NoiseMeasurement(Dsi3Drv_pMeasCtrl_t pMeasCtrl);

/* **************************************************************************//**
 * @brief
 * Activate DMA for echo measurement
 *
 * Activates all dma channels that are needed for this measurement
 *
 * @param       measMode            Indicates if measuring in Standard or Advanced Mode
 * @return      n.a.
 * ****************************************************************************/
void app_ActivateDmaForEchoMeas(Meas_eMeasurementKind_t measMode);

/* **************************************************************************//**
 * @brief
 * Vsup monitoring
 *
 * Measures Vsup and compares the result to a threshold
 *
 * @param       pMeasCtrl             Pointer to measurement struct
 * @return      none
 * ****************************************************************************/
void app_VtankMonitoring(Dsi3Drv_pMeasCtrl_t pMeasCtrl);

/* **************************************************************************//**
 * @brief
 * Check Vsup
 *
 * Measures Vsup and returns its value
 *
 * @return      uint16_t          Result of Vsup measurement
 * ****************************************************************************/
uint16_t app_CheckVsup(void);

/* **************************************************************************//**
 * @brief
 * Check Vtank
 *
 * Measures Vtank and returns its value
 *
 * @return      uint16_t          Result of Vtank measurement
 * ****************************************************************************/
uint16_t app_CheckVtank(void);

/* **************************************************************************//**
 * @brief
 * Ringing Behavior
 *
 * Acquires and saves results from ringing time and frequency measurement
 *
 * @param       pMeasCtrl             Pointer to measurement struct
 * @return      none
 * ****************************************************************************/
void app_RingingBehaviour(Dsi3Drv_pMeasCtrl_t pMeasCtrl);

/* **************************************************************************//**
 * @brief
 * Near field detection
 *
 * Runs near field detection algorithm
 *
 * @param       pMeasCtrl             Pointer to measurement struct
 * @param       measurementTime       Current tick time
 * @return      none
 * ****************************************************************************/
void app_NearFieldDetection(Dsi3Drv_pMeasCtrl_t pMeasCtrl, uint16_t measurementTime);

/* **************************************************************************//**
 * @brief
 * Deactivate DMA for echo measurement
 *
 * Deactivates all dma channels for echo measurement
 *
 * @return      n.a.
 * ****************************************************************************/
void app_DeactivateDmaForEchoMeas(void);

/* *****************************************************************************
 * for description and detailed informations see function implementation header
 * *****************************************************************************/
uint8_t app_calculate_temperature(uint16_t ada_val_temp);

#endif /* MOD_APP_H_ */
