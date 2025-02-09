//
// Created by cory on 2/9/25.
//

#include <malloc.h>
#include <string.h>
#include "map.h"

struct bucket
{
    char* key;
    void* value;
    bucket* next;
};

struct hashmap
{
    bucket** entries;
    size_t size;
};

hashmap* hashmap_new(size_t size)
{
    //printf("malloc hashmap\n");
    hashmap* map = malloc(sizeof(hashmap));

    if (map)
    {
        map->size = size;
        //printf("malloc bucket*\n");
        map->entries = calloc(size, sizeof(bucket*));
    }

    return map;
}

void hashmap_free(hashmap* map)
{
    bucket* entry;

    for (size_t i = 0; i < map->size; ++i)
    {
        entry = map->entries[i];

        while (entry)
        {
            bucket* temp = entry;
            entry = entry->next;
            //printf("freeing key: %s\n", temp->key);
            free(temp->key);
            //printf("free hashmap entry\n");
            free(temp);
        }
    }

    //printf("free hashmap entries list\n");
    free(map->entries);
    //printf("free hashmap\n");
    free(map);
}

static unsigned long dbj2_hash(const char* key)
{
    unsigned long hash = 5381;
    char c;

    while ((c = *key++))
    {
        hash += (hash << 5) + c; /* hash * 33 + c */
    }

    return hash;
}

void hashmap_put(hashmap* map, const char* key, void* value)
{
    unsigned long index = dbj2_hash(key) % map->size;

    //printf("malloc bucket\n");
    bucket* entry = malloc(sizeof(bucket));

    entry->key = strdup(key);
    entry->value = value;
    entry->next = map->entries[index];

    //printf("mapping \"%s\" to %lu at index %lu\n", key, (unsigned long) value, index);
    map->entries[index] = entry;
}

char hashmap_find(hashmap* map, const char* key, void** value)
{
    unsigned long index = dbj2_hash(key) % map->size;

    bucket* entry = map->entries[index];

    // while the keys in the buckets don't match
    while (entry && strcmp(entry->key, key) != 0)
    {
        entry = entry->next;
    }

    if (entry)
    {
        *value = entry->value;
        return 1;
    }
    return 0;
}
