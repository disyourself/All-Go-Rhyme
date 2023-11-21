#include <algorithm>
#include <float.h>
#include <iostream>
#include <ostream>

typedef struct TreeNode
{
    int height;
    int data;
    TreeNode *lchild;
    TreeNode *rchild;
} TreeNode;

int
getHeight (TreeNode *T)
{
    return T ? T->height : 0;
}

void
rrRotation (TreeNode *node, TreeNode **root)
{
    TreeNode *temp = node->rchild;
    node->rchild = temp->lchild;
    temp->lchild = node;
    *root = temp;

    node->height
        = std::max (getHeight (node->lchild), getHeight (node->rchild)) + 1;
    temp->height
        = std::max (getHeight (temp->lchild), getHeight (temp->rchild)) + 1;
}

void
llRotation (TreeNode *node, TreeNode **root)
{
    TreeNode *temp = node->lchild;
    node->lchild = temp->lchild;
    temp->rchild = node;
    *root = temp;

    node->height
        = std::max (getHeight (node->lchild), getHeight (node->rchild)) + 1;
    temp->height
        = std::max (getHeight (temp->lchild), getHeight (temp->rchild)) + 1;
}

void
avlInsert (TreeNode **T, int data)
{
    if ((*T) == nullptr)
    {
        *T = new TreeNode;
        (*T)->data = data;
        (*T)->height = 0;
        (*T)->lchild = nullptr;
        (*T)->rchild = nullptr;
    }
    else if (data < (*T)->data)
    {
        avlInsert (&(*T)->lchild, data);

        // get cur node's l&r child height
        int lHeight = getHeight ((*T)->lchild);
        int rHeight = getHeight ((*T)->rchild);

        // judge height dif
        if (lHeight - rHeight == 2)
        {

            if (data < (*T)->lchild->data)
            {
                // LL adjust
                llRotation (*T, T);
            }
            else
            {
                // LR adjust
                rrRotation ((*T)->lchild, &(*T)->lchild);
                llRotation ((*T), T);
            }
        }
    }
    else if (data > (*T)->data)
    {
        avlInsert (&(*T)->rchild, data);

        int lHeight = getHeight ((*T)->lchild);
        int rHeight = getHeight ((*T)->rchild);

        if (rHeight - lHeight == 2)
        {
            if (data > (*T)->rchild->data)
            {
                // RR adjust
                rrRotation (*T, T);
            }
            else
            {
                // RL adjust
                llRotation ((*T)->rchild, &(*T)->rchild);
                rrRotation (*T, T);
            }
        }
    }

    (*T)->height
        = std::max (getHeight ((*T)->lchild), getHeight ((*T)->rchild)) + 1;
}

void
preOrder (TreeNode *T)
{
    if (!T)
        return;
    std::cout << T->data << " ";
    preOrder (T->lchild);
    preOrder (T->rchild);
}

int
main (int argc, char **argv)
{
    TreeNode *T = nullptr;
    int nums[5] = { 1, 2, 3, 4, 5 };
    for (int &i : nums)
        avlInsert (&T, i);

    preOrder (T);
    std::cout << std::endl;

    return 0;
}