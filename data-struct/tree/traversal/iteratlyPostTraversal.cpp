
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    char data;
    TreeNode *lchild;
    TreeNode *rchild;
    int flag;
} TreeNode;

void
initTree (TreeNode **T, char *data, int *index)
{
    char ch;
    ch = data[*index];
    *index += 1;

    if (ch == '#')
        (*T) = nullptr;
    else
    {
        *T = new TreeNode;
        (*T)->data = ch;
        (*T)->flag = 0;
        initTree (&((*T)->lchild), data, index);
        initTree (&((*T)->rchild), data, index);
    }
}

typedef struct StackNode
{
    TreeNode *data;
    struct StackNode *next;
} StackNode;

StackNode *
initStack ()
{
    StackNode *S = new StackNode;
    S->data = nullptr;
    S->next = nullptr;
    return S;
}

void
push (TreeNode *data, StackNode *S)
{
    StackNode *node = new StackNode;
    node->data = data;
    node->next = S->next;
    S->next = node;
}

int
isEmpty (StackNode *S)
{
    if (S->next == nullptr)
        return 1;
    else
        return 0;
}

StackNode *
pop (StackNode *S)
{
    if (isEmpty (S))
        return nullptr;
    else
    {
        StackNode *node = S->next;
        S->next = S->next->next;
        return node;
    }
}

StackNode *
getTop (StackNode *S)
{
    if (isEmpty (S))
        return nullptr;
    else
    {
        StackNode *node = S->next;
        return node;
    }
}

void
postOrder (TreeNode *T)
{
    TreeNode *node = T;
    StackNode *S = initStack ();

    while (node || !isEmpty (S))
    {
        if (node)
        {
            push (node, S);
            node = node->lchild;
        }
        else
        {
            TreeNode *top = getTop (S)->data;
            if (top->rchild && top->rchild->flag == 0)
            {
                top = top->rchild;
                push (top, S);
                node = top->lchild;
            }
            else
            {
                top = pop (S)->data;
                printf ("%c ", top->data);
                top->flag = 1;
            }
        }
    }
}

int
main (int argc, char **argv)
{
    TreeNode *T;
    int index = 0;
    initTree (&T, argv[1], &index);

    postOrder (T);
    printf ("\n");

    return 0;
}