#include <stdio.h>

typedef struct TreeNode
{
    char data;
    TreeNode *lchild;
    TreeNode *rchild;
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

void
iteratlyPreorder (TreeNode *T)
{
    TreeNode *node = T;
    StackNode *S = initStack ();
    while (node || !isEmpty (S))
    {
        if (node)
        {
            printf ("%c ", node->data);
            push (node, S);
            node = node->lchild;
        }
        else
        {
            node = pop (S)->data;
            node = node->rchild;
        }
    }
}

void
iteratlyInorder (TreeNode *T)
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
            node = pop (S)->data;
            printf ("%c ", node->data);
            node = node->rchild;
        }
    }
}

int
main (int argc, char **argv)
{
    TreeNode *root = new TreeNode;
    int index = 0;
    initTree (&root, argv[1], &index);

    iteratlyPreorder (root);
    printf ("\n");
    iteratlyInorder (root);
    printf ("\n");

    return 0;
}
