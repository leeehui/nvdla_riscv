
#include <stdio.h>
#include <stdlib.h>
#include <nvdla_riscv.h>
#include <nvdla_interface.h>

#include "femto.h"
#include "test.h"

static struct nvdla_device nvdla_dev;
static struct nvdla_submit_task local_task;

void* get_nvdla_dev(void)
{
    return &nvdla_dev;
}
void* get_local_task(void)
{
    return &local_task;
}

uint32_t task_notifier = 0;

int main(void)
{
    void *ptr;
    arch_setup();
    enable_irq_global(MIE);
    enable_irq(IPI_MASK);
    enable_irq(IRQ0_MASK);
    enable_irq(IRQ1_MASK);
    enable_irq(TIME_MASK);
    disable_dla_irq_to_ap();

    printf("hello, riscv!\n");
    ptr = malloc(20);
    printf("ptr: %p\n", ptr);
    free(ptr);

    //test();

    *(volatile uint32_t*)(uintptr_t)(0xFFA881FFF0) = 0xaa;
    mb();

    //wait_for_dla_irq(&task_notifier);

    //*(volatile uint32_t*)(uintptr_t)(0xFFA881FFF0) = 0x55;
    //mb();

    while(1);

#if 0

    nvdla_init(get_nvdla_dev());

    while(1) {

        /* KMD will write ARIANE_CSR_DLA_TASK_CONF, which will trigger ipi*/
        wfi();

        /* check if there is a new task or firmware stop request */

        /* check if there is submitted task */
        if (riscv_csr_read(ARIANE_CSR_DLA_TASK_CONF))
        {
            /* update local_task parameters */

            /* submit task, this will block cpu inside nvdla_submit */
            nvdla_submit(get_nvdla_dev(), get_local_task());

            /* clear */
            riscv_csr_write(ARIANE_CSR_DLA_TASK_CONF, 0);
        }
    }
#endif

    //exit(0);
}
