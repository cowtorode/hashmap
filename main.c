#include "map.h"
#include <stdio.h>

int main(void)
{
    hashmap* map = hashmap_new(7);

    hashmap_put(map, "sunday", (void*) 0);
    hashmap_put(map, "monday", (void*) 1);
    hashmap_put(map, "tuesday", (void*) 2);
    hashmap_put(map, "wednesday", (void*) 3);
    hashmap_put(map, "thursday", (void*) 4);
    hashmap_put(map, "friday", (void*) 5);
    hashmap_put(map, "saturday", (void*) 6);

    char in[256];
    void* value = NULL;

    while (in[0] != 'e')
    {
        scanf("%s", in);

        if (hashmap_find(map, in, &value))
        {
            printf("Value: %lu\n", (unsigned long) value);
        } else
        {
            printf("Value not found\n");
        }
    }

    hashmap_free(map);
    return 0;
}
