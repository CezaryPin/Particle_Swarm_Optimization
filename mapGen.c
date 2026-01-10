#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


double **generate_map(int w,int h,double strenght);
double pythagoras(int a,int b);
void print_map(double **map,int h, int w);
void free_map(double **map, int h);
void map_to_file(double **map, int h, int w,char *source);


//It generates a map of the signal with the assumption that there is no difference in terrain
double **generate_map(int w,int h,double strenght){   //height, width,  strenght [0,1) 
    if(strenght>=1 && strenght<0){
        return NULL;
    }
    srand(time(NULL));
    int pos_h=rand()%h;
    int pos_w=rand()%w;
    double signal=100.0;
    double **map=calloc(h,sizeof(double*));
    for(int i=0;i<h;i++){
        map[i]=calloc(w,sizeof(double));
        for(int j=0;j<w;j++){
            double dis=pythagoras(pos_h-i,pos_w-j);
            double signal_r=signal*pow(strenght,dis);
            if(signal_r<0.01)
                map[i][j]=0;
            else
                map[i][j]=signal_r;
        }
    }
    return map;
}

double pythagoras(int a,int b){
    return sqrt(a*a+b*b);
}

void print_map(double **map,int w,int h){
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            printf("%f ",map[i][j]);
        }
        printf("\n");
    }
}

void free_map(double **map, int h){
    for(int i=0;i<h;i++){
        free(map[i]);
    }
    free(map);
}

void map_to_file(double **map,int w,int h,char *source)
{
    FILE *fptr = fopen(source,"w");
    fprintf(fptr,"%d %d\n",w,h);
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if(j!=w-1)
                fprintf(fptr,"%f ",map[i][j]);
            else
                fprintf(fptr,"%f\n",map[i][j]);
        }
    }
    fclose(fptr);
}