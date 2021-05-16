#include <assert.h>

#include "application.h"
#include "check.h"
#include "crime.h"
#include "criminal.h"
#include "list.h"
#include "menu.h"
#include "organization.h"

// list testing ////////////////////////////////////

void* create_int(int a) {
    int* ptr = malloc(sizeof(int));
    *ptr = a;
    return ptr;
}

void* create_int_copy(void* a) {
    void* copy = malloc(sizeof(int));
    check_mem_alloc(copy);
    *((int*)copy) = *((int*)a);
    return copy;
}

void test_create_push_delete_list() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    check_mem_alloc(example);
    delete_list(example);
    
    example = create_list(sizeof(int), free, create_int_copy);
    push_back(example, create_int(60));
    int* data_ptr = example->beginning->data;
    assert(*data_ptr == 60);
    
    push_back(example, create_int(60));
    data_ptr = example->beginning->next->data;
    assert(*data_ptr == 60);
    
    delete_list(example);
}

void test_create_list_copy() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_back(example, create_int(65));
    push_back(example, create_int(60));
    
    list* example_copy = create_list_copy(example);
    
    int* data_ptr = example_copy->beginning->data;
    assert(*data_ptr == 65);
    
    delete_list(example_copy);
    delete_list(example);
}

void test_get_by_index() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_back(example, create_int(65));
    push_back(example, create_int(60));
    
    assert(*((int*)get_by_index(example, 0)) == *((int*)example->beginning->data));
    
    delete_list(example);
}

void test_get_item_by_index() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_back(example, create_int(65));
    push_back(example, create_int(60));
    
    item* i = get_item_by_index(example, 0);
    int* data = i->data;
    
    assert(*data == *((int*)example->beginning->data));
    
    delete_list(example);
}

void test_push_front() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_front(example, create_int(65));
    push_front(example, create_int(60));
    
    assert(*((int*)example->beginning->data) == 60);
    assert(*((int*)example->beginning->next->data) == 65);
    
    delete_list(example);
}

void test_num_items() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_back(example, create_int(65));
    push_back(example, create_int(60));
    
    assert(num_items(example) == 2);
    
    delete_list(example);
}

void test_pop_back() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_back(example, create_int(65));
    push_back(example, create_int(60));
    assert(num_items(example) == 2);
    
    pop_back(example);
    assert(num_items(example) == 1);
    assert(*((int*)example->beginning->data) == 65);
    
    delete_list(example);
}

void test_pop_front() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_back(example, create_int(60));
    push_back(example, create_int(65));
    assert(num_items(example) == 2);
    
    pop_front(example);
    assert(num_items(example) == 1);
    assert(*((int*)example->beginning->data) == 65);
    
    delete_list(example);
}

void test_insert() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_back(example, create_int(65));
    push_back(example, create_int(60));
    
    insert(example, example->beginning, create_int(100));
    
    assert(num_items(example) == 3);
    assert(*((int*)example->beginning->next->data) == 100);
    
    delete_list(example);
}

void test_erase() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_back(example, create_int(65));
    push_back(example, create_int(60));

    erase(example, example->beginning);
    assert(num_items(example) == 1);
    assert(*((int*)example->beginning->data) == 65);
    
    delete_list(example);
}

// end of list testing /////////////////////////////

// check testing ///////////////////////////////////
// I don't know how to test error(), check_mem_alloc(), clear() and check()

void test_fgets_without_newline() {
    FILE* estream = fopen("test_text.txt", "w");
    fputs("example example\n\n\n\n\n", estream);
    fclose(estream);
    
    estream = fopen("test_text.txt", "r");
    char str[200];
    fgets_without_newline(str, 200, estream);
    fclose(estream);
    
    assert(str[strlen(str) - 1] != '\n');
    remove("test_text.txt");
}

void test_fputs_with_newline() {
    FILE* estream = fopen("test_text.txt", "w");
    fputs_with_newline("mda", estream);
    fclose(estream);
    
    estream = fopen("test_text.txt", "r");
    fgetc(estream); fgetc(estream); fgetc(estream);
    assert(fgetc(estream) == '\n');
    fclose(estream);
    
    remove("test_text.txt");
}

void test_tolower_str() {
    char str[200] = "WHERE BANANA";
    tolower_str(str);
    assert(!strcmp(str, "where banana"));
}

// end of check testing ////////////////////////////

#undef main
int main() {
    test_create_push_delete_list();
    test_create_list_copy();
    test_get_by_index();
    test_get_item_by_index();
    test_push_front();
    test_num_items();
    test_pop_back();
    test_pop_front();
    test_insert();
    test_erase();
    
    test_fgets_without_newline();
    test_fputs_with_newline();
    test_tolower_str();
    
    puts("All tests passed");
    
    return 0;
}
