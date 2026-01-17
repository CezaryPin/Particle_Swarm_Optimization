#include "./Perlin_Noise_Generator/map_gen.h"
#include "./Perlin_Noise_Generator/structs.h"
#include <stdlib.h>
#include <stdio.h>
#include "new_map_gen.h"

int main(int argc,char *argv[]){ //wymyśleć jak to odpalić
    int w=5;
    int h=5;
    int sampling=10;
    double max_val=100; 
    
    create_perlin_file(w,h,sampling,max_val);
    for(int i=2;i<argc;i++){
        if(strcmp(argv[i],"-w")==0){
            w=atoi(argv[i+1]);
            i++;
        }
        else if(strcmp(argv[i],"-h")==0){
            h=atoi(argv[i+1]);
            i++;
        }
        else if(strcmp(argv[i],"-s")==0){
            sampling=atoi(argv[i+1]);
            i++;
        }
        else if(strcmp(argv[i],"-n")==0){
            max_val=atof(argv[i+1]);
            i++;
        }
    }
    return 0;
}

void create_perlin_file(int w,int h, int sampling,double max_val){  //result of it will be grid w*sampling x h*sampling with values in [0,max_val] range 

    map *perlin =perlin_noise_map(w, h, sampling);
    create_image(perlin);
    FILE *fptr = fopen("perlin_map.txt","w+");

    fprintf(fptr,"%d %d\n",perlin->w,perlin->h);
    for(int i=0;i<perlin->h;i++)
        for(int j=0;j<perlin->w;j++)
        {
            double x=perlin->vector_map[j][i]*max_val;
            if(j!=perlin->w-1)
                fprintf(fptr,"%.2f ",x);
            else
                fprintf(fptr,"%.2f\n",x);
        }
    fclose(fptr);
}
