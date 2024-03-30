#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

typedef struct {
    char data[STACK_SIZE];
    int top;
} Stack;

void initialize(Stack *s) {
    s->top = -1;
}

void push(Stack *s, char item) {
    if (s->top == STACK_SIZE - 1) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    s->data[++(s->top)] = item;
}

char pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->data[(s->top)--];
}

char peek(Stack *s) {
    return s->data[s->top];
}

int is_operator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');
}

int precedence(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return 0;
    }
}

void infix_to_postfix(char *infix, char *postfix) {
    Stack operator_stack;
    initialize(&operator_stack);

    int i = 0, j = 0;
    while (infix[i] != '\0') {
        char ch = infix[i];
        if (ch == '(') {
            push(&operator_stack, ch);
            i++;
        }
        else if (ch == ')') {
            while (operator_stack.top != -1 && peek(&operator_stack) != '(') {
                postfix[j++] = pop(&operator_stack);
            }
            if (operator_stack.top == -1 || peek(&operator_stack) != '(') {
                printf("Invalid infix expression\n");
                exit(EXIT_FAILURE);
            }
            pop(&operator_stack); // Discard the '('
            i++;
        }
        else if (is_operator(ch)) {
            while (operator_stack.top != -1 && precedence(ch) <= precedence(peek(&operator_stack))) {
                postfix[j++] = pop(&operator_stack);
            }
            push(&operator_stack, ch);
            i++;
        }
        else if (ch == ' ' || ch == '\t') {
            i++;
        }
        else {
            postfix[j++] = ch;
            i++;
        }
    }

    while (operator_stack.top != -1) {
        if (peek(&operator_stack) == '(') {
            printf("Invalid infix expression\n");
            exit(EXIT_FAILURE);
        }
        postfix[j++] = pop(&operator_stack);
    }
    postfix[j] = '\0';
}

int main() {
    char infix[STACK_SIZE];
    printf("Enter infix expression: ");
    fgets(infix, STACK_SIZE, stdin);

    // Remove trailing newline character
    if (infix[strlen(infix) - 1] == '\n') {
        infix[strlen(infix) - 1] = '\0';
    }

    char postfix[STACK_SIZE];
    infix_to_postfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    return 0;
}

