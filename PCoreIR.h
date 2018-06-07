/**
 * Here is the instruction set & mapping
 **/
#ifndef PCOREIR_H
#define PCOREIR_H
#include "PCoreBase.h"
#include <string.h>
#include <stdio.h>
#define INSTRUCTION_VERSION 2
//instructions
//template: void <NAME>(PBase)
/** key word define **/
typedef struct compileData
{
  int length;
  char key[28];
}IR;
/**SYSTEM CALL**/
void SYS(PBase *p);//6
/**Processor Control**/
void HALT(PBase *p);//2
void SUSPEND(PBase *p);//2
void REBOOT(PBase *p);//2
/** mutex operation **/
void MUTW(PBase *p);//wait//3
void MUTL(PBase *p);//leave//3
void MUTT(PBase *p);//test//3
/** Data transfer **/
void MOV1A(PBase *p);//2
void MOV1(PBase *p);//2+5*2=12
void MOV8A(PBase *p);//2decode
void MOV8(PBase *p);//2decode+(1+4)addr*2=12
void MOVBA(PBase *p);//2decode:stack0//8addr1,8addr2,4size
void PUSH0A(PBase *p);//2decode+(1+4)addr=7, put the value into BASE_STACK0
void PUSH0I8(PBase *p);//2decode+8data=10
void PUSH0I1(PBase *p);//3
void PUSH08(PBase *p);//2decode+(1+4)addr=7
void PUSH01(PBase *p);//7
void POP08(PBase *p);//2decode+(1+4)addr=7
void POP01(PBase *p);//7

void PUSH1(PBase *p);//7
void POP1(PBase *p);//7
void PUSH8(PBase *p);//2decode+(1+4)addr=7
void POP8(PBase *p);//2decode+(1+4)addr=7
/** Type Conventions**/
void CBI(PBase *p);//2
void CIBI(PBase *p);//2
void CIB(PBase *p);//2
void CRI(PBase *p);//2
void CIR(PBase *p);//2
/** Memory Allocation **/
void ALLO(PBase *p);//2
void FREE(PBase *p);//2
/** Control **/
void CALL(PBase *p);//2decode+8offset=10,push pc
void RETN(PBase *p);//2decode=2:recover pc
void JUMP(PBase *p);//2decode+8offset=10
void JMPC(PBase *p);//2decode+4mask+8offset=14
/** Operation **/
void OPADDB(PBase *p);//2
void OPADDI(PBase *p);//2decode=2
void OPADDR(PBase *p);//2

void OPSUBB(PBase *p);//2
void OPSUBI(PBase *p);//2
void OPSUBR(PBase *p);//2

void OPMULB(PBase *p);//2
void OPNULI(PBase *p);//2
void OPMULR(PBase *p);//2

void OPIMULB(PBase *p);//2
void OPIMULI(PBase *p);//2
void OPIMULR(PBase *p);//2

void OPDIVB(PBase *p);//2
void OPDIVI(PBase *p);//2decode=2
void OPDIVR(PBase *p);//2

void OPIDIVB(PBase *p);//2
void OPIDIVI(PBase *p);//2
void OPIDIVR(PBase *p);//2

void OPCMPB(PBase *p);//2
void OPCMPI(PBase *p);//2decode=2
void OPCMPR(PBase *p);//2

void OPNOTB(PBase *p);//2
void OPNOTI(PBase *p);//2decode=2

void OPANDB(PBase *p);//2
void OPANDI(PBase *p);//2

void OPORB(PBase *p);//2
void OPORI(PBase *p);//2

void OPXORB(PBase *p);//2
void OPXORI(PBase *p);//2

void OPTSTB(PBase *p);//2
void OPTSTI(PBase *p);//2decode=2

void OPINCB(PBase *p);//2
void OPINCI(PBase *p);//2

void OPDECB(PBase *p);//2
void OPDECI(PBase *p);//2

void OPSHLB(PBase *p);//2
void OPSHLI(PBase *p);//2

void OPSHRB(PBase *p);//2
void OPSHRI(PBase *p);//2

void OPSARB(PBase *p);//2
void OPSARI(PBase *p);//2
int instructionParser(int *r0, char* code);
void executionOneStep(PBase *p);
//mapping
//void instructions()
#endif
