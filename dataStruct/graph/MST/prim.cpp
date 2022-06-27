#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>

// minimal spanning tree
// 最小生成树 prim

/**
 *  remove the edge of one V to itself
 *  no connected of two vertex, val = MAX
 *  if vertex is itself, val = 0
 */
#define MAX 32767

typedef struct Graph
{
    char *vexs;
    int **edges;
    int vexNum;
    int edgeNum;
} Graph;

typedef struct Edge
{
    char vex;
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
    for (int i = 0; i < G->vexNum; i++)
    {
        G->vexs[i] = vexs[i];
        for (int j = 0; j < G->vexNum; j++)
        {
            G->edges[i][j] = *(edges + i * G->vexNum + j);
            if (G->edges[i][j] != 0 && G->edges[i][j] != MAX)
                ++G->edgeNum;
        }
    }
    G->edgeNum /= 2;
}

void
DFS (Graph *G, int *visited, int index)
{
    std::cout << G->vexs[index] << " ";
    visited[index] = 1;

    for (int i = 0; i < G->vexNum; ++i)
    {
        if (G->edges[index][i] > 0 && G->edges[index][i] != MAX && !visited[i])
        {
            DFS (G, visited, i);
        }
    }
}

/**
 * judge the vertex whether in U set
 * while edge.weight == 0, indicate current vertex has add to U set
 */
Edge *
initEdge (Graph *G, int index)
{
    Edge *edge = new Edge[G->vexNum];
    for (int i = 0; i < G->vexNum; ++i)
    {
        edge[i].vex    = G->vexs[index];
        edge[i].weight = G->edges[index][i];
    }
    return edge;
}

int
getMinEdge (Edge *edge, Graph *G)
{
    int index;
    int min = MAX;
    for (int i = 0; i < G->vexNum; ++i)
    {
        // weight == 0 indicate in U set, have linked
        if (edge[i].weight != 0 && min > edge[i].weight)
        {
            min   = edge[i].weight;
            index = i;
        }
    }
    return index;
}

void
prim (Graph *G, int index)
{
    int min;
    Edge *edge = initEdge (G, index);

    for (int i = 0; i < G->vexNum - 1; ++i)
    {
        min = getMinEdge (edge, G);
        std::printf ("v%c --> v%c, weight = %d\n",
                     edge[min].vex, G->vexs[min], edge[min].weight);
        edge[min].weight = 0;

        // update edge's content, save memory
        for (int j = 0; j < G->vexNum; ++j)
        {
            if (edge[j].weight > G->edges[min][j])
            {
                edge[j].weight = G->edges[min][j];
                edge[j].vex    = G->vexs[min];
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
    for (int i = 0; i < G->vexNum; i++)
        visited[i] = 0;

    DFS (G, visited, 0);
    std::cout << std::endl;

    prim (G, 0);

    return 0;
}
