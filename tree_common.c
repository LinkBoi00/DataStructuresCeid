#include "include/tree_common.h"

void _inorder(TreeNode* root);
double _round_double(double num);

// Functino that allocates a new node in a tree
TreeNode* create_node(char* date, double averageTemp) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "create_node: Memory allocation failed.\n");
        return NULL;
    }

    strncpy(node->date, date, MAX_DATE_LEN - 1);
    node->date[MAX_DATE_LEN - 1] = '\0';
    node->averageTemp = _round_double(averageTemp);
    node->leftNode = NULL;
    node->rightNode = NULL;
    return node;
}

// Function that frees all nodes of a trees
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