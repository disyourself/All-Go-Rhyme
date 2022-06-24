#include <iostream>
#include <ostream>
#include <stdio.h>
#include <vector>

struct node
{
    int val;
    struct node *left;
    struct node *right;

    node (int num)
    {
        val = num;
        left = nullptr;
        right = nullptr;
    }
};

struct AVLTree
{
    struct node *root;
    std::vector<struct node *> nodes;

    AVLTree () { root = nullptr; }

    void insert (int num);
    bool find (int num);

    struct node *findInsertPos (int num);
    void printVals (node *n);
};

int
main ()
{
    int data[10] = { 7, 4, 9, 2, 5, 8, 11, 3, 12, 1 };

    AVLTree avt;

    for (int i = 0; i < 10; i++)
        avt.insert (data[i]);

    avt.printVals (avt.root);
    if (avt.find (5))
    {
        printf ("数字5c存在\n");
    }

    return 0;
}

void
AVLTree::insert (int num)
{
    if (this->root == nullptr)
    {
        root = new node (num);
        this->nodes.push_back (root);
    }
    else
    {
        node *pos = findInsertPos (num);
        if (!pos)
            return;
        if (pos->val > num)
        {
            pos->left = new node (num);
            nodes.push_back (pos->left);
        }
        else
        {
            pos->right = new node (num);
            nodes.push_back (pos->right);
        }
    }
}
bool
AVLTree::find (int num)
{
    node *temp = root;
    while (temp)
    {
        if (temp->val == num)
            return true;
        else if (temp->val < num)
            temp = temp->right;
        else if (temp->val > num)
            temp = temp->left;
    }
    return false;
}

struct node *
AVLTree::findInsertPos (int num)
{
    node *temp = root;
    while (1)
    {
        if (temp->val == num)
            return nullptr;
        else if (temp->val < num)
        {
            if (temp->right)
                temp = temp->right;
            else
                break;
        }
        else if (temp->val > num)
        {
            if (temp->left)
                temp = temp->left;
            else
                break;
        }
    }
    return temp;
}

void
AVLTree::printVals (node *n)
{
    if (!n)
        return;
    std::cout << n->val << " ";
    printVals (n->left);
    printVals (n->right);
}