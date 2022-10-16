
#include <stdio.h>


void modifyPtr(int *p)
{
    p = new int;
}
void modifyPtr(int **p)
{
    *p = new int;
}

void test1()
{
    int val = 1;
    printf("addres of val: %p\n", &val);

    int *p = &val;
    printf("addres of p: %p\n", p);

	// 拷贝了一个指针，在内部更改，不对p造成影像
    modifyPtr(p);
    printf("addres of p: %p\n", p);

    modifyPtr(&p);
    printf("addres of p: %p\n", p);
}


int main()
{
    test1();

    printf("-----------------------\n");
    printf("%p\n", test1);
    return 0;
}
