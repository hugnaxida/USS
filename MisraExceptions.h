// PRQA S 292 ++
/* *************************************************************************//**
 * @file                MisraExceptions.h
 *
 * @creator             StSl
 * @created             17.10.2017
 * @sdfv
 *
 * @brief               Project dependent MISRA rule exceptions
 *
 * *****************************************************************************
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
 * *****************************************************************************
 *
 * Revision: $Revision: 406 $
 * $Id: MisraExceptions.h 406 2019-02-08 15:49:42Z siko $
 *
 * ****************************************************************************/
// PRQA S 292 --

#ifndef LIN_MISRA_H_
#define LIN_MISRA_H_

/*  
* Exception:
* Msg(0292) [I] Source file '%s' has comments containing one of the characters '$', '@' or '`'.
*
* Circumstances and justification:
* code documentation tools like doxygen and many other tools. It does not affect the code.
* 
* Potential consequences:
* Wrong displayed letters in comments
*
* Alternative safety assurance:
* It has no effects on compiled sw
*/
// PRQA S 0292 ++

/*
* Exception:
* Msg(0635) [E] Bit-field %s in %s has been declared with a type not explicitly supported.
*
* Circumstances and justification:
* The used Compiler supports bit-fields
* with other types then int. This language extension is not portable but supported
* by most of the modern c-compilers.
* 
* Potential consequences:
* Unportable extension, if the compiler does not support this language extension.
*
* Alternative safety assurance:
* None, the compiler won't compile the code if this language extension is not supported.
*/ 
// PRQA S 0635 ++
   
/*
* Exception:
* Msg(0750) A union type specifier has been defined.
*
* Circumstances and justification:
* There are useful cases, where the usage of a union is helpful and efficient. Like
* access to an register on bit level.
* 
* Potential consequences:
* none
*
* Alternative safety assurance:
* none
*/
//PRQA S 0750 ++
   
/*  
* Exception:
* Msg(0857) [L] Number of macro definitions exceeds 1024 - program does not 
* conform strictly to ISO:C90. 
*
* Circumstances and justification: 
* The used compiler has been proven to accept more than 1024 macro definitions
* within one header file, which is supported by C99.
* 
* Potential consequences:
* Compiler does not know all defines
*
* Alternative safety assurance:
* None
*/
// PRQA S 0857 ++

/*  
* Exception:
* Msg(2053) This block comment appears to comment out source code.
*
* Circumstances and justification:
* This rule is global deactivated, because this is Demo-Code and should also give source-code examples.
* Also the Disclaimer is affected by this rule
* 
* Potential consequences:
* When uncomment the source-code, it is not garanteed that the code works correctly because it is not tested and analysed.
*
* Alternative safety assurance:
* This code is Demo-Code and it is not assured that the software is working safe.
*/
// PRQA S 2053 ++
   
/*
 * Msg(0306) [I] Cast between a pointer to object and an integral type.
 *
 * According to QA-C help "this type of operation is not uncommon in embedded
 * software applications where memory mapped I/O ports must be addressed."
 */
// PRQA S 0306 ++

#endif /* LIN_MISRA_H_ */
