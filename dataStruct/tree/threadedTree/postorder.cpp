
#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    struct TreeNode *parent;
    int ltag;
    int rtag;
} TreeNode;

void
creatTree (TreeNode **T, char *data, int *index, TreeNode *parent)
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
        (*T)->parent = parent;
        creatTree (&((*T)->lchild), data, index, *T);
        creatTree (&((*T)->rchild), data, index, *T);
    }
}

TreeNode *
getFirst (TreeNode *T)
{
    while (T->ltag == 0)
        T = T->lchild;
    if (T->rtag == 0)
        return getFirst (T->rchild);
    return T;
}

TreeNode *
getNext (TreeNode *node)
{
    if (node->rtag == 1)
        return node->rchild;
    else
    {
        // if root node
        if (node->parent == nullptr)
            return nullptr;
        // if rchild
        else if (node->parent->rchild == node)
            return node->parent;
        // if lchild
        else
        {
            if (node->parent->ltag == 0)

                return getFirst (node->parent->rchild);
            else
                return node->parent;
        }
        return getNext (node->rchild);
    }
}

void
initTreadTree (TreeNode *T, TreeNode **pre)
{
    if (T)
    {

        initTreadTree (T->lchild, pre);
        initTreadTree (T->rchild, pre);

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
    }
}

int
main (int argc, char **argv)
{
    TreeNode *root;
    int index = 0;
    creatTree (&root, argv[1], &index, nullptr);

    TreeNode *pre = nullptr;
    initTreadTree (root, &pre);

    for (TreeNode *node = getFirst (root); node != nullptr;
         node = getNext (node))
        printf ("%c ", node->data);
    printf ("\n");

    return 0;
}