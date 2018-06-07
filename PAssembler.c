#include "PAssembler.h"
void countIdentifier()
{
    while(!readLine())
    {

      if(*(inputBuffer+inputBufferPointer) == IDENTIFIER)
      {
        inputBufferPointer++;
        //printf("%s\n",inputBuffer+inputBufferPointer);
        //printf("%ld\n",strlen(I_PROCESSOR));
        if(!strncmp(inputBuffer+inputBufferPointer,I_PROCESSOR,strlen(I_PROCESSOR))) pe->processorTemplateNum++;
        else if(!strncmp(inputBuffer+inputBufferPointer,I_MUTEX,strlen(I_MUTEX))) pe->mutexNum++;
        else if(!strncmp(inputBuffer+inputBufferPointer,I_INSTANCE,strlen(I_INSTANCE))) pe->processorInstanceNUM++;
        else if(!strncmp(inputBuffer+inputBufferPointer,I_CONNECTION,strlen(I_CONNECTION))) pe->connectionMappingNum++;
        else if(!strncmp(inputBuffer+inputBufferPointer,I_CONSTRAINT,strlen(I_CONSTRAINT))) pe->constraintNum++;
      }
    }
}
int readLine()
{
  static int a0;
  while(fgets(inputBuffer,NAME_BUFFER_SIZE,input))
  {
    inputBufferPointer=0;
    while(inputBuffer[inputBufferPointer]==' '||inputBuffer[inputBufferPointer]=='\t') inputBufferPointer++;//skip whitespaces in one line
    if(inputBuffer[inputBufferPointer]=='\n'||inputBuffer[inputBufferPointer]==';')
    {
      parseLine++;
      continue;//skip empty lines
    }
    //convert \n to NULL
    a0=inputBufferPointer;
    while(inputBuffer[a0]^'\n'&&inputBuffer[a0]^';') a0++;
    inputBuffer[a0]=0;
    parseLine++;
    //printf("%d#%s\n",parseLine,inputBuffer+inputBufferPointer);
    //printf("#%s#\n",inputBuffer+inputBufferPointer);
    return 0;
  }
  inputBuffer[0]=0;
  return -1;
}
char* nameSeek(char* s, int n)
{
  return s + n*NAME_BUFFER_SIZE;
}
int strCopy(char *s,char *d)
{
  static int a0;
  a0=0;
  //printf("&%s&\n",s);
  while((*s != '\n')&&(*s != ' ')&&(*s != '\t')&&(*s != ';')&&(*s != ','&&(*s != '\0')))
  {
    //printf("%d/",*s);
    *d = *s;
    d++;
    s++;
    a0++;
  }
  *d=0;
  return a0;
}
int ifIdentifierOverdefined(char *List,int n)
{//search if exist one match, return -1;
  //strCopy(target,identifierBuffer);
  while(n--)
  {
    if(!strcmp(identifierBuffer,nameSeek(List,n))) return -1;
  }
  return 0;
}
int matchIdentifier(char *List,int n)
{
  //strCopy(target,identifierBuffer);
  while(n--)
  {
    if(!strcmp(identifierBuffer,nameSeek(List,n))) return n;
  }
  errno=3;
  return -1;
}
int addIdentifier(char* t,char *List,int *n)
{

  strcpy(nameSeek(List,*n),t);
  (*n)++;
}
void skipWhitespace()
{
  while(inputBuffer[inputBufferPointer]==' '||inputBuffer[inputBufferPointer]=='\t') inputBufferPointer++;
}
void skipIdentifier()
{
  while(inputBuffer[inputBufferPointer]!=' '&&inputBuffer[inputBufferPointer]!='\t'&&inputBuffer[inputBufferPointer]!=','&&inputBuffer[inputBufferPointer]!='\0') inputBufferPointer++;
}
void skipString()
{
  inputBufferPointer++;
  while(inputBuffer[inputBufferPointer]!='"')
  {
    if(inputBuffer[inputBufferPointer]=='\\') inputBufferPointer+=2;
    else inputBufferPointer++;
  }
  inputBufferPointer++;
}
void parseStart()
{
  if(*inputBuffer==0)
  {
    errno=-1;
    return;
  }
  if(inputBuffer[inputBufferPointer]==IDENTIFIER)
  {//identifier get successful
    inputBufferPointer++;
    if(!strncmp(inputBuffer+inputBufferPointer,I_PROCESSOR,strlen(I_PROCESSOR)))
    {//into processor
      inputBufferPointer+=strlen(I_PROCESSOR);
      //printf("1\n");
      parsingStatus=PS_IN_PROCESSOR;
    }
    else if(!strncmp(inputBuffer+inputBufferPointer,I_MUTEX,strlen(I_MUTEX)))
    {
      inputBufferPointer+=strlen(I_MUTEX);
      //printf("2\n");
      parsingStatus=PS_MUTEX_SECTION;
    }
    else if(!strncmp(inputBuffer+inputBufferPointer,I_INSTANCE,strlen(I_INSTANCE)))
    {
      inputBufferPointer+=strlen(I_INSTANCE);
      //printf("3\n");
      parsingStatus=PS_INSTANCE_SECTION;
    }
    else if(!strncmp(inputBuffer+inputBufferPointer,I_CONNECTION,strlen(I_CONNECTION)))
    {
      inputBufferPointer+=strlen(I_CONNECTION);
      //printf("4\n");
      parsingStatus=PS_CONNECTIONS;
    }
    else if(!strncmp(inputBuffer+inputBufferPointer,I_CONSTRAINT,strlen(I_CONSTRAINT)))
    {
      inputBufferPointer+=strlen(I_CONSTRAINT);
      //printf("4\n");
      parsingStatus=PS_CONSTRAINTS;
    }
    else errno=2;
  }
  //else errno=1;
}
int countI()
{
  static unsigned int a0,a1;
  a1=0;
  for(a0=0;inputBuffer[inputBufferPointer+a0]!='\n'&&inputBuffer[inputBufferPointer+a0]!=';'&&inputBuffer[inputBufferPointer+a0]!=0;a0++)
  {
    //printf("!%d",a0);
    if(inputBuffer[inputBufferPointer+a0]==',') a1++;
  }
  return a1+1;
}
int countC()
{
  //
  static int a0,a1;
  //get the first '"'
  //skipWhitespace();
  a0=0;
  a1=0;//printf(":%s\n",inputBuffer+inputBufferPointer+a1);
  if(inputBuffer[inputBufferPointer+a1]=='"')
  {//right, go on
     //if match '\', +2, else +1
     a1++;
     //printf(":%s\n",inputBuffer+inputBufferPointer+a1);
     while(inputBuffer[inputBufferPointer+a1]!='"')
     {
       //printf(":%s\n",inputBuffer+inputBufferPointer+a1);
         if(inputBuffer[inputBufferPointer+a1]=='\\') a1+=2;
         else a1++;
         a0++;
     }
     return a0;
  }
  else
  {
      errno=13;
      return 0;
  }
}
void parseString(void* base)
{
    static int a0;
    //skip the first closure sign
    ///make sure U have skipped the whitespace already.
    inputBufferPointer++;
    a0=0;
    //printf("^^^^^^%s\n",inputBuffer+inputBufferPointer);
    //loop, parse and copy to base+n
    while(inputBuffer[inputBufferPointer]!='"')
    {//meet to to end
        //parse the character
        if(inputBuffer[inputBufferPointer]=='\\')
        {
            static char c0;
            inputBufferPointer++;
            //get a slash
            switch(inputBuffer[inputBufferPointer])
            {
                case '0':
                    c0='\0';
                    break;
                case 'n':
                    c0='\n';
                    break;
                case 't':
                    c0='\t';
                    break;
                default:
                    c0=inputBuffer[inputBufferPointer];
            }
            *(char*)(base+a0)=c0;
        }
        else
        {
            *(char*)(base+a0)=inputBuffer[inputBufferPointer];
            //normal step
        }
        inputBufferPointer++;
        a0++;
        //move pointer
    }
    inputBufferPointer++;
}
void parseProcessor()
{
  static int a0;
  //get processor name
  skipWhitespace();
  inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
  //check if overrided:error return
  if(ifIdentifierOverdefined(pNameList,pListNum))
  {
    errno = 4;
    return;
  }
  //not override, push table to 新时代
  addIdentifier(identifierBuffer,pNameList,&pListNum);
  //get stack0 int
  skipWhitespace();
  sscanf(inputBuffer+inputBufferPointer,"%d",&a0);
  skipIdentifier();
  pe->processorTemplates[pListNum-1].stack0Size=a0;
  //get stack int
  skipWhitespace();
  sscanf(inputBuffer+inputBufferPointer,"%d",&a0);
  skipIdentifier();
  pe->processorTemplates[pListNum-1].stackSize=a0;
  //get data size
  skipWhitespace();
  sscanf(inputBuffer+inputBufferPointer,"%d",&a0);
  //skipIdentifier();
  pe->processorTemplates[pListNum-1].globalSize=a0;
  //set some pointer to NULL at first
  pe->processorTemplates[pListNum-1].initDataGlobal=NULL;
  //next line
  if(readLine())
  {
    errno=8;
    return;
  }
  //skipWhitespace();
  //look up for segment
  //printf("#%s#\n",inputBuffer+inputBufferPointer);
  if(!strncmp(inputBuffer+inputBufferPointer,I_DATA_SECTION,strlen(I_DATA_SECTION)))
  {//data segment
    parsingStatus=PS_DATA_SECTION_GLOBAL;
  }
  else if(!strncmp(inputBuffer+inputBufferPointer,I_CODE_SECTION,strlen(I_CODE_SECTION)))
  {//code segment
    parsingStatus=PS_CODESECTION;
  }
  else
  {//cannot find proper segment
        //printf("$$");
    errno=8;
    return;
  }
}
void parseProcessorCode()
{
    static long fb;
    static int a0,a1,a2,a3;
  ///1.calculate length of code section.
  //backup file pointer
  fb=ftell(input);
  a3=parseLine;
  //loop:count length of each instruction until meet the . identifier
  //initialize the date first
  a0=0;
  PNLpointer=0;
  while(!readLine())
  {
      if(inputBuffer[inputBufferPointer]==IDENTIFIER) break;
      else if(inputBuffer[inputBufferPointer]=='#')
      {
        inputBufferPointer++;
        //record name and offset
        strCopy(inputBufferPointer+inputBuffer,identifierBuffer);
        for(a2=0;a2<PNLpointer;a2++)
        {
          if(strcmp(PNL[a2].name,identifierBuffer)) continue;
          errno=17;//conflict position name
          return;
        }
        //new position
        strcpy(PNL[PNLpointer].name,identifierBuffer);
        PNL[PNLpointer].ofst=a0;
        PNLpointer++;
        continue;
      }
      //find the instruction
      strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
      //printf("&%s&\n",identifierBuffer);
      instructionParser(&a1,identifierBuffer);
      //printf("&%s&%d&\n",identifierBuffer,a1);
      if(!a1)
      {//error handler: unknown instructions
          errno=14;
          return;
      }
      //count the number
      a0+=a1;
  }
  //test section start
  /**for(a1=0;a1<PNLpointer;a1++)
  {
    printf("%d\t%s\n",PNL[a1].ofst,PNL[a1].name);
  }*/
  //test section ended
  ///2.allocate the space of code section.
  if(!a0)
  {//zero instructions
      errno=12;//error
      return;
  }
  //allocate code space
  pe->processorTemplates[pListNum-1].codeLength=a0;
  pe->processorTemplates[pListNum-1].code = malloc(a0);
  ///3.recover file pointer, start parsing step
  //recover file pointer
  fseek(input,fb,SEEK_SET);
  parseLine=a3;
  //loop, parse instructions
  a1=0;//code section offset
  while(!readLine())
  {
      static char c0;
      static unsigned short id;
      if(inputBuffer[inputBufferPointer]==IDENTIFIER) break;
      else if(inputBuffer[inputBufferPointer]=='#') continue;
      //switch the instructions;
      strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
      id=instructionParser(&a0,identifierBuffer);
      skipIdentifier();
      *(unsigned short*)(pe->processorTemplates[pListNum-1].code+a1)=id;
      switch(a0)
      {//the content parsing step
          case 2://no operand
              break;
          case 12://2 groups of base:offset
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%d:%d",&a2,&a3);
            c0=(char)a2;
            *(char*)(pe->processorTemplates[pListNum-1].code+a1+2)=c0;
            *(int*)(pe->processorTemplates[pListNum-1].code+a1+3)=a3;
            skipIdentifier();
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%d:%d",&a2,&a3);
            c0=(char)a2;
            *(char*)(pe->processorTemplates[pListNum-1].code+a1+7)=c0;
            *(int*)(pe->processorTemplates[pListNum-1].code+a1+8)=a3;
            break;//todo
          case 7://1 group of base:offset
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%d:%d",&a2,&a3);
            c0=(char)a2;
            *(char*)(pe->processorTemplates[pListNum-1].code+a1+2)=c0;
            *(int*)(pe->processorTemplates[pListNum-1].code+a1+3)=a3;
            break;//todo
          case 10://8byte instant number
            skipWhitespace();
            switch(inputBuffer[inputBufferPointer])
            {
              case 'I':
                inputBufferPointer++;
                skipWhitespace();
                sscanf(inputBuffer+inputBufferPointer,"%ld",(long*)(pe->processorTemplates[pListNum-1].code+a1+2));
                break;
              case 'R':
                inputBufferPointer++;
                skipWhitespace();
                sscanf(inputBuffer+inputBufferPointer,"%lf",(double*)(pe->processorTemplates[pListNum-1].code+a1+2));
                break;
              case '#':
                inputBufferPointer++;
                strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
                for(a2=0;a2<PNLpointer;a2++)
                {
                  //printf("#%s#%s#",identifierBuffer,PNL[a2].name);
                  if(!strcmp(identifierBuffer,PNL[a2].name))
                  {//match
                    *(long*)(pe->processorTemplates[pListNum-1].code+a1+2)=(long)(PNL[a2].ofst-a1);
                    //printf("$%ld$\n",*(long*)(pe->processorTemplates[pListNum-1].code+a1+2));
                    //if(*(long*)(pe->processorTemplates[pListNum-1].code+a1+2) > 0)
                      //*(long*)(pe->processorTemplates[pListNum-1].code+a1+2)+=a0;
                    //printf("\t%ld\n",*(long*)(pe->processorTemplates[pListNum-1].code+a1+2));
                    break;
                  }
                  //else continue;
                }
                if(a2==PNLpointer)
                {
                  errno=18;
                  return;
                }
                break;
              default:
                errno=15;
                return;
            }
            //sscanf(inputBuffer+inputBufferPointer,"%ld",(long*)(pe->processorTemplates[pListNum].code+a1+2));
            break;
          case 6://4byte, find with system call number
            skipWhitespace();
            strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
            a2=fetchAPI(identifierBuffer);
            if(a2==-1)
            {
              //handle error:api function not found
              errno=16;
              return;
            }
            *(int*)(pe->processorTemplates[pListNum-1].code+a1+2) = a2;
            break;//todo
          case 3://1 byte instant
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%c",(char*)(pe->processorTemplates[pListNum-1].code+a1+2));
            break;
          case 14://4 byte mask instant, 8 byte offset
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%d",(int*)(pe->processorTemplates[pListNum-1].code+a1+2));
            skipIdentifier();
            skipWhitespace();
            //sscanf(inputBuffer+inputBufferPointer,"%ld",(long*)(pe->processorTemplates[pListNum-1].code+a1+6));
            strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
            for(a2=0;a2<PNLpointer;a2++)
            {
              if(!strcmp(identifierBuffer,PNL[a2].name))
              {//match
                *(long*)(pe->processorTemplates[pListNum-1].code+a1+6)=(long)(PNL[a2].ofst-a1);
                //if(*(long*)(pe->processorTemplates[pListNum-1].code+a1+2) > 0)
                  //*(long*)(pe->processorTemplates[pListNum-1].code+a1+2)+=a0;
                break;
              }
              errno=18;
              return;
            }
            break;//todo
      }
      //move pointer forward
      a1+=a0;
  }
  //set next status
  parsingStatus=PS_START;
  //end;
}
void parseProcessorData()
{
  static long fptr;
  static int ofst,a0,a1,a2,a3;
  //back up pointer
  fptr = ftell(input);
  //backup line pointer
  a0=parseLine;
  //loop,count element's number.
  for(a1=0;!readLine();)
  {//counter:a1
    //met . : break
    //printf("#%s\n",inputBuffer+inputBufferPointer);
    //getchar();
    if(inputBuffer[inputBufferPointer]==IDENTIFIER) break;
    else if(inputBuffer[inputBufferPointer]=='I'||inputBuffer[inputBufferPointer]=='R'||inputBuffer[inputBufferPointer]=='C') a1++;
  }
  //a0=0, error
  //printf("@%d",a1);
  if(!a1)
  {
    errno = 9;
    return;
  }
  //allocate space
  pe->processorTemplates[pListNum-1].initNumGlobal=a1;
  pe->processorTemplates[pListNum-1].initDataGlobal = malloc(sizeof(initD) * a1);
  //reatore the file pointer & line pointer
  parseLine=a0;
  fseek(input,fptr,SEEK_SET);
  //read file, start parse loop
  ofst=0;
  for(a0=0;!readLine();)
  {//a0:element no
    if(inputBuffer[inputBufferPointer]==IDENTIFIER) break;
    switch(inputBuffer[inputBufferPointer])
    {//parse each line
      case 'O'://set offset/ O <int>
        inputBufferPointer++;
        skipWhitespace();
        sscanf(inputBuffer+inputBufferPointer,"%d",&a1);
        ofst=a1;
        break;
      case 'S'://set skip value S <int>
        inputBufferPointer++;
        skipWhitespace();
        sscanf(inputBuffer+inputBufferPointer,"%d",&a1);
        ofst+=a1;
        break;
      case 'I'://integer
        inputBufferPointer++;
        skipWhitespace();
        //getchar();
        if(inputBuffer[inputBufferPointer]=='F')
        {//fixed size
          static int f;
          inputBufferPointer++;
          skipWhitespace();
          sscanf(inputBuffer+inputBufferPointer,"%d",&f);
          //allocate space
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].offset=ofst;
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].length=f * 8;
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].data=malloc(f*8);
          //write space
          skipIdentifier();
          //skipWhitespace();
          a1=countI();
          for(a2=0;a2<a1;a2++)
          {
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%ld",(long*)(pe->processorTemplates[pListNum-1].initDataGlobal[a0].data + a2 * 8));
            skipIdentifier();
            skipWhitespace();
            inputBufferPointer++;
          }
        }
        else
        {
          a1=countI();
          //printf("@%d@%d\n",a1,a0);
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].offset=ofst;

          pe->processorTemplates[pListNum-1].initDataGlobal[a0].length=a1 * 8;
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].data=malloc(a1*8);
          //printf("ADDR%ld\n",pe->processorTemplates[pListNum-1].initDataGlobal[a0].data);
          //printf("@%d@%d\n",a1,a0);
          for(a2=0;a2<a1;a2++)
          {
            skipWhitespace();
            //printf("$%s\n",inputBuffer+inputBufferPointer);
            sscanf(inputBuffer+inputBufferPointer,"%ld",(long*)(pe->processorTemplates[pListNum-1].initDataGlobal[a0].data + a2 * 8));
            skipIdentifier();//getchar();
            skipWhitespace();
            inputBufferPointer++;
          }
        }

        //printf("$%d/%d\t",ofst,a1);
        ofst+=pe->processorTemplates[pListNum-1].initDataGlobal[a0].length;
        a0++;
        //printf("$%d\n",ofst);
        break;
      case 'R':
        inputBufferPointer++;
        skipWhitespace();
        if(inputBuffer[inputBufferPointer]=='F')
        {//fixed size
          static int f;
          inputBufferPointer++;
          skipWhitespace();
          sscanf(inputBuffer+inputBufferPointer,"%d",&f);
          //allocate space
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].offset=ofst;
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].length=f * 8;
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].data=malloc(f*8);
          //write space
          skipIdentifier();
          //skipWhitespace();
          a1=countI();
          for(a2=0;a2<a1;a2++)
          {
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%lf",(double*)(pe->processorTemplates[pListNum-1].initDataGlobal[a0].data + a2 * 8));
            skipIdentifier();
            skipWhitespace();
            inputBufferPointer++;
          }
        }
        else
        {
          a1=countI();
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].offset=ofst;
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].length=a1 * 8;
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].data=malloc(a1*8);
          for(a2=0;a2<a1;a2++)
          {
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%lf",(double*)(pe->processorTemplates[pListNum-1].initDataGlobal[a0].data + a2 * 8));
            skipIdentifier();
            skipWhitespace();
            inputBufferPointer++;
          }
        }

        ofst+=pe->processorTemplates[pListNum-1].initDataGlobal[a0].length;
        a0++;
        break;
      case 'C':
        inputBufferPointer++;
        skipWhitespace();
        if(inputBuffer[inputBufferPointer]=='L')
        {//length appointed
          static int l;
          inputBufferPointer++;
          skipWhitespace();
          sscanf(inputBuffer+inputBufferPointer,"%d",&l);
          skipIdentifier();
          skipWhitespace();
          if(inputBuffer[inputBufferPointer]=='F')
          {//fixed size
            static int f;
            //
            inputBufferPointer++;
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%d",&f);
            skipIdentifier();
            //skipWhitespace();
            //allocate memnory
            pe->processorTemplates[pListNum-1].initDataGlobal[a0].offset=ofst;
            pe->processorTemplates[pListNum-1].initDataGlobal[a0].length=l*f;
            pe->processorTemplates[pListNum-1].initDataGlobal[a0].data=malloc(l*f);
            //count number
            a1=countI();
            for(a2=0;a2<a1;a2++)
            {
              skipWhitespace();
              parseString(pe->processorTemplates[pListNum-1].initDataGlobal[a0].data + a2 * l);
              skipWhitespace();
              inputBufferPointer++;
              //loop, get each char
            }
          }
          else
          {//just l
            //
            a1=countI();
            pe->processorTemplates[pListNum-1].initDataGlobal[a0].offset=ofst;
            pe->processorTemplates[pListNum-1].initDataGlobal[a0].length=l*a1;
            pe->processorTemplates[pListNum-1].initDataGlobal[a0].data=malloc(l*a1);
            a1=countI();
            for(a2=0;a2<a1;a2++)
            {
              skipWhitespace();
              parseString(pe->processorTemplates[pListNum-1].initDataGlobal[a0].data + a2 * l);
              skipWhitespace();
              inputBufferPointer++;
              //loop, get each char
            }
          }
        }
        else
        {//sole string
          a1=countC();
          //printf("\t%d\n",a1);
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].offset=ofst;
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].length=a1;
          pe->processorTemplates[pListNum-1].initDataGlobal[a0].data=malloc(a1);
          parseString(pe->processorTemplates[pListNum-1].initDataGlobal[a0].data);
          //
        }
        ofst+=pe->processorTemplates[pListNum-1].initDataGlobal[a0].length;
        a0++;
        break;
    }
  }
  //data recorded,
  //then go to the next state
  //printf("%s",inputBuffer+inputBufferPointer);
  if(!strncmp(inputBuffer+inputBufferPointer,I_CODE_SECTION,strlen(I_CODE_SECTION)))
  {
    //equal, goto state
    //printf();
    parsingStatus=PS_CODESECTION;
    return;
  }
  //errno
  errno=8;
}
void parseMutex()
{//find the nearest
  //skip whitespace
  static int a0;
  skipWhitespace();
  //printf("##%s\n",inputBuffer+inputBufferPointer);
  //check name
  a0=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
  //printf("#%dFetching Mutex :%s:",a0,identifierBuffer);
  if(ifIdentifierOverdefined(mNameList,mListNum)
  ||ifIdentifierOverdefined(iNameList,iListNum))
  {
    errno=4;
    return;
  }
  //addname & skip name
  //printf("$%s$\n",identifierBuffer);
  addIdentifier(identifierBuffer,mNameList,&mListNum);
  //printf("&%d\n",mListNum);
  //skip whitespace
  inputBufferPointer+=a0;
  skipWhitespace();
  //get size
  //printf("%s",inputBuffer+inputBufferPointer);
  sscanf(inputBuffer+inputBufferPointer,"%d",&a0);
  //printf("$%d$\n",a0);
  //assign the file structure(record)
  pe->mutexSizeList[mListNum-1]=a0;
  parsingStatus=PS_START;
  if(readLine())
  {
    errno=-1;
    return;
  }
}
void parseConnection()
{
  static int a0;
  //find the source name
  skipWhitespace();
  //check if it exist, error return
  inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
  //printf("#%s#\n",identifierBuffer);
  a0=matchIdentifier(iNameList,iListNum);
  if(a0==-1)
  {//error return
    errno=5;
    return;
  }
  pe->connectionMapping[cListNum].nodeSNo=a0;
  //get the port number
  skipWhitespace();
  inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
  sscanf(identifierBuffer,"%d",&a0);
  skipIdentifier();
  pe->connectionMapping[cListNum].nodeSPort=a0;
  //get the destination
  skipWhitespace();
  strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
  a0=matchIdentifier(iNameList,iListNum);
  if(a0==-1)
  {
    errno=0;
    a0=matchIdentifier(mNameList,mListNum);
    if(a0==-1)
    {
      errno=6;
      return;
    }
    pe->connectionMapping[cListNum].nodeDType=TYP_MUTEX;
  }
  else pe->connectionMapping[cListNum].nodeDType=TYP_INST;
  pe->connectionMapping[cListNum].nodeDNo=a0;
  //list pointer+1;
  cListNum++;
  //read next line
  if(readLine())
  {
    errno=-1;
    return;
  }
  //modify the status to start
  parsingStatus=PS_START;
}
void parseInstance()
{
  static int a0;
  //get instance name,
  skipWhitespace();
  inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
  //check the name
  if(ifIdentifierOverdefined(mNameList,mListNum)
  ||ifIdentifierOverdefined(iNameList,iListNum))
  {
    errno=4;
    return;
  }
  //sign up at pe struct
  addIdentifier(identifierBuffer,iNameList,&iListNum);
  //get reference name
  skipWhitespace();
  inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
  //check if it is true
  //printf("#%s#\n",identifierBuffer);
  a0=matchIdentifier(pNameList,pListNum);
  //if its true, assign to proper place, not error return.
  if(a0 == -1)
  {
    errno = 7;
    return;
  }
  pe->processorInstances[iListNum-1].processorReferenceNo = a0;
  skipWhitespace();
  switch(inputBuffer[inputBufferPointer])
  {
    case 'S':
      pe->processorInstances[iListNum-1].initStatus=PROCESSOR_STATUS_SUSPENDED;
      break;
    case 'R':
      pe->processorInstances[iListNum-1].initStatus=PROCESSOR_STATUS_RUNNING;
      break;
    default:
      errno=19;
      return;
  }
  pe->processorInstances[iListNum-1].initData=NULL;
  //next line
  if(readLine())
  {
    errno=-1;
    return;
  }
  //branch: .data / return to start
  if(!strncmp(inputBuffer+inputBufferPointer,I_DATA_SECTION,strlen(I_DATA_SECTION)))
  {
    parsingStatus=PS_DATA_SECTION;
  }

  else parsingStatus=PS_START;
}
void parseInstanceData()
{
  static long fptr;
  static int ofst,a0,a1,a2,a3;
  //back up pointer
  fptr = ftell(input);
  //backup line pointer
  a0=parseLine;
  //loop,count element's number.
  for(a1=0;!readLine();)
  {//counter:a1
    //met . : break
    //printf("#%s\n",inputBuffer+inputBufferPointer);
    //getchar();
    if(inputBuffer[inputBufferPointer]==IDENTIFIER) break;
    else if(inputBuffer[inputBufferPointer]=='I'||inputBuffer[inputBufferPointer]=='R'||inputBuffer[inputBufferPointer]=='C') a1++;
  }
  //a0=0, error
  //printf("@%d",a1);
  if(!a1)
  {
    return;
  }
  //allocate space
  pe->processorInstances[iListNum-1].initNum=a1;
  pe->processorInstances[iListNum-1].initData = malloc(sizeof(initD) * a1);
  //reatore the file pointer & line pointer
  parseLine=a0;
  fseek(input,fptr,SEEK_SET);
  //read file, start parse loop
  ofst=0;
  for(a0=0;!readLine();)
  {//a0:element no
    if(inputBuffer[inputBufferPointer]==IDENTIFIER) break;
    switch(inputBuffer[inputBufferPointer])
    {//parse each line
      case 'O'://set offset/ O <int>
        inputBufferPointer++;
        skipWhitespace();
        sscanf(inputBuffer+inputBufferPointer,"%d",&a1);
        ofst=a1;
        break;
      case 'S'://set skip value S <int>
        inputBufferPointer++;
        skipWhitespace();
        sscanf(inputBuffer+inputBufferPointer,"%d",&a1);
        ofst+=a1;
        break;
      case 'I'://integer
        inputBufferPointer++;
        skipWhitespace();
        //getchar();
        if(inputBuffer[inputBufferPointer]=='F')
        {//fixed size
          static int f;
          inputBufferPointer++;
          skipWhitespace();
          sscanf(inputBuffer+inputBufferPointer,"%d",&f);
          //allocate space
          pe->processorInstances[iListNum-1].initData[a0].offset=ofst;
          pe->processorInstances[iListNum-1].initData[a0].length=f * 8;

          pe->processorInstances[iListNum-1].initData[a0].data=malloc(f*8);
          //write space
          skipIdentifier();
          //skipWhitespace();
          a1=countI();
          for(a2=0;a2<a1;a2++)
          {
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%ld",(long*)(pe->processorInstances[iListNum-1].initData[a0].data + a2 * 8));
            skipIdentifier();
            skipWhitespace();
            inputBufferPointer++;
          }
        }
        else
        {
          a1=countI();
          //printf("@%d@%d\n",a1,a0);
          pe->processorInstances[iListNum-1].initData[a0].offset=ofst;

          pe->processorInstances[iListNum-1].initData[a0].length=a1 * 8;
          pe->processorInstances[iListNum-1].initData[a0].data=malloc(a1*8);
          //printf("ADDR%ld\n",pe->processorInstances[iListNum-1].initData[a0].data);
          //printf("@%d@%d\n",a1,a0);
          for(a2=0;a2<a1;a2++)
          {
            skipWhitespace();
            //printf("$%s\n",inputBuffer+inputBufferPointer);
            sscanf(inputBuffer+inputBufferPointer,"%ld",(long*)(pe->processorInstances[iListNum-1].initData[a0].data + a2 * 8));
            skipIdentifier();//getchar();
            skipWhitespace();
            inputBufferPointer++;
          }
        }
        ofst+=pe->processorInstances[iListNum-1].initData[a0].length;
        a0++;
        break;
      case 'R':
        inputBufferPointer++;
        skipWhitespace();
        if(inputBuffer[inputBufferPointer]=='F')
        {//fixed size
          static int f;
          inputBufferPointer++;
          skipWhitespace();
          sscanf(inputBuffer+inputBufferPointer,"%d",&f);
          //allocate space
          pe->processorInstances[iListNum-1].initData[a0].offset=ofst;
          pe->processorInstances[iListNum-1].initData[a0].length=f * 8;
          pe->processorInstances[iListNum-1].initData[a0].data=malloc(f*8);
          //write space
          skipIdentifier();
          //skipWhitespace();
          a1=countI();
          for(a2=0;a2<a1;a2++)
          {
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%lf",(double*)(pe->processorInstances[iListNum-1].initData[a0].data + a2 * 8));
            skipIdentifier();
            skipWhitespace();
            inputBufferPointer++;
          }
        }
        else
        {
          a1=countI();
          pe->processorInstances[iListNum-1].initData[a0].offset=ofst;
          pe->processorInstances[iListNum-1].initData[a0].length=a1 * 8;
          pe->processorInstances[iListNum-1].initData[a0].data=malloc(a1*8);
          for(a2=0;a2<a1;a2++)
          {
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%lf",(double*)(pe->processorInstances[iListNum-1].initData[a0].data + a2 * 8));
            skipIdentifier();
            skipWhitespace();
            inputBufferPointer++;
          }
        }
        ofst+=pe->processorInstances[iListNum-1].initData[a0].length;
        a0++;
        break;
      case 'C':
        inputBufferPointer++;
        skipWhitespace();
        if(inputBuffer[inputBufferPointer]=='L')
        {//length appointed
          static int l;
          inputBufferPointer++;
          skipWhitespace();
          sscanf(inputBuffer+inputBufferPointer,"%d",&l);
          skipIdentifier();
          skipWhitespace();
          if(inputBuffer[inputBufferPointer]=='F')
          {//fixed size
            static int f;
            //
            inputBufferPointer++;
            skipWhitespace();
            sscanf(inputBuffer+inputBufferPointer,"%d",&f);
            skipIdentifier();
            //skipWhitespace();
            //allocate memnory
            pe->processorInstances[iListNum-1].initData[a0].offset=ofst;
            pe->processorInstances[iListNum-1].initData[a0].length=l*f;
            pe->processorInstances[iListNum-1].initData[a0].data=malloc(l*f);
            //count number
            a1=countI();
            for(a2=0;a2<a1;a2++)
            {
              skipWhitespace();
              parseString(pe->processorInstances[iListNum-1].initData[a0].data + a2 * l);
              skipWhitespace();
              inputBufferPointer++;
              //loop, get each char
            }
          }
          else
          {//just l
            //
            a1=countI();
            pe->processorInstances[iListNum-1].initData[a0].offset=ofst;
            pe->processorInstances[iListNum-1].initData[a0].length=l*a1;
            pe->processorInstances[iListNum-1].initData[a0].data=malloc(l*a1);
            a1=countI();
            for(a2=0;a2<a1;a2++)
            {
              skipWhitespace();
              parseString(pe->processorInstances[iListNum-1].initData[a0].data + a2 * l);
              skipWhitespace();
              inputBufferPointer++;
              //loop, get each char
            }
          }
        }
        else
        {//sole string
          a1=countC();
          printf("\t%d\n",a1);
          pe->processorInstances[iListNum-1].initData[a0].offset=ofst;
          pe->processorInstances[iListNum-1].initData[a0].length=a1;
          pe->processorInstances[iListNum-1].initData[a0].data=malloc(a1);
          parseString(pe->processorInstances[iListNum-1].initData[a0].data);
          //
        }
        ofst+=pe->processorInstances[iListNum-1].initData[a0].length;
        a0++;
        break;
    }
  }
  //data recorded,
  //then go to the next state
  //printf("%s",inputBuffer+inputBufferPointer);
  parsingStatus=PS_START;
  //errno
  //errno=8;
}
void parseConstraint()
{
  static int a0;
  //get the neme
  skipWhitespace();
  inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);//printf("$$$%d$$$\n",sListNum);
  pe->constraintList[sListNum].nodeDNo = matchIdentifier(iNameList,iListNum);
  pe->constraintList[sListNum].nodeSNum = countI();//printf("$%d\n",pe->constraintList[sListNum].nodeSNum);
  pe->constraintList[sListNum].nodeSNoList = malloc(sizeof(int) * pe->constraintList[sListNum].nodeSNum);
  for(a0=0;a0<pe->constraintList[sListNum].nodeSNum;a0++)
  {
    //get the beginning
    skipWhitespace();
    //printf("#%s#\t#%s#\n",identifierBuffer,inputBuffer+inputBufferPointer);
    inputBufferPointer+=strCopy(inputBuffer+inputBufferPointer,identifierBuffer);
    pe->constraintList[sListNum].nodeSNoList[a0] = matchIdentifier(iNameList,iListNum);
    skipWhitespace();
    inputBufferPointer++;
    //printf("$%s$\t$%s$\n",identifierBuffer,inputBuffer+inputBufferPointer);
  }
  sListNum++;
  if(readLine())
  {
    errno=-1;
    return;
  }
  parsingStatus=PS_START;
}
void errorHandler()
{
  if(~errno) printf("Error at line %d,code:%d : ",parseLine,errno);
  switch(errno)
  {
    case 0:printf("No error found");break;
    case 1:printf("expecting a dot(.) identifier");break;
    case 2:printf("Typo or bad announcement");break;
    case 3:printf("identifier undefined");break;
    case 4:printf("identifier conflict, name override");break;
    case 5:printf("undefined instance name");break;
    case 6:printf("undefined destination entity name");break;
    case 7:printf("undefined template name");break;
    case 8:printf("processor template lacking necessary segment(.code)");break;
    case 9:printf("empty data section");break;
    case 10:printf("empty data element");break;
    case 11:printf("unknown key word");break;
    case 12:printf("empty code section");break;
    case 13:printf("syntax error : expect a string closure");break;
    case 14:printf("unknown instructions");break;
    case 15:printf("syntax error : expect a I or R, not others");break;
    case 16:printf("api function not found");break;
    case 17:printf("conflict position name");break;
    case 18:printf("unknown position name");break;
    case 19:printf("syntax error : expect a S or R, not others");break;
    case -1:return;//file end
  }
  printf(".\n");
}
void _debugShowNameList(char *list,int n)
{
  printf("#DEBUG STRAT#%d\n",n);
  while(n--)
  {
    printf("%s\n",list + n * NAME_BUFFER_SIZE);
  }
  printf("#DEBUG ENDED#%d\n",n);
}
