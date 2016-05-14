#include <stdio.h>
#include <stdlib.h>

struct Edge
{
    long long int weight;
    int src, dest, tag;
};

struct Graph
{
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;
 
    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );
 
    return graph;
}

struct subset
{
    int parent;
    int rank;
};

int find(struct subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}

void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
 
int longcomp(const void* elem1, const void* elem2){                                 
    if(*(const long int*)elem1 > *(const long int*)elem2)
        return -1;
    return *(const long int*)elem1 < *(const long int*)elem2;
}

void KruskalMST(struct Graph* graph)
{
    int V = graph->V;
    int v;
    int e = 0; 
    int i = 0; 
    qsort(graph->edge, graph->E, sizeof(*graph->edge), longcomp);
    struct subset *subsets =
        (struct subset*) malloc( V * sizeof(struct subset) );
 
    for (v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    for (i=0; i<graph->E; i++)
    {
        int x = find(subsets, graph->edge[i].src);
        int y = find(subsets, graph->edge[i].dest);
 
        if (x != y)
        {
            graph->edge[i].tag=1;
            Union(subsets, x, y);
        }
        else
            graph->edge[i].tag=0;
    }
    return;
}
 
int main()
{
    int E,V,K,i;
    int found=0;

    scanf("%d %d %d\n", &V, &E, &K);

    struct Graph* graph = createGraph(V, E);
    
    for (i=0; i<E; i++){
        scanf("%d %d %lld\n", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
        graph->edge[i].src--; graph->edge[i].dest--;
    }
    
    KruskalMST(graph);
    
    for (i=0; i<E; i++){
        if(graph->edge[i].tag==1)
            found++;
    }
    if (found <= K) printf("infinity\n");
    else{
        K++;
        for (i=E-1; i>=0; i--){
           if(graph->edge[i].tag==1){
               K--;
               
           }
           if (K==0){
                         printf("%lld\n", graph->edge[i].weight);
                         break;
           }
        }
    }
    return 0;
}
