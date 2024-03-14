/***************************************************************************//**
 * @file      def_app.h
 *
 * @creator   StSl
 * @created   24.04.2017
 * @sdfv
 *
 * @brief     Project Defines
 *
 * @purpose
 * This file contains all project global defines
 *
 * $Id: def_app.h 432 2019-03-26 11:50:03Z siko $
 *
 * $Revision: 432 $
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

#ifndef APP_DEFS_H_
#define APP_DEFS_H_

#include "Dsi3Bus_Types.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define SRAM_BASE_ADDRESS                               (0x20000000u)       /**< Base Address of the SRAM */
#define SYSROM_BASE_ADDRESS                             (0x30000000u)       /**< Base Address of the SYS_ROM */
#define MEAS_SETTINGS_SIZE                              (MEAS_GENERALSETTINGS_SIZE + MEAS_NOISEMEASUREMENT_SIZE + (3*MEAS_STANDARDPATHPROFILE_SIZE) + (2*MEAS_ADVANCEDPATHPROFILE_SIZE) + MEAS_NFDSETTINGS_SIZE + MEAS_NFDSETTINGS2_SIZE + MEAS_DSISETTINGS_SIZE + MEAS_MONITORING_SIZE + MEAS_DATAFORSELFTEST_SIZE + MEAS_TOF_COMPENSATION_SIZE + MEAS_CRCCALCULATION_SIZE + MEAS_SLAVEID_SIZE)
#define MEAS_GENERALSETTINGS_SIZE                        (5u)               /**< size of measurement general settings struct times 16 bit */
#define MEAS_NOISEMEASUREMENT_SIZE                       (2u)               /**< size of measurement noise measurement struct times 16 bit */
#define MEAS_STANDARDPATHPROFILE_SIZE                   (11u)               /**< size of measurement standard path profile struct times 16 bit */
#define MEAS_ADVANCEDPATHPROFILE_SIZE                   (14u)               /**< size of measurement advanced path profile struct times 16 bit */
#define MEAS_NFDSETTINGS_SIZE                            (2u)               /**< size of measurement nfd settings struct times 16 bit */
#define MEAS_NFDSETTINGS2_SIZE                           (2u)               /**< size of measurement nfd settings 2 struct times 16 bit */
#define MEAS_DSISETTINGS_SIZE                           (11u)               /**< size of measurement dsi settings struct times 16 bit */
#define MEAS_MONITORING_SIZE                             (2u)               /**< size of measurement monitoring struct times 16 bit */
#define MEAS_DATAFORSELFTEST_SIZE                        (4u)               /**< size of measurement data for self test struct times 16 bit */
#define MEAS_TOF_COMPENSATION_SIZE                      (10u)               /**< size of measurement data time of flight compensation 16 bit */
#define MEAS_CRCCALCULATION_SIZE                         (3u)               /**< size of measurement crc calculation struct times 16 bit */
#define MEAS_SLAVEID_SIZE                                (2u)               /**< size of measurement slave id struct times 16 bit */

#define MEAS_EEVAL_STDDATAPACKET_SIZE                     (2u)                  /**< size of standard path measurement result data packet times 16 bit */
#define MEAS_EEVAL_ADVDATAPACKET_SIZE                     (3u)                  /**< size of advanced path measurement result data packet times 16 bit */
#define MEAS_STDRESULTBUF_MAX                            (50u)                  /**< number of slots in standard measurement result buffer */
#define MEAS_ADVRESULTBUF_SINGLE_PATH_MAX                (20u)                  /**< number of slots in advanced measurement result buffer */
#define MEAS_ADVRESULTBUF_DUAL_PATH_MAX     (2*MEAS_ADVRESULTBUF_SINGLE_PATH_MAX)                       /**< resulting advanced buffer for both paths */
#define MEAS_STANDARDPATH_BUFFER_SIZE (MEAS_EEVAL_STDDATAPACKET_SIZE * MEAS_STDRESULTBUF_MAX)           /**< size of standard path measurement result buffer times 16 bit */
#define MEAS_ADVANCEDPATH_BUFFER_SIZE (MEAS_EEVAL_ADVDATAPACKET_SIZE * MEAS_ADVRESULTBUF_DUAL_PATH_MAX) /**< size of advanced path measurement result buffer times 16 bit */
#define MEAS_LABMODE_BUFFER_SIZE                       (600u)                 /**< size of lab mode signal buffer */
#define MEAS_GLOBAL_BUFFER_SIZE (MEAS_ADVANCEDPATH_BUFFER_SIZE + MEAS_LABMODE_BUFFER_SIZE)     /**< size of global result buffer times 16 bit (used for std and adv measurement as well as lab mode) */
#define MEAS_EEVAL_STDDATAPACKET_FORMAT0                  (0u)                  /**< Standard measurement data packet format 0 */
#define MEAS_EDI_DMA_CHANNELS                             (4u)                  /**< Number of EDI DMA Channels*/
#define MEAS_EDI_DMA_SAMPLES_TOTAL                        (32u)                 /**< Size of EDI DMA sample buffer in 16bit words - DmaWrapTime= n*(1/(f_c(dsr_sel)) e.g. for 58kHz Transducer:  n*17.24ns  */

#define OTP_BASE_ADDRESS                          (0x00000000u)                 /**< Memory base address of OTP */
#define OTP_LENGTH                                    (0x7C00u)                 /**< Number of bytes in OTP memory !Length has to be even (16bit crc)! */
#define SYSROM_BASE_ADDRESS                       (0x30000000u)                 /**< Memory base address of SysROM */
#define SYSROM_LENGTH                                 (0x6000u)                 /**< Number of bytes in SysROM memory */
#define EEPROM_BASE_ADDRESS                       (0x48000000u)                 /**< Memory base address of EEPROM */
#define EEPROM_LENGTH                                    (208u)                 /**< Number of bytes in EEPROM memory */
#define EEPROM_LENGTH_WITHOUT_CRC_AREA                   (198u)                 /**< Number of bytes in EEPROM memory with the crc area excluded */

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* supported crm command ids */
/* ****************************************************************************/
typedef enum 
{
  dsi3Drv_eCRM_COMMAND_ID_NOP1                            = 0x0u,
  dsi3Drv_eCRM_COMMAND_ID_MEASUREMENT_EXECUTE             = 0x1u,
  dsi3Drv_eCRM_COMMAND_ID_MEASUREMENT_ADVANCED_EXECUTE    = 0x2u,
  dsi3Drv_eCRM_COMMAND_ID_NOP2                            = 0x3u,
  dsi3Drv_eCRM_COMMAND_ID_MEASUREMENT_STOP                = 0x4u,
  dsi3Drv_eCRM_COMMAND_ID_NOP3                            = 0x5u,
  dsi3Drv_eCRM_COMMAND_ID_NOP4                            = 0x6u,
  dsi3Drv_eCRM_COMMAND_ID_NOP5                            = 0x7u,
  dsi3Drv_eCRM_COMMAND_ID_MEASUREMENT_SETTINGS            = 0x8u,
  dsi3Drv_eCRM_COMMAND_ID_MEASUREMENT_SETTINGS_EXTENDED   = 0x9u,
  dsi3Drv_eCRM_COMMAND_ID_EEPROM_ACCESS                   = 0xAu,
  dsi3Drv_eCRM_COMMAND_ID_REGISTER_ACCESS                 = 0xBu,
  dsi3Drv_eCRM_COMMAND_ID_REGISTER_ACCESS_EXTENDED        = 0xCu,
  dsi3Drv_eCRM_COMMAND_ID_READ_STATUS_IN_CRM              = 0xDu,
  dsi3Drv_eCRM_COMMAND_ID_READ_STATUS_IN_PDCM             = 0xEu,
  dsi3Drv_eCRM_COMMAND_ID_IC_MODE                         = 0xFu,
} Dsi3Drv_eCRMCommandID;
typedef Dsi3Drv_eCRMCommandID Dsi3Drv_eCRMCommandID_t;



/* *****************************************************************************
 * control for DSI3 communication
 * ****************************************************************************/
/** DSI3 frame types */
typedef enum{
  DSI3_TYPE_IMP_RESULT_IMPEDANCE                  = 0x0u,                                 /**< results from the impedance measurement */
  DSI3_TYPE_MEAS_RESULT_APP_MODE                  = 0x1u,                                 /**< results from the ultrasonic measurement (application mode) are transmitted */
  DSI3_TYPE_MEAS_RESULT_LAB_MODE                  = 0x2u,                                 /**< results from the ultrasonic measurement (lab mode) are transmitted */
  DSI3_TYPE_SELF_TEST                             = 0x3u,                                 /**< results from the self-test are transmitted */
}Dsi3_ePDCMType_t;


//typedef uint8_t Dsi3_ePDCMType_t;
//const Dsi3_ePDCMType_t DSI3_TYPE_IMP_RESULT_IMPEDANCE = 0u;
//const Dsi3_ePDCMType_t DSI3_TYPE_MEAS_RESULT_APP_MODE = 1u;
//const Dsi3_ePDCMType_t DSI3_TYPE_MEAS_RESULT_LAB_MODE = 2u;
//const Dsi3_ePDCMType_t DSI3_TYPE_SELF_TEST = 3u;
//#define DSI3_TYPE_IMP_RESULT_IMPEDANCE ((Dsi3_ePDCMType_t)0u)
//#define DSI3_TYPE_MEAS_RESULT_APP_MODE (1u)
//#define DSI3_TYPE_MEAS_RESULT_LAB_MODE (2u)
//#define DSI3_TYPE_SELF_TEST (3u)

/** DSI3 synchronization configuration */
typedef enum
{
  DSI3_SYNC_OFF                                   = 0,                                    /**< DSI3 synchronization is turned off */
  DSI3_SYNC_ON_HARDWARE                           = 1,                                    /**< DSI3 synchronization is handled by hardware */
  DSI3_SYNC_ON_CRM                                = 2,                                    /**< DSI3 synchronization is done by software in CRM frames */
  DSI3_SYNC_ON_PDCM                               = 3,                                    /**< DSI3 synchronization is done by software in PDCM frame */
  DSI3_SYNC_ON_CRM_AND_PDCM                       = 4,                                    /**< DSI3 synchronization is done by software in CRM and PDCM frame */
}dsi3_cfg_status_sync_t;
typedef struct
{
  Dsi3BusIf_SlaveID_t                           CurrentNAD;
  bool_t                                        SyncFlag;                                 /**< DSI3 - set if synchronization data from hardware could be ready */
  uint8_t                                       PDCMFrameCounter;                         /**< PDCM frame counter */
  Dsi3_ePDCMType_t                              PDCMCurrentType;                          /**< PDCM current response type */
  Dsi3Drv_eCRMCommandID_t                       CrmLastCommand;                           /**< CRM last executed command */
  uint32_t                                      CrmExtCommandAddress;                     /**< Memory address for the "further write" CRM commands */
  bool_t                                        CrmCxtCommandLastSuccessfull;             /**< Command successful executed flag for "further write" CRM commands */
} Dsi3Drv_sDSI3Ctrl_t;                                                                    /**< Nad control data for Nad, bus etc. */

typedef		Dsi3Drv_sDSI3Ctrl_t*	        Dsi3Drv_pDSI3Ctrl_t;
typedef	const	Dsi3Drv_sDSI3Ctrl_t*	        Dsi3Drv_cpDSI3Ctrl_t;



/* ****************************************************************************/
/* control data for measurement*/
/* ****************************************************************************/

/* measurement parameters - general setting - struct and union */
typedef struct
{
  uint16_t          SamplingFrequency                   :15;        /**< BRG Carrier frequency for the burst */
  uint16_t          reserved0                           : 1;        /**< unused memory space */

  uint16_t          TdrCurrent                          : 5;        /**< TDR Transducer driver current */
  uint16_t          AnalogGain                          : 3;        /**< ASP Analog gain configuration */
  uint16_t          AnalogLp                            : 1;        /**< ASP low pass filter configuration */
  uint16_t          CalibrationGain                     : 5;        /**< ENVP calibration gain configuration */
  uint16_t          reserved2                           : 2;        /**< unused memory space */

  uint16_t          RingFreqStart                       : 5;        /**< RFM start of measurement window */
  uint16_t          RingFreqWidth                       : 5;        /**< RFM Width of measurement window */
  uint16_t          reserved4                           : 6;        /**< unused memory space */

  uint16_t          reserved5                           : 4;        /**< unused memory space */
  uint16_t          Dac1Ctrl                            : 2;        /**< DAC1 output configuration */
  uint16_t          Dac0Ctrl                            : 2;        /**< DAC0 output configuration */
  uint16_t          reserved6                           : 8;        /**< unused memory space */

  uint16_t          UnderVoltageThreshold               :10;        /**< Threshold for VTANK measurement during burst phase */
  uint16_t          reserved8                           : 6;        /**< unused memory space */
} Meas_sGeneralSettings;
typedef union
{
  Meas_sGeneralSettings           fields;
  uint16_t                        halfwords[MEAS_GENERALSETTINGS_SIZE];
} Meas_uGeneralSettings;

/* measurement parameters - noise measurement - struct and union */
typedef struct
{
  uint16_t          NoiseMeasTime                       : 8;        /**< Noise samples to be acquired whilst diagnostic measurement */
  uint16_t          NoiseMeasThreshold                  : 8;        /**< Threshold which defines noise samples that have to be counted by the noise counter */

  uint16_t          NoiseMeasGain                       :7 ;        /**< AMPD signal gain of digital amplifier */
  uint16_t          NoiseMeasFilterBw                   :3 ;        /**< ENVP digital filter bandwidth configuration */
  uint16_t          NoiseAtgThreshold                   :6 ;        /**< Threshold for noise measurement while echo measurement */
} Meas_sNoiseMeasurement;

typedef union
{
  Meas_sNoiseMeasurement          fields;
  uint16_t                        halfwords[MEAS_NOISEMEASUREMENT_SIZE];
} Meas_uNoiseMeasurement;

/* measurement parameters - standard path profile - struct and union */
typedef struct
{
  uint16_t          SpxBurstFreq                        :15;        /**< BRG burst base frequency */
  uint16_t          reserved14                          : 1;        /**< unused memory space */

  uint16_t          SpxBurstPulses                      : 7;        /**< BRG number of burst pulses */
  uint16_t          SpxMeasFilterBw                     : 3;        /**< ENVP digital filter bandwidth configuration */
  uint16_t          SpxDs                               : 1;        /**< ENVP down sampling rate select */
  uint16_t          SpxFtcCfg                           : 3;        /**< FTC configuration */
  uint16_t          SpxFtcEn                            : 1;        /**< FTC enable flag */
  uint16_t          reserved16                          : 1;        /**< unused memory space */

  uint16_t          SpxStcGain                          : 7;        /**< STC target value at which it will stop to increase/decrease AMPD_CTRL.g_dig */
  uint16_t          SpxStcMod                           : 1;        /**< STC autoincrement mode (lin or log) */
  uint16_t          SpxStcStart                         : 8;        /**< STC time between start of meas and start of STC function (datasheet 5.6.6-2) */

  uint16_t          SpxStcTb                            :12;        /**< STC autoincrement time base */
  uint16_t          reserved20                          : 4;        /**< unused memory space */

  uint16_t          SpxStgHeight1                       : 8;        /**< STG target value in interval 1 */
  uint16_t          SpxStgInterval1                     : 8;        /**< STG duration of interval 1 times 32� */

  uint16_t          SpxStgHeight2                       : 8;        /**< STG target value in interval 2 */
  uint16_t          SpxStgInterval2                     : 8;        /**< STG duration of interval 2 times 32� */

  uint16_t          SpxStgHeight3                       : 8;        /**< STG target value in interval 3 */
  uint16_t          SpxStgInterval3                     : 8;        /**< STG duration of interval 3 times 32� */

  uint16_t          SpxStgHeight4                       : 8;        /**< STG target value in interval 4 */
  uint16_t          SpxStgInterval4                     : 8;        /**< STG duration of interval 4 times 32� */

  uint16_t          SpxAtgTau                           : 3;        /**< ATG time response configuration */
  uint16_t          SpxAtgAlpha                         : 3;        /**< ATG sensitivity configuration */
  uint16_t          SpxAtgIni                           : 3;        /**< ATG initial value */
  uint16_t          SpxAtgCfg                           : 1;        /**< ATG configuration */
  uint16_t          reserved30                          : 6;        /**< unused memory space */

  uint16_t          SpxEevalSel                         : 4;        /**< EEVAL data source selection */
  uint16_t          SpxEevalSens                        : 3;        /**< EEVAL echo minimum/maximum evaluation sensitivity */
  uint16_t          SpxEevalVal                         : 1;        /**< EEVAL select value to be stored via DMA */
  uint16_t          SpxMeasGain                         : 7;        /**< AMPD digital amplifier gain configuration */
  uint16_t          reserved32                          : 1;        /**< unused memory space */

  uint16_t          SpxMeasMaskDirect                   : 7;        /**< Period at which echo measurement results should be ignored in direct mode */
  uint16_t          SpxMeasMaskIndirect                 : 7;        /**< Period at which echo measurement results should be ignored in indirect mode */
  uint16_t          reserved34                          : 2;        /**< unused memory space */
} Meas_sStandardPathProfile;

typedef union
{
  Meas_sStandardPathProfile       fields;
  uint16_t                        halfwords[MEAS_STANDARDPATHPROFILE_SIZE];
} Meas_uStandardPathProfile;

/* measurement parameters - advanced path profile - struct and union */
typedef struct
{
  uint16_t          ApxBurstFreqLo                      :15;        /**< BRG chirp low frequency */
  uint16_t          reserved80                          : 1;        /**< unused memory space */

  uint16_t          ApxBurstFreqHi                      :15;        /**< BRG chirp high frequency */
  uint16_t          reserved82                          : 1;        /**< unused memory space */

  uint16_t          ApxBurstFreqDelta                   : 8;        /**< BRG chirp frequency step width */
  uint16_t          ApxFilterLength                     : 6;        /**< ENVP number of filter stages */
  uint16_t          reserved84                          : 2;        /**< unused memory space */

  uint16_t          ApxBurstPulses                      : 7;        /**< BRG number of burst pulses */
  uint16_t          ApxCodeLength                       : 2;        /**< BRG length of the code */
  uint16_t          ApxCode                             : 4;        /**< BRG code word to send */
  uint16_t          ApxDs                               : 1;        /**< ENVP down sampling rate select */
  uint16_t          reserved86                          : 2;        /**< unused memory space */

  uint16_t          ApxEnvpCoeff3_0;                                /**< ENVP filter coefficients in the advanced signal path 0 to 3 */
  uint16_t          ApxEnvpCoeff7_4;                                /**< ENVP filter coefficients in the advanced signal path 4 to 7 */
  uint16_t          ApxEnvpCoeff11_8;                               /**< ENVP filter coefficients in the advanced signal path 8 to 11 */
  uint16_t          ApxEnvpCoeff15_12;                              /**< ENVP filter coefficients in the advanced signal path 12 to 15 */
  uint16_t          ApxEnvpCoeff19_16;                              /**< ENVP filter coefficients in the advanced signal path 16 to 19 */
  uint16_t          ApxEnvpCoeff23_20;                              /**< ENVP filter coefficients in the advanced signal path 20 to 23 */
  uint16_t          ApxEnvpCoeff27_24;                              /**< ENVP filter coefficients in the advanced signal path 24 to 27 */
  uint16_t          ApxEnvpCoeff31_28;                              /**< ENVP filter coefficients in the advanced signal path 28 to 31 */

  uint16_t          ApxAatgCn                           : 3;        /**< AATG cell number configuration */
  uint16_t          ApxAatgCw                           : 3;        /**< AATG cell width configuration */
  uint16_t          ApxAatgAlpha                        : 2;        /**< AATG sensitivity configuration */
  uint16_t          ApxAatgOff                          : 1;        /**< AATG on/off flag */
  uint16_t          ApxEevalSens                        : 3;        /**< EEVAL echo minimum/maximum evaluation sensitivity */
  uint16_t          ApxMinConf                          : 4;        /**< Min confidence level for advanced measurement samples to be transmitted over dsi3 */

  uint16_t          ApxMeasMaskDirect                   : 7;        /**< Period at which echo measurement results should be ignored in direct mode */
  uint16_t          ApxMeasMaskIndirect                 : 7;        /**< Period at which echo measurement results should be ignored in indirect mode */
  uint16_t          reserved106                         : 2;        /**< unused memory space */
} Meas_sAdvancedPathProfile;
typedef union
{
  Meas_sAdvancedPathProfile       fields;
  uint16_t                        halfwords[MEAS_ADVANCEDPATHPROFILE_SIZE];
} Meas_uAdvancedPathProfile;

/* measurement parameters - nfd settings - struct and union */
typedef struct
{
  uint16_t          NfdCtrlSens                         : 3;        /**< NFD_CTRL: Echo evaluation sensitivity */
  uint16_t          NfdCtrlIrq                          : 2;        /**< NFD_CTRL: NFD interrupt configuration */
  uint16_t          reserved136                         : 11;        /**< unused memory space */

  uint16_t          NfdThreshold                        ;           /**< NFD minimum detection threshold */
} Meas_sNfdSettings;
typedef union
{
  Meas_sNfdSettings               fields;
  uint16_t                        halfwords[MEAS_NFDSETTINGS_SIZE];
} Meas_uNfdSettings;

/* measurement parameters - nfd settings 2 - struct and union */
typedef struct
{
  uint16_t          Nfd2Start                           : 8;        /**< NFD start of NFD window */
  uint16_t          Nfd2Length                          : 8;        /**< NFD length of NFD window */

  uint16_t          Nfd2Thres                           :10;        /**< NFD threshold value */
  uint16_t          reserved142                         : 6;        /**< unused memory space */
} Meas_sNfdSettings2;

typedef union
{
  Meas_sNfdSettings2              fields;
  uint16_t                        halfwords[MEAS_NFDSETTINGS2_SIZE];
} Meas_uNfdSettings2;

/* measurement parameters - dsi settings - struct and union */
typedef struct
{
  uint16_t          ChipTime                            : 2;        /**< DSI3 transmitter chip time */
  uint16_t          Dsi3Debounce                        : 3;        /**< DSI3 debouncer -> t_debounce = (2^Dsi3Debounce)*1/24Mhz */
  uint16_t          SyncDsi3                            : 3;        /**< DSI3 mode of synchronization */
  uint16_t          SyncFreq                            : 1;        /**< Measurement burst and sampling frequency compensation enabled flag */
  uint16_t          RCCCurrentOffset                    : 3;        /**< DSI3 RCC current offset configuration */

  uint16_t          CrmFccBlankTime                     :13;        /**< DSI3 blanking time after crm command */
  uint16_t          RCCSlopeSel                         : 3;        /**< DSI3 RCCSlope configuration */

  uint16_t          PdcmFccBlankTime                    :13;        /**< DSI3 blanking time after pdcm command */
  uint16_t          FCC_t_bit                           : 2;        /**< DSI3 FCC bit time configuration */
  uint16_t          RCCCurveSel                         : 1;        /**< DSI3 RCC curve selection configuration */

  uint16_t          PdcmPeriod                          :14;        /**< DSI3 period of one pdcm cycle */
  uint16_t          reserved150                         : 2;        /**< unused memory space */

  uint16_t          PdcmRespSensor1                     :14;        /**< DSI3 start time of sensor 1 pdcm response */
  uint16_t          reserved152                         : 2;        /**< unused memory space */

  uint16_t          PdcmRespSensor2                     :14;        /**< DSI3 start time of sensor 2 pdcm response */
  uint16_t          reserved154                         : 2;        /**< unused memory space */

  uint16_t          PdcmRespSensor3                     :14;        /**< DSI3 start time of sensor 3 pdcm response */
  uint16_t          reserved156                         : 2;        /**< unused memory space */

  uint16_t          PdcmRespSensor4                     :14;        /**< DSI3 start time of sensor 4 pdcm response */
  uint16_t          reserved158                         : 2;        /**< unused memory space */

  uint16_t          PdcmRespSensor5                     :14;        /**< DSI3 start time of sensor 5 pdcm response */
  uint16_t          reserved160                         : 2;        /**< unused memory space */

  uint16_t          PdcmRespSensor6                     :14;        /**< DSI3 start time of sensor 6 pdcm response */
  uint16_t          reserved162                         : 2;        /**< unused memory space */

  uint16_t          PdcmRespSensor7                     :14;        /**< DSI3 start time of sensor 7 pdcm response */
  uint16_t          reserved164                         : 2;        /**< unused memory space */
} Meas_sDsiSettings;

typedef union
{
  Meas_sDsiSettings               fields;
  uint16_t                        halfwords[MEAS_DSISETTINGS_SIZE];
} Meas_uDsiSettings;

/* measurement parameters - monitoring - struct and union */
typedef struct
{
  uint16_t          MonStart                            :11;        /**< Monitoring time to start */
  uint16_t          MonDs                               : 3;        /**< Monitoring down sampling */
  uint16_t          reserved167                         : 2;        /**< unused memory space */

  uint16_t          MonCh0                              : 3;        /**< Monitoring signals to be monitored on channel 0 */
  uint16_t          MonCh1                              : 3;        /**< Monitoring signals to be monitored on channel 1 */
  uint16_t          MonCh2                              : 3;        /**< Monitoring signals to be monitored on channel 2 */
  uint16_t          MonCh3                              : 3;        /**< Monitoring signals to be monitored on channel 3 */
  uint16_t          reserved168                         : 4;        /**< unused memory space */
} Meas_sMonitoring;

typedef union
{
  Meas_sMonitoring                fields;
  uint16_t                        halfwords[MEAS_MONITORING_SIZE];
} Meas_uMonitoring;


/* measurement parameters - data for self test - struct and union */
typedef struct
{
  uint16_t          CrcOtp                              : 1;       /**< Perform self test mask - Perform CRC check on OTP */
  uint16_t          CrcSysRom                           : 1;       /**< Perform self test mask - Perform CRC check on SysROM */
  uint16_t          CrcEeprom                           : 1;       /**< Perform self test mask - Perform CRC check on EEPROM (configuration parameters) */
  uint16_t          CrcRam                              : 1;       /**< Perform self test mask - Perform CRC check on RAM (configuration parameters) */
  uint16_t          CapLossVddd                         : 1;       /**< Perform self test mask - Perform a capacitor loss measurement on VDDD */
  uint16_t          CapLossVdda                         : 1;       /**< Perform self test mask - Perform a capacitor loss measurement on VDDA */
  uint16_t          VoltSup                             : 1;       /**< Perform self test mask - Perform a voltage measurement at VSUP */
  uint16_t          VoltVtank                           : 1;       /**< Perform self test mask - Perform a voltage measurement at VTANK */
  uint16_t          VoltVref                            : 1;       /**< Perform self test mask - Perform a voltage measurement at VREF */
  uint16_t          VoltVddd                            : 1;       /**< Perform self test mask - Perform a voltage measurement at VDDD */
  uint16_t          VoltTempSensor                      : 1;       /**< Perform self test mask - Perform a voltage measurement at temperature sensor */
  uint16_t          DigitalSignalPath                   : 1;       /**< Perform self test mask - Perform a digital signal path test */
  uint16_t          InternalSignalPath                  : 1;       /**< Perform self test mask - Perform an internal signal path test */
  uint16_t          reserved170_5                       : 1;       /**< unused memory space */
  uint16_t          Ringing                             : 1;       /**< Perform self test mask - Perform a ringing frequency, ringing time measurement and driver check */
  uint16_t          reserved170_7                       : 1;       /**< unused memory space */
  uint16_t          CapVdddMin                          : 8;       /**<  */
  uint16_t          CapVdddMax                          : 8;       /**<  */
  uint16_t          CapVddaMin                          : 8;       /**<  */
  uint16_t          CapVddaMax                          : 8;       /**<  */

  uint16_t          RingingFregLim                       : 4;      /**< Relative limit in percent for signal self test ringing frequency */
  uint16_t          RingingTimeLim                       : 2;      /**< Relative limit in percent for signal self test ringing time */
  uint16_t          HeightLim                            : 4;      /**< Relative limit in percent for signal self test echo height */
  uint16_t          TofLim                               : 4;      /**< Relative limit in percent for signal self test echo time of flight */
  uint16_t          ConfLim                              : 2;      /**< Relative limit in percent for signal self test confidence level */

} Meas_sDataForSelfTest;

typedef union
{
  Meas_sDataForSelfTest           fields;
  uint16_t                        halfwords[MEAS_DATAFORSELFTEST_SIZE];
} Meas_uDataForSelfTest;


/* measurement parameters - data for time of flight compensation */
typedef struct
{
  uint16_t          SPA_TOF_compensation_time           : 8;        /**< Datafield for customer to write time of flight compensation for standard path profile a in 32us steps */
  uint16_t          SPA_meas_time                       : 8;        /**< Datafield for customer to write time of flight compensation for standard path profile a in 256us steps */
  uint16_t          SPB_TOF_compensation_time           : 8;        /**< Datafield for customer to write time of flight compensation for standard path profile b in 32us steps */
  uint16_t          SPB_meas_time                       : 8;        /**< Datafield for customer to write time of flight compensation for standard path profile b in 256us steps */
  uint16_t          SPC_TOF_compensation_time           : 8;        /**< Datafield for customer to write time of flight compensation for standard path profile c in slave */
  uint16_t          SPC_meas_time                       : 8;        /**< Datafield for customer to write time of flight compensation for standard path profile c in 256us steps */
  uint16_t          APA_TOF_compensation_time           : 8;        /**< Datafield for customer to write time of flight compensation for advanced path profile a in 32us steps */
  uint16_t          APA_meas_time                       : 8;        /**< Datafield for customer to write time of flight compensation for advanced path profile a in 256us steps */
  uint16_t          APB_TOF_compensation_time           : 8;        /**< Datafield for customer to write time of flight compensation for advanced path profile b in slave */
  uint16_t          APB_meas_time                       : 8;        /**< Datafield for customer to write time of flight compensation for advanced path profile b in 256us steps */
  uint16_t          reserved188                            ;        /**< unused memory space */
  uint16_t          reserved190                            ;        /**< unused memory space */
  uint16_t          reserved192                            ;        /**< unused memory space */
  uint16_t          HardwareRevision                       ;        /**< Hardware revision number */
  uint16_t          SoftwareRevision                       ;        /**< Software revision number */

} Meas_sTimeOfFlightCompensation;

typedef union
{
  Meas_sTimeOfFlightCompensation  fields;
  uint16_t                        halfwords[MEAS_TOF_COMPENSATION_SIZE];
} Meas_uTofCompensation;


/* measurement parameters - crc calculation - struct and union */
typedef struct
{
  uint16_t          CrcOtp                                 ;                    /**< Self-Test Crc over otp */
  uint16_t          CrcSysRom                              ;                    /**< Self-Test Crc over SysRom */
  uint16_t          CrcEepromOrRam                         ;                    /**< Self-Test Crc over Eeprom */
} Meas_sCrcCalculation;

typedef union
{
  Meas_sCrcCalculation            fields;
  uint16_t                        halfwords[MEAS_CRCCALCULATION_SIZE];
} Meas_uCrcCalculation;

/* measurement parameters - slave id - struct and union */
typedef struct
{
  uint16_t          reserved204                            ;                    /**< unused memory space */
  uint16_t          reserved206                         : 8;                    /**< unused memory space */
  uint16_t          SlaveId                             : 4;                    /**< CRM slave id of the sensor */
  uint16_t          reserved207                         : 4;                    /**< unused memory space */
} Meas_sSlaveId;

typedef union
{
  Meas_sSlaveId                   fields;
  uint16_t                        halfwords[MEAS_SLAVEID_SIZE];
} Meas_uSlaveId;

typedef struct
{
  Meas_uGeneralSettings                 GeneralSettings;                        /**< meas parameters - general settings field */
  Meas_uNoiseMeasurement                NoiseMeasurement;                       /**< meas parameters - noise measurement field */
  Meas_uStandardPathProfile             StandardPathProfileA;                   /**< meas parameters - standard path profile A field */
  Meas_uStandardPathProfile             StandardPathProfileB;                   /**< meas parameters - standard path profile B field */
  Meas_uStandardPathProfile             StandardPathProfileC;                   /**< meas parameters - standard path profile C field */
  Meas_uAdvancedPathProfile             AdvancedPathProfileA;                   /**< meas parameters - advanced path profile A field */
  Meas_uAdvancedPathProfile             AdvancedPathProfileB;                   /**< meas parameters - advanced path profile B field */
  Meas_uNfdSettings                     NfdSettings;                            /**< meas parameters - nfd settings field */
  Meas_uNfdSettings2                    NfdSettings2;                           /**< meas parameters - nfd settings 2 field */
  Meas_uDsiSettings                     DsiSettings;                            /**< meas parameters - dsi settings field */
  Meas_uMonitoring                      Monitoring;                             /**< meas parameters - monitoring field */
  Meas_uDataForSelfTest                 DataForSelfTest;                        /**< meas parameters - data for self test field */
  Meas_uTofCompensation                 TimeOfFlightCompensation;               /**< meas parameters - data for time of flight compensation */
  Meas_uCrcCalculation                  CrcCalculation;                         /**< meas parameters - crc calculation field */
  Meas_uSlaveId                         SlaveId;                                /**< meas parameters - slave id field */
} Meas_sMeasurementParameters_t;

typedef union
{
  Meas_sMeasurementParameters_t         data;                                   /**< struct containing all meas related data */
  uint16_t                              halfwords[MEAS_SETTINGS_SIZE];          /**< 16 bit array for direct access to the struct */
} Meas_uMeasurementParameters_t;

/** Measurement FSM States */
typedef enum
{
   meas_eMeas_STATE_IDLE                                                = 0u,   /**< Meas state machine - nothing to do here */
   meas_eMeas_STATE_INIT,                                                       /**< Meas state machine - init phase - set parameters */
   meas_eMeas_STATE_DIAG_MEAS,                                                  /**< Meas state machine - diagnose meas Vcc & temperature */
   meas_eMeas_STATE_PRE_NOISE_MEAS,                                             /**< Meas state machine - wait for noise measurement phase to begin */
   meas_eMeas_STATE_NOISE_MEAS,                                                 /**< Meas state machine - diagnose meas noise */
   meas_eMeas_STATE_INIT_ECHO_MEAS,                                             /**< Meas state machine - prepare echo detection phase */
   meas_eMeas_STATE_PRE_ECHO_MEAS,                                              /**< Meas state machine - wait for echo detection phase */
   meas_eMeas_STATE_ECHO_MEAS_MASKED,                                           /**< Meas state machine - echo detection phase in which results are invalid */
   meas_eMeas_STATE_ECHO_MEAS,                                                  /**< Meas state machine - echo detection phase */
   meas_eMeas_STATE_ECHO_MEAS_2,                                                /**< Meas state machine - echo detection phase */
   meas_eMeas_STATE_ECHO_MEAS_3,                                                /**< Meas state machine - echo detection phase */
   meas_eMeas_STATE_POST_MEAS,                                                  /**< Meas state machine - measurement finished phase */
   meas_eMeas_STATE_POST_LAB,                                                   /**< Meas state machine - labmode finished phase */
} Meas_eMeasurementState_t;

/** Lab mode down sampling modes */
typedef enum
{
   meas_eDown_SAMPLE_EVERYTHING                                         = 0u,   /**< Sample mode - Take every n-th sampling point */
   meas_eDown_SAMPLE_MEAN_VALUE,                                                /**< Sample mode - Calculate the mean value from the last n samples */
   meas_eDown_SAMPLE_MAX_VALUE                                                  /**< Sample mode - Calculate the max value from the last n samples */
} Meas_eDownSamplingModes_t;

/** DMA Channels */
typedef enum
{
  Ch1                 = 0u,                                                     /**< Channel assignment for the runtime data arrays */
  Ch2                 = 1u,                                                     /**< Channel assignment for the runtime data arrays */
  Ch3                 = 2u,                                                     /**< Channel assignment for the runtime data arrays */
  Ch4                 = 3u,                                                     /**< Channel assignment for the runtime data arrays */
}Lab_eDmaChannels_t;

/** Measurement types */
typedef enum
{
  meas_eMeasKind_STANDARD       = 0u,                                           /**< Meas kind flag - standard measurement */
  meas_eMeasKind_ADVANCED       = 1u,                                           /**< Meas kind flag - advanced measurement */
} Meas_eMeasurementKind_t;

/** Measuremnt Configurations */
typedef enum
{
  meas_eMeasConf_NONE           = 0u,                                           /**< Meas config - no measurement */
  meas_eMeasConf_DIRECT         = 1u,                                           /**< Meas config - direct measurement / chirp up */
  meas_eMeasConf_DIRECT_INV     = 2u,                                           /**< Meas config - direct measurement / inverted chirp up */
  meas_eMeasConf_INDIRECT       = 3u,                                           /**< Meas config - indirect measurement */
} Meas_eMeasurementConf_t;

/** Impedance Measurement configuration */
typedef enum
{
  imp_eImpConf_NO_MEASUREMENT_1        = 0u,                                    /**< Imp config - sensor in idle mode */
  imp_eImpConf_IMPEDANCE_MEASUREMENT   = 1u,                                    /**< Imp config - An impedance measurement shall be performed  */
  imp_eImpConf_NO_MEASUREMENT_2        = 2u,                                    /**< Imp config - sensor in idle mode */
  imp_eImpConf_NO_MEASUREMENT_3        = 3u,                                    /**< Imp config - sensor in idle mode */
} Imp_eMeasurementConf_t;

/** Measurement modes */
typedef enum
{
  meas_eMeasMode_APPLICATION    = 0u,                                           /**< Meas mode - application mode */
  meas_eMeasMode_LAB            = 1u,                                           /**< Meas mode - lab mode */
  meas_eMeasMode_APPLAB         = 2u,                                           /**< Meas mode - application and lab mode */
  meas_eMeasMode_APPLICATION2   = 3u,                                           /**< Meas mode - application mode */
} Meas_eMeasurementMode_t;

/** Measurement profiles*/
typedef enum
{
  meas_eMeasProfile_NOCHANGE    = 0u,                                           /**< meas profile - use current register contents -> not used anymore SMA52417-134*/
  meas_eMeasProfile_PROFILEA    = 1u,                                           /**< meas profile - use profile a */
  meas_eMeasProfile_PROFILEB    = 2u,                                           /**< meas profile - use profile b */
  meas_eMeasProfile_PROFILEC    = 3u,                                           /**< meas profile - standard: use profile c / advanced: use current register contents */
} Meas_eMeasurementProfile_t;                                                   /**< measurement profile */

/** Measurement runtime data*/
typedef struct
{
  Meas_eMeasurementKind_t                 MeasurementKind;                      /**< Selected Standard or Advanced Measurement */
  Meas_eMeasurementConf_t                 MeasurementConf;                      /**< Selected direct or indirect measurement */
  Meas_eMeasurementMode_t                 MeasurementMode;                      /**< Selected measurement mode */
  Meas_eMeasurementProfile_t              MeasurementProfile;                   /**< Selected measurement profile */
  bool_t                                  MeasAbortFlag;                        /**< Flag, that indication the manual abortion of a measurement */
  uint16_t                                MaskingTime;                          /**< Period after which a measurement result is valid */
  uint16_t                                MinConf;                              /**< Min confidence level for advanced measurement samples to be transmitted over dsi3 */
  uint16_t                                TOF_Compensation;                     /**< Time of flight compensation time for selected measurement in us */
  uint16_t                                Meas_time;                            /**< Measurement duration in 256us steps */
  uint16_t                                preCalcMaxPdcmDeviation;              /**< max deviation of PdcmPeriod that is allowed (3%)*/
} Dsi3Drv_sMeasCtrl_RuntimeData_t;

/** Lab mode DMA buffers */
typedef enum
{
  buffer1                 = 0u,                                                 /**< First of two usable DMA buffers */
  buffer2                 = 1u,                                                 /**< Second of two usable DMA buffers */                                          /**< EEVAL event type - Maximum above threshold on ENVP_ENV_RAW detected */
}Lab_eBuffer_t;

typedef struct
{
  uint16_t                                timestamp;                            /**< EEVAL data packet - timestamp of the event */
  uint16_t                                envpEnvRaw    :14;                    /**< EEVAL data packet - ENVP_ENV_RAW[15:2] data */
  uint16_t                                eventType     : 2;                    /**< EEVAL data packet - Event type identification */
}Meas_sEevalStdDataPacketFormat0;

typedef struct
{
  uint16_t                                timestamp;                            /**< EEVAL data packet - timestamp of the event */
  uint16_t                                ampdEnv       : 8;                    /**< EEVAL data packet - AMPD_ENV[7:0] data */
  uint16_t                                reserved      : 6;
  uint16_t                                eventType     : 2;                    /**< EEVAL data packet - Event type identification */
}Meas_sEevalStdDataPacketFormat1;

typedef struct
{
  uint16_t                                timestamp;                            /**< EEVAL data packet - timestamp of the event */
  uint16_t                                envData;                              /**< EEVAL data packet - Envelope data */
  uint16_t                                confLvl       : 4;                    /**< EEVAL data packet - Confidence level */
  uint16_t                                reserved      :12;
}Meas_sEevalAdvDataPacketFormat;


typedef union
{
  Meas_sEevalStdDataPacketFormat0         std_type0[MEAS_STDRESULTBUF_MAX];     /**< EEVAL Data packet format for standard path for EEVAL_CTRL.eeval_dma_val=0 */
  Meas_sEevalStdDataPacketFormat1         std_type1[MEAS_STDRESULTBUF_MAX];     /**< EEVAL Data packet format for standard path for EEVAL_CTRL.eeval_dma_val=1 */
  Meas_sEevalAdvDataPacketFormat          adv[MEAS_ADVRESULTBUF_DUAL_PATH_MAX]; /**< EEVAL Data packet for advanced Path 1 & 2 */
  uint16_t                                lab[MEAS_GLOBAL_BUFFER_SIZE];         /**< Raw data signals for lab mode */
  uint16_t                                raw[MEAS_GLOBAL_BUFFER_SIZE];         /**<  */
} Meas_uEevalDataPacket;

typedef struct
{
  bool_t                    AccquisitionFinished;                               /**< Indicates if the Diagnostic Measurement has finished */
  bool_t                    ResultsReadout;                                     /**< Indicates if the Diagnostic Measurement results have been readout */
  uint16_t                  VSUP;                                               /**< Supply voltage */
  uint16_t                  Temperature;                                        /**< Sensor temperature */
  uint16_t                  NoiseMeasSamplesTaken;                              /**< Number of recorded envelope samples in this noise measurement cycle */
  uint16_t                  NoiseMeasNoiseCount;                                /**< Counter for threshold overrun envelope samples in this noise measurement cycle */
  uint16_t                  NoiseMeasNoiseSum;                                  /**< Sum of all envelope samples in this noise measurement cycle */
} Meas_sDiagnosticMeasurement;

typedef struct
{
  bool_t                    AccquisitionFinished;                               /**< Indicates if the Burst Monitoring Measurement has finished */
  bool_t                    ResultsReadout;                                     /**< Indicates if the Burst Monitoring results have been readout */
  uint16_t                  VoltageVTANK1;                                      /**< First measurement result of VTANK during Diagnostic Measurement */
  uint16_t                  VoltageVTANK2;                                      /**< Last measurement result of VTANK during Diagnostic Measurement */
  uint16_t                  BurstLength;                                        /**< Length of transducer burst */
} Meas_sBurstMonitoring;

typedef struct
{
  bool_t                    AccquisitionFinished;                               /**< Indicates if the Ringing Behavior Measurement has finished */
  bool_t                    ResultsReadout;                                     /**< Indicates if the Ringing Behavior Measurement results have been readout */
  uint16_t                  RingTime;                                           /**< RTM time in �s the transducer rang after the burst */
  uint16_t                  RingSamples;                                        /**< RFM number of samples taken */
  uint16_t                  RingCount;                                          /**< RFM number of ringing periods after burst */
} Meas_sRingingBehavior;

typedef struct
{
  bool_t                    Nfd1Finished;                                       /**< NFD algorithm 1 has finished measuring */
  bool_t                    Nfd1Flag;                                           /**< NFD algorithm 1: min two nfd echos detected */
  uint8_t                   Nfd1Echo1;                                          /**< NFD algorithm 1: time in �s at which the first nfd echo has been detected */
  uint8_t                   Nfd1DeltaEcho2;                                     /**< NFD algorithm 1: time in �s after first nfd echo, the second nfd echo has been detected */
  uint8_t                   Nfd1DeltaEcho3;                                     /**< NFD algorithm 1: time in �s after second nfd echo, the third nfd echo has been detected */
  bool_t                    Nfd2Finished;                                       /**< NFD algorithm 2 has finished measuring */
  bool_t                    Nfd2Flag;                                           /**< NFD algorithm 2: energy in meas window above threshold */
  uint8_t                   Nfd2Result;                                         /**< NFD algorithm 2: energy in meas window */
} Meas_sNfdMeasurement;

typedef struct
{
  uint16_t*                               DmaBuffer1_ptr;                       /**< Pointer to the first of two DMA buffers */
  uint16_t*                               DmaBuffer2_ptr;                       /**< Pointer to the second of two DMA buffers */
} Lab_sDmaBuffers;

typedef struct
{
  uint16_t*                               ChannelHeads_ptr;                     /**< Holds the assigned buffer heads for each channel. Zero if the channel is not in use.CH1-Ch4 */
  uint16_t*                               ChannelTails_ptr;                     /**< Holds the tails of the following section */
  uint16_t*                               NextSectionTails_ptr;                 /**< Holds the tails of the following section */
  uint16_t*                               ChannelNextReadOut_ptr;               /**< Holds the position of next read out of each channel. Zero if the channel is not in use.CH1-Ch4 */
  uint16_t*                               DmaData;                              /**< */
  uint16_t*                               CurrentBuffer_ptr;                    /**<  */
  uint16_t*                               NextBuffer_ptr;                       /**< */
  uint16_t                                NextBufferOffset;
  uint16_t                                CurrentBufferOffset;
  bool_t                                  IsActive;
} Lab_sChData;


typedef struct
{
  Lab_sChData                             ChData[4];                            /**< Channel runtime data */
  Lab_sDmaBuffers                         DmaBuffer_ptrs[4];                    /**< DMA buffer pointer - two buffer for every channel */
  uint16_t                                DummyBuffer[MEAS_EDI_DMA_SAMPLES_TOTAL];

  uint16_t**                              FillingLevelHead;
  uint16_t**                              FillingLevelNextSection;
  uint16_t                                MonitoringSamples;                    /**< Number of samples which should be monitored */

  uint16_t                                MonStart;                             /**< EEPROM copy as standard type to reduce the access time */
  uint16_t                                SampleCounter;                        /**< Only used in Speedmode */
  uint16_t                                Speedmode_samples_max;                /**< Number of max samples in speedmode depending on the number of active channels */
  uint8_t                                 LastSentFrameType;                    /**< Type of last sent frame type */
  Lab_eBuffer_t                           DmaBufferBlocked;                     /**< Data buffer which was last used by DMA*/

  bool_t                                  DmaBuffersPendingData;                /**< */
  bool_t                                  IsFinished;                           /**< Stores the state of every channel*/
  bool_t                                  IsInitialised;                        /**< Init State */
  bool_t                                  IsRunning;                            /**< Lab mode running state */
  bool_t                                  Speedmode;                            /**< DMA stores data directly in the result buffer - 4 channels are used*/
  bool_t                                  dma_buffer_bigger_than_downsampling;  /**< */
} Meas_sLabModeRuntimeData;
/*
1. Meas_sDiagnosticMeasurement DiagnosticMeasurement: 存储诊断性测量的结果，如供电电压、温度等。
2. Meas_sBurstMonitoring BurstMonitoring: 存储突发监控的测量结果。3. Meas_sRingingBehavior RingingBehaviour: 存储振铃行为相关的测量结果。
4. Meas_sLabModeRuntimeData LabModeRuntimeData: 存储实验室模式下的运行时数据。5. Meas_sNfdMeasurement NearFieldDetection: 存储近场检测相关的测量结果。
6. uint16_t MeasurementTime: 记录本次回波测量周期所用的时间。7. uint16_t SyncedMeasurementTime: 记录与DSP同步的本次回波测量周期所用时间。
8. uint16_t MeasRingbufTail 和 MeasRingbufTail2: 分别表示测量结果缓冲区1和2的尾部指针，用于追踪缓冲区中最新添加的数据位置。
9. uint16_t MeasRingbufHead 和 MeasRingbufHead2: 分别表示测量结果缓冲区1和2的头部指针，用于追踪缓冲区中待读取数据的位置。10. uint16_t MaxMeasurementSamples: 存储最大测量样本数。
11. uint8_t NoiseAtgThreshold: 存储噪声ATG阈值，这个值是从EEPROM中复制过来的标准类型，目的是减少访问EEPROM的时间开销。12. Meas_uEevalDataPacket resultBuf: 结构体内嵌的一个数据包，用于存储测量结果的具体数据
*/
typedef struct
{
  Meas_sDiagnosticMeasurement             DiagnosticMeasurement;                /**< Measurement results of diagnostic measurement */
  Meas_sBurstMonitoring                   BurstMonitoring;                      /**< Measurement results of burst monitoring */
  Meas_sRingingBehavior                   RingingBehaviour;                     /**< Measurement results of ringing behavior */
  Meas_sLabModeRuntimeData                LabModeRuntimeData;                   /**< Runtime data of Lab mode */
  Meas_sNfdMeasurement                    NearFieldDetection;                   /**< Measurement results of near field detection */
  uint16_t                                MeasurementTime;                      /**< elapsed time in this echo measurement cycle */
  uint16_t                                SyncedMeasurementTime;               /**< elapsed time in this echo measurement cycle synced to DSP MeasurementTime */
  uint16_t                                MeasRingbufTail;                      /**< Tail pointer of measurement results buffer 1 */
  uint16_t                                MeasRingbufTail2;                     /**< Tail pointer of measurement results buffer 2 */
  uint16_t                                MeasRingbufHead;                      /**< Head pointer of measurement results buffer 1 */
  uint16_t                                MeasRingbufHead2;                     /**< Head pointer of measurement results buffer 2 */
  uint16_t                                MaxMeasurementSamples;                /**< Head pointer of measurement results buffer 2 */
  uint8_t                                 NoiseAtgThreshold;                    /**< EEPROM copy as standard type to reduce the access time  */

  Meas_uEevalDataPacket                   resultBuf;
}Meas_sMeasurementResults_t;

typedef struct
{
  Meas_eMeasurementState_t                      CurrentState;                   /**< Current state of measurement state machine */
  Dsi3Drv_sMeasCtrl_RuntimeData_t               RuntimeData;                    /**< Runtime data for measurement execution */
  Meas_uMeasurementParameters_t                 Parameters;                     /**< Struct with all measurement configuration data */
  Meas_sMeasurementResults_t                    Results;                        /**< Memory for Measurement Results */
} Dsi3Drv_sMeasCtrl_t;

typedef		Dsi3Drv_sMeasCtrl_t*	        Dsi3Drv_pMeasCtrl_t;
typedef	const	Dsi3Drv_sMeasCtrl_t*	        Dsi3Drv_cpMeasCtrl_t;

/* ****************************************************************************/
/* control data for EEPROM access & measurement data  */
/* ****************************************************************************/
typedef		Meas_uMeasurementParameters_t*  Dsi3Drv_pMEMCtrl_t;

/* ****************************************************************************/
/* control data for application */
/* ****************************************************************************/
typedef struct
{
  Dsi3Drv_pMEMCtrl_t        EepromCtrl;
  Dsi3Drv_pDSI3Ctrl_t       DSI3Ctrl;
  Dsi3Drv_pMeasCtrl_t       MeasCtrl;
} Dsi3Drv_sApplCtrlData_t;                                                              /**< Application control and runtime data */

typedef   Dsi3Drv_sApplCtrlData_t*  Dsi3Drv_pApplCtrlData_t;
typedef const Dsi3Drv_sApplCtrlData_t*  Dsi3Drv_cpApplCtrlData_t;

#endif /* APP_DEFS_H_ */
