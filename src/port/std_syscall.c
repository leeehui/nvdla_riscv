#include <stdint.h>
#include <device.h>
#include <sys/stat.h>

#define HEAP_SIZE (4*1024)
static unsigned char heap[HEAP_SIZE] __attribute__((section("heap_riscv")));

/* override default write function for newlib */
int _write(int file, char *ptr, int len)
{
    int todo;
    for (todo=0; todo<len; todo++) {
        /* TODO: replace with real redirection function here */
        //*(volatile uint8_t *)(0x000050) = 0xaa;
        console_dev->putchar(*ptr++);
    }
    return len;
}

/* override default sbrk function for newlib */
void *_sbrk(intptr_t increment)
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

int _open(const char *name, int flags, int mode)
{
    return -1;
}

int _close(int file)
{
    return -1;
}

int _isatty(int file)
{
    return 1;
}

int _lseek(int file, int ptr, int dir)
{
    return 0;
}

int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}


