#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
typedef struct
{
        int32_t h;
        int32_t n;
        int32_t d;
        int32_t l;
        int32_t i;
}planets;

typedef struct
{
        int32_t left;
        int32_t right;
}node;


int32_t max(int32_t a, int32_t b){
        if (a > b)
                return a;
        else
                return b;
}
 

node *read_countries(planets *p){
        int32_t i, parent;
        node *t;
 
        p->n = readLong();
 
        t = malloc(sizeof(node) * p->n);
 
        for (i = 0; i < p->n; i++){
                t[i].left = -1;
                t[i].right = -1;
        }
 
        if (p->n == 1)
                parent = readLong();
 
        for (i = 1; i < p->n; i++){
                parent = readLong();
                parent--;
                if (t[parent].left == -1)
                        t[parent].left = i;
                else if(t[parent].right == -1)
                        t[parent].right = i;
        }
        return t;
}
 
int32_t find_height(node* t, int32_t i)
{
        if (i == -1)
                return 0;
        return max(find_height(t, t[i].left), find_height(t, t[i].right)) + 1;
}
 
/* http://www.geeksforgeeks.org/diameter-of-a-binary-node/ */
int32_t find_diameter(node *t, int32_t i, int32_t *height)
{
        int32_t lh = 0, rh = 0;
        int32_t ldiameter = 0, rdiameter = 0;
 
        if(i == -1){
                *height = 0;
                return 0;
        }
 
        ldiameter = find_diameter(t, t[i].left, &lh);
        rdiameter = find_diameter(t, t[i].right, &rh);

        *height = max(lh, rh) + 1;
 
        return max(lh + rh + 1, max(ldiameter, rdiameter));
}

void calc_planet(planets *p)
{
        int32_t gg = 0;
        node *t;
        t = read_countries(p);
        p->h = find_height(t, 0) - 1;
        p->d = find_diameter(t, 0, &gg) - 1;
        free(t);
}

int32_t abs(int32_t a)
{
        if (a > 0)
                return a;
        else
                return -a;
}

int32_t dist(int32_t a, int32_t b, int32_t c)
{
        int32_t temp;
        temp = abs(a - b);
        if (c-temp > temp)
                return c - temp;
        else
                return temp;
}

int32_t right(int32_t a, int32_t b, int32_t c){
        int32_t temp;
        temp = a - b;
        if (temp > 0)
                return temp;
        else
                return c + temp;
}
 
int32_t travel(planets *p, int32_t k){
        int32_t i, temp, max;


        for (i = 1; i < k; i++){
                temp = right(i, 0, k) + p[i].h;
                if (temp > p[0].l){
                        p[0].l = temp;
                        p[0].i = i;
                }
        }
 		
        for (i = 1; i < k; i++){
                temp = right(i-1, i, k) + p[i-1].h + i;
                if (i == p[i-1].i){
                        p[i].l = temp;
                        p[i].i = i-1;
                        continue;
                }
 
                if (temp > p[i-1].l){
                        p[i].l = temp;
                        p[i].i = i - 1;
                }
                else{
                        p[i].l = p[i-1].l;
                        p[i].i = p[i-1].i;
                }
        }
 		
        max = -1;
        for (i = 0; i < k; i++){
                temp = p[i].h + dist(i, p[i].i, k) + p[(p[i].i)].h;
                if (p[i].d > temp){
                        temp = p[i].d;
                }
                if (temp > max){
                        max = temp;
                }
        }
        return max;
}

int main(){
        int32_t i, k;
        k = readLong();
        planets *p = malloc(sizeof(planets) * k);

        for (i = 0; i < k; i++){
                p[i].l = -1;
                p[i].i = -1;
                calc_planet(p + i);
        }

        printf("%" PRId32 "\n", travel(p, k));

        free(p);
        return 0;
}