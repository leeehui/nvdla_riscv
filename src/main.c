
#include <stdio.h>
#include <stdlib.h>
#include <nvdla_riscv.h>
#include <nvdla_interface.h>

#include "femto.h"

extern void riscv_runtime(void);

int main(void)
{
    arch_setup();
    debug(MAIN, "hello, riscv!");

    nvdla_init(get_nvdla_dev());

    enable_irq_global(MIE);
    enable_irq(IRQ_ID_IPI);
    enable_irq(IRQ_ID_IRQ0);
    enable_irq(IRQ_ID_IRQ1);
    enable_irq(IRQ_ID_TIME);
    disable_dla_irq_to_ap();

    riscv_runtime();

    return 0;
}
