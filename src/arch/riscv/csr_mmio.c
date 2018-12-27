
#include "femto.h"


uint32_t riscv_csr_read(uint64_t addr)
{
    return *(volatile uint32_t *)(uintptr_t)(addr);
}

void riscv_csr_write(uint64_t addr, uint32_t value)
{
    *(volatile uint32_t *)(uintptr_t)(addr) = value;
    mb();
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

