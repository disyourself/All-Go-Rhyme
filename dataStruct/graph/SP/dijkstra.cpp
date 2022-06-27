
#include <stdio.h>
#include <string>

#define MAX 32767

typedef struct Graph
{
    char *vexs;
    int **edges;
    int vexNum;
    int edgeNum;
} Graph;

Graph *
initGraph (int num)
{
    Graph *G = new Graph;
    G->vexs  = new char[num];
    G->edges = new int *[num];
    for (int i = 0; i < num; ++i)
        G->edges[i] = new int[num];

    G->vexNum  = num;
    G->edgeNum = 0;
    return G;
}

void
creatGraph (Graph *G, std::string vexs, int *edges)
{
    for (int i = 0; i < G->vexNum; ++i)
    {
        G->vexs[i] = vexs[i];
        for (int j = 0; j < G->vexNum; ++j)
        {
            G->edges[i][j] = *(edges + i * G->vexNum + j);
            if (G->edges[i][j] > 0 && G->edges[i][j] != MAX)
                ++G->edgeNum;
        }
    }
    G->edgeNum /= 2;
}

void
DFS (Graph *G, int *visited, int index)
{
    printf ("%c ", G->vexs[index]);
    visited[index] = 1;
    for (int i = 0; i < G->vexNum; ++i)
    {
        if (G->edges[index][i] > 0 && G->edges[index][i] != MAX && !visited[i])
            DFS (G, visited, i);
    }
}

int
getMin (int *d, int *s, Graph *G)
{
    int min = MAX;
    int index;
    for (int i = 0; i < G->vexNum; i++)
        if (!s[i] && d[i] < min)
        {
            min   = d[i];
            index = i;
        }
    return index;
}

void
dijstra (Graph *G, int index)
{
    int *s = new int[G->vexNum]; // solved
    int *p = new int[G->vexNum]; // previous Vertex
    int *d = new int[G->vexNum]; // distance

    for (int i = 0; i < G->vexNum; ++i)
    {
        s[i] = i == index ? 1 : 0;
        {
            if (G->edges[index][i] > 0 && G->edges[index][i] != MAX)
                p[i] = index;
            else
                p[i] = -1;
        }
        d[i] = G->edges[index][i];
    }

    for (int i = 0; i < G->vexNum; ++i)
        printf ("%d\t%d\t%d\n", s[i], p[i], d[i]);
    printf ("---------------------------------\n");

    for (int i = 0; i < G->vexNum - 1; i++)
    {
        index    = getMin (d, s, G);
        s[index] = 1;
        for (int j = 0; j < G->vexNum; j++)
        {
            if (!s[j] && d[index] + G->edges[index][j] < d[j])
            {
                d[j] = d[index] + G->edges[index][j];
                p[j] = index;
            }
        }
    }

    for (int i = 0; i < G->vexNum; ++i)
        printf ("%d\t%d\t%d\n", s[i], p[i], d[i]);
    printf ("---------------------------------\n");
}

int
main (int argc, char **argv)
{
    Graph *G       = initGraph (7);
    int arcs[7][7] = {
        { 0, 12, MAX, MAX, MAX, 16, 14 },
        { 12, 0, 10, MAX, MAX, 7, MAX },
        { MAX, 10, 0, 3, 5, 6, MAX },
        { MAX, MAX, 3, 0, 4, MAX },
        { MAX, MAX, 5, 4, 0, 2, 8 },
        { 16, 7, 6, MAX, 2, 0, 9 },
        { 14, MAX, MAX, MAX, 8, 9, 0 }
    };
    creatGraph (G, "1234567", (int *)arcs);

    int *visited = new int[G->vexNum];
    for (int i = 0; i < G->vexNum; ++i)
        visited[i] = 0;
    DFS (G, visited, 0);
    printf ("\n");

    dijstra (G, 0);

    return 0;
}