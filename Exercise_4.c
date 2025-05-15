#include <stdio.h>
#include <stdlib.h>

// Node struct
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Linked list struct
typedef struct List {
    Node* head;
    Node* tail;
} List;

Node* createNode(int data);
List* createList();
void insert_at_end(List* list, int data);
void printList(const Node* node);
void freeList(List* list);

int askUserInput(void);
void printSearchResult(const Node* nodeResult);
void initializeList(List* list);
Node* searchRecursive(Node* node, int data);

int main() {
    int input = 0;

    // Create a list and fill it with test values
    List* list = createList();
    initializeList(list);

    // Print the list
    printList(list->head);

    // Get user input
    input = askUserInput();
    Node* node = searchRecursive(list->head, input);

    // Print recursive search result
    printSearchResult(node);

    // Free list
    freeList(list);

    return 0;
}

/*
 * Function that initializes the two lists we use
 * Returns: Void
 */
void initializeList(List* list) {
    insert_at_end(list, 2);
    insert_at_end(list, 6);
    insert_at_end(list, 11);
    insert_at_end(list, -1);
    insert_at_end(list, 99);
    insert_at_end(list, 33);
    insert_at_end(list, -90);
    insert_at_end(list, 1);
}

/*
 * Function that asks the user for an integer to search if it exists in the list
 * Returns: Integer value that was inputted
 */
int askUserInput(void) {
    int userInput = 0;

    printf("Please enter an integer to search in the list: ");
    scanf("%d", &userInput);

    return userInput;
}

/*
 * Function that performs a recursive search for a value (data) in a list's nodes
 * Returns: Pointer to the matching Node, or NULL if there is no match
 */
Node* searchRecursive(Node* node, int data) {
    // Base case: Reached end of list
    if (node == NULL) {
        return NULL;
    }

    // Target value is found
    if (node->data == data) {
        return node;
    }

    // Target value not found, so continue searching
    return searchRecursive(node->next, data);
}

/*
 * Function that prints whether the search for the value was successful
 * Returns: Void
 */
void printSearchResult(const Node* nodeResult) {
    if (nodeResult == NULL) {
        printf("The value does not exist in the list.\n");
    } else {
        printf("The value exists in the list.\n");
    }
}

/*
 * Function that creates a new Node with the given data
 * Returns: Pointer to the newly-created Node, or NULL in case of malloc error
 */
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("createNode: Memory allocation error");
        return NULL;
    }

    node->data = data;
    node->next = NULL;
    return node;
}

/*
 * Function that creates an new empty List
 * Returns: Pointer to the newly-created List, or NULL in case of malloc error
 */
List* createList() {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) {
        printf("createList: Memory allocation error");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    return list;
}

/*
 * Function that inserts an element (data) at the end of a given List
 * Returns: Void
 */
void insert_at_end(List* list, int data) {
    if (list == NULL) {
        printf("insert_at_end: List is NULL\n");
        return;
    }

    // Create new node
    Node* new_node = createNode(data);
    if (new_node == NULL) {
        printf("insert_at_end: Failed to create new node\n");
        return;
    }

    if (list->head == NULL) {
        // If the list is empty: Make the new node
        // both the head and the tail of the list
        list->head = new_node;
        list->tail = new_node;
    } else {
        // If list is not empty: Insert the new node after the current tail
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

/*
 * Function that prints a list starting from a given Node
 * Returns: Void
 */
void printList(const Node* node) {
    if (node == NULL) {
        printf("printList: Node is NULL\n");
        return;
    }

    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }

    printf("\n");
}

/*
 * Function that frees a list and all its nodes
 * Returns: Void
 */
void freeList(List* list) {
    if (list == NULL) {
        return;
    }

    // Free the nodes
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    // Free the list
    free(list);
}
