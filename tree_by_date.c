#include "include/tree_by_date.h"

TreeNode* _binarySearch(TreeNode* root, char* date);
TreeNode* _delete_node(TreeNode* root, char* date);
TreeNode* _find_min_node(TreeNode* node);

// Node insertion (by date) functions with AVL balancing
TreeNode* insert_by_date(TreeNode* root, char* date, double temp) {
    // Step 1: Perform normal BST insertion
    if (root == NULL) {
        return create_node(date, temp);
    }
    
    int cmp = strcmp(date, root->date);
    if (cmp < 0) {
        root->leftNode = insert_by_date(root->leftNode, date, temp);
    } else if (cmp > 0) {
        root->rightNode = insert_by_date(root->rightNode, date, temp);
    } else {
        // Equal dates, don't insert duplicate
        return root;
    }
    
    // Step 2: Update height of current node
    update_height(root);
    
    // Step 3: Get the balance factor
    int balance = get_balance(root);
    
    // Step 4: Perform rotations if unbalanced
    
    // Left Left Case
    if (balance > 1 && strcmp(date, root->leftNode->date) < 0) {
        return rotate_right(root);
    }
    
    // Right Right Case
    if (balance < -1 && strcmp(date, root->rightNode->date) > 0) {
        return rotate_left(root);
    }
    
    // Left Right Case
    if (balance > 1 && strcmp(date, root->leftNode->date) > 0) {
        root->leftNode = rotate_left(root->leftNode);
        return rotate_right(root);
    }
    
    // Right Left Case
    if (balance < -1 && strcmp(date, root->rightNode->date) < 0) {
        root->rightNode = rotate_right(root->rightNode);
        return rotate_left(root);
    }
    
    // Return unchanged root
    return root;
}

// Node searching functions
TreeNode* search_by_date(TreeNode* root) {
    TreeNode* node;
    char date[MAX_DATE_LEN] = {0};

    scanf("%19s", date);

    if ((node = _binarySearch(root, date)) != NULL) {
        printf("Η αναζήτηση ήταν επιτυχής.\n");
        printf("Η ΜΕΣΗ ΘΕΡΜΟΚΡΑΣΙΑ είναι: %.2lf.\n", node->averageTemp);
        return node;
    } else {
        printf("Η αναζήτηση ήταν ανεπιτυχής.\n");
        printf("Δεν βρέθηκαν δεδομένα για τη δοσμένη ΗΜΕΡΑ.\n");
        return NULL;
    }
}

TreeNode* _binarySearch(TreeNode* root, char* date) {
    if (root == NULL) {
        return NULL;
    }

    int cmp = strcmp(date, root->date);
    if (cmp == 0) {
        return root;
    }
    if (cmp < 0) {
        return _binarySearch(root->leftNode, date);
    }

    return _binarySearch(root->rightNode, date);
}

// Node temperature editing functions
void edit_temperature_by_date(TreeNode* root) {
    // Perform binary search to check if the entry exists
    TreeNode* node = search_by_date(root);
    if (node == NULL) {
        return;
    }

    // If it exists, prompt the user to enter the new average temperature
    printf("Εισάγετε νέα τιμή για τη ΜΕΣΗ ΘΕΡΜΟΚΡΑΣΙΑ: ");
    double new_temp = 0.0;
    scanf("%lf", &new_temp);

    node->averageTemp = new_temp;
}

// Helper function to find the minimum node in a subtree
TreeNode* _find_min_node(TreeNode* node) {
    TreeNode* current = node;
    while (current->leftNode != NULL) {
        current = current->leftNode;
    }
    return current;
}

// Node deletion function with AVL balancing
TreeNode* delete_by_date(TreeNode* root) {
    char date[MAX_DATE_LEN] = {0};
    scanf("%19s", date);
    return _delete_node(root, date);
}

TreeNode* _delete_node(TreeNode* root, char* date) {
    // Step 1: Perform standard BST delete
    if (root == NULL) {
        printf("Δεν βρέθηκε εγγραφη για τη συγκεκριμενη ΗΜΕΡΑ.\n");
        return root;
    }

    int cmp = strcmp(date, root->date);
    if (cmp < 0) {
        root->leftNode = _delete_node(root->leftNode, date);
    } else if (cmp > 0) {
        root->rightNode = _delete_node(root->rightNode, date);
    } else {
        // This is the node to be deleted
        printf("H εγγραφη διαγράφηκε επιτυχώς.\n");
        
        if (root->leftNode == NULL || root->rightNode == NULL) {
            TreeNode* temp = root->leftNode ? root->leftNode : root->rightNode;
            
            if (temp == NULL) {
                // No child case
                temp = root;
                root = NULL;
            } else {
                // One child case
                *root = *temp;
            }
            free(temp);
        } else {
            // Node with two children
            TreeNode* temp = _find_min_node(root->rightNode);
            
            // Copy the inorder successor's data to this node
            strcpy(root->date, temp->date);
            root->averageTemp = temp->averageTemp;
            
            // Delete the inorder successor
            root->rightNode = _delete_node(root->rightNode, temp->date);
        }
    }
    
    // If the tree had only one node then return
    if (root == NULL) {
        return root;
    }
    
    // Step 2: Update height of current node
    update_height(root);
    
    // Step 3: Get the balance factor
    int balance = get_balance(root);
    
    // Step 4: Perform rotations if unbalanced
    
    // Left Left Case
    if (balance > 1 && get_balance(root->leftNode) >= 0) {
        return rotate_right(root);
    }
    
    // Left Right Case
    if (balance > 1 && get_balance(root->leftNode) < 0) {
        root->leftNode = rotate_left(root->leftNode);
        return rotate_right(root);
    }
    
    // Right Right Case
    if (balance < -1 && get_balance(root->rightNode) <= 0) {
        return rotate_left(root);
    }
    
    // Right Left Case
    if (balance < -1 && get_balance(root->rightNode) > 0) {
        root->rightNode = rotate_right(root->rightNode);
        return rotate_left(root);
    }
    
    return root;
}