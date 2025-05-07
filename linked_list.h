#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define for_each(pos, head) for(pos = (head); pos != NULL; pos = (pos->next == (head) ? NULL : pos->next))

struct Node {
    void *data;
    struct Node *next;
};

struct Node *create_node(void *data);
int  insert_node(struct Node **head, void *data);
struct  Node *delete_node(struct Node **head);
int delete_node_having_data(struct Node **head, void *data);

#endif