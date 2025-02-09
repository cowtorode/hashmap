//
// Created by cory on 2/9/25.
//

#ifndef CTEST_MAP_H
#define CTEST_MAP_H

#include "stddef.h"

typedef struct hashmap hashmap;

/**
 * Allocates memory for a new hashmap, preparing all buckets for entries
 */
hashmap* hashmap_new(size_t size);

void hashmap_free(hashmap* map);

void hashmap_put(hashmap* map, const char* key, void* value);

/**
 * @return 1 if found, false if not. If found, value will be written. Otherwise it will be whatever it was.
 */
char hashmap_find(hashmap* map, const char* key, void** value);

#endif //CTEST_MAP_H
