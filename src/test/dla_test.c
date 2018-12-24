
#include "csr_mmio.h"
#include "csr.h"
#include "femto.h"



void dla_reg_write_(uint64_t addr, uint32_t value)
{
    *(volatile uint32_t *)(uintptr_t)(addr) = value;
    mb();
}

uint32_t dla_reg_read_(uint64_t addr)
{
    return *(volatile uint32_t *)(uintptr_t)(addr);
}

void dla_reg_read_write(void)
{
    dla_reg_write_(0xffa8400000, 0x5a5a5a5a);
    dla_reg_write_(0xffa8400004, 0x5a5a5a5a);
    dla_reg_write_(0xffa8400008, 0x5a5a5a5a);
    dla_reg_write_(0xffa840000c, 0x5a5a5a5a);
    dla_reg_write_(0xffa8401000, 0x5a5a5a5a);
    dla_reg_write_(0xffa8401004, 0x5a5a5a5a);
    dla_reg_write_(0xffa8401008, 0x5a5a5a5a);
    dla_reg_write_(0xffa840100c, 0x5a5a5a5a);
    dla_reg_write_(0xffa8401014, 0x5a5a5a5a);
    dla_reg_write_(0xffa8401018, 0x5a5a5a5a);
    dla_reg_write_(0xffa840101c, 0x5a5a5a5a);
    dla_reg_write_(0xffa8402000, 0x5a5a5a5a);
    dla_reg_write_(0xffa8403000, 0x5a5a5a5a);
    dla_reg_write_(0xffa8404000, 0x5a5a5a5a);
    dla_reg_write_(0xffa8405000, 0x5a5a5a5a);
    dla_reg_write_(0xffa8406000, 0x5a5a5a5a);
    dla_reg_write_(0xffa8407000, 0x5a5a5a5a);
    dla_reg_write_(0xffa8408000, 0x5a5a5a5a);
    dla_reg_write_(0xffa8409000, 0x5a5a5a5a);
    dla_reg_write_(0xffa840a000, 0x5a5a5a5a);
    dla_reg_write_(0xffa840b000, 0x5a5a5a5a);
    dla_reg_write_(0xffa840c000, 0x5a5a5a5a);
    dla_reg_write_(0xffa840d000, 0x5a5a5a5a);
    dla_reg_write_(0xffa840e000, 0x5a5a5a5a);
    dla_reg_write_(0xffa840f000, 0x5a5a5a5a);

    dla_reg_read_(0xffa8400000);
    dla_reg_read_(0xffa8400004);
    dla_reg_read_(0xffa8400008);
    dla_reg_read_(0xffa840000c);
    dla_reg_read_(0xffa8401000);
    dla_reg_read_(0xffa8401004);
    dla_reg_read_(0xffa8401008);
    dla_reg_read_(0xffa840100c);
    dla_reg_read_(0xffa8401014);
    dla_reg_read_(0xffa8401018);
    dla_reg_read_(0xffa840101c);
    dla_reg_read_(0xffa8402000);
    dla_reg_read_(0xffa8403000);
    dla_reg_read_(0xffa8404000);
    dla_reg_read_(0xffa8405000);
    dla_reg_read_(0xffa8406000);
    dla_reg_read_(0xffa8407000);
    dla_reg_read_(0xffa8408000);
    dla_reg_read_(0xffa8409000);
    dla_reg_read_(0xffa840a000);
    dla_reg_read_(0xffa840b000);
    dla_reg_read_(0xffa840c000);
    dla_reg_read_(0xffa840d000);
    dla_reg_read_(0xffa840e000);
    dla_reg_read_(0xffa840f000);
}

