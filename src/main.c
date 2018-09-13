
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    void *ptr;
    printf("hello\n");
    ptr = malloc(20);
    free(ptr);

    return 0;
}
