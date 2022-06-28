
#include <stdio.h>
#include <string>

#define MAX 32767

typedef struct Graph
{
    char *vexs;
    int **arcs;
    int   vexNum;
    int   arcNum;
} Graph;

Graph *
initGraph (int num)
{
    Graph *G = new Graph;
    G->vexs = new char[num];
    G->arcs = new int *[num];
    for (int i = 0; i < num; ++i)
        G->arcs[i] = new int[num];

    G->vexNum = num;
    G->arcNum = 0;
    return G;
}

typedef struct Node
{
    int   data;
    Node *next;
} Node;

Node *
initStack ()
{
    Node *stack = new Node;
    stack->data = 0;
    stack->next = nullptr;
    return stack;
}

int
isEmpty (Node *stack)
{
    return stack->next ? 0 : 1;
}

void
push (Node *stack, int data)
{
    Node *node = new Node;
    node->data = data;
    node->next = stack->next;
    stack->next = node;
    stack->data++;
}

int
pop (Node *stack)
{
    if (!isEmpty (stack))
    {
        Node *node = stack->next;
        stack->next = node->next;
        return node->data;
    }
    return -1;
}

void
createGraph (Graph *G, std::string vexs, int *arcs)
{
    for (int i = 0; i < G->vexNum; ++i)
    {
        G->vexs[i] = vexs[i];
        for (int j = 0; j < G->vexNum; ++j)
        {
            G->arcs[i][j] = *(arcs + i * G->vexNum + j);
            if (G->arcs[i][j] != 0)
                G->arcNum++;
        }
    }
    G->arcNum /= 2;
}

void
DFS (Graph *G, int *visited, int index)
{
    printf ("%c ", G->vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G->vexNum; ++i)
    {
        if (G->arcs[index][i] != 0 && !visited[i])
            DFS (G, visited, i);
    }
}

int *
findInDegress (Graph *G)
{
    int *inDegress = new int[G->vexNum];
    for (int i = 0; i < G->vexNum; ++i)
        inDegress[i] = 0;
    for (int i = 0; i < G->vexNum; ++i)
    {
        for (int j = 0; j < G->vexNum; ++j)
        {
            if (G->arcs[i][j])
                inDegress[j] += 1;
        }
    }
    return inDegress;
}

void
toplogicalSort (Graph *G)
{
    int  index = 0;
    int *top = new int[G->vexNum];
    int *inDegresss = findInDegress (G);

    Node *stack = initStack ();
    // push vex that indegress == 1 to stack
    for (int i = 0; i < G->vexNum; ++i)
        if (inDegresss[i] == 0)
            push (stack, i);

    while (!isEmpty (stack))
    {
        int vex = pop (stack);
        top[index++] = vex;
        for (int i = 0; i < G->vexNum; ++i)
            // sub 1 indegress from the top vex  to other vex can connect
            if (G->arcs[vex][i] > 0)
            {
                inDegresss[i] -= 1;
                // push 0 indgress vex to stack, loop
                if (inDegresss[i] == 0)
                    push (stack, i);
            }
    }

    for (int i = 0; i < index; ++i)
    {
        printf ("%c ", G->vexs[top[i]]);
    }
    if (index < G->vexNum)
        printf ("图是有环的");
    printf ("\n");
}

int
main ()
{
    Graph *G = initGraph (6);
    int    arcs[6][6] = { { 0, 1, 1, 1, 0, 0 },
                          { 0, 0, 0, 0, 0, 0 },
                          { 0, 1, 0, 0, 1, 0 },
                          { 0, 0, 0, 0, 1, 0 },
                          { 0, 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 1, 1, 0 } };
    createGraph (G, "123456", (int *)arcs);

    int *visited = new int[G->vexNum];
    for (int i = 0; i < G->vexNum; ++i)
        visited[i] = 0;

    DFS (G, visited, 0);
    printf ("\n");

    toplogicalSort (G);

    return 0;
}