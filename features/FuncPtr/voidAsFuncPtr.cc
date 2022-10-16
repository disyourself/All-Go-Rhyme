#include "stdio.h"
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>


void test1()
{
    int data = (int)1.11;


    void *p = nullptr;

    int a = 0;
    p     = &a;
    printf("%d\n", *(int *)p);

    float b = 1.2345f;
    p       = &b;
    printf("%f\n", *(float *)p);
}

void vfunction()
{
    printf("I am void ret function\n");
}
int ifunction()
{
    return printf("I am int ret function\n");
}


void test2()
{
    void *p = nullptr;
    /// void print(); 函数的类型为 void (*)()
    //调用方式为
    p = (void *)vfunction;
    (*(void (*)())p)();
    ((void (*)())p)();

    p = (void *)ifunction;
    (*(int (*)())p)();
    ((void  (*)())p)();
}


int main()
{
    // test1();
    printf("size of int：%lu\n", sizeof(int));
    test2();

    return 0;
}
