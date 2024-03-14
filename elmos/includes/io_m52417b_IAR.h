
/****************************************************************************************************//**
 * @file     m52417b.h
 *
 * @brief    CMSIS Cortex-M0 Peripheral Access Layer Header File for
 *           m52417b from .
 *
 * @version  V1.0
 * @date     21. March 2018
 *
 * @note     Generated with SVDConv V2.87l 
 *           from CMSIS SVD File 'm52417b.svd' Version 1.0,
 *
 * @note:    Generated for MISRA Compliance, this File is NOT CMSIS compliant.
 *******************************************************************************************************/



/** @addtogroup m52417b
  * @{
  */

#ifndef M52417B_H
#define M52417B_H

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum {
/* -------------------  Cortex-M0 Processor Exceptions Numbers  ------------------- */
  Reset_IRQn                    = -15,              /*!<   1  Reset Vector, invoked on Power up and warm reset                 */
  NonMaskableInt_IRQn           = -14,              /*!<   2  Non maskable Interrupt, cannot be stopped or preempted           */
  HardFault_IRQn                = -13,              /*!<   3  Hard Fault, all classes of Fault                                 */
  SVCall_IRQn                   =  -5,              /*!<  11  System Service Call via SVC instruction                          */
  PendSV_IRQn                   =  -2,              /*!<  14  Pendable request for system service                              */
  SysTick_IRQn                  =  -1,              /*!<  15  System Tick Timer                                                */
/* ---------------------  m52417b Specific Interrupt Numbers  --------------------- */
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
#define __CM0_REV                 0x0000            /*!< Cortex-M0 Core Revision                                               */
#define __MPU_PRESENT                  0            /*!< MPU present or not                                                    */
#define __NVIC_PRIO_BITS               2            /*!< Number of Bits used for Priority Levels                               */
#define __Vendor_SysTickConfig         0            /*!< Set to 1 if different SysTick Config is used                          */
/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm0_IAR.h"                           /*!< Cortex-M0 processor and core peripherals                              */
//#include "system_m52417b.h"                         /*!< m52417b System                                                        */


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
    __IO uint16_t  reg;                             /*!< CONTROL register                                                      */
    
    struct {
      __IO uint16_t  run_enable :  1;               /*!< run_enable bitfield                                                   */
      __O  uint16_t  restart    :  1;               /*!< restart bitfield                                                      */
           uint16_t             :  6;
      __IO uint16_t  password   :  8;               /*!< password bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } CONTROL;
  
  union {
    __IO uint16_t  reg;                             /*!< WINDOW register                                                       */
    
    struct {
      __IO uint16_t  size       :  4;               /*!< size bitfield                                                         */
      __IO uint16_t  enable     :  1;               /*!< enable bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } WINDOW;
  
  union {
    __IO uint16_t  reg;                             /*!< PRESCALER register                                                    */
    
    struct {
      __IO uint16_t  val        :  8;               /*!< val bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } PRESCALER;
  
  union {
    __IO uint16_t  reg;                             /*!< RELOAD register                                                       */
    
    struct {
      __IO uint16_t  val        : 16;               /*!< val bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } RELOAD;
  
  union {
    __I  uint16_t  reg;                             /*!< COUNTER register                                                      */
    
    struct {
      __I  uint16_t  val        : 16;               /*!< val bitfield                                                          */
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
    __IO uint16_t  reg;                             /*!< CONTROL register                                                      */
    
    struct {
      __IO uint16_t  sys_clk_sel:  2;               /*!< sys_clk_sel bitfield                                                  */
    } bit;                                          /*!< BitSize                                                               */
  } CONTROL;
  __I  uint16_t  RESERVED;
  
  union {
    __I  uint16_t  reg;                             /*!< RESET_STATUS register                                                 */
    
    struct {
      __I  uint16_t  vcore_ok   :  1;               /*!< vcore_ok bitfield                                                     */
      __I  uint16_t  sys_clk_fail:  1;              /*!< sys_clk_fail bitfield                                                 */
      __I  uint16_t  cpu_lockup :  1;               /*!< cpu_lockup bitfield                                                   */
      __I  uint16_t  debug_reset:  1;               /*!< debug_reset bitfield                                                  */
      __I  uint16_t  software   :  1;               /*!< software bitfield                                                     */
      __I  uint16_t  sram_parity:  1;               /*!< sram_parity bitfield                                                  */
      __I  uint16_t  otp_ecc_fail:  1;              /*!< otp_ecc_fail bitfield                                                 */
      __I  uint16_t  watchdog_window:  1;           /*!< watchdog_window bitfield                                              */
      __I  uint16_t  watchdog   :  1;               /*!< watchdog bitfield                                                     */
      __I  uint16_t  watchdog_zero:  1;             /*!< watchdog_zero bitfield                                                */
      __I  uint16_t  crc16_mismatch:  1;            /*!< crc16_mismatch bitfield                                               */
      __I  uint16_t  trim_parity:  1;               /*!< trim_parity bitfield                                                  */
    } bit;                                          /*!< BitSize                                                               */
  } RESET_STATUS;
  
  union {
    __O  uint16_t  reg;                             /*!< RESET_STATUS_CLEAR register                                           */
    
    struct {
      __O  uint16_t  clear      : 12;               /*!< clear bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } RESET_STATUS_CLEAR;
  
  union {
    __IO uint16_t  reg;                             /*!< RESET_ENABLE register                                                 */
    
    struct {
      __IO uint16_t  cpu_lockup :  1;               /*!< cpu_lockup bitfield                                                   */
      __IO uint16_t  debug_reset:  1;               /*!< debug_reset bitfield                                                  */
      __IO uint16_t  software   :  1;               /*!< software bitfield                                                     */
      __IO uint16_t  sram_parity:  1;               /*!< sram_parity bitfield                                                  */
      __IO uint16_t  otp_ecc_fail:  1;              /*!< otp_ecc_fail bitfield                                                 */
      __IO uint16_t  watchdog_window:  1;           /*!< watchdog_window bitfield                                              */
      __IO uint16_t  watchdog   :  1;               /*!< watchdog bitfield                                                     */
      __IO uint16_t  watchdog_zero:  1;             /*!< watchdog_zero bitfield                                                */
      __IO uint16_t  crc16_mismatch:  1;            /*!< crc16_mismatch bitfield                                               */
      __IO uint16_t  trim_parity:  1;               /*!< trim_parity bitfield                                                  */
    } bit;                                          /*!< BitSize                                                               */
  } RESET_ENABLE;
  
  union {
    __IO uint16_t  reg;                             /*!< SW_RESET register                                                     */
    
    struct {
      __I  uint16_t  por_flag   :  1;               /*!< por_flag bitfield                                                     */
      __I  uint16_t  sw_reset_flag:  3;             /*!< sw_reset_flag bitfield                                                */
      __O  uint16_t  sw_reset   :  1;               /*!< sw_reset bitfield                                                     */
      __O  uint16_t  set_sw_reset_flag:  3;         /*!< set_sw_reset_flag bitfield                                            */
    } bit;                                          /*!< BitSize                                                               */
  } SW_RESET;
  
  union {
    __O  uint16_t  reg;                             /*!< SW_RESET_FLAG_CLEAR register                                          */
    
    struct {
           uint16_t             :  1;
      __O  uint16_t  clear      :  3;               /*!< clear bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } SW_RESET_FLAG_CLEAR;
  
  union {
    __IO uint16_t  reg;                             /*!< ENABLE_DEBUG register                                                 */
    
    struct {
      __IO uint16_t  enable     :  1;               /*!< enable bitfield                                                       */
      __I  uint16_t  exit_boot_loader:  1;          /*!< exit_boot_loader bitfield                                             */
      __I  uint16_t  signature_boot:  1;            /*!< signature_boot bitfield                                               */
      __I  uint16_t  signature_new:  1;             /*!< signature_new bitfield                                                */
      __IO uint16_t  pass       : 12;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } ENABLE_DEBUG;
  
  union {
    __IO uint16_t  reg;                             /*!< WDOG_CLK_FREQ register                                                */
    
    struct {
      __IO uint16_t  freq       : 10;               /*!< freq bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } WDOG_CLK_FREQ;
  
  union {
    __I  uint16_t  reg;                             /*!< SYS_CLK_MEAS register                                                 */
    
    struct {
      __I  uint16_t  cycles     : 11;               /*!< cycles bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } SYS_CLK_MEAS;
  __I  uint32_t  RESERVED1;
  
  union {
    __IO uint16_t  reg;                             /*!< SYS_OSC_TRIM register                                                 */
    
    struct {
      __IO uint16_t  val        :  8;               /*!< val bitfield                                                          */
      __IO uint16_t  lock       :  1;               /*!< lock bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } SYS_OSC_TRIM;
  __I  uint16_t  RESERVED2[3];
  
  union {
    __IO uint16_t  reg;                             /*!< VECTOR_TABLE_REMAP register                                           */
    
    struct {
      __IO uint16_t  val        :  2;               /*!< val bitfield                                                          */
      __IO uint16_t  sel        :  1;               /*!< sel bitfield                                                          */
      __IO uint16_t  lock       :  1;               /*!< lock bitfield                                                         */
      __I  uint16_t  state      :  2;               /*!< state bitfield                                                        */
      __IO uint16_t  lock_table_base:  1;           /*!< lock_table_base bitfield                                              */
           uint16_t             :  1;
      __IO uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } VECTOR_TABLE_REMAP;
  __I  uint16_t  RESERVED3;
  
  union {
    __IO uint16_t  reg;                             /*!< VECTOR_TABLE_BASE0 register                                           */
    
    struct {
      __IO uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } VECTOR_TABLE_BASE0;
  
  union {
    __IO uint16_t  reg;                             /*!< VECTOR_TABLE_BASE1 register                                           */
    
    struct {
      __IO uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } VECTOR_TABLE_BASE1;
  
  union {
    __IO uint16_t  reg;                             /*!< TEST_MASTER_DATA_L register                                           */
    
    struct {
      __IO uint16_t  data       : 16;               /*!< data bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_MASTER_DATA_L;
  
  union {
    __IO uint16_t  reg;                             /*!< TEST_MASTER_DATA_H register                                           */
    
    struct {
      __IO uint16_t  data       : 16;               /*!< data bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_MASTER_DATA_H;
  
  union {
    __O  uint16_t  reg;                             /*!< TEST_MASTER_ADDR register                                             */
    
    struct {
      __O  uint16_t  addr       : 12;               /*!< addr bitfield                                                         */
      __O  uint16_t  write      :  1;               /*!< write bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_MASTER_ADDR;
  
  union {
    __I  uint16_t  reg;                             /*!< TEST_SIGNATURE register                                               */
    
    struct {
      __I  uint16_t  data       : 16;               /*!< data bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_SIGNATURE;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_STATUS register                                                   */
    
    struct {
      __IO uint16_t  cpu_lockup :  1;               /*!< cpu_lockup bitfield                                                   */
      __IO uint16_t  debug_reset:  1;               /*!< debug_reset bitfield                                                  */
      __IO uint16_t  software   :  1;               /*!< software bitfield                                                     */
      __IO uint16_t  sram_parity:  1;               /*!< sram_parity bitfield                                                  */
      __IO uint16_t  otp_ecc_fail:  1;              /*!< otp_ecc_fail bitfield                                                 */
      __IO uint16_t  watchdog_window:  1;           /*!< watchdog_window bitfield                                              */
      __IO uint16_t  watchdog   :  1;               /*!< watchdog bitfield                                                     */
      __IO uint16_t  watchdog_zero:  1;             /*!< watchdog_zero bitfield                                                */
      __IO uint16_t  crc16_mismatch:  1;            /*!< crc16_mismatch bitfield                                               */
      __IO uint16_t  trim_parity:  1;               /*!< trim_parity bitfield                                                  */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_STATUS;
  __I  uint16_t  RESERVED4;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_MASK register                                                     */
    
    struct {
      __IO uint16_t  mask       : 10;               /*!< mask bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_MASK;
  __I  uint16_t  RESERVED5;
  
  union {
    __O  uint16_t  reg;                             /*!< IRQ_VENABLE register                                                  */
    
    struct {
      __O  uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VENABLE;
  
  union {
    __O  uint16_t  reg;                             /*!< IRQ_VDISABLE register                                                 */
    
    struct {
      __O  uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VDISABLE;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_VMAX register                                                     */
    
    struct {
      __IO uint16_t  vmax       :  4;               /*!< vmax bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VMAX;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_VNO register                                                      */
    
    struct {
      __IO uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
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
    __IO uint16_t  reg;                             /*!< START0 register                                                       */
    
    struct {
      __IO uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } START0;
  
  union {
    __IO uint16_t  reg;                             /*!< START1 register                                                       */
    
    struct {
      __IO uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } START1;
  
  union {
    __IO uint16_t  reg;                             /*!< LENGTH0 register                                                      */
    
    struct {
      __IO uint16_t  bytes      : 16;               /*!< bytes bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } LENGTH0;
  
  union {
    __IO uint16_t  reg;                             /*!< LENGTH1 register                                                      */
    
    struct {
      __IO uint16_t  bytes      : 16;               /*!< bytes bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } LENGTH1;
  
  union {
    __IO uint16_t  reg;                             /*!< EXPECTED_CRC register                                                 */
    
    struct {
      __IO uint16_t  crc        : 16;               /*!< crc bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } EXPECTED_CRC;
  
  union {
    __IO uint16_t  reg;                             /*!< CONFIG register                                                       */
    
    struct {
      __IO uint16_t  timing     :  3;               /*!< timing bitfield                                                       */
      __IO uint16_t  keep_sum   :  1;               /*!< keep_sum bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } CONFIG;
  
  union {
    __I  uint16_t  reg;                             /*!< STATUS register                                                       */
    
    struct {
      __I  uint16_t  state      :  2;               /*!< state bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } STATUS;
  
  union {
    __IO uint16_t  reg;                             /*!< CRC_SUM register                                                      */
    
    struct {
      __IO uint16_t  crc        : 16;               /*!< crc bitfield                                                          */
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
    __IO uint16_t  reg;                             /*!< READ_CONFIG register                                                  */
    
    struct {
      __IO uint16_t  differential:  1;              /*!< differential bitfield                                                 */
      __IO uint16_t  redundant  :  1;               /*!< redundant bitfield                                                    */
      __IO uint16_t  trp_config :  2;               /*!< trp_config bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } READ_CONFIG;
  
  union {
    __IO uint16_t  reg;                             /*!< PROG_CONFIG register                                                  */
    
    struct {
      __IO uint16_t  max_soak   :  4;               /*!< max_soak bitfield                                                     */
      __IO uint16_t  trp_config :  3;               /*!< trp_config bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } PROG_CONFIG;
  __I  uint16_t  RESERVED;
  
  union {
    __IO uint16_t  reg;                             /*!< PROG_CONTROL register                                                 */
    
    struct {
      __IO uint16_t  otp_prog   :  1;               /*!< otp_prog bitfield                                                     */
      __IO uint16_t  differential:  1;              /*!< differential bitfield                                                 */
           uint16_t             :  6;
      __IO uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } PROG_CONTROL;
  
  union {
    __IO uint16_t  reg;                             /*!< WDATA0 register                                                       */
    
    struct {
      __IO uint16_t  data       : 16;               /*!< data bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } WDATA0;
  
  union {
    __IO uint16_t  reg;                             /*!< WDATA1 register                                                       */
    
    struct {
      __IO uint16_t  data       : 16;               /*!< data bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } WDATA1;
  __I  uint32_t  RESERVED1;
  
  union {
    __IO uint16_t  reg;                             /*!< WADDR register                                                        */
    
    struct {
      __IO uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } WADDR;
  __I  uint16_t  RESERVED2;
  
  union {
    __I  uint16_t  reg;                             /*!< PROG_STATUS register                                                  */
    
    struct {
      __I  uint16_t  last_soak  :  4;               /*!< last_soak bitfield                                                    */
      __I  uint16_t  busy       :  1;               /*!< busy bitfield                                                         */
      __I  uint16_t  fail0      :  1;               /*!< fail0 bitfield                                                        */
      __I  uint16_t  fail1      :  1;               /*!< fail1 bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } PROG_STATUS;
  
  union {
    __I  uint16_t  reg;                             /*!< BIT_SOAK_STATUS register                                              */
    
    struct {
      __I  uint16_t  take       :  1;               /*!< take bitfield                                                         */
      __I  uint16_t  soak_bit   :  6;               /*!< soak_bit bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } BIT_SOAK_STATUS;
  
  union {
    __IO uint16_t  reg;                             /*!< PROTECT register                                                      */
    
    struct {
      __IO uint16_t  protect    :  8;               /*!< protect bitfield                                                      */
      __IO uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } PROTECT;
  
  union {
    __IO uint16_t  reg;                             /*!< BOOT_PROTECT register                                                 */
    
    struct {
      __IO uint16_t  protect    :  3;               /*!< protect bitfield                                                      */
           uint16_t             :  5;
      __IO uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } BOOT_PROTECT;
  
  union {
    __IO uint16_t  reg;                             /*!< IO_FLAG register                                                      */
    
    struct {
      __IO uint16_t  flag       :  1;               /*!< flag bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IO_FLAG;
  __I  uint16_t  RESERVED3;
  
  union {
    __O  uint16_t  reg;                             /*!< TEST_LOCK register                                                    */
    
    struct {
      __O  uint16_t  lock       :  1;               /*!< lock bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_LOCK;
  
  union {
    __IO uint16_t  reg;                             /*!< TEST_TRP_CONFIG register                                              */
    
    struct {
      __IO uint16_t  val        :  8;               /*!< val bitfield                                                          */
      __IO uint16_t  sel        :  1;               /*!< sel bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_TRP_CONFIG;
  
  union {
    __IO uint16_t  reg;                             /*!< TEST_MR register                                                      */
    
    struct {
      __IO uint16_t  val        :  8;               /*!< val bitfield                                                          */
      __IO uint16_t  read_sel   :  1;               /*!< read_sel bitfield                                                     */
      __IO uint16_t  prog_sel   :  1;               /*!< prog_sel bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_MR;
  
  union {
    __IO uint16_t  reg;                             /*!< TEST_FORCE register                                                   */
    
    struct {
      __IO uint16_t  force      :  1;               /*!< force bitfield                                                        */
      __IO uint16_t  ck         :  1;               /*!< ck bitfield                                                           */
      __IO uint16_t  sel        :  1;               /*!< sel bitfield                                                          */
      __IO uint16_t  we         :  1;               /*!< we bitfield                                                           */
      __IO uint16_t  oe         :  1;               /*!< oe bitfield                                                           */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_FORCE;
  
  union {
    __IO uint16_t  reg;                             /*!< MPP register                                                          */
    
    struct {
      __IO uint16_t  mpp        :  4;               /*!< mpp bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } MPP;
  
  union {
    __IO uint16_t  reg;                             /*!< MRR register                                                          */
    
    struct {
      __IO uint16_t  mrr        : 16;               /*!< mrr bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } MRR;
  
  union {
    __IO uint16_t  reg;                             /*!< VRR register                                                          */
    
    struct {
      __IO uint16_t  vrr1       :  4;               /*!< vrr1 bitfield                                                         */
      __IO uint16_t  vrr2       :  4;               /*!< vrr2 bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } VRR;
  
  union {
    __IO uint16_t  reg;                             /*!< ERASE register                                                        */
    
    struct {
      __O  uint16_t  start      :  1;               /*!< start bitfield                                                        */
      __I  uint16_t  ready      :  1;               /*!< ready bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ERASE;
  
  union {
    __IO uint16_t  reg;                             /*!< TEST_CELL_STRESS register                                             */
    
    struct {
      __IO uint16_t  stress     :  1;               /*!< stress bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_CELL_STRESS;
  
  union {
    __IO uint16_t  reg;                             /*!< TEST_SEL_VAL register                                                 */
    
    struct {
      __IO uint16_t  vpp_e_sel  :  1;               /*!< vpp_e_sel bitfield                                                    */
      __IO uint16_t  vpp_e_val  :  1;               /*!< vpp_e_val bitfield                                                    */
      __IO uint16_t  vrr_e_sel  :  1;               /*!< vrr_e_sel bitfield                                                    */
      __IO uint16_t  vrr_e_val  :  1;               /*!< vrr_e_val bitfield                                                    */
      __IO uint16_t  ehv_e_sel  :  1;               /*!< ehv_e_sel bitfield                                                    */
      __IO uint16_t  ehv_e_val  :  1;               /*!< ehv_e_val bitfield                                                    */
      __IO uint16_t  dben_sel   :  1;               /*!< dben_sel bitfield                                                     */
      __IO uint16_t  dben_val   :  1;               /*!< dben_val bitfield                                                     */
      __IO uint16_t  mask_ips_clks:  1;             /*!< mask_ips_clks bitfield                                                */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_SEL_VAL;
  
  union {
    __IO uint16_t  reg;                             /*!< TEST_ECC register                                                     */
    
    struct {
      __I  uint16_t  ecc_sum    : 12;               /*!< ecc_sum bitfield                                                      */
      __I  uint16_t  ecc_1bit   :  1;               /*!< ecc_1bit bitfield                                                     */
      __I  uint16_t  ecc_2bit   :  1;               /*!< ecc_2bit bitfield                                                     */
      __IO uint16_t  disable_read_ecc:  1;          /*!< disable_read_ecc bitfield                                             */
      __IO uint16_t  force_ecc_write_1:  1;         /*!< force_ecc_write_1 bitfield                                            */
    } bit;                                          /*!< BitSize                                                               */
  } TEST_ECC;
  
  union {
    __IO uint16_t  reg;                             /*!< MDB register                                                          */
    
    struct {
      __IO uint16_t  mdb        :  4;               /*!< mdb bitfield                                                          */
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
    __IO uint16_t  reg;                             /*!< MODE register                                                         */
    
    struct {
      __IO uint16_t  erase      :  1;               /*!< erase bitfield                                                        */
      __IO uint16_t  program    :  1;               /*!< program bitfield                                                      */
      __IO uint16_t  margin_read:  1;               /*!< margin_read bitfield                                                  */
           uint16_t             :  5;
      __IO uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } MODE;
  
  union {
    __I  uint16_t  reg;                             /*!< STATUS register                                                       */
    
    struct {
      __I  uint16_t  busy       :  1;               /*!< busy bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } STATUS;
  
  union {
    __IO uint16_t  reg;                             /*!< LOCK_L register                                                       */
    
    struct {
      __IO uint16_t  lock       :  8;               /*!< lock bitfield                                                         */
      __IO uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } LOCK_L;
  
  union {
    __IO uint16_t  reg;                             /*!< LOCK_U register                                                       */
    
    struct {
      __IO uint16_t  lock       :  8;               /*!< lock bitfield                                                         */
      __IO uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } LOCK_U;
  __I  uint16_t  RESERVED;
  
  union {
    __IO uint16_t  reg;                             /*!< LOCK_CNT register                                                     */
    
    struct {
      __IO uint16_t  lock_counter:  4;              /*!< lock_counter bitfield                                                 */
           uint16_t             :  4;
      __IO uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } LOCK_CNT;
  
  union {
    __IO uint16_t  reg;                             /*!< LOCK_L_FREEZE register                                                */
    
    struct {
      __IO uint16_t  freeze     :  8;               /*!< freeze bitfield                                                       */
      __IO uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } LOCK_L_FREEZE;
  
  union {
    __IO uint16_t  reg;                             /*!< LOCK_U_FREEZE register                                                */
    
    struct {
      __IO uint16_t  freeze     :  8;               /*!< freeze bitfield                                                       */
      __IO uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } LOCK_U_FREEZE;
  
  union {
    __IO uint16_t  reg;                             /*!< IP_ENABLE register                                                    */
    
    struct {
      __IO uint16_t  enable     :  1;               /*!< enable bitfield                                                       */
           uint16_t             :  7;
      __IO uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IP_ENABLE;
  
  union {
    __IO uint16_t  reg;                             /*!< MARGIN_TRIM register                                                  */
    
    struct {
      __IO uint16_t  trim       :  3;               /*!< trim bitfield                                                         */
           uint16_t             :  5;
      __IO uint16_t  pass       :  8;               /*!< pass bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } MARGIN_TRIM;
  
  union {
    __I  uint16_t  reg;                             /*!< TIMEOUT_L register                                                    */
    
    struct {
      __I  uint16_t  val        : 16;               /*!< val bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } TIMEOUT_L;
  
  union {
    __I  uint16_t  reg;                             /*!< TIMEOUT_H register                                                    */
    
    struct {
      __I  uint16_t  val        :  2;               /*!< val bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } TIMEOUT_H;
  __I  uint32_t  RESERVED1[6];
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_STATUS register                                                   */
    
    struct {
      __IO uint16_t  timeout    :  1;               /*!< timeout bitfield                                                      */
      __IO uint16_t  invalid_addr:  1;              /*!< invalid_addr bitfield                                                 */
      __IO uint16_t  ip_off_access:  1;             /*!< ip_off_access bitfield                                                */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_STATUS;
  __I  uint16_t  RESERVED2;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_MASK register                                                     */
    
    struct {
      __IO uint16_t  mask       :  3;               /*!< mask bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_MASK;
  __I  uint16_t  RESERVED3;
  
  union {
    __O  uint16_t  reg;                             /*!< IRQ_VENABLE register                                                  */
    
    struct {
      __O  uint16_t  vno        :  2;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VENABLE;
  
  union {
    __O  uint16_t  reg;                             /*!< IRQ_VDISABLE register                                                 */
    
    struct {
      __O  uint16_t  vno        :  2;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VDISABLE;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_VMAX register                                                     */
    
    struct {
      __IO uint16_t  vmax       :  2;               /*!< vmax bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VMAX;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_VNO register                                                      */
    
    struct {
      __IO uint16_t  vno        :  2;               /*!< vno bitfield                                                          */
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
    __IO uint16_t  reg;                             /*!< DATA_OUT register                                                     */
    
    struct {
      __IO uint16_t  data       :  4;               /*!< data bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } DATA_OUT;
  
  union {
    __IO uint16_t  reg;                             /*!< DATA_OE register                                                      */
    
    struct {
      __IO uint16_t  enable     :  4;               /*!< enable bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } DATA_OE;
  
  union {
    __I  uint16_t  reg;                             /*!< DATA_IN register                                                      */
    
    struct {
      __I  uint16_t  data       :  4;               /*!< data bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } DATA_IN;
  
  union {
    __IO uint16_t  reg;                             /*!< DATA_IE register                                                      */
    
    struct {
      __IO uint16_t  enable     :  4;               /*!< enable bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } DATA_IE;
  
  union {
    __IO uint16_t  reg;                             /*!< DATA_PUE register                                                     */
    
    struct {
      __IO uint16_t  enable     :  4;               /*!< enable bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } DATA_PUE;
  
  union {
    __IO uint16_t  reg;                             /*!< IOMUX register                                                        */
    
    struct {
      __IO uint16_t  mux        :  2;               /*!< mux bitfield                                                          */
      __IO uint16_t  uart_port  :  1;               /*!< uart_port bitfield                                                    */
    } bit;                                          /*!< BitSize                                                               */
  } IOMUX;
  __I  uint32_t  RESERVED[9];
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_STATUS register                                                   */
    
    struct {
      __IO uint16_t  evt_pos_0  :  1;               /*!< evt_pos_0 bitfield                                                    */
      __IO uint16_t  evt_neg_0  :  1;               /*!< evt_neg_0 bitfield                                                    */
      __IO uint16_t  evt_pos_1  :  1;               /*!< evt_pos_1 bitfield                                                    */
      __IO uint16_t  evt_neg_1  :  1;               /*!< evt_neg_1 bitfield                                                    */
      __IO uint16_t  evt_pos_2  :  1;               /*!< evt_pos_2 bitfield                                                    */
      __IO uint16_t  evt_neg_2  :  1;               /*!< evt_neg_2 bitfield                                                    */
      __IO uint16_t  evt_pos_3  :  1;               /*!< evt_pos_3 bitfield                                                    */
      __IO uint16_t  evt_neg_3  :  1;               /*!< evt_neg_3 bitfield                                                    */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_STATUS;
  __I  uint16_t  RESERVED1;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_MASK register                                                     */
    
    struct {
      __IO uint16_t  mask       :  8;               /*!< mask bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_MASK;
  __I  uint16_t  RESERVED2;
  
  union {
    __O  uint16_t  reg;                             /*!< IRQ_VENABLE register                                                  */
    
    struct {
      __O  uint16_t  vno        :  3;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VENABLE;
  
  union {
    __O  uint16_t  reg;                             /*!< IRQ_VDISABLE register                                                 */
    
    struct {
      __O  uint16_t  vno        :  3;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VDISABLE;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_VMAX register                                                     */
    
    struct {
      __IO uint16_t  vmax       :  4;               /*!< vmax bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VMAX;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_VNO register                                                      */
    
    struct {
      __IO uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
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
    __IO uint16_t  reg;                             /*!< CONFIG register                                                       */
    
    struct {
      __IO uint16_t  enables    :  2;               /*!< enables bitfield                                                      */
      __IO uint16_t  cnt_auto_reloads:  2;          /*!< cnt_auto_reloads bitfield                                             */
      __IO uint16_t  ext_strb_src:  2;              /*!< ext_strb_src bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } CONFIG;
  
  union {
    __O  uint16_t  reg;                             /*!< COMMAND register                                                      */
    
    struct {
      __O  uint16_t  cnt_reload_cmd:  2;            /*!< cnt_reload_cmd bitfield                                               */
      __O  uint16_t  div_reload_cmd:  2;            /*!< div_reload_cmd bitfield                                               */
    } bit;                                          /*!< BitSize                                                               */
  } COMMAND;
  
  union {
    __IO uint16_t  reg;                             /*!< CNT0_RELOAD register                                                  */
    
    struct {
      __IO uint16_t  cnt_reload : 16;               /*!< cnt_reload bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } CNT0_RELOAD;
  
  union {
    __IO uint16_t  reg;                             /*!< CNT1_RELOAD register                                                  */
    
    struct {
      __IO uint16_t  cnt_reload : 16;               /*!< cnt_reload bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } CNT1_RELOAD;
  
  union {
    __IO uint16_t  reg;                             /*!< DIV0_RELOAD register                                                  */
    
    struct {
      __IO uint16_t  div_reload :  8;               /*!< div_reload bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } DIV0_RELOAD;
  
  union {
    __IO uint16_t  reg;                             /*!< DIV1_RELOAD register                                                  */
    
    struct {
      __IO uint16_t  div_reload :  8;               /*!< div_reload bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } DIV1_RELOAD;
  
  union {
    __I  uint16_t  reg;                             /*!< CNT0_VALUE register                                                   */
    
    struct {
      __I  uint16_t  cnt_val    : 16;               /*!< cnt_val bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } CNT0_VALUE;
  
  union {
    __I  uint16_t  reg;                             /*!< CNT1_VALUE register                                                   */
    
    struct {
      __I  uint16_t  cnt_val    : 16;               /*!< cnt_val bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } CNT1_VALUE;
  __I  uint32_t  RESERVED[8];
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_STATUS register                                                   */
    
    struct {
      __IO uint16_t  evt_cnt_zero:  2;              /*!< evt_cnt_zero bitfield                                                 */
      __IO uint16_t  evt_div_zero:  2;              /*!< evt_div_zero bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_STATUS;
  __I  uint16_t  RESERVED1;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_MASK register                                                     */
    
    struct {
      __IO uint16_t  mask       :  4;               /*!< mask bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_MASK;
  __I  uint16_t  RESERVED2;
  
  union {
    __O  uint16_t  reg;                             /*!< IRQ_VENABLE register                                                  */
    
    struct {
      __O  uint16_t  vno        :  2;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VENABLE;
  
  union {
    __O  uint16_t  reg;                             /*!< IRQ_VDISABLE register                                                 */
    
    struct {
      __O  uint16_t  vno        :  2;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VDISABLE;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_VMAX register                                                     */
    
    struct {
      __IO uint16_t  vmax       :  3;               /*!< vmax bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VMAX;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_VNO register                                                      */
    
    struct {
      __IO uint16_t  vno        :  3;               /*!< vno bitfield                                                          */
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
    __IO uint16_t  reg;                             /*!< ANALOG_CTRL register                                                  */
    
    struct {
      __IO uint16_t  dsi3_enable:  1;               /*!< dsi3_enable bitfield                                                  */
      __IO uint16_t  rcc_enable :  1;               /*!< rcc_enable bitfield                                                   */
      __IO uint16_t  rcc_lcm    :  1;               /*!< rcc_lcm bitfield                                                      */
      __IO uint16_t  rcc_slope  :  3;               /*!< rcc_slope bitfield                                                    */
      __IO uint16_t  rcc_curve  :  1;               /*!< rcc_curve bitfield                                                    */
      __IO uint16_t  rcc_cur_ofs:  3;               /*!< rcc_cur_ofs bitfield                                                  */
      __IO uint16_t  fcc_hyst_sel:  1;              /*!< fcc_hyst_sel bitfield                                                 */
      __IO uint16_t  fcc_force_connect:  1;         /*!< fcc_force_connect bitfield                                            */
      __IO uint16_t  fcc_force_bypass:  1;          /*!< fcc_force_bypass bitfield                                             */
      __IO uint16_t  fcc_debounce:  3;              /*!< fcc_debounce bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } ANALOG_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< CONFIG register                                                       */
    
    struct {
      __IO uint16_t  crc_check  :  1;               /*!< crc_check bitfield                                                    */
      __IO uint16_t  crc_add    :  1;               /*!< crc_add bitfield                                                      */
      __IO uint16_t  auto_resp  :  1;               /*!< auto_resp bitfield                                                    */
      __IO uint16_t  auto_timer :  1;               /*!< auto_timer bitfield                                                   */
      __IO uint16_t  auto_sync  :  1;               /*!< auto_sync bitfield                                                    */
      __IO uint16_t  disable_sync_vali:  1;         /*!< disable_sync_vali bitfield                                            */
      __IO uint16_t  t_chip     :  2;               /*!< t_chip bitfield                                                       */
      __IO uint16_t  auto_blank_off:  1;            /*!< auto_blank_off bitfield                                               */
      __IO uint16_t  auto_blank_on:  1;             /*!< auto_blank_on bitfield                                                */
      __IO uint16_t  pdcm_seed_sel:  1;             /*!< pdcm_seed_sel bitfield                                                */
      __IO uint16_t  timer_start_sel:  1;           /*!< timer_start_sel bitfield                                              */
      __IO uint16_t  t_bit_fcc  :  2;               /*!< t_bit_fcc bitfield                                                    */
    } bit;                                          /*!< BitSize                                                               */
  } CONFIG;
  
  union {
    __O  uint16_t  reg;                             /*!< CTRL register                                                         */
    
    struct {
      __O  uint16_t  abort_fcc  :  1;               /*!< abort_fcc bitfield                                                    */
      __O  uint16_t  abort_rcc  :  1;               /*!< abort_rcc bitfield                                                    */
      __O  uint16_t  start_rcc  :  1;               /*!< start_rcc bitfield                                                    */
      __O  uint16_t  clr_fcc_low_flag:  1;          /*!< clr_fcc_low_flag bitfield                                             */
      __O  uint16_t  start_timer:  1;               /*!< start_timer bitfield                                                  */
      __O  uint16_t  reset_timer:  1;               /*!< reset_timer bitfield                                                  */
      __O  uint16_t  set_blanking_off:  1;          /*!< set_blanking_off bitfield                                             */
      __O  uint16_t  set_blanking_on:  1;           /*!< set_blanking_on bitfield                                              */
      __O  uint16_t  set_mode   :  2;               /*!< set_mode bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } CTRL;
  
  union {
    __I  uint16_t  reg;                             /*!< STATUS register                                                       */
    
    struct {
      __I  uint16_t  mode       :  2;               /*!< mode bitfield                                                         */
      __I  uint16_t  fcc_idle   :  1;               /*!< fcc_idle bitfield                                                     */
      __I  uint16_t  fcc_signal :  1;               /*!< fcc_signal bitfield                                                   */
      __I  uint16_t  fcc_low_flag:  1;              /*!< fcc_low_flag bitfield                                                 */
      __I  uint16_t  fcc_blanking:  1;              /*!< fcc_blanking bitfield                                                 */
      __I  uint16_t  timer_status:  1;              /*!< timer_status bitfield                                                 */
      __I  uint16_t  sync_cnt_err:  1;              /*!< sync_cnt_err bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } STATUS;
  
  union {
    __IO uint16_t  reg;                             /*!< DISCOVERY_CTRL register                                               */
    
    struct {
      __IO uint16_t  disc_ramp_on:  1;              /*!< disc_ramp_on bitfield                                                 */
      __I  uint16_t  curr_cmp_out:  1;              /*!< curr_cmp_out bitfield                                                 */
      __I  uint16_t  curr_cmp_cap:  1;              /*!< curr_cmp_cap bitfield                                                 */
           uint16_t             :  1;
      __IO uint16_t  auto_disc_resp:  1;            /*!< auto_disc_resp bitfield                                               */
      __IO uint16_t  auto_disc_accept:  1;          /*!< auto_disc_accept bitfield                                             */
           uint16_t             :  2;
      __IO uint16_t  debounce   :  3;               /*!< debounce bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } DISCOVERY_CTRL;
  __I  uint16_t  RESERVED;
  
  union {
    __IO uint16_t  reg;                             /*!< CLK_1US register                                                      */
    
    struct {
      __IO uint16_t  frac       :  5;               /*!< frac bitfield                                                         */
      __IO uint16_t  div        :  5;               /*!< div bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } CLK_1US;
  
  union {
    __I  uint16_t  reg;                             /*!< SYNC_CNT register                                                     */
    
    struct {
      __I  uint16_t  val        : 10;               /*!< val bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } SYNC_CNT;
  
  union {
    __I  uint16_t  reg;                             /*!< FCC_COMMAND_LOW register                                              */
    
    struct {
      __I  uint16_t  cmd        : 16;               /*!< cmd bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } FCC_COMMAND_LOW;
  
  union {
    __I  uint16_t  reg;                             /*!< FCC_COMMAND_HIGH register                                             */
    
    struct {
      __I  uint16_t  cmd        : 16;               /*!< cmd bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } FCC_COMMAND_HIGH;
  
  union {
    __IO uint16_t  reg;                             /*!< RCC_DMA_ADDR_LOW register                                             */
    
    struct {
      __IO uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } RCC_DMA_ADDR_LOW;
  
  union {
    __IO uint16_t  reg;                             /*!< RCC_DMA_ADDR_HIGH register                                            */
    
    struct {
      __IO uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } RCC_DMA_ADDR_HIGH;
  
  union {
    __IO uint16_t  reg;                             /*!< RCC_BUFFER_LENGTH register                                            */
    
    struct {
      __IO uint16_t  length     :  6;               /*!< length bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } RCC_BUFFER_LENGTH;
  
  union {
    __I  uint16_t  reg;                             /*!< RCC_BYTE_CNT register                                                 */
    
    struct {
      __I  uint16_t  byte       :  6;               /*!< byte bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } RCC_BYTE_CNT;
  __I  uint32_t  RESERVED1;
  
  union {
    __IO uint16_t  reg;                             /*!< TIMER_COMPARE_A register                                              */
    
    struct {
      __IO uint16_t  value      : 13;               /*!< value bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } TIMER_COMPARE_A;
  
  union {
    __IO uint16_t  reg;                             /*!< TIMER_COMPARE_B register                                              */
    
    struct {
      __IO uint16_t  value      : 13;               /*!< value bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } TIMER_COMPARE_B;
  
  union {
    __IO uint16_t  reg;                             /*!< TIMER_COMPARE_C register                                              */
    
    struct {
      __IO uint16_t  value      : 13;               /*!< value bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } TIMER_COMPARE_C;
  __I  uint16_t  RESERVED2;
  
  union {
    __I  uint16_t  reg;                             /*!< TIMER_COUNTER register                                                */
    
    struct {
      __I  uint16_t  value      : 13;               /*!< value bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } TIMER_COUNTER;
  
  union {
    __I  uint16_t  reg;                             /*!< TIMER_CAPTURE register                                                */
    
    struct {
      __I  uint16_t  value      : 13;               /*!< value bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } TIMER_CAPTURE;
  
  union {
    __IO uint16_t  reg;                             /*!< SOURCE_ID register                                                    */
    
    struct {
      __IO uint16_t  value      :  8;               /*!< value bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } SOURCE_ID;
  
  union {
    __O  uint16_t  reg;                             /*!< RCC_DAC register                                                      */
    
    struct {
      __O  uint16_t  value      :  8;               /*!< value bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } RCC_DAC;
  __I  uint32_t  RESERVED3[7];
  
  union {
    __I  uint16_t  reg;                             /*!< HW_VERSION register                                                   */
    
    struct {
      __I  uint16_t  value      :  8;               /*!< value bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } HW_VERSION;
  __I  uint16_t  RESERVED4;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_STATUS register                                                   */
    
    struct {
      __IO uint16_t  sync_evt   :  1;               /*!< sync_evt bitfield                                                     */
      __IO uint16_t  cmd_evt    :  1;               /*!< cmd_evt bitfield                                                      */
      __IO uint16_t  pdcm_evt   :  1;               /*!< pdcm_evt bitfield                                                     */
      __IO uint16_t  disc_evt   :  1;               /*!< disc_evt bitfield                                                     */
      __IO uint16_t  crc_err_evt:  1;               /*!< crc_err_evt bitfield                                                  */
      __IO uint16_t  pdcm_err_evt:  1;              /*!< pdcm_err_evt bitfield                                                 */
      __IO uint16_t  disc_err_evt:  1;              /*!< disc_err_evt bitfield                                                 */
      __IO uint16_t  fcc_error  :  1;               /*!< fcc_error bitfield                                                    */
      __IO uint16_t  start_err_evt:  1;             /*!< start_err_evt bitfield                                                */
      __IO uint16_t  timer_a_evt:  1;               /*!< timer_a_evt bitfield                                                  */
      __IO uint16_t  timer_b_evt:  1;               /*!< timer_b_evt bitfield                                                  */
      __IO uint16_t  timer_c_evt:  1;               /*!< timer_c_evt bitfield                                                  */
      __IO uint16_t  rcc_finish :  1;               /*!< rcc_finish bitfield                                                   */
      __IO uint16_t  rcc_ready  :  1;               /*!< rcc_ready bitfield                                                    */
      __IO uint16_t  sync_cnt_evt:  1;              /*!< sync_cnt_evt bitfield                                                 */
      __IO uint16_t  disc_curr_evt:  1;             /*!< disc_curr_evt bitfield                                                */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_STATUS;
  __I  uint16_t  RESERVED5;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_MASK register                                                     */
    
    struct {
      __IO uint16_t  mask       : 16;               /*!< mask bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_MASK;
  __I  uint16_t  RESERVED6;
  
  union {
    __O  uint16_t  reg;                             /*!< IRQ_VENABLE register                                                  */
    
    struct {
      __O  uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VENABLE;
  
  union {
    __O  uint16_t  reg;                             /*!< IRQ_VDISABLE register                                                 */
    
    struct {
      __O  uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VDISABLE;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_VMAX register                                                     */
    
    struct {
      __IO uint16_t  vmax       :  5;               /*!< vmax bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VMAX;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_VNO register                                                      */
    
    struct {
      __IO uint16_t  vno        :  5;               /*!< vno bitfield                                                          */
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
    __IO uint16_t  reg;                             /*!< BRG_CTRL register                                                     */
    
    struct {
      __O  uint16_t  burst_en   :  1;               /*!< burst_en bitfield                                                     */
      __O  uint16_t  burst_brk  :  1;               /*!< burst_brk bitfield                                                    */
      __I  uint16_t  burst_sta  :  2;               /*!< burst_sta bitfield                                                    */
      __O  uint16_t  burst_en_diag:  1;             /*!< burst_en_diag bitfield                                                */
    } bit;                                          /*!< BitSize                                                               */
  } BRG_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< BRG_CFG register                                                      */
    
    struct {
      __IO uint16_t  n_pulses   :  7;               /*!< n_pulses bitfield                                                     */
      __IO uint16_t  burst_type :  2;               /*!< burst_type bitfield                                                   */
      __IO uint16_t  code_len   :  4;               /*!< code_len bitfield                                                     */
      __IO uint16_t  sel_inc    :  1;               /*!< sel_inc bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } BRG_CFG;
  
  union {
    __IO uint16_t  reg;                             /*!< BRG_FC register                                                       */
    
    struct {
      __IO uint16_t  f_c        : 15;               /*!< f_c bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } BRG_FC;
  
  union {
    __IO uint16_t  reg;                             /*!< BRG_F0 register                                                       */
    
    struct {
      __IO uint16_t  f_0        : 15;               /*!< f_0 bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } BRG_F0;
  
  union {
    __IO uint16_t  reg;                             /*!< BRG_F1 register                                                       */
    
    struct {
      __IO uint16_t  f_1        : 15;               /*!< f_1 bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } BRG_F1;
  
  union {
    __IO uint16_t  reg;                             /*!< BRG_FDELTA register                                                   */
    
    struct {
      __IO uint16_t  f_delta    :  8;               /*!< f_delta bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } BRG_FDELTA;
  
  union {
    __IO uint16_t  reg;                             /*!< BRG_CODE register                                                     */
    
    struct {
      __IO uint16_t  code       : 16;               /*!< code bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } BRG_CODE;
  
  union {
    __IO uint16_t  reg;                             /*!< TDR_CTRL register                                                     */
    
    struct {
      __IO uint16_t  i_drv      :  5;               /*!< i_drv bitfield                                                        */
      __IO uint16_t  sel_isrc   :  1;               /*!< sel_isrc bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } TDR_CTRL;
  
  union {
    __I  uint16_t  reg;                             /*!< TDR_STATUS register                                                   */
    
    struct {
      __I  uint16_t  drv1_sta   :  1;               /*!< drv1_sta bitfield                                                     */
      __I  uint16_t  drv2_sta   :  1;               /*!< drv2_sta bitfield                                                     */
      __I  uint16_t  drvs_sta   :  1;               /*!< drvs_sta bitfield                                                     */
      __I  uint16_t  vtank_ov   :  1;               /*!< vtank_ov bitfield                                                     */
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
    __IO uint16_t  reg;                             /*!< DSP_CTRL register                                                     */
    
    struct {
      __IO uint16_t  dsp_on     :  1;               /*!< dsp_on bitfield                                                       */
      __IO uint16_t  dsp_pwr_dwn:  1;               /*!< dsp_pwr_dwn bitfield                                                  */
      __I  uint16_t  dsp_on_state:  1;              /*!< dsp_on_state bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } DSP_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< ENVP_CFG register                                                     */
    
    struct {
      __IO uint16_t  envp_cfg   :  3;               /*!< envp_cfg bitfield                                                     */
      __IO uint16_t  envp_afc   :  1;               /*!< envp_afc bitfield                                                     */
      __IO uint16_t  g_cal      :  5;               /*!< g_cal bitfield                                                        */
      __IO uint16_t  dsr_sel    :  1;               /*!< dsr_sel bitfield                                                      */
      __IO uint16_t  fspi_sel   :  1;               /*!< fspi_sel bitfield                                                     */
      __IO uint16_t  aspi_sel   :  1;               /*!< aspi_sel bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_CFG;
  
  union {
    __O  uint16_t  reg;                             /*!< ENVP_CTRL register                                                    */
    
    struct {
      __O  uint16_t  envp_afc_brk:  1;              /*!< envp_afc_brk bitfield                                                 */
      __O  uint16_t  envp_restart:  1;              /*!< envp_restart bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_CTRL;
  
  union {
    __I  uint16_t  reg;                             /*!< ENVP_ENV_RAW register                                                 */
    
    struct {
      __I  uint16_t  envp_env_raw: 16;              /*!< envp_env_raw bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_ENV_RAW;
  
  union {
    __IO uint16_t  reg;                             /*!< ENVP_FILT_CFG register                                                */
    
    struct {
      __IO uint16_t  filt_len_fix:  6;              /*!< filt_len_fix bitfield                                                 */
      __IO uint16_t  filt_len_code:  6;             /*!< filt_len_code bitfield                                                */
      __IO uint16_t  f1_coeff_sel:  1;              /*!< f1_coeff_sel bitfield                                                 */
      __IO uint16_t  f2_coeff_sel:  1;              /*!< f2_coeff_sel bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_FILT_CFG;
  
  union {
    __IO uint16_t  reg;                             /*!< ENVP_COEFF_3_2_1_0 register                                           */
    
    struct {
      __IO uint16_t  coeff      : 16;               /*!< coeff bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_COEFF_3_2_1_0;
  
  union {
    __IO uint16_t  reg;                             /*!< ENVP_COEFF_7_6_5_4 register                                           */
    
    struct {
      __IO uint16_t  coeff      : 16;               /*!< coeff bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_COEFF_7_6_5_4;
  
  union {
    __IO uint16_t  reg;                             /*!< ENVP_COEFF_11_10_9_8 register                                         */
    
    struct {
      __IO uint16_t  coeff      : 16;               /*!< coeff bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_COEFF_11_10_9_8;
  
  union {
    __IO uint16_t  reg;                             /*!< ENVP_COEFF_15_14_13_12 register                                       */
    
    struct {
      __IO uint16_t  coeff      : 16;               /*!< coeff bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_COEFF_15_14_13_12;
  
  union {
    __IO uint16_t  reg;                             /*!< ENVP_COEFF_19_18_17_16 register                                       */
    
    struct {
      __IO uint16_t  coeff      : 16;               /*!< coeff bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_COEFF_19_18_17_16;
  
  union {
    __IO uint16_t  reg;                             /*!< ENVP_COEFF_23_22_21_20 register                                       */
    
    struct {
      __IO uint16_t  coeff      : 16;               /*!< coeff bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_COEFF_23_22_21_20;
  
  union {
    __IO uint16_t  reg;                             /*!< ENVP_COEFF_27_26_25_24 register                                       */
    
    struct {
      __IO uint16_t  coeff      : 16;               /*!< coeff bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_COEFF_27_26_25_24;
  
  union {
    __IO uint16_t  reg;                             /*!< ENVP_COEFF_31_30_29_28 register                                       */
    
    struct {
      __IO uint16_t  coeff      : 16;               /*!< coeff bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } ENVP_COEFF_31_30_29_28;
  
  union {
    __IO uint16_t  reg;                             /*!< FTC_CTRL register                                                     */
    
    struct {
      __IO uint16_t  ftc_cfg    :  3;               /*!< ftc_cfg bitfield                                                      */
      __IO uint16_t  ftc_en     :  1;               /*!< ftc_en bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } FTC_CTRL;
  
  union {
    __I  uint16_t  reg;                             /*!< ENV_FTC register                                                      */
    
    struct {
      __I  uint16_t  env_ftc    : 16;               /*!< env_ftc bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } ENV_FTC;
  
  union {
    __IO uint16_t  reg;                             /*!< AMPD_CTRL register                                                    */
    
    struct {
      __IO uint16_t  ampd_g_dig :  7;               /*!< ampd_g_dig bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } AMPD_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< STC_CTRL register                                                     */
    
    struct {
      __IO uint16_t  ampd_g_dig_target:  7;         /*!< ampd_g_dig_target bitfield                                            */
      __IO uint16_t  ampd_stc_mod:  1;              /*!< ampd_stc_mod bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } STC_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< STC_TB register                                                       */
    
    struct {
      __IO uint16_t  ampd_stc_tb: 12;               /*!< ampd_stc_tb bitfield                                                  */
    } bit;                                          /*!< BitSize                                                               */
  } STC_TB;
  
  union {
    __I  uint16_t  reg;                             /*!< AMPD_ENV register                                                     */
    
    struct {
      __I  uint16_t  ampd_env   :  8;               /*!< ampd_env bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } AMPD_ENV;
  
  union {
    __I  uint16_t  reg;                             /*!< MT register                                                           */
    
    struct {
      __I  uint16_t  mt_ts      : 16;               /*!< mt_ts bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } MT;
  
  union {
    __IO uint16_t  reg;                             /*!< RFM_CTRL register                                                     */
    
    struct {
      __IO uint16_t  rfm_start  :  5;               /*!< rfm_start bitfield                                                    */
      __IO uint16_t  rfm_width  :  5;               /*!< rfm_width bitfield                                                    */
      __I  uint16_t  rfm_status :  1;               /*!< rfm_status bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } RFM_CTRL;
  
  union {
    __I  uint16_t  reg;                             /*!< RFM_CROSS_COUNT register                                              */
    
    struct {
      __I  uint16_t  rfm_cross_count:  6;           /*!< rfm_cross_count bitfield                                              */
    } bit;                                          /*!< BitSize                                                               */
  } RFM_CROSS_COUNT;
  
  union {
    __I  uint16_t  reg;                             /*!< RFM_COUNTS register                                                   */
    
    struct {
      __I  uint16_t  rfm_counts :  6;               /*!< rfm_counts bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } RFM_COUNTS;
  
  union {
    __I  uint16_t  reg;                             /*!< RFM_SAMPLES register                                                  */
    
    struct {
      __I  uint16_t  rfm_samples: 10;               /*!< rfm_samples bitfield                                                  */
    } bit;                                          /*!< BitSize                                                               */
  } RFM_SAMPLES;
  
  union {
    __I  uint16_t  reg;                             /*!< RTM register                                                          */
    
    struct {
      __I  uint16_t  rtm_rt     : 13;               /*!< rtm_rt bitfield                                                       */
      __I  uint16_t  rtm_rt_end :  1;               /*!< rtm_rt_end bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } RTM;
  
  union {
    __IO uint16_t  reg;                             /*!< ATG_CTRL register                                                     */
    
    struct {
      __IO uint16_t  atg_tau    :  3;               /*!< atg_tau bitfield                                                      */
      __IO uint16_t  atg_alpha  :  3;               /*!< atg_alpha bitfield                                                    */
      __IO uint16_t  atg_ini    :  3;               /*!< atg_ini bitfield                                                      */
      __IO uint16_t  atg_cfg    :  1;               /*!< atg_cfg bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } ATG_CTRL;
  
  union {
    __I  uint16_t  reg;                             /*!< ATG_TH register                                                       */
    
    struct {
      __I  uint16_t  atg_th     :  8;               /*!< atg_th bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } ATG_TH;
  
  union {
    __IO uint16_t  reg;                             /*!< AATG1_CTRL register                                                   */
    
    struct {
      __IO uint16_t  aatg1_cn   :  3;               /*!< aatg1_cn bitfield                                                     */
      __IO uint16_t  aatg1_cw   :  3;               /*!< aatg1_cw bitfield                                                     */
      __IO uint16_t  aatg1_alpha:  2;               /*!< aatg1_alpha bitfield                                                  */
      __IO uint16_t  aatg1_off  :  1;               /*!< aatg1_off bitfield                                                    */
      __I  uint16_t  aatg1_buf_full:  1;            /*!< aatg1_buf_full bitfield                                               */
      __I  uint16_t  aatg1_buf_half:  1;            /*!< aatg1_buf_half bitfield                                               */
    } bit;                                          /*!< BitSize                                                               */
  } AATG1_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< AATG2_CTRL register                                                   */
    
    struct {
      __IO uint16_t  aatg2_cn   :  3;               /*!< aatg2_cn bitfield                                                     */
      __IO uint16_t  aatg2_cw   :  3;               /*!< aatg2_cw bitfield                                                     */
      __IO uint16_t  aatg2_alpha:  2;               /*!< aatg2_alpha bitfield                                                  */
      __IO uint16_t  aatg2_off  :  1;               /*!< aatg2_off bitfield                                                    */
      __I  uint16_t  aatg2_buf_full:  1;            /*!< aatg2_buf_full bitfield                                               */
      __I  uint16_t  aatg2_buf_half:  1;            /*!< aatg2_buf_half bitfield                                               */
    } bit;                                          /*!< BitSize                                                               */
  } AATG2_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< STG_TH register                                                       */
    
    struct {
      __IO uint16_t  stg_th     :  8;               /*!< stg_th bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } STG_TH;
  
  union {
    __IO uint16_t  reg;                             /*!< STG_TB register                                                       */
    
    struct {
      __IO uint16_t  stg_tb     : 10;               /*!< stg_tb bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } STG_TB;
  
  union {
    __IO uint16_t  reg;                             /*!< STG_STEP register                                                     */
    
    struct {
      __IO uint16_t  stg_step   :  8;               /*!< stg_step bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } STG_STEP;
  
  union {
    __IO uint16_t  reg;                             /*!< EEVAL_CTRL register                                                   */
    
    struct {
      __IO uint16_t  eeval_sel  :  4;               /*!< eeval_sel bitfield                                                    */
      __IO uint16_t  eeval_sens :  3;               /*!< eeval_sens bitfield                                                   */
      __IO uint16_t  eeval_dma_val:  1;             /*!< eeval_dma_val bitfield                                                */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< EEVAL_DMA_CTRL register                                               */
    
    struct {
      __IO uint16_t  length     :  8;               /*!< length bitfield                                                       */
      __IO uint16_t  wrap_off   :  1;               /*!< wrap_off bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL_DMA_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< EEVAL1_DMA_CTRL register                                              */
    
    struct {
      __IO uint16_t  length     :  8;               /*!< length bitfield                                                       */
      __IO uint16_t  wrap_off   :  1;               /*!< wrap_off bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL1_DMA_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< EEVAL2_DMA_CTRL register                                              */
    
    struct {
      __IO uint16_t  length     :  8;               /*!< length bitfield                                                       */
      __IO uint16_t  wrap_off   :  1;               /*!< wrap_off bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL2_DMA_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< EEVAL_DMA_ADDR register                                               */
    
    struct {
      __IO uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL_DMA_ADDR;
  
  union {
    __IO uint16_t  reg;                             /*!< EEVAL1_DMA_ADDR register                                              */
    
    struct {
      __IO uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL1_DMA_ADDR;
  
  union {
    __IO uint16_t  reg;                             /*!< EEVAL2_DMA_ADDR register                                              */
    
    struct {
      __IO uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL2_DMA_ADDR;
  
  union {
    __I  uint16_t  reg;                             /*!< EEVAL_DMA_NEXT_ADDR register                                          */
    
    struct {
      __I  uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL_DMA_NEXT_ADDR;
  
  union {
    __I  uint16_t  reg;                             /*!< EEVAL1_DMA_NEXT_ADDR register                                         */
    
    struct {
      __I  uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL1_DMA_NEXT_ADDR;
  
  union {
    __I  uint16_t  reg;                             /*!< EEVAL2_DMA_NEXT_ADDR register                                         */
    
    struct {
      __I  uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL2_DMA_NEXT_ADDR;
  
  union {
    __I  uint16_t  reg;                             /*!< EEVAL_DMA_NEXT_WORD register                                          */
    
    struct {
      __I  uint16_t  words      :  8;               /*!< words bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL_DMA_NEXT_WORD;
  
  union {
    __I  uint16_t  reg;                             /*!< EEVAL1_DMA_NEXT_WORD register                                         */
    
    struct {
      __I  uint16_t  words      :  8;               /*!< words bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL1_DMA_NEXT_WORD;
  
  union {
    __I  uint16_t  reg;                             /*!< EEVAL2_DMA_NEXT_WORD register                                         */
    
    struct {
      __I  uint16_t  words      :  8;               /*!< words bitfield                                                        */
    } bit;                                          /*!< BitSize                                                               */
  } EEVAL2_DMA_NEXT_WORD;
  
  union {
    __IO uint16_t  reg;                             /*!< EDET_PS_VFA register                                                  */
    
    struct {
      __IO uint16_t  edet_ps_vfa:  1;               /*!< edet_ps_vfa bitfield                                                  */
           uint16_t             :  7;
      __IO uint16_t  edet_ps_vfa_pw:  8;            /*!< edet_ps_vfa_pw bitfield                                               */
    } bit;                                          /*!< BitSize                                                               */
  } EDET_PS_VFA;
  
  union {
    __IO uint16_t  reg;                             /*!< EDI_DMA_CHANNEL_SEL register                                          */
    
    struct {
      __IO uint16_t  ch0_sel    :  2;               /*!< ch0_sel bitfield                                                      */
      __IO uint16_t  ch1_sel    :  2;               /*!< ch1_sel bitfield                                                      */
      __IO uint16_t  ch2_sel    :  2;               /*!< ch2_sel bitfield                                                      */
      __IO uint16_t  ch3_sel    :  2;               /*!< ch3_sel bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } EDI_DMA_CHANNEL_SEL;
  
  union {
    __IO uint16_t  reg;                             /*!< EDI0_DMA_CTRL register                                                */
    
    struct {
      __IO uint16_t  length     :  8;               /*!< length bitfield                                                       */
      __IO uint16_t  wrap_off   :  1;               /*!< wrap_off bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } EDI0_DMA_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< EDI1_DMA_CTRL register                                                */
    
    struct {
      __IO uint16_t  length     :  8;               /*!< length bitfield                                                       */
      __IO uint16_t  wrap_off   :  1;               /*!< wrap_off bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } EDI1_DMA_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< EDI2_DMA_CTRL register                                                */
    
    struct {
      __IO uint16_t  length     :  8;               /*!< length bitfield                                                       */
      __IO uint16_t  wrap_off   :  1;               /*!< wrap_off bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } EDI2_DMA_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< EDI3_DMA_CTRL register                                                */
    
    struct {
      __IO uint16_t  length     :  8;               /*!< length bitfield                                                       */
      __IO uint16_t  wrap_off   :  1;               /*!< wrap_off bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } EDI3_DMA_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< EDI0_DMA_ADDR register                                                */
    
    struct {
      __IO uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI0_DMA_ADDR;
  
  union {
    __IO uint16_t  reg;                             /*!< EDI1_DMA_ADDR register                                                */
    
    struct {
      __IO uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI1_DMA_ADDR;
  
  union {
    __IO uint16_t  reg;                             /*!< EDI2_DMA_ADDR register                                                */
    
    struct {
      __IO uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI2_DMA_ADDR;
  
  union {
    __IO uint16_t  reg;                             /*!< EDI3_DMA_ADDR register                                                */
    
    struct {
      __IO uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI3_DMA_ADDR;
  
  union {
    __I  uint16_t  reg;                             /*!< EDI0_DMA_NEXT_ADDR register                                           */
    
    struct {
      __I  uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI0_DMA_NEXT_ADDR;
  
  union {
    __I  uint16_t  reg;                             /*!< EDI1_DMA_NEXT_ADDR register                                           */
    
    struct {
      __I  uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI1_DMA_NEXT_ADDR;
  
  union {
    __I  uint16_t  reg;                             /*!< EDI2_DMA_NEXT_ADDR register                                           */
    
    struct {
      __I  uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI2_DMA_NEXT_ADDR;
  
  union {
    __I  uint16_t  reg;                             /*!< EDI3_DMA_NEXT_ADDR register                                           */
    
    struct {
      __I  uint16_t  addr       : 16;               /*!< addr bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI3_DMA_NEXT_ADDR;
  
  union {
    __I  uint16_t  reg;                             /*!< EDI0_DMA_NEXT_WORD register                                           */
    
    struct {
      __I  uint16_t  word       :  8;               /*!< word bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI0_DMA_NEXT_WORD;
  
  union {
    __I  uint16_t  reg;                             /*!< EDI1_DMA_NEXT_WORD register                                           */
    
    struct {
      __I  uint16_t  word       :  8;               /*!< word bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI1_DMA_NEXT_WORD;
  
  union {
    __I  uint16_t  reg;                             /*!< EDI2_DMA_NEXT_WORD register                                           */
    
    struct {
      __I  uint16_t  word       :  8;               /*!< word bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI2_DMA_NEXT_WORD;
  
  union {
    __I  uint16_t  reg;                             /*!< EDI3_DMA_NEXT_WORD register                                           */
    
    struct {
      __I  uint16_t  word       :  8;               /*!< word bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } EDI3_DMA_NEXT_WORD;
  
  union {
    __IO uint16_t  reg;                             /*!< NFD_CTRL register                                                     */
    
    struct {
      __IO uint16_t  nfd_sens   :  3;               /*!< nfd_sens bitfield                                                     */
      __IO uint16_t  nfd_irq_cfg:  2;               /*!< nfd_irq_cfg bitfield                                                  */
      __I  uint16_t  nfd_max_num:  3;               /*!< nfd_max_num bitfield                                                  */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< NFD_TH register                                                       */
    
    struct {
      __IO uint16_t  nfd_th     : 16;               /*!< nfd_th bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_TH;
  
  union {
    __I  uint16_t  reg;                             /*!< NFD_ECHO1 register                                                    */
    
    struct {
      __I  uint16_t  nfd_echo1  : 16;               /*!< nfd_echo1 bitfield                                                    */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_ECHO1;
  
  union {
    __I  uint16_t  reg;                             /*!< NFD_TS1 register                                                      */
    
    struct {
      __I  uint16_t  nfd_ts1    : 16;               /*!< nfd_ts1 bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_TS1;
  
  union {
    __I  uint16_t  reg;                             /*!< NFD_ECHO2 register                                                    */
    
    struct {
      __I  uint16_t  nfd_echo2  : 16;               /*!< nfd_echo2 bitfield                                                    */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_ECHO2;
  
  union {
    __I  uint16_t  reg;                             /*!< NFD_TS2 register                                                      */
    
    struct {
      __I  uint16_t  nfd_ts2    : 16;               /*!< nfd_ts2 bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_TS2;
  
  union {
    __I  uint16_t  reg;                             /*!< NFD_ECHO3 register                                                    */
    
    struct {
      __I  uint16_t  nfd_echo3  : 16;               /*!< nfd_echo3 bitfield                                                    */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_ECHO3;
  
  union {
    __I  uint16_t  reg;                             /*!< NFD_TS3 register                                                      */
    
    struct {
      __I  uint16_t  nfd_ts3    : 16;               /*!< nfd_ts3 bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_TS3;
  
  union {
    __I  uint16_t  reg;                             /*!< NFD_ECHO4 register                                                    */
    
    struct {
      __I  uint16_t  nfd_echo4  : 16;               /*!< nfd_echo4 bitfield                                                    */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_ECHO4;
  
  union {
    __I  uint16_t  reg;                             /*!< NFD_TS4 register                                                      */
    
    struct {
      __I  uint16_t  nfd_ts4    : 16;               /*!< nfd_ts4 bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_TS4;
  
  union {
    __I  uint16_t  reg;                             /*!< NFD_ECHO5 register                                                    */
    
    struct {
      __I  uint16_t  nfd_echo5  : 16;               /*!< nfd_echo5 bitfield                                                    */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_ECHO5;
  
  union {
    __I  uint16_t  reg;                             /*!< NFD_TS5 register                                                      */
    
    struct {
      __I  uint16_t  nfd_ts5    : 16;               /*!< nfd_ts5 bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } NFD_TS5;
  
  union {
    __IO uint16_t  reg;                             /*!< ASP_CTRL register                                                     */
    
    struct {
      __IO uint16_t  g_ana      :  3;               /*!< g_ana bitfield                                                        */
      __IO uint16_t  fc_x2      :  1;               /*!< fc_x2 bitfield                                                        */
      __IO uint16_t  g_ana_diag :  1;               /*!< g_ana_diag bitfield                                                   */
    } bit;                                          /*!< BitSize                                                               */
  } ASP_CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< ASP_ADC_CTRL register                                                 */
    
    struct {
      __IO uint16_t  soc        :  1;               /*!< soc bitfield                                                          */
      __I  uint16_t  eoc        :  1;               /*!< eoc bitfield                                                          */
      __IO uint16_t  adc_cpu_ctrl:  1;              /*!< adc_cpu_ctrl bitfield                                                 */
    } bit;                                          /*!< BitSize                                                               */
  } ASP_ADC_CTRL;
  
  union {
    __I  uint16_t  reg;                             /*!< ASP_ADC_DTA register                                                  */
    
    struct {
      __I  uint16_t  adc_dta    : 14;               /*!< adc_dta bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } ASP_ADC_DTA;
  __I  uint32_t  RESERVED[5];
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_STATUS register                                                   */
    
    struct {
      __IO uint16_t  eeval_tlh_evt:  1;             /*!< eeval_tlh_evt bitfield                                                */
      __IO uint16_t  eeval_thl_evt:  1;             /*!< eeval_thl_evt bitfield                                                */
      __IO uint16_t  eeval_max_evt:  1;             /*!< eeval_max_evt bitfield                                                */
      __IO uint16_t  eeval_min_evt:  1;             /*!< eeval_min_evt bitfield                                                */
      __IO uint16_t  eeval1_max_evt:  1;            /*!< eeval1_max_evt bitfield                                               */
      __IO uint16_t  eeval2_max_evt:  1;            /*!< eeval2_max_evt bitfield                                               */
      __IO uint16_t  rfm_evt    :  1;               /*!< rfm_evt bitfield                                                      */
      __IO uint16_t  rtm_evt    :  1;               /*!< rtm_evt bitfield                                                      */
      __IO uint16_t  nfd_evt    :  1;               /*!< nfd_evt bitfield                                                      */
      __IO uint16_t  eeval_dma_wrap:  1;            /*!< eeval_dma_wrap bitfield                                               */
      __IO uint16_t  eeval1_dma_wrap:  1;           /*!< eeval1_dma_wrap bitfield                                              */
      __IO uint16_t  eeval2_dma_wrap:  1;           /*!< eeval2_dma_wrap bitfield                                              */
      __IO uint16_t  edi0_dma_wrap:  1;             /*!< edi0_dma_wrap bitfield                                                */
      __IO uint16_t  edi1_dma_wrap:  1;             /*!< edi1_dma_wrap bitfield                                                */
      __IO uint16_t  edi2_dma_wrap:  1;             /*!< edi2_dma_wrap bitfield                                                */
      __IO uint16_t  edi3_dma_wrap:  1;             /*!< edi3_dma_wrap bitfield                                                */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_STATUS;
  __I  uint16_t  RESERVED1;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_MASK register                                                     */
    
    struct {
      __IO uint16_t  mask       : 16;               /*!< mask bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_MASK;
  __I  uint16_t  RESERVED2;
  
  union {
    __O  uint16_t  reg;                             /*!< IRQ_VENABLE register                                                  */
    
    struct {
      __O  uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VENABLE;
  
  union {
    __O  uint16_t  reg;                             /*!< IRQ_VDISABLE register                                                 */
    
    struct {
      __O  uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VDISABLE;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_VMAX register                                                     */
    
    struct {
      __IO uint16_t  vmax       :  5;               /*!< vmax bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VMAX;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_VNO register                                                      */
    
    struct {
      __IO uint16_t  vno        :  5;               /*!< vno bitfield                                                          */
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
    __O  uint16_t  reg;                             /*!< POWER register                                                        */
    
    struct {
      __O  uint16_t  standby    :  1;               /*!< standby bitfield                                                      */
    } bit;                                          /*!< BitSize                                                               */
  } POWER;
  
  union {
    __IO uint16_t  reg;                             /*!< BIST register                                                         */
    
    struct {
      __IO uint16_t  tdr_asp_bist:  1;              /*!< tdr_asp_bist bitfield                                                 */
      __IO uint16_t  dsp_bist   :  1;               /*!< dsp_bist bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } BIST;
  
  union {
    __IO uint16_t  reg;                             /*!< TRIM register                                                         */
    
    struct {
      __IO uint16_t  iconst_trim:  3;               /*!< iconst_trim bitfield                                                  */
      __IO uint16_t  tdr_ic_trim:  3;               /*!< tdr_ic_trim bitfield                                                  */
      __IO uint16_t  dsi3_ib_trim:  3;              /*!< dsi3_ib_trim bitfield                                                 */
           uint16_t             :  4;
      __IO uint16_t  lock       :  1;               /*!< lock bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } TRIM;
  
  union {
    __IO uint16_t  reg;                             /*!< CAP_MEAS_CTRL register                                                */
    
    struct {
      __IO uint16_t  start_diag_meas:  1;           /*!< start_diag_meas bitfield                                              */
      __IO uint16_t  select_diag:  1;               /*!< select_diag bitfield                                                  */
      __I  uint16_t  diag_out_cvddd:  1;            /*!< diag_out_cvddd bitfield                                               */
      __I  uint16_t  diag_out_cvdda:  1;            /*!< diag_out_cvdda bitfield                                               */
    } bit;                                          /*!< BitSize                                                               */
  } CAP_MEAS_CTRL;
  
  union {
    __I  uint16_t  reg;                             /*!< CAP_MEAS_RESULT register                                              */
    
    struct {
      __I  uint16_t  cap_meas_result: 10;           /*!< cap_meas_result bitfield                                              */
    } bit;                                          /*!< BitSize                                                               */
  } CAP_MEAS_RESULT;
  __I  uint16_t  RESERVED[19];
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_STATUS register                                                   */
    
    struct {
      __IO uint16_t  por_wake_up:  1;               /*!< por_wake_up bitfield                                                  */
      __IO uint16_t  dsi3_wake_up:  1;              /*!< dsi3_wake_up bitfield                                                 */
      __IO uint16_t  irq_abort_wake_up:  1;         /*!< irq_abort_wake_up bitfield                                            */
      __IO uint16_t  debug_wake_up:  1;             /*!< debug_wake_up bitfield                                                */
      __IO uint16_t  bist_on    :  1;               /*!< bist_on bitfield                                                      */
      __IO uint16_t  envp_parity_err_evt:  1;       /*!< envp_parity_err_evt bitfield                                          */
      __IO uint16_t  aatg1_parity_err_evt:  1;      /*!< aatg1_parity_err_evt bitfield                                         */
      __IO uint16_t  aatg2_parity_err_evt:  1;      /*!< aatg2_parity_err_evt bitfield                                         */
      __IO uint16_t  cap_meas_ready_evt:  1;        /*!< cap_meas_ready_evt bitfield                                           */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_STATUS;
  __I  uint16_t  RESERVED1;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_MASK register                                                     */
    
    struct {
      __IO uint16_t  mask       :  8;               /*!< mask bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_MASK;
  __I  uint16_t  RESERVED2;
  
  union {
    __O  uint16_t  reg;                             /*!< IRQ_VENABLE register                                                  */
    
    struct {
      __O  uint16_t  vno        :  3;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VENABLE;
  
  union {
    __O  uint16_t  reg;                             /*!< IRQ_VDISABLE register                                                 */
    
    struct {
      __O  uint16_t  vno        :  3;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VDISABLE;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_VMAX register                                                     */
    
    struct {
      __IO uint16_t  vmax       :  4;               /*!< vmax bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VMAX;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_VNO register                                                      */
    
    struct {
      __IO uint16_t  vno        :  4;               /*!< vno bitfield                                                          */
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
    __IO uint16_t  reg;                             /*!< CTRL register                                                         */
    
    struct {
      __IO uint16_t  dac0_cfg   :  2;               /*!< dac0_cfg bitfield                                                     */
      __IO uint16_t  dac1_cfg   :  2;               /*!< dac1_cfg bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } CTRL;
  
  union {
    __IO uint16_t  reg;                             /*!< REG0 register                                                         */
    
    struct {
      __IO uint16_t  reg0       :  8;               /*!< reg0 bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } REG0;
  
  union {
    __IO uint16_t  reg;                             /*!< REG1 register                                                         */
    
    struct {
      __IO uint16_t  reg1       :  8;               /*!< reg1 bitfield                                                         */
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
    __IO uint16_t  reg;                             /*!< ADA_CFG register                                                      */
    
    struct {
      __IO uint16_t  sigsel     :  3;               /*!< sigsel bitfield                                                       */
      __IO uint16_t  chsel      :  2;               /*!< chsel bitfield                                                        */
      __IO uint16_t  en_100k    :  1;               /*!< en_100k bitfield                                                      */
      __IO uint16_t  adc_tsamp  :  2;               /*!< adc_tsamp bitfield                                                    */
      __IO uint16_t  adc_cdiv   :  2;               /*!< adc_cdiv bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } ADA_CFG;
  
  union {
    __IO uint16_t  reg;                             /*!< ADA_CTRL register                                                     */
    
    struct {
      __IO uint16_t  soc        :  1;               /*!< soc bitfield                                                          */
      __I  uint16_t  eoc        :  1;               /*!< eoc bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } ADA_CTRL;
  
  union {
    __I  uint16_t  reg;                             /*!< ADC_DTA register                                                      */
    
    struct {
      __I  uint16_t  adc_dta    : 10;               /*!< adc_dta bitfield                                                      */
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
    __IO uint16_t  reg;                             /*!< DATA register                                                         */
    
    struct {
      __IO uint16_t  data       :  8;               /*!< data bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } DATA;
  __I  uint16_t  RESERVED;
  
  union {
    __IO uint16_t  reg;                             /*!< STAT register                                                         */
    
    struct {
      __I  uint16_t  tx_full    :  1;               /*!< tx_full bitfield                                                      */
      __I  uint16_t  rx_full    :  1;               /*!< rx_full bitfield                                                      */
      __IO uint16_t  tx_ovr     :  1;               /*!< tx_ovr bitfield                                                       */
      __IO uint16_t  rx_ovr     :  1;               /*!< rx_ovr bitfield                                                       */
    } bit;                                          /*!< BitSize                                                               */
  } STAT;
  __I  uint16_t  RESERVED1;
  
  union {
    __IO uint16_t  reg;                             /*!< CTRL register                                                         */
    
    struct {
      __IO uint16_t  txen       :  1;               /*!< txen bitfield                                                         */
      __IO uint16_t  rxen       :  1;               /*!< rxen bitfield                                                         */
      __IO uint16_t  txirqen    :  1;               /*!< txirqen bitfield                                                      */
      __IO uint16_t  rxirqen    :  1;               /*!< rxirqen bitfield                                                      */
      __IO uint16_t  txovrirqen :  1;               /*!< txovrirqen bitfield                                                   */
      __IO uint16_t  rxovrirqen :  1;               /*!< rxovrirqen bitfield                                                   */
      __IO uint16_t  hs         :  1;               /*!< hs bitfield                                                           */
    } bit;                                          /*!< BitSize                                                               */
  } CTRL;
  __I  uint16_t  RESERVED2;
  
  union {
    __IO uint16_t  reg;                             /*!< INTCLR register                                                       */
    
    struct {
      __IO uint16_t  txint      :  1;               /*!< txint bitfield                                                        */
      __IO uint16_t  rxint      :  1;               /*!< rxint bitfield                                                        */
      __IO uint16_t  txovrint   :  1;               /*!< txovrint bitfield                                                     */
      __IO uint16_t  rxovrint   :  1;               /*!< rxovrint bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } INTCLR;
  __I  uint16_t  RESERVED3;
  
  union {
    __IO uint16_t  reg;                             /*!< BAUD_LOW register                                                     */
    
    struct {
      __IO uint16_t  baud_div   : 16;               /*!< baud_div bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } BAUD_LOW;
  
  union {
    __IO uint16_t  reg;                             /*!< BAUD_HIGH register                                                    */
    
    struct {
      __IO uint16_t  baud_div   : 16;               /*!< baud_div bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } BAUD_HIGH;
  __I  uint32_t  RESERVED4[7];
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_STATUS register                                                   */
    
    struct {
      __IO uint16_t  txint      :  1;               /*!< txint bitfield                                                        */
      __IO uint16_t  rxint      :  1;               /*!< rxint bitfield                                                        */
      __IO uint16_t  txovrint   :  1;               /*!< txovrint bitfield                                                     */
      __IO uint16_t  rxovrint   :  1;               /*!< rxovrint bitfield                                                     */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_STATUS;
  __I  uint16_t  RESERVED5;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_MASK register                                                     */
    
    struct {
      __IO uint16_t  mask       :  4;               /*!< mask bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_MASK;
  __I  uint16_t  RESERVED6;
  
  union {
    __O  uint16_t  reg;                             /*!< IRQ_VENABLE register                                                  */
    
    struct {
      __O  uint16_t  vno        :  2;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VENABLE;
  
  union {
    __O  uint16_t  reg;                             /*!< IRQ_VDISABLE register                                                 */
    
    struct {
      __O  uint16_t  vno        :  2;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VDISABLE;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_VMAX register                                                     */
    
    struct {
      __IO uint16_t  vmax       :  3;               /*!< vmax bitfield                                                         */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VMAX;
  
  union {
    __IO uint16_t  reg;                             /*!< IRQ_VNO register                                                      */
    
    struct {
      __IO uint16_t  vno        :  3;               /*!< vno bitfield                                                          */
    } bit;                                          /*!< BitSize                                                               */
  } IRQ_VNO;
} UART_Type;


/* --------------------  End of section using anonymous unions  ------------------- */



/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */

#define WDOG_BASE                       0x40000000UL
#define SYS_STATE_BASE                  0x40000100UL
#define CRC16_BASE                      0x40000200UL
#define OTP0_CTRL_BASE                  0x40000300UL
#define OTP1_CTRL_BASE                  0x40000400UL
#define EEPROM_CTRL_BASE                0x40000500UL
#define GPIO_BASE                       0x50000000UL
#define SWTIMER_BASE                    0x50000100UL
#define DSI3_BASE                       0x50000200UL
#define BRG_BASE                        0x50000300UL
#define DSP_BASE                        0x50000400UL
#define SYSTEM_CTRL_BASE                0x50000500UL
#define DAC_CTRL_BASE                   0x50000600UL
#define ADA_BASE                        0x50000700UL
#define UART_BASE                       0x5F000000UL


/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#define WDOG                            ((WDOG_Type               *) WDOG_BASE)
#define SYS_STATE                       ((SYS_STATE_Type          *) SYS_STATE_BASE)
#define CRC16                           ((CRC16_Type              *) CRC16_BASE)
#define OTP0_CTRL                       ((OTP0_CTRL_Type          *) OTP0_CTRL_BASE)
#define OTP1_CTRL                       ((OTP0_CTRL_Type          *) OTP1_CTRL_BASE)
#define EEPROM_CTRL                     ((EEPROM_CTRL_Type        *) EEPROM_CTRL_BASE)
#define GPIO                            ((GPIO_Type               *) GPIO_BASE)
#define SWTIMER                         ((SWTIMER_Type            *) SWTIMER_BASE)
#define DSI3                            ((DSI3_Type               *) DSI3_BASE)
#define BRG                             ((BRG_Type                *) BRG_BASE)
#define DSP                             ((DSP_Type                *) DSP_BASE)
#define SYSTEM_CTRL                     ((SYSTEM_CTRL_Type        *) SYSTEM_CTRL_BASE)
#define DAC_CTRL                        ((DAC_CTRL_Type           *) DAC_CTRL_BASE)
#define ADA                             ((ADA_Type                *) ADA_BASE)
#define UART                            ((UART_Type               *) UART_BASE)


/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group m52417b */

#ifdef __cplusplus
}
#endif


#endif  /* m52417b_H */

