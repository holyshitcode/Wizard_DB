#include <stdio.h>
#include <string.h>

#include "chain.h"
#include "linked_list.h"
#include "key.h"
#include "database.h"


int main(void) {
    // struct Chain *head = NULL;
    // struct Chain *temp = NULL;
    // struct Chain *pos;
    // temp = create_chain("test");
    // insert_chain_to_list(&head, temp);
    // struct Key *key = create_key("test_key_name","test_key_value");
    // insert_key_into_node(&temp->node_list,key);
    //
    //
    // for_each_c(pos, head) {
    //     if(strcmp(pos->chain_name,"test") == 0) {
    //         printf("%s\n",pos->chain_name);
    //         struct Key *key_temp = get_key_by_name(pos->node_list,"test_key_name");
    //         printf("%s\n",key_temp->value);
    //         printf("%s\n", key_temp->key_name);
    //     }
    // }
    create_database("test.db");
    create_chain_into_database("test.db", "test_chain");
    struct Key *key = create_key("test_key","test_value");
    insert_key_to_chain_db("test.db","test_chain",key);
    struct Database *database = database_list[0];
    struct Chain *chain = database->chain_list;
    struct Key *found_key = get_key_by_name(chain->node_list,"test_key");
    printf("%s,%s",KEY_NAME(found_key),KEY_VALUE(found_key));


    return 0;
}
