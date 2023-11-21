
#include "heap_timer.h"
#include <stdlib.h>
#include <unistd.h>



int main()
{
    HeapTimerNode *node1 = new HeapTimerNode(6);
    HeapTimerNode *node2 = new HeapTimerNode(2);
    HeapTimerNode *node3 = new HeapTimerNode(9);
    HeapTimerNode *node4 = new HeapTimerNode(7);
    HeapTimerNode *node5 = new HeapTimerNode(4);
    HeapTimerNode *node6 = new HeapTimerNode(11);
    HeapTimerNode *node7 = new HeapTimerNode(5);



    TimerHeap heap(10);

    heap.addTimer(node1);
    heap.addTimer(node2);
    heap.addTimer(node3);
    heap.addTimer(node4);
    heap.addTimer(node5);
    heap.addTimer(node6);
    heap.addTimer(node7);

    heap.getTop();

    heap.showAllTimer();
    heap.tick();
    heap.showAllTimer();


    heap.showAllTimer();
    heap.tick();
    heap.showAllTimer();

    sleep(5);

    heap.showAllTimer();
    heap.tick();
    heap.showAllTimer();

    return 0;
}
