#ifndef CHAIN_H
#define CHAIN_H

#include "data.h"
#include "linked_list.h"
#include "key.h"

struct Chain{
    char chain_name[25];
    struct Node *node_list;
    struct Chain *next;
};

struct Chain *create_chain(char *chain_name);
int insert_key_to_chain(struct Chain *target_chain, struct Key *key);
int delete_key_from_chain(struct Chain *target_chain, struct Key *key);

#endif