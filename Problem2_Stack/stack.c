#include <stdio.h>      // Standard input/output
#include <stdlib.h>     // malloc(), free()

#define MAX_SIZE 32     // Maximum stack size

// Node structure for linked list
typedef struct Node {
    int data;           // Stores sensor error code
    struct Node *next;  // Pointer to next node
} Node;

// Stack pointers
Node *top = NULL;       // Points to top of stack (LIFO)
Node *tail = NULL;      // Points to oldest element (for overwrite)
int size = 0;           // Current stack size

/*
 * Function: push
 * Purpose : Push value onto stack
 *           If stack is full, overwrite oldest entry (circular behavior)
 */
void push(int value) {

    // If stack is full, remove the oldest element (tail)
    if (size == MAX_SIZE) {

        Node *temp = top;

        // Traverse to node just before tail
        while (temp->next != tail) {
            temp = temp->next;
        }

        // Remove tail node
        temp->next = top;
        free(tail);
        tail = temp;
        size--;
    }

    // Create new node
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) return;        // Safety check

    newNode->data = value;
    newNode->next = NULL;

    // If stack is empty
    if (top == NULL) {
        top = tail = newNode;
        newNode->next = newNode; // Circular link
    }
    // If stack already has elements
    else {
        newNode->next = top;
        tail->next = newNode;
        top = newNode;
    }

    size++;
}

/*
 * Function: pop
 * Purpose : Remove and return top element from stack
 * Return  : Popped value or -1 if stack is empty
 */
int pop() {

    // Stack underflow condition
    if (top == NULL)
        return -1;

    int value = top->data;

    // If only one node exists
    if (top == tail) {
        free(top);
        top = tail = NULL;
    }
    // More than one node
    else {
        Node *temp = top;
        top = top->next;
        tail->next = top;
        free(temp);
    }

    size--;
    return value;
}

/*
 * Main function for testing stack operations
 */
int main() {

    // Push more than MAX_SIZE values to test overwrite
    for (int i = 1; i <= 35; i++) {
        push(i);
    }

    // Pop elements
    printf("Popped: %d\n", pop());
    printf("Popped: %d\n", pop());

    return 0;
}
