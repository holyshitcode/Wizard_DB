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
    create_chain_into_database("test.db", "test_chain2");
    struct Key *key = create_key("test_key","test_value");
    struct Key *key2 = create_key("test_key2","test_value2");
    insert_key_to_chain_db("test.db","test_chain",key);
    insert_key_to_chain_db("test.db","test_chain",key2);
    // insert_key_to_chain_db("test.db","test_chain2",key);
    insert_key_to_chain_db("test.db","test_chain2",key2);

    struct Database *database = database_list[0];
    struct Chain *chain = database->chain_list;
    struct Key *found_key = get_key_by_name(chain->node_list,"test_key");
    // printf("%s,%s\n",KEY_NAME(found_key),KEY_VALUE(found_key));
    struct Key_List *key_list =get_keys_from_chain_db_same_str("test.db","test_value");
    struct Key_List *pos;
    for_each_key(pos,key_list) {
        printf("%s,%s\n",KEY_NAME(pos->key),KEY_VALUE(pos->key));
    }
    free_key_list(key_list);
    struct Key *key3 = get_key_from_chain_db_by_name("test.db","test_key2");
    printf("%s\n",KEY_NAME(key3));
    // struct Key_List *key_list2 =get_keys_from_chain_db_str_contains("test.db","value");
    // struct Key_List *pos2;
    // for_each_key(pos2,key_list2) {
    //     printf("%s,%s\n",KEY_NAME(pos2->key),KEY_VALUE(pos2->key));
    // }
    // free_key_list(key_list2);



    return 0;
}
