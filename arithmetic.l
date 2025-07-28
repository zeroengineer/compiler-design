%{
#include "y.tab.h"
%}

%%

[ \t\r]+                    ;              
[a-zA-Z_][a-zA-Z_0-9]*      return id;      
[0-9]+(\.[0-9]*)?|\.[0-9]+  return num;    
[\+\*/]                     return op;     
"="                         return '=';    
"-"                         return '-';     
"("                         return '(';    
")"                         return ')';     
";"                         return ';';    
\n                          return 0;       
.                           return yytext[0]; 
%%

int yywrap() {
    return 1;
}
