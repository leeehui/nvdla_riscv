
#include <stdio.h>
#include <stdlib.h>
#include <nvdla_riscv.h>
#include <nvdla_interface.h>
struct nvdla_device *nvdla_dev;

int main(void)
{
    struct nvdla_submit_task local_task;
    void *ptr;
    printf("hello\n");
    ptr = malloc(20);
    free(ptr);

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

    return 0;
}
