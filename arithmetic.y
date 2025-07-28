%{
#include <stdio.h>
int valid = 1;
int yylex(void);
int yyerror(const char *s);
%}

%token num id op

%%

start : id '=' s ';' ;

s     : id x
      | num x
      | '-' num x
      | '(' s ')' x ;

x     : op s
      | '-' s
      | /* empty */ ;

%%

int yyerror(const char *s) {
    valid = 0;
    printf("\nInvalid expression: %s\n", s);
    return 0;
}

int main() {
    printf("Enter the expression:\n");
    yyparse();
    if (valid) {
        printf("\nValid expression!\n");
    }
    return 0;
}
