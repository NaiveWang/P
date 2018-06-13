#include <stdio.h>
#include "PVM.h"
#define EN_STEP 's'
#define EN_DEBUG 'd'
#define EN_GRAPH 'g'
char flag_graph;
char flag_step;
char flag_debug;
void flag_init();
int main(int argc,char **argv)
{
  int a0;
  signal(SIGSEGV,handlerSegFault);
  if(argc==1)
  {
    printf("PVM Warning: No input file.\n");
    return -1;
  }
  flag_init();
  //read argv
  for(a0=2;a0<argc;a0++)
  {
    //the configuration section
    if(argv[a0][0] == '-')
    {
      switch(argv[a0][1])
      {
        case EN_GRAPH:flag_graph=1;break;
        case EN_DEBUG:flag_debug=1;break;
        case EN_STEP:flag_step=1;break;
        default:
          printf("Error : unknown argument.\n");
          return -1;
      }
    }
    else
    {
      printf("Error : Bad argument at %d\n",a0-1);
      return -1;
    }
  }
  //check confliction
  if(flag_step && flag_debug)
  {
    printf("runtime mode conflict.\n");
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
  /*conf start*/
  //make graph
  if(flag_graph)
  {
    graphStartUp(&argc,argv);
    pthread_create(&graphT,NULL,graphMonitor,NULL);
  }
  //mode selection
  else if(flag_step)
  {
    //step

  }
  else if(flag_debug)
  {
    //show debug info
  }
  else
  {
    //normal
    VMStartUp();
  }
  /*conf finished*/
  return 0;
}
void flag_init()
{
  //
  flag_graph=0;
  flag_step=0;
  flag_debug=0;
}
