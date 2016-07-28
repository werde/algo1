#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define TEST_FILE "test.txt"
#define INPUT_FILE "SCC.txt"
#define TEST 0
#define DEF_OUT_SIZE 25
#define ADD_OUT_FACTOR 2 /* Double memory allocated for out node array*/

typedef struct
{
    int index;
    int *out;
    int out_size;
} Node;

typedef struct
{
    Node* nodes;
    int n;
    int m;
} Graph;

int readInput(Graph* g, Graph* rg);
void DFSLoop(Graph* g, int* time, int* timetable);
void DFS5Loop(Graph* g, int* time, int* timetable);
int DFS(Graph* g, int i, char* explored, int* time, int* timetable);
void addMemory(int** array, int size, int factor);
void printGraph(Graph* g);

int main()
{
    int i, time;
    int *timetable;
    Graph g;
    Graph rg; //reverse graph

    readInput(&g, &rg);
    printf("[!] Number of nodes - %d, number of edges - %d.\n", g.n, g.m);
    //printGraph(&g);
    //printGraph(&rg);

    time = g.n;

    timetable = malloc(sizeof(int)*(g.n+1));
    for (i = 0; i <= g.n; i++)
    {
        timetable[i] = 0;
    }

    DFSLoop(&rg, &time, timetable);
    printf("Starting DFS5Loop......\n");
    DFS5Loop(&g, &time, timetable);

    free(timetable);

    return 0;
}

void DFSLoop(Graph* g, int* time, int* timetable)
{
    int i;

    /* Explored nodes init*/
    char* explored;
    explored = malloc(sizeof(char)*((g->n)+1));
    for (i = 0; i <= g->n; i++)
        explored[i] = 0;

    for (i = 1; i <= g->n; i++)
    {
        if (explored[i] == 0)
            DFS(g, i, explored, time, timetable);
    }

    free(explored);
};

void DFS5Loop(Graph* g, int* time, int* timetable)
{
    int i, j;
    int biggestFiveSCC[5] = {0};

    /* Explored nodes init*/
    char* explored;
    explored = malloc(sizeof(char)*((g->n)+1));
    for (i = 0; i <= g->n; i++)
        explored[i] = 0;

    // Temp variables for second DFS loop
    int tempTime = 0;
    int* tempTimetable;
    tempTimetable = malloc(sizeof(int)*(g->n+1));
    for (j = 0; j <= g->n; j++)
        tempTimetable[j] = 0;

    for (j = 1; j <= g->n; j++)
    {
        int trv = 0;

        if (explored[timetable[j]] == 0)
            trv = DFS(g, timetable[j], explored, &tempTime, tempTimetable);

        /* Populate 5 biggest SCC array*/
        if (trv > 0)
        {
            for (i = 0; i < 5; i++)
            {
                if (trv > biggestFiveSCC[i])
                {
                    if (i == 4)
                    {
                        biggestFiveSCC[i] = trv;
                        break;
                    }
                    int* buffer;
                    int bufferSize = 5 - i - 1;

                    buffer = malloc(sizeof(int)*bufferSize);
                    memcpy(buffer, biggestFiveSCC + i, sizeof(int)*bufferSize);
                    biggestFiveSCC[i] = trv;

                    memcpy(biggestFiveSCC + i + 1, buffer, sizeof(int)*(bufferSize));
                    free(buffer);
                    break;
                }
            }
        }
    }

    printf("Five biggest SCC:\n");
    for (i = 0; i < 5; i++)
    {
        printf("\t#%d\t%d\n", i, biggestFiveSCC[i]);
    }

    free(explored);
    free(tempTimetable);
};

int DFS(Graph* g, int i, char* explored, int* time, int* timetable)
{
    if (explored[i] != 0)
        return 0;

    int traversed = 1;
    int j;

    explored[i] += 1;

    for (j = 0; j < g->nodes[i].out_size; j++)
    {
        if (explored[g->nodes[i].out[j]] == 0)
            traversed += DFS(g, g->nodes[i].out[j], explored, time, timetable);
    }

    /* Time */
    if ((*time <= g->n) && (*time >= 1))
    {
        timetable[*time] = i;
        (*time) -= 1;
    }

    return traversed;
}

int readInput(Graph* g, Graph* rg)
{
    int i = 0;
    FILE* f;
    g->n = 0;
    g->m = 0;
    rg->n = 0;
    rg->m = 0;
    int maxNode = 0;
    char buf[200];
#if TEST
    f = fopen("test.txt", "r");
#else
    f = fopen(INPUT_FILE, "r");
#endif

    while (fgets(buf, sizeof(buf), f))
    {
        int i1, i2;
        sscanf(buf, "%d %d", &i1, &i2);

        if (i1 > maxNode)
            maxNode = i1;
        if (i2 > maxNode)
            maxNode = i2;
        (g->m)++;
    }
    g->n = maxNode;
    rg->n = maxNode;
    rg->m = g->m;
    rewind(f);

    g->nodes = malloc(sizeof(Node)*(g->n + 1)); //for convenience because there isn't node 0 in input
    rg->nodes = malloc(sizeof(Node)*(g->n + 1));
    for (i = 1; i <= g->n; i++)
    {
        g->nodes[i].index = i;
        g->nodes[i].out_size = 0;
        rg->nodes[i].index = i;
        rg->nodes[i].out_size = 0;
    }

    while (fgets(buf, sizeof(buf), f))
    {
        int i1, i2;
        sscanf(buf, "%d %d", &i1, &i2);

        Node *node, *rnode;
        node = &(g->nodes[i1]);
        rnode = &(rg->nodes[i2]);

        /* Populate graph */
        if (node->out_size > 0)
        {
            node->out[node->out_size] = i2;
            node->out_size++;

            /* Add memory if necessary */
            if (node->out_size % DEF_OUT_SIZE == 0)
            {
                addMemory(&(node->out), node->out_size, ADD_OUT_FACTOR);
            }
        } else
        {
            node->index = i1;
            node->out = malloc(sizeof(int)*DEF_OUT_SIZE);
            node->out[node->out_size] = i2;
            node->out_size = 1;
        }

        /* Populate reverse graph */
        if (rnode->out_size > 0)
        {
            rnode->out[rnode->out_size] = i1;
            rnode->out_size++;

            /* Add memory if necessary */
            if (rnode->out_size % DEF_OUT_SIZE == 0)
            {
                addMemory(&(rnode->out), rnode->out_size, ADD_OUT_FACTOR);
            }
        } else
        {
            rnode->index = i2;
            rnode->out = malloc(sizeof(int)*DEF_OUT_SIZE);
            rnode->out[rnode->out_size] = i1;
            rnode->out_size = 1;
        }
    }

    fclose(f);

    return 1;
}

void addMemory(int** array, int size, int factor)
{
    int* temp;
    temp = *array;

    *array = malloc(sizeof(int)*size*factor);
    memcpy(*array, temp, size*sizeof(int));

    free(temp);
}

void printGraph(Graph* g)
{
    printf("Graph:\n");
    int i, t;
    for (i = 1; i <= g->n; i++)
    {
        printf("%d \n", g->nodes[i].index);
        for (t = 0; t < g->nodes[i].out_size; t++)
        {
            printf("\t%d\n", g->nodes[i].out[t]);
        }
    }
}
