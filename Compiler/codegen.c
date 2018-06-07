#include "codegen.h"
void fStackPush(int n,char t)
{
  if(fStackPtr==SIZE_FSTACK)
  {
    printf("fetal error : Code Generator Flag Stack Overflow.\n");
    exit(-1);
  }
  //push here
  fStack[fStackPtr].no=n;
  fStack[fStackPtr].type=t;
  fStackPtr++;
}
int fStackFind(char t)
{
  static int a0;
  //find the nearst guy with same type
  for(a0=fStackPtr-1;a0;a0--)
  {
    //conpare
    if(t==fStack[fStackPtr].type) return fStack[fStackPtr].no;
  }
  //nothing find,  0 is the erroe handler
  return 0;
}
int fStackPop()
{
  fStackPtr--;
  return fStack[fStackPtr].no;
}
void initGen(char *s)
{
  //open file
  genOut = fopen(s,"w");
  fStackPtr=1;
  //reserved 0 for error handler
  flagMarker=0;
  //flag marker starts from 0
}
void finishGen()
{
  fflush(genOut);
  fclose(genOut);
}
void gen2 (int codeTyp)
{
  switch(codeTyp)
  {
    case _HALT:
      fprintf(genOut,"HALT");
      break;
    case _SUSPEND:
      fprintf(genOut,"SUSPEND");
      break;
    case _REBOOT:
      fprintf(genOut,"REBOOT");
      break;
  }
  fprintf(genOut,"\n");
}
void gen2OP(char* ins,int type)
{
  //
  fprintf(genOut, "OP%s", ins);
  switch(type)
  {
    case TYP_INT :
      fprintf(genOut, "I\n");
      break;
    case TYP_REAL:
      fprintf(genOut, "R\n");
      break;
    case TYP_CHAR:
      fprintf(genOut, "B\n");
      break;
  }
}
void gen2OP_0(char* s)
{
  fprintf(genOut, "OP%s", s);
}
void gen2OP_1(int t)
{
  switch(t)
  {
    case TYP_INT :
      fprintf(genOut, "I\n" );
      break;
    case TYP_REAL:
      fprintf(genOut, "R\n" );
    case TYP_CHAR:
      fprintf(genOut, "B\n" );
      break;
  }
}
void genPHeader(char* s,int st0,int st,int gl)
{
  //generate the processor header of the file
  fprintf(genOut,".processor %s %d %d %d\n",s,st0,st,gl);
}
void gen(char* s)
{
  fprintf(genOut,"%s\n",s);
}
void genImmI(char* s,long v)
{
  fprintf(genOut, "%s %ld\n", s, v);
}
void genImmR(char* s,double v)
{
  fprintf(genOut, "%s %le\n", s, v);
}
void genImmC(char* s,char v)
{
  fprintf(genOut, "%s %c\n", s, v);
}
void genFlagRelated(char* s,int n)
{
  fprintf(genOut,"%s%d\n",s,n);
}
void gen7(int typ,char* s,char seg,int ofst)
{
  fprintf(genOut,"%s",s);
  switch(typ)
  {
    case TYP_INT:
      fprintf(genOut,"8");
      break;
    case TYP_REAL:

      fprintf(genOut,"8");
      break;
    case TYP_CHAR:
      fprintf(genOut,"1");

      break;
  }
  fprintf(genOut," %d:%d\n",seg,ofst);
}
void gen12(int typ,char* s,char s1,int o1,char s2,int o2)
{
  fprintf(genOut,"%s",s);
  switch(typ)
  {
    case TYP_INT:
      fprintf(genOut,"8");
      break;
    case TYP_REAL:

      fprintf(genOut,"8");
      break;
    case TYP_CHAR:
      fprintf(genOut,"1");

      break;
  }
  fprintf(genOut," %d:%d %d:%d\n",s1,o1,s2,o2);
}
