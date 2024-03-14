/***************************************************************************//**
 * @file			bootloader_UserConfig.h
 *
 * @creator		sbai
 * @created		15.06.2015
 *
 * @brief  		TODO: Short description of this module
 *
 * @purpose
 *
 * TODO: A detailed description of this module
 *
 * $Id: bootloader_UserConfig.h 383 2019-01-09 10:06:08Z siko $
 *
 * $Revision: 383 $
 *
 ******************************************************************************/

#ifndef BOOTLOADER_USERCONFIG_H_
#define BOOTLOADER_USERCONFIG_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/


/***************************************************************************/
struct bldConf_sKey
{
  uint8_t Data[8];
};

typedef struct bldConf_sKey  bldConf_Key_t;
typedef bldConf_Key_t *      bldConf_pKey_t;

/***************************************************************************/
struct bldConf_sBootloaderAccess_bit
{
  uint8_t EnableFlashMainAccess       : 1;
  uint8_t EnableFlashInfoAccess       : 1;
  uint8_t EnableRAMAccess             : 1;
  uint8_t EnableReadAccess            : 1;
  uint8_t EnableProcCall              : 1;
  uint8_t EnableExit                  : 1;  
};

/***************************************************************************/
union bldConf_uBootloaderAccess
{
  struct bldConf_sBootloaderAccess_bit Flags;
  uint8_t                              Value;
};

typedef union bldConf_uBootloaderAccess     bldConf_BootloaderAccess_t;
typedef       bldConf_BootloaderAccess_t *  bldConf_pBootloaderAccess_t;
typedef const bldConf_BootloaderAccess_t *  bldConf_cpBootloaderAccess_t;

/***************************************************************************/
struct bldConf_sDeviceSerial // keep in sync with bldIf_DeviceSerial_t!
{
  uint8_t Data[6];
};

typedef struct bldConf_sDeviceSerial  bldConf_DeviceSerial_t;
typedef bldConf_DeviceSerial_t *      bldConf_pDeviceSerial_t;


/***************************************************************************/
typedef uint8_t           bldConf_SID_t;

/***************************************************************************/
typedef uint8_t           bldConf_I2CDeviceAddress_t;

/***************************************************************************/
typedef uint16_t          bldConf_ApplicationInfoLocation_t;

/***************************************************************************/
typedef uint16_t          bldConf_StaticCustomConfigDataLocation_t;

/***************************************************************************/
typedef uint8_t           bldConf_StaticCustomConfigDataAccessMode_t;

/***************************************************************************/
typedef uint16_t          bldConf_ResetVectorLocation_t;

/***************************************************************************/
typedef uint16_t          bldConf_ApplicationLocation_t;

/***************************************************************************/
typedef uint16_t          bldConf_IdleTimeout_t;

/***************************************************************************/
typedef uint16_t          bldConf_Register_t;

/***************************************************************************/
typedef uint16_t          bldConf_ConfigHint_t;

/***************************************************************************/
typedef uint16_t          bldConf_DeviceSerialLocation_t;

/***************************************************************************/
typedef uint8_t           bldConf_DeviceSerialAccessMode_t;

/***************************************************************************/
typedef uint8_t           bldConf_DeviceSerialLength_t;

/***************************************************************************/
struct bldConf_sDevID
{
  uint8_t Data[8];
};

typedef struct bldConf_sDevID  bldConf_DevID_t;
typedef bldConf_DevID_t *      bldConf_pDevID_t;


/***************************************************************************/
struct bldConf_sBootloaderStaticCustomConfigFlags
{    
  uint16_t ExitOnIdle                  : 1;  // if 1 -> reset device once idle time out has been reached. 
  uint16_t CheckAppCRC                 : 1;  // if 0 -> check reset vector only, 1 -> check crc
  uint16_t TimeWindow                  : 4;  // -> 0 = off, 1 .. 7  = 1=20ms ... 2=40 ... 3=60 ... 7=160ms 
  uint16_t NoAppPermBootloader         : 1;  // if 0 -> bootloader will exit after TW time in any case, 1 -> bootloader will stay active, if no valid app found. (ExitOnIdle may still leave bootloader!)

  uint16_t EnableSPIInterface          : 1;  // if 0 -> bootloader not accessible via SPI, 1 -> bootloader uses SPI interface (If SPI driver compiled into code)
  uint16_t EnableI2CInterface          : 1;  // if 0 -> bootloader not accessible via I2C, 1 -> bootloader uses I2C interface (If I2C driver compiled into code)
  
  // .... 
};

typedef struct bldConf_sBootloaderStaticCustomConfigFlags bldConf_BootloaderStaticCustomConfigFlags_t;

/***************************************************************************/
struct bldConf_sBootloaderStaticConfigFlags
{   
  uint8_t DeviceSerialLength           : 3;  // number of bytes used for device serial (max 6 bytes)
  uint8_t ForceMinTimeWindow           : 1;  // if 1 -> bootloader will go into a time window mode (of 10ms) even in the case of customer configured TW == 0 
                                             // in this case, BL will not listen for any communication on any interface!
                                             // if 0 -> bootloader will start application (if any) immediately if customer TW == 0;   
  
  // .... 
};

typedef struct bldConf_sBootloaderStaticConfigFlags bldConf_BootloaderStaticConfigFlags_t;



/***************************************************************************/
/* Has to be double word aligned. */
struct bldConf_sStaticCustomConfigData  // this is bootloader config data which ist fixed, but customer changeable. 
{
   bldConf_Key_t                                  Key;
   bldConf_I2CDeviceAddress_t                     I2CDeviceAddress; 
   bldConf_BootloaderAccess_t                     AccessFlags;   
   bldConf_BootloaderStaticCustomConfigFlags_t    Flags;
   bldConf_IdleTimeout_t                          IdleTimeout; 
   bldConf_ApplicationInfoLocation_t              ApplicationInfoLocation;             // need to be a word alligned location within OTP! (may be 0x0000 if not used)
   bldConf_Register_t                             FlashProtAreaMainLow;                // see FLASH_CTRL AREA_MAIN_L register 
   bldConf_Register_t                             FlashProtAreaMainHigh;               // see FLASH_CTRL AREA_MAIN_H register
};
   
typedef struct bldConf_sStaticCustomConfigData     bldConf_StaticCustomConfigData_t;
typedef       bldConf_StaticCustomConfigData_t *   bldConf_pStaticCustomConfigData_t;
typedef const bldConf_StaticCustomConfigData_t *   bldConf_cpStaticCustomConfigData_t;


/***************************************************************************/
struct bldConf_sStaticConfigData  // this is factory configurable data stored by elmos! (this struct has to have a word aligned size)
{
   bldConf_DevID_t                               DeviceID;
   bldConf_ConfigHint_t                          ConfigHint;                          // some numeric value which indicates current bootloader build configuration (based on a common knowledge.)   
   bldConf_SID_t                                 BootloaderServiceID;
   bldConf_StaticCustomConfigDataAccessMode_t    StaticCustomConfigDataAccessMode;
   bldConf_StaticCustomConfigDataLocation_t      StaticCustomConfigDataLocation;      // required to be double word aligned  
   bldConf_ResetVectorLocation_t                 ResetVectorLocation;                 // required to be word aligned
   bldConf_BootloaderStaticConfigFlags_t         Flags;                               // elmos-only configurable flags. 
   bldConf_DeviceSerialAccessMode_t              DeviceSerialAccessMode;
   bldConf_DeviceSerialLocation_t                DeviceSerialLocation;                // required to be word aligned  
   
   // ....
};

typedef struct bldConf_sStaticConfigData     bldConf_StaticConfigData_t;
typedef       bldConf_StaticConfigData_t *   bldConf_pStaticConfigData_t;
typedef const bldConf_StaticConfigData_t *   bldConf_cpStaticConfigData_t;

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ********************* EXTERNAL FUNCTIONS / INTERFACE ***********************/
/* ****************************************************************************/

#endif /* BOOTLOADER_USERCONFIG_H_ */  
