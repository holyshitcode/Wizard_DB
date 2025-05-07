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

