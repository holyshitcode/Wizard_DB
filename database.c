#include "database.h"

#include <stdlib.h>
#include <string.h>

struct Database *database_list[DATABASE_MAX];
int database_count = 0;


/*
 * todo
 * 데이터베이스 indexing counter 기준으로 키생성시에 카운터증가하는 키만들기 함수
 * 데이터베이스 인덱스조회해서 duplicate 검사하는 함수
 * done
 */

/*
 * todo
 * primary key를 직접쓰는 모드와 자동증가모드로 선택할수있게 조정해야함
 * 현재구현은 자동증가임
 */

struct Key *create_key_db(char *database_name, char *key_name, char *key_value, long primary_key) {
    struct Database *target_database = get_database_by_name(database_name);
    if (target_database == NULL) {
        return NULL;
    }
    struct Key *created_key = create_key(key_name, key_value);
    if (created_key == NULL) {
        return NULL;
    }
    if(target_database->primary_key_type == AUTO_INC) {
        target_database->index_counter++;
        created_key->primary_key = target_database->index_counter;
        if(insert_tree_node(&target_database->root, target_database->index_counter) == 0) {
            return created_key;
        }
    }else {
        created_key->primary_key = primary_key;
        if(insert_tree_node(&target_database->root, primary_key) == 0) {
            return created_key;
        }
    }
    return NULL;
}

int create_database(char *database_name, enum PRIMARY_KEY_TYPE key_type) {
    //duplicate exception
    if (get_database_by_name(database_name) != NULL) {
        return -1;
    }

    if (database_count >= DATABASE_MAX) {
        return -1;
    }
    struct Database *created_database = malloc(sizeof(struct Database));
    if (created_database == NULL) {
        return -1;
    }
    strcpy(created_database->database_name, database_name);
    created_database->chain_list = NULL;
    //index tree
    created_database->root =  NULL;
    created_database->index_counter = -1;

    //auto,manual selection
    created_database->primary_key_type = key_type;

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

static struct Chain *get_chain_from_database_by_name(char* database_name, char *chain_name) {
    struct Database *target_database = get_database_by_name(database_name);
    struct Chain *pos;
    if (target_database == NULL) {
        return NULL;
    }
    for_each_c(pos, target_database->chain_list) {
        if (strcmp(pos->chain_name, chain_name) == 0) {
            return pos;
        }
    }
    return NULL;
}

int create_chain_into_database(char *database_name, char *chain_name) {

    //duplicate exception
    if(get_chain_from_database_by_name(database_name, chain_name) != NULL) {
        return -1;
    }
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

static struct Key *get_key_from_chain_by_name(struct Chain *target_chain,  char *key_name) {
    struct Chain *pos;
    struct Node *target_node;
    for_each_c(pos,target_chain) {
        for_each(target_node,pos->node_list) {
            struct Key *target_key = target_node->data;
            if(strcmp(KEY_NAME(target_key), key_name) == 0) {
                return target_key;
            }
        }
    }
    return NULL;
}

int insert_key_to_chain_db(char *database_name, char *chain_name, struct Key *key) {
    struct Database *found_database = get_database_by_name(database_name);
    struct Chain *target_chain = get_chain_from_database_by_name(database_name, chain_name);
    //duplicate exception(will be changed by indexing)
    // if (get_key_from_chain_by_name(target_chain,KEY_NAME(key))) {
    //     return -1;
    // }
    if (search_tree_node(&found_database->root, key->primary_key) != NULL) {
        return -1;
    }
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
            delete_tree_node(&found_database->root, target_key->primary_key);
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

struct Key_List *get_keys_from_chain_db_str_contains(char *database_name, char *contains) {
    struct Database *found_database = get_database_by_name(database_name);
    struct Node *found_node;
    struct Key_List *key_list = NULL;
    struct Key *current_key;
    struct Chain *chain_pos;

    if (found_database == NULL) {
        return NULL;
    }
    for_each_c(chain_pos, found_database->chain_list) {
        for_each(found_node, chain_pos->node_list) {
            current_key = found_node->data;
            if(strstr(current_key->value,contains) != NULL) {
                insert_key_into_key_list(&key_list,current_key);
            }
        }
    }
    return key_list;
}

struct Key_List *get_keys_from_chain_db_same_str(char *database_name, char *exact_string) {
    struct Database *found_database = get_database_by_name(database_name);
    struct Node *found_node;
    struct Key_List *key_list = NULL;
    struct Key *current_key;
    struct Chain *chain_pos;

    if (found_database == NULL) {
        return NULL;
    }
    for_each_c(chain_pos, found_database->chain_list) {
        for_each(found_node, chain_pos->node_list) {
            current_key = found_node->data;
            if(strcmp(current_key->value,exact_string) == 0) {
                insert_key_into_key_list(&key_list,current_key);
            }
        }
    }
    return key_list;
}

struct Key *get_key_from_chain_db_by_name(char *database_name, char *key_name) {
    struct Database *found_database = get_database_by_name(database_name);
    struct Node *found_node;
    struct Key *current_key;
    struct Chain *chain_pos;

    if (found_database == NULL) {
        return NULL;
    }

    for_each_c(chain_pos, found_database->chain_list) {
        for_each(found_node, chain_pos->node_list) {
            current_key = found_node->data;
            if(strcmp(KEY_NAME(current_key), key_name) == 0) {
                return current_key;
            }
        }
    }

    return NULL;
}








