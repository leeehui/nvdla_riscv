
#include "arch/riscv/csr_mmio.h"


uint32_t riscv_csr_read(uint64_t addr)
{
    return *(volatile uint32_t *)(uintptr_t)(addr);
}

void riscv_csr_write(uint64_t addr, uint32_t value)
{
    *(volatile uint32_t *)(uintptr_t)(addr) = value;
}

