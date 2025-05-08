#include "database.h"

#include <stdlib.h>
#include <string.h>

struct Database *database_list[DATABASE_MAX];
int database_count = 0;


int create_database(char *database_name) {
    if (database_count >= DATABASE_MAX) {
        return -1;
    }
    struct Database *created_database = malloc(sizeof(struct Database));
    if (created_database == NULL) {
        return -1;
    }
    strcpy(created_database->database_name, database_name);
    created_database->chain_list = NULL;
    database_list[database_count++] = created_database;
    return 0;
}



struct Database *get_database_by_name(char *database_name) {
    for (int i = 0; i < database_count; i++) {
        if (strcmp(database_list[i]->database_name, database_name) == 0) {
            return database_list[i];
        }
    }
    return NULL;
}



int create_chain_into_database(char *database_name, char *chain_name) {
    struct Database *created_database = get_database_by_name(database_name);
    if (created_database == NULL) {
        return -1;
    }
    struct Chain *chain = malloc(sizeof(struct Chain));
    if (chain == NULL) {
        return -1;
    }
    strcpy(chain->chain_name, chain_name);
    chain->next = NULL;
    insert_chain_to_list(&created_database->chain_list, chain);
    return 0;
}

int delete_chain_from_database(char *database_name, char *chain_name) {
    struct Database *found_database = get_database_by_name(database_name);
    if (found_database == NULL) {
        return -1;
    }
    if(found_database->chain_list == NULL) {
        return -1;
    }
    delete_chain_from_list(&found_database->chain_list, chain_name);
    return 0;
}

int insert_key_to_chain_db(char *database_name, char *chain_name, struct Key *key) {
    struct Database *found_database = get_database_by_name(database_name);
    if (found_database == NULL) {
        return -1;
    }
    struct Chain *pos;
    for_each_c(pos, found_database->chain_list) {
        if (strcmp(pos->chain_name, chain_name) == 0) {
            insert_key_into_node(&pos->node_list,key);
        }
    }
    return 0;
}

int delete_key_from_chain_db(char *database_name, char *chain_name, char *key_name) {
    struct Database *found_database = get_database_by_name(database_name);
    if (found_database == NULL) {
        return -1;
    }
    struct Chain *pos;
    for_each_c(pos, found_database->chain_list) {
        if (strcmp(pos->chain_name, chain_name) == 0) {
            struct Key *target_key = get_key_from_chain(pos, key_name);
            delete_node_having_key(&pos->node_list, target_key);
            return 0;
        }
    }
    return -1;
}

void free_database(struct Database *database) {
    struct Chain *chain_pos;
    for_each_c(chain_pos, database->chain_list) {
        struct Node *node_pos;
        struct Node *start_node = chain_pos->node_list;
        if (start_node != NULL) {
            for_each(node_pos, start_node) {
                struct Key *key_data = node_pos->data;
                if (key_data) {
                    free(key_data->value);
                    free(key_data);
                }
                free(node_pos);
            }
        }
    }
    free(database);
}


int delete_database(char *database_name) {
    if (database_count <= 0) {
        return -1;
    }
    struct Database *target_database = get_database_by_name(database_name);
    if (target_database == NULL) {
        return -1;
    }
    for (int i = 0; i < database_count; i++) {
        if (database_list[i] == target_database) {
            free_database(target_database);

            for (int j = i; j < database_count - 1; j++) {
                database_list[j] = database_list[j + 1];
            }
            database_list[database_count - 1] = NULL;
            database_count--;
            return 0;
        }
    }
    return -1;
}




