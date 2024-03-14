/***************************************************************************//**
 * @file      mod_util.c
 *
 * @creator   KeLe
 * @created   22.11.2017
 *
 * @brief     Useful Functions
 *
 * @purpose
 *
 * Useful cross-module functions.
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

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
/***************************************************************************//**
 * @file      mod_util.h
 *
 * @creator   KeLe
 * @created   22.11.2017
 *
 * @brief     Useful Functions (header)
 *
 * @purpose
 *
 * Useful cross-module functions.
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


/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
/* stdint.h standard header */
/* Copyright 2003-2017 IAR Systems AB.  */

  #pragma system_include

/* ycheck.h internal checking header file. */
/* Copyright 2005-2017 IAR Systems AB. */

/* Note that there is no include guard for this header. This is intentional. */

  #pragma system_include

/* __AEABI_PORTABILITY_INTERNAL_LEVEL
 *
 * Note: Redefined each time ycheck.h is included, i.e. for each
 * system header, to ensure that ABI support could be turned off/on
 * individually for each file.
 *
 * Possible values for this preprocessor symbol:
 *
 * 0 - ABI portability mode is disabled.
 *
 * 1 - ABI portability mode (version 1) is enabled.
 *
 * All other values are reserved for future use.
 */


/* yvals.h internal configuration header file. */
/* Copyright 2001-2017 IAR Systems AB. */


  #pragma system_include

/* Convenience macros */



/* Used to refer to '__aeabi' symbols in the library. */ 

/* Dinkum version */

/* DLib version */

/* Module consistency. */
#pragma rtmodel = "__dlib_version", "6"

/* IAR compiler version check */


/* Read configuration */
/***************************************************
 *
 * DLib_Defaults.h is the library configuration manager.
 *
 * Copyright 2003-2017 IAR Systems AB.  
 *
 * This configuration header file performs the following tasks:
 *
 * 1. Includes the configuration header file, defined by _DLIB_CONFIG_FILE,
 *    that sets up a particular runtime environment.
 *
 * 2. Includes the product configuration header file, DLib_Product.h, that
 *    specifies default values for the product and makes sure that the
 *    configuration is valid.
 *
 * 3. Sets up default values for all remaining configuration symbols.
 *
 * This configuration header file, the one defined by _DLIB_CONFIG_FILE, and
 * DLib_Product.h configures how the runtime environment should behave. This
 * includes all system headers and the library itself, i.e. all system headers
 * includes this configuration header file, and the library has been built
 * using this configuration header file.
 *
 ***************************************************
 *
 * DO NOT MODIFY THIS FILE!
 *
 ***************************************************/


  #pragma system_include

/* Include the main configuration header file. */
/* DLib configuration. */
/* Copyright 2003-2017 IAR Systems AB.  */


  #pragma system_include

/* No changes to the defaults. */

  /* _DLIB_CONFIG_FILE_STRING is the quoted variant of above */

/* Include the product specific header file. */
/* Copyright 2017 IAR Systems AB. */


   #pragma system_include


/*********************************************************************
*
*       Configuration
*
*********************************************************************/

/* Wide character and multi byte character support in library.
 * This is not allowed to vary over configurations, since math-library
 * is built with wide character support.
 */

/* This ensures that the standard header file "string.h" includes
 * the Arm-specific file "DLib_Product_string.h". */

/* This ensures that the standard header file "fenv.h" includes
 * the Arm-specific file "DLib_Product_fenv.h". */

/* This ensures that the standard header file "stdlib.h" includes
 * the Arm-specific file "DLib_Product_stdlib.h". */

/* Max buffer used for swap in qsort */


/* Enable AEABI support */

/* Enable rtmodel for setjump buffer size */

/* Enable parsing of hex floats */

/* Special placement for locale structures when building ropi libraries */

/* Use atomic if possible */

/* CPP-library uses software floatingpoint interface */

/* functions for setting errno should be __no_scratch */

/* Use speedy implementation of floats (simple quad). */

/* Configure generic ELF init routines. */







/*
 * The remainder of the file sets up defaults for a number of
 * configuration symbols, each corresponds to a feature in the
 * libary.
 *
 * The value of the symbols should either be 1, if the feature should
 * be supported, or 0 if it shouldn't. (Except where otherwise
 * noted.)
 */


/*
 * File handling
 *
 * Determines whether FILE descriptors and related functions exists or not.
 * When this feature is selected, i.e. set to 1, then FILE descriptors and
 * related functions (e.g. fprintf, fopen) exist. All files, even stdin,
 * stdout, and stderr will then be handled with a file system mechanism that
 * buffers files before accessing the lowlevel I/O interface (__open, __read,
 * __write, etc).
 *
 * If not selected, i.e. set to 0, then FILE descriptors and related functions
 * (e.g. fprintf, fopen) does not exist. All functions that normally uses
 * stderr will use stdout instead. Functions that uses stdout and stdin (like
 * printf and scanf) will access the lowlevel I/O interface directly (__open,
 * __read, __write, etc), i.e. there will not be any buffering.
 *
 * The default is not to have support for FILE descriptors.
 */



/*
 * Use static buffers for stdout
 *
 * This setting controls whether the stream stdout uses a static 80 bytes
 * buffer or uses a one byte buffer allocated in the file descriptor. This
 * setting is only applicable if the FILE descriptors are enabled above.
 *
 * Default is to use a static 80 byte buffer.
 */



/*
 * Support of locale interface
 *
 * "Locale" is the system in C that support language- and
 * contry-specific settings for a number of areas, including currency
 * symbols, date and time, and multibyte encodings.
 *
 * This setting determines whether the locale interface exist or not.
 * When this feature is selected, i.e. set to 1, the locale interface exist
 * (setlocale, etc). A number of preselected locales can be activated during
 * runtime. The preselected locales and encodings are choosen at linkage. The
 * application will start with the "C" locale choosen. (Single byte encoding is
 * always supported in this mode.)
 *
 *
 * If not selected, i.e. set to 0, the locale interface (setlocale, etc) does
 * not exist. The C locale is then preset and cannot be changed.
 *
 * The default is not to have support for the locale interface with the "C"
 * locale and the single byte encoding.
 */


/*
 * Define what memory to place the locale table segment (.iar.locale_table)
 * in.
 */

/*
 * Wide character and multi byte character support in library.
 */


/*
 * Support of multibytes in printf- and scanf-like functions
 *
 * This is the default value for _DLIB_PRINTF_MULTIBYTE and
 * _DLIB_SCANF_MULTIBYTE. See them for a description.
 *
 * Default is to not have support for multibytes in printf- and scanf-like
 * functions.
 */


/*
 * Hexadecimal floating-point numbers in strtod
 *
 * If selected, i.e. set to 1, strtod supports C99 hexadecimal floating-point
 * numbers. This also enables hexadecimal floating-points in internal functions
 * used for converting strings and wide strings to float, double, and long
 * double.
 *
 * If not selected, i.e. set to 0, C99 hexadecimal floating-point numbers
 * aren't supported.
 *
 * Default is not to support hexadecimal floating-point numbers.
 */



/*
 * Printf configuration symbols.
 *
 * All the configuration symbols described further on controls the behaviour
 * of printf, sprintf, and the other printf variants.
 *
 * The library proves four formatters for printf: 'tiny', 'small',
 * 'large', and 'default'.  The setup in this file controls all except
 * 'tiny'.  Note that both small' and 'large' explicitly removes
 * some features.
 */

/*
 * Handle multibytes in printf
 *
 * This setting controls whether multibytes and wchar_ts are supported in
 * printf. Set to 1 to support them, otherwise set to 0.
 *
 * See _DLIB_FORMATTED_MULTIBYTE for the default setting.
 */

/*
 * Support of formatting anything larger than int in printf
 *
 * This setting controls if 'int' should be used internally in printf, rather
 * than the largest existing integer type. If 'int' is used, any integer or
 * pointer type formatting use 'int' as internal type even though the
 * formatted type is larger. Set to 1 to use 'int' as internal type, otherwise
 * set to 0.
 *
 * See also next configuration.
 *
 * Default is to internally use largest existing internally type.
 */

/*
 * Support of formatting anything larger than long in printf
 *
 * This setting controls if 'long' should be used internally in printf, rather
 * than the largest existing integer type. If 'long' is used, any integer or
 * pointer type formatting use 'long' as internal type even though the
 * formatted type is larger. Set to 1 to use 'long' as internal type,
 * otherwise set to 0.
 *
 * See also previous configuration.
 *
 * Default is to internally use largest existing internally type.
 */


/*
 * Emit a char a time in printf
 *
 * This setting controls internal output handling. If selected, i.e. set to 1,
 * then printf emits one character at a time, which requires less code but
 * can be slightly slower for some types of output.
 *
 * If not selected, i.e. set to 0, then printf buffers some outputs.
 *
 * Note that it is recommended to either use full file support (see
 * _DLIB_FILE_DESCRIPTOR) or -- for debug output -- use the linker
 * option "-e__write_buffered=__write" to enable buffered I/O rather
 * than deselecting this feature.
 */


/*
 * Scanf configuration symbols.
 *
 * All the configuration symbols described here controls the
 * behaviour of scanf, sscanf, and the other scanf variants.
 *
 * The library proves three formatters for scanf: 'small', 'large',
 * and 'default'.  The setup in this file controls all, however both
 * 'small' and 'large' explicitly removes some features.
 */

/*
 * Handle multibytes in scanf
 *
 * This setting controls whether multibytes and wchar_t:s are supported in
 * scanf. Set to 1 to support them, otherwise set to 0.
 *
 * See _DLIB_FORMATTED_MULTIBYTE for the default.
 */

/*
 * Handle multibytes in asctime and strftime.
 *
 * This setting controls whether multibytes and wchar_ts are
 * supported.Set to 1 to support them, otherwise set to 0.
 *
 * See _DLIB_FORMATTED_MULTIBYTE for the default setting.
 */

/*
 * Implement "qsort" using a bubble sort algorithm.
 *
 * Bubble sort is less efficient than quick sort but requires less RAM
 * and ROM resources.
 */



/*
 * Set Buffert size used in qsort
 */



/*
 * Use a simple rand implementation to reduce memory footprint.
 *
 * The default "rand" function uses an array of 32 long:s of memory to
 * store the current state.
 *
 * The simple "rand" function uses only a single long. However, the
 * quality of the generated psuedo-random numbers are not as good as
 * the default implementation.
 */



/*
 * Set attributes for the function used by the C-SPY debug interface to stop at.
 */


/*
 * Used by products where one runtime library can be used by applications
 * with different data models, in order to reduce the total number of
 * libraries required. Typically, this is used when the pointer types does
 * not change over the data models used, but the placement of data variables
 * or/and constant variables do.
 *
 * If defined, this symbol is typically defined to the memory attribute that
 * is used by the runtime library. The actual define must use a
 * _Pragma("type_attribute = xxx") construct. In the header files, it is used
 * on all statically linked data objects seen by the application.
 */



/*
 * Turn on support for the Target-specific ABI. The ABI is based on the
 * ARM AEABI. A target, except ARM, may deviate from it.
 */


  /* Possible AEABI deviations */


  /*
   * The "difunc" table contains information about C++ objects that
   * should be dynamically initialized, where each entry in the table
   * represents an initialization function that should be called. When
   * the symbol _DLIB_AEABI_DIFUNC_CONTAINS_OFFSETS is true, each
   * entry in the table is encoded as an offset from the entry
   * location. When false, the entries contain the actual addresses to
   * call.
   */


/*
 * Turn on usage of a pragma to tell the linker the number of elements used
 * in a setjmp jmp_buf.
 */



/*
 * If true, the product supplies a "DLib_Product_string.h" file that
 * is included from "string.h".
 */


/*
 * Determine whether the math fma routines are fast or not.
 */


/*
 * Favor speed versus some size enlargements in floating point functions.
 */


/*
 * Include dlmalloc as an alternative heap manager in the product.
 *
 * Typically, an application will use a "malloc" heap manager that is
 * relatively small but not that efficient. An application can
 * optionally use the "dlmalloc" package, which provides a more
 * effective "malloc" heap manager, if it is included in the product
 * and supported by the settings.
 *
 * See the product documentation on how to use it, and whether or not
 * it is included in the product.
 */

  /* size_t/ptrdiff_t must be a 4 bytes unsigned integer. */


/*
 * Make sure certain C++ functions use the soft floating point variant.
 */



/*
 * Allow the 64-bit time_t interface?
 *
 * Default is yes if long long is 64 bits.
 */



/*
 * Is time_t 64 or 32 bits?
 *
 * Default is 32 bits.
 */



/*
 * Do we include math functions that demands lots of constant bytes?
 * (like erf, erfc, expm1, fma, lgamma, tgamma, and *_accurate)
 *
 */



/*
 * Support of weak.
 *
 * __weak must be supported. Support of weak means that the call to
 * a weak declared function that isn't part of the application will be
 * executed as a nop instruction.
 *
 */


/*
 * Deleted options
 */








/* A definiton for a function of what effects it has.
   NS  = no_state, errno, i.e. it uses no internal or external state. It may
         write to errno though
   NE  = no_state, i.e. it uses no internal or external state, not even
         writing to errno. 
   NRx = no_read(x), i.e. it doesn't read through pointer parameter x.
   NWx = no_write(x), i.e. it doesn't write through pointer parameter x.
   Rx  = returns x, i.e. the function will return parameter x.
   
   All the functions with effects also has "always_returns", 
   i.e. the function will always return.
*/


/* Common function attribute macros */



/* namespace and extern "C" handling */



/*
 * Support for C99/C11 functionality, C99 secure C functionality, and some
 * other functionality.
 *
 * This setting makes available some macros, functions, etc that are
 * either mandatory in C99/C11 or beneficial.
 *
 * Default is to include them.
 *
 * Disabling this in C++ mode will not compile (some C++ functions uses C99
 * functionality).
 */

  /* Default turned on only when compiling C89 (not C++, C99, or C11). */


/* Secure C */



/* C++ language setup */



/* MB_LEN_MAX (max for utf-8 is 4) */

/* for parsing numerics */

/* wchar_t setup */
  typedef unsigned int _Wchart;
    typedef unsigned int _Wintt;

/* POINTER PROPERTIES */

/* size_t setup */
typedef unsigned int     _Sizet;

/* mbstatet setup */
typedef struct _Mbstatet
{ /* state of a multibyte translation */
    unsigned int _Wchar;  /* Used as an intermediary value (up to 32-bits) */
    unsigned int _State;  /* Used as a state value (only some bits used) */

} _Mbstatet;

/* printf setup */

/* stdarg PROPERTIES */

  typedef struct __va_list
  {
    char  *_Ap;
  } __va_list;
  typedef __va_list __Va_list;



/* File position */
typedef struct
{       
    long long _Off;    /* can be system dependent */
  _Mbstatet _Wstate;
} _Fpost;


/* THREAD AND LOCALE CONTROL */

/* MULTITHREAD PROPERTIES */
  
  /* The lock interface for DLib to use. */ 
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_Malloc(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_Stream(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_Debug(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_StaticGuard(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_Malloc(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_Stream(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_Debug(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_StaticGuard(void);


  typedef void *__iar_Rmtx;

  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Initdynamiclock(__iar_Rmtx *);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Dstdynamiclock(__iar_Rmtx *);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Lockdynamiclock(__iar_Rmtx *);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlockdynamiclock(__iar_Rmtx *);

  



/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.50:0576 */


/* Fixed size types. These are all optional. */
  typedef signed char          int8_t;
  typedef unsigned char        uint8_t;

  typedef signed short int         int16_t;
  typedef unsigned short int       uint16_t;

  typedef signed int         int32_t;
  typedef unsigned int       uint32_t;

  typedef signed long long int         int64_t;
  typedef unsigned long long int       uint64_t;

/* Types capable of holding at least a certain number of bits.
   These are not optional for the sizes 8, 16, 32, 64. */
typedef signed char      int_least8_t;
typedef unsigned char    uint_least8_t;

typedef signed short int     int_least16_t;
typedef unsigned short int   uint_least16_t;

typedef signed int     int_least32_t;
typedef unsigned int   uint_least32_t;

/* This isn't really optional, but make it so for now. */
  typedef signed long long int   int_least64_t;
  typedef unsigned long long int uint_least64_t;

/* The fastest type holding at least a certain number of bits.
   These are not optional for the size 8, 16, 32, 64.
   For now, the 64 bit size is optional in IAR compilers. */
typedef signed int       int_fast8_t;
typedef unsigned int     uint_fast8_t;

typedef signed int      int_fast16_t;
typedef unsigned int    uint_fast16_t;

typedef signed int      int_fast32_t;
typedef unsigned int    uint_fast32_t;

  typedef signed long long int    int_fast64_t;
  typedef unsigned long long int  uint_fast64_t;

/* The integer type capable of holding the largest number of bits. */
typedef signed long long int          intmax_t;
typedef unsigned long long int        uintmax_t;

/* An integer type large enough to be able to hold a pointer.
   This is optional, but always supported in IAR compilers. */
typedef signed int          intptr_t;
typedef unsigned int        uintptr_t;

/* An integer capable of holding a pointer to a specific memory type. */
typedef int __data_intptr_t; typedef unsigned int __data_uintptr_t;

/* Minimum and maximum limits. */






















/* Macros expanding to integer constants. */








/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.50:0576 */
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
 * Convert Pointer to Memory Address Offset
 *
 * Converts a Pointer, which has to be located in SRAM, to its
 * offset to the SRAM base address
 *
 * @param       pointer          Pointer in SRAM Memory
 * @return      Offset of given pointer to SRAM base address
 * ****************************************************************************/
uint16_t util_calculateDmaMemoryOffset(void* pointer);

/* **************************************************************************//**
 * @brief
 * Calculate the currently set transducer frequency
 *
 * @return      currently set transducer_frequency
 * ****************************************************************************/
uint32_t util_CalcBurstFrequency(void);

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


/** @addtogroup dsi3_Driver_interfaces
 * @{ */
/***************************************************************************/
/** @file       Dsi3Bus_Types.h
 *
 * @brief       Definitions of basic data types for the DSI3 bus layer implementation.
 *
 * @purpose   Definitions of data types and structs used in the DSI3 bus layer 
 *            implementation.
 *
 * Demo Code Usage Restrictions:
 * Elmos Semiconductor AG provides this source code file simply and solely for
 * IC evaluation purposes in laboratory and this file must not be used for other 
 * purposes or within non laboratory environments. Especially, the use or the
 * integration in production systems, appliances or other installations is
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
 *
 * @section history_sec_Dsi3Bus_Types_h Revision History
 * $Id: Dsi3Bus_Types.h 422 2019-03-14 14:55:33Z poe $
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who Ver  Comment
 * -------------------------------------------------------------------
 * 19/03/11 (F) POE 1008 Added error code for disc mode current detection error.
 * 18/11/20 (F) POE 1007 Changed #pragma declaration for compiler compatibility.
 * 18/08/21 (F) POE 1006 Added doxygen comments.
 * 18/08/17 (F) POE 1005 Renamed Dsi3BusIf_eInterfaceIds Lin_IfId_Count to Dsi3_IfId_Count.
 * 18/03/23 (F) POE 1004 Added 524.17B configuration parameters.
 * 18/02/26 (F) POE 1003 removed unused internal state enums.
 * 18/01/17 (F) POE 1002 updated header and demo usage disclaimer.
 * ...
 * 17/06/19 (F) POE 1000 initial version
 * -------------------------------------------------------------------
 * @endverbatim
 *
 * @creator      POE
 * @created      2017/06/19
 *
 * @project      524.17
 * @requested    ELMOS
 * @inspector    -
 * @verification -
 * @version      $Revision: 422 $
 *
 *
 * $State: Exp $
 * $Author: poe $
 *
 * Additional markers:
 *
 */

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
/* ------------------------------------------------------------------- */
/** @file dsi3_InterruptHandler.h
 *
 * @brief Module interrupt handler for DSI3 hardware module.
 *
 * Purpose:
 * This module provides functions for handling DSI3 interrupts
 * - Interrupt initialization
 * - Interrupt enabling
 * - Interrupt disabling
 * - Registering user callback function for interrupt handling
 * - De-registering user callback function for interrupt handling
 * - The interrupt handler itself, which provides the interrupt handling
 *   in hardware and calls the user callback function for functional 
 *   interrupt handling
 *
 * Demo Code Usage Restrictions:
 * Elmos Semiconductor AG provides this source code file simply and solely for
 * IC evaluation purposes in laboratory and this file must not be used for other 
 * purposes or within non laboratory environments. Especially, the use or the
 * integration in production systems, appliances or other installations is
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
 * @section history_sec Revision History
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who Ver  Comment
 * -------------------------------------------------------------------
 * 17/05/23 (F) poe 1001 first creation
 * -------------------------------------------------------------------
 * @endverbatim
 *
 * @creator      poe
 * @created      2017/05/23
 *
 * @project      524.17
 * @requested    ELMOS
 * @inspector    -
 * @verification -
 * @version      $Revision: 392 $
 *
 *
 * $State: Exp $
 * $Author: siko $
 *
 * Additional markers:
 *
 */

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
/***************************************************************************//**
 * @file			el_types.h
 *
 * @creator		sbai
 * @created		06.10.2014
 *
 * @brief  		Provides all basic data type definitions
 *
 * @purpose
 *
 * Provides all basic data type definitions for Elmos's CPU APIs and development
 * on ELMOS'S intelligent ICs.
 *
 * $Id: el_types.h 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
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
/* ************************ ARCH DEPENDENT INCLUDES ***************************/
/* ****************************************************************************/

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
 


/* ===================================== */
/* arch and compiler defines             */
/* ===================================== */

//#define EL_ARCH_H430               
//#define EL_ARCH_EL16               
//#define EL_ARCH_EL35               

//#define EL_COMPILER_KEIL           
//#define EL_COMPILER_COSMIC            
//#define EL_COMPILER_GCC


/* ===================================== */
/* linux-like types                      */
/* ===================================== */

/* stdbool.h header */
/* Copyright 2003-2017 IAR Systems AB.  */


  #pragma system_include





/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.50:0576 */

typedef _Bool bool_t;
	


typedef unsigned int        bitfield_t;



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





  
	







 /* ------------------------------------------------------------------- */
/** @file nvic_Interface.h
 *
 * @brief Interface definitions for NVIC Interrupt control implementation.
 *
 * Purpose:
 * Provided interface functions for NVIC Interrupt control implementation.
 *
 * Demo Code Usage Restrictions:
 * Elmos Semiconductor AG provides this source code file simply and solely for
 * IC evaluation purposes in laboratory and this file must not be used for other 
 * purposes or within non laboratory environments. Especially, the use or the
 * integration in production systems, appliances or other installations is
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
 * @section history_sec Revision History
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who Ver  Comment
 * -------------------------------------------------------------------
 * 15/13/01 (F) rpy 1001 first creation
 * -------------------------------------------------------------------
 * @endverbatim
 *
 * @creator      rpy
 * @created      2015/13/01
 *
 * @project      524.17
 * @requested    ELMOS
 * @inspector    -
 * @verification -
 * @version      $Revision: 392 $
 *
 *
 * $State: Exp $
 * $Author: siko $
 *
 * Additional markers:
 *
 */


/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* *********************** CORE LEVEL IRQ MANAGEMEN ***************************/
/* ****************************************************************************/



/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

typedef uint16_t nvic_InterfaceVersion_t;         /**< Data type for interface version representation **/

typedef void * nvic_pInterruptModuleEnvironmentData_t;  /**< Generic pointer type to module specific environment data **/


/***************************************************************************//**
 * @brief NVIC IRQ vector numbers 
 ******************************************************************************/
typedef enum nvic_eExceptionVectorNum
{
  nvic_CEVT_INIT_SP                     = 0u,
  nvic_CEVT_RESET                       = 1u,
  nvic_CEVT_NMI                         = 2u,
  nvic_CEVT_HARD_FAULT                  = 3u,
  /* 4u ... 10u reserved */ 
  nvic_CEVT_SVC                         = 11u,
  /* 12u ... 13u reserved */ 
  nvic_CEVT_PEND_SV                     = 14u,
  nvic_CEVT_SYSTICK                     = 15u,
  
  nvic_CEVT_EXT_IRQ_0                   = 16u,
  nvic_CEVT_EXT_IRQ_1                   = 17u,
  nvic_CEVT_EXT_IRQ_2                   = 18u,
  nvic_CEVT_EXT_IRQ_3                   = 19u,
  nvic_CEVT_EXT_IRQ_4                   = 20u,
  nvic_CEVT_EXT_IRQ_5                   = 21u,
  nvic_CEVT_EXT_IRQ_6                   = 22u,
  nvic_CEVT_EXT_IRQ_7                   = 23u,
  nvic_CEVT_EXT_IRQ_8                   = 24u,
  nvic_CEVT_EXT_IRQ_9                   = 25u,
  nvic_CEVT_EXT_IRQ_10                  = 26u,
  nvic_CEVT_EXT_IRQ_11                  = 27u,
  nvic_CEVT_EXT_IRQ_12                  = 28u,
  nvic_CEVT_EXT_IRQ_13                  = 29u,
  nvic_CEVT_EXT_IRQ_14                  = 30u,
  nvic_CEVT_EXT_IRQ_15                  = 31u,
  
  nvic_CEVT_VECTOR_CNT                  = 32u  /**< Number of available interrupt vectors */
   
} nvic_eExceptionVectorNum_t;


/***************************************************************************//**
 * @brief priority level mapping for ARM architecture
 ******************************************************************************/

typedef enum
{
  nvic_Priority_Level_0                 = 0u,
  nvic_Priority_Level_1                 = 1u,
  nvic_Priority_Level_2                 = 2u,
  nvic_Priority_Level_3                 = 3u
} nvic_ePriorityLevels_t;


/***************************************************************************//**
 * @brief mapping defines for the actual module IRQ assignment
 ******************************************************************************/


/***************************************************************************//**
 * @brief Interrupt handler function typedef
 *
 * This function type represents the actual interrupt handler function as 
 * implemented in each module. 
 *
 ******************************************************************************/
typedef __irq void (*nvic_InterruptCallback_t) (void); 


/***************************************************************************//**
 * @brief VIC environment data type
 ******************************************************************************/
typedef struct nvic_sInterruptEnvironmentData
{
    /** Interrupt vector table to module interrupt handler */
    nvic_InterruptCallback_t InterrupVectorTable[nvic_CEVT_VECTOR_CNT];
    
    /** Pointer to module vector table */
    nvic_pInterruptModuleEnvironmentData_t ModuleEnvironmentData[nvic_CEVT_VECTOR_CNT];
    
} nvic_sInterruptEnvironmentData_t;

/***************************************************************************//**
 * @brief Pointer to VIC environment data.
 ******************************************************************************/
typedef nvic_sInterruptEnvironmentData_t * nvic_pInterruptEnvironmentData_t;

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ********************* EXTERNAL FUNCTIONS / INTERFACE ***********************/
/* ****************************************************************************/

/***************************************************************************//**
 * @brief Returns current module specific environment data
 *
 * @param module  Module number 
 *
 * @return        Pointer to module data (may be NULL)
 *
 ******************************************************************************/
typedef nvic_pInterruptModuleEnvironmentData_t (*nvic_GetPointerToEnvironmentData_t)(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * @brief Introduces a module into the global VIC based IRQ handling
 *
 * @param module                  Module number
 *
 * @param interrupthandler        Pointer to module specific interrupt handler
 *
 * @param moduleenvironmentdata   Pointer to module specific interrupt handler runtime data
 *
 *
 ******************************************************************************/
typedef void (*nvic_RegisterModule_t)(nvic_eExceptionVectorNum_t vno, nvic_InterruptCallback_t interrupthandler,
                                     nvic_pInterruptModuleEnvironmentData_t moduleenvironmentdata);

/***************************************************************************//**
 * @brief Removes module handler for a particular module. 
 *
 * @param module                  Module number
 *
 * A default IRQ handler is installed for the selected module.
 *
 ******************************************************************************/
typedef void (*nvic_DeregisterModule_t)(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * @brief Enables interrupt processing for specified module
 *
 * @param module                  Module number
 *
 ******************************************************************************/
typedef void (*nvic_EnableModule_t)(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * @brief Disables interrupt processing for specified module
 *
 * @param module                  Module number
 *
 ******************************************************************************/
typedef void (*nvic_DisableModule_t)(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * @brief Enables interrupt processing for specified module
 *
 * @param module                  Module number
 *
 ******************************************************************************/
typedef void (*nvic_ClearPending_t)(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * @brief Enables interrupt processing for specified module
 *
 * @param module                  Module number
 *
 ******************************************************************************/
typedef void (*nvic_SetPending_t)(nvic_eExceptionVectorNum_t vno);


/***************************************************************************//**
 * @brief Assign interrupt priority level for specified module
 *
 * @param module                  Module number
 *
 ******************************************************************************/
typedef void (*nvic_SetModulePriority_t)(nvic_eExceptionVectorNum_t vno, nvic_ePriorityLevels_t prio);

/***************************************************************************//**
 * @brief Enables general interrupt processing
 *
 ******************************************************************************/
typedef void (*nvic_EnableMain_t)(void);

/***************************************************************************//**
 * @brief Disables general interrupt processing
 *
 ******************************************************************************/
typedef void (*nvic_DisableMain_t)(void);

/***************************************************************************//**
 * @brief Initializes global interrupt handling
 *
 * @param environmentdata  Pointer to Environment data for VIC module in
 *                         user RAM
 *
 ******************************************************************************/
typedef bool_t (*nvic_IRQInitialisation_t)(nvic_pInterruptEnvironmentData_t penvironmentdata);

/***************************************************************************//**
 * @brief LIN driver interface function pointer
 ******************************************************************************/
struct nvic_sInterfaceFunctions
{
  nvic_InterfaceVersion_t            InterfaceVersion;

  nvic_IRQInitialisation_t           IRQInitialisation;

  nvic_GetPointerToEnvironmentData_t GetPointerToEnvironmentData;

  nvic_RegisterModule_t              RegisterModule;
  nvic_DeregisterModule_t            DeregisterModule;
  nvic_EnableModule_t                EnableModule;
  nvic_DisableModule_t               DisableModule;  
  nvic_ClearPending_t                ClearPending;
  nvic_SetPending_t                  SetPending;
  nvic_SetModulePriority_t           SetModulePriority;
  
  nvic_EnableMain_t                  EnableMain;
  nvic_DisableMain_t                 DisableMain;
};

typedef struct nvic_sInterfaceFunctions    nvic_sInterfaceFunctions_t;
typedef        nvic_sInterfaceFunctions_t* nvic_pInterfaceFunctions_t;
typedef const  nvic_sInterfaceFunctions_t* nvic_cpInterfaceFunctions_t;






/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/* *****************************************************************************
 * DSI3_IRQ vector numbers
 * *****************************************************************************/
    
typedef enum {
    dsi3_IRQ_SYNC_EVT                   =  0u,
    dsi3_IRQ_CMD_EVT                    =  1u,
    dsi3_IRQ_PDCM_EVT                   =  2u,
    dsi3_IRQ_DISC_EVT			=  3u,
    dsi3_IRQ_CRC_ERR_EVT                =  4u,
    dsi3_IRQ_PDCM_ERR_EVT               =  5u,
    dsi3_IRQ_DISC_ERR_EVT		=  6u,				
    dsi3_IRQ_FCC_ERROR                  =  7u,
    dsi3_IRQ_START_ERR_EVT              =  8u,
    dsi3_IRQ_TIMER_A_EVT                =  9u,
    dsi3_IRQ_TIMER_B_EVT                = 10u,
    dsi3_IRQ_TIMER_C_EVT		= 11u,
    dsi3_IRQ_RCC_FINISH                 = 12u,
    dsi3_IRQ_RCC_READY                  = 13u,
    dsi3_IRQ_SYNC_CNT_EVT               = 14u,
    dsi3_IRQ_DISC_CURR_EVT		= 15u,
    
    dsi3_INTERRUPT_VECTOR_CNT           = 16u  /**< Number of available interrupt vectors */    
} dsi3_eInterruptVectorNum_t;


/***************************************************************************//**
 * Pointer to context data
 ******************************************************************************/
typedef void * dsi3_pInterruptContextData_t;

/***************************************************************************//**
 * Callback function pointer type
 ******************************************************************************/

typedef void (*dsi3_InterruptCallback_t) (dsi3_eInterruptVectorNum_t sno, dsi3_pInterruptContextData_t genericCbCtxData);

/***************************************************************************//**
 * DSI3 environment data
 ******************************************************************************/
typedef struct dsi3_sInterruptEnvironmentData
{
    /** Interrupt vector table of this module             */
    dsi3_InterruptCallback_t InterrupVectorTable[dsi3_INTERRUPT_VECTOR_CNT];
    
    /** DSI3 module context data */
    dsi3_pInterruptContextData_t ContextData;
    
} dsi3_sInterruptEnvironmentData_t;

/***************************************************************************//**
 * Pointer to DSI3 environment data
 ******************************************************************************/
typedef dsi3_sInterruptEnvironmentData_t * dsi3_pInterruptEnvironmentData_t;

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ********************* EXTERNAL FUNCTIONS / INTERFACE ***********************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ******************************* INTERRUPTS *********************************/
/* ****************************************************************************/

/***************************************************************************//**
 * @brief     Enables an IRQ.
 *
 * @param[in] modulBaseAddress  Pointer to DSI3 module base address
 * @param[in] irqsrc            IRQ to be enabled
 *
 * @pre       A call back function to the related interrupt should have been
 *            registered with dsi3_RegisterInterruptCallback().
 *
 * @post      The related call back function will be called if the desired
 *            interrupt occurs.
 *
 * @detaildesc
 * The DSI3_IRQ_VENABLE register will be set the related IRQ number and therefore
 * the interrupt will be activated.
 *
 ******************************************************************************/
void dsi3_InterruptEnable(dsi3_eInterruptVectorNum_t irqsrc);

/***************************************************************************//**
 * @brief Disables an IRQ.
 *
 * @param[in] modulBaseAddress  Pointer to DSI3 module base address
 * @param[in] irqsrc            IRQ to be disable
 *
 * @post      The interrupt will be disabled and the related callback function
 *            will no longer be called from the interrupt handler.
 *
 * @detaildesc
 * The DSI3_IRQ_VDISABLE register will be set the related IRQ number and therefore
 * the interrupt will be deactivated.
 *
 ******************************************************************************/
void dsi3_InterruptDisable(dsi3_eInterruptVectorNum_t irqsrc);

/***************************************************************************//**
 * @brief Registers/Adds callback function to the module interrupt vector table.
 *
 * @param modulBaseAddress  Pointer to DSI3 module base address
 * @param irqsrc            IRQ number
 * @param cbfnc             Pointer to desired callback function
 *
 * @pre     (optional) Which are the conditions to call this function? i.e. none
 *
 * @post    If the interrupt will be activated the registered callback function
 *          will be called if the IRQ occurs.
 *
 * @detaildesc
 * Registers the callback function at interrupt vector handling. It sets the
 * entry in the interrupt vector table to passed function pointer.
 *
 ******************************************************************************/
void dsi3_InterruptRegisterCallback(dsi3_eInterruptVectorNum_t irqsrc, dsi3_InterruptCallback_t cbfnc);

/***************************************************************************//**
 * @brief Deregisters/deletes callback function from module interrupt vector table.
 *
 * @param modulBaseAddress  Pointer to DSI3 module base address
 * @param irqvecnum         IRQ number
 * @param cbfnc             Pointer to desired callback function
 *
 * @pre   The related IRQ should be disabled.
 *
 * @post  The entry in the module interrupt vector table will point to NULL and
 *        the related IRQ will be disabled.
 *
 * @detaildesc
 * Deregisters the callback function from interrupt vector handling. It sets the
 * entry in the interrupt vector table to NULL and disables the related interrupt.
 *
 ******************************************************************************/
void dsi3_InterruptDeregisterCallback(dsi3_eInterruptVectorNum_t irqvecnum);

/***************************************************************************//**
 * @brief Initialize DSI3 module
 *
 * @param environmentdata  Pointer to Environment data for DSI3 module in
 *                         user RAM
 *
 * @pre        VIC (vic_VectorInterruptControl) and DSI3 (dsi3_SystemStateModule)
 *             have to presented and initialized.
 *
 * @post       DSI3 module is configured for use.
 *
 * @detaildesc
 * Initializes the DSI3 software and hardware module, including the module
 * interrupt vector table. Configures if IRQ nesting is active and if IO2 and
 * IO3 are used as DSI3s or not.
 *
 ******************************************************************************/
void dsi3_InterruptInitialisation(nvic_cpInterfaceFunctions_t vicIf, dsi3_pInterruptEnvironmentData_t environmentdata, dsi3_pInterruptContextData_t contextdata);



/* ------------------------------------------------------------------- */
/** @file def_dsi3.h
 *
 * @brief Helper definitions for DSI3 hardware module.
 *
 * Purpose:
 * Provide register access and register value definitions 
 * for DSI3 hardware module
 *
 * Demo Code Usage Restrictions:
 * Elmos Semiconductor AG provides this source code file simply and solely for
 * IC evaluation purposes in laboratory and this file must not be used for other 
 * purposes or within non laboratory environments. Especially, the use or the
 * integration in production systems, appliances or other installations is
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
 * @section history_sec Revision History
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who Ver  Comment
 * -------------------------------------------------------------------
 * 19/03/11 (F) poe 1006 added macro to read sync cnt err flag.
 * 19/01/11 (F) poe 1005 fixed name typo in typedef for dsi3_eRCC_Curve and dsi3_eRCC_Slope
 * 18/11/30 (F) poe 1004 added macro definition for manual current measurement start (E524.17A1)
 * 18/04/23 (F) poe 1003 added TimerX max value define, synced dsi3_eRCCSlope with 52417B type
 * 18/02/23 (F) poe 1002 added defines for fcc_low_flag access
 * 17/05/23 (F) poe 1001 first creation
 * -------------------------------------------------------------------
 * @endverbatim
 *
 * @creator      poe
 * @created      2017/05/23
 *
 * @project      524.17
 * @requested    ELMOS
 * @inspector    -
 * @verification -
 * @version      $Revision: 424 $
 *
 *
 * $State: Exp $
 * $Author: siko $
 *
 * Additional markers:
 *
 */
//################################################################################
//  Helper defines
//################################################################################


/* *************************************************************************** */
/* ******************************** INCLUDES ********************************* */
/* *************************************************************************** */
/***************************************************************************//**
 * @file			el_types.h
 *
 * @creator		sbai
 * @created		06.10.2014
 *
 * @brief  		Provides all basic data type definitions
 *
 * @purpose
 *
 * Provides all basic data type definitions for Elmos's CPU APIs and development
 * on ELMOS'S intelligent ICs.
 *
 * $Id: io_m52417a.h 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
 *
 *****************************************************************************
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
/* ************************ ARCH DEPENDENT INCLUDES ***************************/
/* ****************************************************************************/


  /* use local modified version for IAR */ 

/****************************************************************************************************//**
 * @file     m52417a.h
 *
 * @brief    CMSIS Cortex-M0 Peripheral Access Layer Header File for
 *           m52417a from .
 *
 * @version  V1.0
 * @date     8. September 2017
 *
 * @note     Generated with SVDConv V2.87l 
 *           from CMSIS SVD File 'm52417a.svd' Version 1.0,
 *
 * @note:    Generated for MISRA Compliance, this File is NOT CMSIS compliant.
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
 *******************************************************************************************************/



/** @addtogroup m52417a
  * @{
  */




/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum {
/* -------------------  Cortex-M0 Processor Exceptions Numbers  ------------------- */
  Reset_IRQn                    = -15,              /*!<   1  Reset Vector, invoked on Power up and warm reset                 */
  NonMaskableInt_IRQn           = -14,              /*!<   2  Non maskable Interrupt, cannot be stopped or preempted           */
  HardFault_IRQn                = -13,              /*!<   3  Hard Fault, all classes of Fault                                 */
  SVCall_IRQn                   =  -5,              /*!<  11  System Service Call via SVC instruction                          */
  PendSV_IRQn                   =  -2,              /*!<  14  Pendable request for system service                              */
  SysTick_IRQn                  =  -1,              /*!<  15  System Tick Timer                                                */
/* ---------------------  m52417a Specific Interrupt Numbers  --------------------- */
  SYS_STATE_IRQn                =   0,              /*!<   0  SYS_STATE                                                        */
  EEPROM_CTRL_IRQn              =   1,              /*!<   1  EEPROM_CTRL                                                      */
  DSI3_IRQn                     =   2,              /*!<   2  DSI3                                                             */
  SWTIMER_IRQn                  =   3,              /*!<   3  SWTIMER                                                          */
  DSP_IRQn                      =   4,              /*!<   4  DSP                                                              */
  GPIO_IRQn                     =   5,              /*!<   5  GPIO                                                             */
  UART_IRQn                     =   6,              /*!<   6  UART                                                             */
  SYSTEM_CTRL_IRQn              =   7               /*!<   7  SYSTEM_CTRL                                                      */
} IRQn_Type;


/** @addtogroup Configuration_of_CMSIS
  * @{
  */


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* ----------------Configuration of the Cortex-M0 Processor and Core Peripherals---------------- */
/** @} */ /* End of group Configuration_of_CMSIS */

/*
 *-----------------------------------------------------------------------------
 * The confidential and proprietary information contained in this file may
 * only be used by a person authorised under and to the extent permitted
 * by a subsisting licensing agreement from ARM Limited.
 *
 *            (C) COPYRIGHT 2009-2010 ARM Limited.
 *                ALL RIGHTS RESERVED
 *
 * This entire notice must be reproduced on all copies of this file
 * and copies of this file may only be made by a person if such person is
 * permitted to do so under the terms of a subsisting license agreement
 * from ARM Limited.
 *
 *      SVN Information
 *
 *      Checked In          : $Date: 2019-01-22 10:59:18 +0100 (Di, 22 Jan 2019) $
 *
 *      Revision            : $Revision: 392 $
 *
 *      Release Information : Cortex-M0-AT510-r0p0-03rel0
 *-----------------------------------------------------------------------------
 */

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












/**************************************************
 *
 * This file declares the ARM intrinsic inline functions.
 *
 * Copyright 1999-2018 IAR Systems. All rights reserved.
 *
 * $Revision: 125703 $
 *
 **************************************************/


  #pragma system_include

/*
 * Check that the correct C compiler is used.
 */


/**************************************************
 *
 * This file declares the ICCARM builtin functions.
 *
 * Copyright 1999-2017 IAR Systems. All rights reserved.
 *
 * $Revision: 126708 $
 *
 **************************************************/



  #pragma system_include

/*
 * Check that the correct C compiler is used.
 */


/* Define function effects for intrinsics */


#pragma language=save
#pragma language=extended

__intrinsic __nounwind void    __iar_builtin_no_operation(void);

__intrinsic __nounwind void    __iar_builtin_disable_interrupt(void);
__intrinsic __nounwind void    __iar_builtin_enable_interrupt(void);

typedef unsigned int __istate_t;

__intrinsic __nounwind __istate_t __iar_builtin_get_interrupt_state(void);
__intrinsic __nounwind void __iar_builtin_set_interrupt_state(__istate_t);

/* System control access for Cortex-M cores */
__intrinsic __nounwind unsigned int __iar_builtin_get_PSR( void );
__intrinsic __nounwind unsigned int __iar_builtin_get_IPSR( void );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_get_MSP( void );
__intrinsic __nounwind void         __iar_builtin_set_MSP( unsigned int );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_get_PSP( void );
__intrinsic __nounwind void         __iar_builtin_set_PSP( unsigned int );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_get_PRIMASK( void );
__intrinsic __nounwind void         __iar_builtin_set_PRIMASK( unsigned int );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_get_CONTROL( void );
__intrinsic __nounwind void         __iar_builtin_set_CONTROL( unsigned int );

/* These are only available for v7M */
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_get_FAULTMASK( void );
__intrinsic __nounwind void         __iar_builtin_set_FAULTMASK(unsigned int);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_get_BASEPRI( void );
__intrinsic __nounwind void         __iar_builtin_set_BASEPRI( unsigned int );

/* "Old" style intrerrupt control routines */
__intrinsic __nounwind void __iar_builtin_disable_irq(void);
__intrinsic __nounwind void __iar_builtin_enable_irq(void);

__intrinsic __nounwind void __iar_builtin_disable_fiq(void);
__intrinsic __nounwind void __iar_builtin_enable_fiq(void);


/* ARM-mode intrinsics */

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SWP( unsigned int, volatile unsigned int * );
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned char __iar_builtin_SWPB( unsigned char, volatile unsigned char * );

typedef unsigned int __ul;
typedef unsigned int __iar_builtin_uint;


/*  Co-processor operations */

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind void __iar_builtin_CDP (unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) opc1, unsigned __constrange(0,15) CRd, unsigned __constrange(0,15) CRn, unsigned __constrange(0,15) CRm, unsigned __constrange(0,8) opc2) ;
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind void __iar_builtin_CDP2(unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) opc1, unsigned __constrange(0,15) CRd, unsigned __constrange(0,15) CRn, unsigned __constrange(0,15) CRm, unsigned __constrange(0,8) opc2) ;

/*  Co-processor access */
__intrinsic __nounwind void          __iar_builtin_MCR( unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opcode_1, __iar_builtin_uint src,
                                unsigned __constrange(0,15) CRn, unsigned __constrange(0,15) CRm, unsigned __constrange(0,8) opcode_2 )  ;
__intrinsic __nounwind unsigned int __iar_builtin_MRC( unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opcode_1,
                                unsigned __constrange(0,15) CRn, unsigned __constrange(0,15) CRm, unsigned __constrange(0,8) opcode_2 )  ;
__intrinsic __nounwind void          __iar_builtin_MCR2( unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opcode_1, __iar_builtin_uint src,
                                 unsigned __constrange(0,15) CRn, unsigned __constrange(0,15) CRm, unsigned __constrange(0,8) opcode_2 ) ;
__intrinsic __nounwind unsigned int __iar_builtin_MRC2( unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opcode_1,
                                 unsigned __constrange(0,15) CRn, unsigned __constrange(0,15) CRm, unsigned __constrange(0,8) opcode_2 ) ;

__intrinsic __nounwind void __iar_builtin_MCRR (unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opc1, unsigned long long src, unsigned __constrange(0,15) CRm) ;
__intrinsic __nounwind void __iar_builtin_MCRR2(unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opc1, unsigned long long src, unsigned __constrange(0,15) CRm) ;

__intrinsic __nounwind unsigned long long __iar_builtin_MRRC (unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opc1, unsigned __constrange(0,15) CRm) ;
__intrinsic __nounwind unsigned long long __iar_builtin_MRRC2(unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opc1, unsigned __constrange(0,15) CRm) ;

/* Load coprocessor register. */
__intrinsic __nounwind void __iar_builtin_LDC  ( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint const *src) ;
__intrinsic __nounwind void __iar_builtin_LDCL ( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint const *src) ;
__intrinsic __nounwind void __iar_builtin_LDC2 ( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint const *src) ;
__intrinsic __nounwind void __iar_builtin_LDC2L( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint const *src) ;

/* Store coprocessor register. */
__intrinsic __nounwind void __iar_builtin_STC  ( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint *dst) ;
__intrinsic __nounwind void __iar_builtin_STCL ( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint *dst) ;
__intrinsic __nounwind void __iar_builtin_STC2 ( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint *dst) ;
__intrinsic __nounwind void __iar_builtin_STC2L( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint *dst) ;

/* Load coprocessor register (noindexed version with coprocessor option). */
__intrinsic __nounwind void __iar_builtin_LDC_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint const *src,
                              unsigned __constrange(0,255) option);

__intrinsic __nounwind void __iar_builtin_LDCL_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint const *src,
                               unsigned __constrange(0,255) option);

__intrinsic __nounwind void __iar_builtin_LDC2_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint const *src,
                               unsigned __constrange(0,255) option);

__intrinsic __nounwind void __iar_builtin_LDC2L_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint const *src,
                                unsigned __constrange(0,255) option);

/* Store coprocessor register (version with coprocessor option). */
__intrinsic __nounwind void __iar_builtin_STC_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint *dst,
                              unsigned __constrange(0,255) option);

__intrinsic __nounwind void __iar_builtin_STCL_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint *dst,
                               unsigned __constrange(0,255) option);

__intrinsic __nounwind void __iar_builtin_STC2_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint *dst,
                               unsigned __constrange(0,255) option);

__intrinsic __nounwind void __iar_builtin_STC2L_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __iar_builtin_uint *dst,
                                unsigned __constrange(0,255) option);


/* Reads a system register */
__intrinsic __nounwind unsigned int       __iar_builtin_rsr(__spec_string const char * special_register)   ;
__intrinsic __nounwind unsigned long long __iar_builtin_rsr64(__spec_string const char * special_register) ;
__intrinsic __nounwind void*              __iar_builtin_rsrp(__spec_string const char * special_register)  ;

/* Writes a system register */
__intrinsic __nounwind void __iar_builtin_wsr(__spec_string const char * special_register, unsigned int value)         ;
__intrinsic __nounwind void __iar_builtin_wsr64(__spec_string const char * special_register, unsigned long long value) ;
__intrinsic __nounwind void __iar_builtin_wsrp(__spec_string const char * special_register, const void *value)         ;

/* Status register access, v7M: */
__intrinsic __nounwind unsigned int __iar_builtin_get_APSR( void );
__intrinsic __nounwind void         __iar_builtin_set_APSR( unsigned int );

/* Status register access */
__intrinsic __nounwind unsigned int __iar_builtin_get_CPSR( void );
__intrinsic __nounwind void         __iar_builtin_set_CPSR( unsigned int );

/* Floating-point status and control register access */
__intrinsic __nounwind unsigned int __iar_builtin_get_FPSCR( void );
__intrinsic __nounwind void __iar_builtin_set_FPSCR( unsigned int );

/* Architecture v5T, CLZ is also available in Thumb mode for Thumb2 cores */
/* For other architecture an instruction sequence is emitted */
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_CLZ(unsigned int) ;
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_ROR(unsigned int, unsigned int) ;
__intrinsic __nounwind unsigned int __iar_builtin_RRX(unsigned int);

/* Architecture v5TE or profile M with DSP-extension */
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind signed int __iar_builtin_QADD( signed int, signed int );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind signed int __iar_builtin_QDADD( signed int, signed int );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind signed int __iar_builtin_QSUB( signed int, signed int );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind signed int __iar_builtin_QDSUB( signed int, signed int );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind signed int __iar_builtin_QDOUBLE( signed int );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int        __iar_builtin_QFlag( void );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int   __iar_builtin_acle_QFlag(void);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind void  __iar_builtin_set_QFlag(int);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind void  __iar_builtin_ignore_QFlag(void);

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int         __iar_builtin_QCFlag( void );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind void __iar_builtin_reset_QC_flag( void );

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind signed int __iar_builtin_SMUL( signed short, signed short );

/* Architecture v6, REV and REVSH are also available in thumb mode */
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_REV( unsigned int );
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind signed int __iar_builtin_REVSH( short );

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_REV16( unsigned int );
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_RBIT( unsigned int );

_Pragma("function_effects = no_state, no_write(1), always_returns") __intrinsic __nounwind unsigned char  __iar_builtin_LDREXB( volatile unsigned char const * );
_Pragma("function_effects = no_state, no_write(1), always_returns") __intrinsic __nounwind unsigned short __iar_builtin_LDREXH( volatile unsigned short const * );
_Pragma("function_effects = no_state, no_write(1), always_returns") __intrinsic __nounwind unsigned int  __iar_builtin_LDREX ( volatile unsigned int const * );
_Pragma("function_effects = no_state, no_write(1), always_returns") __intrinsic __nounwind unsigned long long __iar_builtin_LDREXD( volatile unsigned long long const * );

_Pragma("function_effects = no_state, no_read(2), always_returns") __intrinsic __nounwind unsigned int  __iar_builtin_STREXB( unsigned char, volatile unsigned char * );
_Pragma("function_effects = no_state, no_read(2), always_returns") __intrinsic __nounwind unsigned int  __iar_builtin_STREXH( unsigned short, volatile unsigned short * );
_Pragma("function_effects = no_state, no_read(2), always_returns") __intrinsic __nounwind unsigned int  __iar_builtin_STREX ( unsigned int, volatile unsigned int * );
_Pragma("function_effects = no_state, no_read(2), always_returns") __intrinsic __nounwind unsigned int  __iar_builtin_STREXD( unsigned long long, volatile unsigned long long * );

__intrinsic __nounwind void __iar_builtin_CLREX( void );

__intrinsic __nounwind void __iar_builtin_SEV( void );
__intrinsic __nounwind void __iar_builtin_WFE( void );
__intrinsic __nounwind void __iar_builtin_WFI( void );
__intrinsic __nounwind void __iar_builtin_YIELD( void );

__intrinsic __nounwind void __iar_builtin_PLI( volatile void const * );
__intrinsic __nounwind void __iar_builtin_PLD( volatile void const * );

__intrinsic __nounwind void __iar_builtin_PLIx( volatile void const *, unsigned int __constrange(0,2), unsigned int __constrange(0,1));
__intrinsic __nounwind void __iar_builtin_PLDx( volatile void const *, unsigned int __constrange(0, 1), unsigned int __constrange(0, 2), unsigned int __constrange(0, 1));
__intrinsic __nounwind void __iar_builtin_PLDW( volatile void const * );

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind signed int   __iar_builtin_SSAT     (signed int val, unsigned int __constrange( 1, 32 ) sat );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_USAT     (signed int val, unsigned int __constrange( 0, 31 ) sat );

/* Architecture v6 Media instructions */
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SEL( unsigned int op1, unsigned int op2 );

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SADD8    (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SADD16   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SSUB8    (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SSUB16   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SADDSUBX (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SSUBADDX (unsigned int pair1, unsigned int pair2);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SHADD8   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SHADD16  (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SHSUB8   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SHSUB16  (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SHADDSUBX(unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SHSUBADDX(unsigned int pair1, unsigned int pair2);

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_QADD8    (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_QADD16   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_QSUB8    (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_QSUB16   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_QADDSUBX (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_QSUBADDX (unsigned int pair1, unsigned int pair2);

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UADD8    (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UADD16   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_USUB8    (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_USUB16   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UADDSUBX (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_USUBADDX (unsigned int pair1, unsigned int pair2);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UHADD8   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UHADD16  (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UHSUB8   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UHSUB16  (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UHADDSUBX(unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UHSUBADDX(unsigned int pair1, unsigned int pair2);

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UQADD8   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UQADD16  (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UQSUB8   (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UQSUB16  (unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UQADDSUBX(unsigned int pair1, unsigned int pair2);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UQSUBADDX(unsigned int pair1, unsigned int pair2);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_USAD8(unsigned int x, unsigned int y );
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_USADA8(unsigned int x, unsigned int y,
                                   unsigned int acc );

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SSAT16   (unsigned int pair,
                                      unsigned int __constrange( 1, 16 ) sat );
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_USAT16   (unsigned int pair,
                                      unsigned int __constrange( 0, 15 ) sat );

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMUAD (unsigned int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMUSD (unsigned int x, unsigned int y);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMUADX(unsigned int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMUSDX(unsigned int x, unsigned int y);

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLAD (unsigned int x, unsigned int y, int sum);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLSD (unsigned int x, unsigned int y, int sum);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLADX(unsigned int x, unsigned int y, int sum);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLSDX(unsigned int x, unsigned int y, int sum);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind long long __iar_builtin_SMLALD (unsigned int pair1,
                                 unsigned int pair2,
                                 long long acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind long long __iar_builtin_SMLALDX(unsigned int pair1,
                                 unsigned int pair2,
                                 long long acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind long long __iar_builtin_SMLSLD (unsigned int pair1,
                                 unsigned int pair2,
                                 long long acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind long long __iar_builtin_SMLSLDX(unsigned int pair1,
                                 unsigned int pair2,
                                 long long acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_PKHBT(unsigned int x,
                                  unsigned int y,
                                  unsigned __constrange(0,31) count);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_PKHTB(unsigned int x,
                                  unsigned int y,
                                  unsigned __constrange(0,32) count);

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLABB(unsigned int x, unsigned int y, int acc);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLABT(unsigned int x, unsigned int y, int acc);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLATB(unsigned int x, unsigned int y, int acc);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLATT(unsigned int x, unsigned int y, int acc);

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLAWB(int x, unsigned int y, int acc);
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMLAWT(int x, unsigned int y, int acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMMLA (int x, int y, int acc);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMMLAR(int x, int y, int acc);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMMLS (int x, int y, int acc);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMMLSR(int x, int y, int acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMMUL (int x, int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMMULR(int x, int y);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMULBB(unsigned int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMULBT(unsigned int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMULTB(unsigned int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMULTT(unsigned int x, unsigned int y);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMULWB(int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SMULWT(int x, unsigned int y);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SXTAB (int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind int __iar_builtin_SXTAH (int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UXTAB (unsigned int x, unsigned int y);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UXTAH (unsigned int x, unsigned int y);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned long long __iar_builtin_UMAAL(unsigned int x,
                                       unsigned int y,
                                       unsigned int a,
                                       unsigned int b);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind long long __iar_builtin_SMLALBB(unsigned int x,
                                 unsigned int y,
                                 long long acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind long long __iar_builtin_SMLALBT(unsigned int x,
                                 unsigned int y,
                                 long long acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind long long __iar_builtin_SMLALTB(unsigned int x,
                                 unsigned int y,
                                 long long acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind long long __iar_builtin_SMLALTT(unsigned int x,
                                 unsigned int y,
                                 long long acc);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UXTB16(unsigned int x);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UXTAB16(unsigned int acc, unsigned int x);

_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SXTB16(unsigned int x);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SXTAB16(unsigned int acc, unsigned int x);

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SASX(unsigned int, unsigned int) ;
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SSAX(unsigned int, unsigned int) ;
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SHASX(unsigned int, unsigned int) ;
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_SHSAX(unsigned int, unsigned int) ;
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_QASX(unsigned int, unsigned int) ;
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_QSAX(unsigned int, unsigned int) ;

_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UASX(unsigned int, unsigned int) ;
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_USAX(unsigned int, unsigned int) ;
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UHASX(unsigned int, unsigned int) ;
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UHSAX(unsigned int, unsigned int) ;
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UQASX(unsigned int, unsigned int) ;
_Pragma("function_effects = hidden_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_UQSAX(unsigned int, unsigned int) ;

/* Architecture v7 instructions */
__intrinsic __nounwind void __iar_builtin_DMB(void);
__intrinsic __nounwind void __iar_builtin_DSB(void);
__intrinsic __nounwind void __iar_builtin_ISB(void);
__intrinsic __nounwind void __iar_builtin_DMBx(unsigned int __constrange(1, 15)) ;
__intrinsic __nounwind void __iar_builtin_DSBx(unsigned int __constrange(1, 15)) ;
__intrinsic __nounwind void __iar_builtin_ISBx(unsigned int __constrange(1, 15)) ;

/* Architecture v8-M instructions */
__intrinsic __nounwind unsigned int __iar_builtin_TT(unsigned int);
__intrinsic __nounwind unsigned int __iar_builtin_TTT(unsigned int);
__intrinsic __nounwind unsigned int __iar_builtin_TTA(unsigned int);
__intrinsic __nounwind unsigned int __iar_builtin_TTAT(unsigned int);

__intrinsic __nounwind unsigned int __get_LR(void);
__intrinsic __nounwind void __set_LR(unsigned int);

__intrinsic __nounwind unsigned int __get_SP(void);
__intrinsic __nounwind void __set_SP(unsigned int);

/* VFP: sqrt */
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VSQRT_F32(float x);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VSQRT_F64(double x);

/* VFPv4: fused mac */
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VFMA_F32(float x, float y, float z);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VFMS_F32(float x, float y, float z);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VFNMA_F32(float x, float y, float z);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VFNMS_F32(float x, float y, float z);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VFMA_F64(double x, double y, double z);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VFMS_F64(double x, double y, double z);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VFNMA_F64(double x, double y, double z);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VFNMS_F64(double x, double y, double z);

/* Architecture v8-A/R: CRC extension */
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_CRC32B(unsigned int crc, unsigned char data);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_CRC32H(unsigned int crc, unsigned short data);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_CRC32W(unsigned int crc, unsigned int data);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_CRC32CB(unsigned int crc, unsigned char data);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_CRC32CH(unsigned int crc, unsigned short data);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind unsigned int __iar_builtin_CRC32CW(unsigned int crc, unsigned int data);

/* VFPv5: numerical min/max */
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VMAXNM_F32(float a, float b);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VMINNM_F32(float a, float b);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VMAXNM_F64(double a, double b);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VMINNM_F64(double a, double b);

/* VFPv5: rounding */
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VRINTA_F32(float a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VRINTM_F32(float a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VRINTN_F32(float a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VRINTP_F32(float a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VRINTX_F32(float a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VRINTR_F32(float a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind float __iar_builtin_VRINTZ_F32(float a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VRINTA_F64(double a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VRINTM_F64(double a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VRINTN_F64(double a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VRINTP_F64(double a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VRINTX_F64(double a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VRINTR_F64(double a);
_Pragma("function_effects = no_state, always_returns") __intrinsic __nounwind double __iar_builtin_VRINTZ_F64(double a);

#pragma language=restore




/**************************************************
*
* This file declares ARM intrinsic functions that are 
* common to IAR's intrinsics.h and arm_acle.h
*
* Copyright 2017-2018 IAR Systems. All rights reserved.
*
* $Revision: 124453 $
*
**************************************************/

  #pragma system_include

/* ACLE: Reads a system register */

/* ACLE: Writes a system register */

/* ACLE: Co-processor intrinsics */

/* ACLE:  Floating-point data-processing intrinsics */


/* ACLE: CRC32 extension */




  /* System control access for Cortex-M cores */




/* ARM-mode intrinsics */

/*  Co-processor operations */

/*  Co-processor access */

/* Load coprocessor register. */

/* Store coprocessor register. */

/* Load coprocessor register (noindexed version with coprocessor option). */

/* Store coprocessor register (version with coprocessor option). */

/* square root */

/* fused mac */

/* directed rounding.
 * NOTE: for example VRINTA becomes VCVTA when converted to int.
 */

/* numeric min/max */

/* CRC32 extension */

  /* Status register access, v7M: */

/* Floating-point status and control register access */

/* Architecture v5T, CLZ is also available in Thumb mode for Thumb2 cores */

/* Architecture v5TE */



/* Architecture v6, REV and REVSH are also available in thumb mode */









/* Architecture v7 instructions */

/* Architecture v8-M instructions */






/**
 * IO definitions
 *
 * define access restrictions to peripheral registers
 */


/* following defines should be used for structure members */
//#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
//#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
//#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */



/*******************************************************************************
 *                 Register Abstraction
 ******************************************************************************/


/* System Reset */




/* memory mapping struct for Nested Vectored Interrupt Controller (NVIC) */
typedef struct
{
  volatile uint32_t ISER[1];                      /*!< Interrupt Set Enable Register            */
       uint32_t RESERVED0[31];
  volatile uint32_t ICER[1];                      /*!< Interrupt Clear Enable Register          */
       uint32_t RSERVED1[31];
  volatile uint32_t ISPR[1];                      /*!< Interrupt Set Pending Register           */
       uint32_t RESERVED2[31];
  volatile uint32_t ICPR[1];                      /*!< Interrupt Clear Pending Register         */
       uint32_t RESERVED3[31];
       uint32_t RESERVED4[64];
  volatile uint32_t IP[8];                        /*!< Interrupt Priority Register              */
}  NVIC_Type;


/* memory mapping struct for System Control Block */
typedef struct
{
  volatile const  uint32_t CPUID;                        /*!< CPU ID Base Register                                     */
  volatile uint32_t ICSR;                         /*!< Interrupt Control State Register                         */
       uint32_t RESERVED0;
  volatile uint32_t AIRCR;                        /*!< Application Interrupt / Reset Control Register           */
  volatile uint32_t SCR;                          /*!< System Control Register                                  */
  volatile uint32_t CCR;                          /*!< Configuration Control Register                           */
       uint32_t RESERVED1;
  volatile uint32_t SHP[2];                       /*!< System Handlers Priority Registers. [0] is RESERVED      */
  volatile uint32_t SHCSR;                        /*!< System Handler Control and State Register                */
       uint32_t RESERVED2[2];
  volatile uint32_t DFSR;                         /*!< Debug Fault Status Register                              */
} SCB_Type;


/* memory mapping struct for SysTick */
typedef struct
{
  volatile uint32_t CTRL;                         /*!< SysTick Control and Status Register */
  volatile uint32_t LOAD;                         /*!< SysTick Reload Value Register       */
  volatile uint32_t VAL;                          /*!< SysTick Current Value Register      */
  volatile const  uint32_t CALIB;                        /*!< SysTick Calibration Register        */
} SysTick_Type;



/* Core Debug Register */
typedef struct
{
  volatile uint32_t DHCSR;                        /*!< Debug Halting Control and Status Register       */
  volatile  uint32_t DCRSR;                        /*!< Debug Core Register Selector Register           */
  volatile uint32_t DCRDR;                        /*!< Debug Core Register Data Register               */
  volatile uint32_t DEMCR;                        /*!< Debug Exception and Monitor Control Register    */
} CoreDebug_Type;


/* Memory mapping of Cortex-M0 Hardware */


/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */


/*******************************************************************************
 *                Hardware Abstraction Layer
 ******************************************************************************/





/* ###################  Compiler specific Intrinsics  ########################### */

/* IAR iccarm specific functions */


static inline void __enable_fault_irq()         { __asm volatile ("cpsie f"); }
static inline void __disable_fault_irq()        { __asm volatile ("cpsid f"); }

// Already defined in intrinsics.h
//static __INLINE  void __WFI()                     { __ASM ("wfi"); }
//static __INLINE  void __WFE()                     { __ASM ("wfe"); }
//static __INLINE  void __SEV()                     { __ASM ("sev"); }

//static __INLINE  void __ISB(arg)                  { __ASM ("isb"); }
//static __INLINE  void __DSB(arg)                  { __ASM ("dsb"); }
//static __INLINE  void __DMB(arg)                  { __ASM ("dmb"); }

/**
 * @brief  Return the Process Stack Pointer
 *
 * @param  none
 * @return uint32_t ProcessStackPointer
 *
 * Return the actual process stack pointer
 */
//JN extern uint32_t __get_PSP(void);

/**
 * @brief  Set the Process Stack Pointer
 *
 * @param  uint32_t Process Stack Pointer
 * @return none
 *
 * Assign the value ProcessStackPointer to the MSP
 * (process stack pointer) Cortex processor register
 */
//JN extern void __set_PSP(uint32_t topOfProcStack);

/**
 * @brief  Return the Main Stack Pointer
 *
 * @param  none
 * @return uint32_t Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */
//JN extern uint32_t __get_MSP(void);

/**
 * @brief  Set the Main Stack Pointer
 *
 * @param  uint32_t Main Stack Pointer
 * @return none
 *
 * Assign the value mainStackPointer to the MSP
 * (main stack pointer) Cortex processor register
 */
//JN extern void __set_MSP(uint32_t topOfMainStack);

/**
 * @brief  Reverse byte order in unsigned short value
 *
 * @param  uint16_t value to reverse
 * @return uint32_t reversed value
 *
 * Reverse byte order in unsigned short value
 */
//extern uint32_t __REV16(uint16_t value);



/* intrinsic void __set_PRIMASK();                                    */
/* intrinsic void __get_PRIMASK();                                    */
/* intrinsic uint32_t __REV(uint32_t value);                          */
/* intrinsic uint32_t __REVSH(uint32_t value);                        */





/* ##########################   NVIC functions  #################################### */

/* Interrupt Priorities are WORD accessible only under ARMv6M                   */
/* The following MACROS handle generation of the register offset and byte masks */




/**
 * @brief  Set the Priority Grouping in NVIC Interrupt Controller
 *
 * @param  uint32_t priority_grouping is priority grouping field
 * @return
 *
 * Set the priority grouping field using the required unlock sequence.
 * The parameter priority_grouping is assigned to the field
 * SCB->AIRCR [10:8] PRIGROUP field.
 */
static inline void NVIC_SetPriorityGrouping(uint32_t priority_grouping)
{
  uint32_t reg_value=0;

  reg_value  = ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR;                                                                            /* read old register configuration    */
  reg_value &= ~((0xFFFFU << 16) | (0x0F << 8));                                                      /* clear bits to change               */
  reg_value  = ((reg_value | (0x5FA << 16) | (priority_grouping << 8)));                         /* Insert write key and priorty group */
  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR = reg_value;
}

/**
 * @brief  Enable Interrupt in NVIC Interrupt Controller
 *
 * @param  IRQn_Type IRQn specifies the interrupt number
 * @return none
 *
 * Enable a device specific interupt in the NVIC interrupt controller.
 * The interrupt number cannot be a negative value.
 */
static inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));                             /* enable interrupt */
}

/**
 * @brief  Disable the interrupt line for external interrupt specified
 *
 * @param  IRQn_Type IRQn is the positive number of the external interrupt
 * @return  none
 *
 * Disable a device specific interupt in the NVIC interrupt controller.
 * The interrupt number cannot be a negative value.
 */
static inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));                             /* disable interrupt */
}

/**
 * @brief  Read the interrupt pending bit for a device specific interrupt source
 *
 * @param  IRQn_Type IRQn is the number of the device specifc interrupt
 * @return uint32_t
 *
 * Read the pending register in NVIC and return 1 if the specified
 * interrupt is pending, otherwise it returns zero.
 * The interrupt number cannot be a negative value.
 */
static inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));   /* Return 1 if pending else 0 */
}

/**
 * @brief  Set the pending bit for an external interrupt
 *
 * @param  IRQn_Type IRQn is the Number of the interrupt
 * @return  none
 *
 * Set the pending bit for the specified interrupt.
 * The interrupt number cannot be a negative value.
 */
static inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));                             /* set interrupt pending */
}

/**
 * @brief  Clear the pending bit for an external interrupt
 *
 * @param  IRQn_Type IRQn is the Number of the interrupt
 * @return  none
 *
 * Clear the pending bit for the specified interrupt.
 * The interrupt number cannot be a negative value.
 */
static inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));                             /* Clear pending interrupt */
}

/**
 * @brief  Set the priority for an interrupt
 *
 * @param  IRQn_Type IRQn is the Number of the interrupt
 * @param  priority is the priority for the interrupt
 * @return  none
 *
 * Set the priority for the specified interrupt. The interrupt
 * number can be positive to specify an external (device specific)
 * interrupt, or negative to specify an internal (core) interrupt. \n
 *
 * Note: The priority cannot be set for every core interrupt.
 */
static inline void NVIC_SetPriority(IRQn_Type IRQn, int32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[( ((((uint32_t)(IRQn) & 0x0F)-8) >> 2) )] = (((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[( ((((uint32_t)(IRQn) & 0x0F)-8) >> 2) )] & ~(0xFF << ( (((uint32_t)(IRQn) ) & 0x03) * 8 ))) |
        (((priority << (8 - 2)) & 0xFF) << ( (((uint32_t)(IRQn) ) & 0x03) * 8 )); }
  else {
    ((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[( ((uint32_t)(IRQn) >> 2) )] =  (((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[( ((uint32_t)(IRQn) >> 2) )]  & ~(0xFF << ( (((uint32_t)(IRQn) ) & 0x03) * 8 ))) |
        (((priority << (8 - 2)) & 0xFF) << ( (((uint32_t)(IRQn) ) & 0x03) * 8 )); }
}

/**
 * @brief  Read the priority for an interrupt
 *
 * @param  IRQn_Type IRQn is the Number of the interrupt
 * @return priority is the priority for the interrupt
 *
 * Read the priority for the specified interrupt. The interrupt
 * number can be positive to specify an external (device specific)
 * interrupt, or negative to specify an internal (core) interrupt.
 *
 * The returned priority value is automatically aligned to the implemented
 * priority bits of the microcontroller.
 *
 * Note: The priority cannot be set for every core interrupt.
 */
static inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)((((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[( ((((uint32_t)(IRQn) & 0x0F)-8) >> 2) )] >> ( (((uint32_t)(IRQn) ) & 0x03) * 8 ) ) >> (8 - 2)));  } /* get priority for Cortex-M0 system interrupts   */
  else {
    return((uint32_t)((((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[( ((uint32_t)(IRQn) >> 2) )]  >> ( (((uint32_t)(IRQn) ) & 0x03) * 8 ) ) >> (8 - 2)));  } /* get priority for device specific interrupts    */
}



/* ##################################    SysTick function  ############################################ */


/* SysTick constants */

/**
 * @brief  Initialize and start the SysTick counter and its interrupt.
 *
 * @param  uint32_t ticks is the number of ticks between two interrupts
 * @return  none
 *
 * Initialise the system tick timer and its interrupt and start the
 * system tick timer / counter in free running mode to generate
 * periodical interrupts.
 */
static inline uint32_t SysTick_Config(uint32_t ticks)
{
  uint32_t no_ref_clk;

  if (ticks > ((1<<24) -1)) return (1);                                                       /* Reload value impossible */
  if (ticks < 2)                return (1);                                                       /* Reload value impossible */

  ((SysTick_Type *) ((0xE000E000) + 0x0010))->LOAD  = (ticks & ((1<<24) -1)) - 1;                                                /* set reload register */
  NVIC_SetPriority (SysTick_IRQn, (1<<2) - 1);                                     /* set Priority for Cortex-M0 System Interrupts */
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->VAL   = (0x00);                                                                        /* Load the SysTick Counter Value */
  no_ref_clk     = (((SysTick_Type *) ((0xE000E000) + 0x0010))->CALIB >> 31);
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->CTRL  = (no_ref_clk<<2) | (1<<0) | (1<<1);  /* Enable SysTick IRQ and SysTick Timer */
  return (0);                                                                                     /* Function successful */
}




/* ##################################    Reset function  ############################################ */

/**
 * @brief  Initiate a system reset request.
 *
 * @param   none
 * @return  none
 *
 * Initialize a system reset request to reset the MCU
 */
static inline void NVIC_SystemReset(void)
{
  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR  = ((0x5FA << 16) | (1<<2));                               /* Keep priority group unchanged */
  __iar_builtin_DSBx(15);
  for (;;){};
}



//#include "system_m52417a.h"                         /*!< m52417a System                                                        */


/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */


/** @addtogroup Device_Peripheral_Registers
  * @{
  */


/* -------------------  Start of section using anonymous unions  ------------------ */


/* ================================================================================ */
/* ================                      WDOG                      ================ */
/* ================================================================================ */


/**
  * @brief Watchdog Module (WDOG)
  */

typedef struct {                                    /*!< WDOG Structure                                                        */
  
  union {
    volatile uint16_t  reg;                             /*!< CONTROL register                                                      */
    
    struct {
      volatile uint16_t  run_enable :  1;               /*!< run_enable bitfield                                                   */
      volatile  uint16_t  restart    :  1;               /*!< restart bitfield                                                      */
           uint16_t             :  6;
      volatile uint16_t  password   :  8;               /*!< password bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } CONTROL;
  
  union {
    volatile uint16_t  reg;                             /*!< WINDOW register                                                       */
    
    struct {
      volatile uint16_t  size       :  4;               /*!< size bitfield                                                         */
      volatile uint16_t  enable     :  1;               /*!< enable bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } WINDOW;
  
  union {
    volatile uint16_t  reg;                             /*!< PRESCALER register                                                    */
    
    struct {
      volatile uint16_t  val        :  8;               /*!< val bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } PRESCALER;
  
  union {
    volatile uint16_t  reg;                             /*!< RELOAD register                                                       */
    
    struct {
      volatile uint16_t  val        : 16;               /*!< val bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } RELOAD;
  
  union {
    volatile const  uint16_t  reg;                             /*!< COUNTER register                                                      */
    
    struct {
      volatile const  uint16_t  val        : 16;               /*!< val bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } COUNTER;
} WDOG_Type;


/* ================================================================================ */
/* ================                    SYS_STATE                   ================ */
/* ================================================================================ */


/**
  * @brief System State Module (SYS_STATE)
  */

typedef struct {                                    /*!< SYS_STATE Structure                                                   */
  
  union {
    volatile uint16_t  reg;                             /*!< CONTROL register                                                      */
    
    struct {
      volatile uint16_t  sys_clk_sel:  2;               /*!< sys_clk_sel bitfield                                                  */
    } bit;                                          /*!< BitSize                                                               */
  } CONTROL;
  volatile const  uint16_t  RESERVED;
  
  union {
    volatile const  uint16_t  reg;                             /*!< RESET_STATUS register                                                 */
    
    struct {
      volatile const  uint16_t  vcore_ok   :  1;               /*!< vcore_ok bitfield                                                     */
      volatile const  uint16_t  sys_clk_fail:  1;              /*!< sys_clk_fail bitfield                                                 */
      volatile const  uint16_t  cpu_lockup :  1;               /*!< cpu_lockup bitfield                                                   */
      volatile const  uint16_t  debug_reset:  1;               /*!< debug_reset bitfield                                                  */
      volatile const  uint16_t  software   :  1;               /*!< software bitfield                                                     */
      volatile const  uint16_t  sram_parity:  1;               /*!< sram_parity bitfield                                                  */
      volatile const  uint16_t  otp_ecc_fail:  1;              /*!< otp_ecc_fail bitfield                                                 */
      volatile const  uint16_t  watchdog_window:  1;           /*!< watchdog_window bitfield                                              */
      volatile const  uint16_t  watchdog   :  1;               /*!< watchdog bitfield                                                     */
      volatile const  uint16_t  watchdog_zero:  1;             /*!< watchdog_zero bitfield                                                */
      volatile const  uint16_t  crc16_mismatch:  1;            /*!< crc16_mismatch bitfield                                               */
      volatile const  uint16_t  trim_parity:  1;               /*!< trim_parity bitfield                                                  */
    } bit;                                          /*!< BitSize                                                               */
  } RESET_STATUS;
  
  union {
    volatile  uint16_t  reg;                             /*!< RESET_STATUS_CLEAR register                                           */
    
    struct {
      volatile  uint16_t  clear      : 12;               /*!< clear bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } RESET_STATUS_CLEAR;
  
  union {
    volatile uint16_t  reg;                             /*!< RESET_ENABLE register                                                 */
    
    struct {
      volatile uint16_t  cpu_lockup :  1;               /*!< cpu_lockup bitfield                                                   */
      volatile uint16_t  debug_reset:  1;               /*!< debug_reset bitfield                                                  */
      volatile uint16_t  software   :  1;               /*!< software bitfield                                                     */
      volatile uint16_t  sram_parity:  1;               /*!< sram_parity bitfield                                                  */
      volatile uint16_t  otp_ecc_fail:  1;              /*!< otp_ecc_fail bitfield                                                 */
      volatile uint16_t  watchdog_window:  1;           /*!< watchdog_window bitfield                                              */
      volatile uint16_t  watchdog   :  1;               /*!< watchdog bitfield                                                     */
      volatile uint16_t  watchdog_zero:  1;             /*!< watchdog_zero bitfield                                                */
      volatile uint16_t  crc16_mismatch:  1;            /*!< crc16_mismatch bitfield                                               */
      volatile uint16_t  trim_parity:  1;               /*!< trim_parity bitfield                                                  */
    } bit;                                          /*!< BitSize                                                               */
  } RESET_ENABLE;
  
  union {
    volatile uint16_t  reg;                             /*!< SW_RESET register                                                     */
    
    struct {
      volatile const  uint16_t  por_flag   :  1;               /*!< por_flag bitfield                                                     */
      volatile const  uint16_t  sw_reset_flag:  3;             /*!< sw_reset_flag bitfield                                                */
      volatile  uint16_t  sw_reset   :  1;               /*!< sw_reset bitfield                                                     */
      volatile  uint16_t  set_sw_reset_flag:  3;         /*!< set_sw_reset_flag bitfield                                            */
    } bit;                                          /*!< BitSize                                                               */
  } SW_RESET;
  
  union {
    volatile  uint16_t  reg;                             /*!< SW_RESET_FLAG_CLEAR register                                          */
    
    struct {
           uint16_t             :  1;
      volatile  uint16_t  clear      :  3;               /*!< clear bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } SW_RESET_FLAG_CLEAR;
  
  union {
    volatile uint16_t  reg;                             /*!< ENABLE_DEBUG register                                                 */
    
    struct {
      volatile uint16_t  enable     :  1;               /*!< enable bitfield                                                       */
      volatile const  uint16_t  exit_boot_loader:  1;          /*!< exit_boot_loader bitfield                                             */
      volatile const  uint16_t  signature_boot:  1;            /*!< signature_boot bitfield                                               */
      volatile const  uint16_t  signature_new:  1;             /*!< signature_new bitfield                                                */
      volatile uint16_t  pass       : 12;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } ENABLE_DEBUG;
  
  union {
    volatile uint16_t  reg;                             /*!< WDOG_CLK_FREQ register                                                */
    
    struct {
      volatile uint16_t  freq       : 10;               /*!< freq bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } WDOG_CLK_FREQ;
  
  union {
    volatile const  uint16_t  reg;                             /*!< SYS_CLK_MEAS register                                                 */
    
    struct {
      volatile const  uint16_t  cycles     : 11;               /*!< cycles bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } SYS_CLK_MEAS;
  volatile const  uint32_t  RESERVED1;
  
  union {
    volatile uint16_t  reg;                             /*!< SYS_OSC_TRIM register                                                 */
    
    struct {
      volatile uint16_t  val        :  8;               /*!< val bitfield                                                          */
      volatile uint16_t  lock       :  1;               /*!< lock bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } SYS_OSC_TRIM;
  volatile const  uint16_t  RESERVED2[3];
  
  union {
    volatile uint16_t  reg;                             /*!< VECTOR_TABLE_REMAP register                                           */
    
    struct {
      volatile uint16_t  val        :  2;               /*!< val bitfield                                                          */
      volatile uint16_t  sel        :  1;               /*!< sel bitfield                                                          */
      volatile uint16_t  lock       :  1;               /*!< lock bitfield                                                         */
      volatile const  uint16_t  state      :  2;               /*!< state bitfield                                                        */
      volatile uint16_t  lock_table_base:  1;           /*!< lock_table_base bitfield                                              */
           uint16_t             :  1;
      volatile uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } VECTOR_TABLE_REMAP;
  volatile const  uint16_t  RESERVED3;
  
  union {
    volatile uint16_t  reg;                             /*!< VECTOR_TABLE_BASE0 register                                           */
    
    struct {
      volatile uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } VECTOR_TABLE_BASE0;
  
  union {
    volatile uint16_t  reg;                             /*!< VECTOR_TABLE_BASE1 register                                           */
    
    struct {
      volatile uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } VECTOR_TABLE_BASE1;
  
  union {
    volatile uint16_t  reg;                             /*!< TEST_MASTER_DATA_L register                                           */
    
    struct {
      volatile uint16_t  data       : 16;               /*!< data bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_MASTER_DATA_L;
  
  union {
    volatile uint16_t  reg;                             /*!< TEST_MASTER_DATA_H register                                           */
    
    struct {
      volatile uint16_t  data       : 16;               /*!< data bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_MASTER_DATA_H;
  
  union {
    volatile  uint16_t  reg;                             /*!< TEST_MASTER_ADDR register                                             */
    
    struct {
      volatile  uint16_t  addr       : 12;               /*!< addr bitfield                                                         */
      volatile  uint16_t  write      :  1;               /*!< write bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_MASTER_ADDR;
  
  union {
    volatile const  uint16_t  reg;                             /*!< TEST_SIGNATURE register                                               */
    
    struct {
      volatile const  uint16_t  data       : 16;               /*!< data bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_SIGNATURE;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_STATUS register                                                   */
    
    struct {
      volatile uint16_t  cpu_lockup :  1;               /*!< cpu_lockup bitfield                                                   */
      volatile uint16_t  debug_reset:  1;               /*!< debug_reset bitfield                                                  */
      volatile uint16_t  software   :  1;               /*!< software bitfield                                                     */
      volatile uint16_t  sram_parity:  1;               /*!< sram_parity bitfield                                                  */
      volatile uint16_t  otp_ecc_fail:  1;              /*!< otp_ecc_fail bitfield                                                 */
      volatile uint16_t  watchdog_window:  1;           /*!< watchdog_window bitfield                                              */
      volatile uint16_t  watchdog   :  1;               /*!< watchdog bitfield                                                     */
      volatile uint16_t  watchdog_zero:  1;             /*!< watchdog_zero bitfield                                                */
      volatile uint16_t  crc16_mismatch:  1;            /*!< crc16_mismatch bitfield                                               */
      volatile uint16_t  trim_parity:  1;               /*!< trim_parity bitfield                                                  */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_STATUS;
  volatile const  uint16_t  RESERVED4;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_MASK register                                                     */
    
    struct {
      volatile uint16_t  mask       : 10;               /*!< mask bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_MASK;
  volatile const  uint16_t  RESERVED5;
  
  union {
    volatile  uint16_t  reg;                             /*!< IRQ_VENABLE register                                                  */
    
    struct {
      volatile  uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VENABLE;
  
  union {
    volatile  uint16_t  reg;                             /*!< IRQ_VDISABLE register                                                 */
    
    struct {
      volatile  uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VDISABLE;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_VMAX register                                                     */
    
    struct {
      volatile uint16_t  vmax       :  4;               /*!< vmax bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VMAX;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_VNO register                                                      */
    
    struct {
      volatile uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VNO;
} SYS_STATE_Type;


/* ================================================================================ */
/* ================                      CRC16                     ================ */
/* ================================================================================ */


/**
  * @brief CCITT-CRC-16 Module (CRC16)
  */

typedef struct {                                    /*!< CRC16 Structure                                                       */
  
  union {
    volatile uint16_t  reg;                             /*!< START0 register                                                       */
    
    struct {
      volatile uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } START0;
  
  union {
    volatile uint16_t  reg;                             /*!< START1 register                                                       */
    
    struct {
      volatile uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } START1;
  
  union {
    volatile uint16_t  reg;                             /*!< LENGTH0 register                                                      */
    
    struct {
      volatile uint16_t  bytes      : 16;               /*!< bytes bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } LENGTH0;
  
  union {
    volatile uint16_t  reg;                             /*!< LENGTH1 register                                                      */
    
    struct {
      volatile uint16_t  bytes      : 16;               /*!< bytes bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } LENGTH1;
  
  union {
    volatile uint16_t  reg;                             /*!< EXPECTED_CRC register                                                 */
    
    struct {
      volatile uint16_t  crc        : 16;               /*!< crc bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } EXPECTED_CRC;
  
  union {
    volatile uint16_t  reg;                             /*!< CONFIG register                                                       */
    
    struct {
      volatile uint16_t  timing     :  3;               /*!< timing bitfield                                                       */
      volatile uint16_t  keep_sum   :  1;               /*!< keep_sum bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } CONFIG;
  
  union {
    volatile const  uint16_t  reg;                             /*!< STATUS register                                                       */
    
    struct {
      volatile const  uint16_t  state      :  2;               /*!< state bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } STATUS;
  
  union {
    volatile uint16_t  reg;                             /*!< CRC_SUM register                                                      */
    
    struct {
      volatile uint16_t  crc        : 16;               /*!< crc bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } CRC_SUM;
} CRC16_Type;


/* ================================================================================ */
/* ================                    OTP0_CTRL                   ================ */
/* ================================================================================ */


/**
  * @brief OTP0 Control Module (OTP0_CTRL)
  */

typedef struct {                                    /*!< OTP0_CTRL Structure                                                   */
  
  union {
    volatile uint16_t  reg;                             /*!< READ_CONFIG register                                                  */
    
    struct {
      volatile uint16_t  differential:  1;              /*!< differential bitfield                                                 */
      volatile uint16_t  redundant  :  1;               /*!< redundant bitfield                                                    */
      volatile uint16_t  trp_config :  2;               /*!< trp_config bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } READ_CONFIG;
  
  union {
    volatile uint16_t  reg;                             /*!< PROG_CONFIG register                                                  */
    
    struct {
      volatile uint16_t  max_soak   :  4;               /*!< max_soak bitfield                                                     */
      volatile uint16_t  trp_config :  3;               /*!< trp_config bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } PROG_CONFIG;
  volatile const  uint16_t  RESERVED;
  
  union {
    volatile uint16_t  reg;                             /*!< PROG_CONTROL register                                                 */
    
    struct {
      volatile uint16_t  otp_prog   :  1;               /*!< otp_prog bitfield                                                     */
      volatile uint16_t  differential:  1;              /*!< differential bitfield                                                 */
           uint16_t             :  6;
      volatile uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } PROG_CONTROL;
  
  union {
    volatile uint16_t  reg;                             /*!< WDATA0 register                                                       */
    
    struct {
      volatile uint16_t  data       : 16;               /*!< data bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } WDATA0;
  
  union {
    volatile uint16_t  reg;                             /*!< WDATA1 register                                                       */
    
    struct {
      volatile uint16_t  data       : 16;               /*!< data bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } WDATA1;
  volatile const  uint32_t  RESERVED1;
  
  union {
    volatile uint16_t  reg;                             /*!< WADDR register                                                        */
    
    struct {
      volatile uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } WADDR;
  volatile const  uint16_t  RESERVED2;
  
  union {
    volatile const  uint16_t  reg;                             /*!< PROG_STATUS register                                                  */
    
    struct {
      volatile const  uint16_t  last_soak  :  4;               /*!< last_soak bitfield                                                    */
      volatile const  uint16_t  busy       :  1;               /*!< busy bitfield                                                         */
      volatile const  uint16_t  fail0      :  1;               /*!< fail0 bitfield                                                        */
      volatile const  uint16_t  fail1      :  1;               /*!< fail1 bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } PROG_STATUS;
  
  union {
    volatile const  uint16_t  reg;                             /*!< BIT_SOAK_STATUS register                                              */
    
    struct {
      volatile const  uint16_t  take       :  1;               /*!< take bitfield                                                         */
      volatile const  uint16_t  soak_bit   :  6;               /*!< soak_bit bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } BIT_SOAK_STATUS;
  
  union {
    volatile uint16_t  reg;                             /*!< PROTECT register                                                      */
    
    struct {
      volatile uint16_t  protect    :  8;               /*!< protect bitfield                                                      */
      volatile uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } PROTECT;
  
  union {
    volatile uint16_t  reg;                             /*!< BOOT_PROTECT register                                                 */
    
    struct {
      volatile uint16_t  protect    :  3;               /*!< protect bitfield                                                      */
           uint16_t             :  5;
      volatile uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } BOOT_PROTECT;
  
  union {
    volatile uint16_t  reg;                             /*!< IO_FLAG register                                                      */
    
    struct {
      volatile uint16_t  flag       :  1;               /*!< flag bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IO_FLAG;
  volatile const  uint16_t  RESERVED3;
  
  union {
    volatile  uint16_t  reg;                             /*!< TEST_LOCK register                                                    */
    
    struct {
      volatile  uint16_t  lock       :  1;               /*!< lock bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_LOCK;
  
  union {
    volatile uint16_t  reg;                             /*!< TEST_TRP_CONFIG register                                              */
    
    struct {
      volatile uint16_t  val        :  8;               /*!< val bitfield                                                          */
      volatile uint16_t  sel        :  1;               /*!< sel bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_TRP_CONFIG;
  
  union {
    volatile uint16_t  reg;                             /*!< TEST_MR register                                                      */
    
    struct {
      volatile uint16_t  val        :  8;               /*!< val bitfield                                                          */
      volatile uint16_t  read_sel   :  1;               /*!< read_sel bitfield                                                     */
      volatile uint16_t  prog_sel   :  1;               /*!< prog_sel bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_MR;
  
  union {
    volatile uint16_t  reg;                             /*!< TEST_FORCE register                                                   */
    
    struct {
      volatile uint16_t  force      :  1;               /*!< force bitfield                                                        */
      volatile uint16_t  ck         :  1;               /*!< ck bitfield                                                           */
      volatile uint16_t  sel        :  1;               /*!< sel bitfield                                                          */
      volatile uint16_t  we         :  1;               /*!< we bitfield                                                           */
      volatile uint16_t  oe         :  1;               /*!< oe bitfield                                                           */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_FORCE;
  
  union {
    volatile uint16_t  reg;                             /*!< MPP register                                                          */
    
    struct {
      volatile uint16_t  mpp        :  4;               /*!< mpp bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } MPP;
  
  union {
    volatile uint16_t  reg;                             /*!< MRR register                                                          */
    
    struct {
      volatile uint16_t  mrr        : 16;               /*!< mrr bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } MRR;
  
  union {
    volatile uint16_t  reg;                             /*!< VRR register                                                          */
    
    struct {
      volatile uint16_t  vrr1       :  4;               /*!< vrr1 bitfield                                                         */
      volatile uint16_t  vrr2       :  4;               /*!< vrr2 bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } VRR;
  
  union {
    volatile uint16_t  reg;                             /*!< ERASE register                                                        */
    
    struct {
      volatile  uint16_t  start      :  1;               /*!< start bitfield                                                        */
      volatile const  uint16_t  ready      :  1;               /*!< ready bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ERASE;
  
  union {
    volatile uint16_t  reg;                             /*!< TEST_CELL_STRESS register                                             */
    
    struct {
      volatile uint16_t  stress     :  1;               /*!< stress bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_CELL_STRESS;
  
  union {
    volatile uint16_t  reg;                             /*!< TEST_SEL_VAL register                                                 */
    
    struct {
      volatile uint16_t  vpp_e_sel  :  1;               /*!< vpp_e_sel bitfield                                                    */
      volatile uint16_t  vpp_e_val  :  1;               /*!< vpp_e_val bitfield                                                    */
      volatile uint16_t  vrr_e_sel  :  1;               /*!< vrr_e_sel bitfield                                                    */
      volatile uint16_t  vrr_e_val  :  1;               /*!< vrr_e_val bitfield                                                    */
      volatile uint16_t  ehv_e_sel  :  1;               /*!< ehv_e_sel bitfield                                                    */
      volatile uint16_t  ehv_e_val  :  1;               /*!< ehv_e_val bitfield                                                    */
      volatile uint16_t  dben_sel   :  1;               /*!< dben_sel bitfield                                                     */
      volatile uint16_t  dben_val   :  1;               /*!< dben_val bitfield                                                     */
      volatile uint16_t  mask_ips_clks:  1;             /*!< mask_ips_clks bitfield                                                */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_SEL_VAL;
  
  union {
    volatile uint16_t  reg;                             /*!< TEST_ECC register                                                     */
    
    struct {
      volatile const  uint16_t  ecc_sum    : 12;               /*!< ecc_sum bitfield                                                      */
      volatile const  uint16_t  ecc_1bit   :  1;               /*!< ecc_1bit bitfield                                                     */
      volatile const  uint16_t  ecc_2bit   :  1;               /*!< ecc_2bit bitfield                                                     */
      volatile uint16_t  disable_read_ecc:  1;          /*!< disable_read_ecc bitfield                                             */
      volatile uint16_t  force_ecc_write_1:  1;         /*!< force_ecc_write_1 bitfield                                            */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_ECC;
  
  union {
    volatile uint16_t  reg;                             /*!< MDB register                                                          */
    
    struct {
      volatile uint16_t  mdb        :  4;               /*!< mdb bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } MDB;
} OTP0_CTRL_Type;


/* ================================================================================ */
/* ================                   EEPROM_CTRL                  ================ */
/* ================================================================================ */


/**
  * @brief EEPROM Control Module (EEPROM_CTRL)
  */

typedef struct {                                    /*!< EEPROM_CTRL Structure                                                 */
  
  union {
    volatile uint16_t  reg;                             /*!< MODE register                                                         */
    
    struct {
      volatile uint16_t  erase      :  1;               /*!< erase bitfield                                                        */
      volatile uint16_t  program    :  1;               /*!< program bitfield                                                      */
      volatile uint16_t  margin_read:  1;               /*!< margin_read bitfield                                                  */
           uint16_t             :  5;
      volatile uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } MODE;
  
  union {
    volatile const  uint16_t  reg;                             /*!< STATUS register                                                       */
    
    struct {
      volatile const  uint16_t  busy       :  1;               /*!< busy bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } STATUS;
  
  union {
    volatile uint16_t  reg;                             /*!< LOCK_L register                                                       */
    
    struct {
      volatile uint16_t  lock       :  8;               /*!< lock bitfield                                                         */
      volatile uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } LOCK_L;
  
  union {
    volatile uint16_t  reg;                             /*!< LOCK_U register                                                       */
    
    struct {
      volatile uint16_t  lock       :  8;               /*!< lock bitfield                                                         */
      volatile uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } LOCK_U;
  volatile const  uint16_t  RESERVED;
  
  union {
    volatile uint16_t  reg;                             /*!< LOCK_CNT register                                                     */
    
    struct {
      volatile uint16_t  lock_counter:  4;              /*!< lock_counter bitfield                                                 */
           uint16_t             :  4;
      volatile uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } LOCK_CNT;
  
  union {
    volatile uint16_t  reg;                             /*!< LOCK_L_FREEZE register                                                */
    
    struct {
      volatile uint16_t  freeze     :  8;               /*!< freeze bitfield                                                       */
      volatile uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } LOCK_L_FREEZE;
  
  union {
    volatile uint16_t  reg;                             /*!< LOCK_U_FREEZE register                                                */
    
    struct {
      volatile uint16_t  freeze     :  8;               /*!< freeze bitfield                                                       */
      volatile uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } LOCK_U_FREEZE;
  
  union {
    volatile uint16_t  reg;                             /*!< IP_ENABLE register                                                    */
    
    struct {
      volatile uint16_t  enable     :  1;               /*!< enable bitfield                                                       */
           uint16_t             :  7;
      volatile uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IP_ENABLE;
  
  union {
    volatile uint16_t  reg;                             /*!< MARGIN_TRIM register                                                  */
    
    struct {
      volatile uint16_t  trim       :  3;               /*!< trim bitfield                                                         */
           uint16_t             :  5;
      volatile uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } MARGIN_TRIM;
  
  union {
    volatile const  uint16_t  reg;                             /*!< TIMEOUT_L register                                                    */
    
    struct {
      volatile const  uint16_t  val        : 16;               /*!< val bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } TIMEOUT_L;
  
  union {
    volatile const  uint16_t  reg;                             /*!< TIMEOUT_H register                                                    */
    
    struct {
      volatile const  uint16_t  val        :  2;               /*!< val bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } TIMEOUT_H;
  volatile const  uint32_t  RESERVED1[6];
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_STATUS register                                                   */
    
    struct {
      volatile uint16_t  timeout    :  1;               /*!< timeout bitfield                                                      */
      volatile uint16_t  invalid_addr:  1;              /*!< invalid_addr bitfield                                                 */
      volatile uint16_t  ip_off_access:  1;             /*!< ip_off_access bitfield                                                */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_STATUS;
  volatile const  uint16_t  RESERVED2;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_MASK register                                                     */
    
    struct {
      volatile uint16_t  mask       :  3;               /*!< mask bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_MASK;
  volatile const  uint16_t  RESERVED3;
  
  union {
    volatile  uint16_t  reg;                             /*!< IRQ_VENABLE register                                                  */
    
    struct {
      volatile  uint16_t  vno        :  2;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VENABLE;
  
  union {
    volatile  uint16_t  reg;                             /*!< IRQ_VDISABLE register                                                 */
    
    struct {
      volatile  uint16_t  vno        :  2;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VDISABLE;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_VMAX register                                                     */
    
    struct {
      volatile uint16_t  vmax       :  2;               /*!< vmax bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VMAX;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_VNO register                                                      */
    
    struct {
      volatile uint16_t  vno        :  2;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VNO;
} EEPROM_CTRL_Type;


/* ================================================================================ */
/* ================                      GPIO                      ================ */
/* ================================================================================ */


/**
  * @brief GPIO Module (GPIO)
  */

typedef struct {                                    /*!< GPIO Structure                                                        */
  
  union {
    volatile uint16_t  reg;                             /*!< DATA_OUT register                                                     */
    
    struct {
      volatile uint16_t  data       :  4;               /*!< data bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } DATA_OUT;
  
  union {
    volatile uint16_t  reg;                             /*!< DATA_OE register                                                      */
    
    struct {
      volatile uint16_t  enable     :  4;               /*!< enable bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } DATA_OE;
  
  union {
    volatile const  uint16_t  reg;                             /*!< DATA_IN register                                                      */
    
    struct {
      volatile const  uint16_t  data       :  4;               /*!< data bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } DATA_IN;
  
  union {
    volatile uint16_t  reg;                             /*!< DATA_IE register                                                      */
    
    struct {
      volatile uint16_t  enable     :  4;               /*!< enable bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } DATA_IE;
  
  union {
    volatile uint16_t  reg;                             /*!< DATA_PUE register                                                     */
    
    struct {
      volatile uint16_t  enable     :  4;               /*!< enable bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } DATA_PUE;
  
  union {
    volatile uint16_t  reg;                             /*!< IOMUX register                                                        */
    
    struct {
      volatile uint16_t  mux        :  2;               /*!< mux bitfield                                                          */
      volatile uint16_t  uart_port  :  1;               /*!< uart_port bitfield                                                    */
    } bit;                                          /*!< BitSize                                                               */
  } IOMUX;
  volatile const  uint32_t  RESERVED[9];
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_STATUS register                                                   */
    
    struct {
      volatile uint16_t  evt_pos_0  :  1;               /*!< evt_pos_0 bitfield                                                    */
      volatile uint16_t  evt_neg_0  :  1;               /*!< evt_neg_0 bitfield                                                    */
      volatile uint16_t  evt_pos_1  :  1;               /*!< evt_pos_1 bitfield                                                    */
      volatile uint16_t  evt_neg_1  :  1;               /*!< evt_neg_1 bitfield                                                    */
      volatile uint16_t  evt_pos_2  :  1;               /*!< evt_pos_2 bitfield                                                    */
      volatile uint16_t  evt_neg_2  :  1;               /*!< evt_neg_2 bitfield                                                    */
      volatile uint16_t  evt_pos_3  :  1;               /*!< evt_pos_3 bitfield                                                    */
      volatile uint16_t  evt_neg_3  :  1;               /*!< evt_neg_3 bitfield                                                    */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_STATUS;
  volatile const  uint16_t  RESERVED1;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_MASK register                                                     */
    
    struct {
      volatile uint16_t  mask       :  8;               /*!< mask bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_MASK;
  volatile const  uint16_t  RESERVED2;
  
  union {
    volatile  uint16_t  reg;                             /*!< IRQ_VENABLE register                                                  */
    
    struct {
      volatile  uint16_t  vno        :  3;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VENABLE;
  
  union {
    volatile  uint16_t  reg;                             /*!< IRQ_VDISABLE register                                                 */
    
    struct {
      volatile  uint16_t  vno        :  3;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VDISABLE;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_VMAX register                                                     */
    
    struct {
      volatile uint16_t  vmax       :  4;               /*!< vmax bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VMAX;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_VNO register                                                      */
    
    struct {
      volatile uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VNO;
} GPIO_Type;


/* ================================================================================ */
/* ================                     SWTIMER                    ================ */
/* ================================================================================ */


/**
  * @brief TIMER Module (SWTIMER)
  */

typedef struct {                                    /*!< SWTIMER Structure                                                     */
  
  union {
    volatile uint16_t  reg;                             /*!< CONFIG register                                                       */
    
    struct {
      volatile uint16_t  enables    :  2;               /*!< enables bitfield                                                      */
      volatile uint16_t  cnt_auto_reloads:  2;          /*!< cnt_auto_reloads bitfield                                             */
      volatile uint16_t  ext_strb_src:  2;              /*!< ext_strb_src bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } CONFIG;
  
  union {
    volatile  uint16_t  reg;                             /*!< COMMAND register                                                      */
    
    struct {
      volatile  uint16_t  cnt_reload_cmd:  2;            /*!< cnt_reload_cmd bitfield                                               */
      volatile  uint16_t  div_reload_cmd:  2;            /*!< div_reload_cmd bitfield                                               */
    } bit;                                          /*!< BitSize                                                               */
  } COMMAND;
  
  union {
    volatile uint16_t  reg;                             /*!< CNT0_RELOAD register                                                  */
    
    struct {
      volatile uint16_t  cnt_reload : 16;               /*!< cnt_reload bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } CNT0_RELOAD;
  
  union {
    volatile uint16_t  reg;                             /*!< CNT1_RELOAD register                                                  */
    
    struct {
      volatile uint16_t  cnt_reload : 16;               /*!< cnt_reload bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } CNT1_RELOAD;
  
  union {
    volatile uint16_t  reg;                             /*!< DIV0_RELOAD register                                                  */
    
    struct {
      volatile uint16_t  div_reload :  8;               /*!< div_reload bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } DIV0_RELOAD;
  
  union {
    volatile uint16_t  reg;                             /*!< DIV1_RELOAD register                                                  */
    
    struct {
      volatile uint16_t  div_reload :  8;               /*!< div_reload bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } DIV1_RELOAD;
  
  union {
    volatile const  uint16_t  reg;                             /*!< CNT0_VALUE register                                                   */
    
    struct {
      volatile const  uint16_t  cnt_val    : 16;               /*!< cnt_val bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } CNT0_VALUE;
  
  union {
    volatile const  uint16_t  reg;                             /*!< CNT1_VALUE register                                                   */
    
    struct {
      volatile const  uint16_t  cnt_val    : 16;               /*!< cnt_val bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } CNT1_VALUE;
  volatile const  uint32_t  RESERVED[8];
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_STATUS register                                                   */
    
    struct {
      volatile uint16_t  evt_cnt_zero:  2;              /*!< evt_cnt_zero bitfield                                                 */
      volatile uint16_t  evt_div_zero:  2;              /*!< evt_div_zero bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_STATUS;
  volatile const  uint16_t  RESERVED1;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_MASK register                                                     */
    
    struct {
      volatile uint16_t  mask       :  4;               /*!< mask bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_MASK;
  volatile const  uint16_t  RESERVED2;
  
  union {
    volatile  uint16_t  reg;                             /*!< IRQ_VENABLE register                                                  */
    
    struct {
      volatile  uint16_t  vno        :  2;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VENABLE;
  
  union {
    volatile  uint16_t  reg;                             /*!< IRQ_VDISABLE register                                                 */
    
    struct {
      volatile  uint16_t  vno        :  2;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VDISABLE;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_VMAX register                                                     */
    
    struct {
      volatile uint16_t  vmax       :  3;               /*!< vmax bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VMAX;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_VNO register                                                      */
    
    struct {
      volatile uint16_t  vno        :  3;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VNO;
} SWTIMER_Type;


/* ================================================================================ */
/* ================                      DSI3                      ================ */
/* ================================================================================ */


/**
  * @brief DSI3 Module (DSI3)
  */

typedef struct {                                    /*!< DSI3 Structure                                                        */
  
  union {
    volatile uint16_t  reg;                             /*!< ANALOG_CTRL register                                                  */
    
    struct {
      volatile uint16_t  dsi3_enable:  1;               /*!< dsi3_enable bitfield                                                  */
      volatile uint16_t  rcc_enable :  1;               /*!< rcc_enable bitfield                                                   */
      volatile uint16_t  rcc_lcm    :  1;               /*!< rcc_lcm bitfield                                                      */
      volatile uint16_t  fcc_hyst_sel:  1;              /*!< fcc_hyst_sel bitfield                                                 */
      volatile uint16_t  fcc_force_connect:  1;         /*!< fcc_force_connect bitfield                                            */
      volatile uint16_t  fcc_force_bypass:  1;          /*!< fcc_force_bypass bitfield                                             */
    } bit;                                          /*!< BitSize                                                               */
  } ANALOG_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< CONFIG register                                                       */
    
    struct {
      volatile uint16_t  crc_check  :  1;               /*!< crc_check bitfield                                                    */
      volatile uint16_t  crc_add    :  1;               /*!< crc_add bitfield                                                      */
      volatile uint16_t  auto_resp  :  1;               /*!< auto_resp bitfield                                                    */
      volatile uint16_t  auto_timer :  1;               /*!< auto_timer bitfield                                                   */
      volatile uint16_t  auto_sync  :  1;               /*!< auto_sync bitfield                                                    */
      volatile uint16_t  disable_sync_vali:  1;         /*!< disable_sync_vali bitfield                                            */
      volatile uint16_t  t_chip     :  2;               /*!< t_chip bitfield                                                       */
      volatile uint16_t  auto_blank_off:  1;            /*!< auto_blank_off bitfield                                               */
      volatile uint16_t  auto_blank_on:  1;             /*!< auto_blank_on bitfield                                                */
      volatile uint16_t  pdcm_seed_sel:  1;             /*!< pdcm_seed_sel bitfield                                                */
      volatile uint16_t  timer_start_sel:  1;           /*!< timer_start_sel bitfield                                              */
      volatile uint16_t  debounce   :  3;               /*!< debounce bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } CONFIG;
  
  union {
    volatile  uint16_t  reg;                             /*!< CTRL register                                                         */
    
    struct {
      volatile  uint16_t  abort_fcc  :  1;               /*!< abort_fcc bitfield                                                    */
      volatile  uint16_t  abort_rcc  :  1;               /*!< abort_rcc bitfield                                                    */
      volatile  uint16_t  start_rcc  :  1;               /*!< start_rcc bitfield                                                    */
      volatile  uint16_t  clr_fcc_low_flag:  1;          /*!< clr_fcc_low_flag bitfield                                             */
      volatile  uint16_t  start_timer:  1;               /*!< start_timer bitfield                                                  */
      volatile  uint16_t  reset_timer:  1;               /*!< reset_timer bitfield                                                  */
      volatile  uint16_t  set_blanking_off:  1;          /*!< set_blanking_off bitfield                                             */
      volatile  uint16_t  set_blanking_on:  1;           /*!< set_blanking_on bitfield                                              */
      volatile  uint16_t  set_mode   :  2;               /*!< set_mode bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } CTRL;
  
  union {
    volatile const  uint16_t  reg;                             /*!< STATUS register                                                       */
    
    struct {
      volatile const  uint16_t  mode       :  2;               /*!< mode bitfield                                                         */
      volatile const  uint16_t  fcc_idle   :  1;               /*!< fcc_idle bitfield                                                     */
      volatile const  uint16_t  fcc_signal :  1;               /*!< fcc_signal bitfield                                                   */
      volatile const  uint16_t  fcc_low_flag:  1;              /*!< fcc_low_flag bitfield                                                 */
      volatile const  uint16_t  fcc_blanking:  1;              /*!< fcc_blanking bitfield                                                 */
      volatile const  uint16_t  timer_status:  1;              /*!< timer_status bitfield                                                 */
      volatile const  uint16_t  sync_cnt_err:  1;              /*!< sync_cnt_err bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } STATUS;
  
  union {
    volatile uint16_t  reg;                             /*!< DISCOVERY_CTRL register                                               */
    
    struct {
      volatile uint16_t  disc_ramp_on:  1;              /*!< disc_ramp_on bitfield                                                 */
      volatile const  uint16_t  curr_cmp_out:  1;              /*!< curr_cmp_out bitfield                                                 */
      volatile const  uint16_t  curr_cmp_cap:  1;              /*!< curr_cmp_cap bitfield                                                 */
           uint16_t             :  1;
      volatile uint16_t  auto_disc_resp:  1;            /*!< auto_disc_resp bitfield                                               */
      volatile uint16_t  auto_disc_accept:  1;          /*!< auto_disc_accept bitfield                                             */
           uint16_t             :  2;
      volatile uint16_t  debounce   :  3;               /*!< debounce bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } DISCOVERY_CTRL;
  volatile const  uint16_t  RESERVED;
  
  union {
    volatile uint16_t  reg;                             /*!< CLK_1US register                                                      */
    
    struct {
      volatile uint16_t  frac       :  5;               /*!< frac bitfield                                                         */
      volatile uint16_t  div        :  5;               /*!< div bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } CLK_1US;
  
  union {
    volatile const  uint16_t  reg;                             /*!< SYNC_CNT register                                                     */
    
    struct {
      volatile const  uint16_t  val        : 10;               /*!< val bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } SYNC_CNT;
  
  union {
    volatile const  uint16_t  reg;                             /*!< FCC_COMMAND_LOW register                                              */
    
    struct {
      volatile const  uint16_t  cmd        : 16;               /*!< cmd bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } FCC_COMMAND_LOW;
  
  union {
    volatile const  uint16_t  reg;                             /*!< FCC_COMMAND_HIGH register                                             */
    
    struct {
      volatile const  uint16_t  cmd        : 16;               /*!< cmd bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } FCC_COMMAND_HIGH;
  
  union {
    volatile uint16_t  reg;                             /*!< RCC_DMA_ADDR_LOW register                                             */
    
    struct {
      volatile uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } RCC_DMA_ADDR_LOW;
  
  union {
    volatile uint16_t  reg;                             /*!< RCC_DMA_ADDR_HIGH register                                            */
    
    struct {
      volatile uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } RCC_DMA_ADDR_HIGH;
  
  union {
    volatile uint16_t  reg;                             /*!< RCC_BUFFER_LENGTH register                                            */
    
    struct {
      volatile uint16_t  length     :  6;               /*!< length bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } RCC_BUFFER_LENGTH;
  
  union {
    volatile const  uint16_t  reg;                             /*!< RCC_BYTE_CNT register                                                 */
    
    struct {
      volatile const  uint16_t  byte       :  6;               /*!< byte bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } RCC_BYTE_CNT;
  volatile const  uint32_t  RESERVED1;
  
  union {
    volatile uint16_t  reg;                             /*!< TIMER_COMPARE_A register                                              */
    
    struct {
      volatile uint16_t  value      : 13;               /*!< value bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } TIMER_COMPARE_A;
  
  union {
    volatile uint16_t  reg;                             /*!< TIMER_COMPARE_B register                                              */
    
    struct {
      volatile uint16_t  value      : 13;               /*!< value bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } TIMER_COMPARE_B;
  
  union {
    volatile uint16_t  reg;                             /*!< TIMER_COMPARE_C register                                              */
    
    struct {
      volatile uint16_t  value      : 13;               /*!< value bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } TIMER_COMPARE_C;
  volatile const  uint16_t  RESERVED2;
  
  union {
    volatile const  uint16_t  reg;                             /*!< TIMER_COUNTER register                                                */
    
    struct {
      volatile const  uint16_t  value      : 13;               /*!< value bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } TIMER_COUNTER;
  
  union {
    volatile const  uint16_t  reg;                             /*!< TIMER_CAPTURE register                                                */
    
    struct {
      volatile const  uint16_t  value      : 13;               /*!< value bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } TIMER_CAPTURE;
  
  union {
    volatile uint16_t  reg;                             /*!< SOURCE_ID register                                                    */
    
    struct {
      volatile uint16_t  value      :  8;               /*!< value bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } SOURCE_ID;
  volatile const  uint16_t  RESERVED3;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_STATUS register                                                   */
    
    struct {
      volatile uint16_t  sync_evt   :  1;               /*!< sync_evt bitfield                                                     */
      volatile uint16_t  cmd_evt    :  1;               /*!< cmd_evt bitfield                                                      */
      volatile uint16_t  pdcm_evt   :  1;               /*!< pdcm_evt bitfield                                                     */
      volatile uint16_t  disc_evt   :  1;               /*!< disc_evt bitfield                                                     */
      volatile uint16_t  crc_err_evt:  1;               /*!< crc_err_evt bitfield                                                  */
      volatile uint16_t  pdcm_err_evt:  1;              /*!< pdcm_err_evt bitfield                                                 */
      volatile uint16_t  disc_err_evt:  1;              /*!< disc_err_evt bitfield                                                 */
      volatile uint16_t  fcc_error  :  1;               /*!< fcc_error bitfield                                                    */
      volatile uint16_t  start_err_evt:  1;             /*!< start_err_evt bitfield                                                */
      volatile uint16_t  timer_a_evt:  1;               /*!< timer_a_evt bitfield                                                  */
      volatile uint16_t  timer_b_evt:  1;               /*!< timer_b_evt bitfield                                                  */
      volatile uint16_t  timer_c_evt:  1;               /*!< timer_c_evt bitfield                                                  */
      volatile uint16_t  rcc_finish :  1;               /*!< rcc_finish bitfield                                                   */
      volatile uint16_t  rcc_ready  :  1;               /*!< rcc_ready bitfield                                                    */
      volatile uint16_t  sync_cnt_evt:  1;              /*!< sync_cnt_evt bitfield                                                 */
      volatile uint16_t  disc_curr_evt:  1;             /*!< disc_curr_evt bitfield                                                */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_STATUS;
  volatile const  uint16_t  RESERVED4;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_MASK register                                                     */
    
    struct {
      volatile uint16_t  mask       : 16;               /*!< mask bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_MASK;
  volatile const  uint16_t  RESERVED5;
  
  union {
    volatile  uint16_t  reg;                             /*!< IRQ_VENABLE register                                                  */
    
    struct {
      volatile  uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VENABLE;
  
  union {
    volatile  uint16_t  reg;                             /*!< IRQ_VDISABLE register                                                 */
    
    struct {
      volatile  uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VDISABLE;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_VMAX register                                                     */
    
    struct {
      volatile uint16_t  vmax       :  5;               /*!< vmax bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VMAX;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_VNO register                                                      */
    
    struct {
      volatile uint16_t  vno        :  5;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VNO;
} DSI3_Type;


/* ================================================================================ */
/* ================                       BRG                      ================ */
/* ================================================================================ */


/**
  * @brief Burst generation Module (BRG)
  */

typedef struct {                                    /*!< BRG Structure                                                         */
  
  union {
    volatile uint16_t  reg;                             /*!< BRG_CTRL register                                                     */
    
    struct {
      volatile  uint16_t  burst_en   :  1;               /*!< burst_en bitfield                                                     */
      volatile  uint16_t  burst_brk  :  1;               /*!< burst_brk bitfield                                                    */
      volatile const  uint16_t  burst_sta  :  2;               /*!< burst_sta bitfield                                                    */
      volatile  uint16_t  burst_en_diag:  1;             /*!< burst_en_diag bitfield                                                */
    } bit;                                          /*!< BitSize                                                               */
  } BRG_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< BRG_CFG register                                                      */
    
    struct {
      volatile uint16_t  n_pulses   :  7;               /*!< n_pulses bitfield                                                     */
      volatile uint16_t  burst_type :  2;               /*!< burst_type bitfield                                                   */
      volatile uint16_t  code_len   :  4;               /*!< code_len bitfield                                                     */
      volatile uint16_t  sel_inc    :  1;               /*!< sel_inc bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } BRG_CFG;
  
  union {
    volatile uint16_t  reg;                             /*!< BRG_FC register                                                       */
    
    struct {
      volatile uint16_t  f_c        : 15;               /*!< f_c bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } BRG_FC;
  
  union {
    volatile uint16_t  reg;                             /*!< BRG_F0 register                                                       */
    
    struct {
      volatile uint16_t  f_0        : 15;               /*!< f_0 bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } BRG_F0;
  
  union {
    volatile uint16_t  reg;                             /*!< BRG_F1 register                                                       */
    
    struct {
      volatile uint16_t  f_1        : 15;               /*!< f_1 bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } BRG_F1;
  
  union {
    volatile uint16_t  reg;                             /*!< BRG_FDELTA register                                                   */
    
    struct {
      volatile uint16_t  f_delta    :  8;               /*!< f_delta bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } BRG_FDELTA;
  
  union {
    volatile uint16_t  reg;                             /*!< BRG_CODE register                                                     */
    
    struct {
      volatile uint16_t  code       : 16;               /*!< code bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } BRG_CODE;
  
  union {
    volatile uint16_t  reg;                             /*!< TDR_CTRL register                                                     */
    
    struct {
      volatile uint16_t  i_drv      :  5;               /*!< i_drv bitfield                                                        */
      volatile uint16_t  sel_isrc   :  1;               /*!< sel_isrc bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } TDR_CTRL;
  
  union {
    volatile const  uint16_t  reg;                             /*!< TDR_STATUS register                                                   */
    
    struct {
      volatile const  uint16_t  drv1_sta   :  1;               /*!< drv1_sta bitfield                                                     */
      volatile const  uint16_t  drv2_sta   :  1;               /*!< drv2_sta bitfield                                                     */
      volatile const  uint16_t  drvs_sta   :  1;               /*!< drvs_sta bitfield                                                     */
      volatile const  uint16_t  vtank_ov   :  1;               /*!< vtank_ov bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } TDR_STATUS;
} BRG_Type;


/* ================================================================================ */
/* ================                       DSP                      ================ */
/* ================================================================================ */


/**
  * @brief DSP Module (DSP)
  */

typedef struct {                                    /*!< DSP Structure                                                         */
  
  union {
    volatile uint16_t  reg;                             /*!< DSP_CTRL register                                                     */
    
    struct {
      volatile uint16_t  dsp_on     :  1;               /*!< dsp_on bitfield                                                       */
      volatile uint16_t  dsp_pwr_dwn:  1;               /*!< dsp_pwr_dwn bitfield                                                  */
      volatile const  uint16_t  dsp_on_state:  1;              /*!< dsp_on_state bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } DSP_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< ENVP_CFG register                                                     */
    
    struct {
      volatile uint16_t  envp_cfg   :  3;               /*!< envp_cfg bitfield                                                     */
      volatile uint16_t  envp_afc   :  1;               /*!< envp_afc bitfield                                                     */
      volatile uint16_t  g_cal      :  5;               /*!< g_cal bitfield                                                        */
      volatile uint16_t  dsr_sel    :  1;               /*!< dsr_sel bitfield                                                      */
      volatile uint16_t  fspi_sel   :  1;               /*!< fspi_sel bitfield                                                     */
      volatile uint16_t  aspi_sel   :  1;               /*!< aspi_sel bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_CFG;
  
  union {
    volatile  uint16_t  reg;                             /*!< ENVP_CTRL register                                                    */
    
    struct {
      volatile  uint16_t  envp_afc_brk:  1;              /*!< envp_afc_brk bitfield                                                 */
      volatile  uint16_t  envp_restart:  1;              /*!< envp_restart bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_CTRL;
  
  union {
    volatile const  uint16_t  reg;                             /*!< ENVP_ENV_RAW register                                                 */
    
    struct {
      volatile const  uint16_t  envp_env_raw: 16;              /*!< envp_env_raw bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_ENV_RAW;
  
  union {
    volatile uint16_t  reg;                             /*!< ENVP_FILT_CFG register                                                */
    
    struct {
      volatile uint16_t  filt_len_fix:  6;              /*!< filt_len_fix bitfield                                                 */
      volatile uint16_t  filt_len_code:  6;             /*!< filt_len_code bitfield                                                */
      volatile uint16_t  f1_coeff_sel:  1;              /*!< f1_coeff_sel bitfield                                                 */
      volatile uint16_t  f2_coeff_sel:  1;              /*!< f2_coeff_sel bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_FILT_CFG;
  
  union {
    volatile uint16_t  reg;                             /*!< ENVP_COEFF_3_2_1_0 register                                           */
    
    struct {
      volatile uint16_t  coeff      : 16;               /*!< coeff bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_COEFF_3_2_1_0;
  
  union {
    volatile uint16_t  reg;                             /*!< ENVP_COEFF_7_6_5_4 register                                           */
    
    struct {
      volatile uint16_t  coeff      : 16;               /*!< coeff bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_COEFF_7_6_5_4;
  
  union {
    volatile uint16_t  reg;                             /*!< ENVP_COEFF_11_10_9_8 register                                         */
    
    struct {
      volatile uint16_t  coeff      : 16;               /*!< coeff bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_COEFF_11_10_9_8;
  
  union {
    volatile uint16_t  reg;                             /*!< ENVP_COEFF_15_14_13_12 register                                       */
    
    struct {
      volatile uint16_t  coeff      : 16;               /*!< coeff bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_COEFF_15_14_13_12;
  
  union {
    volatile uint16_t  reg;                             /*!< ENVP_COEFF_19_18_17_16 register                                       */
    
    struct {
      volatile uint16_t  coeff      : 16;               /*!< coeff bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_COEFF_19_18_17_16;
  
  union {
    volatile uint16_t  reg;                             /*!< ENVP_COEFF_23_22_21_20 register                                       */
    
    struct {
      volatile uint16_t  coeff      : 16;               /*!< coeff bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_COEFF_23_22_21_20;
  
  union {
    volatile uint16_t  reg;                             /*!< ENVP_COEFF_27_26_25_24 register                                       */
    
    struct {
      volatile uint16_t  coeff      : 16;               /*!< coeff bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_COEFF_27_26_25_24;
  
  union {
    volatile uint16_t  reg;                             /*!< ENVP_COEFF_31_30_29_28 register                                       */
    
    struct {
      volatile uint16_t  coeff      : 16;               /*!< coeff bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_COEFF_31_30_29_28;
  
  union {
    volatile uint16_t  reg;                             /*!< FTC_CTRL register                                                     */
    
    struct {
      volatile uint16_t  ftc_cfg    :  3;               /*!< ftc_cfg bitfield                                                      */
      volatile uint16_t  ftc_en     :  1;               /*!< ftc_en bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } FTC_CTRL;
  
  union {
    volatile const  uint16_t  reg;                             /*!< ENV_FTC register                                                      */
    
    struct {
      volatile const  uint16_t  env_ftc    : 16;               /*!< env_ftc bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } ENV_FTC;
  
  union {
    volatile uint16_t  reg;                             /*!< AMPD_CTRL register                                                    */
    
    struct {
      volatile uint16_t  ampd_g_dig :  7;               /*!< ampd_g_dig bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } AMPD_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< STC_CTRL register                                                     */
    
    struct {
      volatile uint16_t  ampd_g_dig_target:  7;         /*!< ampd_g_dig_target bitfield                                            */
      volatile uint16_t  ampd_stc_mod:  1;              /*!< ampd_stc_mod bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } STC_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< STC_TB register                                                       */
    
    struct {
      volatile uint16_t  ampd_stc_tb: 12;               /*!< ampd_stc_tb bitfield                                                  */
    } bit;                                          /*!< BitSize                                                               */
  } STC_TB;
  
  union {
    volatile const  uint16_t  reg;                             /*!< AMPD_ENV register                                                     */
    
    struct {
      volatile const  uint16_t  ampd_env   :  8;               /*!< ampd_env bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } AMPD_ENV;
  
  union {
    volatile const  uint16_t  reg;                             /*!< MT register                                                           */
    
    struct {
      volatile const  uint16_t  mt_ts      : 16;               /*!< mt_ts bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } MT;
  
  union {
    volatile uint16_t  reg;                             /*!< RFM_CTRL register                                                     */
    
    struct {
      volatile uint16_t  rfm_start  :  5;               /*!< rfm_start bitfield                                                    */
      volatile uint16_t  rfm_width  :  5;               /*!< rfm_width bitfield                                                    */
      volatile const  uint16_t  rfm_status :  1;               /*!< rfm_status bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } RFM_CTRL;
  
  union {
    volatile const  uint16_t  reg;                             /*!< RFM_CROSS_COUNT register                                              */
    
    struct {
      volatile const  uint16_t  rfm_cross_count:  6;           /*!< rfm_cross_count bitfield                                              */
    } bit;                                          /*!< BitSize                                                               */
  } RFM_CROSS_COUNT;
  
  union {
    volatile const  uint16_t  reg;                             /*!< RFM_COUNTS register                                                   */
    
    struct {
      volatile const  uint16_t  rfm_counts :  6;               /*!< rfm_counts bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } RFM_COUNTS;
  
  union {
    volatile const  uint16_t  reg;                             /*!< RFM_SAMPLES register                                                  */
    
    struct {
      volatile const  uint16_t  rfm_samples: 10;               /*!< rfm_samples bitfield                                                  */
    } bit;                                          /*!< BitSize                                                               */
  } RFM_SAMPLES;
  
  union {
    volatile const  uint16_t  reg;                             /*!< RTM register                                                          */
    
    struct {
      volatile const  uint16_t  rtm_rt     : 13;               /*!< rtm_rt bitfield                                                       */
      volatile const  uint16_t  rtm_rt_end :  1;               /*!< rtm_rt_end bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } RTM;
  
  union {
    volatile uint16_t  reg;                             /*!< ATG_CTRL register                                                     */
    
    struct {
      volatile uint16_t  atg_tau    :  3;               /*!< atg_tau bitfield                                                      */
      volatile uint16_t  atg_alpha  :  3;               /*!< atg_alpha bitfield                                                    */
      volatile uint16_t  atg_ini    :  3;               /*!< atg_ini bitfield                                                      */
      volatile uint16_t  atg_cfg    :  1;               /*!< atg_cfg bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } ATG_CTRL;
  
  union {
    volatile const  uint16_t  reg;                             /*!< ATG_TH register                                                       */
    
    struct {
      volatile const  uint16_t  atg_th     :  8;               /*!< atg_th bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } ATG_TH;
  
  union {
    volatile uint16_t  reg;                             /*!< AATG1_CTRL register                                                   */
    
    struct {
      volatile uint16_t  aatg1_cn   :  3;               /*!< aatg1_cn bitfield                                                     */
      volatile uint16_t  aatg1_cw   :  3;               /*!< aatg1_cw bitfield                                                     */
      volatile uint16_t  aatg1_alpha:  2;               /*!< aatg1_alpha bitfield                                                  */
      volatile uint16_t  aatg1_off  :  1;               /*!< aatg1_off bitfield                                                    */
      volatile const  uint16_t  aatg1_buf_full:  1;            /*!< aatg1_buf_full bitfield                                               */
      volatile const  uint16_t  aatg1_buf_half:  1;            /*!< aatg1_buf_half bitfield                                               */
    } bit;                                          /*!< BitSize                                                               */
  } AATG1_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< AATG2_CTRL register                                                   */
    
    struct {
      volatile uint16_t  aatg2_cn   :  3;               /*!< aatg2_cn bitfield                                                     */
      volatile uint16_t  aatg2_cw   :  3;               /*!< aatg2_cw bitfield                                                     */
      volatile uint16_t  aatg2_alpha:  2;               /*!< aatg2_alpha bitfield                                                  */
      volatile uint16_t  aatg2_off  :  1;               /*!< aatg2_off bitfield                                                    */
      volatile const  uint16_t  aatg2_buf_full:  1;            /*!< aatg2_buf_full bitfield                                               */
      volatile const  uint16_t  aatg2_buf_half:  1;            /*!< aatg2_buf_half bitfield                                               */
    } bit;                                          /*!< BitSize                                                               */
  } AATG2_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< STG_TH register                                                       */
    
    struct {
      volatile uint16_t  stg_th     :  8;               /*!< stg_th bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } STG_TH;
  
  union {
    volatile uint16_t  reg;                             /*!< STG_TB register                                                       */
    
    struct {
      volatile uint16_t  stg_tb     : 10;               /*!< stg_tb bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } STG_TB;
  
  union {
    volatile uint16_t  reg;                             /*!< STG_STEP register                                                     */
    
    struct {
      volatile uint16_t  stg_step   :  8;               /*!< stg_step bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } STG_STEP;
  
  union {
    volatile uint16_t  reg;                             /*!< EEVAL_CTRL register                                                   */
    
    struct {
      volatile uint16_t  eeval_sel  :  4;               /*!< eeval_sel bitfield                                                    */
      volatile uint16_t  eeval_sens :  3;               /*!< eeval_sens bitfield                                                   */
      volatile uint16_t  eeval_dma_val:  1;             /*!< eeval_dma_val bitfield                                                */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< EEVAL_DMA_CTRL register                                               */
    
    struct {
      volatile uint16_t  length     :  8;               /*!< length bitfield                                                       */
      volatile uint16_t  wrap_off   :  1;               /*!< wrap_off bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL_DMA_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< EEVAL1_DMA_CTRL register                                              */
    
    struct {
      volatile uint16_t  length     :  8;               /*!< length bitfield                                                       */
      volatile uint16_t  wrap_off   :  1;               /*!< wrap_off bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL1_DMA_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< EEVAL2_DMA_CTRL register                                              */
    
    struct {
      volatile uint16_t  length     :  8;               /*!< length bitfield                                                       */
      volatile uint16_t  wrap_off   :  1;               /*!< wrap_off bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL2_DMA_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< EEVAL_DMA_ADDR register                                               */
    
    struct {
      volatile uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL_DMA_ADDR;
  
  union {
    volatile uint16_t  reg;                             /*!< EEVAL1_DMA_ADDR register                                              */
    
    struct {
      volatile uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL1_DMA_ADDR;
  
  union {
    volatile uint16_t  reg;                             /*!< EEVAL2_DMA_ADDR register                                              */
    
    struct {
      volatile uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL2_DMA_ADDR;
  
  union {
    volatile const  uint16_t  reg;                             /*!< EEVAL_DMA_NEXT_ADDR register                                          */
    
    struct {
      volatile const  uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL_DMA_NEXT_ADDR;
  
  union {
    volatile const  uint16_t  reg;                             /*!< EEVAL1_DMA_NEXT_ADDR register                                         */
    
    struct {
      volatile const  uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL1_DMA_NEXT_ADDR;
  
  union {
    volatile const  uint16_t  reg;                             /*!< EEVAL2_DMA_NEXT_ADDR register                                         */
    
    struct {
      volatile const  uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL2_DMA_NEXT_ADDR;
  
  union {
    volatile const  uint16_t  reg;                             /*!< EEVAL_DMA_NEXT_WORD register                                          */
    
    struct {
      volatile const  uint16_t  words      :  8;               /*!< words bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL_DMA_NEXT_WORD;
  
  union {
    volatile const  uint16_t  reg;                             /*!< EEVAL1_DMA_NEXT_WORD register                                         */
    
    struct {
      volatile const  uint16_t  words      :  8;               /*!< words bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL1_DMA_NEXT_WORD;
  
  union {
    volatile const  uint16_t  reg;                             /*!< EEVAL2_DMA_NEXT_WORD register                                         */
    
    struct {
      volatile const  uint16_t  words      :  8;               /*!< words bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL2_DMA_NEXT_WORD;
  
  union {
    volatile uint16_t  reg;                             /*!< EDET_PS_VFA register                                                  */
    
    struct {
      volatile uint16_t  edet_ps_vfa:  1;               /*!< edet_ps_vfa bitfield                                                  */
           uint16_t             :  7;
      volatile uint16_t  edet_ps_vfa_pw:  8;            /*!< edet_ps_vfa_pw bitfield                                               */
    } bit;                                          /*!< BitSize                                                               */
  } EDET_PS_VFA;
  
  union {
    volatile uint16_t  reg;                             /*!< EDI_DMA_CHANNEL_SEL register                                          */
    
    struct {
      volatile uint16_t  ch0_sel    :  2;               /*!< ch0_sel bitfield                                                      */
      volatile uint16_t  ch1_sel    :  2;               /*!< ch1_sel bitfield                                                      */
      volatile uint16_t  ch2_sel    :  2;               /*!< ch2_sel bitfield                                                      */
      volatile uint16_t  ch3_sel    :  2;               /*!< ch3_sel bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } EDI_DMA_CHANNEL_SEL;
  
  union {
    volatile uint16_t  reg;                             /*!< EDI0_DMA_CTRL register                                                */
    
    struct {
      volatile uint16_t  length     :  8;               /*!< length bitfield                                                       */
      volatile uint16_t  wrap_off   :  1;               /*!< wrap_off bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } EDI0_DMA_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< EDI1_DMA_CTRL register                                                */
    
    struct {
      volatile uint16_t  length     :  8;               /*!< length bitfield                                                       */
      volatile uint16_t  wrap_off   :  1;               /*!< wrap_off bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } EDI1_DMA_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< EDI2_DMA_CTRL register                                                */
    
    struct {
      volatile uint16_t  length     :  8;               /*!< length bitfield                                                       */
      volatile uint16_t  wrap_off   :  1;               /*!< wrap_off bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } EDI2_DMA_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< EDI3_DMA_CTRL register                                                */
    
    struct {
      volatile uint16_t  length     :  8;               /*!< length bitfield                                                       */
      volatile uint16_t  wrap_off   :  1;               /*!< wrap_off bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } EDI3_DMA_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< EDI0_DMA_ADDR register                                                */
    
    struct {
      volatile uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI0_DMA_ADDR;
  
  union {
    volatile uint16_t  reg;                             /*!< EDI1_DMA_ADDR register                                                */
    
    struct {
      volatile uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI1_DMA_ADDR;
  
  union {
    volatile uint16_t  reg;                             /*!< EDI2_DMA_ADDR register                                                */
    
    struct {
      volatile uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI2_DMA_ADDR;
  
  union {
    volatile uint16_t  reg;                             /*!< EDI3_DMA_ADDR register                                                */
    
    struct {
      volatile uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI3_DMA_ADDR;
  
  union {
    volatile const  uint16_t  reg;                             /*!< EDI0_DMA_NEXT_ADDR register                                           */
    
    struct {
      volatile const  uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI0_DMA_NEXT_ADDR;
  
  union {
    volatile const  uint16_t  reg;                             /*!< EDI1_DMA_NEXT_ADDR register                                           */
    
    struct {
      volatile const  uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI1_DMA_NEXT_ADDR;
  
  union {
    volatile const  uint16_t  reg;                             /*!< EDI2_DMA_NEXT_ADDR register                                           */
    
    struct {
      volatile const  uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI2_DMA_NEXT_ADDR;
  
  union {
    volatile const  uint16_t  reg;                             /*!< EDI3_DMA_NEXT_ADDR register                                           */
    
    struct {
      volatile const  uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI3_DMA_NEXT_ADDR;
  
  union {
    volatile const  uint16_t  reg;                             /*!< EDI0_DMA_NEXT_WORD register                                           */
    
    struct {
      volatile const  uint16_t  word       :  8;               /*!< word bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI0_DMA_NEXT_WORD;
  
  union {
    volatile const  uint16_t  reg;                             /*!< EDI1_DMA_NEXT_WORD register                                           */
    
    struct {
      volatile const  uint16_t  word       :  8;               /*!< word bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI1_DMA_NEXT_WORD;
  
  union {
    volatile const  uint16_t  reg;                             /*!< EDI2_DMA_NEXT_WORD register                                           */
    
    struct {
      volatile const  uint16_t  word       :  8;               /*!< word bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI2_DMA_NEXT_WORD;
  
  union {
    volatile const  uint16_t  reg;                             /*!< EDI3_DMA_NEXT_WORD register                                           */
    
    struct {
      volatile const  uint16_t  word       :  8;               /*!< word bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI3_DMA_NEXT_WORD;
  
  union {
    volatile uint16_t  reg;                             /*!< NFD_CTRL register                                                     */
    
    struct {
      volatile uint16_t  nfd_sens   :  3;               /*!< nfd_sens bitfield                                                     */
      volatile uint16_t  nfd_irq_cfg:  2;               /*!< nfd_irq_cfg bitfield                                                  */
      volatile const  uint16_t  nfd_max_num:  3;               /*!< nfd_max_num bitfield                                                  */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< NFD_TH register                                                       */
    
    struct {
      volatile uint16_t  nfd_th     : 16;               /*!< nfd_th bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_TH;
  
  union {
    volatile const  uint16_t  reg;                             /*!< NFD_ECHO1 register                                                    */
    
    struct {
      volatile const  uint16_t  nfd_echo1  : 16;               /*!< nfd_echo1 bitfield                                                    */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_ECHO1;
  
  union {
    volatile const  uint16_t  reg;                             /*!< NFD_TS1 register                                                      */
    
    struct {
      volatile const  uint16_t  nfd_ts1    : 16;               /*!< nfd_ts1 bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_TS1;
  
  union {
    volatile const  uint16_t  reg;                             /*!< NFD_ECHO2 register                                                    */
    
    struct {
      volatile const  uint16_t  nfd_echo2  : 16;               /*!< nfd_echo2 bitfield                                                    */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_ECHO2;
  
  union {
    volatile const  uint16_t  reg;                             /*!< NFD_TS2 register                                                      */
    
    struct {
      volatile const  uint16_t  nfd_ts2    : 16;               /*!< nfd_ts2 bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_TS2;
  
  union {
    volatile const  uint16_t  reg;                             /*!< NFD_ECHO3 register                                                    */
    
    struct {
      volatile const  uint16_t  nfd_echo3  : 16;               /*!< nfd_echo3 bitfield                                                    */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_ECHO3;
  
  union {
    volatile const  uint16_t  reg;                             /*!< NFD_TS3 register                                                      */
    
    struct {
      volatile const  uint16_t  nfd_ts3    : 16;               /*!< nfd_ts3 bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_TS3;
  
  union {
    volatile const  uint16_t  reg;                             /*!< NFD_ECHO4 register                                                    */
    
    struct {
      volatile const  uint16_t  nfd_echo4  : 16;               /*!< nfd_echo4 bitfield                                                    */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_ECHO4;
  
  union {
    volatile const  uint16_t  reg;                             /*!< NFD_TS4 register                                                      */
    
    struct {
      volatile const  uint16_t  nfd_ts4    : 16;               /*!< nfd_ts4 bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_TS4;
  
  union {
    volatile const  uint16_t  reg;                             /*!< NFD_ECHO5 register                                                    */
    
    struct {
      volatile const  uint16_t  nfd_echo5  : 16;               /*!< nfd_echo5 bitfield                                                    */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_ECHO5;
  
  union {
    volatile const  uint16_t  reg;                             /*!< NFD_TS5 register                                                      */
    
    struct {
      volatile const  uint16_t  nfd_ts5    : 16;               /*!< nfd_ts5 bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_TS5;
  
  union {
    volatile uint16_t  reg;                             /*!< ASP_CTRL register                                                     */
    
    struct {
      volatile uint16_t  g_ana      :  3;               /*!< g_ana bitfield                                                        */
      volatile uint16_t  fc_x2      :  1;               /*!< fc_x2 bitfield                                                        */
      volatile uint16_t  g_ana_diag :  1;               /*!< g_ana_diag bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } ASP_CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< ASP_ADC_CTRL register                                                 */
    
    struct {
      volatile uint16_t  soc        :  1;               /*!< soc bitfield                                                          */
      volatile const  uint16_t  eoc        :  1;               /*!< eoc bitfield                                                          */
      volatile uint16_t  adc_cpu_ctrl:  1;              /*!< adc_cpu_ctrl bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } ASP_ADC_CTRL;
  
  union {
    volatile const  uint16_t  reg;                             /*!< ASP_ADC_DTA register                                                  */
    
    struct {
      volatile const  uint16_t  adc_dta    : 14;               /*!< adc_dta bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } ASP_ADC_DTA;
  volatile const  uint32_t  RESERVED[5];
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_STATUS register                                                   */
    
    struct {
      volatile uint16_t  eeval_tlh_evt:  1;             /*!< eeval_tlh_evt bitfield                                                */
      volatile uint16_t  eeval_thl_evt:  1;             /*!< eeval_thl_evt bitfield                                                */
      volatile uint16_t  eeval_max_evt:  1;             /*!< eeval_max_evt bitfield                                                */
      volatile uint16_t  eeval_min_evt:  1;             /*!< eeval_min_evt bitfield                                                */
      volatile uint16_t  eeval1_max_evt:  1;            /*!< eeval1_max_evt bitfield                                               */
      volatile uint16_t  eeval2_max_evt:  1;            /*!< eeval2_max_evt bitfield                                               */
      volatile uint16_t  rfm_evt    :  1;               /*!< rfm_evt bitfield                                                      */
      volatile uint16_t  rtm_evt    :  1;               /*!< rtm_evt bitfield                                                      */
      volatile uint16_t  nfd_evt    :  1;               /*!< nfd_evt bitfield                                                      */
      volatile uint16_t  eeval_dma_wrap:  1;            /*!< eeval_dma_wrap bitfield                                               */
      volatile uint16_t  eeval1_dma_wrap:  1;           /*!< eeval1_dma_wrap bitfield                                              */
      volatile uint16_t  eeval2_dma_wrap:  1;           /*!< eeval2_dma_wrap bitfield                                              */
      volatile uint16_t  edi0_dma_wrap:  1;             /*!< edi0_dma_wrap bitfield                                                */
      volatile uint16_t  edi1_dma_wrap:  1;             /*!< edi1_dma_wrap bitfield                                                */
      volatile uint16_t  edi2_dma_wrap:  1;             /*!< edi2_dma_wrap bitfield                                                */
      volatile uint16_t  edi3_dma_wrap:  1;             /*!< edi3_dma_wrap bitfield                                                */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_STATUS;
  volatile const  uint16_t  RESERVED1;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_MASK register                                                     */
    
    struct {
      volatile uint16_t  mask       : 16;               /*!< mask bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_MASK;
  volatile const  uint16_t  RESERVED2;
  
  union {
    volatile  uint16_t  reg;                             /*!< IRQ_VENABLE register                                                  */
    
    struct {
      volatile  uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VENABLE;
  
  union {
    volatile  uint16_t  reg;                             /*!< IRQ_VDISABLE register                                                 */
    
    struct {
      volatile  uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VDISABLE;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_VMAX register                                                     */
    
    struct {
      volatile uint16_t  vmax       :  5;               /*!< vmax bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VMAX;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_VNO register                                                      */
    
    struct {
      volatile uint16_t  vno        :  5;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VNO;
} DSP_Type;


/* ================================================================================ */
/* ================                   SYSTEM_CTRL                  ================ */
/* ================================================================================ */


/**
  * @brief SYSTEM Control Module (SYSTEM_CTRL)
  */

typedef struct {                                    /*!< SYSTEM_CTRL Structure                                                 */
  
  union {
    volatile  uint16_t  reg;                             /*!< POWER register                                                        */
    
    struct {
      volatile  uint16_t  standby    :  1;               /*!< standby bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } POWER;
  
  union {
    volatile uint16_t  reg;                             /*!< BIST register                                                         */
    
    struct {
      volatile uint16_t  tdr_asp_bist:  1;              /*!< tdr_asp_bist bitfield                                                 */
      volatile uint16_t  dsp_bist   :  1;               /*!< dsp_bist bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } BIST;
  
  union {
    volatile uint16_t  reg;                             /*!< TRIM register                                                         */
    
    struct {
      volatile uint16_t  iconst_trim:  3;               /*!< iconst_trim bitfield                                                  */
      volatile uint16_t  tdr_ic_trim:  3;               /*!< tdr_ic_trim bitfield                                                  */
      volatile uint16_t  dsi3_ib_trim:  3;              /*!< dsi3_ib_trim bitfield                                                 */
      volatile uint16_t  dsi3_rcc_correct:  4;          /*!< dsi3_rcc_correct bitfield                                             */
      volatile uint16_t  lock       :  1;               /*!< lock bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } TRIM;
  
  union {
    volatile uint16_t  reg;                             /*!< CAP_MEAS_CTRL register                                                */
    
    struct {
      volatile uint16_t  start_diag_meas:  1;           /*!< start_diag_meas bitfield                                              */
      volatile uint16_t  select_diag:  1;               /*!< select_diag bitfield                                                  */
      volatile const  uint16_t  diag_out_cvddd:  1;            /*!< diag_out_cvddd bitfield                                               */
      volatile const  uint16_t  diag_out_cvdda:  1;            /*!< diag_out_cvdda bitfield                                               */
    } bit;                                          /*!< BitSize                                                               */
  } CAP_MEAS_CTRL;
  
  union {
    volatile const  uint16_t  reg;                             /*!< CAP_MEAS_RESULT register                                              */
    
    struct {
      volatile const  uint16_t  cap_meas_result: 10;           /*!< cap_meas_result bitfield                                              */
    } bit;                                          /*!< BitSize                                                               */
  } CAP_MEAS_RESULT;
  volatile const  uint16_t  RESERVED[19];
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_STATUS register                                                   */
    
    struct {
      volatile uint16_t  por_wake_up:  1;               /*!< por_wake_up bitfield                                                  */
      volatile uint16_t  dsi3_wake_up:  1;              /*!< dsi3_wake_up bitfield                                                 */
      volatile uint16_t  irq_abort_wake_up:  1;         /*!< irq_abort_wake_up bitfield                                            */
      volatile uint16_t  debug_wake_up:  1;             /*!< debug_wake_up bitfield                                                */
      volatile uint16_t  bist_on    :  1;               /*!< bist_on bitfield                                                      */
      volatile uint16_t  envp_parity_err_evt:  1;       /*!< envp_parity_err_evt bitfield                                          */
      volatile uint16_t  aatg1_parity_err_evt:  1;      /*!< aatg1_parity_err_evt bitfield                                         */
      volatile uint16_t  aatg2_parity_err_evt:  1;      /*!< aatg2_parity_err_evt bitfield                                         */
      volatile uint16_t  cap_meas_ready_evt:  1;        /*!< cap_meas_ready_evt bitfield                                           */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_STATUS;
  volatile const  uint16_t  RESERVED1;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_MASK register                                                     */
    
    struct {
      volatile uint16_t  mask       :  8;               /*!< mask bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_MASK;
  volatile const  uint16_t  RESERVED2;
  
  union {
    volatile  uint16_t  reg;                             /*!< IRQ_VENABLE register                                                  */
    
    struct {
      volatile  uint16_t  vno        :  3;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VENABLE;
  
  union {
    volatile  uint16_t  reg;                             /*!< IRQ_VDISABLE register                                                 */
    
    struct {
      volatile  uint16_t  vno        :  3;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VDISABLE;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_VMAX register                                                     */
    
    struct {
      volatile uint16_t  vmax       :  4;               /*!< vmax bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VMAX;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_VNO register                                                      */
    
    struct {
      volatile uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VNO;
} SYSTEM_CTRL_Type;


/* ================================================================================ */
/* ================                    DAC_CTRL                    ================ */
/* ================================================================================ */


/**
  * @brief DAC control Module (DAC_CTRL)
  */

typedef struct {                                    /*!< DAC_CTRL Structure                                                    */
  
  union {
    volatile uint16_t  reg;                             /*!< CTRL register                                                         */
    
    struct {
      volatile uint16_t  dac0_cfg   :  2;               /*!< dac0_cfg bitfield                                                     */
      volatile uint16_t  dac1_cfg   :  2;               /*!< dac1_cfg bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } CTRL;
  
  union {
    volatile uint16_t  reg;                             /*!< REG0 register                                                         */
    
    struct {
      volatile uint16_t  reg0       :  8;               /*!< reg0 bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } REG0;
  
  union {
    volatile uint16_t  reg;                             /*!< REG1 register                                                         */
    
    struct {
      volatile uint16_t  reg1       :  8;               /*!< reg1 bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } REG1;
} DAC_CTRL_Type;


/* ================================================================================ */
/* ================                       ADA                      ================ */
/* ================================================================================ */


/**
  * @brief ADA control Module (ADA)
  */

typedef struct {                                    /*!< ADA Structure                                                         */
  
  union {
    volatile uint16_t  reg;                             /*!< ADA_CFG register                                                      */
    
    struct {
      volatile uint16_t  sigsel     :  3;               /*!< sigsel bitfield                                                       */
      volatile uint16_t  chsel      :  2;               /*!< chsel bitfield                                                        */
      volatile uint16_t  en_100k    :  1;               /*!< en_100k bitfield                                                      */
      volatile uint16_t  adc_tsamp  :  2;               /*!< adc_tsamp bitfield                                                    */
      volatile uint16_t  adc_cdiv   :  2;               /*!< adc_cdiv bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } ADA_CFG;
  
  union {
    volatile uint16_t  reg;                             /*!< ADA_CTRL register                                                     */
    
    struct {
      volatile uint16_t  soc        :  1;               /*!< soc bitfield                                                          */
      volatile const  uint16_t  eoc        :  1;               /*!< eoc bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } ADA_CTRL;
  
  union {
    volatile const  uint16_t  reg;                             /*!< ADC_DTA register                                                      */
    
    struct {
      volatile const  uint16_t  adc_dta    : 10;               /*!< adc_dta bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } ADC_DTA;
} ADA_Type;


/* ================================================================================ */
/* ================                      UART                      ================ */
/* ================================================================================ */


/**
  * @brief UART (FPGA only) (UART)
  */

typedef struct {                                    /*!< UART Structure                                                        */
  
  union {
    volatile uint16_t  reg;                             /*!< DATA register                                                         */
    
    struct {
      volatile uint16_t  data       :  8;               /*!< data bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } DATA;
  volatile const  uint16_t  RESERVED;
  
  union {
    volatile uint16_t  reg;                             /*!< STAT register                                                         */
    
    struct {
      volatile const  uint16_t  tx_full    :  1;               /*!< tx_full bitfield                                                      */
      volatile const  uint16_t  rx_full    :  1;               /*!< rx_full bitfield                                                      */
      volatile uint16_t  tx_ovr     :  1;               /*!< tx_ovr bitfield                                                       */
      volatile uint16_t  rx_ovr     :  1;               /*!< rx_ovr bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } STAT;
  volatile const  uint16_t  RESERVED1;
  
  union {
    volatile uint16_t  reg;                             /*!< CTRL register                                                         */
    
    struct {
      volatile uint16_t  txen       :  1;               /*!< txen bitfield                                                         */
      volatile uint16_t  rxen       :  1;               /*!< rxen bitfield                                                         */
      volatile uint16_t  txirqen    :  1;               /*!< txirqen bitfield                                                      */
      volatile uint16_t  rxirqen    :  1;               /*!< rxirqen bitfield                                                      */
      volatile uint16_t  txovrirqen :  1;               /*!< txovrirqen bitfield                                                   */
      volatile uint16_t  rxovrirqen :  1;               /*!< rxovrirqen bitfield                                                   */
      volatile uint16_t  hs         :  1;               /*!< hs bitfield                                                           */
    } bit;                                          /*!< BitSize                                                               */
  } CTRL;
  volatile const  uint16_t  RESERVED2;
  
  union {
    volatile uint16_t  reg;                             /*!< INTCLR register                                                       */
    
    struct {
      volatile uint16_t  txint      :  1;               /*!< txint bitfield                                                        */
      volatile uint16_t  rxint      :  1;               /*!< rxint bitfield                                                        */
      volatile uint16_t  txovrint   :  1;               /*!< txovrint bitfield                                                     */
      volatile uint16_t  rxovrint   :  1;               /*!< rxovrint bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } INTCLR;
  volatile const  uint16_t  RESERVED3;
  
  union {
    volatile uint16_t  reg;                             /*!< BAUD_LOW register                                                     */
    
    struct {
      volatile uint16_t  baud_div   : 16;               /*!< baud_div bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } BAUD_LOW;
  
  union {
    volatile uint16_t  reg;                             /*!< BAUD_HIGH register                                                    */
    
    struct {
      volatile uint16_t  baud_div   : 16;               /*!< baud_div bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } BAUD_HIGH;
  volatile const  uint32_t  RESERVED4[7];
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_STATUS register                                                   */
    
    struct {
      volatile uint16_t  txint      :  1;               /*!< txint bitfield                                                        */
      volatile uint16_t  rxint      :  1;               /*!< rxint bitfield                                                        */
      volatile uint16_t  txovrint   :  1;               /*!< txovrint bitfield                                                     */
      volatile uint16_t  rxovrint   :  1;               /*!< rxovrint bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_STATUS;
  volatile const  uint16_t  RESERVED5;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_MASK register                                                     */
    
    struct {
      volatile uint16_t  mask       :  4;               /*!< mask bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_MASK;
  volatile const  uint16_t  RESERVED6;
  
  union {
    volatile  uint16_t  reg;                             /*!< IRQ_VENABLE register                                                  */
    
    struct {
      volatile  uint16_t  vno        :  2;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VENABLE;
  
  union {
    volatile  uint16_t  reg;                             /*!< IRQ_VDISABLE register                                                 */
    
    struct {
      volatile  uint16_t  vno        :  2;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VDISABLE;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_VMAX register                                                     */
    
    struct {
      volatile uint16_t  vmax       :  3;               /*!< vmax bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VMAX;
  
  union {
    volatile uint16_t  reg;                             /*!< IRQ_VNO register                                                      */
    
    struct {
      volatile uint16_t  vno        :  3;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VNO;
} UART_Type;


/* --------------------  End of section using anonymous unions  ------------------- */



/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */



/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */



/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group m52417a */




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


/***************************************************************************//**
 * @file			el_types.h
 *
 * @creator		sbai
 * @created		06.10.2014
 *
 * @brief  		Provides all basic data type definitions
 *
 * @purpose
 *
 * Provides all basic data type definitions for Elmos's CPU APIs and development
 * on ELMOS'S intelligent ICs.
 *
 * $Id: io_m52417a.h 392 2019-01-22 09:59:18Z siko $
 *
 * $Revision: 392 $
 *
 *****************************************************************************
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
 







// Register definition mapping from CMSIS style to ELMOS style

// module WDOG instance WDOG








// module SYS_STATE instance SYS_STATE
































// module CRC16 instance CRC16










// module OTP_CTRL instance OTP0_CTRL





































// module OTP_CTRL instance OTP1_CTRL





































// module EEPROM_CTRL instance EEPROM_CTRL






















// module GPIO instance GPIO















// module SWTIMER instance SWTIMER















// module DSI3 instance DSI3
































// module BRG instance BRG














// module DSP instance DSP








































































































// module SYSTEM_CTRL instance SYSTEM_CTRL

















// module DAC_CTRL instance DAC_CTRL




// module ADA instance ADA






// module UART instance UART



















	







/* *************************************************************************** */
/* *********************** STRUCTS, ENUMS AND TYPEDEFS *********************** */
/* *************************************************************************** */
enum dsi3_eRCC_Chiptime
{
  dsi3_eRCC_Chiptime_3US = 0u,
  dsi3_eRCC_Chiptime_4US = 1u,
  dsi3_eRCC_Chiptime_5US = 2u,
  dsi3_eRCC_Chiptime_6US = 3u
};

typedef enum dsi3_eRCC_Chiptime dsi3_RCC_Chiptime_t;

enum dsi3_eRCC_Cur 
{

  dsi3_eRCC_Cur_STD     = 0u,
  dsi3_eRCC_Cur_HLF     = 1u
};

typedef enum dsi3_eRCC_Cur dsi3_RCC_Cur_t;

enum dsi3_ePdcmSeed
{
  dsi3_ePDCM_Seed_ID    = 0u,
  dsi3_ePDCM_Seed_FF    = 1u
};

typedef enum dsi3_ePdcmSeed dsi3_PdcmSeed_t;

enum dsi3_etimer_start_sel
{

  DSI3_TIMER_ST_EDGE   = 0u,
  DSI3_TIMER_ST_SYNC   = 1u
};

typedef enum dsi3_etimer_start_sel dsi3_timer_start_sel_t;

enum dsi3_eDebounceValue
{

  dsi3_eDebounceValue_OFF      = 0u,
  dsi3_eDebounceValue_83NS     = 1u,
  dsi3_eDebounceValue_166NS    = 2u,
  dsi3_eDebounceValue_333NS    = 3u,
  dsi3_eDebounceValue_666NS    = 4u,
  dsi3_eDebounceValue_1333NS   = 5u,
  dsi3_eDebounceValue_2666NS   = 6u,
  dsi3_eDebounceValue_5333NS   = 7u
};

typedef enum dsi3_eDebounceValue dsi3_DebounceValue_t;


union dsi3_uClk1US
{
  struct
  {
    uint16_t  frac       :  5;               /*!< frac bitfield                                                         */
    uint16_t  div        :  5;               /*!< div bitfield                                                          */
  }                     Fields;
  uint16_t              Value;
};

typedef union dsi3_uClk1US dsi3_Clk1US_t;



enum dsi3_eRCC_Slope /**< Reverse communication channel current slope selection */
{
  dsi3_eRCC_Slope_1us          = 0u,
  dsi3_eRCC_Slope_2us          = 1u,
  dsi3_eRCC_Slope_3us          = 2u,
  dsi3_eRCC_Slope_4us          = 3u,
  dsi3_eRCC_Slope_6us          = 4u
};

typedef enum dsi3_eRCC_Slope dsi3_RCCSlope_t;


enum dsi3_eRCC_Curve /**< Reverse communication channel current waveform */
{
  dsi3_eRCC_Curve_Rounded      = 0u,
  dsi3_eRCC_Curve_Linear       = 1u
};

typedef enum dsi3_eRCC_Curve dsi3_RCC_Curve_t;


enum dsi3_eRCC_CurrentOffset /**< Reverse communication channel current offset value */
{
  dsi3_eRCC_CurrentOffset_0uA = 0u,
  dsi3_eRCC_CurrentOffset_1uA = 1u,
  dsi3_eRCC_CurrentOffset_2uA = 2u,
  dsi3_eRCC_CurrentOffset_3uA = 3u,
  dsi3_eRCC_CurrentOffset_4uA = 4u,
  dsi3_eRCC_CurrentOffset_5uA = 5u,
  dsi3_eRCC_CurrentOffset_6uA = 6u,
  dsi3_eRCC_CurrentOffset_7uA = 7u
};

typedef enum dsi3_eRCC_CurrentOffset dsi3_RCC_CurrentOffset_t;


enum dsi3_eFCC_TBit /**< Bit timing FCC */
{
  dsi3_eFCC_TBit_08us 		= 0u,
  dsi3_eFCC_TBit_16us 		= 1u,
  dsi3_eFCC_TBit_32us 		= 2u,
  dsi3_eFCC_TBit_reserved  	= 3u
};

typedef enum dsi3_eFCC_TBit dsi3_FCC_TBit_t;

/* *************************************************************************** */
/* *************************** DEFINES AND MACROS **************************** */
/* *************************************************************************** */


/* DSI3_CONFIG */



/* DSI3_CTRL */




/* --> 18-01-22/POE: r4083, Improvement
 * Replaced macro with parameterized version to prevent
 * compiler warning 
 */
/* --> 18-01-22/POE: r4083, Improvement */

/* *************************************************************************** */
/* ******************************* DSI3 CONFIG ******************************* */
/* *************************************************************************** */













/* *************************************************************************** */
/* ********************************* DSI3 STATUS ***************************** */
/* *************************************************************************** */




/*--> 2018-02-23/POE: revision R4346, Improvement
 * Added defines for fcc_low_flag access
 */
/*--> 2018-02-23/POE: revision R4346, Improvement */

  


/* *************************************************************************** */
/* ************************** DSI3 DISCOVERY CTRL **************************** */
/* *************************************************************************** */





  
/* *************************************************************************** */
/* ************************* DSI3 TIMER_COMPARE_A **************************** */
/* *************************************************************************** */


/* *************************************************************************** */
/* ************************* DSI3 TIMER_COMPARE_B **************************** */
/* *************************************************************************** */


/* *************************************************************************** */
/* ************************* DSI3 TIMER_COMPARE_C **************************** */
/* *************************************************************************** */


/* *************************************************************************** */
/* ************************** DSI3 SOURCE ID ********************************* */
/* *************************************************************************** */



/* *************************************************************************** */
/* *************************** DSI3 Interrupts ******************************* */
/* *************************************************************************** */



/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

typedef void *                                    Dsi3BusIf_pvoid_t;                      /**<  Void-pointer data type. */
typedef const   void *                            Dsi3BusIf_cpvoid_t;                     /**<  Constant void-pointer data type. */

typedef         Dsi3BusIf_pvoid_t                 Dsi3BusIf_pGenericEnvData_t;            /**<  Generic pointer to environment data of the BUS layer module */
typedef         Dsi3BusIf_cpvoid_t                Dsi3BusIf_cpGenericImpCfgData_t;        /**<  Generic pointer to configuration parameter of the specific BUS layer implementation */
typedef         Dsi3BusIf_pvoid_t                 Dsi3BusIf_pGenericCbCtxData_t;          /**<  Pointer to BUS callback context data */

typedef         Dsi3BusIf_pvoid_t                 Dsi3BusIf_pGenericRuntimeData_t;        /**<  Pointer to Runtime Data */
typedef const   Dsi3BusIf_pGenericRuntimeData_t   Dsi3BusIf_cpGenericRuntimeData_t;       /**<  Constant Pointer to Runtime Data */

typedef Dsi3BusIf_pvoid_t                         Dsi3BusIf_pGenericInterfaceFunctions_t; /**< Generic pointer to interface functions structure */
typedef Dsi3BusIf_cpvoid_t                        Dsi3BusIf_cpGenericInterfaceFunctions_t;/**< Generic pointer to interface functions structure (const) */

typedef         uint8_t                           Dsi3BusIf_Error_t;                      /**<  Mapping for bus error codes to generic error type */

typedef         bool_t                            Dsi3BusIf_Bool_t;                       /**<  generic bool type */

typedef         uint8_t                           Dsi3BusIf_Data_t;                       /**<  Basic BUS data type */
typedef         Dsi3BusIf_Data_t*                 Dsi3BusIf_pData_t;                      /**<  Pointer to Dsi3BusIf_Data_t */
typedef         Dsi3BusIf_Data_t**                Dsi3BusIf_ppData_t;                     /**<  Pointer-Pointer to Dsi3BusIf_Data_t */
typedef const   Dsi3BusIf_Data_t*                 Dsi3BusIf_cpData_t;                     /**<  Constant Pointer to Dsi3BusIf_Data_t */

typedef         uint8_t                           Dsi3BusIf_CountValue_t;                 /**<  CountValue data type */

typedef         uintptr_t                         Dsi3BusIf_Length_t;                     /**<  BUS layer data type of length values */
typedef         Dsi3BusIf_Length_t*               Dsi3BusIf_pLength_t;                    /**<  Pointer to Dsi3BusIf_Length_t */

typedef         Dsi3BusIf_Length_t                Dsi3BusIf_EnvDataSze_t;                 /**<  Type for bus layer environment data */

typedef         uint8_t                           Dsi3BusIf_ByteData_t;                   /**<  Byte sized data */
typedef         Dsi3BusIf_ByteData_t *            Dsi3BusIf_pByteData_t;                  /**<  Byte sized data pointer */
typedef const   Dsi3BusIf_ByteData_t *            Dsi3BusIf_cpByteData_t;                 /**<  Byte sized data constant pointer */

typedef         uint16_t                          Dsi3BusIf_WordData_t;                   /**<  Word sized data */
typedef         Dsi3BusIf_WordData_t *            Dsi3BusIf_pWordData_t;                  /**<  Word sized data pointer */
typedef  const   Dsi3BusIf_WordData_t *           Dsi3BusIf_cpWordData_t;                 /**<  Word sized data constant pointer */

typedef         uint16_t                          Dsi3BusIf_ClkDiv_t;                     /**<  Data type for clock divider */

typedef         uint16_t                          Dsi3BufIf_SyncCountValue_t;             /**<  Data type for Sync Count Value */
typedef         uint16_t                          Dsi3BufIf_TimerCaptureValue_t;          /**<  Data type for Timer Capture Value */

typedef         uint32_t                          Dsi3BusIf_DWordData_t;                  /**<  Double Word sized data */
typedef         Dsi3BusIf_DWordData_t *           Dsi3BusIf_pDWordData_t;                 /**<  Double Word sized data pointer */
typedef const   Dsi3BusIf_DWordData_t *           Dsi3BusIf_cpDWordData_t;                /**<  Double Word sized data constant pointer */

typedef         uint8_t                           Dsi3BusIf_SlaveID_t;                    /**<  Data type for SlaveID */
typedef         uint32_t                          Dsi3BusIf_Serial_t;                     /**<  Data type for Serial Number */

typedef         uint8_t                           Dsi3BusIf_CmdID_t;                      /**<  Data type for PID representation */

typedef         uint16_t                          Dsi3BusIf_InterfaceVersion_t;           /**<  Data type for interface versioning */
typedef         uint16_t                          Dsi3BusIf_Version_t;                    /**<  Data type for versioning */

typedef         uint16_t                          Dsi3BusIf_Time_t;                       /**<  Data type for register time values */
typedef         uint32_t                          Dsi3BusIf_Tick_t;                       /**<  Data type for tick count representation */
typedef         Dsi3BusIf_Tick_t                  Dsi3BusIf_TimeOut_t;                    /**<  Data type for timeout values */

struct          Dsi3BusIf_sThis;                                                          /**<  Forward declaration of Dsi3 BUS layer This-Pointer. */
typedef struct  Dsi3BusIf_sThis                   Dsi3BusIf_sThis_t;                      /**<  Typedef for Dsi3BusIf_sThis. */
typedef         Dsi3BusIf_sThis_t*                Dsi3BusIf_pThis_t;                      /**<  Typedef of pointer to Dsi3BusIf_sThis. */
typedef const   Dsi3BusIf_sThis_t*                Dsi3BusIf_cpThis_t;                     /**<  Typedef of pointer to Dsi3BusIf_sThis. */

/*
Dsi3BusIf_pvoid_t 和 Dsi3BusIf_cpvoid_t：•Dsi3BusIf_pvoid_t：定义为指向void类型的指针，用于表示通用的指针数据类型。
•Dsi3BusIf_cpvoid_t：定义为指向常量void类型的指针，用于表示通用的常量指针数据类型。
2. Dsi3BusIf_pGenericEnvData_t 和 Dsi3BusIf_cpGenericImpCfgData_t 以及其他与之类似的类型：
•这些类型是基于上面的通用指针类型定义的，用于具体表示DSI3总线层的各种数据指针，如环境数据、配置参数、回调上下文数据、运行时数据及其常量版本等。
3. Dsi3BusIf_pGenericInterfaceFunctions_t 和其const版本：•定义为指向通用接口函数结构体的指针，用于访问总线接口层提供的各种功能函数。
4. Dsi3BusIf_Error_t：•表示DSI3总线错误代码的映射类型，用于表示总线错误。
5. Dsi3BusIf_Bool_t：•定义为一个通用布尔类型，用于在DSI3总线接口层中表示布尔值。
6. Dsi3BusIf_Data_t 及其指针类型：•Dsi3BusIf_Data_t 是DSI3总线的基本数据类型，通常是一个8位无符号整数。
•Dsi3BusIf_pData_t、Dsi3BusIf_ppData_t 和 Dsi3BusIf_cpData_t 分别表示指向该基本数据类型的指针、指针的指针和常量指针。
7. Dsi3BusIf_CountValue_t：•表示计数值的数据类型，这里也是8位无符号整数。
8. Dsi3BusIf_Length_t 及其指针类型：•Dsi3BusIf_Length_t 定义为一个表示总线层长度值的数据类型，通常是无符号整数类型。•Dsi3BusIf_pLength_t 是指向Dsi3BusIf_Length_t类型的指针。
9. Dsi3BusIf_EnvDataSze_t：•定义为一种类型，用于表示DSI3总线层环境数据的大小，其实质上与Dsi3BusIf_Length_t相同。
Dsi3BusIf_ByteData_t 和其指针类型：•Dsi3BusIf_ByteData_t 定义了一个8位无符号整数类型，用于表示单字节大小的数据。
•Dsi3BusIf_pByteData_t 是指向 Dsi3BusIf_ByteData_t 类型的指针。•Dsi3BusIf_cpByteData_t 是指向 Dsi3BusIf_ByteData_t 类型的常量指针。
2. Dsi3BusIf_WordData_t 和其指针类型：•Dsi3BusIf_WordData_t 定义了一个16位无符号整数类型，用于表示双字节（word）大小的数据。•Dsi3BusIf_pWordData_t 是指向 Dsi3BusIf_WordData_t 类型的指针。
•Dsi3BusIf_cpWordData_t 是指向 Dsi3BusIf_WordData_t 类型的常量指针。
3. Dsi3BusIf_ClkDiv_t：•定义了一个16位无符号整数类型，用于表示时钟分频器的值。
4. Dsi3BufIf_SyncCountValue_t 和 Dsi3BufIf_TimerCaptureValue_t：•Dsi3BufIf_SyncCountValue_t 定义了一个16位无符号整数类型，用于表示同步计数值。
•Dsi3BufIf_TimerCaptureValue_t 定义了一个16位无符号整数类型，用于表示定时器捕获值。
5. Dsi3BusIf_DWordData_t 和其指针类型：•Dsi3BusIf_DWordData_t 定义了一个32位无符号整数类型，用于表示双字（double word）大小的数据。
•Dsi3BusIf_pDWordData_t 是指向 Dsi3BusIf_DWordData_t 类型的指针。•Dsi3BusIf_cpDWordData_t 是指向 Dsi3BusIf_DWordData_t 类型的常量指针。
6. Dsi3BusIf_SlaveID_t 和 Dsi3BusIf_Serial_t：•Dsi3BusIf_SlaveID_t 定义了一个8位无符号整数类型，用于表示从设备ID。
•Dsi3BusIf_Serial_t 定义了一个32位无符号整数类型，用于表示序列号。
7. Dsi3BusIf_CmdID_t：•定义了一个8位无符号整数类型，用于表示命令ID（PID）。
8. Dsi3BusIf_InterfaceVersion_t 和 Dsi3BusIf_Version_t：•Dsi3BusIf_InterfaceVersion_t 定义了一个16位无符号整数类型，用于表示接口版本信息。
•Dsi3BusIf_Version_t 同样定义了一个16位无符号整数类型，用于表示版本信息。
9. Dsi3BusIf_Time_t 和 Dsi3BusIf_Tick_t：•Dsi3BusIf_Time_t 定义了一个16位无符号整数类型，用于表示寄存器中的时间值。
•Dsi3BusIf_Tick_t 定义了一个32位无符号整数类型，用于表示滴答计数表示的时间戳。•Dsi3BusIf_TimeOut_t 也使用 Dsi3BusIf_Tick_t 类型，表示超时值。
10. Dsi3BusIf_sThis_t 和其指针类型：•结构体 Dsi3BusIf_sThis 是DSI3总线层的“this”指针的前置声明。
•Dsi3BusIf_sThis_t 是对 Dsi3BusIf_sThis 结构体的类型定义。•Dsi3BusIf_pThis_t 是指向 Dsi3BusIf_sThis_t 结构体的指针。•Dsi3BusIf_cpThis_t 是指向 Dsi3BusIf_sThis_t 结构体的常量指针。
*/


/***************************************************************************//**
 * @brief Enumeration for DSI3 Driver interfaces.
 ******************************************************************************/
enum Dsi3BusIf_eInterfaceIds
{
  Dsi3_IfId_BUS         = 0,  /**< BUS Layer Interface ID. */
  Dsi3_IfId_HWMODULE    = 1,  /**< BUS Layer hardware module Interface ID. */
  Dsi3_IfId_Count       = 2   /**< Actual count of available interfaces ID. */
};

typedef enum Dsi3BusIf_eInterfaceIds Dsi3BusIf_InterfaceIds_t; /**< Typedef of Dsi3_eInterfaceIds. */


/* **************************************************************************//**
 *
 * @brief Command and Response Mode - Command Format  
 * *****************************************************************************/
#pragma pack(push, 4)
struct Dsi3Bus_CrmCommandFields
{
    Dsi3BusIf_ByteData_t                                CRC;                                            /**<  CRM CRC */
    Dsi3BusIf_ByteData_t                                RegisterData;                                   /**<  CRM RegisterData */
    Dsi3BusIf_ByteData_t                                ExtendedData;                                   /**<  CRM Extended Data */
    Dsi3BusIf_ByteData_t                                Command                 : 4;                    /**<  CRM Command */
    Dsi3BusIf_ByteData_t                                PhysicalAddress         : 4;                    /**<  CRM NAD */
};    
#pragma pack(pop)

typedef struct  Dsi3Bus_CrmCommandFields     Dsi3Bus_CrmCommandFields_t;
typedef         Dsi3Bus_CrmCommandFields_t*  Dsi3Bus_pCrmCommandFields_t;
typedef const	Dsi3Bus_CrmCommandFields_t*	Dsi3Bus_cpCrmCommandFields_t;


#pragma pack(push, 4)
union Dsi3Bus_uCrmCommand                                                                               /**<  Union of CRM Command Buffer*/
{
    Dsi3Bus_CrmCommandFields_t                          Fields;                                         /**<  CRM Command Fields */
    Dsi3BusIf_ByteData_t                                Bytes[(4u)];               /**<  CRM Command Bytes */
    Dsi3BusIf_DWordData_t                               Value;                                          /**<  CRM Command Value */
};
#pragma pack(pop)
typedef union   Dsi3Bus_uCrmCommand            Dsi3Bus_CrmCommand_t;                                    /**< Typedef of Dsi3Bus_uCrmCommand */
typedef         Dsi3Bus_CrmCommand_t*          Dsi3Bus_pCrmCommand_t;                                   /**< Typedef of pointer to Dsi3Bus_CrmCommand_t */
typedef const   Dsi3Bus_CrmCommand_t*          Dsi3Bus_cpCrmCommand_t;                                  /**< Typedef of pointer to Dsi3Bus_CrmCommand_t */

/* Command and Response Mode - Response Format */
#pragma pack(push, 4)
union Dsi3Bus_uCrmResponse                                                                              /**<  Union of CRM Response Buffer */
{
  #pragma pack(push, 4)
  struct
  {
    Dsi3BusIf_ByteData_t                  CRC;                                            /**<  CRM CRC */
    Dsi3BusIf_ByteData_t                  RegisterData;                                   /**<  CRM RegisterData */
    Dsi3BusIf_ByteData_t                  ExtendedData;                                   /**<  CRM Extended Data */
    Dsi3BusIf_ByteData_t                  Status                  : 4;                    /**<  CRM Command */
    Dsi3BusIf_ByteData_t                  PhysicalAddress         : 4;                    /**<  CRM SlaveID */
  } Fields;
  #pragma pack(pop)
  Dsi3BusIf_ByteData_t                    Bytes[(4u)];               /**<  CRM Response Bytes */
  Dsi3BusIf_DWordData_t                   Value;                                          /**<  CRM Response Value */
};
#pragma pack(pop)
typedef union  Dsi3Bus_uCrmResponse            Dsi3Bus_CrmResponse_t;                      /**< Typedef of Dsi3Bus_uCrmResponse */
typedef        Dsi3Bus_CrmResponse_t*          Dsi3Bus_pCrmResponse_t;                     /**< Typedef of pointer to Dsi3Bus_CrmResponse_t */
typedef const  Dsi3Bus_CrmResponse_t*          Dsi3Bus_cpCrmResponse_t;                    /**< Typedef of pointer to Dsi3Bus_CrmResponse_t */

/*
此段代码定义了DSI3驱动接口相关的枚举类型、结构体和联合体。1. Dsi3BusIf_eInterfaceIds:•枚举类型，定义了DSI3总线接口的ID，包括BUS层接口ID（Dsi3_IfId_BUS）和硬件模块接口ID（Dsi3_IfId_HWMODULE）。
2. Dsi3Bus_CrmCommandFields_t:•结构体，用于表示DSI3命令模式（Command and Response Mode, CRM）的命令格式。包含CRC校验、寄存器数据、扩展数据、命令标识和物理地址（NAD）等字段。
3. Dsi3Bus_uCrmCommand:•联合体，包含了CRM命令缓冲区的多种表示形式，包括命令字段（Fields）、字节数组（Bytes）和双字数据（Value）。可以通过选择不同的成员访问CRM命令的不同方面。
4. Dsi3Bus_CrmResponse_t:•联合体，类似于命令格式，用于表示CRM响应缓冲区。它同样包含了CRC校验、寄存器数据、扩展数据、状态标识和从设备ID（SlaveID）等字段，并提供了字节数组和双字数据两种访问方式。
以上定义的结构体和联合体主要用于构建和解析DSI3总线上的命令和响应消息，确保数据传输的正确性和完整性。
通过定义指针类型（如Dsi3Bus_pCrmCommandFields_t、Dsi3Bus_cpCrmCommandFields_t、Dsi3Bus_pCrmCommand_t、Dsi3Bus_cpCrmCommand_t等），可以在程序中方便地操作这些命令和响应结构。
同时，使用#pragma pack(push, 4)和#pragma pack(pop)来控制结构体和联合体的内存对齐，确保数据按4字节边界对齐，避免因编译器默认对齐策略
*/
/* **************************************************************************//**
 * @brief DSI3 communication modes enumeration
 * *****************************************************************************/
enum Dsi3BusIf_eCommunicationMode
{
  Dsi3BusIf_eCOMM_COMMANDRESPONSEMODE         = 0u,                                       /**<  Communication Mode CRM */
  Dsi3BusIf_eCOMM_PERIODICDATACOLLECTIONMODE  = 1u,                                       /**<  Communication Mode PDCM */
  Dsi3BusIf_eCOMM_DISCOVERYMODE               = 2u                                        /**<  Communication Mode Discovery Mode */
};

typedef enum   Dsi3BusIf_eCommunicationMode   Dsi3BusIf_eCommunicationMode_t;             /**<  Typedef of Dsi3If_eState. */


/* **************************************************************************//**
 * @brief DSI3 mode state enumeration
 * *****************************************************************************/
enum Dsi3BusIf_eState
{
  Dsi3BusIf_eSTATE_IDLE                                 = 0u,                             /**<  Bus is receiving data */
  Dsi3BusIf_eSTATE_ANSWERING                            = 1u,                             /**<  Bus is transmiting data. */
  Dsi3BusIf_eSTATE_WAIT_FOR_DISC_PULSE                  = 2u,                             /**<  Bus waits for Discovery Pulse. */
  Dsi3BusIf_eSTATE_PDCMPREPAREBUFFER                    = 3u,                             /**<  PDCM response needs to be set up */
  Dsi3BusIf_eSTATE_RESPONSE_PROCESSED                   = 4u                              /**<  Current master request has been processed but not notified to the upper layers  - processing another master request while in this state will result in TaskToSlow error */
};

typedef enum Dsi3BusIf_eState Dsi3BusIf_eState_t;                                         /**<  Typedef of Dsi3If_eState. */


/* **************************************************************************//**
 * @brief DSI3 RCC chip time enumeration
 * *****************************************************************************/
enum Dsi3BusIf_eRCC_Chiptime
{
  Dsi3BusIf_eRCC_Chiptime_3US = 0u,                                                       /**< RCC Chiptime 3us */
  Dsi3BusIf_eRCC_Chiptime_4US = 1u,                                                       /**< RCC Chiptime 4us */
  Dsi3BusIf_eRCC_Chiptime_5US = 2u,                                                       /**< RCC Chiptime 5us */
  Dsi3BusIf_eRCC_Chiptime_6US = 3u                                                        /**< RCC Chiptime 6us */
};

typedef enum  Dsi3BusIf_eRCC_Chiptime   Dsi3BusIf_ChipTime_t;                             /**<  Data type configured RCC chiptime */


/* **************************************************************************//**
 * @brief DSI3 RCC slope selection enumeration
 * *****************************************************************************/
enum Dsi3BusIf_eRCC_Slope 
{
  Dsi3BusIf_eRCC_Slope_1us          = 0u,
  Dsi3BusIf_eRCC_Slope_2us          = 1u,
  Dsi3BusIf_eRCC_Slope_3us          = 2u,
  Dsi3BusIf_eRCC_Slope_4us          = 3u,
  Dsi3BusIf_eRCC_Slope_6us          = 4u
};

typedef enum Dsi3BusIf_eRCC_Slope Dsi3BusIf_RCC_Slope_t;                                  /**<  Data type configured RCC slope selection */


/* **************************************************************************//**
 * @brief DSI3 RCC current waveform enumeration
 * *****************************************************************************/
enum Dsi3BusIf_eRCC_Curve 
{
  Dsi3BusIf_eRCC_Curve_Rounded      = 0u,
  Dsi3BusIf_eRCC_Curve_Linear       = 1u
};

typedef enum Dsi3BusIf_eRCC_Curve Dsi3BusIf_RCC_Curve_t;                                  /**<  Data type configured RCC current waveform selection */

/*
这段代码定义了DSI3总线接口相关的枚举类型：1. Dsi3BusIf_eCommunicationMode:•该枚举描述了DSI3通信模式，包括命令响应模式（CRM）、周期数据采集模式（PDCM）和发现模式（Discovery Mode）。
2. Dsi3BusIf_eCommunicationMode_t:•将 Dsi3BusIf_eCommunicationMode 枚举类型做了typedef，方便后续引用。
3. Dsi3BusIf_eState:•该枚举列举了DSI3总线接口可能的状态，包括空闲（idle）、响应中（answering）、等待发现脉冲（wait_for_disc_pulse）、PDCM响应准备（pdcmpreparebuffer）和响应已处理但未通知上层（response_processed）。
4. Dsi3BusIf_eState_t:•类似于前面的通信模式，此处对 Dsi3BusIf_eState 枚举进行了typedef，简化后续引用。
5. Dsi3BusIf_eRCC_Chiptime:•此枚举列举了DSI3 RCC芯片时间的几种可能值，分别是3us、4us、5us和6us。
6. Dsi3BusIf_ChipTime_t:•对 Dsi3BusIf_eRCC_Chiptime 枚举类型进行了typedef，定义为配置好的RCC芯片时间的数据类型。
这些枚举类型和typedef为DSI3总线接口的通信模式、状态和RCC芯片时间提供了统一的、易于理解和使用的类型定义，便于在实际编程过程中进行状态判断、模式切换和时间配置等工作。
*/
/* **************************************************************************//**
 * @brief DSI3 RCC current offset value enumeration
 * *****************************************************************************/
enum Dsi3BusIf_eRCC_CurrentOffset 
{
  Dsi3BusIf_eRCC_CurrentOffset_0uA = 0u,
  Dsi3BusIf_eRCC_CurrentOffset_1uA = 1u,
  Dsi3BusIf_eRCC_CurrentOffset_2uA = 2u,
  Dsi3BusIf_eRCC_CurrentOffset_3uA = 3u,
  Dsi3BusIf_eRCC_CurrentOffset_4uA = 4u,
  Dsi3BusIf_eRCC_CurrentOffset_5uA = 5u,
  Dsi3BusIf_eRCC_CurrentOffset_6uA = 6u,
  Dsi3BusIf_eRCC_CurrentOffset_7uA = 7u
};

typedef enum Dsi3BusIf_eRCC_CurrentOffset Dsi3BusIf_RCC_CurrentOffset_t;                  /**<  Data type configured RCC current offset value */

/* **************************************************************************//**
 * @brief DSI3 FCC bit timing enumeration
 * *****************************************************************************/
enum Dsi3BusIf_eFCC_TBit 
{
  Dsi3BusIf_eFCC_TBit_08us = 0u,
  Dsi3BusIf_eFCC_TBit_16us = 1u,
  Dsi3BusIf_eFCC_TBit_32us = 2u,
  Dsi3BusIf_eFCC_TBit_8us  = 3u
};

typedef enum Dsi3BusIf_eFCC_TBit Dsi3BusIf_FCC_TBit_t;                                    /**<  Data type configured FCC bit time selection */

/* **************************************************************************//**
 * @brief DSI3 debounce value
 * *****************************************************************************/

typedef      dsi3_DebounceValue_t      Dsi3BusIf_DebounceValue_t;                         /**<  Data type configured debounce value */

/***************************************************************************//**
 * @brief An enumeration indicating how to proceed according to a received CMD
 ******************************************************************************/
enum Dsi3BusIf_eCmdIdAction
{
  Dsi3BusIf_eCMDACT_IGNORE                               = 0u,                            /**<  Invalid or unknown cmd ID. (Bus driver continues to wait for next break) */
  Dsi3BusIf_eCMDACT_RESPONSE                             = 1u                             /**<  This cmd ID indicates the cmd can be processed normally. */
} ;

typedef enum Dsi3BusIf_eCmdIdAction Dsi3BusIf_CmdIdAction_t;

/* **************************************************************************//**
 * @brief DSI3 DISCOVERY mode status enumeration
 * *****************************************************************************/
enum Dsi3BusIf_eDiscoveryModeStatus
{
  Dsi3BusIf_eDISCSTAT_STARTED                           = 0u,                             /**< State Discovery Mode has started */
  Dsi3BusIf_eDISCSTAT_ADDRESSED                         = 1u,                             /**< State Discovery Mode Slave addressed */
  Dsi3BusIf_eDISCSTAT_TERMINATED                        = 2u                              /**< State Discovery Mode has terminated */
};
typedef enum  Dsi3BusIf_eDiscoveryModeStatus          Dsi3BusIf_eDiscoveryModeStatus_t;
typedef       Dsi3BusIf_eDiscoveryModeStatus_t        Dsi3BusIf_DiscoveryModeStatus_t;    /**<  Data type discovery mode status */
/* *****************************************************************************
 * @brief DSI3 BUS layer error enumerator
 * *****************************************************************************/

/**
 * @brief Error Codes
 */
enum Dsi3BusIf_eErrorCodes
{
  Dsi3BusIf_ERR_STATUS_OK                               = 0u,                     /**<  No error at all. */

  Dsi3BusIf_ERR_INIT                                    = 100u + 0,           /**<  Initialization error */
  Dsi3BusIf_ERR_HW_FAIL                                 = 100u + 1,           /**<  Hardware failure */
  Dsi3BusIf_ERR_NO_HANDLER                              = 100u + 2,           /**<  Missing handler callback */

  Dsi3BusIf_ERR_START_ERR_EVT                           = 100u + 3,           /**<  Corrupted or invalid sync byte received */
  
  Dsi3BusIf_ERR_PDCM_ERROR                              = 100u + 4,           /**<  Non sync during pdcm detected */
  Dsi3BusIf_ERR_FCC_ERROR                               = 100u + 5,           /**<  Received data expose framing error */
  Dsi3BusIf_ERR_DISC_ERROR                              = 100u + 6,
  Dsi3BusIf_ERR_BUFFER_ERROR                            = 100u + 7,           /**<  Data buffer setup incorrectly */

  Dsi3BusIf_ERR_CRC                                     = 100u + 8,           /**<  DSI3 CRC error */
  
  Dsi3BusIf_ERR_TASK_TOO_SLOW                           = 100u + 9,           /**<  DSI3 Task error */
  Dsi3BusIf_ERR_SLAVEID_OUT_OF_RANGE                    = 100u + 10,          /**<  DSI3 NAD error */
  Dsi3BusIf_ERR_DISC_VERIFY_ERROR                       = 100u + 11,          /**< DSI3 DISCovery mode unexpected current detected */
  Dsi3BusIf_ERR_IMPL_ERROR_AREA                         = 100u + (32u/2) /**<  Any additional implementation specific errors start here. */
  
};

typedef enum Dsi3BusIf_eErrorCodes Dsi3BusIf_ErrorCodes_t;

/* ****************************************************************************/
/* **************************** GLOBAL VARIABLES ******************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ********************* EXTERNAL FUNCTIONS / INTERFACE ***********************/
/* ****************************************************************************/


/** @} dsi3_Driver_interfaces */

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/



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
  uint16_t                        halfwords[(5u)];
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
  uint16_t                        halfwords[(2u)];
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
  uint16_t                        halfwords[(11u)];
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
  uint16_t                        halfwords[(14u)];
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
  uint16_t                        halfwords[(2u)];
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
  uint16_t                        halfwords[(2u)];
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
  uint16_t                        halfwords[(11u)];
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
  uint16_t                        halfwords[(2u)];
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
  uint16_t                        halfwords[(4u)];
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
  uint16_t                        halfwords[(10u)];
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
  uint16_t                        halfwords[(3u)];
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
  uint16_t                        halfwords[(2u)];
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
  uint16_t                              halfwords[((5u) + (2u) + (3*(11u)) + (2*(14u)) + (2u) + (2u) + (11u) + (2u) + (4u) + (10u) + (3u) + (2u))];          /**< 16 bit array for direct access to the struct */
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
  Meas_sEevalStdDataPacketFormat0         std_type0[(50u)];     /**< EEVAL Data packet format for standard path for EEVAL_CTRL.eeval_dma_val=0 */
  Meas_sEevalStdDataPacketFormat1         std_type1[(50u)];     /**< EEVAL Data packet format for standard path for EEVAL_CTRL.eeval_dma_val=1 */
  Meas_sEevalAdvDataPacketFormat          adv[(2*(20u))]; /**< EEVAL Data packet for advanced Path 1 & 2 */
  uint16_t                                lab[(((3u) * (2*(20u))) + (600u))];         /**< Raw data signals for lab mode */
  uint16_t                                raw[(((3u) * (2*(20u))) + (600u))];         /**<  */
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
  uint16_t                                DummyBuffer[(32u)];

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


/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

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

/* ------------------------------------------------------------------- */
/** @file def_brg.h
 *
 * @brief Helper definitions for BRG hardware module.
 *
 * Purpose:
 * Provide register access and register value definitions 
 * for BRG hardware module
 *
 * Demo Code Usage Restrictions:
 * Elmos Semiconductor AG provides this source code file simply and solely for
 * IC evaluation purposes in laboratory and this file must not be used for other 
 * purposes or within non laboratory environments. Especially, the use or the
 * integration in production systems, appliances or other installations is
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
 * @section history_sec Revision History
 *
 * @verbatim
 * -------------------------------------------------------------------
 * Date     B/F Who Ver  Comment
 * -------------------------------------------------------------------
 * 17/05/23 (F) poe 1001 first creation
 * -------------------------------------------------------------------
 * @endverbatim
 *
 * @creator      poe
 * @created      2017/05/23
 *
 * @project      524.17
 * @requested    ELMOS
 * @inspector    -
 * @verification -
 * @version      $Revision: 392 $
 *
 *
 * $State: Exp $
 * $Author: siko $
 *
 * Additional markers:
 *
 */
//################################################################################
//  Helper defines
//################################################################################


/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

enum brg_eIncrementSelect
{
  brg_eIncrementSelect_LinPeriod        = 0u,
  brg_eIncrementSelect_LinFreq          = 1u
};

typedef enum brg_eIncrementSelect brg_IncrementSelect_t;

enum brg_eBurstStatus
{
  brg_eBurstStatus_Finished             = 0u,
  brg_eBurstStatus_Running              = 1u,
  brg_eBurstStatus_Aborted              = 2u 
};

typedef enum brg_eBurstStatus brg_BurstStatus_t;

enum brg_eBurstType
{
  brg_eBurstType_FixedFreqBrst          = 0u,
  brg_eBurstType_FreqChirp              = 1u,             
  brg_eBurstType_FSKBrst                = 2u,
  brg_eBurstType_MSKBrst                = 3u
};

typedef enum brg_eBurstType brg_BurstType_t;


enum brg_eTDRSourceSelectMode
{
  brg_eTDRSourceSelectMode_Normal       = 0u,
  brg_eTDRSourceSelectMode_Reduced      = 1u
};

typedef enum brg_eTDRSourceSelectMode brg_TDRSourceSelectMode_t;

enum brg_eTDRStatus
{
  brg_eTDRStatus_Normal                 = 0u,
  brg_eTDRStatus_Error                  = 1u
};

typedef enum brg_eTDRStatus brg_TDRStatus_t;

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* ***************************** BURST CONTROL ********************************/
/* ****************************************************************************/





/* ****************************************************************************/
/* ***************************** BURST CONFIG *********************************/
/* ****************************************************************************/













/* ****************************************************************************/
/* ******************** TRANS DRIVER CURRENT CONTROL **************************/
/* ****************************************************************************/








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
/* ******************** FORWARD DECLARATIONS / PROTOTYPES *********************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

uint16_t util_calculateDmaMemoryOffset(void* pointer)
{
  uint32_t tmp  = (uint32_t)(uint32_t*)pointer;          /* get value of pointer */
  /* check if the pointer is located in SRAM memory */
  if((tmp >= (0x20000000u)) && (tmp < (0x30000000u)))
  {
    tmp   = tmp & 0x0000FFFFu;               /* Get memory offset */
  }
  else
  {
    /* the pointer was not in range. set to default ... */
    tmp   = 0u;
    /* ... and call the ErrorHandler */
    err_ErrorHandlerExt(85, ERR_MODLIST_UTIL);;
  }
  return (uint16_t)tmp;
}


/* **************************************************************************//**
 * @brief
 * Calculate the currently set transducer frequency
 *
 * @return      currently set transducer_frequency
 * ****************************************************************************/
uint32_t util_CalcBurstFrequency(void)
{
  /* calculate burst frequency
   *
   * formula:
   * fc= BRG_FC* f_STEP
   * */
  
  /*-> 18/04/09/frk: (JIRA SMA52417-87) corrected calculation (division by 1000 was missing) */
  return ((((BRG_Type *) 0x50000300UL)->BRG_FC . bit).f_c * (5722u)) / 1000;
  /*<- 18/04/09/frk */
}


