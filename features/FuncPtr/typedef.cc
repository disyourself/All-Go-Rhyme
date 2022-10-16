#include <stdio.h>
typedef int INT;


void test1()
{
    int a  = 1;
    INT aa = 1;

    typedef int ARRAY[3];
    ARRAY       ary;
    int         aaa[3];

    printf("size of ARRAY: %d\n", sizeof(ARRAY));
    printf("size of aaa[3]: %d\n", sizeof(aaa));
}

int max(int a, int b) { return a > b ? a : b; }

void test2()
{
    typedef int (*i_ii)(int, int);
    i_ii pMax = max;
    pMax(1, 2);
}

//  test 3
typedef struct Node
{
    int          data;
    struct Node *next;
} NODE, *LPNODE, ARRAY[3];
// typedef struct Node  NODE, *LPNODE, ARRAY[3];
// typdef struct Node NODE
// typdef struct Node *LPNODE
// typdef struct Node ARRAY[3];

void print(int (*pF)(int, int), int, int);
//
typedef int (*PF)(int, int);
// 定义为函数指针类型后
void print(PF pf, int a, int b)
{
    printf("%d\n", pf(a, b));
}



// test 4
using Str = const char *;
typedef void *(*CallBack)(Str, Str);

void trigger(CallBack cb, Str requset, Str response)
{
    int *ret = (int *)cb(requset, response);
    printf("return val: %d\n", *ret);
}


int main()
{
    test1();
    return 0;
}
