
#include "csr_mmio.h"
#include "csr.h"



void riscv_csr_read_write(void)
{
    riscv_csr_read(ARIANE_CSR_BOOT_ADDR_L);
    riscv_csr_write(ARIANE_CSR_BOOT_ADDR_L, 0x12345678);
    riscv_csr_read(ARIANE_CSR_BOOT_ADDR_L);
}

void ariane_csr_read_write(void)
{
    read_csr_enum(csr_mie);
    read_csr_enum(csr_mtvec);
}

