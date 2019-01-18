
#include "dla_engine_internal.h"
#include <nvdla_riscv.h>
#include "test_util.h"


extern uint32_t dla_task_notifier_test;
void dla_task_test(void)
{
    uint64_t t_addrl;
    uint64_t t_addrh;
    uint64_t t_addr;
    uint32_t datal;
    uint32_t datah;

    wait_for_dla_irq(&dla_task_notifier_test);

    t_addrl = riscv_csr_read(ARIANE_CSR_TASK_POINTER_L);
    t_addrh = riscv_csr_read(ARIANE_CSR_TASK_POINTER_H);
    t_addr = (t_addrh << 32) + t_addrl;

    // for ddr mem rw test
    *(volatile uint32_t*)(uintptr_t)(DLA_BASE) = t_addrl;
    *(volatile uint32_t*)(uintptr_t)(DLA_BASE + 4) = t_addrh;
    *(volatile uint64_t*)(uintptr_t)(DLA_BASE + 8) = *(volatile uint64_t*)(uintptr_t)(t_addr);
    *(volatile uint64_t*)(uintptr_t)(DLA_BASE + 16) = *(volatile uint64_t*)(uintptr_t)(t_addr+8);
    debug(TASK_TEST, "t_addr: %p", t_addr);
    debug(TASK_TEST, "*t_addr: %p", *(volatile uint64_t*)(uintptr_t)(t_addr));
    debug(TASK_TEST, "*t_addr+8: %p", *(volatile uint64_t*)(uintptr_t)(t_addr+8));
    mb();

    send_end_to_simulation();
}

void riscv_runtime(void)
{
    // use handler for test
    register_irq_handler(IRQ_ID_IRQ0, irq0_handler_test);

    dla_task_test();
}

