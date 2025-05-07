#include "chain.h"

#include <stdlib.h>
#include <string.h>

struct Chain *create_chain(char *chain_name) {
    struct Chain *chain = malloc(sizeof(struct Chain));
    strcpy(chain->chain_name, chain_name);
    chain->node_list = NULL;
    chain->next = NULL;
    return chain;
}

int insert_key_to_chain(struct Chain *target_chain, struct Key *key) {
    struct Node *target_chain_list = target_chain->node_list;

    if(insert_key_into_node(target_chain_list, key) == 0) {
        return 0;
    }
    return -1;
}

int delete_key_from_chain(struct Chain *target_chain, struct Key *key) {
    struct Node *target_chain_list = target_chain->node_list;

    if(delete_node_having_key(target_chain_list, key) == 0) {
        return 0;
    }
    return -1;
}
