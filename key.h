#ifndef KEY_H
#define KEY_H

#define KEY_NAME(key) key->key_name
#define KEY_VALUE(key) key->value

struct Key {
    char key_name[25];
    char *value;
};

struct Key *create_key(char *name, char *value);
int delete_key(struct Key *key);
int delete_node_having_data(struct Node **head, void *data);

#endif