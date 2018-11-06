// See LICENSE for license details.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* SUPERVISOR MODE CSRS */
#define    CSR_SSTATUS             0x100
#define    CSR_SIE                 0x104
#define    CSR_STVEC               0x105
#define    CSR_SCOUNTEREN          0x106
#define    CSR_SSCRATCH            0x140
#define    CSR_SEPC                0x141
#define    CSR_SCAUSE              0x142
#define    CSR_STVAL               0x143
#define    CSR_SIP                 0x144
#define    CSR_SATP                0x180
                                         
/* MACHINE MODE CSRS */                  
#define    CSR_MSTATUS             0x300
#define    CSR_MISA                0x301
#define    CSR_MEDELEG             0x302
#define    CSR_MIDELEG             0x303
#define    CSR_MIE                 0x304
#define    CSR_MTVEC               0x305
#define    CSR_MCOUNTEREN          0x306
#define    CSR_MSCRATCH            0x340
#define    CSR_MEPC                0x341
#define    CSR_MCAUSE              0x342
#define    CSR_MTVAL               0x343
#define    CSR_MIP                 0x344
#define    CSR_PMPCFG0             0x3A0
#define    CSR_PMPADDR0            0x3B0
#define    CSR_MVENDORID           0xF11
#define    CSR_MARCHID             0xF12
#define    CSR_MIMPID              0xF13
#define    CSR_MHARTID             0xF14
#define    CSR_MCYCLE              0xB00
#define    CSR_MINSTRET            0xB02
#define    CSR_DCACHE              0x701
#define    CSR_ICACHE              0x700
                                         
/* COUNTERS AND TIMERS CSRS */           
#define    CSR_CYCLE               0xC00
#define    CSR_TIME                0xC01
#define    CSR_INSTRET             0xC02
                                         
/* PERFORMANCE COUNTERS CSRS */          
#define    CSR_L1_ICACHE_MISS      0xC03
#define    CSR_L1_DCACHE_MISS      0xC04
#define    CSR_ITLB_MISS           0xC05
#define    CSR_DTLB_MISS           0xC06
#define    CSR_LOAD                0xC07
#define    CSR_STORE               0xC08
#define    CSR_EXCEPTION           0xC09
#define    CSR_EXCEPTION_RET       0xC0A
#define    CSR_BRANCH_JUMP         0xC0B
#define    CSR_CALL                0xC0C
#define    CSR_RET                 0xC0D
#define    CSR_MIS_PREDICT         0xC0E

int* csr_enum_array();
const char** csr_name_array();
long read_csr_enum(int csrenum);
void write_csr_enum(int csrenum, long value);

enum {

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

#ifdef __cplusplus
}
#endif
