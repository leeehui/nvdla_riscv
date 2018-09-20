#include <stdint.h>

#define HEAP_SIZE (4*1024)
static unsigned char heap[HEAP_SIZE] __attribute__((section("heap_riscv")));

/* override default _write function fo newlib */
int _write(int file, char *ptr, int len)
{
    int todo;
    for (todo=0; todo<len; todo++) {
        /* TODO: replace with real redirection function here */
        *(volatile uint8_t *)(0x000050) = 0xaa;
    }
    return len;
}

/* override default _write function fo newlib */
void * _sbrk(intptr_t increment)
{
    static int first=1;
    static void *curbrk; 
    void * oldbrk; 

    if(first) 
    {
        //curbrk = (void *)HEAP_TOP;
		curbrk = (void *)heap;
        first = 0;
    }
    if(increment == 0)
    {
        return (void *)curbrk;
    }

	if (((intptr_t)curbrk + increment - (intptr_t)heap) > HEAP_SIZE ) {
        return (void *)-1;
    }

    oldbrk = curbrk;
    curbrk = (void *)((intptr_t)curbrk + increment);

    return oldbrk;
}


