#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>

#include "check.h"

typedef struct item {
    void* data; // pointer to the object with data
    struct item* next;
    struct item* prev;
} item;

typedef void(* deleting_item_data_func)(void*);
typedef void*(* creating_copy_func)(void*);

typedef struct {
    item* beginning;
    item* ending;
    size_t data_size;
    deleting_item_data_func delete_item_data;
    creating_copy_func create_copy_item_data;
} list;

list* create_list(size_t data_size, deleting_item_data_func delete_item_data, creating_copy_func create_copy_item_data);
list* create_list_copy(list *other);
void delete_list(list* l);
void pop_front(list* lst);
void push_front(list* lst, void* data);
void pop_back(list* lst);
void push_back(list* lst, void* data);
void insert(list* lst, item* prev, void* data);
void erase(list* lst, item* prev);
void* get_by_index(list* lst, int i);
item* get_item_by_index(list* lst, int i);
int num_items(list* lst);

#endif // LIST_H
