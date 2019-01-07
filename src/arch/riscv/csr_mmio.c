
#include "femto.h"


// single core, in-order, device of riscv subsystem do NOT need barrier
// as the devices have no need to access outer normal memory(unlike DLA)
uint32_t riscv_csr_read(uint64_t addr)
{
    uint32_t val;
    val = readl_relaxed((void *)addr);
    return val;
}

void riscv_csr_write(uint64_t addr, uint32_t value)
{
    writel_relaxed(value, (void *)addr);
}

void enable_dla_irq_to_ap(void)
{
    uint32_t value = riscv_csr_read(ARIANE_CSR_IN2EX_MASK);
    value &= (~DLA_HW_INTR_MASK);
    riscv_csr_write(ARIANE_CSR_IN2EX_MASK, value);
}

void disable_dla_irq_to_ap(void)
{
    uint32_t value = riscv_csr_read(ARIANE_CSR_IN2EX_MASK);
    value |= (DLA_HW_INTR_MASK);
    riscv_csr_write(ARIANE_CSR_IN2EX_MASK, value);
}

void send_irq_to_ap(void)
{
    riscv_csr_write(ARIANE_CSR_INTR_IN_TRIG, 0x1);
}
