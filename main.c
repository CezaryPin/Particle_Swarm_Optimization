#include "pso.h"
#include "psoStructs.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{

    char *map_file=argv[0];

    int probe_num=30;
    int iterations=100;
    char config_file="";
    int save_frq=0;
    pso_config *conf=NULL;

    init_random();


    for(int i=1;i<argc;i++){
        if(argv[i]=="-p"){
            probe_num=atoi(argv[i+1]);
            i++;
        }
        else if(argv[i]=="-i"){
            iterations=atoi(argv[i+1]);
            i++;
        }
        else if(argv[i]=="-c"){
            config_file=argv[i+1];
            i++;
            conf=load_config(config_file); //TODO
        }
        else if(argv[i]=="-n"){
            save_frq=argv[i+1];
            i++;
        }
    }

    

    double **map=load_map(map_file);//TODO 
    int w=load_w_from_map(map_file);//TODO
    int h=load_h_from_map(map_file);//TODO

    swarm *hive=NULL;
    if(conf==NULL)
        hive=initialize_swarm(probe_num);
    else
        hive=initialize_probe_config(probe_num,conf);


    place_probes(hive,w,h,map);

    for(int i=0;i<iterations;i++){
        move_hive(hive,map,w,h);
        if(save_frq!=0 && i%save_frq==0)
            save_to_csv(hive);//TODO
    }
        
        
    free_swarm(hive);
    free_map(map,h);
    
    
    return 0;
}