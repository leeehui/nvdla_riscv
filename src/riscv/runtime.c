
#include <stdio.h>
#include <stdlib.h>
#include <nvdla_riscv.h>
#include <nvdla_interface.h>

#include "femto.h"


extern uint32_t task_notifier;
int riscv_runtime(void)
{


    while(1) {


        // check if there is a new task or firmware stop request 
        wait_for_dla_irq(&task_notifier);

        // update local_task parameters 
        update_submit_task_params();

        // submit task, this will block cpu inside nvdla_submit
        nvdla_submit(get_nvdla_dev(), get_local_task());

        // notice to ap
        send_irq_to_ap();
    }
}

