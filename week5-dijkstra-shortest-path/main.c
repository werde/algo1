#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>

#include "heap.h"

#define TEST 0
#define TEST_INPUT_FILE "test.txt"
#define INPUT_FILE "dijkstraData.txt"

typedef struct
{
    int s;
    int e;
    int ln;
} Edge;

typedef struct
{
    Edge* edges;
    int sz;
} Edges;

typedef struct
{
    Edges** nodes;
    int n;
    int m;
} Graph;

typedef struct
{
    Edge *edges;
    int sz;
} CrosEdges;

void readInput(Graph *g);
void dijkstraSP(Graph *g);
void addNode();
Edge* pickMinEdge(int *A, CrosEdges *ce);
void fixCrossEdges(CrosEdges *ce, char *visited);
void printEdge(Edge *edge);

int main()
{
    srand(time(NULL));

    Graph g;
    g.n = 0;
    g.m = 0;
    readInput(&g);
    printf("[!] Number of vertices - %d\n", g.n);
    printf("[!] Number of edges    - %d\n", g.m);

    dijkstraSP(&g);

    return 0;
}

void readInput(Graph* g)
{
    FILE *f;
    int i, j;
#if TEST
    f = fopen(TEST_INPUT_FILE, "r");
#else
    f = fopen(INPUT_FILE, "r");
#endif // TEST

    char buffer[200000];
    while (fgets(buffer, sizeof(buffer), f))
    {
        //printf("%s\n", buffer);
        g->n++;
    }
    rewind(f);

    g->nodes = malloc(sizeof(Edges*)*g->n);

    while (fgets(buffer, sizeof(buffer), f))
    {
        char *start;
        int node, n, ln, chRead;

        start = buffer;
        sscanf(buffer, "%d%n", &node, &chRead);
        start += chRead;

        g->nodes[node] = malloc(sizeof(Edges));
        g->nodes[node]->edges = malloc(sizeof(Edge)*120);
        g->nodes[node]->sz = 0;

        while (sscanf(start, "%d,%d%n", &n, &ln, &chRead) > 0)
        {
            //printf ("edge %d-%d of length %d\n", node, n , ln);
            start += chRead;
            g->m++;

            Edge* tempE;
            int edgeIndex = g->nodes[node]->sz;
            tempE = g->nodes[node]->edges + edgeIndex;

            tempE->s = node;
            tempE->e = n;
            tempE->ln = ln;
            g->nodes[node]->sz++;
        }
    }

/*
    for (i = 1; i <= g->n; i++)
    {
        printf("#%d %d:\n", i, g->nodes[i].edges[0].s);
        for (j = 0; j < g->nodes[i].sz; j++)
        {
            Edge* tempE;
            tempE = g->nodes[i].edges + j;
            printf("\t %d %d\n", tempE->e, tempE->ln);
        }
    }
*/
}

void dijkstraSP(Graph *g)
{
    int i;
    int A[g->n + 1];
    char visited[g->n+ 1];
    for (i = 0; i <= g->n; i++)
    {
        A[i] = 0;
        visited[i] = 0;
    }

    CrosEdges ce;
    ce.edges = malloc(sizeof(Edge)*g->m);
    ce.sz = 0;

    Edge *tempEdge;
    tempEdge = malloc(sizeof(Edge));
    tempEdge->s = 1;
    tempEdge->e = 1;
    tempEdge->ln = 0;

    addNode(g, visited, 1, A, tempEdge, &ce);

    for (i = 0; i < g->n - 1; i++)
    {
        Edge *minEdge;
        minEdge = pickMinEdge(A, &ce);
        printEdge(minEdge);
        addNode(g, visited, minEdge->e, A, minEdge, &ce);
    }

    for (i = 0; i < ce.sz; i++)
    {
        printf("#%d %d %d %d \n", i, ce.edges[i].s, ce.edges[i].e, ce.edges[i].ln);
    }

    for (i = 0; i <= g->n; i++)
    {
        printf("#%d %d %d %d \n", i, A[i], visited[i]);
    }

    printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", A[7],A[37],A[59],A[82],A[99],A[115],A[133],A[165],A[188],A[197]);
};

void addNode(Graph *g, char *visited, int index, int *A, Edge* edge, CrosEdges *ce)
{
    int i;

    visited[index] = 1;

    A[index] = A[edge->s] + edge->ln;

    Edges *edges;
    edges = g->nodes[index];

    printf("%d %d \n", index, edges->sz);

    for (i = 0; i < edges->sz; i++)
    {
        if (visited[edges->edges[i].e] == 0)
        {
            memcpy(ce->edges + ce->sz, edges->edges + i, sizeof(Edge));
            (ce->sz)++;
            //printf("s %d %d \n", edge->s, ce->sz);
        }
    }
    fixCrossEdges(ce, visited);
};

Edge* pickMinEdge(int *A, CrosEdges *ce)
{
    int i;
    Edge *minEdge;
    minEdge = ce->edges;
    for (i = 0; i < ce->sz; i++)
    {
        if (minEdge->ln + A[minEdge->s]> ce->edges[i].ln + A[ce->edges[i].s])
        {
            minEdge = ce->edges + i;
        }
    }

    return minEdge;
};

void fixCrossEdges(CrosEdges *ce, char *visited)
{
    int i;

    for (i = 0; i < ce->sz; i++)
    {
        if (visited[ce->edges[i].e] > 0)
        {
            memcpy(ce->edges + i, ce->edges + i + 1, sizeof(Edge)*(ce->sz - i -1));
            (ce->sz)--;
            i--;
        }
    }
}

void printEdge(Edge *edge)
{
    printf("Edge : %d %d %d\n", edge->s, edge->e, edge->ln);
};
