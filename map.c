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
    struct bucket* next;
};

struct hashmap
{
    struct bucket** entries;
    size_t size;
};

hashmap* hashmap_new(size_t size)
{
    hashmap* map = malloc(sizeof(hashmap));

    if (map)
    {
        map->size = size;
        map->entries = calloc(size, sizeof(struct bucket*));
    }

    return map;
}

void hashmap_free(hashmap* map)
{
    struct bucket* entry;

    /* We have to iterate through each bucket in the hashmap to free
       the linked list of buckets */

    // Iterate through all buckets
    for (size_t i = 0; i < map->size; ++i)
    {
        entry = map->entries[i];

        // Iterate through the linked list of buckets
        while (entry)
        {
            struct bucket* temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }

    free(map->entries);
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

    struct bucket* entry = malloc(sizeof(struct bucket));

    entry->key = strdup(key);
    entry->value = value;
    // Write to the linked list for any collisions
    entry->next = map->entries[index];

    // Write to the hashmap entry set
    map->entries[index] = entry;
}

char hashmap_find(hashmap* map, const char* key, void** value)
{
    unsigned long index = dbj2_hash(key) % map->size;

    struct bucket* entry = map->entries[index];

    // while the keys in the buckets don't match
    while (entry && strcmp(entry->key, key) != 0)
    {
        entry = entry->next;
    }

    // entry could be null here if all collisions expired
    if (entry)
    {
        *value = entry->value;
        return 1;
    }
    return 0;
}
