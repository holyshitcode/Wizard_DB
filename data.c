#include "data.h"

#include <stddef.h>
#include <string.h>


int insert_key_into_node(struct Node **head, struct Key *target_key) {
    if(insert_node(head, target_key) != 0) {
        return -1;
    }
    return 0;
}

int delete_node_having_key(struct Node **head, struct Key *target_key) {
    if(delete_node_having_data(head, target_key) == 0) {
        return 0;
    }
    return -1;
}

struct Key *get_key_by_name(struct Node *head, char *name) {
    struct Node *pos;
    struct Key *target_key;
    for_each(pos,head) {
        target_key = pos->data;
        if(strcmp(KEY_NAME(target_key), name) == 0) {
            return target_key;
        }
    }
    return NULL;
}