#include <stdio.h>
#include <stdlib.h>

typedef struct{                                                                         
        long long int f;
        long long int s;
}ts;


int longcomp(const void* elem1, const void* elem2){                                 
    if(*(const long long int*)elem1 < *(const long long int*)elem2)
        return -1;
    return *(const long long int*)elem1 > *(const long long int*)elem2;
}



long long int n, i, k, y, smin, fmax, right, left, mid;



int main(int argc, char *argv[]){
                                                      
    scanf("%lld %lld", &n, &k);
    
    ts *t = malloc(sizeof(ts) * (n));
    
    for (i = 0; i<n; i++){                                             
             scanf("%lld %lld", &t[i].s, &t[i].f);
    }

    //find minimum Si and maximum Fi
    smin=1000000000; fmax=0;
    for (i=0; i<n; i++){
        if (t[i].s < smin) smin = t[i].s;
        if (t[i].f > fmax) fmax = t[i].f;
    }
    
    //binary search best time
    y=0;
    right=fmax; left=smin; mid=(fmax+smin)/2;
    for (i=0; i<n; i++){
              if (t[i].s <= mid){
                 if (t[i].f >= mid) y = y + mid - t[i].s + 1;
                 else y = y + t[i].f - t[i].s + 1; 
              }
          }
          
    while ((right-left)>1 || y<k) {
          if (y < k){
                left=mid; mid=(right+left)/2;
                if (left==mid) mid++;
          }
          else {
               right=mid; mid=(right+left)/2;
               if (right==mid) mid--;
          }
          y=0;
          for (i=0; i<n; i++){
              if (t[i].s <= mid){
                 if (t[i].f >= mid) y = y + mid - t[i].s + 1;
                 else y = y + t[i].f - t[i].s + 1; 
              }
          }
    }
    
    printf("%lld\n", mid);
                                         
    free(t);                                               
    return 0;
}
