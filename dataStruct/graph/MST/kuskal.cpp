#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <string>

#define MAX 32767

typedef struct Graph
{
    char *vexs;
    int **edges;
    int edgeNum;
    int vexNum;
} Graph;

typedef struct Edge
{
    int start;
    int end;
    int weight;
} Edge;

Graph *
initGraph (int num)
{
    Graph *G = new Graph;
    G->vexs  = new char[num];
    G->edges = new int *[num];
    for (int i = 0; i < num; i++)
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
            if (G->edges[i][j] != 0 && G->edges[i][j] != MAX)
                G->edgeNum++;
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

Edge *
initEdge (Graph *G)
{
    int index  = 0;
    Edge *edge = new Edge[G->edgeNum];
    for (int i = 0; i < G->vexNum; ++i)
    {
        for (int j = i + 1; j < G->vexNum; j++)
        {

            // egde's weight = 0 indicate one vertex are connected omponent with itself
            if (G->edges[i][j] != MAX)
            {
                edge[index].start  = i;
                edge[index].end    = j;
                edge[index].weight = G->edges[i][j];
                index++;
            }
        }
    }
    return edge;
}

void
sortEdge (Edge *edge, Graph *G)
{
    Edge temp;
    for (int i = 0; i < G->edgeNum - 1; ++i)
        for (int j = 0; j < G->edgeNum - 1; ++j)
        {
            if (edge[j].weight > edge[j + 1].weight)
            {
                temp        = edge[j];
                edge[j]     = edge[j + 1];
                edge[j + 1] = temp;
            }
        }
}

void
kruskal (Graph *G)
{
    int *connected = new int[G->vexNum];
    for (int i = 0; i < G->vexNum; ++i)
        connected[i] = i;

    Edge *edge = initEdge (G);
    sortEdge (edge, G);
    for (int i = 0; i < G->edgeNum; ++i)
    {
        int start = connected[edge[i].start];
        int end   = connected[edge[i].end];
        // egde's weight = 0 indicate one vertex are connected component with itself
        if (start != end)
        {
            printf ("v%c --> v%c , weight= %d\n",
                    G->vexs[edge[i].start], G->vexs[edge[i].end], edge[i].weight);
            for (int j = 0; j < G->vexNum; ++j)
            {
                if (connected[j] == end)
                    connected[j] = start;
            }
        }
    }
}

int
main (int argc, char **argv)
{
    Graph *G = initGraph (6);

    int arcs[6][6] = {
        { 0, 6, 1, 5, MAX, MAX },
        { 6, 0, 5, MAX, 3, MAX },
        { 1, 5, 0, 5, 6, 4 },
        { 5, MAX, 5, 0, MAX, 2 },
        { MAX, 3, 6, MAX, 0, 6 },
        { MAX, MAX, 4, 2, 6, 0 },
    };
    creatGraph (G, "123456", (int *)arcs);

    int *visited = new int[G->vexNum];
    for (int i = 0; i < G->vexNum; ++i)
        visited[i] = 0;

    DFS (G, visited, 0);
    std::printf ("\n");

    kruskal (G);

    return 0;
}