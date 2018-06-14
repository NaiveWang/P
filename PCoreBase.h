/**
 * This file contains the fundamental data structures of a processor.
 **/
#ifndef PCOREBASE_H
#define PCOREBASE_H
//offset macros
#define L_ADDR sizeof(void*)
#define BASE_DATA 0
#define BASE_STACK0 BASE_DATA+L_ADDR*1
#define POINTER_STACK0 BASE_DATA+L_ADDR*2
#define BASE_STACK BASE_DATA+L_ADDR*3
#define POINTER_STACK BASE_DATA+L_ADDR*4
#define BASE_GLOBAL BASE_DATA+L_ADDR*5

#define PROCESSOR_STATUS_RUNNING 0
#define PROCESSOR_STATUS_HALT 1
#define PROCESSOR_STATUS_SUSPENDED 2
#define PROCESSOR_STATUS_MWAIT 3
#define PROCESSOR_STATUS_MTEST 4
#define PROCESSOR_STATUS_MLEAVE 5
#define PROCESSOR_STATUS_REBOOT 6
#define PROCESSOR_STATUS_SYS 7

typedef struct AInstanceOfProcessor
{
  void *PID;
  long debugBuffer;
  int performance;
  int triggerNum;
  int *triggerList;
  int triggerVal;
  int currentVal;
  //unsigned int memoryUsage;
  void* exAddr;
  unsigned int APICallID;
  int status;
  void *pc;
  void *code;
  int eflag;
  void *data;
  /**
   * data segment arrangement:
   * 1B for flag;$-8
   * 256*8B for segment pointers
    * data base           $0
    * stack0 base         $8
    * stack0 pointer      $16
    * stack base          $24
    * stack pointer       $32
    * global base         $40
    * const/string base   $44
    * reserved for users
   */
}PBase;
#endif
