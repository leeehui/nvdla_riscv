/*
 * Copyright (c) 2017-2018, NVIDIA CORPORATION. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated into other
 * software packages, subject to the following license:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdarg.h>

#include <nvdla_interface.h>
#include <nvdla_riscv.h>
#include "femto.h"

uint32_t dla_irq_notifier = 0;

uint32_t task_notifier = 0;
static void irq0_handler(void)
{
    //debug(IRQ0, "irq0_handler.");
    if (riscv_csr_read(ARIANE_CSR_DLA_TASK_CONF))
    {
        debug(IRQ0, "new task.");
        notify_dla_irq(&task_notifier);
        riscv_csr_write(ARIANE_CSR_DLA_TASK_CONF, 0);
    }
    else
    {
        debug(IRQ0, "dla intr.");
        nvdla_engine_isr(0, get_nvdla_dev());
    }
}


static struct nvdla_device nvdla_dev;
static struct nvdla_submit_task local_task;

void* get_nvdla_dev(void)
{
    return &nvdla_dev;
}
void* get_local_task(void)
{
    return &local_task;
}

void update_submit_task_params(void)
{
    struct nvdla_submit_task *local_task;
    uint64_t addrl = riscv_csr_read(ARIANE_CSR_TASK_POINTER_L);
    uint64_t addrh = riscv_csr_read(ARIANE_CSR_TASK_POINTER_H);
    uint64_t addr = (addrh << 32) + addrl;
    local_task = get_local_task();
    memcpy(local_task, (void *)addr, sizeof(struct nvdla_submit_task));
}

static struct nvdla_config nvdla_config_os_initial = {
	.atom_size = 32,
	.bdma_enable = true,
	.rubik_enable = true,
	.weight_compress_support = true,
};

static struct nvdla_config nvdla_config_small = {
	.atom_size = 8,
	.bdma_enable = false,
	.rubik_enable = false,
	.weight_compress_support = false,
};

void dla_debug(const char *str, ...)
{
#if (NVDLA_INFO_ON==1)
	va_list args;
	va_start(args, str);
	vprintf(str, args);
	va_end(args);
#else
#endif
}

void dla_info(const char *str, ...)
{
#if (NVDLA_INFO_ON==1)
	va_list args;
	va_start(args, str);
	vprintf(str, args);
	va_end(args);
#else
#endif
}

void dla_warn(const char *str, ...)
{
#if (NVDLA_INFO_ON==1)
	va_list args;
	va_start(args, str);
	vprintf(str, args);
	va_end(args);
#else
#endif
}

void dla_error(const char *str, ...)
{
#if (NVDLA_INFO_ON==1)
	va_list args;
	va_start(args, str);
	vprintf(str, args);
	va_end(args);
#else
#endif
}

void *dla_memset(void *src, int ch, uint64_t len)
{
	return memset(src, ch, len);
}

void *dla_memcpy(void *dest, const void *src, uint64_t len)
{
	return memcpy(dest, src, len);
}

int64_t dla_get_time_us(void)
{
    return 0;
}

// DLA has normal memory master(DMA) which could be conflict with cpu
// e.g. 
// cpu write data to normal memory
// data actually resides in cache
// cpu writel DLA regs to start  <----fence w,o should be added so that data flushed before DLA start
// DLA read data from normal memory
void dla_reg_write(void *driver_context, uint32_t addr, uint32_t reg)
{
	struct nvdla_device *nvdla_dev =
			(struct nvdla_device *)driver_context;

	if (!nvdla_dev)
		return;
    writel(reg, (nvdla_dev->base + addr));
}

uint32_t dla_reg_read(void *driver_context, uint32_t addr)
{
	struct nvdla_device *nvdla_dev =
			(struct nvdla_device *)driver_context;

	if (!nvdla_dev)
		return 0;
    return readl(nvdla_dev->base + addr);
}

void  nvdla_engine_isr(int32_t irq, void *data)
{
	unsigned long flags;
	struct nvdla_device *nvdla_dev = (struct nvdla_device *)data;

	if (!nvdla_dev)
		return;

	dla_isr_handler(nvdla_dev->engine_context);

    notify_dla_irq(&dla_irq_notifier);

    return;
}


static int32_t dla_read_dma_address(void *driver_context, void *task_data,
						int16_t index, void *dst)
{
	int32_t ret = 0;
	struct nvdla_mem_handle *handles;
	uint64_t *phys_addr = (uint64_t *)(dst);
	struct nvdla_task *task = (struct nvdla_task *)task_data;

	if (index == -1 || index > task->num_addresses)
		return -1;

    handles = task->address_list;

    /* phys_addr is actually a vaddr that smmu recognizes, legacy name from nvdla kmd */
    *phys_addr = handles[index].paddr + handles[index].offset;

	return ret;
}

static int32_t dla_read_cpu_address(void *driver_context, void *task_data,
						int16_t index, void *dst)
{
	uint64_t *temp = (uint64_t *)dst;
	struct nvdla_task *task = (struct nvdla_task *)task_data;

	if (index == -1 || index > task->num_addresses)
		return -1;

	*temp = (uint64_t)index;
	return 0;
}

int32_t dla_get_dma_address(void *driver_context, void *task_data,
					int16_t index, void *dst_ptr,
					uint32_t destination)
{
	int32_t ret = 0;

    dla_debug("dla_get_dma_address.\n");

	if (destination == DESTINATION_PROCESSOR) {
		ret = dla_read_cpu_address(driver_context, task_data,
						index, dst_ptr);
	} else if (destination == DESTINATION_DMA) {
		ret = dla_read_dma_address(driver_context, task_data,
						index, dst_ptr);
	} else {
		ret = -1;
	}

	return ret;
}

int32_t dla_data_write(void *driver_context, void *task_data,
				void *src, uint64_t dst,
				uint32_t size, uint64_t offset)
{
	int32_t ret;
	struct nvdla_mem_handle *handles;
	struct nvdla_task *task = (struct nvdla_task *)task_data;

    handles = task->address_list;


    //TODO: confirm data actually flushed, be aware if smmu exists
	memcpy((void *)(handles[dst].paddr + handles[dst].offset + offset), src, size);
    mb();

	return ret;
}

int32_t dla_data_read(void *driver_context, void *task_data,
				uint64_t src, void *dst,
				uint32_t size, uint64_t offset)
{
	int32_t ret;
	struct nvdla_mem_handle *handles;
	struct nvdla_task *task = (struct nvdla_task *)task_data;

    handles = task->address_list;

    //TODO: confirm data actually flushed, be aware if smmu exists
	memcpy(dst, (void *)(handles[src].paddr + handles[src].offset + offset), size);

	return ret;
}


static int32_t nvdla_task_submit(struct nvdla_device *nvdla_dev, struct nvdla_task *task)
{
	int32_t err = 0;
	uint32_t task_complete = 0;

	nvdla_dev->task = task;

	err = dla_execute_task(nvdla_dev->engine_context, (void *)task, nvdla_dev->config_data);
	if (err) {
		return err;
	}

	while (1) {

        //TODO: wait for interrupt, probably WFI instruction
        wait_for_dla_irq(&dla_irq_notifier);

		err = dla_process_events(nvdla_dev->engine_context, &task_complete);

		if (err || task_complete)
			break;
	}

	dla_clear_task(nvdla_dev->engine_context);

	return err;
}

static int32_t nvdla_fill_task_desc(struct nvdla_submit_task *local_task, struct nvdla_task *task)
{
	struct nvdla_mem_handle *handles;

	/* update task desc fields */
	task->num_addresses = local_task->num_addresses;

	handles = malloc(local_task->num_addresses *
				sizeof(struct nvdla_mem_handle));
	if (handles == NULL)
		return -1;

    /* local_task points to data in dram, the actual data is list of nvdla_mem_handle */
    memcpy(handles, (void *)local_task->base_address, local_task->num_addresses * sizeof(struct nvdla_mem_handle));

	task->address_list = handles;

	return 0;
}


int32_t nvdla_submit(struct nvdla_device *nvdla_dev,  struct nvdla_submit_task *local_task)
{
	int32_t err = 0;
	struct nvdla_task *task;
    

	task = malloc(sizeof(*task));
	if (task == NULL)
		return -1;

	nvdla_dev->task = task;

	task->nvdla_dev = nvdla_dev;

	/* update task desc fields */
	err = nvdla_fill_task_desc(local_task, task);
	if (err)
		goto free_task_desc;

	err = nvdla_task_submit(nvdla_dev, task);

    free(task->address_list);

free_task_desc:
	free(task);
	return err;
}

int32_t nvdla_init(struct nvdla_device *nvdla_dev)
{

    /* TODO: make this configurable */
    nvdla_dev->config_data = &nvdla_config_os_initial;

    /* initialize io base */
    nvdla_dev->base = (volatile void *)(RISCV_DLA_SS_BASE);

    /* register irq function */
    register_irq_handler(IRQ_ID_IRQ0, irq0_handler);

    dla_register_driver(&nvdla_dev->engine_context, (void *)nvdla_dev);
    dla_clear_task(nvdla_dev->engine_context);

    return 0;
}


