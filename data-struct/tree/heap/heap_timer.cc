#include "heap_timer.h"

#include <algorithm>
#include <bits/types/timer_t.h>
#include <exception>
#include <iostream>
#include <iterator>


TimerHeap::TimerHeap(int capacity) : m_capacity(capacity)
{
    m_heapArray.resize(capacity);
    m_currentSize = 0;
    m_deletedNum  = 0;

    for (auto &timer : m_heapArray) {
        timer = nullptr;
    }
    std::make_heap(m_heapArray.begin(), m_heapArray.begin() + m_currentSize, compareHeapTimerNode);
}

TimerHeap::~TimerHeap()
{
    for (int i = 0; i < m_currentSize; i++) {
        delete m_heapArray[i];
        m_heapArray[i] = nullptr;
    }
}

void TimerHeap::addTimer(HeapTimerNode *timer)
{
    if (!timer)
        return;

    if (m_currentSize >= m_capacity) {
        resize();
    }

    m_heapArray[m_currentSize] = timer;
    ++m_currentSize;

    std::push_heap(m_heapArray.begin(), m_heapArray.begin() + m_currentSize, compareHeapTimerNode);
}

void TimerHeap::delTimer(HeapTimerNode *timer)
{
    if (!timer) {
        return;
    }

    timer->cb_func     = nullptr; // Reduce the cost of delete, only set CB and Flag as null
    timer->m_validFlag = false;
    m_deletedNum++;

    if (m_deletedNum >= m_currentSize / 2)
    {
        int validIndex = 0;
        for (int i = 0; i < m_currentSize; ++i)
        {
            if (m_heapArray[i]->m_validFlag) {
                m_heapArray[validIndex] = m_heapArray[i];
                validIndex++;
                m_heapArray[i] = nullptr;
            }
            else {
                delete m_heapArray[i];
                m_heapArray[i] = nullptr;
            }
        }
        m_currentSize = validIndex;
        std::make_heap(m_heapArray.begin(), m_heapArray.begin() + m_currentSize, compareHeapTimerNode);
    }
}


HeapTimerNode *TimerHeap::getTop()
{
    if (isEmpty()) {
        return nullptr;
    }
    else {
        return m_heapArray.front();
    }
}

void TimerHeap::delTop()
{
    if (isEmpty()) {
        return;
    }

    // pop_heap: move front to last
    std::pop_heap(m_heapArray.begin(), m_heapArray.begin() + m_currentSize, compareHeapTimerNode);

    // delete that timer
    delete m_heapArray[m_currentSize - 1];
    m_heapArray[m_currentSize - 1] = nullptr;
    m_currentSize--;
}

bool TimerHeap::isEmpty()
{
    return m_currentSize == 0;
}

void TimerHeap::tick()
{
    auto pTopTiemr = getTop();

    time_t curTime = time(nullptr);

    while (!isEmpty())
    {
        if (!pTopTiemr) {
            break;
        }
        // If top timer hasn't expire
        if (pTopTiemr->m_expire > curTime) {
            break;
        }

        // Or did call back
        if (pTopTiemr->m_validFlag && pTopTiemr->cb_func != nullptr) {
            pTopTiemr->cb_func(pTopTiemr->p_userData);
        }

        delTop();
        pTopTiemr = getTop();
    }
}

void TimerHeap::resize()
{
    m_currentSize *= 2;
    m_heapArray.resize(m_currentSize);
}


void TimerHeap::showAllTimer()
{
    std::cout << "Timer:\n";

    for (int i = 0; i < m_capacity; ++i)
    {
        if (m_heapArray[i] == nullptr) {
            break;
        }

        std::cout << m_heapArray[i]->m_expire << " ";
    }
    std::cout << std::endl;
}
