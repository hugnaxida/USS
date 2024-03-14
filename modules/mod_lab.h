/***************************************************************************//**
 * @file      mod_lab.h
 *
 * @creator   KeLe
 * @created   22.11.2017
 *
 * @brief     Labmode software module (header)
 *
 * @purpose
 *
 * Software module for managing and controlling lab mode processes.
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
 ******************************************************************************/

#ifndef LABMODE_H_
#define LABMODE_H_

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "def_app.h"
#include "dsp_InterruptHandler.h"
#include "mod_dsi3.h"
/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

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
 * Initializes the lab mode module
 *
 * The function must be called once to make the module aware of the global data structure.
 * Furthermore the ISR for the module are registered.
 * This function only needs to be called once.
 *
 * @return      none
 * ****************************************************************************/
void lab_init_module(void);

/* **************************************************************************//**
 * @brief
 * Initializes all registers/data needed in lab mode.
 *
 * This function must be called every time the lab mode is executed to set registers
 * and to assign memory considering the number of used channels.
 *
 * @return      none
 * ****************************************************************************/
void lab_TaskState_INIT_Lab(void);

/* **************************************************************************//**
 * @brief
 * Self test Task
 *
 * Main task of module lab mode, which processes the buffered DMA data.
 * Needs to be called in main loop
 *
 * @return      bool_t      true ever
 * ****************************************************************************/
void lab_Task(void);

/* **************************************************************************//**
 * @brief
 * Start Lab Mode
 *
 * The function starts the DMA. The lab_TaskState_INIT_Lab must be called before.
 *
 * @return      none
 * ****************************************************************************/
void lab_StartLabMode(void);

/* **************************************************************************//**
 * @brief
 * PDCM: Measurement Response PDCM handler routine in Lab Mode
 *
 * Sends 1 (allowed) data packet from the Measurement results pool.
 * On repeated PDCM req, iterates through allowed data packets.
 * If all allowed packets have been sent, continues to send ACK GRA packets.
 * Is called if in lab and applab mode
 * In case of applab the app mode data is sent before the lab mode data.
 *
 * @param       ansData                 pointer to PDCM response buffer for next PDCM pulse
 * @return      none
 * ****************************************************************************/
void lab_PdcmCmdHandler_LAB_MODE(Dsi3Drv_uPDCMResponseFrame_t* ansData);


#endif
