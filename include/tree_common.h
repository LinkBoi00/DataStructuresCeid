#ifndef TREE_COMMON_H
#define TREE_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATE_LEN 11  // YYYY-MM-DD plus NULL string terminator

typedef struct TreeNode {
    char date[MAX_DATE_LEN];
    double averageTemp;
    struct TreeNode *leftNode;
    struct TreeNode *rightNode;
} TreeNode;

TreeNode* create_node(char* date, double averageTemp);
void free_tree(TreeNode* root);
void print_tree_inorder(TreeNode* root);

#endif