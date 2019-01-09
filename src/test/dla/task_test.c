
#include "dla_engine_internal.h"
#include <nvdla_riscv.h>
#include "test_util.h"


extern uint32_t dla_task_notifier_test;
void dla_task_test(void)
{
    uint64_t t_addrl;
    uint64_t t_addrh;
    uint64_t t_addr;
    uint64_t ddr_dstl;
    uint64_t ddr_dsth;
    uint64_t ddr_dst;
    uint32_t data;

    wait_for_dla_irq(&dla_task_notifier_test);

    t_addrl = riscv_csr_read(ARIANE_CSR_TASK_POINTER_L);
    t_addrh = riscv_csr_read(ARIANE_CSR_TASK_POINTER_H);
    t_addr = (t_addrh << 32) + t_addrl;
    data = *(volatile uint32_t*)(uintptr_t)(t_addr);

    ddr_dstl = gpsram_read32(DLA_BASE);
    ddr_dsth = gpsram_read32(DLA_BASE + 4);

    ddr_dst = (ddr_dsth << 32) + ddr_dstl;

    *(volatile uint32_t*)(uintptr_t)(ddr_dst) = data;
    mb();

    debug(TASK_TEST, "t_addr: %p", t_addr);
    debug(TASK_TEST, "ddr_dst: %p", ddr_dst);
    debug(TASK_TEST, "data: 0x%x", data);

    send_end_to_simulation();
}

void riscv_runtime(void)
{
    // use handler for test
    register_irq_handler(IRQ_ID_IRQ0, irq0_handler_test);

    send_signal_to_simulation(0xaa);

    dla_task_test();
}

