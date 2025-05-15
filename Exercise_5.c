#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int data;
    struct treeNode *left;
    struct treeNode *right;
} TreeNode;

// Tree functions
TreeNode* createTreeNode(int data);
TreeNode* insertSorted(TreeNode* root, int data);
void printPreorder(const TreeNode* root);
void printInorder(TreeNode* root);
void freeTree(TreeNode* root);

// Exercise-specific fuctions
TreeNode* binaryTreeSearch(TreeNode* root, int data);
void printSearchResults(const TreeNode* nodeSearch, int searchData);
void initializeTree(TreeNode** rootPtr);

int main(void) {
    TreeNode* root = NULL;
    int searchData = 100;

    // Initialize the tree with test values
    initializeTree(&root);

    // Print the tree in pre-order
    printf("BST in pre-order:\n");
    printPreorder(root);
    printf("\n");

    // Print the tree in in-order
    printf("BST in in-order:\n");
    printInorder(root);
    printf("\n");

    // Perform the search and print the output
    TreeNode* nodeSearch = binaryTreeSearch(root, 100);
    printSearchResults(nodeSearch, searchData);

    // Free the allocated memory
    freeTree(root);

    return 0;
}

// Exercise-specific fuctions
TreeNode* binaryTreeSearch(TreeNode* root, int data) {
    TreeNode* current = root;

    while (current != NULL) {
        if (current->data == data) {
            return current;
        } else if (current->data > data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL;
}

void printSearchResults(const TreeNode* nodeSearch, int searchData) {
    if (nodeSearch == NULL) {
        printf("The element %d was not found\n", searchData);
    } else {
        printf("The element %d was found\n", searchData);
    }
}

void initializeTree(TreeNode** rootPtr) {
    *rootPtr = insertSorted(*rootPtr, 3);
    insertSorted(*rootPtr, -1);
    insertSorted(*rootPtr, 4);
    insertSorted(*rootPtr, 80);
    insertSorted(*rootPtr, -90);
    insertSorted(*rootPtr, 50);
    insertSorted(*rootPtr, 10);
}

// Tree functions
TreeNode* createTreeNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode* insertSorted(TreeNode* root, int data) {
    // If the root is NULL, then create it and return it
    if (root == NULL) {
        return createTreeNode(data);
    }

    // Start at the root of the tree
    TreeNode* current = root;
    TreeNode* parent = root;

    // Traverse the tree to find insertion point
    // Note: The data is inserted in a way that the tree is a BST (Not necessary)
    while (current != NULL) {
        parent = current;

        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            printf("Duplicate value %d not inserted\n", data);
            return root;
        }
    }

    // Create the new node
    TreeNode* newNode = createTreeNode(data);
    if (newNode == NULL) {
        return NULL;
    }

    // Insert the new node at the appropriate position
    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}

void printPreorder(const TreeNode* root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->data);
    printPreorder(root->left);
    printPreorder(root->right);
}

void printInorder(TreeNode* root) {
    if(root){
        printInorder(root->left);
        printf("%i ",root->data);
        printInorder(root->right);
    }
}

void freeTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Free children first (post-order traversal)
    freeTree(root->left);
    freeTree(root->right);

    // Then free the node itself
    free(root);
}
