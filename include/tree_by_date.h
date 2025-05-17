#ifndef TREE_BY_DATE_H
#define TREE_BY_DATE_H

#include "tree_common.h"

TreeNode* insert_by_date(TreeNode* root, char* date, double temp);
TreeNode* search_by_date(TreeNode* root);
void edit_temperature_by_date(TreeNode* root);
TreeNode* delete_by_date(TreeNode* root);

#endif