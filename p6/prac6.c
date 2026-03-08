#include <stdio.h>
#include <string.h>

/* Stack for parsing */
char stack[20];
int top = -1;

/* Function declarations */
void push(char);
void pop();
char precedence(char, char);

int main() {
    char input[20];
    int i = 0;
    char a, b;

    printf("Enter the input string (end with $): ");
    scanf("%s", input);

    /* Initialize stack with $ */
    push('$');

    printf("\nStack\tInput\tAction\n");

    while (1) {
        a = stack[top];     // Top of stack
        b = input[i];       // Current input symbol

        printf("%s\t%s\t", stack, &input[i]);

        if (a == '$' && b == '$') {
            printf("Accept\n");
            break;
        }

        if (precedence(a, b) == '<' || precedence(a, b) == '=') {
            push(b);
            i++;
            printf("Shift\n");
        }
        else if (precedence(a, b) == '>') {
            pop();
            printf("Reduce\n");
        }
        else {
            printf("Error\n");
            break;
        }
    }

    return 0;
}

/* Push operation */
void push(char c) {
    stack[++top] = c;
    stack[top + 1] = '\0';
}

/* Pop operation */
void pop() {
    top--;
    stack[top + 1] = '\0';
}

/* Operator precedence function */
char precedence(char a, char b) {
    if (a == '$' && b == '$') return '=';
    if (a == '$') return '<';
    if (b == '$') return '>';

    if (a == 'i' && b == 'i') return ' ';
    if (a == 'i') return '>';
    if (b == 'i') return '<';

    if (a == '+' && b == '+') return '>';
    if (a == '+' && b == '*') return '<';
    if (a == '*' && b == '+') return '>';
    if (a == '*' && b == '*') return '>';

    return ' ';
}