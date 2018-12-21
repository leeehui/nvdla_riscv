// See LICENSE for license details.

#include "femto.h"
#include "arch/riscv/trap.h"
#include "arch/riscv/encoding.h"
#include "arch/riscv/machine.h"
#include "arch/riscv/csr.h"
#include "arch/riscv/csr_mmio.h"

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

void disable_interrupt(uint64_t mask)
{
    uint64_t mie = read_csr_enum(csr_mie);
    mie = mie & (~mask);
    write_csr_enum(csr_mie, mie);  
}

void enable_interrupt(uint64_t mask)
{
    uint64_t mie = read_csr_enum(csr_mie);
    mie = mie | (mask);
    write_csr_enum(csr_mie, mie);  
}

void disable_irq0(void)
{
    disable_interrupt(IRQ0_MASK);
}

void enable_irq0(void)
{
    enable_interrupt(IRQ0_MASK);
}

void trap_handler(void)
{
    int64_t mcause;
    uint64_t mip;
    mcause = (int32_t)read_csr(0x342);

    // interrupt
    if (mcause < 0)
    {
        mip = read_csr(0x344);
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

    }
}

static void irq0_handler(void)
{
    nvdla_engine_isr(0, get_nvdla_dev());
}

static void irq1_handler(void)
{
}

static void timer_handler(void)
{
}

static void ipi_handler(void)
{
}
