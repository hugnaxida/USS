/******************************************************************************
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
#ifndef EL_TYPES_ACM0_IAR_H_
#define EL_TYPES_ACM0_IAR_H_

/* ===================================== */
/* arch and compiler defines             */
/* ===================================== */

#define EL_ARCH_ACM0               
//#define EL_ARCH_H430               
//#define EL_ARCH_EL16               
//#define EL_ARCH_EL35               

//#define EL_COMPILER_IAR            
//#define EL_COMPILER_KEIL           
//#define EL_COMPILER_COSMIC            
#define EL_COMPILER_GCC


/* ===================================== */
/* linux-like types                      */
/* ===================================== */

#include <stdint.h>
#include <stdbool.h>

typedef _Bool bool_t;
#define TRUE true
#define FALSE false
	

#if 0
typedef unsigned long long  uint64_t;
typedef unsigned long       uint32_t;
typedef unsigned short      uint16_t;
typedef unsigned char       uint8_t;

typedef signed long long    int64_t;
typedef signed long         int32_t;
typedef signed short        int16_t;
typedef signed char         int8_t;

typedef          int        intptr_t;
typedef unsigned int        uintptr_t;
#endif

typedef unsigned int        bitfield_t;


#ifdef DPI  /* DPI simulation */
  #include <stdint.h>
#endif

/* ===================================== */
/* deprecated types                      */
/* ===================================== */

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned long       u32;
typedef unsigned long long  u64;

typedef signed char         s8;
typedef signed short        s16;
typedef signed long         s32;
typedef signed long long    s64;

typedef volatile u64        reg64;
typedef volatile u32        reg32;
typedef volatile u16        reg16;
typedef volatile u8         reg8;

/* ===================================== */
/* additional types                      */
/* ===================================== */

#if 0
#if defined(DPI) && defined(__cplusplus)
#else
typedef enum {
  false = 0,
  true  = 1
} bool;
#endif

#ifndef DPI
typedef int ssize_t;
#endif

#endif


#ifndef NULL
#define NULL ((void *)0)
#endif

#endif /* EL_TYPES_ACM0_IAR_H_ */

