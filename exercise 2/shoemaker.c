#include <stdio.h>
#include <stdlib.h>
	
typedef struct{                                                                         
        long long int a;
        int A;
}das;

typedef struct{
        long long int b;
        int B;
}dbs;	

typedef struct memo{
        long long int x;
        long long int y;
        long long int sold;
        struct memo * next;
}memo_t;

int L,R;

long long int max(long long a, long long b){
        if (a>b)
            return a;
        else
            return b;
}

long long calc(int i, int j, long long int x, long long int y, memo_t ***c, das *da, dbs *db){
     long long int found;
     if ((i>=L) || (j>=R)) return 0;
     memo_t *search = c[i][j];
     found=-1;
     
     while (search!=NULL){
           if ((search->x==x) && (search->y==y)){
                      found=search->sold;
           }
           search=search->next;
     }
     
     if (found == -1){
           if ((da[i].A == db[j].B) && (x>y)){
                found=y+calc(i, j+1, x-y, db[j+1].b, c, da, db);
           }
           else if ((da[i].A==db[j].B) && (x<y)){
                found=x+calc(i+1, j, da[i+1].a, y-x, c, da, db);
           }
           else if ((da[i].A==db[j].B) && (x==y)){
                found=x+calc(i+1, j+1, da[i+1].a, db[j+1].b, c, da, db);
           }
           else if (da[i].A != db[j].B){
                found=max(calc(i+1, j, da[i+1].a, y, c, da, db), calc(i, j+1, x, db[j+1].b, c, da, db));
           }
           memo_t * neo = (memo_t *) malloc(sizeof(memo_t));
           neo->x=x; neo->y=y; neo->sold=found; neo->next=c[i][j]; c[i][j]=neo;
     }
     
     return found;
}       

int main(){
    int i, j;
    
    scanf("%d %d", &L, &R);
    
    das *da = malloc(sizeof(das) * (L));
    dbs *db = malloc(sizeof(dbs) * (R));
    
    for (i = 0; i < L; i++){
             scanf("%lld %d", &da[i].a, &da[i].A);
    }
    for (j = 0; j < R; j++){
             scanf("%lld %d", &db[j].b, &db[j].B);
    }
    
    memo_t ***c = malloc(L * sizeof(memo_t **));
    for (i=0; i<L; i++){
            c[i] = malloc(R * sizeof(memo_t *));
            for (j=0; j<R; j++){
                c[i][j]=NULL;
            }
    }
    
    printf("%lld\n", calc(0, 0, da[0].a, db[0].b, c, da, db)); 
                                                                 
    free(da);
    free(db);
    free(c);                                              
    return 0;
}
