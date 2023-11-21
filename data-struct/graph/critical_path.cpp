#include <errno.h>
#include <stdio.h>
#include <string>

#define MAX 32767
#define M MAX

typedef struct Graph
{
    char *vexs;
    int **arcs;
    int   vexNum;
    int   arcNum;
} Graph;

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

void
createGraph (Graph *G, std::string vexs, int *arcs)
{
    for (int i = 0; i < G->vexNum; ++i)
    {
        G->vexs[i] = vexs[i];
        for (int j = 0; j < G->vexNum; ++j)
        {
            G->arcs[i][j] = *(arcs + i * G->vexNum + j);
            if (G->arcs[i][j] > 0 && G->arcs[i][j] != MAX)
                G->arcNum++;
        }
    }
}

void
DFS (Graph *G, int *visited, int index)
{
    printf ("%c ", G->vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G->vexNum; ++i)
        if (G->arcs[index][i] > 0 && G->arcs[index][i] != MAX && !visited[i])
            DFS (G, visited, i);
}

int *
findInDegress (Graph *G)
{
    int *indegress = new int[G->vexNum];
    for (int i = 0; i < G->vexNum; ++i)
        indegress[i] = 0;

    for (int i = 0; i < G->vexNum; ++i)
        for (int j = 0; j < G->vexNum; ++j)
            if (G->arcs[i][j] > 0 && G->arcs[i][j] != MAX)
                indegress[j]++;

    return indegress;
}

int *
topologicalSort (Graph *G)
{
    int   index = 0;
    int  *top = new int[G->vexNum];
    int  *inDegrees = findInDegress (G);
    Node *stack = initStack ();

    for (int i = 0; i < G->vexNum; ++i)
        if (inDegrees[i] == 0)
            push (stack, i);

    while (!isEmpty (stack))
    {
        int vex = pop (stack);
        top[index++] = vex;
        for (int i = 0; i < G->vexNum; ++i)
            // from vexs[vex] to vexs[i]
            if (G->arcs[vex][i] > 0 && G->arcs[vex][i] != MAX)
            {
                inDegrees[i] -= 1;
                if (inDegrees[i] == 0)
                    push (stack, i);
            }
    }

    for (int i = 0; i < index; i++)
        printf ("%c ", G->vexs[top[i]]);
    printf ("\n");

    return top;
}

int
getIndex (int *top, Graph *G, int i)
{
    int j;
    for (j = 0; j < G->vexNum; ++j)
    {
        if (top[j] == i)
            break;
    }
    return j;
}

void
criticalPath (Graph *G)
{
    int *top = topologicalSort (G);
    int  early[G->vexNum];
    int *late = new int[G->vexNum];
    for (int i = 0; i < G->vexNum; i++)
    {
        early[i] = 0;
        late[i] = 0;
    }

    // Calculate the early times
    for (int i = 0; i < G->vexNum; ++i)
    {
        int max = 0;
        for (int j = 0; j < G->vexNum; j++)
        {
            if (G->arcs[j][top[i]] > 0 && G->arcs[j][top[i]] != MAX)
            {
                int index = getIndex (top, G, j);
                if (early[index] + G->arcs[j][top[i]] > max)
                    max = early[index] + G->arcs[j][top[i]];
            }
        }
        early[i] = max;
    }

    for (int i = 0; i < G->vexNum; ++i)
        printf ("%c ", early[i]);
    printf ("\n");
}

int
main (int argc, char **argv)
{
    Graph *G = initGraph (9);
    int    arcs[9][9] = {
           { 0, 6, 4, 5, M, M, M, M, M },
           { M, 0, M, M, 1, M, M, M, M },
           { M, M, 0, M, 1, M, M, M, M },
           { M, M, M, 0, M, 2, M, M, M },
           { M, M, M, M, 0, M, 9, 7, M },
           { M, M, M, M, M, 0, M, 4, M },
           { M, M, M, M, M, M, 0, M, 2 },
           { M, M, M, M, M, M, M, 0, 4 },
           { M, M, M, M, M, M, M, M, 0 }
    };
    createGraph (G, "012345678", (int *)arcs);

    int visited[G->vexNum];
    for (auto &i : visited)
        i = 0;
    DFS (G, visited, 0);
    printf ("\n");
    // topologicalSort (G);

    criticalPath (G);

    return 0;
}