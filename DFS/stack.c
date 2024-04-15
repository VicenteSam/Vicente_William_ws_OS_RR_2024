#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Node* createNode(long data) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    return n;
}

Stack* createStack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    s->height = 0;
    return s;
}

void destroyStack(Stack** s_ref) {
    Stack* s = *s_ref;
    while (s->top != NULL) {
        Node* temp = s->top;
        s->top = s->top->next;
        free(temp);
    }
    free(s);
    *s_ref = NULL;
}

int stackIsEmpty(Stack* s) {
    return s->height == 0;
}

void printStack(Stack* s) {
    if (stackIsEmpty(s)) {
        printf("Stack is empty!\n");
    } else {
        Node* n = s->top;
        while (n != NULL) {
            printf("%ld|", n->data);
            n = n->next;
        }
        printf("\n");
    }
}

void push(Stack* s, long element) {
    Node* n = createNode(element);
    n->next = s->top;
    s->top = n;
    s->height++;
}

long pop(Stack* s) {
    if (stackIsEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    } else {
        Node* temp = s->top;
        long data = temp->data;
        s->top = temp->next;
        free(temp);
        s->height--;
        return data;
    }
}
