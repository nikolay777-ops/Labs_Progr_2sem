#include "list.h"

list* create_list(size_t data_size, deleting_item_data_func delete_item_data, creating_copy_func create_copy_item_data) {
    list* l = (list*)malloc(sizeof(list));
    check_mem_alloc(l);
    
    l->beginning = l->ending = NULL;
    l->data_size = data_size;
    l->delete_item_data = delete_item_data;
    l->create_copy_item_data = create_copy_item_data;
    return l;
}

list* create_list_copy(list *other) {
    list* new_list = create_list(other->data_size, other->delete_item_data, other->create_copy_item_data);
      
    for (item* i = other->beginning; i; i = i->next) {
        void* data;
        
        // default copying
        if (other->create_copy_item_data == NULL) {
            data = malloc(sizeof(other->data_size));
            check_mem_alloc(data);
            memcpy(data, i->data, other->data_size);
        }
        // copying using specified function
        else {
            data = other->create_copy_item_data(i->data);
        }
        
        push_back(new_list, data);
    }
    
    return new_list;
}

void delete_list(list* l) {
    item* beginning = l->beginning;
    if (!beginning) { 
        free(l);
        return; 
    }

    item* next = beginning->next;
    for (item* i = beginning; i; i = next) {
        next = i->next;
        l->delete_item_data(i->data);
        free(i);
    }
    free(l);
}

void pop_front(list* lst) {
    if (!lst->beginning || !lst) { return; }
    
    if (lst->ending == lst->beginning) {
        lst->delete_item_data(lst->beginning->data);
        free(lst->beginning);
        lst->beginning = lst->ending = NULL;
        return;
    }

    item* new_beginning = lst->beginning->next;
    new_beginning->prev = NULL;
    lst->delete_item_data(lst->beginning->data);
    free(lst->beginning);
    lst->beginning = new_beginning;
}

void push_front(list* lst, void* data) {
    if (!lst->beginning) {
        lst->beginning = (item*)malloc(sizeof (item));
        check_mem_alloc(lst->beginning);

        lst->beginning->data = data;
        lst->beginning->next = lst->beginning->prev = NULL;
        lst->ending = lst->beginning;
        return;
    }

    item* new_item = (item*)malloc(sizeof (item));
    check_mem_alloc(new_item);

    new_item->data = data;
    new_item->prev = NULL;
    new_item->next = lst->beginning;
    lst->beginning->prev = new_item;
    lst->beginning = new_item;
}

void pop_back(list* lst) {
    if (!lst->ending) { return; }
    
    if (lst->ending == lst->beginning) {
        lst->delete_item_data(lst->ending->data);
        free(lst->ending);
        lst->beginning = lst->ending = NULL;
        return;
    }

    item* new_ending = lst->ending->prev;
    new_ending->next = NULL;
    lst->delete_item_data(lst->ending->data);
    free(lst->ending);
    lst->ending = new_ending;
}

void push_back(list* lst, void* data) {
    if (lst->beginning == NULL && lst->ending == NULL) {
        lst->ending = (item*)malloc(sizeof (item));
        check_mem_alloc(lst->ending);

        lst->ending->data = data;
        lst->ending->next = lst->ending->prev = NULL;
        lst->beginning = lst->ending;
        return;
    }

    item* new_item = (item*)malloc(sizeof (item));
    check_mem_alloc(new_item);
    new_item->data = data;
    new_item->next = NULL;
    new_item->prev = lst->ending;
    lst->ending->next = new_item;
    lst->ending = new_item;
}

void insert(list* lst, item* prev, void* data) {
    if (prev == NULL) {
        push_front(lst, data);
        return;
    }
    if (prev == lst->ending) {
        push_back(lst, data);
        return;
    }

    item* new_item = (item*)malloc(sizeof (item));
    new_item->data = data;
    new_item->next = prev->next;
    new_item->prev = prev;
    item* old_next = prev->next;
    old_next->prev = new_item;
    prev->next = new_item;
}

void erase(list* lst, item* prev) {
    if (prev == NULL) {
        pop_front(lst);
        return;
    }
    if (prev == lst->ending->prev) {
        pop_back(lst);
        return;
    }
    if (lst->beginning == lst->ending) {
        pop_back(lst);
        return;
    }

    item* next_item = prev->next->next;
    lst->delete_item_data(prev->next->data);
    free(prev->next);
    prev->next = next_item;
    next_item->prev = prev;
}

void* get_by_index(list* lst, int i) {
    item* itm = get_item_by_index(lst, i);
    if (itm == NULL) { return NULL; }
    return itm->data;
}

item* get_item_by_index(list* lst, int i) {
    if (i < 0 || i >= num_items(lst)) {
        return NULL;
    }
    
    int index = 0;
    for (item* it = lst->beginning; it; it = it->next) {
        if (index == i) {
            return it;
        }
        index++;
    }
    
    return NULL;
}

int num_items(list* lst) {
    int num = 0;
    
    for (item* i = lst->beginning; i; i = i->next) {
        num++;
    }
    
    return num;
}
