#include <stdio.h>
#include <stdlib.h>
#include "psoStructs.h"
#include "map.h"

map* load_map(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Nie mozna otworzyc pliku mapy");
        return NULL;
    }

    map *m = malloc(sizeof(map));
    if (!m) { fclose(file); return NULL; }


    if (fscanf(file, "%d %d", &m->w, &m->h) != 2) {
        fclose(file);
        free(m);
        return NULL;
    }

    //printf("%d %d",m->w,m->h);
    m->plot = malloc(m->h * sizeof(double*));
    for (int i = 0; i < m->h; i++) {
        m->plot[i] = malloc(m->w * sizeof(double));
        for (int j = 0; j < m->w; j++) {
            fscanf(file, "%lf", &m->plot[i][j]);
        }
    }

    fclose(file);
    return m;
}
void free_map(map *m){
    for(int i=0;i<m->h;i++){
        free(m->plot[i]);
    }
    free(m->plot);
    free(m);
}
