
#include "femto.h"
#include "test_util.h"


extern uint32_t task_notifier;
void riscv_runtime(void)
{

    wait_for_dla_irq(&task_notifier);

    signal_to_simulation(0xaa);

}
