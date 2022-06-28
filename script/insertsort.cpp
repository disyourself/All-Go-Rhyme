#include <cstdio>
#include <iostream>
#include <stdio.h>

void printArray (int array[], int length);

void
insertSort (int array[], int length)
{
    for (int i = 1; i < length - 1; ++i)
    {
        if (array[i + 1] < array[i])
        {
            for (int k = i + 1; k > 0; k--)
                if (array[k] < array[k - 1])
                {
                    std::swap (array[k], array[k - 1]);
                }
        }

        printArray (array, 10);
    }
}

void
printArray (int array[], int length)
{
    for (int i = 0; i < length; ++i)
        printf ("%d ", array[i]);
    printf ("\n");
}

int
main ()
{
    int array[] = { 4, 3, 5, 1, 9, 6, 23, 84, 86, 15 };
    printArray (array, 10);
    printf ("\n");
    insertSort (array, 10);

    return 0;
}