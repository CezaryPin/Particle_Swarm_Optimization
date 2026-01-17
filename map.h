#ifndef MAP_H
#define MAP_H
#include "psoStructs.h" 

map* load_map(const char *filename);
void free_map(map *m);

#endif