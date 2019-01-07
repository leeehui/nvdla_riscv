
#include "femto.h"
#include "test_util.h"


void riscv_runtime(void)
{
    gpsram_write32(SIM_SIGNAL_ADDR, 0x5a5a5a5a);
    __asm__ __volatile__ ("fence w,w" :::"memory");
    *(volatile uint32_t*)(uintptr_t)(ARIANE_CSR_INTR_IN_TRIG) = 0x1;

    gpsram_write32(SIM_SIGNAL_ADDR+4, 0x5a5a5a5a);
    __asm__ __volatile__ ("fence w,o" :::"memory");
    *(volatile uint32_t*)(uintptr_t)(ARIANE_CSR_INTR_IN_TRIG) = 0x1;

    gpsram_write32(DLA_BASE, 0x5a5a5a5a);
    __asm__ __volatile__ ("fence w,o" :::"memory");
    *(volatile uint32_t*)(uintptr_t)(ARIANE_CSR_INTR_IN_TRIG) = 0x1;

    gpsram_write32(DLA_BASE+0x100, 0x5a5a5a5a);
    __asm__ __volatile__ ("fence w,w" :::"memory");
    *(volatile uint32_t*)(uintptr_t)(ARIANE_CSR_INTR_IN_TRIG) = 0x1;

    gpsram_write32(DLA_BASE+0x200, 0x5a5a5a5a);
    __asm__ __volatile__ ("fence w,o" :::"memory");
    *(volatile uint32_t*)(uintptr_t)(ARIANE_CSR_INTR_IN_TRIG) = 0x1;

    gpsram_write32(DLA_BASE+0x300, 0x5a5a5a5a);
    __asm__ __volatile__ ("fence w,w" :::"memory");
    *(volatile uint32_t*)(uintptr_t)(ARIANE_CSR_INTR_IN_TRIG) = 0x1;

    gpsram_write32(DLA_BASE+0x400, 0x5a5a5a5a);
    __asm__ __volatile__ ("fence w,o" :::"memory");
    *(volatile uint32_t*)(uintptr_t)(ARIANE_CSR_INTR_IN_TRIG) = 0x1;

    gpsram_write32(DLA_BASE+0x500, 0x5a5a5a5a);
    __asm__ __volatile__ ("fence w,w" :::"memory");
    *(volatile uint32_t*)(uintptr_t)(ARIANE_CSR_INTR_IN_TRIG) = 0x1;

    signal_to_simulation(0xaa);

}
