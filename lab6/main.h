#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct tree_node {
    int data;
    struct tree_node* left;
    struct tree_node* right;
} tree_node;

tree_node* create_empty_node(int data);
void clear_tree(tree_node* root);
void add_node_to_tree(tree_node** root, tree_node* new_node);
void show_tree(tree_node* root);
bool tree_contains(tree_node* root, int elem);
int get_height(tree_node* root);
bool tree_is_balanced(tree_node* root);

void check_mem_alloc(void* data);

#endif // MAIN_H
