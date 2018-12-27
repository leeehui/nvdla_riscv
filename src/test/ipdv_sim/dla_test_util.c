
#include "dla_test.h"


void signal_to_simulation(uint32_t value)
{
    gpsram_write32(SIM_SIGNAL_ADDR, value);
    mb();
}

void gpsram_write32(uint64_t addr, uint32_t value)
{
    *(volatile uint32_t*)(uintptr_t)(addr) = value;
}

uint32_t gpsram_read32(uint64_t addr)
{
    return *(volatile uint32_t*)(uintptr_t)(addr);
}
