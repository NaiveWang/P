#include <stdio.h>
#include "PVM.h"
int main(int argc,char **argv)
{
  signal(SIGSEGV,handlerSegFault);
  if(argc==1)
  {
    printf("PVM Warning: No input file.\n");
    return -1;
  }
  printf("Reading %s\n",*(argv+1));
  VMReadFile(*(argv+1));
  //checkStructure(VMpe);
  clearFile(VMpe,CODE_RESERVED);
  printf("execution file loaded.\n");
  debugPrintConstraint();
  dispatcher();
  debugPrintMountingList();
  printf("dispatching finished\n");
  //mutexTinit();
  printf("mutex finished\n");
  graphStartUp(&argc,argv);
  pthread_create(&graphT,NULL,graphMonitor,NULL);
  VMStartUp();
  return 0;
}
