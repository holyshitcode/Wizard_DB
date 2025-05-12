#ifndef KEY_H
#define KEY_H

#define KEY_NAME(key) key->key_name
#define KEY_VALUE(key) key->value
#define for_each_key(pos,head) for(pos = (head); pos != NULL; pos = pos->next)

struct Key {
    char key_name[25];
    char *value;
};

struct Key_List {
    struct Key *key;
    struct Key_List *next;
};


int insert_key_into_key_list(struct Key_List **head, struct Key *key);
struct Key *create_key(char *name, char *value);
int delete_key(struct Key *key);
void free_key_list(struct Key_List *head);

#endif