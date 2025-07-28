%{
#include <stdio.h>

int yylex(void);
void yyerror(const char *s);
%}

%token LETTER DIGIT

%%

/* A valid line is a valid identifier followed by a newline */
line:     identifier '\n'   { printf("\nIt is a valid identifier!\n"); }
          | error '\n'        { /* Catches errors and resets for next line */ }
          ;

/* An identifier must start with a LETTER */
identifier:
          LETTER
          | identifier LETTER
          | identifier DIGIT
          ;

%%

int main(void) {
    printf("Enter a name to be tested as an identifier (CTRL+D to exit):\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    // The default "syntax error" message from yyparse is enough.
    // We can print our own custom message if needed.
    fprintf(stderr, "\nInvalid identifier!\n");
}
