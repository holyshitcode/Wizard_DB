#ifndef CHAIN_H
#define CHAIN_H

#include "linked_list.h"
#include "key.h"

struct Chain{
    char chain_name[25];
    struct Node *node_list;
    struct Chain *next;
};

struct Chain *create_chain(char *chain_name);

#endif