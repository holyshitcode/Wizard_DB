#ifndef DATABASE_H
#define DATABASE_H

#include "chain.h"
#include "key.h"
#include "index_tree.h"
#define DATABASE_MAX 100

extern struct Database *database_list[DATABASE_MAX];
extern int database_count;

struct Database {
    char database_name[25];
    struct Chain *chain_list;
    //tree pointer will be added
    long index_counter;
    //indexing base counter will be added
    struct Tree_Node *root;
};
struct Database *get_database_by_name(char *database_name);
int create_database(char *database_name);
int create_chain_into_database(char *database_name, char *chain_name);
int delete_chain_from_database(char *database_name, char *chain_name);
int insert_key_to_chain_db(char *database_name, char *chain_name, struct Key *key);
int delete_key_from_chain_db(char *database_name, char *chain_name, char *key_name);
void free_database(struct Database *database);
int delete_database(char *database_name);
struct Key_List *get_keys_from_chain_db_str_contains(char *database_name, char *contains);
struct Key_List *get_keys_from_chain_db_same_str(char *database_name, char *exact_string);
struct Key *get_key_from_chain_db_by_name(char *database_name, char *key_name);



#endif