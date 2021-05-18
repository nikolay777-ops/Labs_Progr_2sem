#include "menu.h"

void* create_function(func f) {
    func* ptr_to_f = malloc(sizeof(func));
    check_mem_alloc(ptr_to_f);
    *ptr_to_f = f;
    return (void*)ptr_to_f;
}

void* create_function_copy(void* ptr_to_f) {
    func* f = (func*)ptr_to_f;
    return create_function(*f);
}

void* create_punct(const char* p) {
    return (void*)strdup(p);
}

menu* create_menu(list* functions, list* puncts) {
    menu* m = (menu*)malloc(sizeof(menu));
    check_mem_alloc(m);
    m->functions = create_list_copy(functions);
    m->puncts = create_list_copy(puncts);
    return m;
}

// LCOV_EXCL_START
void delete_menu(menu* m) {
    delete_list(m->functions);
    delete_list(m->puncts);
    free(m);
}
// LCOV_EXCL_STOP

void execute_menu(menu* m) {
    while (true) {
        int n = 1;
        
        for (item* i = m->puncts->beginning; i; i = i->next) {
            const char* current_punct = (const char*)i->data;
            char line[200];
            sprintf(line, "%d: %s", n, current_punct);
            puts(line);
            n++;
        }
        puts("0. Back");
        
        int choice;
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > num_items(m->puncts)) {
            puts("Please enter a valid number");
            clear();
        }
        
        clear();
        choice--;
        
        if (choice == -1) {
            break;
        }
        
        func* f = (func*)get_by_index(m->functions, choice);
        (*f)();
    }
}
