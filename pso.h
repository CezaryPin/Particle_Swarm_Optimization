#include "psoStructs.h"

pso_config* load_config(const char *filename);
swarm *initialize_swarm(int num_probes);
swarm *initialize_swarm_config(int num_probes,pso_config *conf);
probe *initialize_probe(swarm *hive);
probe *initialize_probe_config(swarm *hive,pso_config *conf);
void place_probes(swarm *hive,map *plot);
void print_swarm(swarm *hive);
void print_probe_pos(probe *drone);
void free_swarm(swarm *hive);
void move_hive(swarm *hive, map *plot);
void move_probe(probe *drone, map *plot);
