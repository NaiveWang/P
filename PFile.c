#include "PFile.h"
PExe* parseFile(char *fileS)
{
  static int count;
  FILE *fp=fopen(fileS,"rb");
  PExe *pe=malloc(sizeof(PExe));
  fread(&pe->processorTemplateNum,sizeof(int),1,fp);//get number of P
  pe->processorTemplates=malloc(sizeof(processorT)*pe->processorTemplateNum);//allocate accomdation
  for(count=0;count < pe->processorTemplateNum;count++)
  {//processor template
    processorT *ppt=pe->processorTemplates+count;
    fread(&ppt->codeLength,sizeof(int),1,fp);//get Code length
    ppt->code = malloc(ppt->codeLength);//allocate space first
    fread(ppt->code,1,ppt->codeLength,fp);//get code section
    fread(&ppt->stack0Size,sizeof(int),1,fp);//get size of stack0
    fread(&ppt->stackSize,sizeof(int),1,fp);//get size of stack
    fread(&ppt->globalSize,sizeof(int),1,fp);
    fread(&ppt->initNumGlobal,sizeof(int),1,fp);//get the list size
    if(ppt->initNumGlobal)
    {
      ppt->initDataGlobal = malloc(sizeof(initD) * ppt->initNumGlobal);//allocate space
      {
        int count1 = ppt->initNumGlobal;
        while(count1--)
        {//read the initializing data into the memory, need to allocate space.
          fread(&(ppt->initDataGlobal + count1)->offset,sizeof(int),1,fp);
          fread(&(ppt->initDataGlobal + count1)->length,sizeof(int),1,fp);
          (ppt->initDataGlobal + count1)->data = malloc((ppt->initDataGlobal + count1)->length);
          fread((ppt->initDataGlobal + count1)->data,1,(ppt->initDataGlobal + count1)->length,fp);
          //bingo
        }
      }
    }
    else ppt->initDataGlobal=NULL;

  }
  //template finished
  fread(&pe->mutexNum,sizeof(int),1,fp);//get number of mutex
  if(pe->mutexNum)
  {
    pe->mutexSizeList=malloc(sizeof(int) * pe->mutexNum);//allocate
    fread(pe->mutexSizeList,sizeof(int),pe->mutexNum,fp);//get data directly.
  }
  else pe->mutexSizeList=NULL;
  //mutex finished
  fread(&pe->processorInstanceNUM,sizeof(int),1,fp);

  //allocate first!!
  pe->processorInstances=malloc(sizeof(processorI) * pe->processorInstanceNUM);
  for(count=0;count<pe->processorInstanceNUM;count++)
  {//get instancelist
    processorI *ppi=pe->processorInstances+count;
    fread(&ppi->processorReferenceNo,sizeof(int),1,fp);//number
    fread(&ppi->initStatus,sizeof(int),1,fp);
    fread(&ppi->initNum,sizeof(int),1,fp);//get the list size
    if(ppi->initNum)
    {
      ppi->initData = malloc(sizeof(initD) * ppi->initNum);//allocate space
      {
        int count1 = ppi->initNum;
        while(count1--)
        {//read the initializing data into the memory, need to allocate space.
          fread(&(ppi->initData + count1)->offset,sizeof(int),1,fp);
          fread(&(ppi->initData + count1)->length,sizeof(int),1,fp);
          (ppi->initData + count1)->data = malloc((ppi->initData + count1)->length);
          fread((ppi->initData + count1)->data,1,(ppi->initData + count1)->length,fp);
          //bingo
        }
      }
    }
    else ppi->initData=NULL;
  }
  //instances finished
  fread(&pe->connectionMappingNum,sizeof(int),1,fp);

  if(pe->connectionMappingNum)
  {
    pe->connectionMapping = malloc(sizeof(connections) * pe->connectionMappingNum);
    fread(pe->connectionMapping,sizeof(connections),pe->connectionMappingNum,fp);
  }
  else pe->connectionMapping=NULL;
  //finished
  fread(&pe->constraintNum,sizeof(int),1,fp);
  if(pe->constraintNum)
  {
    //allocate space
    pe->constraintList = malloc(sizeof(constraints) * pe->constraintNum);
    //read each constraints
    for(count=0;count<pe->constraintNum;count++)
    {
      //read in top-down style
      fread(&pe->constraintList[count].nodeDNo,sizeof(int),1,fp);
      fread(&pe->constraintList[count].nodeSNum,sizeof(int),1,fp);
      //allocate
      pe->constraintList[count].nodeSNoList = malloc(sizeof(int) * pe->constraintList[count].nodeSNum);
      fread(pe->constraintList[count].nodeSNoList,sizeof(int),pe->constraintList[count].nodeSNum,fp);
      //bingo
    }
  }
  else pe->constraintList=NULL;
  fclose(fp);
  return pe;
}
void makeExeFile(char *fileS, PExe *pe)
{
  //open the file
  static unsigned int a0,a1;
  FILE *fp=fopen(fileS,"wb");
  //write the template number
  fwrite(&pe->processorTemplateNum,sizeof(int),1,fp);
  //loop, write each processor
  for(a0=0;a0<pe->processorTemplateNum;a0++)
  {
    //write code length int
    fwrite(&pe->processorTemplates[a0].codeLength,sizeof(int),1,fp);
    //write code block
    fwrite(pe->processorTemplates[a0].code,1,pe->processorTemplates[a0].codeLength,fp);
    //write stack0 size int
    fwrite(&pe->processorTemplates[a0].stack0Size,sizeof(int),1,fp);
    //write stack size int
    fwrite(&pe->processorTemplates[a0].stackSize,sizeof(int),1,fp);
    fwrite(&pe->processorTemplates[a0].globalSize,sizeof(int),1,fp);
    //write initializing group number
    fwrite(&pe->processorTemplates[a0].initNumGlobal,sizeof(int),1,fp);
    //loop, write init-data
    for(a1=0;a1<pe->processorTemplates[a0].initNumGlobal;a1++)
    {
      //write offset into
      fwrite(&pe->processorTemplates[a0].initDataGlobal[a1].offset,sizeof(int),1,fp);
      //write length int
      fwrite(&pe->processorTemplates[a0].initDataGlobal[a1].length,sizeof(int),1,fp);
      //write data block
      fwrite(pe->processorTemplates[a0].initDataGlobal[a1].data,1,pe->processorTemplates[a0].initDataGlobal[a1].length,fp);
    }
  }
  //write mutex
  //write mutex number int
  fwrite(&pe->mutexNum,sizeof(int),1,fp);
  if(pe->mutexNum)
  {
    //write mutex size array
    fwrite(pe->mutexSizeList,sizeof(int),pe->mutexNum,fp);
  }
  //write instance
  //write instance number int
  fwrite(&pe->processorInstanceNUM,sizeof(int),1,fp);
  //loop, write each instance
  for(a0=0;a0<pe->processorInstanceNUM;a0++)
  {
    //write reference number int
    fwrite(&pe->processorInstances[a0].processorReferenceNo,sizeof(int),1,fp);
    fwrite(&pe->processorInstances[a0].initStatus,sizeof(int),1,fp);
    //write init nember int
    fwrite(&pe->processorInstances[a0].initNum,sizeof(int),1,fp);
    //loop, write all if the initializing data.
    for(a1=0;a1<pe->processorInstances[a0].initNum;a1++)
    {
      //write offset into
      fwrite(&pe->processorInstances[a0].initData[a1].offset,sizeof(int),1,fp);
      //write length int
      fwrite(&pe->processorInstances[a0].initData[a1].length,sizeof(int),1,fp);
      //write data block
      fwrite(pe->processorInstances[a0].initData[a1].data,1,pe->processorInstances[a0].initData[a1].length,fp);
    }
  }
  //write connections
  //write connection number int
  fwrite(&pe->connectionMappingNum,sizeof(int),1,fp);
  //write connection array
  if(pe->connectionMappingNum)
  {
    fwrite(pe->connectionMapping,sizeof(connections),pe->connectionMappingNum,fp);
  }
  //write constraints
  fwrite(&pe->constraintNum,sizeof(int),1,fp);
  for(a0=0;a0<pe->constraintNum;a0++)
  {
    fwrite(&pe->constraintList[a0].nodeDNo,sizeof(int),1,fp);
    fwrite(&pe->constraintList[a0].nodeSNum,sizeof(int),1,fp);
    fwrite(pe->constraintList[a0].nodeSNoList,sizeof(int),pe->constraintList[a0].nodeSNum,fp);
  }
  //finished
  fclose(fp);
}
void clearFile(PExe *pe,char flag)
{//this funtion free all of the memory of a PEXE struct
  //except for the code section
  static unsigned int a0,a1;
  //loop, free processorTemplates

  for(a0=0;a0<pe->processorTemplateNum;a0++)
  {//putchar('$');
    //reserve the code section
    if(flag==CLEAR_ALL) free(pe->processorTemplates[a0].code);
    //free the list of init-data;
    for(a1=0;a1<pe->processorTemplates[a0].initNumGlobal;a1++)
    {
      free(pe->processorTemplates[a0].initDataGlobal[a1].data);
    }
    free(pe->processorTemplates[a0].initDataGlobal);
  }
  free(pe->processorTemplates);
  //free mutexList

  if(pe->mutexSizeList)
    free(pe->mutexSizeList);

  //free inmstance list, loop
  for(a0=0;a0<pe->processorInstanceNUM;a0++)
  {
    //free the list of init-data;
    for(a1=0;a1<pe->processorInstances[a0].initNum;a1++)
    {
      free(pe->processorInstances[a0].initData[a1].data);
    }
    free(pe->processorInstances[a0].initData);
  }
  //printf("#%d\n",pe->processorInstances);
  free(pe->processorInstances);

  //free connection List
  if(pe->connectionMapping)
    free(pe->connectionMapping);
  //printf("$\n");
  if(pe->constraintNum)
  {
    for(a0=0;a0<pe->constraintNum;a0++)
    {
      free(pe->constraintList[a0].nodeSNoList);
    }
    free(pe->constraintList);
  }
  free(pe);
}
void checkStructure(PExe *pe)
{
  static int a0,a1;
  printf("T:%d\tM:%d\tI:%d\tC:%d\tS:%d\n",pe->processorTemplateNum,pe->mutexNum,pe->processorInstanceNUM,pe->connectionMappingNum,pe->constraintNum);
  for(a0=0;a0<pe->processorTemplateNum;a0++)
  {
    printf("#%d",pe->processorTemplates[a0].codeLength);
    printf("#%d",pe->processorTemplates[a0].stack0Size);
    printf("#%d",pe->processorTemplates[a0].stackSize);
    printf("#%d",pe->processorTemplates[a0].globalSize);
    printf("#%d\n",pe->processorTemplates[a0].initNumGlobal);
  }
  for(a0=0;a0<pe->mutexNum;a0++)
  {
    printf("$%d",pe->mutexSizeList[a0]);
  }
  printf("\n");
  for(a0=0;a0<pe->processorInstanceNUM;a0++)
  {
    printf("@%d",pe->processorInstances[a0].processorReferenceNo);
    printf("@%d\n",pe->processorInstances[a0].initNum);
  }
  for(a0=0;a0<pe->connectionMappingNum;a0++)
  {
    printf("!%d",pe->connectionMapping[a0].nodeSNo);
    printf("!%d",pe->connectionMapping[a0].nodeSPort);
    printf("!%d",pe->connectionMapping[a0].nodeDType);
    printf("!%d\n",pe->connectionMapping[a0].nodeDNo);
  }
  for(a0=0;a0<pe->constraintNum;a0++)
  {
    printf("+%d",pe->constraintList[a0].nodeDNo);
    printf("+%d",pe->constraintList[a0].nodeSNum);//getchar();
    printf("+%d\n",*pe->constraintList[a0].nodeSNoList);
  }
}
