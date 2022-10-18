#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <utility>


using namespace std;


void show0()
{
    cout << "你好" << endl;
}

void show1(const string &msg)
{
    cout << "亲爱的," << msg << endl;
}

struct CC
{
    void show2(int id, const string &msg)
    {
        cout << "亲爱的" << id << "号," << msg << endl;
    }
};


int test01()
{
    thread t1(show0);
    thread t2(show1, "我是 show1");
    CC     cc;
    thread t3(&CC::show2, &cc, 3, "我是 CC::show2");

    t1.join();
    t2.join();
    t3.join();

    cout << "-----------------------------" << endl;
    return 0;
}


template <typename Fn, typename... Args>
// auto show(Fn fn, Args... args)
// auto show(Fn fn, Args... args) -> decltype(bind(fn, args...)) // C++11
//
// 传递右值与左值属性
auto show(Fn &&fn, Args &&...args)
// auto show(Fn fn, Args... args) -> decltype(bind(std::forward<Fn>(fn), forward<Args>(args)...)) // C++11
{
    cout << "准备工作...." << endl;
    // auto f = bind(fn, args...);
    // 转发左值与右值
    auto f = bind(std::forward<Fn>(fn), forward<Args>(args)...);
    f();

    cout << "完成...." << endl;
    return f; // 返回 这个 函数指针
}

void test02()
{
    show(show0);                        // bind(show0);
    show(show1, "我是show(show1,msg)"); // bind(show1, "msg");

    CC   cc;
    auto f = show(&CC::show2, &cc, 3, "我是 show(&CC::show2, &cc, 3, msg)"); // bind(&CC::show2,&cc,3,msg);
    f();
}


int main()
{
    test01();
    test02();

    return 0;
}
