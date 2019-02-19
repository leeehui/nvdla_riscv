
#include "femto.h"
#include "test_util.h"
#include "time.h"
#include "stdlib.h"


void riscv_runtime(void)
{
    
    srand(time(NULL));
    int a = rand();
    int b = rand();

    *(volatile uint64_t*)(uintptr_t)(DLA_BASE) = a;
    *(volatile uint64_t*)(uintptr_t)(DLA_BASE+8) = b;

    uint32_t j = 0;
    for (uint32_t i = 0; i < RISCV_CVSRAM_SIZE; i = i + 8) {
        *(volatile uint64_t*)(uintptr_t)(RISCV_CVSRAM_BASE + i) = a + b * j++;
    }
    mb();

    send_end_to_simulation();

}

