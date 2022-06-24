

#include <iostream>
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
        {
            if (T->data[i].weight < min)
            {
                min = T->data[i].weight;
                minIndex = i;
            }
        }
    }
    for (int i = 0; i < T->length; i++)
    {
        if (T->data[i].parent == 0 && i != minIndex)
            if (T->data[i].weight < min)
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
        T->data[i].weight = T->data[min].weight + T->data[secondMin].weight;
        T->data->lchild = min;
    }
}

int
main (int argc, char **argv)
{
    int weight[4] = { 1, 2, 3, 4 };
    HFM *T = initTree (weight, 4);

    int *res = selectMin (T);
    std::cout << "res[0]= " << res[0];
    std::cout << "res[1]= " << res[1];
    return 0;
}