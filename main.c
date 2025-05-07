#include <stdio.h>
#include "linked_list.h"


int main(void) {
    struct Node *head = NULL;
    struct Node *pos = NULL;
    int a = 10;
    int b = 20;
    insert_node(&head, &a);
    insert_node(&head, &b);
    for_each(pos, head) {
        printf("%d\n",*(int*) pos->data);
    }

    return 0;
}
