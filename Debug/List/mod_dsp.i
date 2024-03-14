/***************************************************************************//**
  * @file mod_dsp.c
  * @brief DSP configuration and access module
  *
  * Purpose:
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
  * @section history_sec Revision History
  * $Id: mod_dsp.c 394 2019-01-23 15:20:39Z siko $
  *
  * @verbatim
  * -------------------------------------------------------------------
  * Date     B/F Who Comment
  * ------------------------------------------------------------------- 
  * 17/05/27 (F) POE initial version
  * -------------------------------------------------------------------
  * @endverbatim
  * 
  *
  * @creator      POE
  * @created      2017/07/02
  * 
  * @project      524.17
  * @requested    -
  * @inspector    - 
  * @verification -
  * @version      $Revision: 394 $
  * 
  * 
  * $State: Exp $   
  * $Author: siko $
  * $Date: 2019-01-23 16:20:39 +0100 (Mi, 23 Jan 2019) $

  * $Locker:  $
  * $Url:   $
  *
  * Additional markers:
  *
  *
  *
  */

/*################################################################################
  DSP
  ################################################################################
*/


/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
/* *************************************************************************//**
 * @file		mod_dsp.h
 *
 * @creator		poe
 * @created		07.02.2017
 * @sdfv      Elmos Flow
 *
 * @brief  		DSP configuration and access module (header)
 *
 * @purpose
 *
 * The DSP module 
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
 * $Id: mod_dsp.h 394 2019-01-23 15:20:39Z siko $
 *
 * $Revision: 394 $
 *
 * *****************************************************************************/


/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
/* ------------------------------------------------------------------- */
/** @file def_dsp.h
 *
 * @brief Helper definitions for DSP hardware module.
 *
 * Purpose:
 * Provide register access and register value definitions 
 * for DSP hardware module
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



















	







/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/
enum dsp_eRTMStatus
{
  dsp_eRTM_ONGOING      = 0u,
  dsp_eRTM_FINISHED     = 1u
};

typedef enum dsp_eRTMStatus dsp_RTMStatus_t;

struct dsp_sEevalDmaCtrl
{
  volatile uint16_t  length     :  8;               
  volatile uint16_t  wrap_off   :  1;               
};  

typedef struct dsp_sEevalDmaCtrl dsp_EevalDmaCtrl_t;

struct dsp_sEdiDmaCtrl
{
  volatile uint16_t  length     :  8;               
  volatile uint16_t  wrap_off   :  1;               
} ;      

typedef struct dsp_sEdiDmaCtrl dsp_EdiDmaCtrl_t;


enum dsp_eEDI_CH
{
  dsp_eEDI_CH_0                 = 0u,
  dsp_eEDI_CH_1                 = 1u,
  dsp_eEDI_CH_2                 = 2u,
  dsp_eEDI_CH_3                 = 3u
};

typedef enum dsp_eEDI_CH dsp_EDI_CH_t;

enum dsp_eEDISEL_CH0
{
  dsp_eEDISEL_CH0_AMPD_ENV      = 0u,
  dsp_eEDISEL_CH0_ENVP_ENV_RAW  = 1u,
  dsp_eEDISEL_CH0_FILT1         = 2u,
  dsp_eEDISEL_CH0_AATG2_TH      = 3u
};

typedef enum dsp_eEDISEL_CH0 dsp_EDISEL_CH0_t;

enum dsp_eEDISEL_CH1
{
  dsp_eEDISEL_CH1_AMPD_ENV      = 0u,
  dsp_eEDISEL_CH1_ENVD_RAW      = 1u,
  dsp_eEDISEL_CH1_ENVD_PHI      = 2u,
  dsp_eEDISEL_CH1_CONF1         = 3u
};

typedef enum dsp_eEDISEL_CH1 dsp_EDISEL_CH1_t;

enum dsp_eEDISEL_CH2
{
  dsp_eEDISEL_CH2_ENV_I         = 0u,
  dsp_eEDISEL_CH2_ENVD_PHID     = 1u,
  dsp_eEDISEL_CH2_FILT2         = 2u,
  dsp_eEDISEL_CH2_AATG_TH       = 3u
};

typedef enum dsp_eEDISEL_CH2 dsp_EDISEL_CH2_t;

enum dsp_eEDISEL_CH3
{
  dsp_eEDISEL_CH3_ENV_Q         = 0u,
  dsp_eEDISEL_CH3_ATG_TH        = 1u,
  dsp_eEDISEL_CH3_STG_TH        = 2u,
  dsp_eEDISEL_CH3_CONF2         = 3u
};

typedef enum dsp_eEDISEL_CH3 dsp_EDISEL_CH3_t;

enum dsp_eEEVAL_PacketFormat
{
  dsp_eEEVAL_32BIT              = 0u,
  dsp_eEEVAL_26BIT              = 1u
};

typedef enum dsp_eEEVAL_PacketFormat dsp_EEVAL_PacketFormat_t;


struct dsp_sEEVAL_Packet_32Bit
{
  uint16_t Timestamp            : 16;
  uint16_t ENVP_ENV_RAW         : 14;
  uint8_t  TypeIdentifier       :  2;
} ;

typedef struct dsp_sEEVAL_Packet_32Bit dsp_EEVAL_Packet_32Bit_t;


struct dsp_sEEVAL_Packet_26Bit
{
  uint16_t Timestamp            : 15;
  uint16_t ENVP_ENV_RAW         :  8;
  uint8_t  TypeIdentifier       :  2;
} ;

typedef struct dsp_sEEVAL_Packet_26Bit dsp_EEVAL_Packet_26Bit_t;


enum dsp_eFTC_ConfigSet
{
  dsp_eFTC_FastFiltering0       = 0u,
  dsp_eFTC_FastFiltering1       = 1u,
  dsp_eFTC_FastFiltering2       = 2u,
  dsp_eFTC_ForNPulses_4         = 3u,
  dsp_eFTC_ForNPulses_8         = 4u,
  dsp_eFTC_ForNPulses_12_20     = 5u,
  dsp_eFTC_ForNPulses_24_32     = 6u
};

typedef enum dsp_eFTC_ConfigSet dsp_FTC_ConfigSet_t;


enum dsp_eNFDIRQ_Echos
{
  dsp_eNFDIRQ_2_ECHOS           = 0u,
  dsp_eNFDIRQ_3_ECHOS           = 1u,
  dsp_eNFDIRQ_4_ECHOS           = 2u,
  dsp_eNFDIRQ_5_ECHOS           = 3u
};

typedef enum dsp_eNFDIRQ_Echos dsp_NFDIRQ_Echos_t;


/* *************************************************************************** */
/* *************************** DEFINES AND MACROS **************************** */
/* *************************************************************************** */



/* *************************************************************************** */
/* ****************************** DSP CONTROL ******************************** */
/* *************************************************************************** */






/* *************************************************************************** */
/* ****************************** RFM CONTROL ******************************** */
/* *************************************************************************** */








/* *************************************************************************** */
/* ****************************** RTM/MT CONTROL ***************************** */
/* *************************************************************************** */






/* *************************************************************************** */
/* **************************** ENVELOPE CONTROL ***************************** */
/* *************************************************************************** */











/* *************************************************************************** */
/* ****************************** FTC CONTROL ******************************** */
/* *************************************************************************** */






/* *************************************************************************** */
/* ********************* DIGITAL AMPLIFIER CONTROL *************************** */
/* *************************************************************************** */






/* *************************************************************************** */
/* ***************************** STC CONTROL ********************************* */
/* *************************************************************************** */




/* *************************************************************************** */
/* ********************* STATIC THRESHOLD GENERATION ************************* */
/* *************************************************************************** */





/* *************************************************************************** */
/* ************************** ANALOG GAIN CONTROL **************************** */
/* *************************************************************************** */






/* *************************************************************************** */
/* ************************ ECHO EVALUATION CONTROL ************************** */
/* *************************************************************************** */







/* *************************************************************************** */
/* ************************** ENVELOPE DATA INTERFACE ************************ */
/* *************************************************************************** */







/* *************************************************************************** */
/* ********************** NEAR FIELD DETECTION CONTROL *********************** */
/* *************************************************************************** */










/* *************************************************************************** */
/* **************************** DSP Interrupts ******************************* */
/* *************************************************************************** */





 /* ------------------------------------------------------------------- */
/** @file nvic_InterruptHandler.h
 *
 * @brief NVIC Interrupt handler for interrupt controller implementation.
 *
 * Purpose:
 *  NVIC Interrupt handler for interrupt controller implementation
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

/* ****************************************************************************/
/* **************************** GLOBALE VARIABLES *****************************/
/* ****************************************************************************/
extern const nvic_sInterfaceFunctions_t nvic_InterfaceFunctions;

/* ****************************************************************************/
/* ********************* EXTERNAL FUNCTIONS / INTERFACE ***********************/
/* ****************************************************************************/

/***************************************************************************//**
 * Return pointer to interrupt environment for given exception vector number.
 *
 * @param       vno: Exception vector number
 *
 * @return      Pointer to interrupt environment
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Return pointer to interrupt environment for given exception vector number.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
nvic_pInterruptModuleEnvironmentData_t nvic_GetPointerToEnvironmentData(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * Register interrupt handler and interrupt environment
 *
 * @param       Exception vector number
 *              Interrupt handler callback
 *              Module Environment Data
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Register interrupt handler and interrupt environment for module according to 
 * given exception vector number.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_RegisterModule(nvic_eExceptionVectorNum_t vno, nvic_InterruptCallback_t interrupthandler, nvic_pInterruptModuleEnvironmentData_t moduleenvironmentdata);

/***************************************************************************//**
 * De-register interrupt handling in NVIC
 *
 * @param       Exception vector number
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Disable given module in NVIC. Set interrupt handler function to default 
 * exception handler for system IRQs or default interrupt handler for module 
 * interrupts. Invalidate pointer to interrupt environment.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_DeregisterModule(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * Enable interrupts for module
 *
 * @param       Exception vector number
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Clear pending IRQs and enable IRQs for given module.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_EnableModule(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * Disable interrupts for module
 *
 * @param       Exception vector number
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Check exception vector number for valid range. 
 * Disable IRQs for given module.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_DisableModule(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * Clear pending IRQs for given module.
 *
 * @param       Exception vector number
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Clear pending IRQs for given module.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_ClearPending(nvic_eExceptionVectorNum_t vno);

/***************************************************************************//**
 * Set pending IRQs for given module.
 *
 * @param       Exception vector number
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Set pending IRQs for given module.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_SetPending(nvic_eExceptionVectorNum_t vno);


/***************************************************************************//**
 * Set IRQ priority for given module.
 *
 * @param       Exception vector number
 *              Interrupt priority
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Set IRQ priority for given module.
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_SetModulePriority(nvic_eExceptionVectorNum_t vno, nvic_ePriorityLevels_t prio);

/***************************************************************************//**
 * Globally enable interrupts in NVIC
 *
 * @param       void
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Globally enable interrupts in NVIC
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_EnableMain(void);

/***************************************************************************//**
 * Globally disable interrupts in NVIC
 *
 * @param       void
 *
 * @return      void
 *
 * @pre         (optional) Which are the conditions to call this function? i.e. none
 *
 * @post        (optional) How has the status changed, after the function ran?
 *
 * Globally disable interrupts in NVIC
 *
 * @see        (optional) Crossreference
 *
 ******************************************************************************/
void nvic_DisableMain(void);

/***************************************************************************//**
 * @brief Initialize VIC module
 *
 * @param environmentdata  Pointer to Environment data for VIC module in
 *                         user RAM
 *
 * @pre        VIC (vic_VectorInterruptControl) and SYSS (syss_SystemStateModule)
 *             have to present and initialized.
 *
 * @post       VIC module is configured for use.
 *
 * @detaildesc
 *
 ******************************************************************************/
bool_t nvic_IRQInitialisation(nvic_pInterruptEnvironmentData_t penvironmentdata);


/* ------------------------------------------------------------------- */
/** @file dsp_InterruptHandler.h
 *
 * @brief Module interrupt handler for DSP hardware module.
 *
 * Purpose:
 * This module provides functions for handling DSP interrupts
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

/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/

/***************************************************************************//**
 * DSP IRQ vector numbers
 ******************************************************************************/
typedef enum {
  dsp_IRQ_EEVAL_TLH_EVT                 = 0u,
  dsp_IRQ_EEVAL_THL_EVT                 = 1u,
  dsp_IRQ_EEVAL_MAX_EVT                 = 2u,
  dsp_IRQ_EEVAL_MIN_EVT                 = 3u,
  dsp_IRQ_EEVAL1_MAX_EVT                = 4u,
  dsp_IRQ_EEVAL2_MAX_EVT                = 5u,
  dsp_IRQ_RFM_EVT                       = 6u,
  dsp_IRQ_RTM_EVT                       = 7u,
  dsp_IRQ_NFD_EVT                       = 8u,
  dsp_IRQ_EEVAL_DMA_WRAP                = 9u,
  dsp_IRQ_EEVAL1_DMA_WRAP               = 10u,
  dsp_IRQ_EEVAL2_DMA_WRAP               = 11u,
  dsp_IRQ_EDI0_DMA_WRAP                 = 12u,
  dsp_IRQ_EDI1_DMA_WRAP                 = 13u,
  dsp_IRQ_EDI2_DMA_WRAP                 = 14u,
  dsp_IRQ_EDI3_DMA_WRAP                 = 15u,
  
  dsp_INTERRUPT_VECTOR_CNT              = 16u  /**< Number of available interrupt vectors */
         
} dsp_eInterruptVectorNum_t;

/***************************************************************************//**
 * Pointer to DSP context data
 ******************************************************************************/
typedef void * dsp_pInterruptContextData_t;

/***************************************************************************//**
 * Callback function pointer type
 ******************************************************************************/
typedef void (*dsp_InterruptCallback_t) (dsp_eInterruptVectorNum_t irqsrc, dsp_pInterruptContextData_t contextdata);

/***************************************************************************//**
 * DSP environment data
 ******************************************************************************/
typedef struct dsp_sInterruptEnvironmentData
{
    /** Interrupt vector table of this module             */
    dsp_InterruptCallback_t InterrupVectorTable[dsp_INTERRUPT_VECTOR_CNT];
    
    /** DSP module context data */
    dsp_pInterruptContextData_t ContextData;
    
} dsp_sInterruptEnvironmentData_t;

/***************************************************************************//**
 * Pointer to DSP environment data
 ******************************************************************************/
typedef dsp_sInterruptEnvironmentData_t * dsp_pInterruptEnvironmentData_t;

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
 * @param[in] modulBaseAddress  Pointer to DSP module base address
 * @param[in] irqsrc            IRQ to be enabled
 *
 * @pre       A call back function to the related interrupt should have been
 *            registered with dsp_RegisterInterruptCallback().
 *
 * @post      The related call back function will be called if the desired
 *            interrupt occurs.
 *
 * @detaildesc
 * The DSP IRQ_VENABLE register will be set the related IRQ number and therefore
 * the interrupt will be activated.
 *
 ******************************************************************************/
void dsp_InterruptEnable(dsp_eInterruptVectorNum_t irqsrc);

/***************************************************************************//**
 * @brief Disables an IRQ.
 *
 * @param[in] modulBaseAddress  Pointer to DSP module base address
 * @param[in] irqsrc            IRQ to be disable
 *
 * @post      The interrupt will be disabled and the related callback function
 *            will no longer be called from the interrupt handler.
 *
 * @detaildesc
 * The DSP IRQ_VDISABLE register will be set the related IRQ number and therefore
 * the interrupt will be deactivated.
 *
 ******************************************************************************/
void dsp_InterruptDisable(dsp_eInterruptVectorNum_t irqsrc);

/***************************************************************************//**
 * @brief Registers/Adds callback function to the module interrupt vector table.
 *
 * @param modulBaseAddress  Pointer to DSP module base address
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
void dsp_InterruptRegisterCallback(dsp_eInterruptVectorNum_t irqsrc, dsp_InterruptCallback_t cbfnc);

/***************************************************************************//**
 * @brief Deregisters/deletes callback function from module interrupt vector table.
 *
 * @param modulBaseAddress  Pointer to DSP module base address
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
void dsp_InterruptDeregisterCallback(dsp_eInterruptVectorNum_t irqvecnum);

/***************************************************************************//**
 * @brief Initialize DSP module
 *
 * @param environmentdata  Pointer to Environment data for DSP module in
 *                         user RAM
 *
 * @pre        VIC (vic_VectorInterruptControl) and DSP (dsp_SystemStateModule)
 *             have to presented and initialized.
 *
 * @post       DSP module is configured for use.
 *
 * @detaildesc
 * Initializes the DSP software and hardware module, including the module
 * interrupt vector table. Configures if IRQ nesting is active and if IO2 and
 * IO3 are used as DSPs or not.
 *
 ******************************************************************************/
void dsp_InterruptInitialisation(nvic_cpInterfaceFunctions_t vicIf, dsp_pInterruptEnvironmentData_t environmentdata, dsp_pInterruptContextData_t contextdata);



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
extern nvic_cpInterfaceFunctions_t nvic_IfFuns;

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* *****************************************************************************
 * @brief Initialize DSP module
 *
 * @param none
 *
 * @pre        NVIC (nvic_VectorInterruptControl) has to presented and initialized
 *
 * @post       DSP module is configured for use.
 *
 * @detaildesc
 * Initializes the DSP software and hardware module, including the module
 * interrupt vector table. 
 *
 * *****************************************************************************/
void dsp_Init(void);

/* ****************************************************************************
 * @implementation
 * Register a custom ISR for a specific interrupt
 *
 * @param       irq             target irq
 * @param       cb              pointer to custom isr function
 * @return      TRUE            if assignment successful
 * ****************************************************************************/
bool_t dsp_RegisterCustomInterruptCallback(dsp_eInterruptVectorNum_t irqNum, dsp_InterruptCallback_t cb);



/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/

static dsp_sInterruptEnvironmentData_t dsp_envData; /* DSP interrupt controller environment data */

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* ************************************************************************//**
 * @implementation
 * DSP initialization
 *
 * @param       none
 * @return
 * ****************************************************************************/
void dsp_Init(void)
{     
  /* Initialize DSP IRQ */  
  dsp_InterruptInitialisation(&nvic_InterfaceFunctions,&dsp_envData, ((void *)0));
  
  /* Set module priority level */
  nvic_InterfaceFunctions.SetModulePriority(nvic_CEVT_EXT_IRQ_4, nvic_Priority_Level_1);
}

/* ************************************************************************//**
 * @implementation
 * Register a custom ISR for a specific interrupt
 *
 * @param       irqNum          target irq
 * @param       cb              pointer to custom isr function
 * @return      TRUE            if assignment successful
 * ****************************************************************************/
bool_t dsp_RegisterCustomInterruptCallback(dsp_eInterruptVectorNum_t irqNum,  dsp_InterruptCallback_t cb)
{
  bool_t retVal = 0;

  if (dsp_INTERRUPT_VECTOR_CNT > irqNum) 
  {
    dsp_InterruptRegisterCallback((dsp_eInterruptVectorNum_t)irqNum, cb);
    retVal = 1;
  }

  return retVal;
}

