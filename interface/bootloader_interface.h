/***************************************************************************//**
 * @file			bootloader_interface.h
 *
 * @creator		RPY
 * @created		21.04.2015
 *
 * @brief  		TODO: Short description of this module
 *
 * @purpose
 *
 * TODO: A detailed description of this module
 *
 * $Id: bootloader_interface.h 383 2019-01-09 10:06:08Z siko $
 *
 * $Revision: 383 $
 *
 ******************************************************************************/

#ifndef BOOTLOADER_INTERFACE_H_
#define BOOTLOADER_INTERFACE_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "elmos/includes/el_types.h"
#include "bootloader_UserConfig.h"

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define BOOTLOADER_INTERFACE_VERSION           0x0102


/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

typedef uint16_t     bldIf_Version_t;

typedef uint16_t     bldIf_WritePassword_t;

#define BLDIF_WRITE_PASSWORD      0xA509


/* *****************************************************************************
 * Interface callback function types
 ******************************************************************************/

/***************************************************************************//**
 * TODO: A short description.
 *
 * @param param TODO: Parameter description
 *
 * @return      TODO: return description
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * TODO: A more detailed description.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
typedef bool_t (*bldIf_ReadConfig_t) (bldConf_pConfigData_t pConf);

/***************************************************************************//**
 * TODO: A short description.
 *
 * @param param TODO: Parameter description
 *
 * @return      TODO: return description
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * TODO: A more detailed description.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
typedef bool_t (*bldIf_WriteConfig_t) (bldIf_WritePassword_t pass,bldConf_cpConfigData_t cpConf,bldConf_Lock_t lock);


/***************************************************************************//**
 * TODO: A short description.
 *
 * @param param TODO: Parameter description
 *
 * @return      TODO: return description
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * TODO: A more detailed description.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
typedef bool_t (*bldIf_ReadDeviceSerial_t) (bldConf_pDeviceSerial_t pSerial);

/***************************************************************************//**
 * TODO: A short description.
 *
 * @param param TODO: Parameter description
 *
 * @return      TODO: return description
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * TODO: A more detailed description.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
typedef bool_t (*bldIf_ReadStaticConfig_t) (bldConf_pStaticConfigData_t pConf);

/***************************************************************************//**
 * TODO: A short description.
 *
 * @param param TODO: Parameter description
 *
 * @return      TODO: return description
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * TODO: A more detailed description.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
typedef bool_t (*bldIf_ReadCustomStaticConfig_t) (bldConf_pStaticCustomConfigData_t pConf);


/***************************************************************************//**
 * bootloader application layer interface function pointer
 ******************************************************************************/
struct bldIf_sBootloaderFunctions
{
    bldIf_Version_t                     InterfaceVersion;
 
    bldIf_ReadConfig_t                  ReadConfig;
    bldIf_WriteConfig_t                 WriteConfig;

    bldIf_ReadDeviceSerial_t            ReadDeviceSerial;
    
    bldIf_ReadStaticConfig_t            ReadStaticConfig;
    bldIf_ReadCustomStaticConfig_t      ReadCustomStaticConfig;
};
  
typedef struct bldIf_sBootloaderFunctions    bldIf_BootloaderFunctions_t;
typedef        bldIf_BootloaderFunctions_t*  bldIf_pBootloaderFunctions_t;
typedef const  bldIf_BootloaderFunctions_t*  bldIf_cpBootloaderFunctions_t;


/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/

#define BLDIF_ENVIRONMENT_DATA_SIZE    0  // currently no env data needed. 

#ifdef BUILD_ROM
extern const bldIf_BootloaderFunctions_t bldIf_InterfaceFunctions;
#endif

/* ****************************************************************************/
/* ********************* EXTERNAL FUNCTIONS / INTERFACE ***********************/
/* ****************************************************************************/

#endif /* BOOTLOADER_INTERFACE_H_ */
