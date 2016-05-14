/* modified original code from http://www.geeksforgeeks.org/greedy-algorithms-set-7-dijkstras-algorithm-for-adjacency-list-representation/ */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>
#define BSIZE 1<<15


char buffer[BSIZE];
long bpos = 0L, bsize = 0L;

long readLong() 
{
    long d = 0L, x = 0L;
    char c;

    while (1)  {
        if (bpos >= bsize) {
            bpos = 0;
            if (feof(stdin)) return x;
            bsize = fread(buffer, 1, BSIZE, stdin);
        }
        c = buffer[bpos++];
        if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
        else if (d == 1) return x;
    }
    return -1;
}

// Structure to represent a min heap node
struct MinHeapNode
{
    int64_t vi;         //sintetagmenes ston c[][]
    int64_t vj;         //sintetagmenes ston c[][]
    int64_t dist;       //trexousa apostash
    int64_t direction;  //kateythinsi apo tin opia eftasa sto node
};
 
// Structure to represent a min heap
struct MinHeap
{
    int64_t size;      // Number of heap nodes present currently
    int64_t capacity;  // Capacity of min heap
    int64_t **pos;     // This is needed for decreaseKey()
    struct MinHeapNode **array; //pinakas [] me nodes
};
 
// A utility function to create a new Min Heap Node
struct MinHeapNode* newMinHeapNode(int64_t i, int64_t j, long dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->vi = i;
    minHeapNode->vj = j;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
// A utility function to create a Min Heap
struct MinHeap* createMinHeap(int64_t l, int64_t w)
{
    int64_t i;
    int64_t capacity = l*w;
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = malloc(sizeof *minHeap->pos * l);
    if (minHeap->pos){
        for (i = 0; i < l; i++){
            minHeap->pos[i] = malloc(sizeof *minHeap->pos[i] * w);
        }
    }
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int64_t idx)
{
    int64_t smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        struct MinHeapNode *smallestNode = minHeap->array[smallest];
        struct MinHeapNode *idxNode = minHeap->array[idx];
 
        // Swap positions
        minHeap->pos[smallestNode->vi][smallestNode->vj] = idx;
        minHeap->pos[idxNode->vi][idxNode->vj] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}

// A utility function to check if the given minHeap is empty or not
int64_t isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}

// Standard function to extract minimum (top) node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap)){
        return NULL;
    }
 
    // Store the root node
    struct MinHeapNode* root = minHeap->array[0];
 
    // Replace root node with last node
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    // Update position of last node
    minHeap->pos[root->vi][root->vj] = minHeap->size-1;
    minHeap->pos[lastNode->vi][lastNode->vj] = 0;
 
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}


// Function to decrease dist value of a given vertex v. This function
// uses pos[][] of min heap to get the current index of node in min heap
void decreaseKey(struct MinHeap* minHeap, int64_t grammh, int64_t sthlh, long dist)
{
    // Get the index of (grammh, sthlh) in  heap array
    int64_t i = minHeap->pos[grammh][sthlh];
 
    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;
 
    // Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->vi][minHeap->array[i]->vj] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->vi][minHeap->array[(i-1)/2]->vj] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
 
        // move to parent index
        i = (i - 1) / 2;
    }
}

int isInMinHeap(struct MinHeap *minHeap, int64_t i, int64_t j)
{
   if (minHeap->pos[i][j] < minHeap->size)
     return 1;
   return 0;
}



int main()
{

    int64_t l, w, i, j, t, proto, grammh, sthlh;
    
    l = readLong();
    w = readLong();
    struct MinHeap* minHeap = createMinHeap(l, w);
    int64_t **c = malloc(sizeof *c * l);
    if (c)
    {
        for (i = 0; i < l; i++)
        {
            c[i] = malloc(sizeof *c[i] * w);
        }
    }
    proto =1;
    for (i = 0; i < l; i++){
        for (j = 0; j < w; j++){
            c[i][j] = readLong();
            if (c[i][j]==0 && proto ==1){
                proto = 0;
                minHeap->array[0] = newMinHeapNode(i, j, 0);
                minHeap->pos[i][j] = 0;
            }
        }
    }
    t=1;
    proto = 1;
    for (i = 0; i < l; i++){
        for (j = 0; j < w; j++){
            if (c[i][j]==0 && proto ==1){
                //printf("zero(%d, %d)", i, j);
                proto = 0;
                continue;
            }
            minHeap->array[t] = newMinHeapNode(i, j, LONG_MAX);
            minHeap->pos[i][j] = t;
            t++;
        }
    }
    minHeap->size = l*w;
    
    
    proto = 1;
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with minimum distance value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        grammh = minHeapNode->vi; // Store the extracted vertex number
        sthlh = minHeapNode->vj;
        if (c[grammh][sthlh]==0 && proto ==0){
                printf("%" PRId64 "\n", minHeapNode->dist);
                return 0;
        }
        proto = 0;
        
        //printf("poping dist=%d. Cost (%d,%d) = %d\n", minHeapNode->dist, grammh, sthlh, c[grammh][sthlh]);
        // Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their distance values
        if (minHeapNode->direction == 1 || c[grammh][sthlh] == 0){
            for (i = sthlh+1; i < w; i++){
                if (c[grammh][i] == 4000)
                    break;
                if (isInMinHeap(minHeap, grammh, i) && (minHeapNode->dist + c[grammh][i] < minHeap->array[minHeap->pos[grammh][i]]->dist)){
                    //printf("%d\n", minHeap->array[0]->dist);
                    //printf("updating %d, (%d,%d) from %d to %d\n", minHeap->pos[grammh][i], grammh, i, minHeap->array[minHeap->pos[grammh][i]]->dist, minHeapNode->dist + c[grammh][i]);
                    minHeap->array[minHeap->pos[grammh][i]]->direction = 0;
                    decreaseKey(minHeap, grammh, i, minHeapNode->dist + c[grammh][i]);
                    //printf("confirming %d, (%d,%d) : %d   direction %d\n", minHeap->pos[grammh][i], grammh, i, minHeap->array[minHeap->pos[grammh][i]]->dist, minHeap->array[minHeap->pos[grammh][i]]->direction);
                }
            }
            for (i = sthlh-1; i >=0; i--){
                if (c[grammh][i] == 4000)
                    break;
                if (isInMinHeap(minHeap, grammh, i) && (minHeapNode->dist + c[grammh][i] < minHeap->array[minHeap->pos[grammh][i]]->dist)){
                    //printf("updating %d, (%d,%d) from %d to %d\n", minHeap->pos[grammh][i], grammh, i, minHeap->array[minHeap->pos[grammh][i]]->dist, minHeapNode->dist + c[grammh][i]);
                    minHeap->array[minHeap->pos[grammh][i]]->direction = 0;
                    decreaseKey(minHeap, grammh, i, minHeapNode->dist + c[grammh][i]);
                    //printf("confirming %d, (%d,%d) : %d   direction %d\n", minHeap->pos[grammh][i], grammh, i, minHeap->array[minHeap->pos[grammh][i]]->dist, minHeap->array[minHeap->pos[grammh][i]]->direction);
                }
            }
        }
        if (minHeapNode->direction == 0 || c[grammh][sthlh] == 0){
            for (i = grammh+1; i < l; i++){
                if (c[i][sthlh] == 4000)
                    break;
                if (isInMinHeap(minHeap, i, sthlh) && (minHeapNode->dist + c[i][sthlh] < minHeap->array[minHeap->pos[i][sthlh]]->dist)){
                    //printf("updating %d, (%d,%d) from %d to %d\n", minHeap->pos[i][sthlh], i, sthlh, minHeap->array[minHeap->pos[i][sthlh]]->dist, minHeapNode->dist + c[i][sthlh]);
                    minHeap->array[minHeap->pos[i][sthlh]]->direction = 1;
                    decreaseKey(minHeap, i, sthlh, minHeapNode->dist + c[i][sthlh]);
                    //printf("confirming %d, (%d,%d) : %d   direction %d\n", minHeap->pos[i][sthlh], i, sthlh, minHeap->array[minHeap->pos[i][sthlh]]->dist, minHeap->array[minHeap->pos[i][sthlh]]->direction);
                }
            }
            for (i = grammh-1; i >= 0; i--){
                if (c[i][sthlh] == 4000)
                    break;
                if (isInMinHeap(minHeap, i, sthlh) && (minHeapNode->dist + c[i][sthlh] < minHeap->array[minHeap->pos[i][sthlh]]->dist)){
                    //printf("updating %d, (%d,%d) from %d to %d\n", minHeap->pos[i][sthlh], i, sthlh, minHeap->array[minHeap->pos[i][sthlh]]->dist, minHeapNode->dist + c[i][sthlh]);
                    minHeap->array[minHeap->pos[i][sthlh]]->direction = 1;
                    decreaseKey(minHeap, i, sthlh, minHeapNode->dist + c[i][sthlh]);
                   // printf("confirming %d, (%d,%d) : %d   direction %d\n", minHeap->pos[i][sthlh], i, sthlh, minHeap->array[minHeap->pos[i][sthlh]]->dist, minHeap->array[minHeap->pos[i][sthlh]]->direction);
                }
            }
        }
        
    }
    
    return 0;
}