#include "linked_list.h"

#include <stdlib.h>


struct Node *create_node(void *data) {
    struct Node *create_node = malloc(sizeof(struct Node));
    create_node->data = data;
    create_node->next = NULL;
    return create_node;
}

int insert_node(struct Node **head, void *data) {
    struct Node *insert_target_node = create_node(data);
    if(insert_target_node == NULL) {
        return -1;
    }
    if (*head == NULL) {
        *head = insert_target_node;
         insert_target_node->next = insert_target_node;
        return 0;
    }
    insert_target_node->next = (*head)->next;
    (*head)->next = insert_target_node;
    *head = insert_target_node;
    return 0;
}

struct Node *delete_node(struct Node **head) {
    struct Node *delete_target_node = (*head)->next;
    (*head)->next = delete_target_node->next;
    return delete_target_node;
}


int delete_node_having_data(struct Node **head, void *data) {
    struct Node *pos, *prev = *head;

    for_each(pos, *head) {
        if (pos->data == data) {
            if (pos == *head) {
                *head = (*head)->next;
                free(pos);
                return 0;
            }
            prev->next = pos->next;
            free(pos);
            return 0;
        }
        prev = pos;
    }
    return -1;
}



