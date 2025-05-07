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

int insert_chain_to_list(struct Chain **head, struct Chain *target_chain) {
    struct Chain *pos;

    if(target_chain == NULL) {
        return -1;
    }

    if (*head == NULL) {
        *head = target_chain;
        return 0;
    }

    for_each_c(pos, *head) {
        if (pos->next == NULL) {
            pos->next = target_chain;
            return 0;
        }
    }

    return -1;
}

int delete_chain_from_list(struct Chain **head, char *chain_name) {
    if (*head == NULL || chain_name == NULL) {
        return -1;
    }
    struct Chain *pos, *prev = *head;;
    for_each_c(pos, *head) {
        if (strcmp(pos->chain_name, chain_name) == 0) {
            prev->next = pos->next;
            free(pos);
        }
        prev = pos;
    }
    return 0;
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

struct Key *get_key_from_chain(struct Chain *target_chain, char *key_name) {
    struct Node *target_chain_list = target_chain->node_list;
    struct Key *target_key = get_key_by_name(target_chain_list, key_name);
    if(target_key == NULL) {
        return NULL;
    }
    return target_key;
}
