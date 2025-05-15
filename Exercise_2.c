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

void initializeLists(List* list1, List* list2);
Node* sortedMerge(Node* head1, Node* head2);

int main(void) {
    List* list1 = createList();
    List* list2 = createList();

    // Initialize the two lists with test values
    initializeLists(list1, list2);

    // Print the two sorted lists
    printf("The first sorted list (list1) is:\n");
    printList(list1->head);
    printf("The second sorted list (list2) is:\n");
    printList(list2->head);

    // Merge the two sorted lists
    printf("Merging list1 with list2...\n");
    Node* mergedNode = sortedMerge(list1->head, list2->head);

    // Print the merged list
    printf("Modified (merged) list:\n");
    printList(mergedNode);

    // Since list1 is the concatenated list, free it and all nodes
    // and then free list2
    freeList(list1);
    free(list2);

    return 0;
}

/*
 * Function that initializes the two lists we use
 * Returns: Void
 */
void initializeLists(List* list1, List* list2) {
    insert_at_end(list1, 2);
    insert_at_end(list1, 6);
    insert_at_end(list1, 11);
    insert_at_end(list1, 99);
    insert_at_end(list1, 101);

    insert_at_end(list2, -1);
    insert_at_end(list2, 15);
    insert_at_end(list2, 30);
    insert_at_end(list2, 900);
}

/*
 * Function to merge two sorted lists together while keeping them sorted
 * Returns: Pointer to the head Node of the new merged list
 */
Node* sortedMerge(Node* head1, Node* head2) {
    Node tempNode;
    Node* mergedtail = &tempNode;
    tempNode.next = NULL;

    // Iterate through both lists and build up the merged list
    while (head1 != NULL && head2 != NULL) {
        if (head1->data <= head2->data) {
            mergedtail->next = head1;
            head1 = head1->next;
        } else {
            mergedtail->next = head2;
            head2 = head2->next;
        }
        mergedtail = mergedtail->next;
    }

    // Attach the remaining nodes of head1 or head2
    if (head1 != NULL) {
        mergedtail->next = head1;
    } else {
        mergedtail->next = head2;
    }

    // Return the merged list (skip the temp node)
    return tempNode.next;
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
