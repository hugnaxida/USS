/***************************************************************************//**
 * @file      mod_dsi3.h
 *
 * @author    StSl
 * @date      21.09.2017
 *
 * @brief     Callback functions for DSI3 bus layer (header)
 *
 * This file contains all callbacks for the DSI3 interface
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
 * $Id: mod_dsi3.h 406 2019-02-08 15:49:42Z siko $
 *
 * $Revision: 406 $
 *
 ******************************************************************************/

#ifndef DSI3_CALLBACKS_H_
#define DSI3_CALLBACKS_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "def_app.h"
#include "Dsi3Bus_Interface.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define DSI3_COMERRBIT_NOTSET                               (0u)                  /**< CRM answer ComErr bit - no error occurred */
#define DSI3_COMERRBIT_SET                                  (1u)                  /**< CRM answer ComErr bit - error occurred */

#define DSI3_STATUSBITS_NOTUSED                             (0x0u)                /**< CRM answer status bits - not used */
#define DSI3_STATUSBITS_OK                                  (0x1u)                /**< CRM answer status bits - received "command" frame was valid and will be performed */
#define DSI3_STATUSBITS_ERROR                               (0x2u)                /**< CRM answer status bits - received "command" frame was not valid and will not be perfomred */
#define DSI3_STATUSBITS_BUSY                                (0x3u)                /**< CRM answer status bits - received "command" frame was valid, but the sensor is still occupied with last command, the command will not be performed */

#define DSI3_PDCM_ANSWER_FRAME_LENGTH                       (8u)                  /**< size of PDCM response frame in byte */

#define DSI3_MEASSTOP_STOP                                  (0x3)                 /**< CRM meas stop cmd - stop measurement operation*/

#define DSI3_MEASSETTINGS_READ                              (0u)                  /**< CRM meas settings cmd - R/W bit is read */
#define DSI3_MEASSETTINGS_WRITE                             (1u)                  /**< CRM meas settings cmd - R/W bit is write */
#define DSI3_MEASSETTINGS_ADRMAX                            (203u)                /**< CRM meas settings cmd - range of address field */

#define DSI3_EEPROMACC_OP1_WRITE_EEPROM_TO_RAM              (0x1u)                /**< CRM EEPROM access cmd - operation - Write config. parameters from EEPROM to RAM */
#define DSI3_EEPROMACC_OP2_ENABLE_EEPROM                    (0x2u)                /**< CRM EEPROM access cmd - operation - Enable EEPROM programming */
#define DSI3_EEPROMACC_OP3_WRITE_RAM_TO_EEPROM              (0x4u)                /**< CRM EEPROM access cmd - operation - Program config. parameters from RAM to EEPROM */
#define DSI3_EEPROMACC_OP4_COPY_SLAVEID_TO_EEPROM           (0x8u)                /**< CRM EEPROM access cmd - operation - Program SLAVE_ID from RAM to EEPROM */
#define DSI3_EEPROMACC_PASSWORD_OP1                         (0xAAu)               /**< CRM EEPROM access cmd - password for DSI3_EEPROMACC_OP1_WRITE_EEPROM_TO_RAM */
#define DSI3_EEPROMACC_PASSWORD_OP2                         (0x66u)               /**< CRM EEPROM access cmd - password for DSI3_EEPROMACC_OP2_ENABLE_EEPROM */
#define DSI3_EEPROMACC_PASSWORD_OP3                         (0x33u)               /**< CRM EEPROM access cmd - password for DSI3_EEPROMACC_OP3_WRITE_RAM_TO_EEPROM */
#define DSI3_EEPROMACC_PASSWORD_OP4                         (0x55u)               /**< CRM EEPROM access cmd - password for DSI3_EEPROMACC_OP4_COPY_SLAVEID_TO_EEPROM */

#define DSI3_IC_REGACCESS_READ                              (0u)                  /**< CRM IC register access cmd - R/W bit is read */
#define DSI3_IC_REGACCESS_WRITE                             (1u)                  /**< CRM IC register access cmd - R/W bit is write */
#define DSI3_IC_REGACCESS_MODNUM_MAX                        (22u)                 /**< CRM IC register access cmd - range of base address */
#define DSI3_IC_REGACCESS_MODNUM_CNT      (DSI3_IC_REGACCESS_MODNUM_MAX + 1)      /**< CRM IC register access cmd - amount of base address *//*-?|AP2|wladimir.pauls|c38|?*/

#define DSI3_ICMODE_OP1_DISCOVERY_MODE                      (0x01u)               /**< CRM Ic mode cmd - ICMode - switch to discovery mode */
#define DSI3_ICMODE_OP2_SELF_TEST                           (0x02u)               /**< CRM Ic mode cmd - ICMode - switch to self test mode */
#define DSI3_ICMODE_OP3_SOFTWARE_RESET                      (0x04u)               /**< CRM Ic mode cmd - ICMode - execute software reset */
#define DSI3_ICMODE_OP4_STANDBY                             (0x08u)               /**< CRM Ic mode cmd - ICMode - switch to standby */
#define DSI3_ICMODE_OP5_WAKE_UP                             (0x10u)               /**< CRM Ic mode cmd - ICMode - execute wake up */
#define DSI3_ICMODE_OP6_DSP_ON                              (0x20u)               /**< CRM Ic mode cmd - ICMode - execute dsp on */
#define DSI3_ICMODE_OP7_DSP_OFF                             (0x40u)               /**< CRM Ic mode cmd - ICMode - execute dsp off */
#define DSI3_ICMODE_OP8_TBD                                 (0x80u)               /**< CRM Ic mode cmd - ICMode - tbd */
#define DSI3_ICMODE_PASSWORD                                (0x55u)               /**< CRM Ic mode cmd - password IC mode cmd */


#define DSI3_CRM_CHIPTIME_MAX_DEVIATION                     (23)                  /**< max deviation of chiptime (3% of 24 cycle counts -> 23/32 ->23 frac) */
#define DSI3_CRM_CHIPTIME_EXPECTED                          (0x0300)              /**< expected SYNC_Counter value */
#define DSI3_SYNC_COUNT_ERROR_MAX                           (5u)                  /**< maximum sync_deviation_errors that are allowed before communication error flag is set */

#if defined (FPGA_52417B)
#define CRM_ASSIGNID_BITMASK_RD_NAD     (0x07u)
#define DSI3_NAD_MAX_CUSTOM             (0x07u)
#define DSI3_CRM_RESPONSE_NOK_SYMBOL    (0x7Fu)
#define DSI3_CRM_RESPONSE_OK_SYMBOL     (0x80u)
typedef enum
{
  loc_eIDAssign_SubCmd_EnableStore        = 1u,
  loc_eIDAssign_SubCmd_StoreBusAndNad     = 3u,
  loc_eIDAssign_SubCmd_ChangeBusAndNad    = 7u,
} loc_eIDAssign_SubCmd_t;
#endif
/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/
typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC */
  uint8_t                                 Data2;                                          /**< CRM RegisterData */
  uint8_t                                 Data1;                                          /**< CRM Extended Data */
  uint8_t                                 Command                 : 4;                    /**< CRM Command */
  uint8_t                                 PhysicalAddress         : 4;                    /**< CRM NAD */
}Dsi3_sDefault_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC */
  uint8_t                                 Profile                 : 2;                    /**< Standard Measurement - Profile */
  uint8_t                                 Mode                    : 2;                    /**< Standard Measurement - Mode */
  uint8_t                                 Sensor1                 : 2;                    /**< Standard Measurement - Sensor 1 */
  uint8_t                                 Sensor2                 : 2;                    /**< Standard Measurement - Sensor 2 */
  uint8_t                                 Sensor3                 : 2;                    /**< Standard Measurement - Sensor 3 */
  uint8_t                                 Sensor4                 : 2;                    /**< Standard Measurement - Sensor 4 */
  uint8_t                                 Sensor5                 : 2;                    /**< Standard Measurement - Sensor 5 */
  uint8_t                                 Sensor6                 : 2;                    /**< Standard Measurement - Sensor 6 */
  uint8_t                                 Command                 : 4;                    /**< CRM Command */
  uint8_t                                 PhysicalAddress         : 4;                    /**< CRM NAD */
}Dsi3_sMeasurementExecute_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC */
  uint8_t                                 Profile                 : 2;                    /**< Advanced Measurement - Profile */
  uint8_t                                 Mode                    : 2;                    /**< Advanced Measurement - Mode */
  uint8_t                                 Sensor1                 : 2;                    /**< Advanced Measurement - Sensor 1 */
  uint8_t                                 Sensor2                 : 2;                    /**< Advanced Measurement - Sensor 2 */
  uint8_t                                 Sensor3                 : 2;                    /**< Advanced Measurement - Sensor 3 */
  uint8_t                                 Sensor4                 : 2;                    /**< Advanced Measurement - Sensor 4 */
  uint8_t                                 Sensor5                 : 2;                    /**< Advanced Measurement - Sensor 5 */
  uint8_t                                 Sensor6                 : 2;                    /**< Advanced Measurement - Sensor 6 */
  uint8_t                                 Command                 : 4;                    /**< CRM Command */
  uint8_t                                 PhysicalAddress         : 4;                    /**< CRM NAD */
}Dsi3_sAdvMeasurementExecute_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC */
  uint8_t                                 FillBits                : 4;                    /**< No data. Filled with zeroes*/
  uint8_t                                 Sensor1                 : 2;                    /**< Measurement Stop Flag - Sensor 1 */
  uint8_t                                 Sensor2                 : 2;                    /**< Measurement Stop Flag - Sensor 2 */
  uint8_t                                 Sensor3                 : 2;                    /**< Measurement Stop Flag - Sensor 3 */
  uint8_t                                 Sensor4                 : 2;                    /**< Measurement Stop Flag - Sensor 4 */
  uint8_t                                 Sensor5                 : 2;                    /**< Measurement Stop Flag - Sensor 5 */
  uint8_t                                 Sensor6                 : 2;                    /**< Measurement Stop Flag - Sensor 6 */
  uint8_t                                 Command                 : 4;                    /**< CRM Command */
  uint8_t                                 PhysicalAddress         : 4;                    /**< CRM NAD */
}Dsi3_sMeasurementStop_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC */
  uint8_t                                 Address;                                        /**< Adress of measurement configuration data (0-203)*/
  uint8_t                                 FillBits                : 7;                    /**< No data. Filled with zeroes */
  uint8_t                                 RW                      : 1;                    /**< R/W Flag */
  uint8_t                                 Command                 : 4;                    /**< CRM Command */
  uint8_t                                 PhysicalAddress         : 4;                    /**< CRM NAD */
}Dsi3_sMeasurementSettings_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC */
  uint8_t                                 Password;                                       /**< Password für EEPROM Access*/
  uint8_t                                 Operation               : 4;                    /**< EEPROMAccess - Operation */
  uint8_t                                 FillBits                : 4;                    /**< No data. Filled with zeroes */
  uint8_t                                 Command                 : 4;                    /**< CRM Command */
  uint8_t                                 PhysicalAddress         : 4;                    /**< CRM NAD */
}Dsi3_sEEPROMAccess_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC */
  uint8_t                                 Address;                                        /**< Defines the address within the module*/
  uint8_t                                 ModAddr                 : 5;                    /**< Defines the base address of the module */
  uint8_t                                 FillBits                : 2;                    /**< No data. Filled with zeroes */
  uint8_t                                 RW                      : 1;                    /**< R/W Flag */
  uint8_t                                 Command                 : 4;                    /**< CRM Command */
  uint8_t                                 PhysicalAddress         : 4;                    /**< CRM NAD */
}Dsi3_sRegisterAccess_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC */
  uint8_t                                 Address                 : 5;                    /**< Read status information from the specific address*/
  uint8_t                                 FillBits2               : 3;                    /**< No data. Filled with zeroes */
  uint8_t                                 FillBits;                                       /**< No data. Filled with zeroes */
  uint8_t                                 Command                 : 4;                    /**< CRM Command */
  uint8_t                                 PhysicalAddress         : 4;                    /**< CRM NAD */
}Dsi3_sReadStatusInCRM_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC */
  uint8_t                                 Status0                 : 1;                    /**< Send Status0 in next PDCM Slot Flag*/
  uint8_t                                 Status1                 : 1;                    /**< Send Status1 in next PDCM Slot Flag*/
  uint8_t                                 Status2                 : 1;                    /**< Send Status2 in next PDCM Slot Flag*/
  uint8_t                                 Status3                 : 1;                    /**< Send Status3 in next PDCM Slot Flag*/
  uint8_t                                 Status4                 : 1;                    /**< Send Status4 in next PDCM Slot Flag*/
  uint8_t                                 Status5                 : 1;                    /**< Send Status5 in next PDCM Slot Flag*/
  uint8_t                                 Status6                 : 1;                    /**< Send Status6 in next PDCM Slot Flag*/
  uint8_t                                 Status7                 : 1;                    /**< Send Status7 in next PDCM Slot Flag*/
  uint8_t                                 Status8                 : 1;                    /**< Send Status8 in next PDCM Slot Flag*/
  uint8_t                                 Status9                 : 1;                    /**< Send Status9 in next PDCM Slot Flag*/
  uint8_t                                 Status10                : 1;                    /**< Send Status10 in next PDCM Slot Flag*/
  uint8_t                                 Status11                : 1;                    /**< Send Status11 in next PDCM Slot Flag*/
  uint8_t                                 Status12                : 1;                    /**< Send Status12 in next PDCM Slot Flag*/
  uint8_t                                 Status13                : 1;                    /**< Send Status13 in next PDCM Slot Flag*/
  uint8_t                                 Status14                : 1;                    /**< Send Status14 in next PDCM Slot Flag*/
  uint8_t                                 Status15                : 1;                    /**< Send Status15 in next PDCM Slot Flag*/
  uint8_t                                 Command                 : 4;                    /**< CRM Command */
  uint8_t                                 PhysicalAddress         : 4;                    /**< CRM NAD */
}Dsi3_sReadStatusInPDCM_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC */
  uint8_t                                 Password;                                       /**< Password has to be 0x55*/
  uint8_t                                 ICMode;                                         /**< New IC Mode */
  uint8_t                                 Command                 : 4;                    /**< CRM Command */
  uint8_t                                 PhysicalAddress         : 4;                    /**< CRM NAD */
}Dsi3_sIcMode_t;

typedef union{
  Dsi3Bus_CrmCommandFields_t              rawData;                                        /**< CRM command standard format */
  Dsi3_sDefault_t                         Default;                                        /**< CRM command default format (identical to standard format but with correct notation) */
  Dsi3_sMeasurementExecute_t              MeasurementExecute;                             /**< CRM command measurement execute format */
  Dsi3_sAdvMeasurementExecute_t           AdvMeasurementExecute;                          /**< CRM command advanced measurement execute format */
  Dsi3_sMeasurementStop_t                 MeasurementStop;                                /**< CRM command measurement stop format */
  Dsi3_sMeasurementSettings_t             MeasurementSettings;                            /**< CRM command measurement settings format */
  Dsi3_sEEPROMAccess_t                    EepromAccess;                                   /**< CRM command eeprom access format */
  Dsi3_sRegisterAccess_t                  RegisterAccess;                                 /**< CRM command register access format */
  Dsi3_sReadStatusInCRM_t                 ReadStatusInCrm;                                /**< CRM command read status in crm format */
  Dsi3_sReadStatusInPDCM_t                ReadStatusInPdcm;                               /**< CRM command read status in pdcm format */
  Dsi3_sIcMode_t                          IcMode;                                         /**< CRM command ic mode format */
} Dsi3_uCrmCommand_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC */
  uint8_t                                 Data2;                                          /**< CRM Register Data */
  uint8_t                                 Data1;                                          /**< CRM Extended Data */
  uint8_t                                 Status                  : 2;                    /**< CRM Status bits */
  uint8_t                                 HwErr                   : 1;                    /**< Hardware Error Flag */
  uint8_t                                 ComErr                  : 1;                    /**< Communication Error Flag */
  uint8_t                                 PhysicalAddress         : 4;                    /**< CRM NAD */
}Dsi3_sAnswerFrame_t;

/** 
 * Enumerations for PDCM Subtyps 
 */
typedef enum{
  DSI3_SUBTYPE_NO_DATA_AVAILABLE                  = 0x0u,                                 /**< SubType bits - no new measurement data available */
  DSI3_SUBTYPE_DIAGNOSTIC_DATA                    = 0x1u,                                 /**< SubType bits - ringing frequency information */
  DSI3_SUBTYPE_BURST_DATA                         = 0x2u,                                 /**< SubType bits - new echo information */
  DSI3_SUBTYPE_RINGING_DATA                       = 0x3u,                                 /**< SubType bits - tbd */
  DSI3_SUBTYPE_STD_ECHO_DATA                      = 0x4u,                                 /**< SubType bits - Echo Information in standard path */
  DSI3_SUBTYPE_ADV_ECHO_DATA                      = 0x5u,                                 /**< SubType bits - Echo Information in advanced path */
  DSI3_SUBTYPE_NFD_DATA                           = 0x6u,                                 /**< SubType bits - Near field detection data */
  DSI3_SUBTYPE_STD_ECHO_DATA_SELECTED             = 0x7u,                                 /**< SubType bits - Specific echo information desired */
  DSI3_SUBTYPE_TBD4                               = 0x8u,                                 /**< SubType bits - tbd */
  DSI3_SUBTYPE_TBD5                               = 0x9u,                                 /**< SubType bits - tbd */
  DSI3_SUBTYPE_TBD6                               = 0xAu,                                 /**< SubType bits - tbd */
  DSI3_SUBTYPE_TBD7                               = 0xBu,                                 /**< SubType bits - tbd */
  DSI3_SUBTYPE_TBD8                               = 0xCu,                                 /**< SubType bits - tbd */
  DSI3_SUBTYPE_TBD9                               = 0xDu,                                 /**< SubType bits - tbd */
  DSI3_SUBTYPE_TBD10                              = 0xEu,                                 /**< SubType bits - tbd */
  DSI3_SUBTYPE_IMPEDANCE_DATA                     = 0xFu,                                 /**< SubType bits - Results of impedance measurement */
}Dsi3_ePDCMSubType_t;

/**
 * Enumeration of LabMode DSI3-Subtypes
 */
typedef enum{
  DSI3_SUBTYPE_FRAME_1                            = 0x1u,                                 /**< SubType bits - Identifies Frame 1 */
  DSI3_SUBTYPE_FRAME_2                            = 0x2u                                  /**< SubType bits - Identifies Frame 2 */
}Dsi3_eLabmodeSubType_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC*/
  Dsi3BusIf_Data_t                        Data6;                                          /**< CRM pdcm response frame - data field 6 */
  Dsi3BusIf_Data_t                        Data5;                                          /**< CRM pdcm response frame - data field 5 */
  Dsi3BusIf_Data_t                        Data4;                                          /**< CRM pdcm response frame - data field 4 */
  Dsi3BusIf_Data_t                        Data3;                                          /**< CRM pdcm response frame - data field 3 */
  Dsi3BusIf_Data_t                        Data2;                                          /**< CRM pdcm response frame - data field 2 */
  uint8_t                                 SubType                 : 4;                    /**< CRM pdcm response frame - frame subtype */
  uint8_t                                 Type                    : 2;                    /**< CRM pdcm response frame - frame type */
  uint8_t                                 HwErr                   : 1;                    /**< Hardware Error Flag */
  uint8_t                                 ComErr                  : 1;                    /**< Communication Error Flag */
  uint8_t                                 FrameCounter            : 4;                    /**< CRM pdcm response frame - number of this frame since start of pdcm */
  uint8_t                                 PhysAddr                : 4;                    /**< CRM NAD */
} Dsi3Drv_sPDCMDefaultResponseFrame_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC*/
  uint8_t                                 NoiseCount;
  uint8_t                                 NoiseSum7_0;
  uint8_t                                 NoiseSum11_8            : 4;
  uint8_t                                 VoltageVSUP3_0          : 4;
  uint8_t                                 VoltageVSUP9_4          : 6;
  uint8_t                                 reserved                : 2;
  uint8_t                                 Temperature;
  uint8_t                                 SubType                 : 4;                    /**< CRM pdcm response frame - frame subtype */
  uint8_t                                 Type                    : 2;                    /**< CRM pdcm response frame - frame type */
  uint8_t                                 HwErr                   : 1;                    /**< Hardware Error Flag */
  uint8_t                                 ComErr                  : 1;                    /**< Communication Error Flag */
  uint8_t                                 FrameCounter            : 4;                    /**< CRM pdcm response frame - number of this frame since start of pdcm */
  uint8_t                                 PhysAddr                : 4;                    /**< CRM NAD */
} Dsi3Drv_sPDCMDiagnosticResponseFrame_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC*/
  uint8_t                                 VoltageVTANK1_7_0;
  uint8_t                                 VoltageVTANK1_9_8       :2;
  uint8_t                                 VoltageVTANK2_5_0       :6;
  uint8_t                                 VoltageVTANK2_9_6       :4;
  uint8_t                                 zeroes1                 :4;
  uint8_t                                 BurstLength;
  uint8_t                                 zeroes2;
  uint8_t                                 SubType                 : 4;                    /**< CRM pdcm response frame - frame subtype */
  uint8_t                                 Type                    : 2;                    /**< CRM pdcm response frame - frame type */
  uint8_t                                 HwErr                   : 1;                    /**< Hardware Error Flag */
  uint8_t                                 ComErr                  : 1;                    /**< Communication Error Flag */
  uint8_t                                 FrameCounter            : 4;                    /**< CRM pdcm response frame - number of this frame since start of pdcm */
  uint8_t                                 PhysAddr                : 4;                    /**< CRM NAD */
} Dsi3Drv_sPDCMBurstResponseFrame_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC*/
  uint8_t                                 RingTime7_0;
  uint8_t                                 RingTime15_8;
  uint8_t                                 RingSamples7_0;
  uint8_t                                 RingSamples9_8          : 2;
  uint8_t                                 RingCount               : 6;
  uint8_t                                 tbd;
  uint8_t                                 SubType                 : 4;                    /**< CRM pdcm response frame - frame subtype */
  uint8_t                                 Type                    : 2;                    /**< CRM pdcm response frame - frame type */
  uint8_t                                 HwErr                   : 1;                    /**< Hardware Error Flag */
  uint8_t                                 ComErr                  : 1;                    /**< Communication Error Flag */
  uint8_t                                 FrameCounter            : 4;                    /**< CRM pdcm response frame - number of this frame since start of pdcm */
  uint8_t                                 PhysAddr                : 4;                    /**< CRM NAD */
} Dsi3Drv_sPDCMRingingResponseFrame_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC*/
  uint8_t                                 Nfd2Result;
  uint8_t                                 Nfd1DeltaEcho3;
  uint8_t                                 Nfd1DeltaEcho2;
  uint8_t                                 Nfd1_Echo1;
  uint8_t                                 Nfd2Flag                : 1;
  uint8_t                                 Nfd1Flag                : 1;
  uint8_t                                 zero                    : 6;
  uint8_t                                 SubType                 : 4;                    /**< CRM pdcm response frame - frame subtype */
  uint8_t                                 Type                    : 2;                    /**< CRM pdcm response frame - frame type */
  uint8_t                                 HwErr                   : 1;                    /**< Hardware Error Flag */
  uint8_t                                 ComErr                  : 1;                    /**< Communication Error Flag */
  uint8_t                                 FrameCounter            : 4;                    /**< CRM pdcm response frame - number of this frame since start of pdcm */
  uint8_t                                 PhysAddr                : 4;                    /**< CRM NAD */
} Dsi3Drv_sPDCMNfdResponseFrame_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC*/
  uint8_t                                 TimeStamp7_0;
  uint8_t                                 TimeStamp15_8;
  uint8_t                                 EchoHeight_Raw7_0;
  uint8_t                                 EchoHeight_Raw13_8      : 6;
  uint8_t                                 EchoEvent               : 2;
  uint8_t                                 Buffer                  : 1;
  uint8_t                                 zeroes                  : 7;
  uint8_t                                 SubType                 : 4;                    /**< CRM pdcm response frame - frame subtype */
  uint8_t                                 Type                    : 2;                    /**< CRM pdcm response frame - frame type */
  uint8_t                                 HwErr                   : 1;                    /**< Hardware Error Flag */
  uint8_t                                 ComErr                  : 1;                    /**< Communication Error Flag */
  uint8_t                                 FrameCounter            : 4;                    /**< CRM pdcm response frame - number of this frame since start of pdcm */
  uint8_t                                 PhysAddr                : 4;                    /**< CRM NAD */
} Dsi3Drv_sPDCMStdResponseFrame_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC*/
  uint8_t                                 TimeStamp7_0;
  uint8_t                                 TimeStamp15_8;
  uint8_t                                 EchoHeight7_0;
  uint8_t                                 EchoHeight15_8;
  uint8_t                                 Confidence              : 4;
  uint8_t                                 Buffer                  : 1;
  uint8_t                                 FrameSelect             : 1;
  uint8_t                                 zeroes                  : 2;
  uint8_t                                 SubType                 : 4;                    /**< CRM pdcm response frame - frame subtype */
  uint8_t                                 Type                    : 2;                    /**< CRM pdcm response frame - frame type */
  uint8_t                                 HwErr                   : 1;                    /**< Hardware Error Flag */
  uint8_t                                 ComErr                  : 1;                    /**< Communication Error Flag */
  uint8_t                                 FrameCounter            : 4;                    /**< CRM pdcm response frame - number of this frame since start of pdcm */
  uint8_t                                 PhysAddr                : 4;                    /**< CRM NAD */
} Dsi3Drv_sPDCMAdvResponseFrame_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC*/
  uint8_t                                 MonChannel3_7_0;
  uint8_t                                 MonChannel3_15_8;
  uint8_t                                 MonChannel4_7_0;
  uint8_t                                 MonChannel4_15_8;
  uint8_t                                 zeroes;
  uint8_t                                 SubType                 : 4;                    /**< CRM pdcm response frame - frame subtype */
  uint8_t                                 Type                    : 2;                    /**< CRM pdcm response frame - frame type */
  uint8_t                                 HwErr                   : 1;                    /**< Hardware Error Flag */
  uint8_t                                 ComErr                  : 1;                    /**< Communication Error Flag */
  uint8_t                                 FrameCounter            : 4;                    /**< CRM pdcm response frame - number of this frame since start of pdcm */
  uint8_t                                 PhysAddr                : 4;                    /**< CRM NAD */
} Dsi3Drv_sPDCMLab1ResponseFrame_t;

typedef struct
{
  uint8_t                                 CRC;                                            /**< CRM CRC*/
  uint8_t                                 MonChannel1_7_0;
  uint8_t                                 MonChannel1_15_8;
  uint8_t                                 MonChannel2_7_0;
  uint8_t                                 MonChannel2_15_8;
  uint8_t                                 zeroes;
  uint8_t                                 SubType                 : 4;                    /**< CRM pdcm response frame - frame subtype */
  uint8_t                                 Type                    : 2;                    /**< CRM pdcm response frame - frame type */
  uint8_t                                 HwErr                   : 1;                    /**< Hardware Error Flag */
  uint8_t                                 ComErr                  : 1;                    /**< Communication Error Flag */
  uint8_t                                 FrameCounter            : 4;                    /**< CRM pdcm response frame - number of this frame since start of pdcm */
  uint8_t                                 PhysAddr                : 4;                    /**< CRM NAD */
} Dsi3Drv_sPDCMLab2ResponseFrame_t;

typedef union
{
  Dsi3BusIf_ByteData_t                    systemResponseFrame;
  Dsi3Drv_sPDCMDefaultResponseFrame_t     defaultResponseFrame;
  Dsi3Drv_sPDCMDiagnosticResponseFrame_t  diagnosticResponseFrame;
  Dsi3Drv_sPDCMBurstResponseFrame_t       burstResponseFrame;
  Dsi3Drv_sPDCMRingingResponseFrame_t     ringingResponseFrame;
  Dsi3Drv_sPDCMNfdResponseFrame_t         nearFieldDetection;
  Dsi3Drv_sPDCMStdResponseFrame_t         standardResponseFrame;
  Dsi3Drv_sPDCMAdvResponseFrame_t         advancedResponseFrame;
  Dsi3Drv_sPDCMLab1ResponseFrame_t        labModeResponseFrame1;
  Dsi3Drv_sPDCMLab2ResponseFrame_t        labModeResponseFrame2;
  uint8_t                                 rawData[8];
} Dsi3Drv_uPDCMResponseFrame_t;

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/
extern uint16_t HardwareVersionNumber;
extern uint16_t const FirmwareVersionNumber;
/* ****************************************************************************/
/* ********************* EXTERNAL FUNCTIONS / INTERFACE ***********************/
/* ****************************************************************************/

/* ****************************************************************************/
/*                               BUS CALLBACKS                                */
/* ****************************************************************************/

/* ***************************************************************************
 * @brief
 * dsi driver initialization callback
 *
 * @param       applRuntimeData      generic application data, should point to application environment data
 * @return      none
 * ****************************************************************************/
void Dsi3_Callbacks_Init(Dsi3Drv_pApplCtrlData_t applRuntimeData);

/* ***************************************************************************
 * @brief
 * dsi communication task
 *
 * @param       genericEnvData      generic environment data pointer, should point to bus environment data
 * @return      none
 * ****************************************************************************/
extern void COMCtrl_Task(Dsi3BusIf_pGenericEnvData_t genericEnvData);

/* ***************************************************************************
 * @brief
 * error callback routine from bus layer
 *
 * The callback routine for error handling from the bus layer.
 *
 * @param       genericEnvData          generic environment data pointer, should point to bus environment data
 * @param       busIfFuns               bus interface function
 * @param       error                   DSI3 bus error code
 * @param       genericBusCbCtxData     generic context data pointer (optional)
 * @return      none
 * ****************************************************************************/
void Dsi3_BusErrorCbFun(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_cpInterfaceFunctions_t busIfFuns, Dsi3BusIf_Error_t error, Dsi3BusIf_pGenericCbCtxData_t genericBusCbCtxData);

/* **************************************************************************//**
 * @brief
 * Dsi3 mode change callback routine from bus layer
 *
 * The callback routine for dsi3 mode change handling from the bus layer.
 *
 * @param   genericEnvData          generic environment data pointer, should point to bus environment data
 * @param   busIfFuns               bus interface function
 * @param   currentMode             current DSI3 mode
 * @param   genericBusCbCtxData     generic context data pointer (optional)
 * @return  none
 * ****************************************************************************/
void Dsi3_BusModeChangedCbFun(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_cpInterfaceFunctions_t busIfFuns, Dsi3BusIf_eCommunicationMode_t currentMode, Dsi3BusIf_pGenericCbCtxData_t genericBusCbCtxData);

/* **************************************************************************//**
 * @brief
 * Auto addressing callback routine from bus layer
 *
 * The callback routine for auto addressing changes the NAD depending on the number of pulses.
 *
 * @param   busEnvData                    bus environment data pointer
 * @param   busIfFuns                     bus interface function
 * @param   pulseNum                      number of Discovery pulses since start of Discovery mode
 * @param   currentDiscoveryModeStatus    current Discovery mode status
 * @param   genericTransCbCtxData          genericCbCtxData generic context data pointer (optional)
 * @return  void
 * ****************************************************************************/
void Dsi3_BusAutoAddrCbFun(Dsi3BusIf_pGenericEnvData_t busEnvData, Dsi3BusIf_cpInterfaceFunctions_t busIfFuns, Dsi3BusIf_CountValue_t pulseNum,Dsi3BusIf_DiscoveryModeStatus_t currentDiscoveryModeStatus, Dsi3BusIf_pGenericCbCtxData_t genericTransCbCtxData);

/* **************************************************************************//**
 * @brief
 * CRM: default handler routine
 * default crm handler to use if for non assigned crm commands.
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      never
 *              Dsi3BusIf_eCMDACT_IGNORE        ever
 * ****************************************************************************/
extern Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_Default                (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer, Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* ***************************************************************************
 * @brief
 * CRM: Start a standard measurement
 * initiate an ultrasonic measurement cycle by using the echo detection in the fix frequency signal path
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       currentMode                     current DSI3 bus operation mode
 * @param       genericCbCtxData                pointer to relevant context data
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      never
 *              Dsi3BusIf_eCMDACT_IGNORE        ever
 * ****************************************************************************/
extern Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_MeasExecute (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer, Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* ***************************************************************************
 * @brief
 * CRM: Start an advanced measurement
 * initiate an ultrasonic measurement cycle by using the echo detection in the advanced signal paths
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      never
 *              Dsi3BusIf_eCMDACT_IGNORE        ever
 * ****************************************************************************/
extern Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_AdvMeasurementExecute (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer, Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* ***************************************************************************
 * @brief
 * CRM: Start impedance measurement
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       currentMode                     current DSI3 bus operation mode
 * @param       genericCbCtxData                pointer to relevant context data
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      never
 *              Dsi3BusIf_eCMDACT_IGNORE        ever
 * ****************************************************************************/
extern Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_ImpedanceMeasurement (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer, Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* ***************************************************************************
 * @brief
 * CRM: Stop a running Measurement
 * stop an ultrasonic measurement cycle
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       currentMode                     current DSI3 bus operation mode
 * @param       genericCbCtxData                pointer to relevant context data
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      never
 *              Dsi3BusIf_eCMDACT_IGNORE        ever
 * ****************************************************************************/
extern Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_MeasStop (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer, Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* ***************************************************************************
 * @brief
 * CRM: Measurement configuration data access
 * transmit or receive measurement configuration data (in combination with a further “command” frame)
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       currentMode                     current DSI3 bus operation mode
 * @param       genericCbCtxData                pointer to relevant context data
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      if addressed directly
 *              Dsi3BusIf_eCMDACT_IGNORE        if addressed by wildcard
 * ****************************************************************************/
extern Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_MeasSettings (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer, Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* ***************************************************************************
 * @brief
 * CRM: Measurement configuration data access
 * further "command" frame after "Measurement configuration data access"
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       currentMode                     current DSI3 bus operation mode
 * @param       genericCbCtxData                pointer to relevant context data
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      if addressed directly
 *              Dsi3BusIf_eCMDACT_IGNORE        if addressed by wildcard
 * ****************************************************************************/
extern Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_MeasSettingsExt (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer, Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* ***************************************************************************
 * @brief
 * CRM: EEPROM access
 * enable EEPROM access and EEPROM copy operations.
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      if addressed directly
 *              Dsi3BusIf_eCMDACT_IGNORE        if addressed by wildcard
 * ****************************************************************************/
extern Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_EEPROMAccess (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer, Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* ***************************************************************************
 * @brief
 * CRM: IC register access
 * transmit or receive IC register data (in combination with a further “command” frame)
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      if addressed directly
 *              Dsi3BusIf_eCMDACT_IGNORE        if addressed by wildcard
 * ****************************************************************************/
extern Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_RegisterAccess (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer, Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* ***************************************************************************
 * @brief
 * CRM: IC register access
 * further "command" frame after "IC register access"
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      never
 *              Dsi3BusIf_eCMDACT_IGNORE        never
 * ****************************************************************************/
extern Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_RegisterAccessExt (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer, Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* ***************************************************************************
 * @brief
 * CRM: Read status in CRM
 * transmit IC Status information in CRM (results of self-test)
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      if addressed directly
 *              Dsi3BusIf_eCMDACT_IGNORE        if addressed by wildcard
 * ****************************************************************************/
extern Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_ReadStatInCRM (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer, Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* ***************************************************************************
 * @brief
 * CRM: Read Status in PDCM
 * transmit IC status information in PDCM. This allows a much higher data rate to transfer all data from the sensor (results of self-test)
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      never
 *              Dsi3BusIf_eCMDACT_IGNORE        never
 * ****************************************************************************/
extern Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_ReadStatInPDCM (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer, Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* ***************************************************************************
 * @brief
 * CRM: IC mode
 * configure different IC modes within the IC
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       commandBuffer                   pointer to CRM command data struct (in buffer)
 * @param       responseBuffer                  pointer to CRM response data struct (out buffer)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      if addressed directly
 *              Dsi3BusIf_eCMDACT_IGNORE        if addressed by wildcard
 * ****************************************************************************/
extern Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_IcMode (Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer, Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);

/* **************************************************************************//**
 * @implementation
 * PDCM: Measurement Response PDCM handler routine.
 *
 * Sends 1 (allowed) data packet from the Measurement results pool.
 * On repeated PDCM req, iterates through allowed data packets.
 * If all allowed packets have been sent, continues to send ACK GRA packets.
 *
 * @param       genericEnvData                  pointer to DSI3 bus environment data structure
 * @param       responseBuffer                  pointer to PDCM response buffer for next PDCM pulse
 * @param       bufsize                         max size of PDCM response buffer
 * @param       msgLen                          pointer to PDCM response message size (out)
 * @param       currentNad                      the currently assigned NAD
 * @param       genericCbCtxData                pointer to relevant context data
 *
 * @return      Dsi3BusIf_eCMDACT_RESPONSE      always
 * ****************************************************************************/
extern Dsi3BusIf_CmdIdAction_t Dsi3_PdcmCmdHandler(Dsi3BusIf_pGenericEnvData_t genericEnvData, Dsi3BusIf_ByteData_t* responseBuffer, const Dsi3BusIf_Length_t bufsize, uint8_t *msgLen, const Dsi3BusIf_SlaveID_t currentNad, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);


/* ****************************************************************************/
/*                    FPGA Development specific functions                     */
/* ****************************************************************************/
#if defined (FPGA_52417B)
extern Dsi3BusIf_CmdIdAction_t Dsi3_CrmCmdHandler_IdAssign(Dsi3BusIf_pGenericEnvData_t genericEnvData, const Dsi3Bus_CrmCommand_t* commandBuffer, Dsi3Bus_CrmResponse_t* responseBuffer, const Dsi3BusIf_SlaveID_t currentNad, Dsi3BusIf_pGenericCbCtxData_t genericCbCtxData);
#endif

#endif /* DSI3_CALLBACKS_H_ */
