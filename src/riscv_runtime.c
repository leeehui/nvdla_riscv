
#include <stdio.h>
#include <stdlib.h>
#include <nvdla_riscv.h>
#include <nvdla_interface.h>

#include "femto.h"


extern uint32_t task_notifier;
int riscv_runtime(void)
{


    while(1) {


        /* check if there is a new task or firmware stop request */

        /* update local_task parameters */

        /* submit task, this will block cpu inside nvdla_submit */
        nvdla_submit(get_nvdla_dev(), get_local_task());
    }
}

