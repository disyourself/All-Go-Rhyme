#include <chrono>
#include <condition_variable>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <thread>
#include <type_traits>
#include <utility>


using std::cout, std::endl;

// 普通 处理 业务函数
void handle(const std::string &msg)
{
    cout << "处理数据：" << msg << endl;
}

// 处理业务的类
struct Handle
{
    void handle(const std::string &msg)
    {
        cout << "处理数据：" << msg << endl;
    }
};



class __Factory
{
  private:
    std::mutex              m_mutex;
    std::condition_variable m_cond;

    // 采用 deque 做底层容器
    std::queue<std::string, std::deque<std::string>> m_q;

    // 框架处理函数 要求 void fn(const string&);
    std::function<void(const std::string &)> m_callback;

  public:


    template <typename Fn, typename... Args>
    void callback(Fn &&fn, Args &&...args)
    {
        m_callback = std::bind(std::forward<Fn>(fn),
                               std::forward<Args>(args)...,
                               std::placeholders::_1);
    }


    // 消费者线程
    void consumer()
    {
        while (true)
        {
            // RAII
            std::unique_lock<std::mutex> lock(m_mutex);

            // 没有信号时
            // 解锁后阻塞，等待被唤醒，在加锁
            m_cond.wait(lock, [this] { return !m_q.empty(); });

            // dequeue
            auto msg = m_q.front();
            m_q.pop();

            std::cout << "线程：" << std::this_thread::get_id() << " --> " << msg << std::endl;


            // 消费掉数据
            // 在实际工程中， 框架固定， 不能轻易修改代码
            // 于是使用回调函数处理 队列中的数据 更加实际
            if (m_callback)
                m_callback(msg);
        }
    }

    // 生产者线程
    void producer(int num)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (int i = 0; i < num; ++i) {
            static int  idx = 1;
            std::string msg = std::to_string(idx++) + " 号数据";
            m_q.push(msg);
        }

        // m_cond.notify_one(); // 唤醒一个被当前条件变量阻塞的线程
        m_cond.notify_all();
    }
};


int main()
{
    __Factory factory;

    // 注册框架的回调函数
    // factory.callback(handle);
    Handle obj;
    factory.callback(&Handle::handle, &obj);

    // 创建三个消费者
    std::thread t1(&__Factory::consumer, &factory);
    std::thread t2(&__Factory::consumer, &factory);
    std::thread t3(&__Factory::consumer, &factory);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    factory.producer(2); // 生产两个数据并唤醒

    std::this_thread::sleep_for(std::chrono::seconds(2));
    factory.producer(5); // 生产两个数据并唤醒

    // 回收子线程
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
