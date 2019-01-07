
#include "femto.h"
#include "test_util.h"


void riscv_runtime(void)
{
    gpsram_write32(DLA_BASE, 0x12345678);
    gpsram_write32(DLA_BASE+4, 0xa5a5a5a5);
    gpsram_write32(DLA_BASE+8, 0x5a5a5a5a);
    gpsram_write32(DLA_BASE+12, 0xa5a5a5a5);
    mb();

    //*(volatile uint32_t*)(uintptr_t)(0xffa8900000) = 0x87654321;
    //*(volatile uint32_t*)(uintptr_t)(0xffa8900004) = 0xa5a5a5a5;
    //*(volatile uint32_t*)(uintptr_t)(0xffa8900008) = 0x5a5a5a5a;
    //*(volatile uint32_t*)(uintptr_t)(0xffa890000c) = 0xa5a5a5a5;
    //mb();
    //
    //*(volatile uint32_t*)(uintptr_t)(0x840000000) = 0x11111111;
    //*(volatile uint32_t*)(uintptr_t)(0x840000004) = 0xa5a5a5a5;
    //*(volatile uint32_t*)(uintptr_t)(0x840000008) = 0x5a5a5a5a;
    //*(volatile uint32_t*)(uintptr_t)(0x84000000c) = 0xa5a5a5a5;
    //mb();

    signal_to_simulation(0xaa);

}
