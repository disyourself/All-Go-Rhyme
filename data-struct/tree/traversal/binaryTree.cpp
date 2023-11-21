

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode;

void
creatTree (TreeNode **T, char *data, int *index)
{
    char ch;
    ch = data[*index];
    *index += 1;

    if (ch == '#' )
    {
        // empty node
        *T = nullptr;
    }
    else
    {
        *T = (TreeNode *)malloc (sizeof (TreeNode));
        (*T)->data = ch;
        creatTree (&((*T)->lchild), data, index);
        creatTree (&((*T)->rchild), data, index);
    }
}

void
preOrder (TreeNode *node)
{
    if (node == nullptr)
        return;

    std::cout << node->data << " ";
    preOrder (node->lchild);
    preOrder (node->rchild);
}

void
midOrder (TreeNode *node)
{
    if (node == nullptr)
        return;

    preOrder (node->lchild);
    std::cout << node->data << " ";
    preOrder (node->rchild);
}

void
postOrder (TreeNode *node)
{
    if (node == nullptr)
        return;

    preOrder (node->lchild);
    preOrder (node->rchild);
    std::cout << node->data << " ";
}

int
main (int argc, char **argv)
{
    TreeNode *root;
    int index = 0;
    creatTree (&root, argv[1], &index);

    preOrder (root);
    cout << endl;
    midOrder (root);
    cout << endl;
    postOrder (root);
    cout << endl;
    return 0;
}