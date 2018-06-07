#include "PCompiler.h"
void openFile(char *s)
{
  //tokenlizer initializer
  //readfile
  input=fopen(s,"r");
  if(input==NULL)
  {
    errno=1;
  }
  else
  {
    //initialize the cursor and sole args
    tokenlizerStatus=TOKENLIZER_STATUS_CONTENT;
    instantListCursor=0;
    symbolTableCursor=0;
    lineBufferCursor=0;
    tokenBufferCursor=0;
    lineCursor=0;
    errno=0;
    readLine();
  }
}
char readLine()
{
  //read line into the line buffer
  //increase the line cursor
  if(fgets(lineBuffer,LENGTH_OF_LINE_BUFFER,input))
  {
    //success
    lineBufferCursor=0;
    lineCursor++;
    return -1;
  }
  else
  {
    fclose(input);
    return 0;
  }
}
void skipWhitespace()
{
  while(lineBuffer[lineBufferCursor]==' ' || lineBuffer[lineBufferCursor]=='\t') lineBufferCursor++;
}
symbol* addIdentifier()
{
  static int a0;
  //check the identifier in buffer
    //check if it has been declared
  for(a0=0;a0<symbolTableCursor;a0++)
  {
    //check
    if(strcmp(symbolTable[a0].name,tokenBuffer))
    {
      //not match, continue
      continue;
    }
    else
    {
      //match, return the current symbol addr
      return symbolTable+a0;
    }
  }
  //new identifier
  //check if it was valid
  //check first character
  if(
    (*tokenBuffer <= 'Z' && *tokenBuffer >= 'A')||
    (*tokenBuffer <= 'z' && *tokenBuffer >= 'a')||
    (*tokenBuffer == '_'))
  {
    //match, next step
    for(a0=1;tokenBuffer[a0];a0++)
    {
      //check each element
      if(
        (*tokenBuffer <= 'Z' && *tokenBuffer >= 'A')||
        (*tokenBuffer <= 'z' && *tokenBuffer >= 'a')||
        (*tokenBuffer <= '9' && *tokenBuffer >= '0')||
        (*tokenBuffer == '_'))
        continue;//matched
      else
        break;//not match
    }
  }
  else
  {
    //not match
    return NULL;
  }
  if(tokenBuffer[a0])
  {
    //not match
    return NULL;
  }
  else
  {
    //match, add element
    strcpy(symbolTable[symbolTableCursor].name,tokenBuffer);
    //return address
    symbolTableCursor++;
    return symbolTable+symbolTableCursor-1;
  }
}
instant* addInstant()
{
  static int a0,a1;
  static char bs[LENGTH_OF_TOKEN_BUFFER];
  static char bc;
  static long bi;
  static double br;
  //check type:
  switch(*tokenBuffer)
  {
    case '\'':
      //character
      if(sscanf(tokenBuffer+1,"%c",&bc)==1)
      {
        //success, char
        for(a0=0;a0<instantListCursor;a0++)
        {
          if(instantList[a0].type==TOKEN_INSTANT_CHAR &&
            *(char*)instantList[a0].content==bc)
            return instantList+a0;
        }
        //add new element
        instantList[instantListCursor].type==TOKEN_INSTANT_CHAR;
        instantList[instantListCursor].content=malloc(sizeof(char));
        *(char*)instantList[instantListCursor].content=bc;
        instantListCursor++;
        return instantList+instantListCursor-1;
      }
      else
      {
        //failure
        errno=2;
        return NULL;
      }
      break;
    case '"':
      //string
      //must be success
      strcpy(bs,tokenBuffer+1);
      //add string to list anyway
      instantList[instantListCursor].type = TOKEN_INSTANT_STRING;
      instantList[instantListCursor].content = malloc(strlen(tokenBuffer));
      strcpy((char*)instantList[instantListCursor].content,tokenBuffer+1);
      instantListCursor++;
      return instantList+instantListCursor-1;
      break;
    default:
      //number
      //check if it is real number
      for(a0=0;tokenBuffer[a0];a0++)
      {
        if(tokenBuffer[a0]=='.' || tokenBuffer[a0]|0x20 =='e') break;
      }
      if(tokenBuffer[a0])
      {
        //integer
        if(*tokenBuffer=='0')
        {
          //special number
          if(tokenBuffer[1]|0x20 =='x')
          {
            //hex, scan & check
            if(sscanf(tokenBuffer,"%lx",&bi)==1)
            {
              //success, int8
              for(a0=0;a0<instantListCursor;a0++)
              {
                if(instantList[a0].type==TOKEN_INSTANT_INT &&
                  *(long*)instantList[a0].content==bi)
                  return instantList+a0;
              }
              //add new element
              instantList[instantListCursor].type==TOKEN_INSTANT_INT;
              instantList[instantListCursor].content=malloc(sizeof(long));
              *(long*)instantList[instantListCursor].content=bi;
              instantListCursor++;
              return instantList+instantListCursor-1;
            }
            else
            {
              //failure
              errno=2;
              return NULL;
            }
          }
          else
          {
            //oct, scan & check
            if(sscanf(tokenBuffer,"%lo",&bi)==1)
            {
              //success , int8
              for(a0=0;a0<instantListCursor;a0++)
              {
                if(instantList[a0].type==TOKEN_INSTANT_INT &&
                  *(long*)instantList[a0].content==bi)
                  return instantList+a0;
              }
              //add new element
              instantList[instantListCursor].type==TOKEN_INSTANT_INT;
              instantList[instantListCursor].content=malloc(sizeof(long));
              *(long*)instantList[instantListCursor].content=bi;
              instantListCursor++;
              return instantList+instantListCursor-1;
            }
            else
            {
              //failure
              errno=2;
              return NULL;
            }
          }
        }
        else
        {
          //ordinary int
          if(sscanf(tokenBuffer,"%ld",&bi)==1)
          {
            //success , int8
            for(a0=0;a0<instantListCursor;a0++)
            {
              if(instantList[a0].type==TOKEN_INSTANT_INT &&
                *(long*)instantList[a0].content==bi)
                return instantList+a0;
            }
            //add new element
            instantList[instantListCursor].type==TOKEN_INSTANT_INT;
            instantList[instantListCursor].content=malloc(sizeof(long));
            *(long*)instantList[instantListCursor].content=bi;
            instantListCursor++;
            return instantList+instantListCursor-1;
          }
          else
          {
            //failure
            errno=2;
            return NULL;
          }
        }
      }
      else
      {
        //float
        if(sscanf(tokenBuffer,"%le",&br)==1)
        {
          //success, real
          for(a0=0;a0<instantListCursor;a0++)
          {
            if(instantList[a0].type==TOKEN_INSTANT_REAL &&
              *(double*)instantList[a0].content==br)
              return instantList+a0;
          }
          //add new element
          instantList[instantListCursor].type==TOKEN_INSTANT_REAL;
          instantList[instantListCursor].content=malloc(sizeof(double));
          *(double*)instantList[instantListCursor].content=br;
          instantListCursor++;
          return instantList+instantListCursor-1;
        }
        else
        {
          //failure
          errno=2;
          return NULL;
        }
      }
  }
}
token* getToken()
{
  int a0;
  token *rtnp;
  //the matching list is over here
  static const int reserveda = TOKEN_GROUPA;
  static const reserved groupa[TOKEN_GROUPA]=
    {
      {TOKEN_PROCESSOR,TOKEN_STR_PROCESSOR},
      {TOKEN_CONTINUE,TOKEN_STR_CONTINUE},
      {TOKEN_REBOOT,TOKEN_STR_REBOOT},
      {TOKEN_RETURN,TOKEN_STR_RETURN},
      {TOKEN_SWITCH,TOKEN_STR_SWITCH},
      {TOKEN_WHILE,TOKEN_STR_WHILE},
      {TOKEN_BREAK,TOKEN_STR_BREAK},
      {TOKEN_ELSE,TOKEN_STR_ELSE},
      {TOKEN_HALT,TOKEN_STR_HALT},
      {TOKEN_REAL,TOKEN_STR_REAL},
      {TOKEN_CHAR,TOKEN_STR_CHAR},
      {TOKEN_FOR,TOKEN_STR_FOR},
      {TOKEN_INT,TOKEN_STR_INT},
      {TOKEN_IF,TOKEN_STR_IF}
    };
  static const int reservedb = TOKEN_GROUPB;
  static const reserved groupb[TOKEN_GROUPB]=
    {
      {TOKEN_EQUAL,TOKEN_STR_EQUAL},
      {TOKEN_DIFF,TOKEN_STR_DIFF},
      {TOKEN_GRTEQU,TOKEN_STR_GRTEQU},
      {TOKEN_SHL,TOKEN_STR_SHL},
      {TOKEN_SAR,TOKEN_STR_SAR},
      {TOKEN_SHR,TOKEN_STR_SHR},
      {TOKEN_LESEQU,TOKEN_STR_LESEQU},
      {TOKEN_RAND,TOKEN_STR_RAND},
      {TOKEN_ROR,TOKEN_STR_ROR},
      {TOKEN_COMMA,TOKEN_COMMA},
      {TOKEN_SEMI,TOKEN_SEMI},
      {TOKEN_DOT,TOKEN_DOT},
      {TOKEN_OPEN_PAREN,TOKEN_OPEN_PAREN},
      {TOKEN_CLOSE_PAREN,TOKEN_CLOSE_PAREN},
      {TOKEN_OPEN_BRACE,TOKEN_OPEN_BRACE},
      {TOKEN_CLOSE_BRACE,TOKEN_CLOSE_BRACE},
      {TOKEN_OPEN_BRACKET,TOKEN_OPEN_BRACKET},
      {TOKEN_CLOSE_BRACKET,TOKEN_CLOSE_BRACKET},
      {TOKEN_PLUS,TOKEN_PLUS},
      {TOKEN_ASSIGN,TOKEN_ASSIGN},
      {TOKEN_BAR,TOKEN_BAR},
      {TOKEN_STAR,TOKEN_STAR},
      {TOKEN_SLASH,TOKEN_SLASH},
      {TOKEN_PERCENT,TOKEN_PERCENT},
      {TOKEN_LAND,TOKEN_LAND},
      {TOKEN_LOR,TOKEN_LOR},
      {TOKEN_LEOR,TOKEN_LEOR},
      {TOKEN_LNOT,TOKEN_LNOT},
      {TOKEN_RNOT,TOKEN_RNOT},
      {TOKEN_GRT,TOKEN_GRT},
      {TOKEN_LES,TOKEN_LES},
    };
  //match next key word
  //skip whitespace of a line
  for(a0=0;a0;a0=0)
  {
    skipWhitespace();
    //check if is the end of the line or line comment
    while(!strncmp(lineBuffer+lineBufferCursor,COMMENT_SINGLELINE,strlen(COMMENT_SINGLELINE)) ||
        lineBuffer[lineBufferCursor]=='\n')
    {//detected
      a0=1;
      //skip line
      if(readLine())
        continue;
      else return NULL;
      skipWhitespace();
    }
    //check if is the start comment
    if(!strncmp(lineBuffer+lineBufferCursor,COMMENT_START,strlen(COMMENT_START)))
    {
      a0=1;
      //meet the comment start,
      lineBufferCursor+=strlen(COMMENT_START);
      //find the end of comment
      while(!strncmp(lineBuffer+lineBufferCursor,COMMENT_END,strlen(COMMENT_END)))
      {
        if(lineBuffer[lineBufferCursor]=='\n')
          if(readLine())
            continue;
          else return NULL;
        else
          lineBufferCursor++;
      }
      lineBufferCursor+=strlen(COMMENT_END);
    }
    //loop, until met the read item
  }
  //finally, we've met the token.
  //match the reserved first
  //1.try to match with the group b
  for(a0=0;a0<reservedb;a0++)
  {
    //each
    if(!strncmp(groupb[a0].matchingString,
      lineBuffer+lineBufferCursor,
      strlen(groupb[a0].matchingString)))
    {
      //matched
      //increase line buffer cursor
      lineBufferCursor+=strlen(groupb[a0].matchingString);
      //return the value
      rtnp = malloc(sizeof(token));
      rtnp->type = groupb[a0].val;
      rtnp->content = NULL;
      return rtnp;
    }
  }
  //not match, try to match with groupa
  for(a0=0;a0<reserveda;a0++)
  {
    //each
    if(!strncmp(groupa[a0].matchingString,
      lineBuffer+lineBufferCursor,
      strlen(groupa[a0].matchingString)))
    {
      //matched
      //check if the tail is dirty
      char temp = lineBuffer[lineBufferCursor+strlen(groupa[a0].matchingString)];
      if(
        (temp<='9' && temp>='0')||
        (temp<='z' && temp>='a')||
        (temp<='Z' && temp>='Z')||
        temp=='_'
      )
      {
        //go to the identifier section
        break;
      }
      //increase line buffer cursor
      lineBufferCursor+=strlen(groupb[a0].matchingString);
      //return the value
      rtnp = malloc(sizeof(token));
      rtnp->type = groupb[a0].val;
      rtnp->content = NULL;
      return rtnp;
    }
  }
  //copy the content into token buffer, as an identifier
  for(tokenBufferCursor=0,a0=0;
      (lineBuffer[lineBufferCursor+a0]=<'9' && lineBuffer[lineBufferCursor+a0]>='0')||
      (lineBuffer[lineBufferCursor+a0]|0x20 =<'z' && lineBuffer[lineBufferCursor+a0]0x20 >= 'a')||
      (lineBuffer[lineBufferCursor+a0]=='_');
      a0++,tokenBufferCursor++)
    {
      //copy the content
      tokenBuffer[tokenBufferCursor]=lineBuffer[lineBufferCursor+a0];
    }
    tokenBuffer[tokenBufferCursor]='\0';
  //
  if(a0)
  {
    //something in the buffer, test identifier
    symbol *sp = addIdentifier();
    if(sp)
    {
      //success
      lineBufferCursor+=strlen(tokenBuffer);
      rtnp=malloc(sizeof(token));
      rtnp->type=TOKEN_ID;
      rtnp->content = sp;
      return rtnp;
    }
  }
  //copy comtent into the buffer via different manner
  switch(lineBuffer[lineBufferCursor])
  {
    case '"'://string
      break;
    case '\''://character
      break;
    default:;//number
  }
}
void errorNotifier()
{
  //print error info via the error number
  printf("Error No.%d:",errno);
  switch(errno)
  {
    case 1 : printf("cannot open file");break;
    case 2 : printf("invalid token lexis at line %d",lineCursor);break;
    case 3 : printf("enviroment error : stackoverflow");break;
    default:printf("undefined errno");
  }
  printf(".\n");
}
