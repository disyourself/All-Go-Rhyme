#ifndef HEAP_TIMER_L_H
#define HEAP_TIMER_L_H

#include <arpa/inet.h>
#include <bits/types/time_t.h>
#include <netinet/in.h>
#include <time.h>

#include <algorithm>
#include <vector>



#define BUF_SIZ 64



class HeapTimerNode;

struct ClientData
{
    sockaddr_in    address;
    int            sockfd;
    char           buf[BUF_SIZ];
    HeapTimerNode *timer;
};

class HeapTimerNode
{
  public:
    HeapTimerNode(int delay)
    {
        //m_expire    = delay;
        m_expire    = time(nullptr) + delay;
        m_validFlag = true;
    }

  public:

    time_t      m_expire;
    bool        m_validFlag;
    ClientData *p_userData;

    void (*cb_func)(ClientData *); // timer的回调函数
};


// 谓词 构建heap时的比较函数
inline bool compareHeapTimerNode(HeapTimerNode *node_A, HeapTimerNode *node_B)
{
    return node_A->m_expire > node_B->m_expire;
}


class TimerHeap
{
  public:
    TimerHeap(int capacity);
    ~TimerHeap();

  public:

    void addTimer(HeapTimerNode *timer);

    void delTimer(HeapTimerNode *timer);

    HeapTimerNode *getTop();
    void           delTop();

    void tick();

    void showAllTimer();

    bool isEmpty();

  private:
    void resize();

  private:

    std::vector<HeapTimerNode *> m_heapArray;

    int m_capacity;
    int m_currentSize;
    int m_deletedNum;
};



#endif
