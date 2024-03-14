/***************************************************************************//**
 * @file			el_helper.c
 *
 * @creator		sbai
 * @created		17.06.2015
 *
 * @brief  		TODO: Short description of this module
 *
 * @purpose
 *
 * TODO: A detailed description of this module
 *
 * $Id: el_helper_ACM0_Keil.c 383 2019-01-09 10:06:08Z siko $
 *
 * $Revision: 383 $
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

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "el_helper.h"

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
/* ******************** FORWARD DECLARATIONS / PROTOTYPES *********************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/***************************************************************************//**
 * TODO: Concrete implementation description.
 *
 ******************************************************************************/
inline void el_CopyBytes(const uint8_t *src, uint8_t *dest, uint16_t srclen)
{
  while(srclen>0u)  { *dest++=*src++;  --srclen; }
}

/***************************************************************************//**
 * TODO: Concrete implementation description.
 *
 ******************************************************************************/
inline void el_FillBytes(const uint8_t value, uint8_t *dest, uint16_t destlen)
{
  while(destlen>0u)  { *dest++=value;  --destlen; }
}

/***************************************************************************//**
 * TODO: Concrete implementation description.
 *
 ******************************************************************************/
inline void el_CopyAndFillBytes(const uint8_t *src, uint8_t *dest, uint16_t srclen, const uint8_t value, uint16_t destlen)
{
  destlen-=srclen; // TODO: if once some calling context will be unknown, eventuall check if destlen>srclen

  while(srclen>0u)  { *dest++=*src++;  --srclen; }

  while(destlen>0u)  { *dest++=value;  --destlen; }

}

/***************************************************************************//**
 * TODO: Concrete implementation description.
 *
 ******************************************************************************/
/* returns true, if arrays are equal */
bool_t el_CompareBytes(uint8_t * a, uint8_t * b, uint16_t size)
{
  while (0 < size--)
  {
    if (*a++ != *b++)
    {
      return FALSE;
    }
  }
  return TRUE;
}
