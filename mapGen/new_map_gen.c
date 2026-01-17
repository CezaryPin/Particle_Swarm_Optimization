#include "./Perlin_Noise_Generator/map_gen.h"
#include "./Perlin_Noise_Generator/structs.h"
#include <stdlib.h>
#include <stdio.h>
#include "new_map_gen.h"

int main(){ //wymyśleć jak to odpalić
    create_perlin_file(4,5,10,100);
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
