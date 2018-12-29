
#include "dla_engine_internal.h"
#include <nvdla_riscv.h>
#include "test_util.h"

static void  nvdla_engine_isr_test(void);
static int32_t dla_isr_handler_test(void);
static void irq0_handler_test(void);

static uint32_t dla_irq_flag_test = 0;
static uint32_t task_notifier_test = 0;
static uint32_t saved_irq = 0;
static uint32_t chech_irq = MASK(GLB_S_INTR_STATUS_0, SDP_DONE_STATUS0) |
                            MASK(GLB_S_INTR_STATUS_0, CACC_DONE_STATUS0) |
                            MASK(GLB_S_INTR_STATUS_0, CDMA_DAT_DONE_STATUS0) |
                            MASK(GLB_S_INTR_STATUS_0, CDMA_WT_DONE_STATUS0);
void dla_conv_test(void)
{
    cdma_reg_write(S_POINTER, 0x0);
    cdma_reg_write(S_ARBITER, 0x3000f);
    cdma_reg_write(D_MISC_CFG, 0x11001100);
    cdma_reg_write(D_DATAIN_FORMAT, 0x0);
    cdma_reg_write(D_DATAIN_SIZE_0, 0x70007);
    cdma_reg_write(D_DATAIN_SIZE_1, 0x1f);
    cdma_reg_write(D_PIXEL_OFFSET, 0x0);
    cdma_reg_write(D_DAIN_RAM_TYPE, 0x1);
    cdma_reg_write(D_DAIN_ADDR_LOW_0, gpsram_read32(DLA_BASE));
    cdma_reg_write(D_DAIN_ADDR_HIGH_0, gpsram_read32(DLA_BASE + 4));
    cdma_reg_write(D_DAIN_ADDR_LOW_0, 0x0);
    cdma_reg_write(D_DAIN_ADDR_HIGH_0, 0x0);
    cdma_reg_write(D_LINE_STRIDE, 0x100);
    cdma_reg_write(D_SURF_STRIDE, 0x800);
    cdma_reg_write(D_DAIN_MAP, 0x10001);
    cdma_reg_write(D_BATCH_NUMBER, 0x0);
    cdma_reg_write(D_BATCH_STRIDE, 0x0);
    cdma_reg_write(D_ENTRY_PER_SLICE, 0x3);
    cdma_reg_write(D_FETCH_GRAIN, 0x0);
    cdma_reg_write(D_WEIGHT_FORMAT, 0x0);
    cdma_reg_write(D_WEIGHT_SIZE_0, 0xfff);
    cdma_reg_write(D_WEIGHT_SIZE_1, 0xf);
    cdma_reg_write(D_WEIGHT_RAM_TYPE, 0x1);
    cdma_reg_write(D_WEIGHT_ADDR_LOW, gpsram_read32(DLA_BASE + 8));
    cdma_reg_write(D_WEIGHT_ADDR_HIGH, gpsram_read32(DLA_BASE + 16));
    cdma_reg_write(D_WEIGHT_BYTES, 0x10000);
    cdma_reg_write(D_WGS_ADDR_LOW, 0x0);
    cdma_reg_write(D_WGS_ADDR_HIGH, 0x0);
    cdma_reg_write(D_WMB_BYTES, 0x0);
    cdma_reg_write(D_MEAN_FORMAT, 0x0);
    cdma_reg_write(D_MEAN_GLOBAL_0, 0x0);
    cdma_reg_write(D_MEAN_GLOBAL_1, 0x0);
    cdma_reg_write(D_CVT_CFG, 0x0);
    cdma_reg_write(D_CVT_OFFSET, 0x0);
    cdma_reg_write(D_CVT_SCALE, 0x0);
    cdma_reg_write(D_CONV_STRIDE, 0x0);
    cdma_reg_write(D_ZERO_PADDING, 0x0);
    cdma_reg_write(D_BANK, 0x20001);
    cdma_reg_write(D_CYA, 0x0);
    csc_reg_write(S_POINTER, 0x0);
    csc_reg_write(D_MISC_CFG, 0x11001100);
    csc_reg_write(D_DATAIN_FORMAT, 0x0);
    csc_reg_write(D_DATAIN_SIZE_EXT_0, 0x70007);
    csc_reg_write(D_DATAIN_SIZE_EXT_1, 0x1f);
    csc_reg_write(D_BATCH_NUMBER, 0x0);
    csc_reg_write(D_ENTRY_PER_SLICE, 0x3);
    csc_reg_write(D_WEIGHT_FORMAT, 0x0);
    csc_reg_write(D_WEIGHT_SIZE_EXT_0, 0x70007);
    csc_reg_write(D_WEIGHT_SIZE_EXT_1, 0xf001f);
    csc_reg_write(D_WEIGHT_BYTES, 0x10000);
    csc_reg_write(D_WMB_BYTES, 0x0);
    csc_reg_write(D_DATAOUT_SIZE_0, 0x0);
    csc_reg_write(D_DATAOUT_SIZE_1, 0xf);
    csc_reg_write(D_ATOMICS, 0x0);
    csc_reg_write(D_CONV_STRIDE_EXT, 0x0);
    csc_reg_write(D_DILATION_EXT, 0x0);
    csc_reg_write(D_ZERO_PADDING, 0x0);
    csc_reg_write(D_ZERO_PADDING_VALUE, 0x0);
    csc_reg_write(D_BANK, 0x20001);
    csc_reg_write(D_CYA, 0x0);
    cmac_a_reg_write(S_POINTER, 0x0);
    cmac_a_reg_write(D_MISC_CFG, 0x1000);
    cmac_b_reg_write(S_POINTER, 0x0);
    cmac_b_reg_write(D_MISC_CFG, 0x1000);
    cacc_reg_write(S_POINTER, 0x0);
    cacc_reg_write(D_MISC_CFG, 0x1000);
    cacc_reg_write(D_DATAOUT_SIZE_0, 0x0);
    cacc_reg_write(D_DATAOUT_SIZE_1, 0xf);
    cacc_reg_write(D_DATAOUT_ADDR, gpsram_read32(DLA_BASE + 20));
    cacc_reg_write(D_BATCH_NUMBER, 0x0);
    cacc_reg_write(D_LINE_STRIDE, 0x20);
    cacc_reg_write(D_SURF_STRIDE, 0x20);
    cacc_reg_write(D_DATAOUT_MAP, 0x10001);
    cacc_reg_write(D_CLIP_CFG, 0x0);
    cacc_reg_write(D_CYA, 0x0);
    sdp_rdma_reg_write(D_NRDMA_CFG, 0x1b);
    sdp_rdma_reg_write(D_ERDMA_CFG, 0x1b);
    sdp_rdma_reg_write(D_BRDMA_CFG, 0x1b);
    sdp_reg_write(S_POINTER, 0x0);
    sdp_reg_write(S_LUT_ACCESS_CFG, 0x0);
    sdp_reg_write(S_LUT_ACCESS_DATA, 0x0);
    sdp_reg_write(S_LUT_CFG, 0x0);
    sdp_reg_write(D_DATA_CUBE_WIDTH, 0x0);
    sdp_reg_write(D_DATA_CUBE_HEIGHT, 0x0);
    sdp_reg_write(D_DATA_CUBE_CHANNEL, 0xf);
    sdp_reg_write(D_DST_BASE_ADDR_LOW, gpsram_read32(DLA_BASE + 20));
    sdp_reg_write(D_DST_BASE_ADDR_HIGH, gpsram_read32(DLA_BASE + 24));
    sdp_reg_write(D_DST_LINE_STRIDE, 0x20);
    sdp_reg_write(D_DST_SURFACE_STRIDE, 0x20);
    sdp_reg_write(D_DP_BS_CFG, 0x1a);
    sdp_reg_write(D_DP_BS_ALU_CFG, 0x2);
    sdp_reg_write(D_DP_BS_ALU_SRC_VALUE, 0x0);
    sdp_reg_write(D_DP_BS_MUL_CFG, 0x0);
    sdp_reg_write(D_DP_BS_MUL_SRC_VALUE, 0x1);
    sdp_reg_write(D_FEATURE_MODE_CFG, 0x1);
    sdp_reg_write(D_DP_BN_CFG, 0x1);
    sdp_reg_write(D_DP_EW_CFG, 0x1);
    sdp_reg_write(D_DST_DMA_CFG, 0x1);
    sdp_reg_write(D_DST_BATCH_STRIDE, 0x0);
    sdp_reg_write(D_DATA_FORMAT, 0x5);
    sdp_reg_write(D_CVT_OFFSET, 0x0);
    sdp_reg_write(D_CVT_SCALE, 0x1);
    sdp_reg_write(D_CVT_SHIFT, 0x0);

    while(cdma_reg_read(S_CBUF_FLUSH_STATUS) != 1);
    
    cacc_reg_write(D_OP_ENABLE, 0x1);
    cmac_a_reg_write(D_OP_ENABLE, 0x1);
    cmac_b_reg_write(D_OP_ENABLE, 0x1);
    csc_reg_write(D_OP_ENABLE, 0x1);
    cdma_reg_write(D_OP_ENABLE, 0x1);
    sdp_reg_write(D_OP_ENABLE, 0x1);
    sdp_rdma_reg_write(D_OP_ENABLE, 0x0);

    wait_for_dla_irq(&dla_irq_flag_test);

    signal_to_simulation(0xaa);
}

void riscv_runtime(void)
{
    // use handler for test
    register_irq_handler(IRQ_ID_IRQ0, irq0_handler_test);

    dla_conv_test();
}

static void irq0_handler_test(void)
{
    debug(IRQ0, "irq0_handler.");
    if (riscv_csr_read(ARIANE_CSR_DLA_TASK_CONF))
    {
        debug(IRQ0, "new task.");
        notify_dla_irq(&task_notifier_test);
        riscv_csr_write(ARIANE_CSR_DLA_TASK_CONF, 0);
    }
    else
    {
        debug(IRQ0, "dla intr.");
        nvdla_engine_isr_test();
    }
}

static void  nvdla_engine_isr_test(void)
{
	dla_isr_handler_test();
    if (saved_irq == chech_irq)
    {
        notify_dla_irq(&dla_irq_flag_test);
    }

    return;
}

static int32_t dla_isr_handler_test(void)
{
	uint32_t mask;
	uint32_t reg;


	mask = glb_reg_read(S_INTR_MASK);
	reg = glb_reg_read(S_INTR_STATUS);

    saved_irq |= reg;
    debug(IRQ0, "saved_irq: 0x%08x, reg: 0x%08x", saved_irq, reg);

	glb_reg_write(S_INTR_STATUS, reg);

	mask = glb_reg_read(S_INTR_MASK);
	reg = glb_reg_read(S_INTR_STATUS);

	RETURN(0);
}
