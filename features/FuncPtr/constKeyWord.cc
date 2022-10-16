


void test1()
{
    int num = 1;

    // 1. const 在 * 之前是相同的
    /// const int* 和 int const* 等价
    const int *a1 = &num;
    int const *a2 = &num;



    int  val = 0;
    int *p0;
    // 2. 作用：修饰类型
    const int *p1; // 修饰int，即指针的地址可以改变，但是指向的值不能变
    p1 = p0;
    //*p1 = 124; // wrong

    int *const p2 = &val; // 修饰int* ,地址不能变，但指向的值可以变
    // p2 = p0; // wrong
    *p2 = 123;

    const int *const a3 = &val; // 修饰了 int 与 int *
    a3                  = p0;
    *a3                 = 1235;
}


int main()
{
    test1();
    return 0;
}
