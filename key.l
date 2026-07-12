%{ 
#include "y.tab.h" 
#include <stdlib.h> 
%} 

%% 

    /* Match integer numbers (Indented comments are safe) */
[0-9]+ { 
    yylval.num = atoi(yytext); 
    return NUMBER; 
} 
 
    /* Ignore spaces and tabs */ 
[ \t]+ ; 
 
    /* Return newline to parser */ 
\n { 
    return '\n'; 
} 
 
    /* Return operators and parentheses directly */ 
[()+\-*/] { 
    return yytext[0]; 
} 
 
    /* Handle invalid characters */ 
. { 
    printf("Unknown character: %s\n", yytext); 
} 
 
%% 
 
int yywrap(void) 
{ 
    return 1; 
}