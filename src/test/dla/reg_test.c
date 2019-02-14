
#include "dla_engine_internal.h"
#include <nvdla_riscv.h>
#include "test_util.h"

typedef struct {
    uint32_t reg_start;
    uint32_t reg_end;
}dla_reg_t;


dla_reg_t regs[] = 
{
    {   MCIF0_FIRST_REG,        MCIF0_LAST_REG      },
    {   CVIF0_FIRST_REG,        CVIF0_LAST_REG      },
    {   BDMA0_FIRST_REG,        BDMA0_LAST_REG      },
    {   CDMA0_FIRST_REG,        CDMA0_LAST_REG      },
    {   CSC0_FIRST_REG,         CSC0_LAST_REG       },
    {   CMAC_A0_FIRST_REG,      CMAC_A0_LAST_REG    },
    {   CMAC_B0_FIRST_REG,      CMAC_B0_LAST_REG    },
    {   CACC0_FIRST_REG,        CACC0_LAST_REG      },
    {   SDP_RDMA0_FIRST_REG,    SDP_RDMA0_LAST_REG  },
    {   SDP0_FIRST_REG,         SDP0_LAST_REG       },
    {   PDP_RDMA0_FIRST_REG,    PDP_RDMA0_LAST_REG  },
    {   PDP0_FIRST_REG,         PDP0_LAST_REG       },
    {   CDP_RDMA0_FIRST_REG,    CDP_RDMA0_LAST_REG  },
    {   CDP0_FIRST_REG,         CDP0_LAST_REG       },
    {   RBK0_FIRST_REG,         RBK0_LAST_REG       },
    {   0   }
};

void check_value(uint32_t reg, uint32_t read_val, uint32_t check_val)
{
    if (read_val != check_val)
    {
        debug(DLA_REG_TEST, "0x%05x check failed. read_val: 0x%08x, check_val: 0x%08x", reg, read_val, check_val);
    }
    else
    {
        debug(DLA_REG_TEST, "0x%05x check pass.");
    }
}
void dla_reg_rw_check_test(void)
{
    uint32_t val;
    uint32_t addr_value = 0xa5a5a5a5;
    uint32_t bit_value = 1;

    glb_reg_write(S_INTR_MASK, bit_value);
    val = glb_reg_read(S_INTR_MASK);
    check_value(GLB_REG(S_INTR_MASK), val, bit_value);

    bdma_reg_write(CFG_SRC_ADDR_LOW, addr_value);
    val = bdma_reg_read(CFG_SRC_ADDR_LOW);
    check_value(BDMA_REG(CFG_SRC_ADDR_LOW), val, addr_value);

    cdma_reg_write(D_DAIN_ADDR_LOW_0, addr_value);
    val = cdma_reg_read(D_DAIN_ADDR_LOW_0);
    check_value(CDMA_REG(D_DAIN_ADDR_LOW_0), val, addr_value);

    //csc_reg_write(reg, val)     
    //csc_reg_read(reg)           

    cmac_a_reg_write(S_POINTER, bit_value);
    val = cmac_a_reg_read(S_POINTER);        
    check_value(CMAC_A_REG(S_POINTER), val, bit_value);

    cmac_b_reg_write(S_POINTER, bit_value);
    val = cmac_b_reg_read(S_POINTER);        
    check_value(CMAC_B_REG(S_POINTER), val, bit_value);

    cacc_reg_write(D_DATAOUT_ADDR, addr_value);
    val = cacc_reg_read(D_DATAOUT_ADDR);          
    check_value(CACC_REG(D_DATAOUT_ADDR), val, addr_value);

    sdp_rdma_reg_write(D_SRC_BASE_ADDR_LOW, addr_value);
    val = sdp_rdma_reg_read(D_SRC_BASE_ADDR_LOW);          
    check_value(SDP_RDMA_REG(D_SRC_BASE_ADDR_LOW), val, addr_value);

    sdp_reg_write(D_DST_BASE_ADDR_LOW, addr_value);
    val = sdp_reg_read(D_DST_BASE_ADDR_LOW);          
    check_value(SDP_REG(D_DST_BASE_ADDR_LOW), val, addr_value);

    pdp_rdma_reg_write(D_SRC_BASE_ADDR_LOW, addr_value);
    val = pdp_rdma_reg_read(D_SRC_BASE_ADDR_LOW);          
    check_value(PDP_RDMA_REG(D_SRC_BASE_ADDR_LOW), val, addr_value);

    pdp_reg_write(D_DST_BASE_ADDR_LOW, addr_value);
    val = pdp_reg_read(D_DST_BASE_ADDR_LOW);          
    check_value(PDP_REG(D_DST_BASE_ADDR_LOW), val, addr_value);

    cdp_rdma_reg_write(D_SRC_BASE_ADDR_LOW, addr_value);
    val = cdp_rdma_reg_read(D_SRC_BASE_ADDR_LOW);          
    check_value(CDP_RDMA_REG(D_SRC_BASE_ADDR_LOW), val, addr_value);

    cdp_reg_write(D_DST_BASE_ADDR_LOW, addr_value);
    val = cdp_reg_read(D_DST_BASE_ADDR_LOW);          
    check_value(CDP_REG(D_DST_BASE_ADDR_LOW), val, addr_value);

    rubik_reg_write(D_DAIN_ADDR_LOW, addr_value);
    val = rubik_reg_read(D_DAIN_ADDR_LOW);          
    check_value(RBK_REG(D_DAIN_ADDR_LOW), val, addr_value);
}

void dla_reg_group_test(dla_reg_t *dla_reg)
{
    for (uint32_t reg = dla_reg->reg_start; reg <= dla_reg->reg_end; reg = reg + 4)
    {
        uint32_t value;
        uint32_t write_value_1 = 0x5a5a5a5a;
        uint32_t write_value_2 = 0x0;
        dla_reg_write(get_nvdla_dev(), reg, write_value_1);
        value = dla_reg_read(get_nvdla_dev(), reg);
        //debug(DLA_REG_TEST, "0x%05x : 0x%08x(write_val:0x%08x)", reg, value, write_value_1);
        //dla_reg_write(get_nvdla_dev(), reg, write_value_2);
        //value = dla_reg_read(get_nvdla_dev(), reg);
        //debug(DLA_REG_TEST, "0x%05x : 0x%08x(write_val:0x%08x)", reg, value, write_value_2);
    }
}

void dla_reg_test(dla_reg_t *dla_regs)
{
    while(dla_regs && dla_regs->reg_start != 0)
    {
        dla_reg_group_test(dla_regs);
        dla_regs++;
    }
}

void riscv_runtime(void)
{

    // as we just want to read write regs of dla, 
    // so disable all interrupts in case dla interrupt occurs unexpectedly
    disable_irq_global(MIE);

    //dla_reg_test(&regs[0]);

    dla_reg_rw_check_test();

    send_end_to_simulation();
}   
