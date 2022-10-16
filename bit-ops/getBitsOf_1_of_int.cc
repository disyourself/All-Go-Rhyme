
// see as : https://www.cnblogs.com/graphics/archive/2010/06/21/1752421.html

int BitCount(unsigned int n)
{
    unsigned int c =0 ; // 计数器
    while (n >0)
    {
        if((n &1) ==1) // 当前位是1
            ++c ; // 计数器加1
        n >>=1 ; // 移位
    }
    return c ;
}

int BitCount1(unsigned int n)
{
    unsigned int c =0 ; // 计数器
    for (c =0; n; n >>=1) // 循环移位
        c += n &1 ; // 如果当前位是1，则计数器加1
    return c ;
}

int BitCount2(unsigned int n)
{
    unsigned int c =0 ;
    for (c =0; n; ++c)
    {
        n &= (n -1) ; // 清除最低位的1
    }
    return c ;
}

