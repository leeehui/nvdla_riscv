
#include "test_util.h"

uint32_t dla_irq_notifier_test = 0;
static uint32_t *saved_irq_ptr = NULL;
static void  nvdla_engine_isr_test(void);
static int32_t dla_isr_handler_test(void);

void signal_to_simulation(uint32_t value)
{
    gpsram_write32(SIM_SIGNAL_ADDR, value);
    mb_always_required();
}

void gpsram_write32(uint64_t addr, uint32_t value)
{
    *(volatile uint32_t*)(uintptr_t)(addr) = value;
}

uint32_t gpsram_read32(uint64_t addr)
{
    return *(volatile uint32_t*)(uintptr_t)(addr);
}

void irq0_handler_test(void)
{
    debug(IRQ0, "irq0_handler.");
    if (riscv_csr_read(ARIANE_CSR_DLA_TASK_CONF))
    {
        debug(IRQ0, "new task.");
    }
    else
    {
        debug(IRQ0, "dla intr.");
        nvdla_engine_isr_test();
    }
}
void set_saved_irq(uint32_t *saved_irq_ptr_set)
{
    saved_irq_ptr = saved_irq_ptr_set;
}

static void  nvdla_engine_isr_test(void)
{
	dla_isr_handler_test();
    notify_dla_irq(&dla_irq_notifier_test);

    return;
}

static int32_t dla_isr_handler_test(void)
{
	uint32_t mask;
	uint32_t reg;


	mask = glb_reg_read(S_INTR_MASK);
	reg = glb_reg_read(S_INTR_STATUS);

    *saved_irq_ptr |= reg;
    debug(IRQ0, "saved_irq: 0x%08x, reg: 0x%08x", *saved_irq_ptr, reg);

	glb_reg_write(S_INTR_STATUS, reg);

	mask = glb_reg_read(S_INTR_MASK);
	reg = glb_reg_read(S_INTR_STATUS);

	RETURN(0);
}
