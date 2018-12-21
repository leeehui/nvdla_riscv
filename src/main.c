
#include <stdio.h>
#include <stdlib.h>
#include <nvdla_riscv.h>
#include <nvdla_interface.h>

#include "femto.h"

#include "test.h"
#include "csr_mmio.h"
#include "csr.h"

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



int main(void)
{
    void *ptr;
    //arch_setup();

    //printf("hello, lihui\n");
    //ptr = malloc(20);
    //printf("ptr: %p\n", ptr);
    //free(ptr);

    test();

    *(volatile uint32_t*)(uintptr_t)(0xFFA881FFF0) = 0xaa;

    //while(1);

#if 1

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
