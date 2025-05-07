#include <stdio.h>
#include <string.h>

#include "chain.h"
#include "linked_list.h"
#include "key.h"


int main(void) {
    struct Chain *head = NULL;
    struct Chain *temp = NULL;
    struct Chain *pos;
    temp = create_chain("test");
    insert_chain_to_list(&head, temp);
    struct Key *key = create_key("test_key_name","test_key_value");
    insert_key_into_node(&temp->node_list,key);


    for_each_c(pos, head) {
        if(strcmp(pos->chain_name,"test") == 0) {
            printf("%s\n",pos->chain_name);
            struct Key *key_temp = get_key_by_name(pos->node_list,"test_key_name");
            printf("%s\n",key_temp->value);
            printf("%s\n", key_temp->key_name);
        }
    }



    return 0;
}
