
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "dla_engine_internal.h"
#include "femto.h"

#define DLA_BASE 0xFFA881C000             
#define SIM_SIGNAL_ADDR 0xFFA881FFF0

uint32_t gpsram_read32(uint64_t addr);
void gpsram_write32(uint64_t addr, uint32_t value);
void send_end_to_simulation(void);
void send_signal_to_simulation(uint32_t value);
void irq0_handler_test(void);
void set_saved_irq(uint32_t *saved_irq_ptr_set);

#ifdef __cplusplus
}
#endif
