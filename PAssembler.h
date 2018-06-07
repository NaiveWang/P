#ifndef PASSENBLER_H
#define PASSENBLER_H
#include <stdio.h>
#include <string.h>
#include "PCore.h"
#include "PFile.h"
#include "PVMAPILib.h"

#define IDENTIFIER '.'
#define BUFFER_SIZE 1024
#define NAME_BUFFER_SIZE 128
#define POSITION_NAME_SIZE 28
#define POSITION_NAME_LENGTH 500
//define identifier reserved key word
#define I_PROCESSOR "processor "
#define I_MUTEX "mutex "
#define I_INSTANCE "instance "
#define I_CONNECTION "connection "
#define I_CONSTRAINT "constraint "
#define I_DATA_SECTION ".data"
#define I_CODE_SECTION ".code"
//define parsing status
#define PS_START 0
#define PS_IN_PROCESSOR 1
#define PS_DATA_SECTION_GLOBAL 2
#define PS_DATA_SECTION 3
#define PS_CODESECTION 4
#define PS_MUTEX_SECTION 5
#define PS_INSTANCE_SECTION 6
#define PS_CONNECTIONS 7
#define PS_CONSTRAINTS 8
typedef struct positionNameElement
{
  int ofst;
  char name[POSITION_NAME_SIZE];
}pnl;
/** Global Variables **/
char inputBuffer[BUFFER_SIZE];
char identifierBuffer[NAME_BUFFER_SIZE];
pnl PNL[POSITION_NAME_LENGTH];
int PNLpointer;//backup the line number while backtracing
int inputBufferPointer;
FILE *input;//*output;
PExe *pe;
int parsingStatus;
int errno;
int parseLine;
//element list
char *pNameList;
char *iNameList;
char *mNameList;
//char *cNameList;
int pListNum,iListNum,cListNum,mListNum,sListNum;
/**Utility Function Section**/
int readLine();
char* nameSeek(char* s, int n);
int ifIdentifierOverdefined(char *List,int n);
int matchIdentifier(char *List,int n);
int strCopy(char *s,char *d);
int addIdentifier(char* t,char *List,int *n);
int countI();
int countC();
void parseString(void* base);
void skipWhitespace();
void skipIdentifier();
void skipString();
void countIdentifier();
void parseStart();
void parseProcessor();
void parseProcessorCode();
void parseProcessorData();
void parseMutex();
void parseConnection();
void parseInstance();
void parseInstanceData();
void parseConstraint();
void errorHandler();
void _debugShowNameList(char *list,int n);
/** Assembler main body **/
int main(int argv,char** argc)
{
  if(argv!=3)
  {
    printf("Error : lack of input file or output file.\n");
    //system("pause");
    return -1;
  }
  //argc+1: input file, text.
  //argc+2: output file, binary.
  pe=malloc(sizeof(PExe));
  //read input file.
  pe->processorTemplateNum=0;
  pe->mutexNum=0;
  pe->processorInstanceNUM=0;
  pe->connectionMappingNum=0;
  pe->constraintNum=0;
  input=fopen(*(argc+1),"r");
  if(input!=NULL) printf("reading file successful\n");
  else
  {
    printf("Error:File opening failure.\n");
    return -1;
  }
  //printf("counting emelemts\n");
  countIdentifier();
  printf("Template(s):%d\t",pe->processorTemplateNum);
  printf("Mutex(es):%d\t",pe->mutexNum);
  printf("Instance(s):%d\t",pe->processorInstanceNUM);
  printf("Connection(s):%d\t",pe->connectionMappingNum);
  printf("Constraint(s):%d\n",pe->constraintNum);
  fseek(input,0,SEEK_SET);
  //allocate the space,
  if(pe->processorTemplateNum)
  {
    pNameList=malloc(NAME_BUFFER_SIZE * pe->processorTemplateNum);
    pe->processorTemplates = malloc(sizeof(processorT) * pe->processorTemplateNum);
  }
  else
  {
    printf("Warning : No template found, cannot generate execution file.\n");
    return -1;
  }
  if(pe->mutexNum)
  {
    pe->mutexSizeList = malloc(sizeof(int) * pe->mutexNum);
    mNameList=malloc(NAME_BUFFER_SIZE * pe->mutexNum);
  }
  else
  {
    pe->mutexSizeList=NULL;
  }
  if(pe->processorInstanceNUM)
  {
    pe->processorInstances = calloc(pe->processorInstanceNUM,sizeof(processorI));
    iNameList=malloc(NAME_BUFFER_SIZE * pe->processorInstanceNUM);
  }
  else
  {
    printf("Warning : No instance found, cannot generate execution file.\n");
    return -1;
  }
  if(pe->connectionMappingNum)
  {
    //cNameList=malloc(NAME_BUFFER_SIZE * pe->connectionMappingNum);
    pe->connectionMapping = malloc(sizeof(connections) * pe->connectionMappingNum);
  }
  else
  {
    pe->connectionMapping = NULL;
  }
  if(pe->constraintNum) pe->constraintList = malloc(sizeof(constraints) * pe->constraintNum);
  else pe->constraintList=NULL;
  //allocate the space for element
  //if(pe->processorTemplateNum)
  //if(pe->mutexNum)
  //if(pe->processorInstanceNUM)
  //parse processor, record name and others
  //while(fgets(inputBuffer,NAME_BUFFER_SIZE,input)!=NULL) printf("%s",inputBuffer);
  parsingStatus = PS_START;
  errno = 0;
  parseLine=0;
  pListNum=0;
  iListNum=0;
  cListNum=0;
  mListNum=0;
  sListNum=0;
  /**if(readLine())
  {//read first line failed
    printf("Error:Cannot read file content.\n");
    return -1;
  }
  printf("%s\n",inputBuffer+inputBufferPointer);
  while(!readLine())
  {
    printf("%s\n",inputBuffer+inputBufferPointer);
  }
  //breakpoint 0
  return 0;*/
  printf("Parsing...\n");
  if(readLine())
  {
    printf("Error: cannot parse file.\n");
  }
  for(;;)
  {
    //parse with status
    //printf("parsing line:%d,%d\n",parseLine,parsingStatus);
    //getchar();
    switch(parsingStatus)
    {
      case PS_START:parseStart();break;
      case PS_IN_PROCESSOR:parseProcessor();break;
      case PS_DATA_SECTION_GLOBAL:parseProcessorData();break;
      case PS_DATA_SECTION:parseInstanceData();break;
      case PS_CODESECTION:parseProcessorCode();break;
      case PS_MUTEX_SECTION:parseMutex();break;
      case PS_INSTANCE_SECTION:parseInstance();break;
      case PS_CONNECTIONS:parseConnection();break;
      case PS_CONSTRAINTS:parseConstraint();break;
    }
    if(errno)
    {
      errorHandler();
      if(errno!=-1)
        return -1;
      break;
    }
    //_debugShowNameList(mNameList,mListNum);
    //parseLine++;
  }
  fclose(input);
  makeExeFile(*(argc+2),pe);
  //output=fopen(*(argc+2),"wb");
  printf("Finished.\n");
  //checkStructure(pe);
  clearFile(pe,CLEAR_ALL);
  free(iNameList);
  free(pNameList);
  free(mNameList);
  //printf("----------------------------------Checking execution file\n");
  //pe = parseFile(*(argc+2));
  //checkStructure(pe);
  //clearFile(pe,CLEAR_ALL);
  return 0;
}
#endif
