#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

uint32_t riscv_csr_read(uint64_t addr);

void riscv_csr_write(uint64_t addr, uint32_t value);

#define     RISCV_BASE                      (0xFFA8000000)

/* dlass related csrs */
#define     RISCV_DLA_SS_BASE               (RISCV_BASE + 0x400000)
#define     RISCV_PERIPH_BASE               (RISCV_BASE + 0x500000)
#define     RISCV_GPSRAM_BASE               (RISCV_BASE + 0x800000)
#define     RISCV_CVSRAM_BASE               (RISCV_BASE + 0x900000)

/* timer */
#define     RISCV_TIMER_BASE                (RISCV_PERIPH_BASE + 0x0000)

/* wdt */
#define     RISCV_WDT_BASE                  (RISCV_PERIPH_BASE + 0x1000)

/* dla csrs */
#define     RISCV_CSR_BASE                  (RISCV_PERIPH_BASE + 0x2000)
#define     RISCV_CSR_BOOT_ADDR_L           (RISCV_CSR_BASE + 0x00)
#define     RISCV_CSR_BOOT_ADDR_H           (RISCV_CSR_BASE + 0x04)
#define     RISCV_CSR_ARIANE_CTRL           (RISCV_CSR_BASE + 0x08)
#define     RISCV_CSR_INTR_EX_MASK          (RISCV_CSR_BASE + 0x10)
#define     RISCV_CSR_IN2EX_RAW             (RISCV_CSR_BASE + 0x14)
#define     RISCV_CSR_IN2EX_MASK            (RISCV_CSR_BASE + 0x18)
#define     RISCV_CSR_IN2EX_STATUS          (RISCV_CSR_BASE + 0x1C)
#define     RISCV_CSR_DLA_TASK_CONF         (RISCV_CSR_BASE + 0x60)
#define     RISCV_CSR_TASK_POINTER_L        (RISCV_CSR_BASE + 0x64)
#define     RISCV_CSR_TASK_POINTER_H        (RISCV_CSR_BASE + 0x68)
#define     RISCV_CSR_FW_STATUS             (RISCV_CSR_BASE + 0x70)
#define     RISCV_CSR_FW_STATUS_EXT         (RISCV_CSR_BASE + 0x74)
#define     RISCV_CSR_FW_ERROR_CODE         (RISCV_CSR_BASE + 0x78)
#define     RISCV_CSR_FW_ERROR_CODE_EXT     (RISCV_CSR_BASE + 0x7C)
#define     RISCV_CSR_INTR_IN_TRIG          (RISCV_CSR_BASE + 0x80)

#ifdef __cplusplus
}
#endif
