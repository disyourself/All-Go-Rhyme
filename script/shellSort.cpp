#include <stdio.h>


void
printArr (int *arr, int length)
{
    for (int i = 0; i < length; ++i)
        printf ("%d ", arr[i]);
    printf ("\n");
}


/**
 * @brief Shell Sort
 *  1. From the step of k, partical groupping the array, do insert sort of  array;
    2. Decrease the length of step, redo 1st , until k = 1;
 * @param arr
 * @param length
 * @param step
 */
void
shellSort (int *arr, int length, int step)
{
    for (int i = 0; i < length; ++i)
        // compare 2 elements of opposite pos of step
        for (int j = i + step; j < length; j += step)
            for (int k = i; k < j; k += step)
                // if the rear lesser than the front
                if (arr[j] < arr[k])
                {
                    // the last smallest element
                    int temp = arr[j];
                    // swap the front element to rear by one step
                    for (int l = j - step; l >= k; l -= step)
                    {
                        arr[l + step] = arr[l];
                    }
                    // headmost element = smallest
                    arr[k] = temp;
                }
}

int
main (int argc, char **argv)
{
    int arr[10] = { 49, 38, 65, 97, 76, 13, 29, 49, 55, 4 };
    printArr (arr, 10);

    int step = 5;
    while (step >= 1)
    {
        shellSort (arr, 10, step);
        step /= 2;
        printArr (arr, 10);
    }

    return 0;
}