#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define INPUT_FILE "kargerMinCut.txt"
#define INPUT_TEST_FILE "test.txt"
#define TEST 1

typedef struct
{
    char f;
    char s;
} Edge;

typedef struct
{
    Edge *edges;
    int n;
    int m;
} Graph;

Graph g;
Graph original;
Edge *edges;

int cut();
int merge();
void deleteSelfLoops();
int readInput(FILE *f);
void addEdge(Edge *e);

int main()
{
    int i = 0;
    srand(time(NULL));

    FILE *f;
    g.n = 0;
    g.m = 0;
    original.n = 0;
    original.m = 0;
#if TEST
    f = fopen(INPUT_TEST_FILE, "r");
#else
    f = fopen(INPUT_FILE, "r");
#endif

    readInput(f);
    printf("[!] Number of vertices - %d\n", original.n);
    printf("[!] Number of edges - %d\n", original.m);

    int loops = original.n*original.n;
    int minCut = 99;

    for (i = 0; i < loops; i++)
    {
        int c = 13;
        c = cut();
        if (c < minCut)
            minCut = c;
    }
    printf("[!] Minimal cut - %d \n", minCut);

    return 0;
}

int cut()
{
    g.n = original.n;
    g.m = original.m;
    g.edges = edges;
    memcpy(edges, original.edges, original.m*sizeof(Edge));

    while (g.n > 2)
    {
        merge();
    }

    return g.m;
}

int merge()
{
    int random, i;
    i = 0;
    random = (int) (g.m - 1)*((double)rand()/(double)RAND_MAX);

    char first = edges[random].f;
    char second = edges[random].s;

    for (i = 0; i < g.m; i++)
    {
        if (edges[i].f == second)
            edges[i].f = first;
        if (edges[i].s == second)
            edges[i].s = first;
    }

    deleteSelfLoops();
    g.n--;

    return random;
};

void deleteSelfLoops()
{
    Edge *e;
    e = edges;

    while ( e != (edges + g.m))
    {
        if (e->f == e->s)
        {
            memcpy(e, e + 1, (g.m - (e - edges) - 1)*sizeof(Edge));
            g.m--;
        } else
        {
            e++;
        }
    }
}

int readInput(FILE *f)
{
    int size = 0;
    char temp[2000];

    while (fgets(temp, sizeof(temp), f) != NULL)
    {
        size++;
    }
    rewind(f);

    original.edges = malloc(sizeof(Edge)*size*(size-1)/2);
    original.n = size;
    edges = malloc(sizeof(Edge)*size*(size-1)/2);
    g.edges = edges;

    int charactersRead;

    while (fgets(temp, sizeof(temp), f) != NULL)
    {
        Edge tempEdge;
        char *start;
        start = temp;

        int t;
        while (sscanf(start, "%d%n", &t, &charactersRead) > 0)
        {
            if (start == temp)
            {
                tempEdge.f = t;
            } else
            {
                tempEdge.s = t;
                if (tempEdge.s > tempEdge.f)
                {
                    addEdge(&tempEdge);
                }
            }
            start += charactersRead;
        }
    }

    return size;
}

void addEdge(Edge *e)
{
    original.edges[original.m].f = e->f;
    original.edges[original.m].s = e->s;
    original.m += 1;
}
