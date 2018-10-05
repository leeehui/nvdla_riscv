
#include <stdio.h>
#include <stdlib.h>
#include <nvdla_riscv.h>
#include <nvdla_interface.h>

#include "femto.h"

struct nvdla_device *nvdla_dev;

void trap_handler(uintptr_t* regs, uintptr_t mcause, uintptr_t mepc)
{
    return;
}


int main(void)
{
    struct nvdla_submit_task local_task;
    void *ptr;
    arch_setup();
    //console_dev->putchar('a');
    printf("hello\n");
    ptr = malloc(20);
    printf("ptr: %p\n", ptr);
    free(ptr);

    //while(1);

#if 0
    nvdla_dev = malloc(sizeof(*nvdla_dev));
    if (nvdla_dev == NULL) {
        dla_debug("fail to allocate nvdla_device.\n");
        return -1;
    }

    nvdla_init(nvdla_dev);

    while(1) {
        /* check if there is submitted task */

        /* update local_task parameters */

        /* submit task, this will block cpu inside nvdla_submit */
        nvdla_submit(nvdla_dev, &local_task);
    }

    free(nvdla_dev);
#endif

    //exit(0);
}
