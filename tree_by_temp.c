#include "include/tree_by_temp.h"

void find_min_temp(TreeNode* root, double* min_temp);
void find_max_temp(TreeNode* root, double* max_temp);
void inorder_with_temp(TreeNode* node, double temp);

// Node insertion (by temp) functions with AVL balancing
TreeNode* insert_by_temp(TreeNode* root, char* date, double temp) {
    if (root == NULL) {
        return create_node(date, temp);
    }

    // Insert a node based on average temperature
    if (temp < root->averageTemp) {
        // If temp < root->averageTemp: go to left child
        root->leftNode = insert_by_temp(root->leftNode, date, temp);
    } else {
        // If temp >= root->averageTemp: go to left child
        root->rightNode = insert_by_temp(root->rightNode, date, temp);
    }

    // Update AVL height
    update_height(root);

    // Get AVL balance factor
    int balance = get_balance(root);

    // Perform rotations if unbalanced
    if (balance > 1 && temp < root->leftNode->averageTemp) {
        return rotate_right(root);
    }
    if (balance < -1 && temp > root->rightNode->averageTemp) {
        return rotate_left(root);
    }
    if (balance > 1 && temp > root->leftNode->averageTemp) {
        root->leftNode = rotate_left(root->leftNode);
        return rotate_right(root);
    }
    if (balance < -1 && temp < root->rightNode->averageTemp) {
        root->rightNode = rotate_right(root->rightNode);
        return rotate_left(root);
    }


    return root;
}

// Minimum average temperature functions
void find_days_with_min_temp(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    double min_temp = 0;
    find_min_temp(root, &min_temp);

    printf("\nΗΜΕΡΑ/ΗΜΕΡΕΣ με την ΕΛΑΧΙΣΤΗ ΜΕΣΗ ΘΕΡΜΟΚΡΑΣΙΑ (%.2lf°C):\n", min_temp);

    inorder_with_temp(root, min_temp);
}

void find_min_temp(TreeNode* root, double* min_temp) {
    if (root == NULL) {
        return;
    }

    // Go to the left-most node
    TreeNode* current = root;
    while (current->leftNode != NULL) {
        current = current->leftNode;
    }

    // Update min average temperature
    *min_temp = current->averageTemp;
}

// Maximum average temperature functions
void find_days_with_max_temp(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    double max_temp = 0;
    find_max_temp(root, &max_temp);

    printf("\nΗΜΕΡΑ/ΗΜΕΡΕΣ με τη ΜΕΓΙΣΤΗ ΜΕΣΗ ΘΕΡΜΟΚΡΑΣΙΑ (%.2lf°C):\n", max_temp);

    inorder_with_temp(root, max_temp);
}

void find_max_temp(TreeNode* root, double* max_temp) {
    if (root == NULL) {
        return;
    }

    // Go to the right-most node
    TreeNode* current = root;
    while (current->rightNode != NULL) {
        current = current->rightNode;
    }

    // Update max average temperature
    *max_temp = current->averageTemp;
}

// Function that does an in-order traversal but only prints
// the nodes that have a specific temp
void inorder_with_temp(TreeNode* node, double temp) {
    if (node == NULL) {
        return;
    }

    inorder_with_temp(node->leftNode, temp);

    if (node->averageTemp == temp)
        printf("%s\n", node->date);

    inorder_with_temp(node->rightNode, temp);
}