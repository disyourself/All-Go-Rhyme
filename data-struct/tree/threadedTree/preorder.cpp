
#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    int ltag;
    int rtag;
} TreeNode;

void
creatTree (TreeNode **T, char *data, int *index)
{
    char ch;
    ch = data[*index];
    *index += 1;

    if (ch == '#')
    {
        // empty node
        *T = nullptr;
    }
    else
    {
        *T = (TreeNode *)malloc (sizeof (TreeNode));
        (*T)->data = ch;
        (*T)->ltag = 0;
        (*T)->rtag = 0;
        creatTree (&((*T)->lchild), data, index);
        creatTree (&((*T)->rchild), data, index);
    }
}


TreeNode *
getNext (TreeNode *node)
{
    if (node->rtag == 1)
        return node->rchild;
    else
    {
        if (node->ltag == 0)
            return node->lchild;
        else
            return node->rchild;
    }
}

void
initTreadTree (TreeNode *T, TreeNode **pre)
{
    if (T)
    {
        // connect pre and cur
        if (T->lchild == nullptr)
        {
            T->ltag = 1;
            T->lchild = *pre;
        }
        if (*pre != nullptr && (*pre)->rchild == nullptr)
        {
            (*pre)->rtag = 1;
            (*pre)->rchild = T;
        }
        *pre = T;

        if (T->ltag == 0)
            initTreadTree (T->lchild, pre);
        initTreadTree (T->rchild, pre);
    }
}

int
main (int argc, char **argv)
{
    TreeNode *root;
    int index = 0;
    creatTree (&root, argv[1], &index);

    TreeNode *pre = nullptr;
    initTreadTree (root, &pre);
    pre->rtag = 0;
    pre->rchild = nullptr;
    
    for (TreeNode *node = root; node != nullptr; node = getNext (node))
        printf ("%c ", node->data);
    printf ("\n");

    return 0;
}