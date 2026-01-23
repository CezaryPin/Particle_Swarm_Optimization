#include <time.h>
#include <stdlib.h>
#include <stdio.h>


void init_random(){
    srand(time(NULL));
}

//int from [min,max] max included
int rand_in_range(int min,int max){
    return rand()%(max-min+1)+min;
}

//double from[0,1)
double rand_double(){
    double a=rand();
    double b=rand();
    
    while(a==b)
        b=rand();
    if(a<b)
        return a/b;
    else if(a>b)
        return b/a;
    else
        return 0;
}
