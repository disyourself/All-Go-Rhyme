#include <iostream>
#include <ostream>
#include <stdio.h>

typedef struct TreeNode
{
    int weight;
    int parent;
    int lchild;
    int rchild;
} TreeNode;

typedef struct HFM
{
    TreeNode *data;
    int length;
} HFM;

HFM *
initTree (int *weight, int length)
{
    HFM *T = new HFM;
    T->data = new TreeNode[2 * length - 1];
    T->length = length;

    for (int i = 0; i < length; i++)
    {
        T->data[i].weight = weight[i];
        T->data[i].parent = 0;
        T->data[i].lchild = -1;
        T->data[i].rchild = -1;
    }
    return T;
}

int *
selectMin (HFM *T)
{
    int min = 10000;
    int secondMin = 10000;
    int minIndex;
    int secondIndex;

    for (int i = 0; i < T->length; i++)
    {
        if (T->data[i].parent == 0)
            if (T->data[i].weight < min)
            {
                min = T->data[i].weight;
                minIndex = i;
            }
    }
    for (int i = 0; i < T->length; i++)
    {
        if (T->data[i].parent == 0 && i != minIndex)
            if (T->data[i].weight < secondMin)
            {
                secondMin = T->data[i].weight;
                secondIndex = i;
            }
    }
    int *res = new int[2];
    res[0] = minIndex;
    res[1] = secondIndex;
    return res;
}

void
createHFM (HFM *T)
{
    int *res;
    int min;
    int secondMin;
    int length = T->length * 2 - 1;

    for (int i = T->length; i < length; i++)
    {
        res = selectMin (T);
        min = res[0];
        secondMin = res[1];

        // add new node init its father
        T->data[i].parent = 0;

        T->data[i].weight = T->data[min].weight + T->data[secondMin].weight;
        T->data[i].lchild = min;
        T->data[i].rchild = secondMin;
        // remove from select min
        T->data[min].parent = i;
        T->data[secondMin].parent = i;
        T->length++;
    }
}

void
preOrder (HFM *T, int index)
{
    if (index != -1)
    {
        printf ("%d ", T->data[index].weight);
        preOrder (T, T->data[index].lchild);
        preOrder (T, T->data[index].rchild);
    }
}

int
main (int argc, char **argv)
{
    int weight[7] = { 5, 1, 3, 6, 11, 2, 4 };
    HFM *T = initTree (weight, 7);
    createHFM (T);

    preOrder (T, T->length - 1);
    std::cout << std::endl;
    return 0;
}