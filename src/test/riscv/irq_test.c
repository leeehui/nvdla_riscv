
#include "femto.h"
#include "test_util.h"


static uint32_t task_notifier_test = 0;
static void irq0_handler_riscv_test(void)
{
    debug(IRQ0, "irq0_handler.");
    if (riscv_csr_read(ARIANE_CSR_DLA_TASK_CONF))
    {
        debug(IRQ0, "new task.");
        notify_dla_irq(&task_notifier_test);
        riscv_csr_write(ARIANE_CSR_DLA_TASK_CONF, 0);
    }
    else
    {
        debug(IRQ0, "dla intr.");
    }
}
void riscv_runtime(void)
{

    // use handler for test
    register_irq_handler(IRQ_ID_IRQ0, irq0_handler_riscv_test);

    wait_for_dla_irq(&task_notifier_test);

    signal_to_simulation(0xaa);

}
