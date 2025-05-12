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

int insert_key_into_key_list(struct Key_List **head, struct Key *key) {
    struct Key_List *key_list = malloc(sizeof(struct Key_List));
    if (key_list == NULL) {
        return -1;
    }

    key_list->key = key;
    key_list->next = NULL;

    if (*head == NULL) {
        *head = key_list;
    } else {
        struct Key_List *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = key_list;
    }

    return 0;
}

int delete_key(struct Key *key) {
    free(KEY_VALUE(key));
    free(key);
    return 0;
}

void free_key_list(struct Key_List *head) {
    struct Key_List *current = head;
    struct Key_List *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
