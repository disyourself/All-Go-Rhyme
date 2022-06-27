
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

void
floyd (Graph *G)
{
    int d[G->vexNum][G->vexNum];
    int p[G->vexNum][G->vexNum];
    for (int i = 0; i < G->vexNum; ++i)
        for (int j = 0; j < G->vexNum; ++j)
        {
            d[i][j] = G->edges[i][j];
            if (G->edges[i][j] > 0 && G->edges[i][j] != MAX)
                p[i][j] = i;
            else
                p[i][j] = -1;
        }

    // the 3 fors of floyd
    for (int i = 0; i < G->vexNum; ++i)
        for (int j = 0; j < G->vexNum; ++j)
            for (int k = 0; k < G->vexNum; ++k)
            {
                if (d[j][i] + d[i][k] < d[j][k])
                {
                    d[j][k] = d[j][i] + d[i][k];
                    p[j][k] = p[i][k];
                }
            }

    for (auto &i : d)
    {
        for (auto &j : i)
            printf ("%d\t", j);
        printf ("\n");
    }
    printf ("\n");
    for (auto &i : p)
    {
        for (auto &j : i)
            printf ("%d\t", j);
        printf ("\n");
    }
}

int
main (int argc, char **argv)
{
    Graph *G       = initGraph (4);
    int arcs[4][4] = {
        { 0, 1, MAX, 3 },
        { 1, 0, 2, 2 },
        { MAX, 2, 0, 8 },
        { 3, 2, 8, 0 }
    };
    creatGraph (G, "1234567", (int *)arcs);

    int *visited = new int[G->vexNum];
    for (int i = 0; i < G->vexNum; ++i)
        visited[i] = 0;
    DFS (G, visited, 0);
    printf ("\n\n");

    floyd (G);

    return 0;
}