#include "psoStructs.h"
#include "utils.h"
#include <stdlib.h>
#include "pso.h"
#include <stdio.h>
#include <math.h>


pso_config* load_config(const char *filename) {
    if (filename == NULL || filename[0] == '\0') return NULL;

    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    pso_config *conf = malloc(sizeof(pso_config));
    if (fscanf(file, "%lf %lf %lf %lf %lf", 
               &conf->w, &conf->c_1, &conf->r_1, &conf->c_2, &conf->r_2) != 5) {
        free(conf);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return conf;
}

swarm *initialize_swarm(int num_probes){
    swarm *hive=malloc(sizeof(swarm));
    hive->s_best_x=-1;
    hive->s_best_y=-1;
    hive->s_best_val=-9999;
    hive->num_probes=num_probes;
    hive->probe_list=calloc(num_probes,sizeof(probe));
    for(int i=0;i<num_probes;i++)
        hive->probe_list[i]=initialize_probe(hive);
    return hive;
}
swarm *initialize_swarm_config(int num_probes,pso_config *conf){
    swarm *hive=malloc(sizeof(swarm));
    hive->s_best_x=-1;
    hive->s_best_y=-1;
    hive->s_best_val=-9999;
    hive->num_probes=num_probes;
    hive->probe_list=calloc(num_probes,sizeof(probe));
    for(int i=0;i<num_probes;i++)
        hive->probe_list[i]=initialize_probe_config(hive,conf);
    return hive;
}

probe *initialize_probe(swarm *hive){
    probe *tmp=malloc(sizeof(probe));
    tmp->my_swarm=hive;
    tmp-> weight=rand_double(); 
    tmp-> c_1=rand_double();  
    tmp-> c_2=rand_double();  
    tmp-> r_1=1;  
    tmp-> r_2=1;  
    tmp->p_best_val=-1000; 
    tmp->p_best_x=0;
    tmp->p_best_y=0;
    tmp-> v_x=0;
    tmp->v_y=0;
    

    return tmp;
}
probe *initialize_probe_config(swarm *hive,pso_config *conf){
    probe *tmp=malloc(sizeof(probe));
    tmp->my_swarm=hive;
    tmp-> weight=conf->w; 
    tmp-> c_1=conf->c_1;  
    tmp-> c_2=conf->c_2;  
    tmp-> r_1=conf->r_1;  
    tmp-> r_2=conf->r_2;  
    tmp->p_best_val=-1000; 
    tmp->p_best_x=0;
    tmp->p_best_y=0;
    tmp-> v_x=0;
    tmp->v_y=0;

    return tmp;
}

void place_probes(swarm *hive,map *plot){
    probe *drone;
    for(int i=0;i<hive->num_probes;i++){
        drone=hive->probe_list[i];
        drone->pos_x=rand_double()*(plot->w-1);
        drone->pos_y=rand_double()*(plot->h-1);
        
        drone->p_best_x=drone->pos_x;
        drone->p_best_y=drone->pos_y;
        drone->p_best_val=plot->plot[(int)round(drone->pos_y)][(int)round(drone->pos_x)];
        if(drone->p_best_val>drone->my_swarm->s_best_val){
            drone->my_swarm->s_best_x=drone->pos_x;
            drone->my_swarm->s_best_y=drone->pos_y;
            drone->my_swarm->s_best_val=drone->p_best_val;
        }
    }
    
}

void print_swarm(swarm *hive){
    for(int i=0;i<hive->num_probes;i++){
        print_probe_pos(hive->probe_list[i]);
    }
}

void print_probe_pos(probe *drone){
    printf("[%.2f, %.2f]   ",round(drone->pos_x),round(drone->pos_y));
    printf("[%.2f, %.2f]   ",drone->pos_x,drone->pos_y);
    printf("%.2f [%.2f, %.2f] ",drone->p_best_val,drone->p_best_x,drone->p_best_y);
    printf("me: %.3f, hive: %.3f ",drone->c_1,drone->c_2);
    printf("v_x: %.2f, v_y: %.2f ",drone->v_x,drone->v_y);
    printf("W: %.3f\n",drone->weight);
}

void free_swarm(swarm *hive){
    for(int i=0;i<hive->num_probes;i++)
        free(hive->probe_list[i]);
    free(hive);
}

void move_hive(swarm *hive, map *plot){//max_x and max_y should be map sizes
    for(int i=0;i<hive->num_probes;i++)
    {
        hive->probe_list[i]->r_1=rand_double();
        hive->probe_list[i]->r_2=rand_double();
        move_probe(hive->probe_list[i],plot);
    }
        
}

void move_probe(probe *drone,map *plot){
    //print_probe_pos(drone);
    //change speed
    drone->v_x=drone->weight*drone->v_x+drone->c_1*drone->r_1*(drone->p_best_x-drone->pos_x)+drone->c_2*drone->r_2*(drone->my_swarm->s_best_x-drone->pos_x);
    drone->v_y=drone->weight*drone->v_y+drone->c_1*drone->r_1*(drone->p_best_y-drone->pos_y)+drone->c_2*drone->r_2*(drone->my_swarm->s_best_y-drone->pos_y);


    //max speed
    double max_speed=((double)plot->h+(double)plot->w)/10;
    //printf("max speed=%f\n", max_speed);

    if(drone->v_x>max_speed)
        drone->v_x=max_speed;
    else if(drone->v_x< -max_speed)
        drone->v_x=-max_speed;

    if(drone->v_y>max_speed)
        drone->v_y=max_speed;
    else if(drone->v_y< -max_speed)
        drone->v_y=-max_speed;

    //change place
    drone->pos_x+=drone->v_x;
    drone->pos_y+=drone->v_y;
    int idx_x = (int)round(drone->pos_x);
    int idx_y = (int)round(drone->pos_y);
    if(idx_x < 0 || idx_x >= plot->w || idx_y < 0 || idx_y >=plot->h)
    {
        return;
    }
    if(plot->plot[idx_y][idx_x]>drone->p_best_val){
        drone->p_best_x=drone->pos_x;
        drone->p_best_y=drone->pos_y;
        drone->p_best_val=plot->plot[idx_y][idx_x];
        if(drone->p_best_val>drone->my_swarm->s_best_val){
            drone->my_swarm->s_best_x=drone->pos_x;
            drone->my_swarm->s_best_y=drone->pos_y;
            drone->my_swarm->s_best_val=drone->p_best_val;
        }
    }
        

}
