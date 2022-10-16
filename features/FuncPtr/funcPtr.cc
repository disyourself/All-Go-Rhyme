#include <iostream>

using namespace std;

int Max(int a, int b)
{
    return a > b ? a : b;
}

int Min(int a, int b)
{
    return a < b ? a : b;
}


// void (*printData）(int (*)(int,int),int,int);
void printData(int (*pp)(int, int), int a, int b)
{
    cout << pp(a, b) << endl;
}


int test1()
{
    char str[] = "你好世界";

    int (*pMax)(int, int) = nullptr;

    pMax = Max;

    // 只有两种方式
    // 1. 直接使用
    cout << pMax(1, 2) << endl;
    // 2. 解引用
    cout << (*pMax)(2, 3) << endl;

    cout << &Max << ":" << &pMax << endl;

    return 0;
}


void test2()
{
    void (*pD)(int (*)(int, int), int, int) = printData;
    pD(Max, 1, 2);
    pD(Min, 1, 2);
}


int main()
{
    // test1();
    test2();
    return 0;
}
