#include "include/tree_by_date.h"

TreeNode* _binarySearch(TreeNode* root, char* date);
TreeNode* _delete_node(TreeNode* root, char* date);

// Node insertion (by date) functions
TreeNode* insert_by_date(TreeNode* root, char* date, double temp) {
    if (root == NULL) {
        return create_node(date, temp);
    }
    
    // Insert a node based on its date
    int cmp = strcmp(date, root->date);
    if (cmp < 0) {
        // If date < root->date: go to the left child
        root->leftNode = insert_by_date(root->leftNode, date, temp);
    } else if (cmp > 0) {
        // If date > root->date: go to the right child
        root->rightNode = insert_by_date(root->rightNode, date, temp);
    }
    
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

// Node deletion function
TreeNode* delete_by_date(TreeNode* root) {
    TreeNode* node;
    char date[MAX_DATE_LEN] = {0};

    scanf("%19s", date);

    node = _delete_node(root, date);
    return node;
}

TreeNode* _delete_node(TreeNode* root, char* date) {
    if (root == NULL) {
        printf("Δεν βρέθηκε εγγραφη για τη συγκεκριμενη ΗΜΕΡΑ.\n");
        return NULL;
    }

    // Travel through the BST in a binarySearch-like pattern
    int cmp = strcmp(date, root->date);
    if (cmp < 0) {
        root->leftNode = _delete_node(root->leftNode, date);
    } else if (cmp > 0) {
        root->rightNode = _delete_node(root->rightNode, date);
    } else {
        // This node should be deleted
        if (root->leftNode == NULL && root->rightNode == NULL) {
            // Case 1: No children
            free(root);
            printf("H εγγραφη διαγράφηκε επιτυχώς.\n");
            return NULL; 
        } else if (root->leftNode == NULL) {
            // Case 2: One child (right)
            TreeNode* temp = root->rightNode;
            free(root);
            printf("H εγγραφη διαγράφηκε επιτυχώς.\n");
            return temp;
        } else if (root->rightNode == NULL) {
            // Case 2: One child (left)
            TreeNode* temp = root->leftNode;
            free(root);
            printf("H εγγραφη διαγράφηκε επιτυχώς.\n");
            return temp;
        } else {
            // Case 3: Two children (Find the inorder successor)
            TreeNode* successor = root->rightNode;
            while (successor->leftNode != NULL)
                successor = successor->leftNode;

            strcpy(root->date, successor->date);
            root->averageTemp = successor->averageTemp;
            root->rightNode = _delete_node(root->rightNode, successor->date);
            printf("H εγγραφη διαγράφηκε επιτυχώς.\n");
        }
    }
    
    return root;
}