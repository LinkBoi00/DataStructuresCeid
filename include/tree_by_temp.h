#ifndef TREE_BY_TEMP_H
#define TREE_BY_TEMP_H

#include "tree_common.h"

TreeNode* insert_by_temp(TreeNode* root, char* date, double temp);
void find_days_with_min_temp(TreeNode* root);
void find_days_with_max_temp(TreeNode* root);

#endif
