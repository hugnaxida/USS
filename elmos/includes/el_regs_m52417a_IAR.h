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

#ifndef __EL_REGS_M52417A_H__
#define __EL_REGS_M52417A_H__

#include "elmos/includes/io_m52417a.h"

// Register definition mapping from CMSIS style to ELMOS style

// module WDOG instance WDOG

#define WDOG_CONTROL                              (WDOG->CONTROL.reg)
#define WDOG_CONTROL_bit                          (WDOG->CONTROL.bit)

#define E_WDOG_CONTROL_RUN_ENABLE                 (0x0001u)
#define E_WDOG_CONTROL_RESTART                    (0x0002u)

#define WDOG_WINDOW                               (WDOG->WINDOW.reg)
#define WDOG_WINDOW_bit                           (WDOG->WINDOW.bit)

#define E_WDOG_WINDOW_ENABLE                      (0x0010u)

#define WDOG_PRESCALER                            (WDOG->PRESCALER.reg)
#define WDOG_PRESCALER_bit                        (WDOG->PRESCALER.bit)

#define WDOG_RELOAD                               (WDOG->RELOAD.reg)
#define WDOG_RELOAD_bit                           (WDOG->RELOAD.bit)

#define WDOG_COUNTER                              (WDOG->COUNTER.reg)
#define WDOG_COUNTER_bit                          (WDOG->COUNTER.bit)

// module SYS_STATE instance SYS_STATE

#define SYS_STATE_CONTROL                         (SYS_STATE->CONTROL.reg)
#define SYS_STATE_CONTROL_bit                     (SYS_STATE->CONTROL.bit)

#define SYS_STATE_RESET_STATUS                    (SYS_STATE->RESET_STATUS.reg)
#define SYS_STATE_RESET_STATUS_bit                (SYS_STATE->RESET_STATUS.bit)

#define E_SYS_STATE_RESET_STATUS_VCORE_OK         (0x0001u)
#define E_SYS_STATE_RESET_STATUS_SYS_CLK_FAIL     (0x0002u)
#define E_SYS_STATE_RESET_STATUS_CPU_LOCKUP       (0x0004u)
#define E_SYS_STATE_RESET_STATUS_DEBUG_RESET      (0x0008u)
#define E_SYS_STATE_RESET_STATUS_SOFTWARE         (0x0010u)
#define E_SYS_STATE_RESET_STATUS_SRAM_PARITY      (0x0020u)
#define E_SYS_STATE_RESET_STATUS_OTP_ECC_FAIL     (0x0040u)
#define E_SYS_STATE_RESET_STATUS_WATCHDOG_WINDOW  (0x0080u)
#define E_SYS_STATE_RESET_STATUS_WATCHDOG         (0x0100u)
#define E_SYS_STATE_RESET_STATUS_WATCHDOG_ZERO    (0x0200u)
#define E_SYS_STATE_RESET_STATUS_CRC16_MISMATCH   (0x0400u)
#define E_SYS_STATE_RESET_STATUS_TRIM_PARITY      (0x0800u)

#define SYS_STATE_RESET_STATUS_CLEAR              (SYS_STATE->RESET_STATUS_CLEAR.reg)
#define SYS_STATE_RESET_STATUS_CLEAR_bit          (SYS_STATE->RESET_STATUS_CLEAR.bit)

#define SYS_STATE_RESET_ENABLE                    (SYS_STATE->RESET_ENABLE.reg)
#define SYS_STATE_RESET_ENABLE_bit                (SYS_STATE->RESET_ENABLE.bit)

#define E_SYS_STATE_RESET_ENABLE_CPU_LOCKUP       (0x0001u)
#define E_SYS_STATE_RESET_ENABLE_DEBUG_RESET      (0x0002u)
#define E_SYS_STATE_RESET_ENABLE_SOFTWARE         (0x0004u)
#define E_SYS_STATE_RESET_ENABLE_SRAM_PARITY      (0x0008u)
#define E_SYS_STATE_RESET_ENABLE_OTP_ECC_FAIL     (0x0010u)
#define E_SYS_STATE_RESET_ENABLE_WATCHDOG_WINDOW  (0x0020u)
#define E_SYS_STATE_RESET_ENABLE_WATCHDOG         (0x0040u)
#define E_SYS_STATE_RESET_ENABLE_WATCHDOG_ZERO    (0x0080u)
#define E_SYS_STATE_RESET_ENABLE_CRC16_MISMATCH   (0x0100u)
#define E_SYS_STATE_RESET_ENABLE_TRIM_PARITY      (0x0200u)

#define SYS_STATE_SW_RESET                        (SYS_STATE->SW_RESET.reg)
#define SYS_STATE_SW_RESET_bit                    (SYS_STATE->SW_RESET.bit)

#define E_SYS_STATE_SW_RESET_POR_FLAG             (0x0001u)
#define E_SYS_STATE_SW_RESET_SW_RESET             (0x0010u)

#define SYS_STATE_SW_RESET_FLAG_CLEAR             (SYS_STATE->SW_RESET_FLAG_CLEAR.reg)
#define SYS_STATE_SW_RESET_FLAG_CLEAR_bit         (SYS_STATE->SW_RESET_FLAG_CLEAR.bit)

#define SYS_STATE_ENABLE_DEBUG                    (SYS_STATE->ENABLE_DEBUG.reg)
#define SYS_STATE_ENABLE_DEBUG_bit                (SYS_STATE->ENABLE_DEBUG.bit)

#define E_SYS_STATE_ENABLE_DEBUG_ENABLE           (0x0001u)
#define E_SYS_STATE_ENABLE_DEBUG_EXIT_BOOT_LOADER (0x0002u)
#define E_SYS_STATE_ENABLE_DEBUG_SIGNATURE_BOOT   (0x0004u)
#define E_SYS_STATE_ENABLE_DEBUG_SIGNATURE_NEW    (0x0008u)

#define SYS_STATE_WDOG_CLK_FREQ                   (SYS_STATE->WDOG_CLK_FREQ.reg)
#define SYS_STATE_WDOG_CLK_FREQ_bit               (SYS_STATE->WDOG_CLK_FREQ.bit)

#define SYS_STATE_SYS_CLK_MEAS                    (SYS_STATE->SYS_CLK_MEAS.reg)
#define SYS_STATE_SYS_CLK_MEAS_bit                (SYS_STATE->SYS_CLK_MEAS.bit)

#define SYS_STATE_SYS_OSC_TRIM                    (SYS_STATE->SYS_OSC_TRIM.reg)
#define SYS_STATE_SYS_OSC_TRIM_bit                (SYS_STATE->SYS_OSC_TRIM.bit)

#define E_SYS_STATE_SYS_OSC_TRIM_LOCK             (0x0100u)

#define SYS_STATE_VECTOR_TABLE_REMAP              (SYS_STATE->VECTOR_TABLE_REMAP.reg)
#define SYS_STATE_VECTOR_TABLE_REMAP_bit          (SYS_STATE->VECTOR_TABLE_REMAP.bit)

#define E_SYS_STATE_VECTOR_TABLE_REMAP_SEL        (0x0004u)
#define E_SYS_STATE_VECTOR_TABLE_REMAP_LOCK       (0x0008u)
#define E_SYS_STATE_VECTOR_TABLE_REMAP_LOCK_TABLE_BASE (0x0040u)

#define SYS_STATE_VECTOR_TABLE_BASE0              (SYS_STATE->VECTOR_TABLE_BASE0.reg)
#define SYS_STATE_VECTOR_TABLE_BASE0_bit          (SYS_STATE->VECTOR_TABLE_BASE0.bit)

#define SYS_STATE_VECTOR_TABLE_BASE1              (SYS_STATE->VECTOR_TABLE_BASE1.reg)
#define SYS_STATE_VECTOR_TABLE_BASE1_bit          (SYS_STATE->VECTOR_TABLE_BASE1.bit)

#define SYS_STATE_TEST_MASTER_DATA_L              (SYS_STATE->TEST_MASTER_DATA_L.reg)
#define SYS_STATE_TEST_MASTER_DATA_L_bit          (SYS_STATE->TEST_MASTER_DATA_L.bit)

#define SYS_STATE_TEST_MASTER_DATA_H              (SYS_STATE->TEST_MASTER_DATA_H.reg)
#define SYS_STATE_TEST_MASTER_DATA_H_bit          (SYS_STATE->TEST_MASTER_DATA_H.bit)

#define SYS_STATE_TEST_MASTER_ADDR                (SYS_STATE->TEST_MASTER_ADDR.reg)
#define SYS_STATE_TEST_MASTER_ADDR_bit            (SYS_STATE->TEST_MASTER_ADDR.bit)

#define E_SYS_STATE_TEST_MASTER_ADDR_WRITE        (0x1000u)

#define SYS_STATE_TEST_SIGNATURE                  (SYS_STATE->TEST_SIGNATURE.reg)
#define SYS_STATE_TEST_SIGNATURE_bit              (SYS_STATE->TEST_SIGNATURE.bit)

#define SYS_STATE_IRQ_STATUS                      (SYS_STATE->IRQ_STATUS.reg)
#define SYS_STATE_IRQ_STATUS_bit                  (SYS_STATE->IRQ_STATUS.bit)

#define E_SYS_STATE_IRQ_STATUS_CPU_LOCKUP         (0x0001u)
#define E_SYS_STATE_IRQ_STATUS_DEBUG_RESET        (0x0002u)
#define E_SYS_STATE_IRQ_STATUS_SOFTWARE           (0x0004u)
#define E_SYS_STATE_IRQ_STATUS_SRAM_PARITY        (0x0008u)
#define E_SYS_STATE_IRQ_STATUS_OTP_ECC_FAIL       (0x0010u)
#define E_SYS_STATE_IRQ_STATUS_WATCHDOG_WINDOW    (0x0020u)
#define E_SYS_STATE_IRQ_STATUS_WATCHDOG           (0x0040u)
#define E_SYS_STATE_IRQ_STATUS_WATCHDOG_ZERO      (0x0080u)
#define E_SYS_STATE_IRQ_STATUS_CRC16_MISMATCH     (0x0100u)
#define E_SYS_STATE_IRQ_STATUS_TRIM_PARITY        (0x0200u)

#define SYS_STATE_IRQ_MASK                        (SYS_STATE->IRQ_MASK.reg)
#define SYS_STATE_IRQ_MASK_bit                    (SYS_STATE->IRQ_MASK.bit)

#define SYS_STATE_IRQ_VENABLE                     (SYS_STATE->IRQ_VENABLE.reg)
#define SYS_STATE_IRQ_VENABLE_bit                 (SYS_STATE->IRQ_VENABLE.bit)

#define SYS_STATE_IRQ_VDISABLE                    (SYS_STATE->IRQ_VDISABLE.reg)
#define SYS_STATE_IRQ_VDISABLE_bit                (SYS_STATE->IRQ_VDISABLE.bit)

#define SYS_STATE_IRQ_VMAX                        (SYS_STATE->IRQ_VMAX.reg)
#define SYS_STATE_IRQ_VMAX_bit                    (SYS_STATE->IRQ_VMAX.bit)

#define SYS_STATE_IRQ_VNO                         (SYS_STATE->IRQ_VNO.reg)
#define SYS_STATE_IRQ_VNO_bit                     (SYS_STATE->IRQ_VNO.bit)

// module CRC16 instance CRC16

#define CRC16_START0                              (CRC16->START0.reg)
#define CRC16_START0_bit                          (CRC16->START0.bit)

#define CRC16_START1                              (CRC16->START1.reg)
#define CRC16_START1_bit                          (CRC16->START1.bit)

#define CRC16_LENGTH0                             (CRC16->LENGTH0.reg)
#define CRC16_LENGTH0_bit                         (CRC16->LENGTH0.bit)

#define CRC16_LENGTH1                             (CRC16->LENGTH1.reg)
#define CRC16_LENGTH1_bit                         (CRC16->LENGTH1.bit)

#define CRC16_EXPECTED_CRC                        (CRC16->EXPECTED_CRC.reg)
#define CRC16_EXPECTED_CRC_bit                    (CRC16->EXPECTED_CRC.bit)

#define CRC16_CONFIG                              (CRC16->CONFIG.reg)
#define CRC16_CONFIG_bit                          (CRC16->CONFIG.bit)

#define E_CRC16_CONFIG_KEEP_SUM                   (0x0008u)

#define CRC16_STATUS                              (CRC16->STATUS.reg)
#define CRC16_STATUS_bit                          (CRC16->STATUS.bit)

#define CRC16_CRC_SUM                             (CRC16->CRC_SUM.reg)
#define CRC16_CRC_SUM_bit                         (CRC16->CRC_SUM.bit)

// module OTP_CTRL instance OTP0_CTRL

#define OTP0_CTRL_READ_CONFIG                     (OTP0_CTRL->READ_CONFIG.reg)
#define OTP0_CTRL_READ_CONFIG_bit                 (OTP0_CTRL->READ_CONFIG.bit)

#define E_OTP_CTRL_READ_CONFIG_DIFFERENTIAL       (0x0001u)
#define E_OTP_CTRL_READ_CONFIG_REDUNDANT          (0x0002u)

#define OTP0_CTRL_PROG_CONFIG                     (OTP0_CTRL->PROG_CONFIG.reg)
#define OTP0_CTRL_PROG_CONFIG_bit                 (OTP0_CTRL->PROG_CONFIG.bit)

#define OTP0_CTRL_PROG_CONTROL                    (OTP0_CTRL->PROG_CONTROL.reg)
#define OTP0_CTRL_PROG_CONTROL_bit                (OTP0_CTRL->PROG_CONTROL.bit)

#define E_OTP_CTRL_PROG_CONTROL_OTP_PROG          (0x0001u)
#define E_OTP_CTRL_PROG_CONTROL_DIFFERENTIAL      (0x0002u)

#define OTP0_CTRL_WDATA0                          (OTP0_CTRL->WDATA0.reg)
#define OTP0_CTRL_WDATA0_bit                      (OTP0_CTRL->WDATA0.bit)

#define OTP0_CTRL_WDATA1                          (OTP0_CTRL->WDATA1.reg)
#define OTP0_CTRL_WDATA1_bit                      (OTP0_CTRL->WDATA1.bit)

#define OTP0_CTRL_WADDR                           (OTP0_CTRL->WADDR.reg)
#define OTP0_CTRL_WADDR_bit                       (OTP0_CTRL->WADDR.bit)

#define OTP0_CTRL_PROG_STATUS                     (OTP0_CTRL->PROG_STATUS.reg)
#define OTP0_CTRL_PROG_STATUS_bit                 (OTP0_CTRL->PROG_STATUS.bit)

#define E_OTP_CTRL_PROG_STATUS_BUSY               (0x0010u)
#define E_OTP_CTRL_PROG_STATUS_FAIL0              (0x0020u)
#define E_OTP_CTRL_PROG_STATUS_FAIL1              (0x0040u)

#define OTP0_CTRL_BIT_SOAK_STATUS                 (OTP0_CTRL->BIT_SOAK_STATUS.reg)
#define OTP0_CTRL_BIT_SOAK_STATUS_bit             (OTP0_CTRL->BIT_SOAK_STATUS.bit)

#define E_OTP_CTRL_BIT_SOAK_STATUS_TAKE           (0x0001u)

#define OTP0_CTRL_PROTECT                         (OTP0_CTRL->PROTECT.reg)
#define OTP0_CTRL_PROTECT_bit                     (OTP0_CTRL->PROTECT.bit)

#define OTP0_CTRL_BOOT_PROTECT                    (OTP0_CTRL->BOOT_PROTECT.reg)
#define OTP0_CTRL_BOOT_PROTECT_bit                (OTP0_CTRL->BOOT_PROTECT.bit)

#define OTP0_CTRL_IO_FLAG                         (OTP0_CTRL->IO_FLAG.reg)
#define OTP0_CTRL_IO_FLAG_bit                     (OTP0_CTRL->IO_FLAG.bit)

#define E_OTP_CTRL_IO_FLAG_FLAG                   (0x0001u)

#define OTP0_CTRL_TEST_LOCK                       (OTP0_CTRL->TEST_LOCK.reg)
#define OTP0_CTRL_TEST_LOCK_bit                   (OTP0_CTRL->TEST_LOCK.bit)

#define E_OTP_CTRL_TEST_LOCK_LOCK                 (0x0001u)

#define OTP0_CTRL_TEST_TRP_CONFIG                 (OTP0_CTRL->TEST_TRP_CONFIG.reg)
#define OTP0_CTRL_TEST_TRP_CONFIG_bit             (OTP0_CTRL->TEST_TRP_CONFIG.bit)

#define E_OTP_CTRL_TEST_TRP_CONFIG_SEL            (0x0100u)

#define OTP0_CTRL_TEST_MR                         (OTP0_CTRL->TEST_MR.reg)
#define OTP0_CTRL_TEST_MR_bit                     (OTP0_CTRL->TEST_MR.bit)

#define E_OTP_CTRL_TEST_MR_READ_SEL               (0x0100u)
#define E_OTP_CTRL_TEST_MR_PROG_SEL               (0x0200u)

#define OTP0_CTRL_TEST_FORCE                      (OTP0_CTRL->TEST_FORCE.reg)
#define OTP0_CTRL_TEST_FORCE_bit                  (OTP0_CTRL->TEST_FORCE.bit)

#define E_OTP_CTRL_TEST_FORCE_FORCE               (0x0001u)
#define E_OTP_CTRL_TEST_FORCE_CK                  (0x0002u)
#define E_OTP_CTRL_TEST_FORCE_SEL                 (0x0004u)
#define E_OTP_CTRL_TEST_FORCE_WE                  (0x0008u)
#define E_OTP_CTRL_TEST_FORCE_OE                  (0x0010u)

#define OTP0_CTRL_MPP                             (OTP0_CTRL->MPP.reg)
#define OTP0_CTRL_MPP_bit                         (OTP0_CTRL->MPP.bit)

#define OTP0_CTRL_MRR                             (OTP0_CTRL->MRR.reg)
#define OTP0_CTRL_MRR_bit                         (OTP0_CTRL->MRR.bit)

#define OTP0_CTRL_VRR                             (OTP0_CTRL->VRR.reg)
#define OTP0_CTRL_VRR_bit                         (OTP0_CTRL->VRR.bit)

#define OTP0_CTRL_ERASE                           (OTP0_CTRL->ERASE.reg)
#define OTP0_CTRL_ERASE_bit                       (OTP0_CTRL->ERASE.bit)

#define E_OTP_CTRL_ERASE_START                    (0x0001u)
#define E_OTP_CTRL_ERASE_READY                    (0x0002u)

#define OTP0_CTRL_TEST_CELL_STRESS                (OTP0_CTRL->TEST_CELL_STRESS.reg)
#define OTP0_CTRL_TEST_CELL_STRESS_bit            (OTP0_CTRL->TEST_CELL_STRESS.bit)

#define E_OTP_CTRL_TEST_CELL_STRESS_STRESS        (0x0001u)

#define OTP0_CTRL_TEST_SEL_VAL                    (OTP0_CTRL->TEST_SEL_VAL.reg)
#define OTP0_CTRL_TEST_SEL_VAL_bit                (OTP0_CTRL->TEST_SEL_VAL.bit)

#define E_OTP_CTRL_TEST_SEL_VAL_VPP_E_SEL         (0x0001u)
#define E_OTP_CTRL_TEST_SEL_VAL_VPP_E_VAL         (0x0002u)
#define E_OTP_CTRL_TEST_SEL_VAL_VRR_E_SEL         (0x0004u)
#define E_OTP_CTRL_TEST_SEL_VAL_VRR_E_VAL         (0x0008u)
#define E_OTP_CTRL_TEST_SEL_VAL_EHV_E_SEL         (0x0010u)
#define E_OTP_CTRL_TEST_SEL_VAL_EHV_E_VAL         (0x0020u)
#define E_OTP_CTRL_TEST_SEL_VAL_DBEN_SEL          (0x0040u)
#define E_OTP_CTRL_TEST_SEL_VAL_DBEN_VAL          (0x0080u)
#define E_OTP_CTRL_TEST_SEL_VAL_MASK_IPS_CLKS     (0x0100u)

#define OTP0_CTRL_TEST_ECC                        (OTP0_CTRL->TEST_ECC.reg)
#define OTP0_CTRL_TEST_ECC_bit                    (OTP0_CTRL->TEST_ECC.bit)

#define E_OTP_CTRL_TEST_ECC_ECC_1BIT              (0x1000u)
#define E_OTP_CTRL_TEST_ECC_ECC_2BIT              (0x2000u)
#define E_OTP_CTRL_TEST_ECC_DISABLE_READ_ECC      (0x4000u)
#define E_OTP_CTRL_TEST_ECC_FORCE_ECC_WRITE_1     (0x8000u)

#define OTP0_CTRL_MDB                             (OTP0_CTRL->MDB.reg)
#define OTP0_CTRL_MDB_bit                         (OTP0_CTRL->MDB.bit)

// module OTP_CTRL instance OTP1_CTRL

#define OTP1_CTRL_READ_CONFIG                     (OTP1_CTRL->READ_CONFIG.reg)
#define OTP1_CTRL_READ_CONFIG_bit                 (OTP1_CTRL->READ_CONFIG.bit)

#define E_OTP_CTRL_READ_CONFIG_DIFFERENTIAL       (0x0001u)
#define E_OTP_CTRL_READ_CONFIG_REDUNDANT          (0x0002u)

#define OTP1_CTRL_PROG_CONFIG                     (OTP1_CTRL->PROG_CONFIG.reg)
#define OTP1_CTRL_PROG_CONFIG_bit                 (OTP1_CTRL->PROG_CONFIG.bit)

#define OTP1_CTRL_PROG_CONTROL                    (OTP1_CTRL->PROG_CONTROL.reg)
#define OTP1_CTRL_PROG_CONTROL_bit                (OTP1_CTRL->PROG_CONTROL.bit)

#define E_OTP_CTRL_PROG_CONTROL_OTP_PROG          (0x0001u)
#define E_OTP_CTRL_PROG_CONTROL_DIFFERENTIAL      (0x0002u)

#define OTP1_CTRL_WDATA0                          (OTP1_CTRL->WDATA0.reg)
#define OTP1_CTRL_WDATA0_bit                      (OTP1_CTRL->WDATA0.bit)

#define OTP1_CTRL_WDATA1                          (OTP1_CTRL->WDATA1.reg)
#define OTP1_CTRL_WDATA1_bit                      (OTP1_CTRL->WDATA1.bit)

#define OTP1_CTRL_WADDR                           (OTP1_CTRL->WADDR.reg)
#define OTP1_CTRL_WADDR_bit                       (OTP1_CTRL->WADDR.bit)

#define OTP1_CTRL_PROG_STATUS                     (OTP1_CTRL->PROG_STATUS.reg)
#define OTP1_CTRL_PROG_STATUS_bit                 (OTP1_CTRL->PROG_STATUS.bit)

#define E_OTP_CTRL_PROG_STATUS_BUSY               (0x0010u)
#define E_OTP_CTRL_PROG_STATUS_FAIL0              (0x0020u)
#define E_OTP_CTRL_PROG_STATUS_FAIL1              (0x0040u)

#define OTP1_CTRL_BIT_SOAK_STATUS                 (OTP1_CTRL->BIT_SOAK_STATUS.reg)
#define OTP1_CTRL_BIT_SOAK_STATUS_bit             (OTP1_CTRL->BIT_SOAK_STATUS.bit)

#define E_OTP_CTRL_BIT_SOAK_STATUS_TAKE           (0x0001u)

#define OTP1_CTRL_PROTECT                         (OTP1_CTRL->PROTECT.reg)
#define OTP1_CTRL_PROTECT_bit                     (OTP1_CTRL->PROTECT.bit)

#define OTP1_CTRL_BOOT_PROTECT                    (OTP1_CTRL->BOOT_PROTECT.reg)
#define OTP1_CTRL_BOOT_PROTECT_bit                (OTP1_CTRL->BOOT_PROTECT.bit)

#define OTP1_CTRL_IO_FLAG                         (OTP1_CTRL->IO_FLAG.reg)
#define OTP1_CTRL_IO_FLAG_bit                     (OTP1_CTRL->IO_FLAG.bit)

#define E_OTP_CTRL_IO_FLAG_FLAG                   (0x0001u)

#define OTP1_CTRL_TEST_LOCK                       (OTP1_CTRL->TEST_LOCK.reg)
#define OTP1_CTRL_TEST_LOCK_bit                   (OTP1_CTRL->TEST_LOCK.bit)

#define E_OTP_CTRL_TEST_LOCK_LOCK                 (0x0001u)

#define OTP1_CTRL_TEST_TRP_CONFIG                 (OTP1_CTRL->TEST_TRP_CONFIG.reg)
#define OTP1_CTRL_TEST_TRP_CONFIG_bit             (OTP1_CTRL->TEST_TRP_CONFIG.bit)

#define E_OTP_CTRL_TEST_TRP_CONFIG_SEL            (0x0100u)

#define OTP1_CTRL_TEST_MR                         (OTP1_CTRL->TEST_MR.reg)
#define OTP1_CTRL_TEST_MR_bit                     (OTP1_CTRL->TEST_MR.bit)

#define E_OTP_CTRL_TEST_MR_READ_SEL               (0x0100u)
#define E_OTP_CTRL_TEST_MR_PROG_SEL               (0x0200u)

#define OTP1_CTRL_TEST_FORCE                      (OTP1_CTRL->TEST_FORCE.reg)
#define OTP1_CTRL_TEST_FORCE_bit                  (OTP1_CTRL->TEST_FORCE.bit)

#define E_OTP_CTRL_TEST_FORCE_FORCE               (0x0001u)
#define E_OTP_CTRL_TEST_FORCE_CK                  (0x0002u)
#define E_OTP_CTRL_TEST_FORCE_SEL                 (0x0004u)
#define E_OTP_CTRL_TEST_FORCE_WE                  (0x0008u)
#define E_OTP_CTRL_TEST_FORCE_OE                  (0x0010u)

#define OTP1_CTRL_MPP                             (OTP1_CTRL->MPP.reg)
#define OTP1_CTRL_MPP_bit                         (OTP1_CTRL->MPP.bit)

#define OTP1_CTRL_MRR                             (OTP1_CTRL->MRR.reg)
#define OTP1_CTRL_MRR_bit                         (OTP1_CTRL->MRR.bit)

#define OTP1_CTRL_VRR                             (OTP1_CTRL->VRR.reg)
#define OTP1_CTRL_VRR_bit                         (OTP1_CTRL->VRR.bit)

#define OTP1_CTRL_ERASE                           (OTP1_CTRL->ERASE.reg)
#define OTP1_CTRL_ERASE_bit                       (OTP1_CTRL->ERASE.bit)

#define E_OTP_CTRL_ERASE_START                    (0x0001u)
#define E_OTP_CTRL_ERASE_READY                    (0x0002u)

#define OTP1_CTRL_TEST_CELL_STRESS                (OTP1_CTRL->TEST_CELL_STRESS.reg)
#define OTP1_CTRL_TEST_CELL_STRESS_bit            (OTP1_CTRL->TEST_CELL_STRESS.bit)

#define E_OTP_CTRL_TEST_CELL_STRESS_STRESS        (0x0001u)

#define OTP1_CTRL_TEST_SEL_VAL                    (OTP1_CTRL->TEST_SEL_VAL.reg)
#define OTP1_CTRL_TEST_SEL_VAL_bit                (OTP1_CTRL->TEST_SEL_VAL.bit)

#define E_OTP_CTRL_TEST_SEL_VAL_VPP_E_SEL         (0x0001u)
#define E_OTP_CTRL_TEST_SEL_VAL_VPP_E_VAL         (0x0002u)
#define E_OTP_CTRL_TEST_SEL_VAL_VRR_E_SEL         (0x0004u)
#define E_OTP_CTRL_TEST_SEL_VAL_VRR_E_VAL         (0x0008u)
#define E_OTP_CTRL_TEST_SEL_VAL_EHV_E_SEL         (0x0010u)
#define E_OTP_CTRL_TEST_SEL_VAL_EHV_E_VAL         (0x0020u)
#define E_OTP_CTRL_TEST_SEL_VAL_DBEN_SEL          (0x0040u)
#define E_OTP_CTRL_TEST_SEL_VAL_DBEN_VAL          (0x0080u)
#define E_OTP_CTRL_TEST_SEL_VAL_MASK_IPS_CLKS     (0x0100u)

#define OTP1_CTRL_TEST_ECC                        (OTP1_CTRL->TEST_ECC.reg)
#define OTP1_CTRL_TEST_ECC_bit                    (OTP1_CTRL->TEST_ECC.bit)

#define E_OTP_CTRL_TEST_ECC_ECC_1BIT              (0x1000u)
#define E_OTP_CTRL_TEST_ECC_ECC_2BIT              (0x2000u)
#define E_OTP_CTRL_TEST_ECC_DISABLE_READ_ECC      (0x4000u)
#define E_OTP_CTRL_TEST_ECC_FORCE_ECC_WRITE_1     (0x8000u)

#define OTP1_CTRL_MDB                             (OTP1_CTRL->MDB.reg)
#define OTP1_CTRL_MDB_bit                         (OTP1_CTRL->MDB.bit)

// module EEPROM_CTRL instance EEPROM_CTRL

#define EEPROM_CTRL_MODE                          (EEPROM_CTRL->MODE.reg)
#define EEPROM_CTRL_MODE_bit                      (EEPROM_CTRL->MODE.bit)

#define E_EEPROM_CTRL_MODE_ERASE                  (0x0001u)
#define E_EEPROM_CTRL_MODE_PROGRAM                (0x0002u)
#define E_EEPROM_CTRL_MODE_MARGIN_READ            (0x0004u)

#define EEPROM_CTRL_STATUS                        (EEPROM_CTRL->STATUS.reg)
#define EEPROM_CTRL_STATUS_bit                    (EEPROM_CTRL->STATUS.bit)

#define E_EEPROM_CTRL_STATUS_BUSY                 (0x0001u)

#define EEPROM_CTRL_LOCK_L                        (EEPROM_CTRL->LOCK_L.reg)
#define EEPROM_CTRL_LOCK_L_bit                    (EEPROM_CTRL->LOCK_L.bit)

#define EEPROM_CTRL_LOCK_U                        (EEPROM_CTRL->LOCK_U.reg)
#define EEPROM_CTRL_LOCK_U_bit                    (EEPROM_CTRL->LOCK_U.bit)

#define EEPROM_CTRL_LOCK_CNT                      (EEPROM_CTRL->LOCK_CNT.reg)
#define EEPROM_CTRL_LOCK_CNT_bit                  (EEPROM_CTRL->LOCK_CNT.bit)

#define EEPROM_CTRL_LOCK_L_FREEZE                 (EEPROM_CTRL->LOCK_L_FREEZE.reg)
#define EEPROM_CTRL_LOCK_L_FREEZE_bit             (EEPROM_CTRL->LOCK_L_FREEZE.bit)

#define EEPROM_CTRL_LOCK_U_FREEZE                 (EEPROM_CTRL->LOCK_U_FREEZE.reg)
#define EEPROM_CTRL_LOCK_U_FREEZE_bit             (EEPROM_CTRL->LOCK_U_FREEZE.bit)

#define EEPROM_CTRL_IP_ENABLE                     (EEPROM_CTRL->IP_ENABLE.reg)
#define EEPROM_CTRL_IP_ENABLE_bit                 (EEPROM_CTRL->IP_ENABLE.bit)

#define E_EEPROM_CTRL_IP_ENABLE_ENABLE            (0x0001u)

#define EEPROM_CTRL_MARGIN_TRIM                   (EEPROM_CTRL->MARGIN_TRIM.reg)
#define EEPROM_CTRL_MARGIN_TRIM_bit               (EEPROM_CTRL->MARGIN_TRIM.bit)

#define EEPROM_CTRL_TIMEOUT_L                     (EEPROM_CTRL->TIMEOUT_L.reg)
#define EEPROM_CTRL_TIMEOUT_L_bit                 (EEPROM_CTRL->TIMEOUT_L.bit)

#define EEPROM_CTRL_TIMEOUT_H                     (EEPROM_CTRL->TIMEOUT_H.reg)
#define EEPROM_CTRL_TIMEOUT_H_bit                 (EEPROM_CTRL->TIMEOUT_H.bit)

#define EEPROM_CTRL_IRQ_STATUS                    (EEPROM_CTRL->IRQ_STATUS.reg)
#define EEPROM_CTRL_IRQ_STATUS_bit                (EEPROM_CTRL->IRQ_STATUS.bit)

#define E_EEPROM_CTRL_IRQ_STATUS_TIMEOUT          (0x0001u)
#define E_EEPROM_CTRL_IRQ_STATUS_INVALID_ADDR     (0x0002u)
#define E_EEPROM_CTRL_IRQ_STATUS_IP_OFF_ACCESS    (0x0004u)

#define EEPROM_CTRL_IRQ_MASK                      (EEPROM_CTRL->IRQ_MASK.reg)
#define EEPROM_CTRL_IRQ_MASK_bit                  (EEPROM_CTRL->IRQ_MASK.bit)

#define EEPROM_CTRL_IRQ_VENABLE                   (EEPROM_CTRL->IRQ_VENABLE.reg)
#define EEPROM_CTRL_IRQ_VENABLE_bit               (EEPROM_CTRL->IRQ_VENABLE.bit)

#define EEPROM_CTRL_IRQ_VDISABLE                  (EEPROM_CTRL->IRQ_VDISABLE.reg)
#define EEPROM_CTRL_IRQ_VDISABLE_bit              (EEPROM_CTRL->IRQ_VDISABLE.bit)

#define EEPROM_CTRL_IRQ_VMAX                      (EEPROM_CTRL->IRQ_VMAX.reg)
#define EEPROM_CTRL_IRQ_VMAX_bit                  (EEPROM_CTRL->IRQ_VMAX.bit)

#define EEPROM_CTRL_IRQ_VNO                       (EEPROM_CTRL->IRQ_VNO.reg)
#define EEPROM_CTRL_IRQ_VNO_bit                   (EEPROM_CTRL->IRQ_VNO.bit)

// module GPIO instance GPIO

#define GPIO_DATA_OUT                             (GPIO->DATA_OUT.reg)
#define GPIO_DATA_OUT_bit                         (GPIO->DATA_OUT.bit)

#define GPIO_DATA_OE                              (GPIO->DATA_OE.reg)
#define GPIO_DATA_OE_bit                          (GPIO->DATA_OE.bit)

#define GPIO_DATA_IN                              (GPIO->DATA_IN.reg)
#define GPIO_DATA_IN_bit                          (GPIO->DATA_IN.bit)

#define GPIO_DATA_IE                              (GPIO->DATA_IE.reg)
#define GPIO_DATA_IE_bit                          (GPIO->DATA_IE.bit)

#define GPIO_DATA_PUE                             (GPIO->DATA_PUE.reg)
#define GPIO_DATA_PUE_bit                         (GPIO->DATA_PUE.bit)

#define GPIO_IOMUX                                (GPIO->IOMUX.reg)
#define GPIO_IOMUX_bit                            (GPIO->IOMUX.bit)

#define E_GPIO_IOMUX_UART_PORT                    (0x0004u)

#define GPIO_IRQ_STATUS                           (GPIO->IRQ_STATUS.reg)
#define GPIO_IRQ_STATUS_bit                       (GPIO->IRQ_STATUS.bit)

#define E_GPIO_IRQ_STATUS_EVT_POS_0               (0x0001u)
#define E_GPIO_IRQ_STATUS_EVT_NEG_0               (0x0002u)
#define E_GPIO_IRQ_STATUS_EVT_POS_1               (0x0004u)
#define E_GPIO_IRQ_STATUS_EVT_NEG_1               (0x0008u)
#define E_GPIO_IRQ_STATUS_EVT_POS_2               (0x0010u)
#define E_GPIO_IRQ_STATUS_EVT_NEG_2               (0x0020u)
#define E_GPIO_IRQ_STATUS_EVT_POS_3               (0x0040u)
#define E_GPIO_IRQ_STATUS_EVT_NEG_3               (0x0080u)

#define GPIO_IRQ_MASK                             (GPIO->IRQ_MASK.reg)
#define GPIO_IRQ_MASK_bit                         (GPIO->IRQ_MASK.bit)

#define GPIO_IRQ_VENABLE                          (GPIO->IRQ_VENABLE.reg)
#define GPIO_IRQ_VENABLE_bit                      (GPIO->IRQ_VENABLE.bit)

#define GPIO_IRQ_VDISABLE                         (GPIO->IRQ_VDISABLE.reg)
#define GPIO_IRQ_VDISABLE_bit                     (GPIO->IRQ_VDISABLE.bit)

#define GPIO_IRQ_VMAX                             (GPIO->IRQ_VMAX.reg)
#define GPIO_IRQ_VMAX_bit                         (GPIO->IRQ_VMAX.bit)

#define GPIO_IRQ_VNO                              (GPIO->IRQ_VNO.reg)
#define GPIO_IRQ_VNO_bit                          (GPIO->IRQ_VNO.bit)

// module SWTIMER instance SWTIMER

#define SWTIMER_CONFIG                            (SWTIMER->CONFIG.reg)
#define SWTIMER_CONFIG_bit                        (SWTIMER->CONFIG.bit)

#define SWTIMER_COMMAND                           (SWTIMER->COMMAND.reg)
#define SWTIMER_COMMAND_bit                       (SWTIMER->COMMAND.bit)

#define SWTIMER_CNT0_RELOAD                       (SWTIMER->CNT0_RELOAD.reg)
#define SWTIMER_CNT0_RELOAD_bit                   (SWTIMER->CNT0_RELOAD.bit)

#define SWTIMER_CNT1_RELOAD                       (SWTIMER->CNT1_RELOAD.reg)
#define SWTIMER_CNT1_RELOAD_bit                   (SWTIMER->CNT1_RELOAD.bit)

#define SWTIMER_DIV0_RELOAD                       (SWTIMER->DIV0_RELOAD.reg)
#define SWTIMER_DIV0_RELOAD_bit                   (SWTIMER->DIV0_RELOAD.bit)

#define SWTIMER_DIV1_RELOAD                       (SWTIMER->DIV1_RELOAD.reg)
#define SWTIMER_DIV1_RELOAD_bit                   (SWTIMER->DIV1_RELOAD.bit)

#define SWTIMER_CNT0_VALUE                        (SWTIMER->CNT0_VALUE.reg)
#define SWTIMER_CNT0_VALUE_bit                    (SWTIMER->CNT0_VALUE.bit)

#define SWTIMER_CNT1_VALUE                        (SWTIMER->CNT1_VALUE.reg)
#define SWTIMER_CNT1_VALUE_bit                    (SWTIMER->CNT1_VALUE.bit)

#define SWTIMER_IRQ_STATUS                        (SWTIMER->IRQ_STATUS.reg)
#define SWTIMER_IRQ_STATUS_bit                    (SWTIMER->IRQ_STATUS.bit)

#define SWTIMER_IRQ_MASK                          (SWTIMER->IRQ_MASK.reg)
#define SWTIMER_IRQ_MASK_bit                      (SWTIMER->IRQ_MASK.bit)

#define SWTIMER_IRQ_VENABLE                       (SWTIMER->IRQ_VENABLE.reg)
#define SWTIMER_IRQ_VENABLE_bit                   (SWTIMER->IRQ_VENABLE.bit)

#define SWTIMER_IRQ_VDISABLE                      (SWTIMER->IRQ_VDISABLE.reg)
#define SWTIMER_IRQ_VDISABLE_bit                  (SWTIMER->IRQ_VDISABLE.bit)

#define SWTIMER_IRQ_VMAX                          (SWTIMER->IRQ_VMAX.reg)
#define SWTIMER_IRQ_VMAX_bit                      (SWTIMER->IRQ_VMAX.bit)

#define SWTIMER_IRQ_VNO                           (SWTIMER->IRQ_VNO.reg)
#define SWTIMER_IRQ_VNO_bit                       (SWTIMER->IRQ_VNO.bit)

// module DSI3 instance DSI3

#define DSI3_ANALOG_CTRL                          (DSI3->ANALOG_CTRL.reg)
#define DSI3_ANALOG_CTRL_bit                      (DSI3->ANALOG_CTRL.bit)

#define E_DSI3_ANALOG_CTRL_DSI3_ENABLE            (0x0001u)
#define E_DSI3_ANALOG_CTRL_RCC_ENABLE             (0x0002u)
#define E_DSI3_ANALOG_CTRL_RCC_LCM                (0x0004u)
#define E_DSI3_ANALOG_CTRL_FCC_HYST_SEL           (0x0008u)
#define E_DSI3_ANALOG_CTRL_FCC_FORCE_CONNECT      (0x0010u)
#define E_DSI3_ANALOG_CTRL_FCC_FORCE_BYPASS       (0x0020u)

#define DSI3_CONFIG                               (DSI3->CONFIG.reg)
#define DSI3_CONFIG_bit                           (DSI3->CONFIG.bit)

#define E_DSI3_CONFIG_CRC_CHECK                   (0x0001u)
#define E_DSI3_CONFIG_CRC_ADD                     (0x0002u)
#define E_DSI3_CONFIG_AUTO_RESP                   (0x0004u)
#define E_DSI3_CONFIG_AUTO_TIMER                  (0x0008u)
#define E_DSI3_CONFIG_AUTO_SYNC                   (0x0010u)
#define E_DSI3_CONFIG_DISABLE_SYNC_VALI           (0x0020u)
#define E_DSI3_CONFIG_AUTO_BLANK_OFF              (0x0100u)
#define E_DSI3_CONFIG_AUTO_BLANK_ON               (0x0200u)
#define E_DSI3_CONFIG_PDCM_SEED_SEL               (0x0400u)
#define E_DSI3_CONFIG_TIMER_START_SEL             (0x0800u)

#define DSI3_CTRL                                 (DSI3->CTRL.reg)
#define DSI3_CTRL_bit                             (DSI3->CTRL.bit)

#define E_DSI3_CTRL_ABORT_FCC                     (0x0001u)
#define E_DSI3_CTRL_ABORT_RCC                     (0x0002u)
#define E_DSI3_CTRL_START_RCC                     (0x0004u)
#define E_DSI3_CTRL_CLR_FCC_LOW_FLAG              (0x0008u)
#define E_DSI3_CTRL_START_TIMER                   (0x0010u)
#define E_DSI3_CTRL_RESET_TIMER                   (0x0020u)
#define E_DSI3_CTRL_SET_BLANKING_OFF              (0x0040u)
#define E_DSI3_CTRL_SET_BLANKING_ON               (0x0080u)

#define DSI3_STATUS                               (DSI3->STATUS.reg)
#define DSI3_STATUS_bit                           (DSI3->STATUS.bit)

#define E_DSI3_STATUS_FCC_IDLE                    (0x0004u)
#define E_DSI3_STATUS_FCC_SIGNAL                  (0x0008u)
#define E_DSI3_STATUS_FCC_LOW_FLAG                (0x0010u)
#define E_DSI3_STATUS_FCC_BLANKING                (0x0020u)
#define E_DSI3_STATUS_TIMER_STATUS                (0x0040u)
#define E_DSI3_STATUS_SYNC_CNT_ERR                (0x0080u)

#define DSI3_DISCOVERY_CTRL                       (DSI3->DISCOVERY_CTRL.reg)
#define DSI3_DISCOVERY_CTRL_bit                   (DSI3->DISCOVERY_CTRL.bit)

#define E_DSI3_DISCOVERY_CTRL_DISC_RAMP_ON        (0x0001u)
#define E_DSI3_DISCOVERY_CTRL_CURR_CMP_OUT        (0x0002u)
#define E_DSI3_DISCOVERY_CTRL_CURR_CMP_CAP        (0x0004u)
#define E_DSI3_DISCOVERY_CTRL_AUTO_DISC_RESP      (0x0010u)
#define E_DSI3_DISCOVERY_CTRL_AUTO_DISC_ACCEPT    (0x0020u)

#define DSI3_CLK_1US                              (DSI3->CLK_1US.reg)
#define DSI3_CLK_1US_bit                          (DSI3->CLK_1US.bit)

#define DSI3_SYNC_CNT                             (DSI3->SYNC_CNT.reg)
#define DSI3_SYNC_CNT_bit                         (DSI3->SYNC_CNT.bit)

#define DSI3_FCC_COMMAND_LOW                      (DSI3->FCC_COMMAND_LOW.reg)
#define DSI3_FCC_COMMAND_LOW_bit                  (DSI3->FCC_COMMAND_LOW.bit)

#define DSI3_FCC_COMMAND_HIGH                     (DSI3->FCC_COMMAND_HIGH.reg)
#define DSI3_FCC_COMMAND_HIGH_bit                 (DSI3->FCC_COMMAND_HIGH.bit)

#define DSI3_RCC_DMA_ADDR_LOW                     (DSI3->RCC_DMA_ADDR_LOW.reg)
#define DSI3_RCC_DMA_ADDR_LOW_bit                 (DSI3->RCC_DMA_ADDR_LOW.bit)

#define DSI3_RCC_DMA_ADDR_HIGH                    (DSI3->RCC_DMA_ADDR_HIGH.reg)
#define DSI3_RCC_DMA_ADDR_HIGH_bit                (DSI3->RCC_DMA_ADDR_HIGH.bit)

#define DSI3_RCC_BUFFER_LENGTH                    (DSI3->RCC_BUFFER_LENGTH.reg)
#define DSI3_RCC_BUFFER_LENGTH_bit                (DSI3->RCC_BUFFER_LENGTH.bit)

#define DSI3_RCC_BYTE_CNT                         (DSI3->RCC_BYTE_CNT.reg)
#define DSI3_RCC_BYTE_CNT_bit                     (DSI3->RCC_BYTE_CNT.bit)

#define DSI3_TIMER_COMPARE_A                      (DSI3->TIMER_COMPARE_A.reg)
#define DSI3_TIMER_COMPARE_A_bit                  (DSI3->TIMER_COMPARE_A.bit)

#define DSI3_TIMER_COMPARE_B                      (DSI3->TIMER_COMPARE_B.reg)
#define DSI3_TIMER_COMPARE_B_bit                  (DSI3->TIMER_COMPARE_B.bit)

#define DSI3_TIMER_COMPARE_C                      (DSI3->TIMER_COMPARE_C.reg)
#define DSI3_TIMER_COMPARE_C_bit                  (DSI3->TIMER_COMPARE_C.bit)

#define DSI3_TIMER_COUNTER                        (DSI3->TIMER_COUNTER.reg)
#define DSI3_TIMER_COUNTER_bit                    (DSI3->TIMER_COUNTER.bit)

#define DSI3_TIMER_CAPTURE                        (DSI3->TIMER_CAPTURE.reg)
#define DSI3_TIMER_CAPTURE_bit                    (DSI3->TIMER_CAPTURE.bit)

#define DSI3_SOURCE_ID                            (DSI3->SOURCE_ID.reg)
#define DSI3_SOURCE_ID_bit                        (DSI3->SOURCE_ID.bit)

#define DSI3_IRQ_STATUS                           (DSI3->IRQ_STATUS.reg)
#define DSI3_IRQ_STATUS_bit                       (DSI3->IRQ_STATUS.bit)

#define E_DSI3_IRQ_STATUS_SYNC_EVT                (0x0001u)
#define E_DSI3_IRQ_STATUS_CMD_EVT                 (0x0002u)
#define E_DSI3_IRQ_STATUS_PDCM_EVT                (0x0004u)
#define E_DSI3_IRQ_STATUS_DISC_EVT                (0x0008u)
#define E_DSI3_IRQ_STATUS_CRC_ERR_EVT             (0x0010u)
#define E_DSI3_IRQ_STATUS_PDCM_ERR_EVT            (0x0020u)
#define E_DSI3_IRQ_STATUS_DISC_ERR_EVT            (0x0040u)
#define E_DSI3_IRQ_STATUS_FCC_ERROR               (0x0080u)
#define E_DSI3_IRQ_STATUS_START_ERR_EVT           (0x0100u)
#define E_DSI3_IRQ_STATUS_TIMER_A_EVT             (0x0200u)
#define E_DSI3_IRQ_STATUS_TIMER_B_EVT             (0x0400u)
#define E_DSI3_IRQ_STATUS_TIMER_C_EVT             (0x0800u)
#define E_DSI3_IRQ_STATUS_RCC_FINISH              (0x1000u)
#define E_DSI3_IRQ_STATUS_RCC_READY               (0x2000u)
#define E_DSI3_IRQ_STATUS_SYNC_CNT_EVT            (0x4000u)
#define E_DSI3_IRQ_STATUS_DISC_CURR_EVT           (0x8000u)

#define DSI3_IRQ_MASK                             (DSI3->IRQ_MASK.reg)
#define DSI3_IRQ_MASK_bit                         (DSI3->IRQ_MASK.bit)

#define DSI3_IRQ_VENABLE                          (DSI3->IRQ_VENABLE.reg)
#define DSI3_IRQ_VENABLE_bit                      (DSI3->IRQ_VENABLE.bit)

#define DSI3_IRQ_VDISABLE                         (DSI3->IRQ_VDISABLE.reg)
#define DSI3_IRQ_VDISABLE_bit                     (DSI3->IRQ_VDISABLE.bit)

#define DSI3_IRQ_VMAX                             (DSI3->IRQ_VMAX.reg)
#define DSI3_IRQ_VMAX_bit                         (DSI3->IRQ_VMAX.bit)

#define DSI3_IRQ_VNO                              (DSI3->IRQ_VNO.reg)
#define DSI3_IRQ_VNO_bit                          (DSI3->IRQ_VNO.bit)

// module BRG instance BRG

#define BRG_BRG_CTRL                              (BRG->BRG_CTRL.reg)
#define BRG_BRG_CTRL_bit                          (BRG->BRG_CTRL.bit)

#define E_BRG_CTRL_BURST_EN                       (0x0001u)
#define E_BRG_CTRL_BURST_BRK                      (0x0002u)
#define E_BRG_CTRL_BURST_EN_DIAG                  (0x0010u)

#define BRG_BRG_CFG                               (BRG->BRG_CFG.reg)
#define BRG_BRG_CFG_bit                           (BRG->BRG_CFG.bit)

#define E_BRG_CFG_SEL_INC                         (0x2000u)

#define BRG_BRG_FC                                (BRG->BRG_FC.reg)
#define BRG_BRG_FC_bit                            (BRG->BRG_FC.bit)

#define BRG_BRG_F0                                (BRG->BRG_F0.reg)
#define BRG_BRG_F0_bit                            (BRG->BRG_F0.bit)

#define BRG_BRG_F1                                (BRG->BRG_F1.reg)
#define BRG_BRG_F1_bit                            (BRG->BRG_F1.bit)

#define BRG_BRG_FDELTA                            (BRG->BRG_FDELTA.reg)
#define BRG_BRG_FDELTA_bit                        (BRG->BRG_FDELTA.bit)

#define BRG_BRG_CODE                              (BRG->BRG_CODE.reg)
#define BRG_BRG_CODE_bit                          (BRG->BRG_CODE.bit)

#define BRG_TDR_CTRL                              (BRG->TDR_CTRL.reg)
#define BRG_TDR_CTRL_bit                          (BRG->TDR_CTRL.bit)

#define E_BRG_TDR_CTRL_SEL_ISRC                   (0x0020u)

#define BRG_TDR_STATUS                            (BRG->TDR_STATUS.reg)
#define BRG_TDR_STATUS_bit                        (BRG->TDR_STATUS.bit)

#define E_BRG_TDR_STATUS_DRV1_STA                 (0x0001u)
#define E_BRG_TDR_STATUS_DRV2_STA                 (0x0002u)
#define E_BRG_TDR_STATUS_DRVS_STA                 (0x0004u)
#define E_BRG_TDR_STATUS_VTANK_OV                 (0x0008u)

// module DSP instance DSP

#define DSP_DSP_CTRL                              (DSP->DSP_CTRL.reg)
#define DSP_DSP_CTRL_bit                          (DSP->DSP_CTRL.bit)

#define E_DSP_CTRL_DSP_ON                         (0x0001u)
#define E_DSP_CTRL_DSP_PWR_DWN                    (0x0002u)
#define E_DSP_CTRL_DSP_ON_STATE                   (0x0004u)

#define DSP_ENVP_CFG                              (DSP->ENVP_CFG.reg)
#define DSP_ENVP_CFG_bit                          (DSP->ENVP_CFG.bit)

#define E_DSP_ENVP_CFG_ENVP_AFC                   (0x0008u)
#define E_DSP_ENVP_CFG_DSR_SEL                    (0x0200u)
#define E_DSP_ENVP_CFG_FSPI_SEL                   (0x0400u)
#define E_DSP_ENVP_CFG_ASPI_SEL                   (0x0800u)

#define DSP_ENVP_CTRL                             (DSP->ENVP_CTRL.reg)
#define DSP_ENVP_CTRL_bit                         (DSP->ENVP_CTRL.bit)

#define E_DSP_ENVP_CTRL_ENVP_AFC_BRK              (0x0001u)
#define E_DSP_ENVP_CTRL_ENVP_RESTART              (0x0002u)

#define DSP_ENVP_ENV_RAW                          (DSP->ENVP_ENV_RAW.reg)
#define DSP_ENVP_ENV_RAW_bit                      (DSP->ENVP_ENV_RAW.bit)

#define DSP_ENVP_FILT_CFG                         (DSP->ENVP_FILT_CFG.reg)
#define DSP_ENVP_FILT_CFG_bit                     (DSP->ENVP_FILT_CFG.bit)

#define E_DSP_ENVP_FILT_CFG_F1_COEFF_SEL          (0x1000u)
#define E_DSP_ENVP_FILT_CFG_F2_COEFF_SEL          (0x2000u)

#define DSP_ENVP_COEFF_3_2_1_0                    (DSP->ENVP_COEFF_3_2_1_0.reg)
#define DSP_ENVP_COEFF_3_2_1_0_bit                (DSP->ENVP_COEFF_3_2_1_0.bit)

#define DSP_ENVP_COEFF_7_6_5_4                    (DSP->ENVP_COEFF_7_6_5_4.reg)
#define DSP_ENVP_COEFF_7_6_5_4_bit                (DSP->ENVP_COEFF_7_6_5_4.bit)

#define DSP_ENVP_COEFF_11_10_9_8                  (DSP->ENVP_COEFF_11_10_9_8.reg)
#define DSP_ENVP_COEFF_11_10_9_8_bit              (DSP->ENVP_COEFF_11_10_9_8.bit)

#define DSP_ENVP_COEFF_15_14_13_12                (DSP->ENVP_COEFF_15_14_13_12.reg)
#define DSP_ENVP_COEFF_15_14_13_12_bit            (DSP->ENVP_COEFF_15_14_13_12.bit)

#define DSP_ENVP_COEFF_19_18_17_16                (DSP->ENVP_COEFF_19_18_17_16.reg)
#define DSP_ENVP_COEFF_19_18_17_16_bit            (DSP->ENVP_COEFF_19_18_17_16.bit)

#define DSP_ENVP_COEFF_23_22_21_20                (DSP->ENVP_COEFF_23_22_21_20.reg)
#define DSP_ENVP_COEFF_23_22_21_20_bit            (DSP->ENVP_COEFF_23_22_21_20.bit)

#define DSP_ENVP_COEFF_27_26_25_24                (DSP->ENVP_COEFF_27_26_25_24.reg)
#define DSP_ENVP_COEFF_27_26_25_24_bit            (DSP->ENVP_COEFF_27_26_25_24.bit)

#define DSP_ENVP_COEFF_31_30_29_28                (DSP->ENVP_COEFF_31_30_29_28.reg)
#define DSP_ENVP_COEFF_31_30_29_28_bit            (DSP->ENVP_COEFF_31_30_29_28.bit)

#define DSP_FTC_CTRL                              (DSP->FTC_CTRL.reg)
#define DSP_FTC_CTRL_bit                          (DSP->FTC_CTRL.bit)

#define E_DSP_FTC_CTRL_FTC_EN                     (0x0008u)

#define DSP_ENV_FTC                               (DSP->ENV_FTC.reg)
#define DSP_ENV_FTC_bit                           (DSP->ENV_FTC.bit)

#define DSP_AMPD_CTRL                             (DSP->AMPD_CTRL.reg)
#define DSP_AMPD_CTRL_bit                         (DSP->AMPD_CTRL.bit)

#define DSP_STC_CTRL                              (DSP->STC_CTRL.reg)
#define DSP_STC_CTRL_bit                          (DSP->STC_CTRL.bit)

#define E_DSP_STC_CTRL_AMPD_STC_MOD               (0x0080u)

#define DSP_STC_TB                                (DSP->STC_TB.reg)
#define DSP_STC_TB_bit                            (DSP->STC_TB.bit)

#define DSP_AMPD_ENV                              (DSP->AMPD_ENV.reg)
#define DSP_AMPD_ENV_bit                          (DSP->AMPD_ENV.bit)

#define DSP_MT                                    (DSP->MT.reg)
#define DSP_MT_bit                                (DSP->MT.bit)

#define DSP_RFM_CTRL                              (DSP->RFM_CTRL.reg)
#define DSP_RFM_CTRL_bit                          (DSP->RFM_CTRL.bit)

#define E_DSP_RFM_CTRL_RFM_STATUS                 (0x0400u)

#define DSP_RFM_CROSS_COUNT                       (DSP->RFM_CROSS_COUNT.reg)
#define DSP_RFM_CROSS_COUNT_bit                   (DSP->RFM_CROSS_COUNT.bit)

#define DSP_RFM_COUNTS                            (DSP->RFM_COUNTS.reg)
#define DSP_RFM_COUNTS_bit                        (DSP->RFM_COUNTS.bit)

#define DSP_RFM_SAMPLES                           (DSP->RFM_SAMPLES.reg)
#define DSP_RFM_SAMPLES_bit                       (DSP->RFM_SAMPLES.bit)

#define DSP_RTM                                   (DSP->RTM.reg)
#define DSP_RTM_bit                               (DSP->RTM.bit)

#define E_DSP_RTM_RTM_RT_END                      (0x2000u)

#define DSP_ATG_CTRL                              (DSP->ATG_CTRL.reg)
#define DSP_ATG_CTRL_bit                          (DSP->ATG_CTRL.bit)

#define E_DSP_ATG_CTRL_ATG_CFG                    (0x0200u)

#define DSP_ATG_TH                                (DSP->ATG_TH.reg)
#define DSP_ATG_TH_bit                            (DSP->ATG_TH.bit)

#define DSP_AATG1_CTRL                            (DSP->AATG1_CTRL.reg)
#define DSP_AATG1_CTRL_bit                        (DSP->AATG1_CTRL.bit)

#define E_DSP_AATG1_CTRL_AATG1_OFF                (0x0100u)
#define E_DSP_AATG1_CTRL_AATG1_BUF_FULL           (0x0200u)
#define E_DSP_AATG1_CTRL_AATG1_BUF_HALF           (0x0400u)

#define DSP_AATG2_CTRL                            (DSP->AATG2_CTRL.reg)
#define DSP_AATG2_CTRL_bit                        (DSP->AATG2_CTRL.bit)

#define E_DSP_AATG2_CTRL_AATG2_OFF                (0x0100u)
#define E_DSP_AATG2_CTRL_AATG2_BUF_FULL           (0x0200u)
#define E_DSP_AATG2_CTRL_AATG2_BUF_HALF           (0x0400u)

#define DSP_STG_TH                                (DSP->STG_TH.reg)
#define DSP_STG_TH_bit                            (DSP->STG_TH.bit)

#define DSP_STG_TB                                (DSP->STG_TB.reg)
#define DSP_STG_TB_bit                            (DSP->STG_TB.bit)

#define DSP_STG_STEP                              (DSP->STG_STEP.reg)
#define DSP_STG_STEP_bit                          (DSP->STG_STEP.bit)

#define DSP_EEVAL_CTRL                            (DSP->EEVAL_CTRL.reg)
#define DSP_EEVAL_CTRL_bit                        (DSP->EEVAL_CTRL.bit)

#define E_DSP_EEVAL_CTRL_EEVAL_DMA_VAL            (0x0080u)

#define DSP_EEVAL_DMA_CTRL                        (DSP->EEVAL_DMA_CTRL.reg)
#define DSP_EEVAL_DMA_CTRL_bit                    (DSP->EEVAL_DMA_CTRL.bit)

#define E_DSP_EEVAL_DMA_CTRL_WRAP_OFF             (0x0100u)

#define DSP_EEVAL1_DMA_CTRL                       (DSP->EEVAL1_DMA_CTRL.reg)
#define DSP_EEVAL1_DMA_CTRL_bit                   (DSP->EEVAL1_DMA_CTRL.bit)

#define DSP_EEVAL2_DMA_CTRL                       (DSP->EEVAL2_DMA_CTRL.reg)
#define DSP_EEVAL2_DMA_CTRL_bit                   (DSP->EEVAL2_DMA_CTRL.bit)

#define E_DSP_EEVAL1_DMA_CTRL_WRAP_OFF            (0x0100u)

#define DSP_EEVAL_DMA_ADDR                        (DSP->EEVAL_DMA_ADDR.reg)
#define DSP_EEVAL_DMA_ADDR_bit                    (DSP->EEVAL_DMA_ADDR.bit)

#define DSP_EEVAL1_DMA_ADDR                       (DSP->EEVAL1_DMA_ADDR.reg)
#define DSP_EEVAL1_DMA_ADDR_bit                   (DSP->EEVAL1_DMA_ADDR.bit)

#define DSP_EEVAL2_DMA_ADDR                       (DSP->EEVAL2_DMA_ADDR.reg)
#define DSP_EEVAL2_DMA_ADDR_bit                   (DSP->EEVAL2_DMA_ADDR.bit)

#define DSP_EEVAL_DMA_NEXT_ADDR                   (DSP->EEVAL_DMA_NEXT_ADDR.reg)
#define DSP_EEVAL_DMA_NEXT_ADDR_bit               (DSP->EEVAL_DMA_NEXT_ADDR.bit)

#define DSP_EEVAL1_DMA_NEXT_ADDR                  (DSP->EEVAL1_DMA_NEXT_ADDR.reg)
#define DSP_EEVAL1_DMA_NEXT_ADDR_bit              (DSP->EEVAL1_DMA_NEXT_ADDR.bit)

#define DSP_EEVAL2_DMA_NEXT_ADDR                  (DSP->EEVAL2_DMA_NEXT_ADDR.reg)
#define DSP_EEVAL2_DMA_NEXT_ADDR_bit              (DSP->EEVAL2_DMA_NEXT_ADDR.bit)

#define DSP_EEVAL_DMA_NEXT_WORD                   (DSP->EEVAL_DMA_NEXT_WORD.reg)
#define DSP_EEVAL_DMA_NEXT_WORD_bit               (DSP->EEVAL_DMA_NEXT_WORD.bit)

#define DSP_EEVAL1_DMA_NEXT_WORD                  (DSP->EEVAL1_DMA_NEXT_WORD.reg)
#define DSP_EEVAL1_DMA_NEXT_WORD_bit              (DSP->EEVAL1_DMA_NEXT_WORD.bit)

#define DSP_EEVAL2_DMA_NEXT_WORD                  (DSP->EEVAL2_DMA_NEXT_WORD.reg)
#define DSP_EEVAL2_DMA_NEXT_WORD_bit              (DSP->EEVAL2_DMA_NEXT_WORD.bit)

#define DSP_EDET_PS_VFA                           (DSP->EDET_PS_VFA.reg)
#define DSP_EDET_PS_VFA_bit                       (DSP->EDET_PS_VFA.bit)

#define E_DSP_EDET_PS_VFA_EDET_PS_VFA             (0x0001u)

#define DSP_EDI_DMA_CHANNEL_SEL                   (DSP->EDI_DMA_CHANNEL_SEL.reg)
#define DSP_EDI_DMA_CHANNEL_SEL_bit               (DSP->EDI_DMA_CHANNEL_SEL.bit)

#define DSP_EDI0_DMA_CTRL                         (DSP->EDI0_DMA_CTRL.reg)
#define DSP_EDI0_DMA_CTRL_bit                     (DSP->EDI0_DMA_CTRL.bit)

#define DSP_EDI1_DMA_CTRL                         (DSP->EDI1_DMA_CTRL.reg)
#define DSP_EDI1_DMA_CTRL_bit                     (DSP->EDI1_DMA_CTRL.bit)

#define DSP_EDI2_DMA_CTRL                         (DSP->EDI2_DMA_CTRL.reg)
#define DSP_EDI2_DMA_CTRL_bit                     (DSP->EDI2_DMA_CTRL.bit)

#define DSP_EDI3_DMA_CTRL                         (DSP->EDI3_DMA_CTRL.reg)
#define DSP_EDI3_DMA_CTRL_bit                     (DSP->EDI3_DMA_CTRL.bit)

#define E_DSP_EDI0_DMA_CTRL_WRAP_OFF              (0x0100u)

#define DSP_EDI0_DMA_ADDR                         (DSP->EDI0_DMA_ADDR.reg)
#define DSP_EDI0_DMA_ADDR_bit                     (DSP->EDI0_DMA_ADDR.bit)

#define DSP_EDI1_DMA_ADDR                         (DSP->EDI1_DMA_ADDR.reg)
#define DSP_EDI1_DMA_ADDR_bit                     (DSP->EDI1_DMA_ADDR.bit)

#define DSP_EDI2_DMA_ADDR                         (DSP->EDI2_DMA_ADDR.reg)
#define DSP_EDI2_DMA_ADDR_bit                     (DSP->EDI2_DMA_ADDR.bit)

#define DSP_EDI3_DMA_ADDR                         (DSP->EDI3_DMA_ADDR.reg)
#define DSP_EDI3_DMA_ADDR_bit                     (DSP->EDI3_DMA_ADDR.bit)

#define DSP_EDI0_DMA_NEXT_ADDR                    (DSP->EDI0_DMA_NEXT_ADDR.reg)
#define DSP_EDI0_DMA_NEXT_ADDR_bit                (DSP->EDI0_DMA_NEXT_ADDR.bit)

#define DSP_EDI1_DMA_NEXT_ADDR                    (DSP->EDI1_DMA_NEXT_ADDR.reg)
#define DSP_EDI1_DMA_NEXT_ADDR_bit                (DSP->EDI1_DMA_NEXT_ADDR.bit)

#define DSP_EDI2_DMA_NEXT_ADDR                    (DSP->EDI2_DMA_NEXT_ADDR.reg)
#define DSP_EDI2_DMA_NEXT_ADDR_bit                (DSP->EDI2_DMA_NEXT_ADDR.bit)

#define DSP_EDI3_DMA_NEXT_ADDR                    (DSP->EDI3_DMA_NEXT_ADDR.reg)
#define DSP_EDI3_DMA_NEXT_ADDR_bit                (DSP->EDI3_DMA_NEXT_ADDR.bit)

#define DSP_EDI0_DMA_NEXT_WORD                    (DSP->EDI0_DMA_NEXT_WORD.reg)
#define DSP_EDI0_DMA_NEXT_WORD_bit                (DSP->EDI0_DMA_NEXT_WORD.bit)

#define DSP_EDI1_DMA_NEXT_WORD                    (DSP->EDI1_DMA_NEXT_WORD.reg)
#define DSP_EDI1_DMA_NEXT_WORD_bit                (DSP->EDI1_DMA_NEXT_WORD.bit)

#define DSP_EDI2_DMA_NEXT_WORD                    (DSP->EDI2_DMA_NEXT_WORD.reg)
#define DSP_EDI2_DMA_NEXT_WORD_bit                (DSP->EDI2_DMA_NEXT_WORD.bit)

#define DSP_EDI3_DMA_NEXT_WORD                    (DSP->EDI3_DMA_NEXT_WORD.reg)
#define DSP_EDI3_DMA_NEXT_WORD_bit                (DSP->EDI3_DMA_NEXT_WORD.bit)

#define DSP_NFD_CTRL                              (DSP->NFD_CTRL.reg)
#define DSP_NFD_CTRL_bit                          (DSP->NFD_CTRL.bit)

#define DSP_NFD_TH                                (DSP->NFD_TH.reg)
#define DSP_NFD_TH_bit                            (DSP->NFD_TH.bit)

#define DSP_NFD_ECHO1                             (DSP->NFD_ECHO1.reg)
#define DSP_NFD_ECHO1_bit                         (DSP->NFD_ECHO1.bit)

#define DSP_NFD_TS1                               (DSP->NFD_TS1.reg)
#define DSP_NFD_TS1_bit                           (DSP->NFD_TS1.bit)

#define DSP_NFD_ECHO2                             (DSP->NFD_ECHO2.reg)
#define DSP_NFD_ECHO2_bit                         (DSP->NFD_ECHO2.bit)

#define DSP_NFD_TS2                               (DSP->NFD_TS2.reg)
#define DSP_NFD_TS2_bit                           (DSP->NFD_TS2.bit)

#define DSP_NFD_ECHO3                             (DSP->NFD_ECHO3.reg)
#define DSP_NFD_ECHO3_bit                         (DSP->NFD_ECHO3.bit)

#define DSP_NFD_TS3                               (DSP->NFD_TS3.reg)
#define DSP_NFD_TS3_bit                           (DSP->NFD_TS3.bit)

#define DSP_NFD_ECHO4                             (DSP->NFD_ECHO4.reg)
#define DSP_NFD_ECHO4_bit                         (DSP->NFD_ECHO4.bit)

#define DSP_NFD_TS4                               (DSP->NFD_TS4.reg)
#define DSP_NFD_TS4_bit                           (DSP->NFD_TS4.bit)

#define DSP_NFD_ECHO5                             (DSP->NFD_ECHO5.reg)
#define DSP_NFD_ECHO5_bit                         (DSP->NFD_ECHO5.bit)

#define DSP_NFD_TS5                               (DSP->NFD_TS5.reg)
#define DSP_NFD_TS5_bit                           (DSP->NFD_TS5.bit)

#define DSP_ASP_CTRL                              (DSP->ASP_CTRL.reg)
#define DSP_ASP_CTRL_bit                          (DSP->ASP_CTRL.bit)

#define E_DSP_ASP_CTRL_FC_X2                      (0x0008u)
#define E_DSP_ASP_CTRL_G_ANA_DIAG                 (0x0010u)

#define DSP_ASP_ADC_CTRL                          (DSP->ASP_ADC_CTRL.reg)
#define DSP_ASP_ADC_CTRL_bit                      (DSP->ASP_ADC_CTRL.bit)

#define E_DSP_ASP_ADC_CTRL_SOC                    (0x0001u)
#define E_DSP_ASP_ADC_CTRL_EOC                    (0x0002u)
#define E_DSP_ASP_ADC_CTRL_ADC_CPU_CTRL           (0x0004u)

#define DSP_ASP_ADC_DTA                           (DSP->ASP_ADC_DTA.reg)
#define DSP_ASP_ADC_DTA_bit                       (DSP->ASP_ADC_DTA.bit)

#define DSP_IRQ_STATUS                            (DSP->IRQ_STATUS.reg)
#define DSP_IRQ_STATUS_bit                        (DSP->IRQ_STATUS.bit)

#define E_DSP_IRQ_STATUS_EEVAL_TLH_EVT            (0x0001u)
#define E_DSP_IRQ_STATUS_EEVAL_THL_EVT            (0x0002u)
#define E_DSP_IRQ_STATUS_EEVAL_MAX_EVT            (0x0004u)
#define E_DSP_IRQ_STATUS_EEVAL_MIN_EVT            (0x0008u)
#define E_DSP_IRQ_STATUS_EEVAL1_MAX_EVT           (0x0010u)
#define E_DSP_IRQ_STATUS_EEVAL2_MAX_EVT           (0x0020u)
#define E_DSP_IRQ_STATUS_RFM_EVT                  (0x0040u)
#define E_DSP_IRQ_STATUS_RTM_EVT                  (0x0080u)
#define E_DSP_IRQ_STATUS_NFD_EVT                  (0x0100u)
#define E_DSP_IRQ_STATUS_EEVAL_DMA_WRAP           (0x0200u)
#define E_DSP_IRQ_STATUS_EEVAL1_DMA_WRAP          (0x0400u)
#define E_DSP_IRQ_STATUS_EEVAL2_DMA_WRAP          (0x0800u)
#define E_DSP_IRQ_STATUS_EDI0_DMA_WRAP            (0x1000u)
#define E_DSP_IRQ_STATUS_EDI1_DMA_WRAP            (0x2000u)
#define E_DSP_IRQ_STATUS_EDI2_DMA_WRAP            (0x4000u)
#define E_DSP_IRQ_STATUS_EDI3_DMA_WRAP            (0x8000u)

#define DSP_IRQ_MASK                              (DSP->IRQ_MASK.reg)
#define DSP_IRQ_MASK_bit                          (DSP->IRQ_MASK.bit)

#define DSP_IRQ_VENABLE                           (DSP->IRQ_VENABLE.reg)
#define DSP_IRQ_VENABLE_bit                       (DSP->IRQ_VENABLE.bit)

#define DSP_IRQ_VDISABLE                          (DSP->IRQ_VDISABLE.reg)
#define DSP_IRQ_VDISABLE_bit                      (DSP->IRQ_VDISABLE.bit)

#define DSP_IRQ_VMAX                              (DSP->IRQ_VMAX.reg)
#define DSP_IRQ_VMAX_bit                          (DSP->IRQ_VMAX.bit)

#define DSP_IRQ_VNO                               (DSP->IRQ_VNO.reg)
#define DSP_IRQ_VNO_bit                           (DSP->IRQ_VNO.bit)

// module SYSTEM_CTRL instance SYSTEM_CTRL

#define SYSTEM_CTRL_POWER                         (SYSTEM_CTRL->POWER.reg)
#define SYSTEM_CTRL_POWER_bit                     (SYSTEM_CTRL->POWER.bit)

#define E_SYSTEM_CTRL_POWER_STANDBY               (0x0001u)

#define SYSTEM_CTRL_BIST                          (SYSTEM_CTRL->BIST.reg)
#define SYSTEM_CTRL_BIST_bit                      (SYSTEM_CTRL->BIST.bit)

#define E_SYSTEM_CTRL_BIST_TDR_ASP_BIST           (0x0001u)
#define E_SYSTEM_CTRL_BIST_DSP_BIST               (0x0002u)

#define SYSTEM_CTRL_TRIM                          (SYSTEM_CTRL->TRIM.reg)
#define SYSTEM_CTRL_TRIM_bit                      (SYSTEM_CTRL->TRIM.bit)

#define E_SYSTEM_CTRL_TRIM_LOCK                   (0x2000u)

#define SYSTEM_CTRL_CAP_MEAS_CTRL                 (SYSTEM_CTRL->CAP_MEAS_CTRL.reg)
#define SYSTEM_CTRL_CAP_MEAS_CTRL_bit             (SYSTEM_CTRL->CAP_MEAS_CTRL.bit)

#define E_SYSTEM_CTRL_CAP_MEAS_CTRL_START_DIAG_MEAS (0x0001u)
#define E_SYSTEM_CTRL_CAP_MEAS_CTRL_SELECT_DIAG   (0x0002u)
#define E_SYSTEM_CTRL_CAP_MEAS_CTRL_DIAG_OUT_CVDDD (0x0004u)
#define E_SYSTEM_CTRL_CAP_MEAS_CTRL_DIAG_OUT_CVDDA (0x0008u)

#define SYSTEM_CTRL_CAP_MEAS_RESULT               (SYSTEM_CTRL->CAP_MEAS_RESULT.reg)
#define SYSTEM_CTRL_CAP_MEAS_RESULT_bit           (SYSTEM_CTRL->CAP_MEAS_RESULT.bit)

#define SYSTEM_CTRL_IRQ_STATUS                    (SYSTEM_CTRL->IRQ_STATUS.reg)
#define SYSTEM_CTRL_IRQ_STATUS_bit                (SYSTEM_CTRL->IRQ_STATUS.bit)

#define E_SYSTEM_CTRL_IRQ_STATUS_POR_WAKE_UP      (0x0001u)
#define E_SYSTEM_CTRL_IRQ_STATUS_DSI3_WAKE_UP     (0x0002u)
#define E_SYSTEM_CTRL_IRQ_STATUS_IRQ_ABORT_WAKE_UP (0x0004u)
#define E_SYSTEM_CTRL_IRQ_STATUS_DEBUG_WAKE_UP    (0x0008u)
#define E_SYSTEM_CTRL_IRQ_STATUS_BIST_ON          (0x0010u)
#define E_SYSTEM_CTRL_IRQ_STATUS_ENVP_PARITY_ERR_EVT (0x0020u)
#define E_SYSTEM_CTRL_IRQ_STATUS_AATG1_PARITY_ERR_EVT (0x0040u)
#define E_SYSTEM_CTRL_IRQ_STATUS_AATG2_PARITY_ERR_EVT (0x0080u)
#define E_SYSTEM_CTRL_IRQ_STATUS_CAP_MEAS_READY_EVT (0x0100u)

#define SYSTEM_CTRL_IRQ_MASK                      (SYSTEM_CTRL->IRQ_MASK.reg)
#define SYSTEM_CTRL_IRQ_MASK_bit                  (SYSTEM_CTRL->IRQ_MASK.bit)

#define SYSTEM_CTRL_IRQ_VENABLE                   (SYSTEM_CTRL->IRQ_VENABLE.reg)
#define SYSTEM_CTRL_IRQ_VENABLE_bit               (SYSTEM_CTRL->IRQ_VENABLE.bit)

#define SYSTEM_CTRL_IRQ_VDISABLE                  (SYSTEM_CTRL->IRQ_VDISABLE.reg)
#define SYSTEM_CTRL_IRQ_VDISABLE_bit              (SYSTEM_CTRL->IRQ_VDISABLE.bit)

#define SYSTEM_CTRL_IRQ_VMAX                      (SYSTEM_CTRL->IRQ_VMAX.reg)
#define SYSTEM_CTRL_IRQ_VMAX_bit                  (SYSTEM_CTRL->IRQ_VMAX.bit)

#define SYSTEM_CTRL_IRQ_VNO                       (SYSTEM_CTRL->IRQ_VNO.reg)
#define SYSTEM_CTRL_IRQ_VNO_bit                   (SYSTEM_CTRL->IRQ_VNO.bit)

// module DAC_CTRL instance DAC_CTRL

#define DAC_CTRL_CTRL                             (DAC_CTRL->CTRL.reg)
#define DAC_CTRL_CTRL_bit                         (DAC_CTRL->CTRL.bit)

#define DAC_CTRL_REG0                             (DAC_CTRL->REG0.reg)
#define DAC_CTRL_REG0_bit                         (DAC_CTRL->REG0.bit)

#define DAC_CTRL_REG1                             (DAC_CTRL->REG1.reg)
#define DAC_CTRL_REG1_bit                         (DAC_CTRL->REG1.bit)

// module ADA instance ADA

#define ADA_ADA_CFG                               (ADA->ADA_CFG.reg)
#define ADA_ADA_CFG_bit                           (ADA->ADA_CFG.bit)

#define E_ADA_CFG_EN_100K                         (0x0020u)

#define ADA_ADA_CTRL                              (ADA->ADA_CTRL.reg)
#define ADA_ADA_CTRL_bit                          (ADA->ADA_CTRL.bit)

#define E_ADA_CTRL_SOC                            (0x0001u)
#define E_ADA_CTRL_EOC                            (0x0002u)

#define ADA_ADC_DTA                               (ADA->ADC_DTA.reg)
#define ADA_ADC_DTA_bit                           (ADA->ADC_DTA.bit)

// module UART instance UART

#define UART_DATA                                 (UART->DATA.reg)
#define UART_DATA_bit                             (UART->DATA.bit)

#define UART_STAT                                 (UART->STAT.reg)
#define UART_STAT_bit                             (UART->STAT.bit)

#define E_UART_STAT_TX_FULL                       (0x0001u)
#define E_UART_STAT_RX_FULL                       (0x0002u)
#define E_UART_STAT_TX_OVR                        (0x0004u)
#define E_UART_STAT_RX_OVR                        (0x0008u)

#define UART_CTRL                                 (UART->CTRL.reg)
#define UART_CTRL_bit                             (UART->CTRL.bit)

#define E_UART_CTRL_TXEN                          (0x0001u)
#define E_UART_CTRL_RXEN                          (0x0002u)
#define E_UART_CTRL_TXIRQEN                       (0x0004u)
#define E_UART_CTRL_RXIRQEN                       (0x0008u)
#define E_UART_CTRL_TXOVRIRQEN                    (0x0010u)
#define E_UART_CTRL_RXOVRIRQEN                    (0x0020u)
#define E_UART_CTRL_HS                            (0x0040u)

#define UART_INTCLR                               (UART->INTCLR.reg)
#define UART_INTCLR_bit                           (UART->INTCLR.bit)

#define E_UART_INTCLR_TXINT                       (0x0001u)
#define E_UART_INTCLR_RXINT                       (0x0002u)
#define E_UART_INTCLR_TXOVRINT                    (0x0004u)
#define E_UART_INTCLR_RXOVRINT                    (0x0008u)

#define UART_BAUD_LOW                             (UART->BAUD_LOW.reg)
#define UART_BAUD_LOW_bit                         (UART->BAUD_LOW.bit)

#define UART_BAUD_HIGH                            (UART->BAUD_HIGH.reg)
#define UART_BAUD_HIGH_bit                        (UART->BAUD_HIGH.bit)

#define UART_IRQ_STATUS                           (UART->IRQ_STATUS.reg)
#define UART_IRQ_STATUS_bit                       (UART->IRQ_STATUS.bit)

#define E_UART_IRQ_STATUS_TXINT                   (0x0001u)
#define E_UART_IRQ_STATUS_RXINT                   (0x0002u)
#define E_UART_IRQ_STATUS_TXOVRINT                (0x0004u)
#define E_UART_IRQ_STATUS_RXOVRINT                (0x0008u)

#define UART_IRQ_MASK                             (UART->IRQ_MASK.reg)
#define UART_IRQ_MASK_bit                         (UART->IRQ_MASK.bit)

#define UART_IRQ_VENABLE                          (UART->IRQ_VENABLE.reg)
#define UART_IRQ_VENABLE_bit                      (UART->IRQ_VENABLE.bit)

#define UART_IRQ_VDISABLE                         (UART->IRQ_VDISABLE.reg)
#define UART_IRQ_VDISABLE_bit                     (UART->IRQ_VDISABLE.bit)

#define UART_IRQ_VMAX                             (UART->IRQ_VMAX.reg)
#define UART_IRQ_VMAX_bit                         (UART->IRQ_VMAX.bit)

#define UART_IRQ_VNO                              (UART->IRQ_VNO.reg)
#define UART_IRQ_VNO_bit                          (UART->IRQ_VNO.bit)

#endif

