// See LICENSE for license details.

#include "femto.h"
#include "arch/riscv/csr.h"
#include "arch/riscv/encoding.h"
#include "arch/riscv/machine.h"

static int all_csr_enums[] = {
    /* supervisor mode csrs */
    csr_sstatus,
    csr_sie,
    csr_stvec,
    csr_scounteren,
    csr_sscratch,
    csr_sepc,
    csr_scause,
    csr_stval,
    csr_sip,
    csr_satp,

    /* machine mode csrs */
    csr_mstatus,
    csr_misa,
    csr_medeleg,
    csr_mideleg,
    csr_mie,
    csr_mtvec,
    csr_mcounteren,
    csr_mscratch,
    csr_mepc,
    csr_mcause,
    csr_mtval,
    csr_mip,
    csr_pmpcfg0,
    csr_pmpaddr0,
    csr_mvendorid,
    csr_marchid,
    csr_mimpid,
    csr_mhartid,
    csr_mcycle,
    csr_minstret,
    csr_dcache,
    csr_icache,

    /* counters and timers csrs */
    csr_cycle,
    csr_time,
    csr_instret,

    /* performance counters csrs */
    csr_l1_icache_miss,
    csr_l1_dcache_miss,
    csr_itlb_miss,
    csr_dtlb_miss,
    csr_load,
    csr_store,
    csr_exception,
    csr_exception_ret,
    csr_branch_jump,
    csr_call,
    csr_ret,
    csr_mis_predict
};

static const char* all_csr_names[] = {
    /* supervisor mode csrs */
    "csr_sstatus",
    "csr_sie",
    "csr_stvec",
    "csr_scounteren",
    "csr_sscratch",
    "csr_sepc",
    "csr_scause",
    "csr_stval",
    "csr_sip",
    "csr_satp",

    /* machine mode csrs */
    "csr_mstatus",
    "csr_misa",
    "csr_medeleg",
    "csr_mideleg",
    "csr_mie",
    "csr_mtvec",
    "csr_mcounteren",
    "csr_mscratch",
    "csr_mepc",
    "csr_mcause",
    "csr_mtval",
    "csr_mip",
    "csr_pmpcfg0",
    "csr_pmpaddr0",
    "csr_mvendorid",
    "csr_marchid",
    "csr_mimpid",
    "csr_mhartid",
    "csr_mcycle",
    "csr_minstret",
    "csr_dcache",
    "csr_icache",

    /* counters and timers csrs */
    "csr_cycle",
    "csr_time",
    "csr_instret",

    /* performance counters csrs */
    "csr_l1_icache_miss",
    "csr_l1_dcache_miss",
    "csr_itlb_miss",
    "csr_dtlb_miss",
    "csr_load",
    "csr_store",
    "csr_exception",
    "csr_exception_ret",
    "csr_branch_jump",
    "csr_call",
    "csr_ret",
    "csr_mis_predict"
};

int* csr_enum_array()
{
    return all_csr_enums;
}

const char** csr_name_array()
{
    return all_csr_names;
}

long read_csr_enum(int csrenum)
{
    long result = -1;
    switch (csrenum) {
    /* supervisor mode csrs */
    case csr_sstatus:		result = read_csr(0x100); break;
    case csr_sie:			result = read_csr(0x104); break;
    case csr_stvec:			result = read_csr(0x105); break;
    case csr_scounteren:	result = read_csr(0x106); break;
    case csr_sscratch:		result = read_csr(0x140); break;
    case csr_sepc:			result = read_csr(0x141); break;
    case csr_scause:		result = read_csr(0x142); break;
    case csr_stval:			result = read_csr(0x143); break;
    case csr_sip:			result = read_csr(0x144); break;
    case csr_satp:			result = read_csr(0x180); break;

    /* machine mode csrs */
    case csr_mstatus:		result = read_csr(0x300); break;
    case csr_misa:			result = read_csr(0x301); break;
    case csr_medeleg:		result = read_csr(0x302); break;
    case csr_mideleg:		result = read_csr(0x303); break;
    case csr_mie:			result = read_csr(0x304); break;
    case csr_mtvec:			result = read_csr(0x305); break;
    case csr_mcounteren:	result = read_csr(0x306); break;
    case csr_mscratch:		result = read_csr(0x340); break;
    case csr_mepc:			result = read_csr(0x341); break;
    case csr_mcause:		result = read_csr(0x342); break;
    case csr_mtval:			result = read_csr(0x343); break;
    case csr_mip:			result = read_csr(0x344); break;
    case csr_pmpcfg0:		result = read_csr(0x3A0); break;
    case csr_pmpaddr0:		result = read_csr(0x3B0); break;
    case csr_mvendorid:		result = read_csr(0xF11); break;
    case csr_marchid:		result = read_csr(0xF12); break;
    case csr_mimpid:		result = read_csr(0xF13); break;
    case csr_mhartid:		result = read_csr(0xF14); break;
    case csr_mcycle:		result = read_csr(0xB00); break;
    case csr_minstret:		result = read_csr(0xB02); break;
    case csr_dcache:		result = read_csr(0x701); break;
    case csr_icache:		result = read_csr(0x700); break;

    /* counters and timers csrs */
    case csr_cycle:			result = read_csr(0xC00); break;
    case csr_time:			result = read_csr(0xC01); break;
    case csr_instret:		result = read_csr(0xC02); break;

    /* performance counters csrs */
    case csr_l1_icache_miss:result = read_csr(0xC03); break;
    case csr_l1_dcache_miss:result = read_csr(0xC04); break;
    case csr_itlb_miss:		result = read_csr(0xC05); break;
    case csr_dtlb_miss:		result = read_csr(0xC06); break;
    case csr_load:			result = read_csr(0xC07); break;
    case csr_store:			result = read_csr(0xC08); break;
    case csr_exception:		result = read_csr(0xC09); break;
    case csr_exception_ret:	result = read_csr(0xC0A); break;
    case csr_branch_jump:	result = read_csr(0xC0B); break;
    case csr_call:			result = read_csr(0xC0C); break;
    case csr_ret:			result = read_csr(0xC0D); break;
    case csr_mis_predict:   result = read_csr(0xC0E); break;
    default: break;
    }
    return result;
}

void write_csr_enum(int csrenum, long value)
{
    switch (csrenum) {
    /* supervisor mode csrs */
    case csr_sstatus:		write_csr(0x100, value); break;
    case csr_sie:			write_csr(0x104, value); break;
    case csr_stvec:			write_csr(0x105, value); break;
    case csr_scounteren:	write_csr(0x106, value); break;
    case csr_sscratch:		write_csr(0x140, value); break;
    case csr_sepc:			write_csr(0x141, value); break;
    case csr_scause:		write_csr(0x142, value); break;
    case csr_stval:			write_csr(0x143, value); break;
    case csr_sip:			write_csr(0x144, value); break;
    case csr_satp:			write_csr(0x180, value); break;

    /* machine mode csrs */
    case csr_mstatus:		write_csr(0x300, value); break;
    case csr_misa:			write_csr(0x301, value); break;
    case csr_medeleg:		write_csr(0x302, value); break;
    case csr_mideleg:		write_csr(0x303, value); break;
    case csr_mie:			write_csr(0x304, value); break;
    case csr_mtvec:			write_csr(0x305, value); break;
    case csr_mcounteren:	write_csr(0x306, value); break;
    case csr_mscratch:		write_csr(0x340, value); break;
    case csr_mepc:			write_csr(0x341, value); break;
    case csr_mcause:		write_csr(0x342, value); break;
    case csr_mtval:			write_csr(0x343, value); break;
    case csr_mip:			write_csr(0x344, value); break;
    case csr_pmpcfg0:		write_csr(0x3A0, value); break;
    case csr_pmpaddr0:		write_csr(0x3B0, value); break;
    case csr_mvendorid:		write_csr(0xF11, value); break;
    case csr_marchid:		write_csr(0xF12, value); break;
    case csr_mimpid:		write_csr(0xF13, value); break;
    case csr_mhartid:		write_csr(0xF14, value); break;
    case csr_mcycle:		write_csr(0xB00, value); break;
    case csr_minstret:		write_csr(0xB02, value); break;
    case csr_dcache:		write_csr(0x701, value); break;
    case csr_icache:		write_csr(0x700, value); break;

    /* counters and timers csrs */
    case csr_cycle:			write_csr(0xC00, value); break;
    case csr_time:			write_csr(0xC01, value); break;
    case csr_instret:		write_csr(0xC02, value); break;

    /* performance counters csrs */
    case csr_l1_icache_miss:write_csr(0xC03, value); break;
    case csr_l1_dcache_miss:write_csr(0xC04, value); break;
    case csr_itlb_miss:		write_csr(0xC05, value); break;
    case csr_dtlb_miss:		write_csr(0xC06, value); break;
    case csr_load:			write_csr(0xC07, value); break;
    case csr_store:			write_csr(0xC08, value); break;
    case csr_exception:		write_csr(0xC09, value); break;
    case csr_exception_ret:	write_csr(0xC0A, value); break;
    case csr_branch_jump:	write_csr(0xC0B, value); break;
    case csr_call:			write_csr(0xC0C, value); break;
    case csr_ret:			write_csr(0xC0D, value); break;
    case csr_mis_predict:   write_csr(0xC0E, value); break;
    default: break;
    }
}
