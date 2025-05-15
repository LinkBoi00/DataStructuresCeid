#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES_COUNT 256

typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} TreeNode;

// Tree functions
TreeNode* createTreeNode(char data);
void printPreorder(const TreeNode* root);
void printInorder(TreeNode* root);
void freeTree(TreeNode* root);

// Excercise-specific functions
TreeNode* buildTree(char* inorder, char* levelorder, int inSize);
int findCharIndex(char* arr, int size, char target);
void readUserInput(char* string);
void clearStdin(void);

int main(void) {
    TreeNode* root = NULL;
    char in_order[MAX_NODES_COUNT];
    char level_order[MAX_NODES_COUNT];

    printf("Input the in-order traversal: ");
    readUserInput(in_order);

    printf("Input the level-order traversal: ");
    readUserInput(level_order);

    printf("In-order: %s\n", in_order);
    printf("Level-order: %s\n", level_order);

    root = buildTree(in_order, level_order, strlen(in_order));
    printf("\nBuilt tree's in-order traversal: ");
    printInorder(root);
    printf("\n");

    // Free the allocated memory
    freeTree(root);

    return 0;
}

// Exercise-specific functions
TreeNode* buildTree(char* inorder, char* levelorder, int inSize) {
    int rootIndex, leftSize, rightSize;
    char* leftIn;
    char* rightIn;

    if (inSize == 0) return NULL;

    // The first element of the level order is the root
    TreeNode* root = createTreeNode(levelorder[0]);
    if (root == NULL) {
        printf("Root is NULL.\n");
        return NULL;
    }

    if (inSize == 1) return root; // Trivial case

    rootIndex = findCharIndex(inorder, inSize, levelorder[0]);

    leftIn = inorder;
    leftSize = rootIndex;

    rightIn = inorder + rootIndex + 1;
    rightSize = inSize - rootIndex - 1;

    char* leftLevel = malloc(leftSize * sizeof(char));
    char* rightLevel = malloc(rightSize * sizeof(char));

    int leftCount = 0, rightCount = 0;
    for (int i = 1; i < inSize; ++i) {
        if (findCharIndex(leftIn, leftSize, levelorder[i]) != -1)
            leftLevel[leftCount++] = levelorder[i];
        else
            rightLevel[rightCount++] = levelorder[i];
    }

    root->left = buildTree(leftIn, leftLevel, leftSize);
    root->right = buildTree(rightIn, rightLevel, rightSize);

    free(leftLevel);
    free(rightLevel);
    return root;
}

int findCharIndex(char* arr, int size, char target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

void readUserInput(char* string) {
    int ch, i = 0;

    // Put the input's characters in the array
    while ((ch = getchar()) != '\n' && ch != EOF && i < MAX_NODES_COUNT - 1) {
        if (ch == ' ') continue; // Ignore spaces
        string[i++] = (char)ch;
    }
    string[i] = '\0';

    // If there are leftover characters, clean them up
    if (i - 1 > MAX_NODES_COUNT) {
        printf("Warning: Leftover characters will be ignored.\n");
        clearStdin();
    }
}

void clearStdin(void) {
    int ch;
    while ((ch = getchar()) != EOF && ch != '\n');
}

// Tree functions
TreeNode* createTreeNode(char data) {
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

void printPreorder(const TreeNode* root) {
    if (root == NULL) {
        return;
    }

    printf("%c ", root->data);
    printPreorder(root->left);
    printPreorder(root->right);
}

void printInorder(TreeNode* root) {
    if(root){
        printInorder(root->left);
        printf("%c ",root->data);
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
