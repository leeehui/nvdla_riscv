
#include "dla_test.h"
#include "dla_engine_internal.h"


#define DLA_BASE 0xFFA881C000

#define BDMA_REG_(name)               BDMA_##name##_0
#define bdma_reg_write_(reg, val)     dla_reg_write_(BDMA_REG(reg), val)

uint32_t gpsram_read32(uint64_t addr)
{
    return *(volatile uint32_t*)(uintptr_t)(addr);
}

void dla_reg_write_(uint64_t offset, uint32_t value)
{
    *(volatile uint32_t *)(uintptr_t)(RISCV_DLA_SS_BASE + offset) = value;
    mb();
}

uint32_t dla_reg_read_(uint64_t offset)
{
    return *(volatile uint32_t *)(uintptr_t)(RISCV_DLA_SS_BASE + offset);
}

extern uint32_t dla_irq_flag;
void dla_bdma_test(void)
{
    bdma_reg_write_(CFG_DST_SURF, 0x800);
    bdma_reg_write_(CFG_DST_LINE, 0x100);
    bdma_reg_write_(CFG_SRC_SURF, 0x800);
    bdma_reg_write_(CFG_SRC_LINE, 0x100);
    bdma_reg_write_(CFG_SURF_REPEAT, 0x0);
    bdma_reg_write_(CFG_LINE_REPEAT, 0x7);
    bdma_reg_write_(CFG_LINE, 0x7);
    bdma_reg_write_(CFG_CMD, 0x3);
    bdma_reg_write_(CFG_SRC_ADDR_LOW, gpsram_read32(DLA_BASE));
    bdma_reg_write_(CFG_SRC_ADDR_HIGH, gpsram_read32(DLA_BASE + 4));
    bdma_reg_write_(CFG_DST_ADDR_LOW, gpsram_read32(DLA_BASE + 8));
    bdma_reg_write_(CFG_DST_ADDR_HIGH, gpsram_read32(DLA_BASE + 12));
    bdma_reg_write_(CFG_OP, 0x1);
    bdma_reg_write_(CFG_LAUNCH0, 0x1);

    wait_for_dla_irq(&dla_irq_flag);
}

void dla_reg_read_write(void)
{
    dla_reg_write_(0x00000, 0x5a5a5a5a);
    dla_reg_write_(0x00004, 0x5a5a5a5a);
    dla_reg_write_(0x00008, 0x5a5a5a5a);
    dla_reg_write_(0x0000c, 0x5a5a5a5a);
    dla_reg_write_(0x01000, 0x5a5a5a5a);
    dla_reg_write_(0x01004, 0x5a5a5a5a);
    dla_reg_write_(0x01008, 0x5a5a5a5a);
    dla_reg_write_(0x0100c, 0x5a5a5a5a);
    dla_reg_write_(0x01014, 0x5a5a5a5a);
    dla_reg_write_(0x01018, 0x5a5a5a5a);
    dla_reg_write_(0x0101c, 0x5a5a5a5a);
    dla_reg_write_(0x02000, 0x5a5a5a5a);
    dla_reg_write_(0x03000, 0x5a5a5a5a);
    dla_reg_write_(0x04000, 0x5a5a5a5a);
    dla_reg_write_(0x05000, 0x5a5a5a5a);
    dla_reg_write_(0x06000, 0x5a5a5a5a);
    dla_reg_write_(0x07000, 0x5a5a5a5a);
    dla_reg_write_(0x08000, 0x5a5a5a5a);
    dla_reg_write_(0x09000, 0x5a5a5a5a);
    dla_reg_write_(0x0a000, 0x5a5a5a5a);
    dla_reg_write_(0x0b000, 0x5a5a5a5a);
    dla_reg_write_(0x0c000, 0x5a5a5a5a);
    dla_reg_write_(0x0d000, 0x5a5a5a5a);
    dla_reg_write_(0x0e000, 0x5a5a5a5a);
    dla_reg_write_(0x0f000, 0x5a5a5a5a);

    dla_reg_read_(0x00000);
    dla_reg_read_(0x00004);
    dla_reg_read_(0x00008);
    dla_reg_read_(0x0000c);
    dla_reg_read_(0x01000);
    dla_reg_read_(0x01004);
    dla_reg_read_(0x01008);
    dla_reg_read_(0x0100c);
    dla_reg_read_(0x01014);
    dla_reg_read_(0x01018);
    dla_reg_read_(0x0101c);
    dla_reg_read_(0x02000);
    dla_reg_read_(0x03000);
    dla_reg_read_(0x04000);
    dla_reg_read_(0x05000);
    dla_reg_read_(0x06000);
    dla_reg_read_(0x07000);
    dla_reg_read_(0x08000);
    dla_reg_read_(0x09000);
    dla_reg_read_(0x0a000);
    dla_reg_read_(0x0b000);
    dla_reg_read_(0x0c000);
    dla_reg_read_(0x0d000);
    dla_reg_read_(0x0e000);
    dla_reg_read_(0x0f000);
}

