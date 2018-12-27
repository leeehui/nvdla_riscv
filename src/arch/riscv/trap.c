// See LICENSE for license details.

#include "femto.h"
#include "arch/riscv/trap.h"
#include "arch/riscv/encoding.h"
#include "arch/riscv/machine.h"
#include "arch/riscv/csr.h"
#include "arch/riscv/csr_mmio.h"

#define TRAP 1

static trap_fn tfn = 0;
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
    "store_page_fault"
};

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


void disable_irq(uint64_t mask)
{
    uint64_t mie = read_csr_enum(csr_mie);
    mie = mie & (~mask);
    write_csr_enum(csr_mie, mie);  
}

void enable_irq(uint64_t mask)
{
    uint64_t mie = read_csr_enum(csr_mie);
    mie = mie | (mask);
    write_csr_enum(csr_mie, mie);  
}

static void clear_irq_pend(uint64_t mask)
{
    uint64_t mip = read_csr_enum(csr_mip);
    mip = mip & (~mask);
    write_csr_enum(csr_mip, mip);  
}

void disable_irq0(void)
{
    disable_irq(IRQ0_MASK);
}

void enable_irq0(void)
{
    enable_irq(IRQ0_MASK);
}

void trap_handler(int64_t mcause, uint64_t mip)
{
    // interrupt
    if (mcause < 0)
    {
        if (mip & IRQ0_MASK)
        {
            irq0_handler();
        }
        else if (mip & IRQ1_MASK)
        {
            irq1_handler();
        }
        else if (mip & IPI_MASK)
        {
            ipi_handler();
        }
        else if (mip & TIME_MASK)
        {
            timer_handler();
        }
    }
    // synchronous exception
    else
    {
        debug(TRAP, "synchronous exception.");
    }
}

extern uint32_t task_notifier;
static void irq0_handler(void)
{
    debug(TRAP, "irq0_handler.");
    if (riscv_csr_read(ARIANE_CSR_DLA_TASK_CONF))
    {
        debug(TRAP, "new task.");
        notify_dla_irq(&task_notifier);
        riscv_csr_write(ARIANE_CSR_DLA_TASK_CONF, 0);
    }
    else
    {
        debug(TRAP, "dla intr.");
        nvdla_engine_isr(0, get_nvdla_dev());
    }
    //clear_irq_pend(IRQ0_MASK);
}

static void irq1_handler(void)
{
    //clear_irq_pend(IRQ1_MASK);
    debug(TRAP, "irq1_handler.");
}

static void timer_handler(void)
{
    //clear_irq_pend(TIME_MASK);
    debug(TRAP, "timer_handler.");
}

static void ipi_handler(void)
{
    //clear_irq_pend(IPI_MASK);
    debug(TRAP, "ipi_handler.");
}
