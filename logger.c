#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "psoStructs.h"

void save_to_csv(swarm *hive) {
    static int iteration_count = 0; 
    char filename[64];

    sprintf(filename, "pso_log_iter_%d.csv", iteration_count);
    
    iteration_count++; 

    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("Nie udalo sie otworzyc pliku do zapisu");
        return;
    }

    fprintf(f, "id,x,y,p_best_val\n");

    for (int i = 0; i < hive->num_probes; i++) {
        probe *p = hive->probe_list[i]; 
        
        fprintf(f, "%d,%f,%f,%f\n", i, p->pos_x, p->pos_y, p->p_best_val);
    }

    fclose(f);
}