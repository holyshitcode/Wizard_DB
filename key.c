#include "key.h"

#include <stdlib.h>
#include <string.h>

struct Key *create_key(char *name, char *value) {
    struct Key *create_key = malloc(sizeof(struct Key));
    KEY_VALUE(create_key) = malloc(sizeof(char) * strlen(value) + 1);
    strcpy(KEY_NAME(create_key), name);
    strcpy(KEY_VALUE(create_key), value);
    return create_key;
}

int delete_key(struct Key *key) {
    free(KEY_VALUE(key));
    free(key);
    return 0;
}
