
#include "femto.h"


uint32_t riscv_csr_read(uint64_t addr)
{
    uint32_t val;

    val = readl((void *)addr);
    return val;
}

void riscv_csr_write(uint64_t addr, uint32_t value)
{
    writel(value, (void *)addr);
}

void enable_dla_irq_to_ap(void)
{
    uint32_t value = riscv_csr_read(ARIANE_CSR_IN2EX_MASK);
    value |= (DLA_HW_INTR_MASK);
    riscv_csr_write(ARIANE_CSR_IN2EX_MASK, value);
}

void disable_dla_irq_to_ap(void)
{
    uint32_t value = riscv_csr_read(ARIANE_CSR_IN2EX_MASK);
    value &= (~DLA_HW_INTR_MASK);
    riscv_csr_write(ARIANE_CSR_IN2EX_MASK, value);
}

