
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode;

typedef struct QueueNode
{
    TreeNode *treenode;
    QueueNode *pre;
    QueueNode *next;
} QueueNode;

void
creatTree (TreeNode **T, char *data, int *index)
{
    char ch;
    ch = data[*index];
    *index += 1;
    if (ch == '#')
        *T = nullptr;
    else
    {
        *T = (TreeNode *)malloc (sizeof (TreeNode));
        (*T)->data = ch;
        creatTree (&((*T)->lchild), data, index);
        creatTree (&((*T)->rchild), data, index);
    }
}

void
preOrder (TreeNode *T)
{
    if (T == nullptr)
        return;
    printf ("%c ", T->data);
    preOrder (T->lchild);
    preOrder (T->rchild);
}

QueueNode *
initQueue ()
{
    QueueNode *Q = new QueueNode;
    Q->next = Q;
    Q->pre = Q;
    Q->treenode = nullptr;
    return Q;
}

void
enQueue (QueueNode *Q, TreeNode *T)
{
    QueueNode *node = new QueueNode;
    node->treenode = T;
    node->next = Q;
    //
    node->pre = Q->pre;
    Q->pre->next = node;
    Q->pre = node;
}

int
isEmpty (QueueNode *Q)
{
    if (Q->next == Q)
        return 1;
    return 0;
}

QueueNode *
deQueue (QueueNode *Q)
{
    if (isEmpty (Q))
        return nullptr;

    QueueNode *node = Q->next;
    Q->next->next->pre = Q;
    Q->next = Q->next->next;
    return node;
}

void
layerTraversal (QueueNode *Q, TreeNode *T)
{
    enQueue (Q, T);
    while (!isEmpty (Q))
    {
        QueueNode *node = deQueue (Q);
        printf ("%c ", node->treenode->data);
        if (node->treenode->lchild)
            enQueue (Q, node->treenode->lchild);

        if (node->treenode->rchild)
            enQueue (Q, node->treenode->rchild);
    }
}

int
main (int argc, char **argv)
{

    TreeNode *T;
    int index = 0;
    creatTree (&T, argv[1], &index);
    preOrder (T);
    printf ("\n");

    QueueNode *Q = initQueue ();
    layerTraversal (Q, T);
    std::cout << std::endl;
    return 0;
}