#include "index_tree.h"

#include <stdlib.h>


struct Tree_Node *create_tree_node(long index_key) {
    struct Tree_Node *create_tree_node = malloc(sizeof(struct Tree_Node));
    create_tree_node->key = index_key;
    create_tree_node->left = NULL;
    create_tree_node->right = NULL;
    return create_tree_node;
}

int insert_tree_node(struct Tree_Node **current, long index_key) {
    if(*current == NULL) {
        *current = create_tree_node(index_key);
        return 0;
    }
    if((*current)->key == index_key) {
        return -1;
    }
    if((*current)->key < index_key) {
        return insert_tree_node(&((*current)->right), index_key);
    }
    return insert_tree_node(&((*current)->left), index_key);
}

struct Tree_Node *search_tree_node(struct Tree_Node **current, long index_key) {
    if (*current == NULL) {
        return NULL;
    }

    if ((*current)->key == index_key) {
        return *current;
    }

    if ((*current)->key < index_key) {
        return search_tree_node(&((*current)->right), index_key);
    }

    return search_tree_node(&((*current)->left), index_key);

}

struct Tree_Node *find_successor(struct Tree_Node **current) {
    if (*current == NULL || (*current)->right == NULL) {
        return NULL;
    }

    struct Tree_Node *node = (*current)->right;

    while (node->left != NULL) {
        node = node->left;
    }

    return node;
}

int delete_tree_node(struct Tree_Node **current, long index_key) {
    if (*current == NULL) {
        return -1;
    }

    if ((*current)->key > index_key) {
        return delete_tree_node(&((*current)->left), index_key);
    } else if ((*current)->key < index_key) {
        return delete_tree_node(&((*current)->right), index_key);
    }

    struct Tree_Node *node_to_delete = *current;

    if ((*current)->left == NULL && (*current)->right == NULL) {
        free(*current);
        *current = NULL;
    }
    else if ((*current)->left == NULL) {
        *current = (*current)->right;
        free(node_to_delete);
    }
    else if ((*current)->right == NULL) {
        *current = (*current)->left;
        free(node_to_delete);
    }
    else {
        struct Tree_Node *successor = find_successor(&((*current)->right));
        (*current)->key = successor->key;
        delete_tree_node(&((*current)->right), successor->key);
    }

    return 0;
}