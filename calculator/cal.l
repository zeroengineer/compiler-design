%{
#include <stdio.h>
#include "y.tab.h" // Include header from Yacc
// yylval is automatically made available by Yacc
%}

%%
[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[ \t]       ; /* Ignore whitespace */
\n          { return '\n'; } // Return newline as a token
.           { return yytext[0]; }
%%

int yywrap() {
    return 1;
}
