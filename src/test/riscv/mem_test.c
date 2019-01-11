
#include "femto.h"
#include "test_util.h"


void riscv_runtime(void)
{
    gpsram_write32(DLA_BASE, 0x12345678);
    gpsram_write32(DLA_BASE+4, 0xa5a5a5a5);
    gpsram_write32(DLA_BASE+8, 0x5a5a5a5a);
    gpsram_write32(DLA_BASE+12, 0xa5a5a5a5);
    mb();
    debug(MEM_TEST, "gpsram(%p): 0x%x, 0x%x, 0x%x, 0x%x", 
            DLA_BASE,
            gpsram_read32(DLA_BASE), 
            gpsram_read32(DLA_BASE+4), 
            gpsram_read32(DLA_BASE+8), 
            gpsram_read32(DLA_BASE+12)); 

    *(volatile uint32_t*)(uintptr_t)(0xffa8900000) = 0x87654321;
    *(volatile uint32_t*)(uintptr_t)(0xffa8900004) = 0xa5a5a5a5;
    *(volatile uint32_t*)(uintptr_t)(0xffa8900008) = 0x5a5a5a5a;
    *(volatile uint32_t*)(uintptr_t)(0xffa890000c) = 0xa5a5a5a5;
    mb();
    debug(MEM_TEST, "cvsram(%p): 0x%x, 0x%x, 0x%x, 0x%x", 
            0xffa8900000,
            *(volatile uint32_t*)(uintptr_t)(0xffa8900000),
            *(volatile uint32_t*)(uintptr_t)(0xffa8900004),
            *(volatile uint32_t*)(uintptr_t)(0xffa8900008),
            *(volatile uint32_t*)(uintptr_t)(0xffa890000c));
    
    // Note: dram rw test can NOT be done as we need sim give us proper addr, this is done in task_test

    send_end_to_simulation();

}
