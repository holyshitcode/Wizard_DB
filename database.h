#ifndef DATABASE_H
#define DATABASE_H

#include "chain.h"
#define DATABASE_MAX 100

extern struct Database *database_list[DATABASE_MAX];
extern int database_count = 0;

struct Database {
    char database_name[25];
    struct Chain *chain_list;
};
struct Database *get_database_by_name(char *database_name);
int create_database(char *database_name);
int create_chain_into_database(char *database_name, char *chain_name);
int delete_chain_from_database(char *database_name, char *chain_name);
int insert_key_to_chain(char *database_name, char *chain_name, struct Key *key);
int delete_key_from_chain(char *database_name, char *chain_name, char *key_name);
void free_database(struct Database *database);
int delete_database(char *database_name);



#endif