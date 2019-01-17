
#include "femto.h"
#include "test_util.h"


void riscv_runtime(void)
{
    uint32_t data1, data2, data3, data4;
    uint64_t cvsram_addrl = 0;
    uint64_t cvsram_addrh = 0;
    uint64_t cvsram_addr = 0;
    cvsram_addrl = gpsram_read32(DLA_BASE);
    cvsram_addrh = gpsram_read32(DLA_BASE+4);
    cvsram_addr = (cvsram_addrh << 32) + cvsram_addrl;
    debug(MEM_TEST, "cvsram_addr: %p", cvsram_addr); 

    *(volatile uint32_t*)(uintptr_t)(cvsram_addr) = 0x11111111;
    *(volatile uint32_t*)(uintptr_t)(cvsram_addr+4) = 0x22222222;
    *(volatile uint32_t*)(uintptr_t)(cvsram_addr+8) = 0x33333333;
    *(volatile uint32_t*)(uintptr_t)(cvsram_addr+12) = 0x44444444;
    mb();

    send_end_to_simulation();

}

