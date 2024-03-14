/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2008-2017 IAR Systems AB.
 *
 * $Revision: 392 $
 *
 **************************************************/

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY, which
; is where to find the SP start value.
; If vector table is not located at address 0, the user has to initialize the  NVIC vector
; table register (VTOR) before using interrupts.
;
; Cortex-M version
;

        MODULE  ?cstartup

        PUBLIC  __iar_program_start
        EXTERN  __cmain
        EXTERN  __vector_table
        EXTWEAK __iar_init_core
        EXTWEAK __iar_init_vfp
        IMPORT  CSTACK$$Base,CSTACK$$Length

        SECTION .text:CODE:REORDER(2)
        THUMB
        
__iar_program_start:
        FUNCALL __iar_program_start, __iar_init_core
        BL      __iar_init_core
        

; config gpio 0 output
;        LDR     R0, =0x50000002
;        LDRH    R1, [R0]
;        MOVS    R2, #1
;        ORRS    R2, R2, R1
;        STRH    R2, [R0]
;set GPIO0
;        LDR     R0, =0x50000000
;        LDRH    R1, [R0]
;        MOVS    R2, #1
;        ORRS    R2, R2, R1
;        STRH    R2, [R0]
; start stack initialization 
        LDR     R0, =CSTACK$$Base         ;start stack
        LDR     R1, =CSTACK$$Length       ;stack size
        LDR     R2, =0x51C051C0           ;pattern
        MOVS    R3, R2
        MOVS    R4, R2
        MOVS    R5, R2
        SUBS    R1, R1, #16
        BCC.N   twobyteloop
fourbyteloop:
        SUBS    R1, R1, #16
        STM     R0!, {R2-R5}
        BCS.N   fourbyteloop
twobyteloop:
        LSLS    R1, R1, #29
        BCC.N   onebyteloop
        STM     R0!, {R2, R3}
onebyteloop:
        BPL.N   zerobyteloop
        STM     R0!, {R2}
zerobyteloop:
        NOP
; end stack initialization
; clear GPIO0
;        LDR     R0, =0x50000000
;        LDRH    R1, [R0]
;        MOVS    R2, #0
;        ANDS    R2, R2, R1
;        STRH    R2, [R0]

        FUNCALL __iar_program_start, __cmain
        BL      __cmain

        REQUIRE __vector_table


        END
