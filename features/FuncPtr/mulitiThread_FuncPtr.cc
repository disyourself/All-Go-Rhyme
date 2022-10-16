#include <iostream>
#include <thread>

using namespace std;



void testThread1()
{
    cout << "test thread 1st" << endl;
}

void testThread2()
{
    cout << "test thread 2nd" << endl;
}


int main()
{
    void (*func)() = nullptr;

    func = testThread1;

    thread t1(func);
    thread t2(testThread2);


    t1.detach();
    t2.detach();


    return 0;
}
