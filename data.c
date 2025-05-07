#include "data.h"


int insert_key_into_node(struct Node *head, struct Key *target_key) {
    if(insert_node(&head, target_key) != 0) {
        return -1;
    }
    return 0;
}

int delete_node_having_key(struct Node *head, struct Key *target_key) {
    if(delete_node_having_data(&head, target_key) == 0) {
        return 0;
    }
    return -1;
}