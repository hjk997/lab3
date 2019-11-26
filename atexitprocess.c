#include <stdio.h>
#include <stdlib.h>

void exitfunc1(void);
void exitfunc2(void);

void main()
{
    atexit(exitfunc1);
    atexit(exitfunc2);
    printf("This is main function.");
}

void exitfunc1(void)
{
    printf("This is exit 1.");
}

void exitfunc2(void)
{
    printf("This is exit 2.");
}
