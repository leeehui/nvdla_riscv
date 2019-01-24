#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
//#include "atomic.h"

uint32_t riscv_csr_read(uint64_t addr);

void riscv_csr_write(uint64_t addr, uint32_t value);
void enable_dla_irq_to_ap(void);
void disable_dla_irq_to_ap(void);
void send_irq_to_ap(void);

#define     RISCV_BASE                      (0xFFA8000000)

/* dlass related csrs */
#define     RISCV_DLA_SS_BASE               (RISCV_BASE + 0x400000)
#define     RISCV_PERIPH_BASE               (RISCV_BASE + 0x500000)
#define     RISCV_GPSRAM_BASE               (RISCV_BASE + 0x800000)
#define     RISCV_CVSRAM_BASE               (RISCV_BASE + 0x900000)

/* timer */
#define     TIMER_CSR_BASE                  (RISCV_PERIPH_BASE + 0x0000)

/* wdt */
#define     WDT_CSR_BASE                    (RISCV_PERIPH_BASE + 0x1000)
#define     WDT_REG_LOAD                    (WDT_CSR_BASE + 0x00) 
#define     WDT_REG_VALUE                   (WDT_CSR_BASE + 0x04) 
#define     WDT_REG_CONTROL                 (WDT_CSR_BASE + 0x08) 
#define     WDT_REG_INTCLR                  (WDT_CSR_BASE + 0x0C) 

/* dla csrs */
#define     ARIANE_CSR_BASE                  (RISCV_PERIPH_BASE + 0x2000)
#define     ARIANE_CSR_BOOT_ADDR_L           (ARIANE_CSR_BASE + 0x00)
#define     ARIANE_CSR_BOOT_ADDR_H           (ARIANE_CSR_BASE + 0x04)
#define     ARIANE_CSR_ARIANE_CTRL           (ARIANE_CSR_BASE + 0x08)
#define     ARIANE_CSR_INTR_EX_MASK          (ARIANE_CSR_BASE + 0x10)
#define     ARIANE_CSR_INTR_IN2EX_RAW        (ARIANE_CSR_BASE + 0x14)
#define     ARIANE_CSR_INTR_IN2EX_MASK       (ARIANE_CSR_BASE + 0x18)
#define     ARIANE_CSR_INTR_IN2EX_STATUS     (ARIANE_CSR_BASE + 0x1C)
#define     ARIANE_CSR_DLA_TASK_CONF         (ARIANE_CSR_BASE + 0x60)
#define     ARIANE_CSR_TASK_POINTER_L        (ARIANE_CSR_BASE + 0x64)
#define     ARIANE_CSR_TASK_POINTER_H        (ARIANE_CSR_BASE + 0x68)
#define     ARIANE_CSR_FW_STATUS             (ARIANE_CSR_BASE + 0x70)
#define     ARIANE_CSR_FW_STATUS_EXT         (ARIANE_CSR_BASE + 0x74)
#define     ARIANE_CSR_FW_ERROR_CODE         (ARIANE_CSR_BASE + 0x78)
#define     ARIANE_CSR_FW_ERROR_CODE_EXT     (ARIANE_CSR_BASE + 0x7C)
#define     ARIANE_CSR_INTR_IN_TRIG          (ARIANE_CSR_BASE + 0x80)
#define     ARIANE_CSR_DLA_SS_TESTBUS_SEL    (ARIANE_CSR_BASE + 0xF0)


#define     DLA_HW_INTR_MASK                (1<<0)
#define     WDT_BITE_MASK                   (1<<1)

#define     DLA_FPGA_LOG_BUF                    0xFFA881C000
#define     DLA_FPGA_LOG_BUF_SIZE               0x4000

#define     DLA_SIM_LOG_ADDR                    0xFFA881FFFF

#ifdef __cplusplus
}
#endif
