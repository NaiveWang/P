#ifndef CODEGEN_H
#define CODEGEN_H
#include <stdio.h>
#include "symbol.h"
#include "y.tab.h"
#include "../PCoreIR.h"
#include "../PCoreBase.h"
#define TYP_LOOP 0
#define TYP_LOOP_ESCAPE 1
#define TYP_BRANCH_TRUE 2
#define TYP_BRANCH_FALSE 3
#define TYP_BRANCH_ESCAPE 4
#define SIZE_FSTACK 256
/**/
typedef struct flagStack
{
  int no;
  char type;
}fSt;
/* external */
//extern IR pir[];

/* global parameter */

int flagMarker;

FILE *genOut;

fSt fStack[SIZE_FSTACK];
int fStackPtr;

/* util functions */
void fStackPush(int,char);
int fStackFind(char);
int fStackPop();
/*initializer*/
void initGen(char*);
/*closeing function*/
void finishGen();
/* gen functions */
void gen2(int);
void gen2OP(char*,int);
void gen2OP_0(char*);
void gen2OP_1(int);
void genImmI(char*,long);
void genImmR(char*,double);
void genImmC(char*,char);
void genMark(int);
void genPHeader(char*,int,int,int);
void gen(char*);
void genFlagRelated(char*,int);
void gen7(int,char*,char,int);
void gen12(int,char*,char,int,char,int);
#endif
