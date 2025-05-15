#include <stdio.h>
#include <string.h>

#include "chain.h"
#include "linked_list.h"
#include "key.h"
#include "database.h"


int main(void) {
    create_database("testdb",MANUAL);
    struct Database *db = get_database_by_name("testdb");
    create_chain_into_database("testdb","testc");
    struct Key *key =create_key_db("testdb","testkeyname","testkeyvalue",5);
    insert_key_to_chain_db("testdb","testc",key);
    struct Tree_Node *result = search_tree_node(&db->root,5);
    // delete_key_from_chain_db("testdb","testc","testkeyname");
    if(result !=NULL) {
        printf("%ld\n ",result->key);
    }






    return 0;
}
