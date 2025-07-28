%{
#include "y.tab.h"
%}

%%
[a-zA-Z_]   { return LETTER; }
[0-9]       { return DIGIT; }
\n          { return '\n'; /* Return newline to end parsing for the line */ }
.           { /* Ignore any other character or return it as an error */ }
%%

int yywrap(void) {
    return 1;
}
