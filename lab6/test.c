#include <stdio.h>
#include <assert.h>

#include "main.h"

void test_create_empty_node() {
    tree_node* en = create_empty_node(5);
    
    assert(en);
    assert(en->data == 5);
    assert(!en->left && !en->right);
    
    clear_tree(en);
}

void test_add_node_to_tree() {
    tree_node* root = NULL;
    add_node_to_tree(&root, create_empty_node(60));
    
    assert(root);
    assert(root->data == 60);
    assert(!root->left && !root->right);
    
    add_node_to_tree(&root, create_empty_node(80));
    assert(root->right->data == 80);
    
    add_node_to_tree(&root, create_empty_node(30));
    assert(root->left->data == 30);
    
    add_node_to_tree(&root, create_empty_node(20));
    assert(root->left->left->data == 20);
    
    clear_tree(root);
}

void test_tree_contains() {
    tree_node* root = NULL;
    
    assert(!tree_contains(root, 4));
    
    add_node_to_tree(&root, create_empty_node(50));
    add_node_to_tree(&root, create_empty_node(60));
    add_node_to_tree(&root, create_empty_node(70));
    add_node_to_tree(&root, create_empty_node(80));
    add_node_to_tree(&root, create_empty_node(30));
    add_node_to_tree(&root, create_empty_node(40));
    add_node_to_tree(&root, create_empty_node(22));
    add_node_to_tree(&root, create_empty_node(32));
    add_node_to_tree(&root, create_empty_node(11));
    
    assert(tree_contains(root, 50));
    assert(tree_contains(root, 60));
    assert(!tree_contains(root, 24));
    assert(!tree_contains(root, 12));
    
    clear_tree(root);
}

void test_get_height() {
    tree_node* root = NULL;
    
    assert(get_height(root) == 0);
    add_node_to_tree(&root, create_empty_node(500));
    assert(get_height(root) == 1);
    add_node_to_tree(&root, create_empty_node(600));
    assert(get_height(root) == 2);
    add_node_to_tree(&root, create_empty_node(700));
    assert(get_height(root) == 3);
    add_node_to_tree(&root, create_empty_node(400));
    assert(get_height(root) == 3);
    
    clear_tree(root);
}

void test_tree_is_balanced() {
    tree_node* root = NULL;
    
    add_node_to_tree(&root, create_empty_node(333));
    add_node_to_tree(&root, create_empty_node(222));
    add_node_to_tree(&root, create_empty_node(111));
    add_node_to_tree(&root, create_empty_node(230));
    add_node_to_tree(&root, create_empty_node(444));
    add_node_to_tree(&root, create_empty_node(400));
    add_node_to_tree(&root, create_empty_node(555)); 
    
    assert(tree_is_balanced(root));
    add_node_to_tree(&root, create_empty_node(666));
    assert(tree_is_balanced(root));
    add_node_to_tree(&root, create_empty_node(1000));
    assert(!tree_is_balanced(root));
    
    clear_tree(root);
}

#undef main
int main() {
    test_create_empty_node();
    test_add_node_to_tree();
    test_tree_contains();
    test_get_height();
    test_tree_is_balanced();
    
    puts("Tests passed successfully");
    
    return 0;
}
