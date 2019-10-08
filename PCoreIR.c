#include "PCoreIR.h"
void (*InstructionSet[])(PBase *p) = {
  SYS,HALT,SUSPEND,REBOOT,
  MUTW,MUTL,MUTT,
  MOV1A,MOV1,MOV8A,MOV8,MOVBA,
  PUSH0A,PUSH0I8,PUSH0I1,PUSH08,PUSH01,POP08,POP01,
  PUSH1,POP1,PUSH8,POP8,
  CBI,CIBI,CIB,CRI,CIR,
  ALLO,FREE,
  CALL,RETN,JUMP,JMPC,JMPN,
  OPADDB,OPADDI,OPADDR,OPSUBB,OPSUBI,OPSUBR,
  OPMULB,OPMULI,OPMULR,OPIMULB,OPIMULI,OPIMULR,
  OPDIVB,OPDIVI,OPDIVR,OPIDIVB,OPIDIVI,OPIDIVR,
  OPCMPB,OPCMPI,OPCMPR,
  OPNOTB,OPNOTI,
  OPANDB,OPANDI,OPORB,OPORI,OPXORB,OPXORI,
  OPTSTB,OPTSTI,
  OPINCB,OPINCI,OPDECB,OPDECI,
  OPSHLB,OPSHLI,OPSHRB,OPSHRI,OPSARB,OPSARI
};
const int pir_n=75;
IR pir[]={
  {6,"SYS"},{2,"HALT"},{2,"SUSPEND"},{2,"REBOOT"},
  {3,"MUTW"},{3,"MUTL"},{3,"MUTT"},
  {2,"MOV1A"},{12,"MOV1"},{2,"MOV8A"},{12,"MOV8"},{2,"MOVBA"},
  {7,"PUSH0A"},{10,"PUSH0I8"},{3,"PUSH0I1"},{7,"PUSH08"},{7,"PUSH01"},{7,"POP08"},{7,"POP01"},
  {7,"PUSH1"},{7,"POP1"},{7,"PUSH8"},{7,"POP8"},
  {2,"CBI"},{2,"CIBI"},{2,"CIB"},{2,"CRI"},{2,"CIR"},
  {2,"ALLO"},{2,"FREE"},
  {10,"CALL"},{2,"RETN"},{10,"JUMP"},{14,"JMPC"},{14,"JMPN"},
  {2,"OPADDB"},{2,"OPADDI"},{2,"OPADDR"},
  {2,"OPSUBB"},{2,"OPSUBI"},{2,"OPSUBR"},
  {2,"OPMULB"},{2,"OPMULI"},{2,"OPMULR"},{2,"OPIMULB"},{2,"OPIMULI"},{2,"OPIMULR"},
  {2,"OPDIVB"},{2,"OPDIVI"},{2,"OPDIVR"},{2,"OPIDIVB"},{2,"OPIDIVI"},{2,"OPIDIVR"},
  {2,"OPCMPB"},{2,"OPCMPI"},{2,"OPCMPR"},
  {2,"OPNOTB"},{2,"OPNOTI"},
  {2,"OPANDB"},{2,"OPANDI"},
  {2,"OPORB"},{2,"OPORI"},
  {2,"OPXORB"},{2,"OPXORI"},
  {2,"OPTSTB"},{2,"OPTSTI"},
  {2,"OPINCB"},{2,"OPINCI"},
  {2,"OPDECB"},{2,"OPDECI"},
  {2,"OPSHLB"},{2,"OPSHLI"},
  {2,"OPSHRB"},{2,"OPSHRI"},
  {2,"OPSARB"},{2,"OPSARI"}
};

int instructionParser(int *r0, char *code)
{
    static int a0;
    for(a0=0;a0<pir_n;a0++)
    {
        //printf("^%s^\n",);
        if(strcmp(code,pir[a0].key)) continue;
        //printf("FOUND ONE!!!!!!!!!!!!!!\n");
        *r0=pir[a0].length;
        return a0;
    }
    *r0=0;
    return -1;
}
void executionOneStep(PBase *p)
{
  unsigned short codeNo;
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("movw (%%rbx),%0":"=r"(codeNo));
  //printf("^%d^\n",codeNo);
  //getchar();
  InstructionSet[codeNo](p);
  //getchar();
}
