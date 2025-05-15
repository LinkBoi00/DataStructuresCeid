#include <stdio.h>
#include <stdlib.h>

// Stack struct
typedef struct Stack {
    char* data;
    int sp;
    int total_capacity;
} Stack;

Stack* createStack(int capacity);
void push(Stack* stack, char content);
char pop(Stack* stack);
int isEmpty(Stack* stack);
void freeStack(Stack* stack);

int my_strlen(char* str);
int isPalindrome(char* str);

int main() {

    char* testStr = "aaa";
    printf("Is the string %s palindrome? %d\n", testStr, isPalindrome(testStr));

    char* testStr2 = "hello";
    printf("Is the string %s palindrome? %d\n", testStr2, isPalindrome(testStr2));

    char* testStr3 = "acaca";
    printf("Is the string %s palindrome? %d\n", testStr3, isPalindrome(testStr3));

    return 0;
}

/* Function that checks if a string is a palindrome
 * Returns: 1 if it's a palindrome and 0 if it isn't
 */
int isPalindrome(char* str) {
    int i;
    char c;

    if (str == NULL) {
        printf("isPalindrome: Input string is NULL.\n");
        return 0;
    }

    // Create the stack
    int len = my_strlen(str);
    if (len == 0) return 0;     // Trivial case: String is empty so there aren't any counterexamples

    Stack* stack = createStack(len);
    if (!stack) {
        printf("isPalindrome: Failed to create stack.\n");
        return 0;
    }

    // Push all characters into the stack
    for (i = 0; i < len; i++) {
        push(stack, str[i]);
    }

    // Compare by popping from stack
    for (i = 0; i < len; i++) {
        c = pop(stack);
        if (c != str[i]) {
            freeStack(stack);
            return 0;
        }
    }

    freeStack(stack);
    return 1;
}

/* Function that counts the length of a string
 * Returns: Number of readable characters (Int)
 */
int my_strlen(char* str) {
    if (str == NULL) {
        printf("my_strlen: Input string is NULL.\n");
        return -1;
    }

    int len = 0;
    while(str[len] != '\0'){
        len++; // Ignore '\0' at the end
    }

    return len;
}

/*
 * Function that allocates the needed memory for a stack and its data
 * Returns: Pointer to the newly created stack
 */
Stack* createStack(int capacity) {
    if (capacity <= 0) {
        printf("createStack: Capacity parameter is invalid.\n");
        return NULL;
    }

    // Allocate memory for the stack structure
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("createStack: Error allocating memory for stack.\n");
        return NULL;
    }

    // Initialize the stack pointer
    stack->sp = -1;

    // Allocate memory for the stack's data
    stack->data = (char*)malloc(capacity * sizeof(char));
    if (stack->data == NULL) {
        printf("createStack: Error allocating memory for stack data.\n");
        free(stack);
        return NULL;
    }
    stack->total_capacity = capacity;

    return stack;
}

/* Function that inserts an element to the top of a stack
 * Returns: Void
 */
void push(Stack* stack, char c) {
    if (stack == NULL) {
        printf("push: Stack is NULL.\n");
        return;
    }

    if (stack->sp < stack->total_capacity - 1) {
        stack->data[++stack->sp] = c;
    } else {
        printf("push: Stack is full.\n");
    }
}

/* Function that removes an elements from the top of a stack
 * Returns: The removed element (char)
 */
char pop(Stack* stack) {
    if (stack != NULL && stack->sp >= 0) {
        return stack->data[stack->sp--];
    } else {
        printf("pop: Stack is empty.\n");
        return '\0';  // Return null character if stack is empty
    }
}

/* Function that checks if a stack is empty
 * Returns: Boolean expression
 */
int isEmpty(Stack* stack) {
    if (stack == NULL) {
        printf("isEmpty: Stack is NULL.\n");
        return 0;
    }

    return (stack->sp == -1);
}

/* Function that frees the memory used by a stack and its data
 * Returns: Void
 */
void freeStack(Stack* stack) {
    if (stack == NULL) {
        printf("freeStack: Stack is NULL.\n");
        return;
    }

    free(stack->data);
    free(stack);
}
