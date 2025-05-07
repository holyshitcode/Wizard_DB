#include <stdio.h>
#include "linked_list.h"
#include "key.h"


int main(void) {
    struct Node *head = NULL;
    struct Node *pos = NULL;
    struct Key *key = create_key("test_key","test_value");
    struct Key *key2 = create_key("test_key2","test_value2");
    insert_node(&head,key );
    insert_node(&head, key2);
    for_each(pos, head) {
        struct Key *key = pos->data;
        printf("%s,%s\n",KEY_NAME(key),KEY_VALUE(key));
    }

    return 0;
}
