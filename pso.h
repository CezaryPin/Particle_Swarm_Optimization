#include "psoStructs.h"

swarm *initialize_swarm(int num_probes);
probe *initialize_probe(swarm *hive);
probe *initialize_probe_config(swarm *hive,pso_config *conf);
void place_probes(swarm *hive,int max_x,int max_y,double **map);
void print_swarm(swarm *hive);
void print_probe_pos(probe *drone);
void free_swarm(swarm *hive);
void move_hive(swarm *hive, double **map,int max_x,int max_y);
void move_probe(probe *drone,double **map,int max_x, int max_y);