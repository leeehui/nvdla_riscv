// See LICENSE for license details.

#include "femto.h"
#include "arch/riscv/trap.h"
#include "arch/riscv/encoding.h"
#include "arch/riscv/machine.h"
#include "arch/riscv/csr.h"
#include "arch/riscv/csr_mmio.h"


static trap_fn tfn = 0;

static irq_handler_t trap_handlers[IRQ_NUM] = {0};
static uint32_t irq_masks[IRQ_NUM] = {
    IRQ_MASK_IRQ0,
    IRQ_MASK_IRQ1,
    IRQ_MASK_IPI,
    IRQ_MASK_TIME
};


static void irq0_handler(void);
static void irq1_handler(void);
static void timer_handler(void);
static void ipi_handler(void);

extern void* get_nvdla_dev(void);
extern void  nvdla_engine_isr(int32_t irq, void *data);

const char * riscv_excp_names[16] = {
    "misaligned_fetch",
    "fault_fetch",
    "illegal_instruction",
    "breakpoint",
    "misaligned_load",
    "fault_load",
    "misaligned_store",
    "fault_store",
    "user_ecall",
    "supervisor_ecall",
    "hypervisor_ecall",
    "machine_ecall",
    "exec_page_fault",
    "load_page_fault",
    "reserved",
    "store_page_fault" }; 
const char * riscv_intr_names[16] = {
    "u_software",
    "s_software",
    "h_software",
    "m_software",
    "u_timer",
    "s_timer",
    "h_timer",
    "m_timer",
    "u_external",
    "s_external",
    "h_external",
    "m_external",
    "reserved",
    "reserved",
    "reserved",
    "reserved"
};

trap_fn get_trap_fn()
{
    return tfn;
}

void set_trap_fn(trap_fn fn)
{
    tfn = fn;
}

irq_handler_t get_irq_handler(uint32_t id)
{
    if (id < IRQ_NUM)
    {
        return trap_handlers[id];
    }
    else
    {
        return (irq_handler_t)(0);
    }
}

void register_irq_handler(uint32_t id, irq_handler_t fn)
{
    if (id < IRQ_NUM)
    {
        trap_handlers[id] = fn;
    }
}

void disable_irq_global(uint64_t mask)
{
    uint64_t mstatus = read_csr_enum(csr_mstatus);
    mstatus = mstatus & (~mask);
    write_csr_enum(csr_mstatus, mstatus);  
}

void enable_irq_global(uint64_t mask)
{
    uint64_t mstatus = read_csr_enum(csr_mstatus);
    mstatus = mstatus | (mask);
    write_csr_enum(csr_mstatus, mstatus);  
}


void disable_irq(uint32_t id)
{
    if (id < IRQ_NUM)
    {
        uint64_t mie = read_csr_enum(csr_mie);
        mie = mie & (~irq_masks[id]);
        write_csr_enum(csr_mie, mie);  
    }
}

void enable_irq(uint32_t id)
{
    if (id < IRQ_NUM)
    {
        uint64_t mie = read_csr_enum(csr_mie);
        mie = mie | (irq_masks[id]);
        write_csr_enum(csr_mie, mie);  
    }
}

void disable_irq0(void)
{
    disable_irq(IRQ_ID_IRQ0);
}

void enable_irq0(void)
{
    enable_irq(IRQ_ID_IRQ0);
}

void trap_handler(int64_t mcause, uint64_t mip)
{
    irq_id_t id = IRQ_NUM;
    irq_handler_t irq;

    // interrupt
    if (mcause < 0)
    {
        if (mip & IRQ_MASK_IRQ0)
        {
            id = IRQ_ID_IRQ0;
        }
        else if (mip & IRQ_MASK_IRQ1)
        {
            id = IRQ_ID_IRQ1;
        }
        else if (mip & IRQ_MASK_IPI)
        {
            id = IRQ_ID_IPI;
        }
        else if (mip & IRQ_MASK_TIME)
        {
            id = IRQ_ID_TIME;
        }

        if (irq = get_irq_handler(id))
            irq();
    }
    // synchronous exception
    else
    {
        debug(TRAP, "synchronous exception.");
    }

}

