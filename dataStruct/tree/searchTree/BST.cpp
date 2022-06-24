
#include <iostream>
#include <ostream>
typedef struct TreeNode
{
    int data;
    TreeNode *lchild;
    TreeNode *rchild;
} TreeNode;

void
bstInset (TreeNode **T, int key)
{
    if (*T == nullptr)
    {
        *T = new TreeNode;
        (*T)->data = key;
        (*T)->lchild = nullptr;
        (*T)->rchild = nullptr;
    }
    else if (key < (*T)->data)
        bstInset (&(*T)->lchild, key);
    else if (key > (*T)->data)
        bstInset (&(*T)->rchild, key);
    else
        return;
}

TreeNode *
bstSearch (TreeNode *T, int key)
{
    if (T)
    {
        if (T->data == key)
            return T;
        else if (T->data > key)
            return bstSearch (T->lchild, key);
        else if (key > T->data)
            return bstSearch (T->rchild, key);
    }
    return nullptr;
}

void
preOrderTraversal (TreeNode *T)
{
    if (!T)
        return;
    std::cout << T->data << " ";
    preOrderTraversal (T->lchild);
    preOrderTraversal (T->rchild);
}

int
main (int argc, char **argv)
{
    TreeNode *T = nullptr;
    int num[6] = { 8, 6, 10, 9, 11, 23 };
    for (int &i : num)
        bstInset (&T, i);

    preOrderTraversal (T);
    std::cout << std::endl;
    return 0;
}