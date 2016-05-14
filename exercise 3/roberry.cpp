#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<iostream>
#include <list>
#define NIL -1
using namespace std;

struct Edge
{
    long int weight;
    int src, dest, tag;
};

struct Graphc
{
    int V, E, aparetites, avevees, axristes, gefires;

    struct Edge* edge;
};

struct Graphc* createGraphc(int V, int E)
{
    struct Graphc* Graphc = (struct Graphc*) malloc( sizeof(struct Graphc) );
    Graphc->V = V;
    Graphc->E = E;
    Graphc->aparetites=0;
    Graphc->avevees=0;
    Graphc->axristes=0;
    
    Graphc->edge = (struct Edge*) malloc( Graphc->E * sizeof( struct Edge ) );
 
    return Graphc;
}

class Graph
{
    int V;
    list<int> *adj;
    void bridgeUtil(int v, bool visited[], int disc[], int low[], int parent[], int countchildren[], int isbridge[], struct Graphc* Graphc);
public:
    Graph(int V);
    void addEdge(int v, int w);
    void removeEdge(int v, int w);
    void bridge(struct Graphc* Graphc);
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::removeEdge(int v, int w)
{
    adj[v].pop_back();
    adj[w].pop_back();
}

void Graph::bridgeUtil(int u, bool visited[], int disc[], int low[], int parent[], int countchildren[], int isbridge[], struct Graphc* Graphc)
{

    static int time = 0;
 
    visited[u] = true;
 
    disc[u] = low[u] = ++time;
 
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;
        
        if (parent[v]==-1)
           parent[v]=u;
        if (parent[v]==u)
           countchildren[v]++;
           
        if (!visited[v])
        {
            bridgeUtil(v, visited, disc, low, parent, countchildren, isbridge, Graphc);

            low[u]  = min(low[u], low[v]);
 
            if (low[v] > disc[u]){
              Graphc->gefires++;
              isbridge[v]=1;
            }
        }
        else if (v != parent[u])
            low[u]  = min(low[u], disc[v]);
            
        if ((parent[v]==u) && (countchildren[v]>1) && (isbridge[v]==1)){
           isbridge[v]=0;
           Graphc->gefires--;
        }
    }
}

void Graph::bridge(struct Graphc* Graphc)
{
    bool *visited = new bool[V];
    int *disc = new int[V];
    int *low = new int[V];
    int *parent = new int[V];
    int *countchildren = new int [V];
    int *isbridge = new int [V];

    for (int i = 0; i < V; i++)
    {
        parent[i] = -1;
        visited[i] = false;
        countchildren[i]=0;
        isbridge[i]=0;
    }

    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            bridgeUtil(i, visited, disc, low, parent, countchildren, isbridge, Graphc);
}

long int min(long int a, long int b){
     if (a<b) return a;
     else return b;
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

int myComp(const void* a, const void* b)
{
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight < b1->weight;
}


int longcomp(const void* elem1, const void* elem2){                                 
    if(*(const long int*)elem1 < *(const long int*)elem2)
        return -1;
    return *(const long int*)elem1 > *(const long int*)elem2;
}

void KruskalMST(struct Graphc* Graphc)
{
    int V = Graphc->V; int E = Graphc->E;
    int j = 0; int x, y, t, i;
    int tocheck=0;
    Graphc->aparetites=0; Graphc->avevees=0; Graphc->axristes=0; Graphc->gefires=0;
    
    Graph g1(V);
    
    qsort(Graphc->edge, E, sizeof(*Graphc->edge), longcomp);

    struct subset *subsets = (struct subset*) malloc( V * sizeof(struct subset) );

    for (i = 0; i < V; ++i)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    for (i=0; i<E; i++)
    {
        if (find(subsets, Graphc->edge[i].src) == find(subsets, Graphc->edge[i].dest)){
            Graphc->edge[i].tag = 0;
            Graphc->axristes++;
        }
        else{
             Graphc->edge[i].tag = 1;
             tocheck++;
        }
        if (((i == (E - 1)) || (Graphc->edge[min(i + 1, E - 1)].weight > Graphc->edge[i].weight)) && (tocheck > 0) ){
           for (t=j; t<=i; t++){
               if (Graphc->edge[t].tag==1){
               g1.addEdge(find(subsets, Graphc->edge[t].src), find(subsets, Graphc->edge[t].dest));
               }
           }
        
           g1.bridge(Graphc);
           Graphc->aparetites = Graphc->aparetites + Graphc->gefires;
           Graphc->avevees = Graphc->avevees + tocheck - Graphc->gefires;
          
           for (t=i; t>=j; t--){
               if (Graphc->edge[t].tag==1){
                  g1.removeEdge(find(subsets, Graphc->edge[t].src), find(subsets, Graphc->edge[t].dest));//remove apo grafo
               }
           }
           for (t=i; t>=j; t--){
               if (Graphc->edge[t].tag==1){ 
                  x = find(subsets, Graphc->edge[t].src);
                  y = find(subsets, Graphc->edge[t].dest);
                  if (x != y){
                     Union(subsets, x, y);
                  }
                  else
                      Graphc->edge[t].tag = 0;
               }
           }
           j=i+1;
           tocheck=0;
           Graphc->gefires=0;
        }
    }
    return;
}
 



int main()
{
    int E,V,i;
    scanf("%d %d\n", &V, &E);
    struct Graphc* Graphc = createGraphc(V, E);
    for (i=0; i<E; i++){
        scanf("%d %d %ld\n", &Graphc->edge[i].src, &Graphc->edge[i].dest, &Graphc->edge[i].weight);
        Graphc->edge[i].src--; Graphc->edge[i].dest--;
    }
    
    KruskalMST(Graphc);

    printf("%d\n%d\n%d\n", Graphc->aparetites,  Graphc->axristes, Graphc->avevees);
    return 0;
}
