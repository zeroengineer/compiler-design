%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *s);
int yylex(void);
%}
%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%%
program:
      | program expr '\n'   { printf("= %d\n", $2); }
      ;
expr:
      NUMBER              { $$ = $1; }
      | expr '+' expr     { $$ = $1 + $3; }
      | expr '-' expr     { $$ = $1 - $3; }
      | expr '*' expr     { $$ = $1 * $3; }
      | expr '/' expr     { 
                              if ($3 == 0) {
                                  yyerror("Error: Division by zero");
                                  exit(1);
                              }
                              $$ = $1 / $3; 
                          }
      | expr '%' expr     { 
                              if ($3 == 0) {
                                  yyerror("Error: Modulo by zero");
                                  exit(1);
                              }
                              $$ = $1 % $3; 
                          }
      | '(' expr ')'      { $$ = $2; }
      ;
%%
int main(void) {
    printf("Enter an arithmetic expression (or CTRL+D to exit):\n");
    yyparse();
    return 0;
}
void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
}
