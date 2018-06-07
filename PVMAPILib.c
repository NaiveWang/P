#include "PVMAPILib.h"
void basicIO_Buffer(PBase* p)
{
  switch(*(((short*)&p->APICallID)+1))
  {
    case 0 :printf("%ld ",*(long*)p->exAddr);break;//print 8 i
    case 1 :printf("%c ",*(char*)p->exAddr);break;//print c c
    case 2 :printf("%s",(char*)p->exAddr);break;//print string
    case 3 :scanf("%ld",(long*)p->exAddr);break;//scan 8 i
    case 4 :scanf("%c",(char*)p->exAddr);break;//scan c c
    default:printf("API Error:no such calling identifier in basicIO_Buffer");
  }
}
void basicIO_File(PBase* p)
{
  static FILE *fp;
  switch(*(((short*)&p->APICallID)+1))
  {
    default:printf("API Error:no such calling identifier in basicIO_File");
  }
}
void APIHandler(PBase *p)
{
  switch(*(short*)&p->APICallID)
  {
    case 0:basicIO_Buffer(p);break;
    case 1:basicIO_File(p);break;
    default:printf("Error:unknown calling ID\n");
  }
}
const int apiir_n=2;
APIIR apiir[]={
  {0,0,"BUFF_PRINT_I10"},{0,3,"BUFF_SCAN_I10"}
  //{1,0}
};
int fetchAPI(char* target)
{
  static int *a0;
  static int a1;
  //find the ID
  for(a1=0;a1<apiir_n;a1++)
  {
    if(strcmp(target,apiir[a1].key)) continue;
    a0=(int*)&apiir[a1].apiNumber;
    return *a0;
  }
  return -1;
}
