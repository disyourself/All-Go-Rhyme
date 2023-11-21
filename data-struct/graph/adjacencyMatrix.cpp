#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdio.h>

/*    Circular Queue       */
#define MAXSIZE 5
struct Queue;
Queue *initQueue ();
int    isFull (Queue *Q);
int    isEmpty (Queue *Q);
int    enQueue (Queue *Q, int data);
int    deQueue (Queue *Q);
/***************************/

typedef struct Graph
{
    char *vexs; // vertexs
    int **arcs; // edges
    int   vexNum;
    int   arcNum;
} Graph;

Graph *
initGraph (int vexNum)
{
    Graph *G = (Graph *)std::malloc (sizeof (Graph));
    G->vexs  = (char *)std::malloc (sizeof (char) * vexNum);

    // maintain  vexNum  ptrs
    G->arcs = (int **)std::malloc (sizeof (int *) * vexNum);
    for (int i = 0; i < vexNum; i++)
    {
        // malloc memory for every ptr
        G->arcs[i] = (int *)std::malloc (sizeof (int) * vexNum);
    }

    G->vexNum = vexNum;
    G->arcNum = 0;
    return G;
}

void
creatGraph (Graph *G, std::string vexs, int *arcs)
{
    for (int i = 0; i < G->vexNum; i++)
    {
        G->vexs[i] = vexs[i];
        for (int j = 0; j < G->vexNum; j++)
        {
            // arcs + i* vexNum == i+1
            G->arcs[i][j] = *(arcs + i * G->vexNum + j);
            if (G->arcs[i][j] != 0)
                G->arcNum++;
        }
    }
    G->arcNum /= 2;
}

void
DFS (Graph *G, int *visited, int vexIndex)
{
    printf ("%c ", G->vexs[vexIndex]);
    visited[vexIndex] = 1;

    for (int i = 0; i < G->vexNum; i++)
        if (G->arcs[vexIndex][i] == 1 && !visited[i])
            DFS (G, visited, i);
}

void
BFS (Graph *G, int *visited, int index)
{
    Queue *Q = initQueue ();
    printf ("%c ", G->vexs[index]);
    visited[index] = 1;
    enQueue (Q, index);

    while (!isEmpty (Q))
    {
        int i = deQueue (Q);
        for (int j = 0; j < G->vexNum; j++)
        {
            if (G->arcs[i][j] == 1 && !visited[j])
            {
                printf ("%c ", G->vexs[j]);
                visited[j] = 1;
                enQueue (Q, j);
            }
        }
    }
}

int
main (int argc, char **argv)
{
    Graph *G = initGraph (5);

    int arcs[5][5] = { { 0, 1, 1, 1, 0 }, { 1, 0, 1, 1, 1 }, { 1, 1, 0, 0, 0 }, { 1, 1, 0, 0, 1 }, { 0, 1, 0, 1, 0 } };

    creatGraph (G, "ABCDE", (int *)arcs);

    int *visited = new int[G->vexNum];
    for (int i = 0; i < G->vexNum; i++)
        visited[i] = 0;

    DFS (G, visited, 0);
    std::cout << std::endl;

    for (int i = 0; i < G->vexNum; i++)
        visited[i] = 0;
    BFS (G, visited, 0);
    std::cout << std::endl;
    return 0;
}

//////////////////////////////////////////////////////////////////////

typedef struct Queue
{
    int front;
    int rear;
    int data[MAXSIZE];
} Queue;

Queue *
initQueue ()
{
    Queue *Q = new Queue;
    Q->front = Q->rear = 0;
    return Q;
}

int
isFull (Queue *Q)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front)
        return 1;
    return 0;
}

int
isEmpty (Queue *Q)
{
    if (Q->front == Q->rear)
        return 1;
    return 0;
}

int
enQueue (Queue *Q, int data)
{
    if (isFull (Q))
        return 0;
    Q->data[Q->rear] = data;
    Q->rear          = (Q->rear + 1) % MAXSIZE;
    return 1;
}

int
deQueue (Queue *Q)
{
    if (isEmpty (Q))
        return -1;
    int data = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return data;
}
