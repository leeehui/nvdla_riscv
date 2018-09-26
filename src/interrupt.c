#include <nvdla_riscv.h>

extern struct nvdla_device *nvdla_dev;

void ISR_WDT (void)
{
	/*
	1, clear int
	2, record wdt status
	*/

	//IEU_INT_CLEAR_PENDING |= INT_WDT_EN;
    //do some thing
}

void ISR_TIMER (void)
{
	/*
	1, clear int
	2, record wdt status
	*/

	//IEU_INT_CLEAR_PENDING |= INT_WDT_EN;
    //do some thing
}

void ISR_NVDLA (void)
{
	/*
	1, clear int
	2, record wdt status
	*/
    nvdla_engine_isr(0, (void *)nvdla_dev);
	//IEU_INT_CLEAR_PENDING |= INT_WDT_EN;
    //do some thing
}
