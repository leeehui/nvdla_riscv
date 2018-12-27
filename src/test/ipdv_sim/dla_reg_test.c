
#include "dla_engine_internal.h"
#include "dla_test.h"


void dla_reg_test(void)
{
    dla_reg_write(0x00000, 0x5a5a5a5a);
    dla_reg_write(0x00004, 0x5a5a5a5a);
    dla_reg_write(0x00008, 0x5a5a5a5a);
    dla_reg_write(0x0000c, 0x5a5a5a5a);
    dla_reg_write(0x01000, 0x5a5a5a5a);
    dla_reg_write(0x01004, 0x5a5a5a5a);
    dla_reg_write(0x01008, 0x5a5a5a5a);
    dla_reg_write(0x0100c, 0x5a5a5a5a);
    dla_reg_write(0x01014, 0x5a5a5a5a);
    dla_reg_write(0x01018, 0x5a5a5a5a);
    dla_reg_write(0x0101c, 0x5a5a5a5a);
    dla_reg_write(0x02000, 0x5a5a5a5a);
    dla_reg_write(0x03000, 0x5a5a5a5a);
    dla_reg_write(0x04000, 0x5a5a5a5a);
    dla_reg_write(0x05000, 0x5a5a5a5a);
    dla_reg_write(0x06000, 0x5a5a5a5a);
    dla_reg_write(0x07000, 0x5a5a5a5a);
    dla_reg_write(0x08000, 0x5a5a5a5a);
    dla_reg_write(0x09000, 0x5a5a5a5a);
    dla_reg_write(0x0a000, 0x5a5a5a5a);
    dla_reg_write(0x0b000, 0x5a5a5a5a);
    dla_reg_write(0x0c000, 0x5a5a5a5a);
    dla_reg_write(0x0d000, 0x5a5a5a5a);
    dla_reg_write(0x0e000, 0x5a5a5a5a);
    dla_reg_write(0x0f000, 0x5a5a5a5a);

    dla_reg_read(0x00000);
    dla_reg_read(0x00004);
    dla_reg_read(0x00008);
    dla_reg_read(0x0000c);
    dla_reg_read(0x01000);
    dla_reg_read(0x01004);
    dla_reg_read(0x01008);
    dla_reg_read(0x0100c);
    dla_reg_read(0x01014);
    dla_reg_read(0x01018);
    dla_reg_read(0x0101c);
    dla_reg_read(0x02000);
    dla_reg_read(0x03000);
    dla_reg_read(0x04000);
    dla_reg_read(0x05000);
    dla_reg_read(0x06000);
    dla_reg_read(0x07000);
    dla_reg_read(0x08000);
    dla_reg_read(0x09000);
    dla_reg_read(0x0a000);
    dla_reg_read(0x0b000);
    dla_reg_read(0x0c000);
    dla_reg_read(0x0d000);
    dla_reg_read(0x0e000);
    dla_reg_read(0x0f000);
}

void riscv_runtime(void)
{
    dla_reg_test();
}
