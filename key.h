#ifndef KEY_H
#define KEY_H

#define KEY_NAME(key) key->key_name
#define KEY_VALUE(key) key->value
#define for_each_key(pos,head) for(pos = (head); pos != NULL; pos = pos->next)


/*
 * todo
 * indexing 하기위해서 key의 primary value를 만들고
 * 그 primary value를 관리하는 이진트리를 구현
 * duplicate 검사시 Database의 이진트리를 조회하도록 변경해야함
 * 1. primary key add
 * 2.  binary tree
 * 3. duplicate method change
 *
 */
struct Key {
    long primary_key;
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