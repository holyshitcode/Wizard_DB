#ifndef DATA_H
#define DATA_H

#include "key.h"
#include "linked_list.h"

int insert_key_into_node(struct Node *head, struct Key *target_key);
int delete_node_having_key(struct Node *head, struct Key *target_key);
struct Key *get_key_by_name(struct Node *head, char *name);

#endif