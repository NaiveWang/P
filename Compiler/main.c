#include <stdio.h>
#include "compiler.h"
int main(int argc,char**argv)
{
  initGen(argv[1]);
  symbolInit();
  yyparse();
  finishGen();
  return 0;
}
