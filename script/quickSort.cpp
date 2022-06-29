#include "stdio.h"

void
printArr (int arr[], int length)
{
    for (int i = 0; i < length; ++i)
        printf ("%d ", arr[i]);
    printf ("\n");
}


int
partition (int arr[], int l, int r)
{
    int temp = arr[l];
    while (l < r)
    {
        while (l < r && arr[r] > temp)
            r--;
        if (l < r)
        {
            arr[l] = arr[r];
            ++l;
        }
        while (l < r && arr[l] <= temp)
            l++;
        if (l < r)
        {
            arr[r] = arr[l];
            r--;
        }
    }
    arr[l] = temp;

    return l;
}


void
quickSort (int arr[], int left, int right)
{
    if (left < right)
    {
        int index = partition (arr, left, right);
        printArr (arr, 9);
        quickSort (arr, left, index - 1);
        quickSort (arr, index + 1, right);
    }
}


int
main ()
{
    int arr[9] = { 13, 80, 28, 90, 60, 13, 40, 17 };
    printArr (arr, 9);

    quickSort (arr, 0, 8);
    printf ("\n");
    printArr (arr, 9);

    return 0;
}
