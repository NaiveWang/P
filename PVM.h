#ifndef PVM_H
#define PVM_H
/**
 * This is the header of Process VM
 * it describes the organization of the main body.
 * structures and utility functions.
 **/
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <GL/glut.h>
#include "PCore.h"
#include "PFile.h"
#include "PVMAPILib.h"
//<<<<<<< Updated upstream
#define NUM_E_THREAD 2
//#define M_WAITING_LIST_SIZE 256
//#define NUM_E_THREAD 2
//#define M_WAITING_LIST_SIZE 256
//>>>>>>> Stashed changes
#define INITIAL_PERFORMANCE_VAL 8
#define INITIAL_DELAY_VAL 2000
#define MAX_PERFORMANCE_VAL 32000
#define MAX_DELAY_VAL 500000
#define PRINTADDR(x) printf("ADDR:%lx\n",(long)(x))
#define SEEK_TABLE(x,y,a) ((x)+(y)*(a))
//graph global
#define GRAPH_WINDOW_L 600
#define GRAPH_WINDOW_H 400
#define GRAPH_SLEEPING_TIME 50000
#define TESTING_TIMER 5000000
/** MACRO Section **/
//the number of execution threads, it mainly depends on the hardware
//#define TN_EXE 3//my computer has 8 logical core, extended by the technology known as intel's hyper threading.
typedef struct instanceMountingLinkList
{
  PBase *instance;
  struct instanceMountingLinkList *next;
}IMLList;
typedef struct instanceMountingElement
{
  int INumber;
  IMLList *start;
  IMLList *list;
}IME;
typedef struct waitLinkList
{
  PBase *pid;
  struct waitLinkList *next;
}waitL;
typedef struct MutexStructure
{
  unsigned long size;
  void* lock;//can be used to the id of threads
  void* content;
  waitL *waitList;
}mutex;
typedef struct haltInformations
{
  PBase *pid;
  int val;
}hInfo;
#define MTX_HDL_TYP_WAIT 0
#define MTX_HDL_TYP_TEST 1
#define MTX_HDL_TYP_LEAVE 2
//#define TRIGGER 3
typedef struct mutexHandlerWaitingQueue
{
  PBase *pid;
  int opTyp;
  mutex *mTarget;
}MHQ;
typedef struct triggerListElement
{
  int number;
  int *list;
}tgr;
typedef struct graphInstancePosition
{
  float x;
  float y;
}gPos;
/** Global Section **/
//necassary sole data
PExe *VMpe;
//Lists & boundary
int listCodeSize;
void* *listCode;
int listMutexSize;
mutex *listMutex;
int listInstanceSize;
PBase *listInstance;
//halt
hInfo haltInfo;
//mutex handler global
pthread_mutex_t rtLock;
pthread_mutex_t rtExecLock;
pthread_mutex_t triggerLock;
//pthread_mutex_t qLock;
pthread_mutex_t haltExecLock;
//int queueH,queueT;
//MHQ waitingQueue[M_WAITING_LIST_SIZE];
MHQ mutexHandlerArg;
//thread pool
pthread_t haltT;
//pthread_t constraintHandler;
pthread_t mutexT;
pthread_t executionThread[NUM_E_THREAD];
pthread_t graphT;
pthread_t testingT;
IME executionGroup[NUM_E_THREAD];
//global variables
tgr *triggerList;
/** Error Handle Val **/
int errno;
/** graph global section **/
gPos *gpp;
float graph_size;
//Statistic Data
/** utility functions **/
/** mutex **/
//void mutexTinit();
void *mutexHandler();
/** Functions **/
void VMReadFile(char *file);
void debugVM(PBase *p,int howManyStack0Elem);
void debugPrintConstraint();
void debugPrintMountingList();
void *execDebug(void* no);
void *execNormal();
void dispatcher();
void VMStartUp();
void *VMHalt();
void graphStartUp(int* argv,char **argc);
void graphShape();
void graphDrawInstance(int id);
void graphDisp();
void *graphMonitor();
void handlerSegFault(int);
void releaseMemory();
void handlerKilled();
void *performanceCounter();
#endif
