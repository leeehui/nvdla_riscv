
#include "dla_engine_internal.h"
#include <nvdla_riscv.h>
#include "test_util.h"

typedef struct {
    uint32_t reg_start;
    uint32_t reg_end;
}dla_reg_t;


dla_reg_t regs[] = 
{
    {   MCIF0_FIRST_REG, MCIF0_LAST_REG      },
    {   CVIF0_FIRST_REG, CVIF0_LAST_REG      },
    {   BDMA0_FIRST_REG, BDMA0_LAST_REG      },
    {   CDMA0_FIRST_REG, CDMA0_LAST_REG      },
    {   CSC0_FIRST_REG,  CSC0_LAST_REG       },
    {   CMAC_A0_FIRST_REG,  CMAC_A0_LAST_REG    },
    {   CMAC_B0_FIRST_REG,  CMAC_B0_LAST_REG    },
    {   CACC0_FIRST_REG,  CACC0_LAST_REG      },
    {   SDP_RDMA0_FIRST_REG,  SDP_RDMA0_LAST_REG  },
    {   SDP0_FIRST_REG,  SDP0_LAST_REG       },
    {   PDP_RDMA0_FIRST_REG,  PDP_RDMA0_LAST_REG  },
    {   PDP0_FIRST_REG,  PDP0_LAST_REG       },
    {   CDP_RDMA0_FIRST_REG,  CDP_RDMA0_LAST_REG  },
    {   CDP0_FIRST_REG,  CDP0_LAST_REG       },
    {   RBK0_FIRST_REG,  RBK0_LAST_REG      },
    {   0   }
};

void dla_reg_group_test(dla_reg_t *dla_reg)
{
    for (uint32_t reg = dla_reg->reg_start; reg <= dla_reg->reg_end; reg = reg + 4)
    {
        dla_reg_write(get_nvdla_dev(), reg, 0x5a5a5a5a);
        dla_reg_read(get_nvdla_dev(), reg);
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

    dla_reg_test(&regs[0]);

    signal_to_simulation(0xaa);
}                       
