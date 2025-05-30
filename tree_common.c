#include "include/tree_common.h"

void _inorder(TreeNode* root);
double _round_double(double num);
int _max(int a, int b);

// Function that allocates a new node in a tree
TreeNode* create_node(char* date, double averageTemp) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "create_node: Memory allocation failed.\n");
        return NULL;
    }

    strncpy(node->date, date, MAX_DATE_LEN - 1);
    node->date[MAX_DATE_LEN - 1] = '\0';
    node->averageTemp = _round_double(averageTemp);
    node->height = 1;
    node->leftNode = NULL;
    node->rightNode = NULL;
    return node;
}

// Function that frees all nodes of a tree
void free_tree(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    free_tree(root->leftNode);
    free_tree(root->rightNode);

    free(root);
}

// Function that prints an in-order traversal of a tree
void print_tree_inorder(TreeNode* root) {
    printf("\nΕνδο-διατεταγμένη διαπέραση:\n");
    printf("ΗΜΕΡΟΜΗΝΙΑ \t | ΜΕΣΗ ΘΕΡΜΟΚΡΑΣΙΑ\n");
    printf("-----------------|-----------------\n");

    _inorder(root);
}

void _inorder(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Visit the left subtree first
    _inorder(root->leftNode);

    // Print the node data
    printf("%s \t | %.2lf\n", root->date, root->averageTemp);

    // Visit the right subtree now
    _inorder(root->rightNode);
}

// Helper function that rounds a double number to the 2nd decimal point
double _round_double(double num) {
    if (num >= 0)
        return (int)(num * 100.0 + 0.5) / 100.0;
    else
        return (int)(num * 100.0 - 0.5) / 100.0;
}

// AVL tree specific: Get height of a node
int get_height(TreeNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// AVL tree specific: Get balance factor of a node
int get_balance(TreeNode* node) {
    if (node == NULL)
        return 0;
    return get_height(node->leftNode) - get_height(node->rightNode);
}

// AVL tree specific: Update height of a node
void update_height(TreeNode* node) {
    if (node != NULL) {
        node->height = 1 + _max(get_height(node->leftNode), get_height(node->rightNode));
    }
}

// AVL tree specific: Right rotate
TreeNode* rotate_right(TreeNode* y) {
    TreeNode* x = y->leftNode;
    TreeNode* temp = x->rightNode;

    // Perform rotation
    x->rightNode = y;
    y->leftNode = temp;

    // Update heights
    update_height(y);
    update_height(x);

    // Return new root
    return x;
}

// AVL tree specific: Left rotate
TreeNode* rotate_left(TreeNode* x) {
    TreeNode* y = x->rightNode;
    TreeNode* temp = y->leftNode;

    // Perform rotation
    y->leftNode = x;
    x->rightNode = temp;

    // Update heights
    update_height(x);
    update_height(y);

    // Return new root
    return y;
}

// Helper function to get maximum of two integers
int _max(int a, int b) {
    return (a > b) ? a : b;
}