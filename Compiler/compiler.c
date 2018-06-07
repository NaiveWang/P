#include "compiler.h"
int lexNextToken()
{
  static int a0;
  a0=yylex();
  if(
    a0==CONSTANT_CHAR||
    a0==CONSTANT_STRING
  )
    printf("\n$%s$\n",yytext);
}
