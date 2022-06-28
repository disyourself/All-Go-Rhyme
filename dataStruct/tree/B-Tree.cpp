#include <stdio.h>

typedef struct Node
{
    int           level;
    int           keyNum;
    int           childNum;
    int          *keys;
    struct Node **children; // child ptr's array
    struct Node  *parent;
} Node;

Node *
initNode (int level)
{
    Node *node = new Node;
    node->level = level;
    node->keyNum = 0;
    node->childNum = 0;
    node->keys = new int[level + 1];
    node->children = new Node *[level];
    node->parent = nullptr;

    int i;
    for (i = 0; i < level; ++i)
    {
        node->keys[i] = 0;
        node->children[i] = nullptr;
    }
    node->keys[i] = 0;

    return node;
}

// find proper insert index in one node
int
findSuiteIndex (Node *node, int data)
{
    int index;
    for (index = 1; index <= node->keyNum; ++index)
        if (data < node->keys[index])
            break;

    return index;
}

// find proper insert leaf in one node's chilren
Node *
findSuiteLeafNode (Node *T, int data)
{
    if (T->childNum == 0)
        return T;
    // have children, is a root node
    else
    {
        int index = findSuiteIndex (T, data);
        return findSuiteLeafNode (T->children[index - 1], data);
    }
}

void
addData (Node *node, int data, Node **T)
{
    int index = findSuiteIndex (node, data);

    for (int i = node->keyNum; i >= index; i--)
    {
        node->keys[i + 1] = node->keys[i];
    }
    node->keys[index] = data;
    node->keyNum++;

    // judge T/F spilit
    if (node->keyNum == node->level)
    {
        // find split pos
        int   mid = node->level / 2 + node->level % 2;
        Node *lchild = initNode (node->level);
        Node *rchild = initNode (node->level);

        for (int i = 1; i < mid; ++i)
            addData (lchild, node->keys[i], T);

        for (int i = mid + 1; i <= node->keyNum; ++i)
            addData (rchild, node->keys[i], T);

        // move node's left part children to  mid that splited's left child
        for (int i = 0; i < mid; ++i)
        {
            lchild->children[i] = node->children[i];
            if (node->children[i] != nullptr)
            {
                node->children[i]->parent = lchild;
                lchild->childNum++;
            }
        }

        // move node's right part chilren to mid that splited's right child
        int index = 0;
        for (int i = mid; i < node->childNum; i++)
        {
            rchild->children[index++] = node->children[i];
            if (node->children[i] != nullptr)
            {
                node->children[i]->parent = rchild;
                rchild->childNum++;
            }
        }

        // operations to parent
        if (node->parent == nullptr)
        {
            Node *newParent = initNode (node->level);
            addData (newParent, node->keys[mid], T);

            newParent->children[0] = lchild;
            newParent->children[1] = rchild;
            newParent->childNum = 2;
            lchild->parent = newParent;
            rchild->parent = newParent;
            *T = newParent;
        }
        else
        {
            int index = findSuiteIndex (node->parent, node->keys[mid]);
            lchild->parent = node->parent;
            rchild->parent = node->parent;
            // replace the pos that node's mid move to its parent after splited left
            node->parent->children[index - 1] = lchild;
            if (node->parent->children[index] != nullptr)
            {
                for (int i = node->parent->childNum - 1; i >= index; i--)
                {
                    node->parent->children[i + 1] = node->parent->children[i];
                }
            }
            node->parent->children[index] = rchild;
            node->parent->childNum++;

            addData (node->parent, node->keys[mid], T);
        }
        /* for more infomation ./B-Tree_split_graph/B-Tree_split_graph.png */
    }
}

void
insert (Node **T, int data)
{
    Node *node = findSuiteLeafNode (*T, data);
    addData (node, data, T);
}

void
printTree (Node *T)
{
    if (T != nullptr)
    {
        // i =1 <= keyNum
        for (int i = 1; i <= T->keyNum; i++)
            printf ("%d ", T->keys[i]);
        printf ("\n");

        for (int i = 0; i < T->childNum; ++i)
            printTree (T->children[i]);
    }
}

int
main (int argc, char **argv)
{
    Node *T = initNode (5);
    insert (&T, 1);
    insert (&T, 2);
    insert (&T, 3);
    insert (&T, 4);
    insert (&T, 5);
    insert (&T, 6);
    insert (&T, 7);
    insert (&T, 8);
    insert (&T, 9);
    insert (&T, 10);
    insert (&T, 11);
    insert (&T, 12);
    insert (&T, 13);
    insert (&T, 14);
    insert (&T, 15);
    insert (&T, 16);
    insert (&T, 17);

    printTree (T);

    return 0;
}