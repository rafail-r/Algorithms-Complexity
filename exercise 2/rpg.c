#include <stdio.h>
#include <stdlib.h>
	
typedef struct{                                                                         
        int a;
        int A;
}das;

typedef struct{
        int b;
        int B;
}dbs;	

int L,R,k,l,n,m,i,j;
int max(int a, int b){
    if (a>=b) return a;
    if (a<b) return b;
}

int main(int argc, char *argv[]){
    FILE *file;
    file = fopen(argv[1], "r");
    fscanf(file, "%d %d", &L, &R);
    
    das *da = malloc(sizeof(das) * (L));
    dbs *db = malloc(sizeof(dbs) * (R));
    
    for (i = 0; i < L; i++){
             fscanf(file, "%d %d", &da[i].a, &da[i].A);
    }
    for (i = 0; i < R; i++){
             fscanf(file, "%d %d", &db[i].b, &db[i].B);
    }
    ///////////////
    n=0;
    for (i=0; i<L; i++){
            n=da[i].a+n;
    }
    m=0;
    for (i=0; i<R; i++){
            m=db[i].b+m;
    }
    ////////////
    int * x = malloc(n * sizeof(int));
    int * y = malloc(m * sizeof(int));
    ////////////
    k=0;
    for (i = 0; i < L; i++){
        for (j=0; j<da[i].a; j++){
            x[k]=da[i].A;
            k++;
        }
    }
    l=0;
    for (i = 0; i < R; i++){
        for (j=0; j<db[i].b; j++){
            y[l]=db[i].B;
            l++;
        }
    }
    ////////////
    int **c;
    c = malloc((m+1) * sizeof(int *));
    for (i = 0; i < (m+1); i++)
        c[i] = malloc((n+1) * sizeof(int));
    //////////////   
    for (i = 0; i < m; i++) {
        c[i][0] = 0;
    }
    for (j=0; j < n; j++) {
        c[0][j] = 0;
    }     
    //////////////    

    for (i=1; i<m+1; i++){
        for (j=1; j<n+1; j++){
            if (x[j-1] == y[i-1])
                c[i][j]=c[i-1][j-1]+1;
            else
                c[i][j]=max(c[i][j-1],c[i-1][j]);
        }
    }
    
    printf("LCS=%d\n", c[m][n]); 
    fclose(file);                                                                
    free(da);
    free(db);
    free(c);
    free(x);
    free(y);
    system("pause");                                                
    return 0;
}
