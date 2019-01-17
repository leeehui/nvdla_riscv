
#include "femto.h"
#include "test_util.h"


void riscv_runtime(void)
{
    uint32_t data1, data2, data3, data4;
    uint32_t sigval = 0;
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

    *(volatile uint32_t*)(uintptr_t)(0xffa890000c) = 0x11111111;
    mb();
    data4 = *(volatile uint32_t*)(uintptr_t)(0xffa890000c);
    *(volatile uint32_t*)(uintptr_t)(0xffa8900008) = 0x22222222;
    mb();
    data3 = *(volatile uint32_t*)(uintptr_t)(0xffa8900008);
    *(volatile uint32_t*)(uintptr_t)(0xffa8900004) = 0x33333333;
    mb();
    data2 = *(volatile uint32_t*)(uintptr_t)(0xffa8900004);
    *(volatile uint32_t*)(uintptr_t)(0xffa8900000) = 0x44444444;
    mb();
    data1 = *(volatile uint32_t*)(uintptr_t)(0xffa8900000);
    debug(MEM_TEST, "cvsram(%p): 0x%x, 0x%x, 0x%x, 0x%x", 
            0xffa8900000, data1, data2, data3, data4);

    if (data4 == 0x11111111)
        sigval |= (1<<0);
    if (data3 == 0x22222222)
        sigval |= (1<<1);
    if (data2 == 0x33333333)
        sigval |= (1<<2);
    if (data1 == 0x44444444)
        sigval |= (1<<3);

    gpsram_write32(SIM_SIGNAL_ADDR, sigval);
    mb();

    //debug(MEM_TEST, "cvsram(%p): 0x%x, 0x%x, 0x%x, 0x%x", 
    //        0xffa8900000,
    //        *(volatile uint32_t*)(uintptr_t)(0xffa8900000),
    //        *(volatile uint32_t*)(uintptr_t)(0xffa8900004),
    //        *(volatile uint32_t*)(uintptr_t)(0xffa8900008),
    //        *(volatile uint32_t*)(uintptr_t)(0xffa890000c));
    
    // Note: dram rw test can NOT be done as we need sim give us proper addr, this is done in task_test

    // the following code can only run on fpga
    //*(volatile uint32_t*)(uintptr_t)(0x84000000c) = 0x55555555;
    //mb();
    //data4 = *(volatile uint32_t*)(uintptr_t)(0x84000000c);
    //*(volatile uint32_t*)(uintptr_t)(0x840000008) = 0x66666666;
    //mb();
    //data3 = *(volatile uint32_t*)(uintptr_t)(0x840000008);
    //*(volatile uint32_t*)(uintptr_t)(0x840000004) = 0x77777777;
    //mb();
    //data2 = *(volatile uint32_t*)(uintptr_t)(0x840000004);
    //*(volatile uint32_t*)(uintptr_t)(0x840000000) = 0x88888888;
    //mb();
    //data1 = *(volatile uint32_t*)(uintptr_t)(0x840000000);
    //debug(MEM_TEST, "cvsram(%p): 0x%x, 0x%x, 0x%x, 0x%x", 
    //        0x840000000, data1, data2, data3, data4);

    send_end_to_simulation();

}
