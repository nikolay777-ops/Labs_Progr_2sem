#ifndef MENU_H
#define MENU_H

#include "list.h"

typedef void(* func)();
typedef char punct[150];

typedef struct {
    list* functions;
    list* puncts;
} menu;

void* create_function(func f);
void* create_function_copy(void* ptr_to_f);
void* create_punct(const char* p);
menu* create_menu(list* functions, list* puncts);
void delete_menu(menu* m);
void execute_menu(menu* m);

#endif // MENU_H
