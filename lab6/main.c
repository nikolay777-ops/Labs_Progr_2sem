#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct tree_node {
    int data;
    struct tree_node* left;
    struct tree_node* right;
} tree_node;

void check_mem_alloc(void* data) {
    if (!data) {
        fprintf(stderr, "failed to allocate memory!\n");
        exit(EXIT_FAILURE);
    }
}

tree_node* create_empty_node(int data) {
    tree_node* node = (tree_node*)malloc(sizeof(tree_node));
    check_mem_alloc((void*)node);

    node->data = data;
    node->left = node->right = NULL;
    return node;
}

void clear_tree(tree_node* root) {
    if (!root) {
        return;
    }

    clear_tree(root->left);
    clear_tree(root->right);
    free(root);
}

void add_node_to_tree(tree_node** root, tree_node* new_node) {
    if (!(*root)) {
        *root = new_node;
        return;
    }
    // если меньше - влево.
    // если больше - вправо.
    if (new_node->data > (*root)->data) {
        if (!(*root)->right) {
            (*root)->right = new_node;
        }
        else {
            add_node_to_tree(&(*root)->right, new_node);
        }
    }
    else {
        if (!(*root)->left) {
            (*root)->left = new_node;
        }
        else {
            add_node_to_tree(&(*root)->left, new_node);
        }
    }
}

void show_tree(tree_node* root) {
    if (!root) {
        return;
    }

    printf("%d ", root->data);
    show_tree(root->left);
    show_tree(root->right);
}

bool tree_contains(tree_node* root, int elem) {
    if (!root) {
        return false;
    }

    if (root->data == elem) {
        return true;
    }

    if (elem > root->data) {
        return tree_contains(root->right, elem);
    }

    return tree_contains(root->left, elem);
}

int get_height(tree_node* root) {
    if (!root) {
        return 0;
    }

    int left_height = get_height(root->left);
    int right_height = get_height(root->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

bool tree_is_balanced(tree_node* root) {
    int left_height;
    int right_height;

    if (root == NULL) {
        return true;
    }

    left_height = get_height(root->left);
    right_height = get_height(root->right);

    if (abs(left_height - right_height) <= 1
            && tree_is_balanced(root->left)
            && tree_is_balanced(root->right)) {
        return true;
    }

    return false;
}

int main() {
    tree_node* root = NULL;

    while (true) {
        puts("Enter an integer. Enter 0 to finish: ");
        int n = 0;

        while (scanf("%d", &n) != 1 || tree_contains(root, n)) {
            puts("Incorrect input. Please try again:");
            getchar();
        }

        if (!n) { break; }

        add_node_to_tree(&root, create_empty_node(n));
    }

    show_tree(root);
    puts("");

    if (tree_is_balanced(root)) {
        puts("\nThis tree is balanced");
    }
    else {
        puts("\nThis tree is not balanced");
    }

    clear_tree(root);

    return 0;
}
