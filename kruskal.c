#include <stdio.h>
#include <stdlib.h>

#define MAX 30

typedef struct edge
{
    int u, v, w;
} edge;

typedef struct edgelist
{
    edge data[MAX];
    int n;
} edgelist;

edgelist elist;

int parent[MAX];

int find(int i)
{
    while (parent[i])
        i = parent[i];
    return i;
}

int uni(int i, int j)
{
    if (i != j)
    {
        parent[j] = i;
        return 1;
    }
    return 0;
}

void sort()
{
    int i, j;
    edge temp;
    for (i = 1; i < elist.n; i++)
        for (j = 0; j < elist.n - 1; j++)
            if (elist.data[j].w > elist.data[j + 1].w)
            {
                temp = elist.data[j];
                elist.data[j] = elist.data[j + 1];
                elist.data[j + 1] = temp;
            }
}

void kruskal()
{
    int i, j, sum = 0;
    int a, b;
    for (i = 0; i < elist.n; i++)
        parent[i] = 0;
    sort();
    printf("\nSelected Edges:\n");
    for (i = 0; i < elist.n; i++)
    {
        a = find(elist.data[i].u);
        b = find(elist.data[i].v);
        if (uni(a, b))
        {
            printf("(%d, %d) -> %d\n", elist.data[i].u, elist.data[i].v, elist.data[i].w);
            sum += elist.data[i].w;
        }
    }
    printf("\nMinimum Cost: %d\n", sum);
}

int main()
{
    int n, e, i, j;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the number of edges: ");
    scanf("%d", &e);
    elist.n = e;
    printf("Enter the edges [source destination weight]:\n");
    for (i = 0; i < e; i++)
        scanf("%d %d %d", &elist.data[i].u, &elist.data[i].v, &elist.data[i].w);
    kruskal();
    return 0;
}