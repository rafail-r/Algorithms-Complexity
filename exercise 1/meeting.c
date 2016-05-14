#include <stdio.h>
#include <stdlib.h>
	
typedef struct{                                                                         
        long long int x;
        long long int id;
}cxs;

typedef struct{
        long long int y;
        long long int id;
}cys;	

typedef struct{
        long long int x;
        long long int y;
}sums;	


int longcomp(const void* elem1, const void* elem2){                                 
    if(*(const long long int*)elem1 < *(const long long int*)elem2)
        return -1;
    return *(const long long int*)elem1 > *(const long long int*)elem2;
}


long long int main(){                      
    long long int n,dist,i,t1,t2;
    scanf("%lld", &n);                           
    cxs *cx = malloc(sizeof(cxs) * (n));
    cys *cy = malloc(sizeof(cys) * (n));
    sums *sum = malloc(sizeof(sums) * (n));
    for (i = 0; i < n; i++){                                             
             scanf("%lld %lld", &cx[i].x, &cy[i].y);
             cx[i].id=i; cy[i].id=i; sum[i].x=0; sum[i].y=0;
    }
    
    qsort(cx, n, sizeof(*cx), longcomp);
    qsort(cy, n, sizeof(*cy), longcomp);
    //gia x
    t1=0; t2=0;
    for (i=1; i<n; i++){
        t1=i*(cx[i].x-cx[i-1].x);
        t2=t2+t1;
        sum[cx[i].id].x=t2;
    }
    t1=0; t2=0;
    for (i=n-2; i>-1; i--){
        t1=((n-2)-i+1)*(cx[i+1].x-cx[i].x);
        t2=t1+t2;
        sum[cx[i].id].x=t2+sum[cx[i].id].x;
    }

    //gia y
    t1=0; t2=0;
    for (i=1; i<n; i++){
        t1=i*(cy[i].y-cy[i-1].y);
        t2=t2+t1;
        sum[cy[i].id].y=t2;
    }
    t1=0; t2=0;
    for (i=n-2; i>-1; i--){
        t1=((n-2)-i+1)*(cy[i+1].y-cy[i].y);
        t2=t1+t2;
        sum[cy[i].id].y=t2+sum[cy[i].id].y;
    }
    
    //add them all up
    for (i=0; i<n; i++){
        sum[i].x=sum[i].x+sum[i].y;
    }
    dist=1000000000000000;
    //find least
    for (i=0; i<n; i++){
        if (dist>sum[i].x){
           dist=sum[i].x;
        }
    } 
    printf("%lld\n", dist);                                   
    free(cx);
    free(cy);
    free(sum);                                                
    return 0;
}
