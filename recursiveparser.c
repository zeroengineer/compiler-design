#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Global variables
char ip_sym[15];    // Input symbols string
int ip_ptr = 0;     // Pointer to current input symbol
char op[50];        // Current production string
char tmp[50];       // Temporary buffer used in manipulating 'op'

void e();
void e_prime();
void t();
void t_prime();
void f();
void advance();

void e() {
    strcpy(op, "TE'");
    printf("E=%-25s", op);
    printf("E -> TE'\n");
    t();
    e_prime();
}

void e_prime() {
    int i, n = 0, l;

    // Remove all 'e' (epsilon) from op before processing
    for (i = 0; i <= (int)strlen(op); i++) {
        if (op[i] != 'e')
            tmp[n++] = op[i];
    }
    tmp[n] = '\0';
    strcpy(op, tmp);

    l = strlen(op);

    // Find position of 'E' in op
    for (n = 0; n < l && op[n] != 'E'; n++);

    // If next input symbol is '+', expand E' -> +TE'
    if (ip_sym[ip_ptr] == '+') {
        // Shift right the substring starting at n+2 to make space for "+TE'"
        i = n + 2;
        do {
            op[i + 2] = op[i];
            i++;
        } while (i <= l);

        op[n++] = '+';
        op[n++] = 'T';
        op[n++] = 'E';
        op[n++] = '\'';

        printf("E=%-25s", op);
        printf("E' -> +TE'\n");

        advance();
        t();
        e_prime();
    } else {
        // If '+' not found, replace E' with epsilon 'e'
        op[n] = 'e';
        for (i = n + 1; i <= (int)strlen(op); i++)
            op[i] = op[i + 1];  // Shift left to remove extra char

        printf("E=%-25s", op);
        printf("E' -> e\n");
    }
}

void t() {
    int i, n = 0, l;

    // Remove 'e' from op
    for (i = 0; i <= (int)strlen(op); i++) {
        if (op[i] != 'e')
            tmp[n++] = op[i];
    }
    tmp[n] = '\0';
    strcpy(op, tmp);

    l = strlen(op);

    // Find position of 'T' in op
    for (n = 0; n < l && op[n] != 'T'; n++);

    // Shift right to make space for "FT'"
    i = n + 1;
    do {
        op[i + 2] = op[i];
        i++;
    } while (i < l);

    op[n++] = 'F';
    op[n++] = 'T';
    op[n++] = '\'';

    printf("E=%-25s", op);
    printf("T -> FT'\n");

    f();
    t_prime();
}

void t_prime() {
    int i, n = 0, l;

    // Remove 'e' from op
    for (i = 0; i <= (int)strlen(op); i++) {
        if (op[i] != 'e')
            tmp[n++] = op[i];
    }
    tmp[n] = '\0';
    strcpy(op, tmp);

    l = strlen(op);

    // Find position of 'T' in op
    for (n = 0; n < l && op[n] != 'T'; n++);

    // If next input symbol is '*', expand T' -> *FT'
    if (ip_sym[ip_ptr] == '*') {
        i = n + 2;
        do {
            op[i + 2] = op[i];
            i++;
        } while (i < l);

        op[n++] = '*';
        op[n++] = 'F';
        op[n++] = 'T';
        op[n++] = '\'';

        printf("E=%-25s", op);
        printf("T' -> *FT'\n");

        advance();
        f();
        t_prime();
    } else {
        // Otherwise T' -> epsilon
        op[n] = 'e';
        for (i = n + 1; i <= (int)strlen(op); i++)
            op[i] = op[i + 1];

        printf("E=%-25s", op);
        printf("T' -> e\n");
    }
}

void f() {
    int i, n = 0, l;

    // Remove 'e' from op
    for (i = 0; i <= (int)strlen(op); i++) {
        if (op[i] != 'e')
            tmp[n++] = op[i];
    }
    tmp[n] = '\0';
    strcpy(op, tmp);

    l = strlen(op);

    // Find position of 'F' in op
    for (n = 0; n < l && op[n] != 'F'; n++);

    if (ip_sym[ip_ptr] == 'i' || ip_sym[ip_ptr] == 'I') {
        op[n] = 'i';
        printf("E=%-25s", op);
        printf("F -> i\n");
        advance();
    } else if (ip_sym[ip_ptr] == '(') {
        advance();
        e();
        if (ip_sym[ip_ptr] == ')') {
            advance();

            i = n + 2;
            do {
                op[i + 2] = op[i];
                i++;
            } while (i <= l);

            op[n++] = '(';
            op[n++] = 'E';
            op[n++] = ')';

            printf("E=%-25s", op);
            printf("F -> (E)\n");
        } else {
            printf("\n\tSyntax error: Missing closing ')'\n");
            exit(1);
        }
    } else {
        printf("\n\tSyntax error: Unexpected symbol '%c'\n", ip_sym[ip_ptr]);
        exit(1);
    }
}

void advance() {
    ip_ptr++;
}

int main() {
    int i, n = 0;

    printf("\nGrammar without left recursion:");
    printf("\n\t E -> TE'");
    printf("\n\t E' -> +TE' | e");
    printf("\n\t T -> FT'");
    printf("\n\t T' -> *FT' | e");
    printf("\n\t F -> (E) | i\n");

    printf("\nEnter the input expression: ");
    scanf("%s", ip_sym);

    printf("\nExpressions\t\tSequence of production rules\n");
    e();

    // Validate input characters
    for (i = 0; i < (int)strlen(ip_sym); i++) {
        if (ip_sym[i] != '+' && ip_sym[i] != '*' && ip_sym[i] != '(' &&
            ip_sym[i] != ')' && ip_sym[i] != 'i' && ip_sym[i] != 'I') {
            printf("\nSyntax error: Invalid character '%c'\n", ip_sym[i]);
            break;
        }
    }

    // Print final production string without epsilon
    n = 0;
    for (i = 0; i <= (int)strlen(op); i++) {
        if (op[i] != 'e')
            tmp[n++] = op[i];
    }
    tmp[n] = '\0';
    strcpy(op, tmp);

    printf("\nE=%-25s\n", op);

    return 0;
}
