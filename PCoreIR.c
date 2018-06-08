#include "PCoreIR.h"
void SYS(PBase *p)
{
  //put id & push address
  //make sure we have the proper data to the API functions
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("movl 2(%rbx),%r8d");
  asm("movl %%r8d,%0":"=r"(p->APICallID));
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $8,%rbx");
  asm("movq %rbx,(%rdx)");
  asm("movq (%rbx),%rbx");
  asm("movq %%rbx,%0":"=r"(p->exAddr));
  p->pc+=6;
}
void HALT(PBase *p)
{
  //set the global var to halt
  p->status = PROCESSOR_STATUS_HALT;
}
void SUSPEND(PBase *p)
{
  //
  p->status=PROCESSOR_STATUS_SUSPENDED;
}
void REBOOT(PBase *p)
{
  //
  p->pc=p->code;
  *(void**)(p->data + POINTER_STACK0) = *(void**)(p->data +BASE_STACK0);
  *(void**)(p->data + POINTER_STACK) = *(void**)(p->data +BASE_STACK);
  p->status = PROCESSOR_STATUS_SUSPENDED;
  printf("\t\trebooted\n");
}
void MUTW(PBase *p)
{
  //set the status
  p->status = PROCESSOR_STATUS_MWAIT;
  //put addr into exporting address
  asm("movq %0,%%rax"::"r"(p->pc));
  asm("xorq %rcx,%rcx");
  asm("movb 2(%rax),%cl");
  asm("movq %0,%%rax"::"r"(p->data + POINTER_STACK0));
  asm("movq (%rax,%rcx,8),%rax");
  asm("movq %%rax,%0":"=r"(p->exAddr));
  //modify pc
  p->pc+=3;
}
void MUTL(PBase *p)
{
  p->status = PROCESSOR_STATUS_MLEAVE;
  asm("movq %0,%%rax"::"r"(p->pc));
  asm("xorq %rcx,%rcx");
  asm("movb 2(%rax),%cl");
  asm("movq %0,%%rax"::"r"(p->data + POINTER_STACK0));
  asm("movq (%rax,%rcx,8),%rax");
  asm("movq %%rax,%0":"=r"(p->exAddr));
  p->pc+=3;
}
void MUTT(PBase *p)
{
  p->status = PROCESSOR_STATUS_MTEST;
  asm("movq %0,%%rax"::"r"(p->pc));
  asm("xorq %rcx,%rcx");
  asm("movb 2(%rax),%cl");
  asm("movq %0,%%rax"::"r"(p->data + POINTER_STACK0));
  asm("movq (%rax,%rcx,8),%rax");
  asm("movq %%rax,%0":"=r"(p->exAddr));
  p->pc+=3;
}
void MOV1A(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $16,%rbx");
  asm("movq (%rbx),%rax");
  asm("movb (%rax),%cl");
  asm("movq 8(%rbx),%rax");
  asm("movb %cl,(%rax)");
  asm("movq %rbx,(%rdx)");
  p->pc+=2;
}
void MOV1(PBase *p)
{
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq %0,%%rcx"::"r"(p->data));
  asm("movq (%rcx,%rdx,8),%rax");
  asm("xorq %rdx,%rdx");
  asm("movl 3(%rbx),%edx");
  asm("addq %rdx,%rax");

  asm("movb (%rax),%al");// value stored at rax
  asm("xorq %rdx,%rdx");
  asm("movb 7(%rbx),%dl");
  asm("movq (%rcx,%rdx,8),%rcx");
  asm("xorb %dl,%dl");
  asm("movl 8(%rbx),%edx");
  asm("addq %rdx,%rcx");
  asm("movb %al,(%rcx)");
  p->pc+=12;
}
void MOV8A(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $16,%rbx");

  asm("movq (%rbx),%rax");
  asm("movq (%rax),%rcx");
  asm("movq 8(%rbx),%rax");
  asm("movq %rcx,(%rax)");

  //asm("leaq %0,%%rax"::"r")
  asm("movq %rbx,(%rdx)");
//asm("movq %%rdx,%0":"=r"(p->debugBuffer));printf("$%ld/%lx$\n",p->debugBuffer,p->debugBuffer);
  p->pc+=2;
}
void MOV8(PBase *p)//checked
{
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq %0,%%rcx"::"r"(p->data));
  asm("movq (%rcx,%rdx,8),%rax");
  asm("xorq %rdx,%rdx");
  asm("movl 3(%rbx),%edx");
  asm("addq %rdx,%rax");

  asm("movq (%rax),%rax");// value stored at rax
//asm("movq %%rax,%0":"=r"(p->debugBuffer));printf("$%ld/%lx$\n",p->debugBuffer,p->debugBuffer);
  asm("xorq %rdx,%rdx");
  asm("movb 7(%rbx),%dl");

  //asm("movq %0,%%rcx"::"r"(p->data));

  asm("movq (%rcx,%rdx,8),%rcx");
  asm("xorb %dl,%dl");
  asm("movl 8(%rbx),%edx");
  asm("addq %rdx,%rcx");
//asm("movq %%rax,%0":"=r"(p->debugBuffer));
  asm("movq %rax,(%rcx)");
  //printf("$%ld/%lx$\n",p->debugBuffer,p->debugBuffer);
  p->pc+=12;
}
void MOVBA(PBase *p)
{
  asm("leaq (%0),%%rdx"::"r"(p->data + POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $24,%rbx");
  asm("movq %rbx,(%rdx)");
  asm("movq 16(%rbx),%rcx");
  asm("movq 8(%rbx),%rax");
  asm("movq (%rbx),%rbx");
  asm("movq %rcx,%rdx");
  asm("andq $0x000000000000000f,%rdx");
  asm("shrq $4,%rcx");

  asm("loop1:");
  asm("jz loop2");
  asm("movdqu (%rax),%xmm0");
  asm("movdqu %xmm0,(%rbx)");
  asm("addq $16,%rax");
  asm("addq $16,%rbx");
  asm("decq %rcx");
  asm("jmp loop1");
  asm("loop2:");

  //asm("loop1:")
  asm("jz loopend");
  asm("movb (%rax),%ch");
  asm("movb %ch,(%rbx)");
  asm("incq %rax");
  asm("incq %rbx");
  asm("decq %rdx");
  asm("jmp loop2");
  asm("loopend:");
  p->pc+=2;
}
void PUSH0A(PBase *p)//checked
{
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq %0,%%rcx"::"r"(p->data));

  asm("movq (%rcx,%rdx,8),%rax");
  asm("xorq %rdx,%rdx");
  asm("movl 3(%rbx),%edx");
  asm("addq %rdx,%rax");//address calculation finshed:rax
  //asm("movq (%rax),%rax");// value stored at rax
  asm("movq 16(%rcx),%rdx");
  asm("movq %rax,(%rdx)");
  asm("addq $8,16(%rcx)");
  //asm("movq %%rdx,%0":"=r"(p->debugBuffer));
  //printf("$%ld/%lx$\n",p->debugBuffer,p->debugBuffer);
  p->pc+=7;
}
void PUSH0I1(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("movq %0,%%rax"::"r"(p->pc+2));
  asm("movb (%rax),%al");
  asm("movb %al,(%rbx)");
  asm("addq $1,%rbx");
  asm("movq %rbx,(%rdx)");
  p->pc+=3;
}
void PUSH0I8(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));//getchar();
  asm("movq (%rdx),%rbx");
  //asm("movq %%rbx,%0":"=r"(p->debugBuffer));printf("!%ld!%lx\n",p->debugBuffer,p->debugBuffer);
  asm("movq %0,%%rax"::"r"(p->pc+2));

  asm("movq (%rax),%rax");


  asm("movq %rax,(%rbx)");//getchar();

  asm("addq $8,%rbx");
  asm("movq %rbx,(%rdx)");
  //

  p->pc+=10;
}
void PUSH01(PBase *p)
{
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq %0,%%rcx"::"r"(p->data));

  asm("movq (%rcx,%rdx,8),%rax");
  asm("xorq %rdx,%rdx");
  asm("movl 3(%rbx),%edx");
  asm("addq %rdx,%rax");//address calculation finshed:rax
  asm("movb (%rax),%al");// value stored at rax
  asm("movq 16(%rcx),%rdx");
  asm("movb %al,(%rdx)");
  asm("incq 16(%rcx)");
  p->pc+=7;
}
void PUSH08(PBase *p)//checked
{
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq %0,%%rcx"::"r"(p->data));

  asm("movq (%rcx,%rdx,8),%rax");
  asm("xorq %rdx,%rdx");
  asm("movl 3(%rbx),%edx");
  asm("addq %rdx,%rax");//address calculation finshed:rax
  asm("movq (%rax),%rax");// value stored at rax
  asm("movq 16(%rcx),%rdx");
  asm("movq %rax,(%rdx)");
  asm("addq $8,16(%rcx)");
  p->pc+=7;
}
void POP08(PBase *p)//checked
{
  asm("movq %0,%%rcx"::"r"(p->data));
  asm("movq 16(%rcx),%rbx");
  asm("subq $8,%rbx");
  asm("movq (%rbx),%r8");
  //asm("pushq %rax");
  asm("movq %rbx,16(%rcx)");
  //value:rax base:rcx
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq (%rcx,%rdx,8),%rcx");
  asm("xorb %dl,%dl");
  asm("movl 3(%rbx),%edx");
  //asm("popq %rax");
  asm("movq %r8,(%rdx,%rcx)");
  //asm("movq %%rax,%0":"=r"(p->debugBuffer));printf("!%ld!%lx\n",p->debugBuffer,p->debugBuffer);
  p->pc+=7;
}
void POP01(PBase *p)
{
  asm("movq %0,%%rcx"::"r"(p->data));
  asm("movq 16(%rcx),%rbx");
  asm("decq %rbx");
  asm("movb (%rbx),%r8b");
  //asm("pushq %rax");
  asm("movq %rbx,16(%rcx)");
  //value:rax base:rcx
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq (%rcx,%rdx,8),%rcx");
  asm("xorb %dl,%dl");
  asm("movl 3(%rbx),%edx");
  //asm("popq %rax");
  asm("movb %r8b,(%rdx,%rcx)");
  p->pc+=7;
}
void PUSH1(PBase *p)
{
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq %0,%%rcx"::"r"(p->data));

  asm("movq (%rcx,%rdx,8),%rax");
  asm("xorq %rdx,%rdx");
  asm("movl 3(%rbx),%edx");
  asm("addq %rdx,%rax");//address calculation finshed:rax
  asm("movb (%rax),%al");// value stored at rax
  asm("movq 32(%rcx),%rdx");
  asm("movb %al,(%rdx)");
  asm("incq 16(%rcx)");
  p->pc+=7;
}
void POP1(PBase *p)
{
  asm("movq %0,%%rcx"::"r"(p->data));
  asm("movq 32(%rcx),%rbx");
  asm("decq %rbx");
  asm("movb (%rbx),%r8b");
  //asm("pushq %rax");
  asm("movq %rbx,16(%rcx)");
  //value:rax base:rcx
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq (%rcx,%rdx,8),%rcx");
  asm("xorb %dl,%dl");
  asm("movl 3(%rbx),%edx");
  //asm("popq %rax");
  asm("movb %r8b,(%rdx,%rcx)");
  p->pc+=7;
}
void PUSH8(PBase *p)//2decode+(1+4)addr=7
{
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq %0,%%rcx"::"r"(p->data));

  asm("movq (%rcx,%rdx,8),%rax");
  asm("xorq %rdx,%rdx");
  asm("movl 3(%rbx),%edx");
  asm("addq %rdx,%rax");//address calculation finshed:rax
  asm("movq (%rax),%rax");// value stored at rax
  asm("movq 32(%rcx),%rdx");
  asm("movq %rax,(%rdx)");
  asm("addq $8,16(%rcx)");
  p->pc+=7;
}
void POP8(PBase *p)//2decode+(1+4)addr=7
{
  asm("movq %0,%%rcx"::"r"(p->data));
  asm("movq 32(%rcx),%rbx");
  asm("subq $8,%rbx");
  asm("movq (%rbx),%r8");
  //asm("pushq %rax");
  asm("movq %rbx,16(%rcx)");
  //value:rax base:rcx
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("xorq %rdx,%rdx");
  asm("movb 2(%rbx),%dl");
  asm("movq (%rcx,%rdx,8),%rcx");
  asm("xorb %dl,%dl");
  asm("movl 3(%rbx),%edx");
  //asm("popq %rax");
  asm("movq %r8,(%rdx,%rcx)");
  p->pc+=7;
}
void CBI(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("addq $7,%rbx");
  asm("xorq %rax,%rax");
  asm("movb (%rbx),%al");
  asm("movq %rax,-8(%rbx)");
  asm("movq %rbx,(%rdx)");
  p->pc+=2;
}
void CIBI(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("addq $7,%rbx");
  //asm("xorq %rax,%rax");
  asm("movsxb (%rbx),%ax");
  asm("cwde");
  asm("cdqe");
  asm("movq %rax,-8(%rbx)");
  asm("movq %rbx,(%rdx)");
  p->pc+=2;
}
void CIB(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $7,%rbx");
  //asm("xorq %rax,%rax");
  asm("movq -1(%rbx),%rax");
  asm("movb %al,-1(%rbx)");
  asm("movq %rbx,(%rdx)");
  p->pc+=2;
}
void CRI(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("fldl -8(%rbx)");
  asm("fistpq -8(%rbx)");
  p->pc+=2;
}
void CIR(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("fildq -8(%rbx)");
  asm("fstl -8(%rbx)");
  p->pc+=2;
}
void ALLO(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rcx");
  asm("xchgq %rdi,%r8");
  asm("movq -8(%rcx),%rdi");
  //asm("extern malloc");
  asm("callq malloc");
  asm("xchgq %rdi,%r8");
  asm("movq %rax,-8(%rcx)");
  p->pc+=2;
}
void FREE(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rcx");
  asm("subq $8,%rcx");
  asm("xchgq %rdi,%r8");
  asm("movq (%rcx),%rdi");
  asm("callq free");
  asm("xchgq %rdi,%r8");
  asm("movq %rcx,(%rdx)");
  p->pc+=2;
}
void CALL(PBase *p)
{
  //get stack pointer
  asm("movq %0,%%rbx"::"r"(p->data + POINTER_STACK));
  //get pc,pc is now in %rax
  asm("movq %0,%%rax"::"r"(p->pc));
  //get new pc to %rcx
  asm("movq 2(%rax),%rcx");
  //change pc to new start point with current instruction lenth
  asm("addq $10,%rax");
  //push pc value
  asm("movq %rax,(%rbx)");
  //add pc with code base, now %rbx is free
  asm("addq %0,%%rcx"::"r"(p->code));
  //put rcx(new pc to pc's addr)
  asm("movq %%rcx,%0":"=r"(p->pc));
  //end
}
void RETN(PBase *p)
{
  //get recovery pc from stack
  //get stack pointer
  asm("movq %0,%%r9"::"r"(p->data + POINTER_STACK));
  //operate the stack
  asm("movq (%r9),%r8");
  asm("subq $8,%r8");
  asm("movq %r8,(%r9)");
  //get the value
  asm("movq (%r8),%rcx");
  //old pc in %rax, put it to his home
  asm("movq %%rcx,%0":"=r"(p->pc));
  //end, notice:no need to influence pc with its length.
}
void JUMP(PBase *p)
{
  //get the offset
  //get pc
  asm("movq %0,%%rcx"::"r"(p->pc));
  //get offset
  //asm("movq (%rcx),%rax");
  asm("movq 2(%rcx),%r8");
  //offset in the %rax, add it to the pc
  //asm("movq %rcx,%rbx");
  //asm("addq $10,%rax");
  //asm("addq %rax,%rbx");
  //p->pc+=p->debugBuffer;
  //asm("movq %0,%%rcx"::"r"(p->pc));
  asm("addq %r8,%rcx");
  asm("movq %%rcx,%0":"=r"(p->pc));
  //printf("$%lx$%ld$\n",p->debugBuffer,p->debugBuffer);
}
void JMPC(PBase *p)
{
  //get flag
  asm("movl %0,%%edx"::"r"(p->eflag));
  //get mask
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("movl 2(%rbx),%ecx");
  //and flag
  //asm("movl %%edx,%0":"=r"(p->debugBuffer));
  asm("andl %ecx,%edx");
  //zf:

  asm("jz njump");//printf("$$$$$$$$$$$$$$$$$$$$\n");
  //jump, get val
  asm("movq 6(%rbx),%rax");
  asm("addq %rax,%rbx");//add offset
  asm("movq %%rbx,%0":"=r"(p->pc));
  //return;
  asm("jmp jp");
  asm("njump:");
  p->pc+=14;
  asm("jp:");
  //printf("\t\t\t###%X\n",p->debugBuffer);
  //get pc
}
void JMPN(PBase *p)
{
  //get flag
  asm("movl %0,%%edx"::"r"(p->eflag));
  //get mask
  asm("movq %0,%%rbx"::"r"(p->pc));
  asm("movl 2(%rbx),%ecx");
  //and flag
  asm("movl %%edx,%0":"=r"(p->debugBuffer));
  asm("andl %ecx,%edx");
  //zf:

  asm("jnz nojump");//printf("$$$$$$$$$$$$$$$$$$$$\n");
  //jump, get val
  asm("movq 6(%rbx),%rax");
  asm("addq %rax,%rbx");//add offset
  asm("movq %%rbx,%0":"=r"(p->pc));
  //return;
  asm("jmp jump");
  asm("nojump:");
  p->pc+=14;
  asm("jump:");
  printf("\t\t\t###%X\n",p->debugBuffer);
  //get pc
}
void OPADDB(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("decq %rbx");
  asm("movb (%rbx),%al");
  asm("addb %al,-1(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPADDI(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");

  asm("subq $8,%rbx");
  asm("movq (%rbx),%rax");

  asm("addq %rax,-8(%rbx)");
  asm("lahf");//asm("movq %%rbx,%0":"=r"(p->debugBuffer));

  asm("movq %rbx,(%rdx)");
  //asm("movb %ah,%al");
  asm("movl %%eax,%0":"=r"(p->eflag));
  //printf("$%ld/%lx$\n",p->debugBuffer,p->debugBuffer);
  p->pc+=2;
}
void OPADDR(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $8,%rbx");
  asm("fldl (%rbx)");
  //asm("movq (%rbx),%rax");
  //asm("addq %rax,-8(%rbx)");
  asm("faddl -8(%rbx)");
  asm("fstl -8(%rbx)");
  asm("fstsw %ax");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPSUBB(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("decq %rbx");
  asm("movb (%rbx),%al");
  asm("subb %al,-1(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPSUBI(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $8,%rbx");
  asm("movq (%rbx),%rax");
  asm("subq %rax,-8(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPSUBR(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $8,%rbx");
  asm("fldl (%rbx)");
  //asm("movq (%rbx),%rax");
  //asm("addq %rax,-8(%rbx)");
  asm("fsubl -8(%rbx)");
  asm("fstl -8(%rbx)");
  asm("fstsw %ax");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPMULB(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("decq %rbx");
  asm("movb (%rbx),%al");
  asm("mulb -1(%rbx)");
  asm("movb %al,-1(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPMULI(PBase *p)
{
  asm("movq %0,%%rcx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rcx),%rbx");
  asm("subq $8,%rbx");
  asm("movq (%rbx),%rax");
  asm("mulq -8(%rbx)");
  asm("movq %rax,-8(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rcx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPMULR(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $8,%rbx");
  asm("fldl (%rbx)");
  asm("fmull -8(%rbx)");
  asm("fstl -8(%rbx)");
  asm("fstsw %ax");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPIMULB(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("decq %rbx");
  asm("movb (%rbx),%al");
  asm("imulb -1(%rbx)");
  asm("movb %al,-1(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPIMULI(PBase *p)
{
  asm("movq %0,%%rcx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rcx),%rbx");
  asm("subq $8,%rbx");
  asm("movq (%rbx),%rax");
  asm("imulq -8(%rbx)");
  asm("movq %rax,-8(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rcx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPIMULR(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $8,%rbx");
  asm("fldl (%rbx)");
  asm("fimull -8(%rbx)");
  asm("fstl -8(%rbx)");
  asm("fstsw %ax");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPDIVB(PBase *p)//checked
{
  asm("movq %0,%%rbx"::"r"(p->data+POINTER_STACK0));
  //asm("subq $8,%rbx");
  asm("movq (%rbx),%rbx");
  asm("movb -2(%rbx),%cl");
  asm("xorw %ax,%ax");
  asm("movb -1(%rbx),%al");
  //asm("cqo");
  asm("divb %cl");
  asm("movb %al,-1(%rbx)");//quotient
  asm("movb %ah,-2(%rbx)");//reminder
  asm("lahf");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPDIVI(PBase *p)//checked
{
  asm("movq %0,%%rbx"::"r"(p->data+POINTER_STACK0));
  //asm("subq $8,%rbx");
  asm("movq (%rbx),%rbx");
  asm("xorq %rdx,%rdx");
  asm("movq -8(%rbx),%rcx");
  asm("movq -16(%rbx),%rax");
  //asm("cqo");
  asm("divq %rcx");
  asm("movq %rdx,-8(%rbx)");//quotient
  asm("movq %rax,-16(%rbx)");//reminder
  //asm("movq %%rax,%0":"=r"(p->debugBuffer));
  asm("lahf");
  //asm("movb %ah,%al");
  asm("movl %%eax,%0":"=r"(p->eflag));

  //printf("$%ld/%lx$\n",p->debugBuffer,p->debugBuffer);
  p->pc+=2;
}
void OPDIVR(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $8,%rbx");
  asm("fldl (%rbx)");
  asm("fdivl -8(%rbx)");
  asm("fstl -8(%rbx)");
  asm("fstsw %ax");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPIDIVB(PBase *p)//checked
{
  asm("movq %0,%%rbx"::"r"(p->data+POINTER_STACK0));
  //asm("subq $8,%rbx");
  asm("movq (%rbx),%rbx");
  asm("movb -2(%rbx),%cl");
  //asm("xorw %ax,%ax")
  asm("movsxb -1(%rbx),%ax");
  //asm("cqo");
  asm("idivb %cl");
  asm("movb %al,-1(%rbx)");//quotient
  asm("movb %ah,-2(%rbx)");//reminder
  asm("lahf");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPIDIVI(PBase *p)//checked
{
  asm("movq %0,%%rbx"::"r"(p->data+POINTER_STACK0));
  //asm("subq $8,%rbx");
  asm("movq (%rbx),%rbx");
  //asm("xorq %rdx,%rdx")
  asm("movq -8(%rbx),%rcx");
  asm("movq -16(%rbx),%rax");
  asm("cqo");
  asm("idivq %rcx");
  asm("movq %rdx,-8(%rbx)");//quotient
  asm("movq %rax,-16(%rbx)");//reminder
  //asm("movq %%rax,%0":"=r"(p->debugBuffer));
  asm("lahf");
  //asm("movb %ah,%al");
  asm("movl %%eax,%0":"=r"(p->eflag));

  //printf("$%ld/%lx$\n",p->debugBuffer,p->debugBuffer);
  p->pc+=2;
}
void OPIDIVR(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $8,%rbx");
  asm("fldl (%rbx)");
  asm("fidivl -8(%rbx)");
  asm("fstl -8(%rbx)");
  asm("fstsw %ax");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPCMPB(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $2,%rbx");
  asm("movb (%rbx),%al");
  asm("cmpb %al,1(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPCMPI(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $16,%rbx");
  asm("movq (%rbx),%rax");
  asm("cmpq %rax,8(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPCMPR(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $16,%rbx");
  //asm("movq (%rbx),%rax");
  asm("fldl (%rbx)");
  //asm("cmpq %rax,8(%rbx)");
  asm("fcoml 8(%rbx)");
  asm("fstsw %ax");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPNOTB(PBase *p)//checked
{
  asm("movq %0,%%rbx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rbx),%rbx");
  asm("notb -1(%rbx)");
  asm("lahf");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPNOTI(PBase *p)//checked
{
  asm("movq %0,%%rbx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rbx),%rbx");
  asm("notq -8(%rbx)");
  asm("lahf");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPANDB(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("decq %rbx");
  asm("movb (%rbx),%al");
  asm("andb %al,-1(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPANDI(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $8,%rbx");
  asm("movq (%rbx),%rax");
  asm("andq %rax,-8(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPORB(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("decq %rbx");
  asm("movb (%rbx),%al");
  asm("ORB %al,-1(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPORI(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $8,%rbx");
  asm("movq (%rbx),%rax");
  asm("ORq %rax,-8(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPXORB(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("decq %rbx");
  asm("movb (%rbx),%al");
  asm("XORB %al,-1(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPXORI(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $8,%rbx");
  asm("movq (%rbx),%rax");
  asm("XORq %rax,-8(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPTSTB(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $2,%rbx");
  asm("movq %rbx,(%rdx)");
  asm("movb 1(%rbx),%al");
  asm("testb (%rbx),%al");
  asm("lahf");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPTSTI(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("subq $16,%rbx");
  asm("movq %rbx,(%rdx)");
  asm("movq 8(%rbx),%rax");
  asm("testq (%rbx),%rax");
  asm("lahf");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPINCB(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  //asm("decq %rbx");
  //asm("movb (%rbx),%al");
  asm("incb -1(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPINCI(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("incq -8(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPDECB(PBase *p)
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("decb -1(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPDECI(PBase *p)//checked
{
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rbx");
  asm("decq -8(%rbx)");
  asm("lahf");
  asm("movq %rbx,(%rdx)");
  asm("movl %%eax,%0":"=r"(p->eflag));
  p->pc+=2;
}
void OPSHLB(PBase *p)
{
  //shift left, byte
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rax");
  //2 element
  asm("decq %rax");
  asm("movq %rax,(%rdx)");
  asm("movb (%rax),%cl");
  asm("shlb %cl,-1(%rax)");
  asm("lahf");
  asm("movl %%eax,%0":"=r"(p->eflag));
}
void OPSHLI(PBase *p)
{
  //shift left, byte
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rax");
  //2 element
  asm("decq %rax");
  asm("movq %rax,(%rdx)");
  asm("movb (%rax),%cl");
  asm("shlq %cl,-8(%rax)");
  asm("lahf");
  asm("movl %%eax,%0":"=r"(p->eflag));
}
void OPSHRB(PBase *p)
{
  //shift left, byte
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rax");
  //2 element
  asm("decq %rax");
  asm("movq %rax,(%rdx)");
  asm("movb (%rax),%cl");
  asm("SHRB %cl,-1(%rax)");
  asm("lahf");
  asm("movl %%eax,%0":"=r"(p->eflag));
}
void OPSHRI(PBase *p)
{
  //shift left, byte
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rax");
  //2 element
  asm("decq %rax");
  asm("movq %rax,(%rdx)");
  asm("movb (%rax),%cl");
  asm("SHRq %cl,-8(%rax)");
  asm("lahf");
  asm("movl %%eax,%0":"=r"(p->eflag));
}
void OPSARB(PBase *p)
{
  //shift left, byte
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rax");
  //2 element
  asm("decq %rax");
  asm("movq %rax,(%rdx)");
  asm("movb (%rax),%cl");
  asm("SARB %cl,-1(%rax)");
  asm("lahf");
  asm("movl %%eax,%0":"=r"(p->eflag));
}
void OPSARI(PBase *p)
{
  //shift left, byte
  asm("movq %0,%%rdx"::"r"(p->data+POINTER_STACK0));
  asm("movq (%rdx),%rax");
  //2 element
  asm("decq %rax");
  asm("movq %rax,(%rdx)");
  asm("movb (%rax),%cl");
  asm("SARq %cl,8(%rax)");
  asm("lahf");
  asm("movl %%eax,%0":"=r"(p->eflag));
}
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
  {7,"PUSH0A"},{10,"PUSH0I8"},{10,"PUSH0I1"},{7,"PUSH08"},{7,"PUSH01"},{7,"POP08"},{7,"POP01"},
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
