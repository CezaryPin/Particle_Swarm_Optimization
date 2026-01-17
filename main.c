#include "pso.h"
#include "psoStructs.h"
#include "utils.h"
#include "map.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ./out.exe <map_file> -p probe_num -i interations -c <config_filr> -n save_frq
int main(int argc,char *argv[])
{

    char *map_file=argv[1];
    
    int probe_num=30;
    int iterations=100;
    char *config_file="";
    int save_frq=0;
    pso_config *conf=NULL;

    init_random();


    for(int i=2;i<argc;i++){
        if(strcmp(argv[i],"-p")==0){
            probe_num=atoi(argv[i+1]);
            i++;
        }
        else if(strcmp(argv[i],"-i")==0){
            iterations=atoi(argv[i+1]);
            i++;
        }
        else if(strcmp(argv[i],"-c")==0){
            config_file=argv[i+1];
            i++;
            printf("c ");
            conf=load_config(config_file); //TODO
        }
        else if(strcmp(argv[i],"-n")==0){
            save_frq=atoi(argv[i+1]);
            i++;
        }
    }

    

    map *plot=load_map(map_file);//TODO 
    

    swarm *hive=NULL;
    if(conf==NULL)
        hive=initialize_swarm(probe_num);
    else
        hive=initialize_swarm_config(probe_num,conf);


    place_probes(hive,plot);

    for(int i=0;i<iterations;i++){
        move_hive(hive,plot);
        printf("\n");
        if(save_frq!=0 && i%save_frq==0)
            save_to_csv(hive);//TODO
    }
        
        
    free_swarm(hive);
    free_map(plot);
    
    
    return 0;
}
