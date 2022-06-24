
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <vector>

// 顺序开始，数字如果大，向上移动
// arr[0...index-1]已经是大根堆了，现在某个数字处在index，向上 移动
void
heapInsert (std::vector<int> &arr, int index)
{
    while (arr[index] > arr[(index - 1) / 2])
    {
        std::swap (arr[index], arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// 逆序开始，判断每个数字是否比下面小，向下移动
// 形成大根堆
// 某个数在index位置，看看能否往 下沉
// 不断和左右两个孩子比较
void
heapify (std::vector<int> &array, int index, int heapsize)
{
    int left = index * 2 + 1; // 左孩子的下标

    while (left < heapsize)
    {
        // 左右孩子中，谁的值大，把下标给 largest
        int largest = left + 1 < heapsize && array[left + 1] > array[left]
                          ? left + 1
                          : left;
        // 父和较大的孩子大的把下标给largest
        largest = array[largest] > array[index] ? largest : index;
        // 如果下标相等就break
        if (largest == index)
            break;

        // 把大的换上来
        std::swap (array[largest], array[index]);

        // 切换到
        // 换下去的节点->节点左孩子->左右孩子较大的->是否与这个节点交换->loop
        index = largest;
        left = index * 2 + 1;
    }
}

void
heapSort (std::vector<int> &array)
{
    /* for (int i = 0; i < array.size (); i++)
    {
        heapInsert (array, i);
    } */

    for (int i = array.size () - 1; i >= 0; i--)
    {
        heapify (array, i, array.size ());
    }

    // 将大根与最后一个换位，然后对 0 到 heapSize-1 做heapfiy， 堆排序完成
    int heapSize = array.size ();
    // std::swap (array[0], array[--heapSize]);
    while (heapSize > 0)
    {
        heapify (array, 0, heapSize);
        std::swap (array[0], array[--heapSize]);
    }
}

int
main ()
{
    std::vector<int> array{ 5, 8, 7, 4, 2, 3, 1, 9 };

    heapSort (array);

    for (auto i : array)
        printf ("%d", i);
    std::cout << std::endl;

    return 0;
}