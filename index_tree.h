#ifndef INDEX_TREE_H
#define INDEX_TREE_H


struct Tree_Node {
    long key;
    struct Tree_Node* left;
    struct Tree_Node* right;
};

struct Tree_Node *create_tree_node(long index_key);
int insert_tree_node(struct Tree_Node **current, long index_key);
struct Tree_Node *search_tree_node(struct Tree_Node **current, long index_key);
struct Tree_Node *find_successor(struct Tree_Node **current);
int delete_tree_node(struct Tree_Node **current, long index_key);

#endif