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

// Exercise-specific functions
int height(TreeNode* root);
void initializeTree(TreeNode** rootPtr);

int main(void) {
    int treeHeight = -1;
    TreeNode* root = NULL;

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

    // Find the height of the tree
    treeHeight = height(root);
    printf("The tree's height is: %d\n", treeHeight);

    // Free the allocated memory
    freeTree(root);

    return 0;
}

// Exercise-specific functions
int height(TreeNode* root) {
    // Base case: Empty tree
    if (root == NULL) {
        return -1;
    }

    // Recursively find height of left and right subtrees
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    // Return the larger height + 1 (for the current node)
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
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
