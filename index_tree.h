#ifndef INDEX_TREE_H
#define INDEX_TREE_H

struct Tree {
    struct Tree_Node* root;
};

struct Tree_Node {
    int key;
    struct Tree_Node* left;
    struct Tree_Node* right;
};


#endif