#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int data;
    struct treeNode *left;
    struct treeNode *right;
} TreeNode;

typedef struct queueNode {
    TreeNode* data;
    struct queueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* head;
    QueueNode* rear;
} Queue;

// Tree functions
TreeNode* createTreeNode(int data);
TreeNode* insertSorted(TreeNode* root, int data);
void printPreorder(const TreeNode* root);
void printInorder(TreeNode* root);
void freeTree(TreeNode* root);

// Queue functions
Queue* createQueue();
void enqueue(Queue* queue, TreeNode* node);
TreeNode* dequeue(Queue* queue);
int isQueueEmpty(Queue* q);

// Exercise-specific functions
void initializeTree(TreeNode** rootPtr);
void levelOrder(TreeNode* root);

int main(void) {
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

    // Print the tree with level order
    printf("BST in level-order:\n");
    levelOrder(root);
    printf("\n");

    // Free the allocated memory
    freeTree(root);

    return 0;
}

// Exercise-specific functions
void levelOrder(TreeNode* root) {
    if (root == NULL) {
        printf("levelOrder: Tree is empty.\n");
        return;
    }

    // Create a queue and insert the root
    Queue* queue = createQueue();
    enqueue(queue, root);

    // While the queue isn't empty:
    while (!isQueueEmpty(queue)) {
        // Get the next TreeNode in the queue with dequeue
        TreeNode* current = dequeue(queue);
        printf("%i ", current->data);

        // Insert the appropriate TreeNode to the queue
        if (current->left != NULL) {
            enqueue(queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(queue, current->right);
        }
    }

    free(queue);
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

// Queue functions
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    queue->head = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, TreeNode* node) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = node;
    newNode->next = NULL;

    // If the tail is NULL, set both the head and the tail to newNode
    if (queue->rear == NULL) {
        queue->head = queue->rear = newNode;
        return;
    }

    // Both rear and head aren't NULL so append newNode to the tail of the Queue
    queue->rear->next = newNode;
    queue->rear = newNode;
}

TreeNode* dequeue(Queue* queue) {
    if (queue->head == NULL)
        return NULL;

    QueueNode* tempQueue = queue->head;
    TreeNode* tempData = tempQueue->data;

    queue->head = queue->head->next;
    if (queue->head == NULL) {
        queue->rear = NULL;
    }

    free(tempQueue);
    return tempData;
}

int isQueueEmpty(Queue* q) {
    return q->head == NULL;
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
