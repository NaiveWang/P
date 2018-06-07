#include "symbol.h"
void symbolInit()
{
  //set the cursor to zero
  identifiersCursor=0;
  constantsCursor=0;
  currentScope=0;
  globalSegOfst=0;
  stackSegOfst=0;
  stackCounter=0;
}
id* addID(int typ,char* s)
{
  //use before enter a new scope
  //check there is no name same as the current one
  static int a0;
  //debug01();
  for(a0=identifiersCursor-1;a0!=-1 && identifiers[a0].scope==currentScope;a0--)
  {
    //check each content
    if(!strcmp(s,identifiers[a0].name))//equal
      return NULL;
  }
  //add new item
  identifiers[identifiersCursor].type = typ;
  identifiers[identifiersCursor].scope = currentScope;
  strcpy(identifiers[identifiersCursor].name,s);
  identifiersCursor++;
  //a0=123++;
  return identifiers+identifiersCursor;
}
id* findID(char* s)
{
  //return the
  //find the id from top to bottom
  static int a0;
  debug01();
  for(a0=identifiersCursor-1;a0!=-1;a0--)
  {
    if(!strcmp(s,identifiers[a0].name))//found the nearst one
      return identifiers+a0;
  }
  //nothing matched
  return NULL;
}
void leaveScope()
{
  //leave current scope
  while(identifiersCursor&&
    identifiers[identifiersCursor-1].scope &&
    identifiers[identifiersCursor-1].scope==currentScope)
    identifiersCursor--;
  currentScope--;
}
void setMetaType(int typ)
{
  static int a0;
  for(a0=identifiersCursor-1;a0!=-1 && identifiers[a0].type==TYP_META;a0--)
  {
    identifiers[a0].type=typ;
  }
}
constant* addConst(int typ,char* str)
{
  //switch it!
  //check if the list is overflow
  static long i;
  static double r;
  static char c;
  //static char *s;
  static int a0;
  if(constantsCursor==SIZE_CONSTLIST)
    return NULL;
  //parse the item
  //correct ----------assign the type
  //constants[constantsCursor]
  switch(typ)
  {
    case CONSTANT_REAL:
      //
      sscanf(str,"%le",&r);
      for(a0=0;a0<constantsCursor;a0++)
      {
        //check
        if(constants[a0].type==TYP_REAL &&
          *(double*)constants[a0].content==r)
        {
          //match
          return constants+a0;
        }
      }
      //rookie
      constants[constantsCursor].type = TYP_REAL;
      constants[constantsCursor].content = malloc(sizeof(double));
      *(double*)constants[constantsCursor].content = r;
      constantsCursor++;
      return constants+constantsCursor-1;
      break;
    case CONSTANT_INT:
      //
      sscanf(str,"%ld",&i);
      for(a0=0;a0<constantsCursor;a0++)
      {
        //check
        if(constants[a0].type==TYP_INT &&
          *(long*)constants[a0].content==r)
        {
          //match
          return constants+a0;
        }
      }
      //rookie
      constants[constantsCursor].type = TYP_INT;
      constants[constantsCursor].content = malloc(sizeof(long));
      *(long*)constants[constantsCursor].content = i;
      constantsCursor++;
      return constants+constantsCursor-1;
      break;

      case CONSTANT_HEX:
        //
        sscanf(str,"%lx",&i);
        for(a0=0;a0<constantsCursor;a0++)
        {
          //check
          if(constants[a0].type==TYP_INT &&
            *(long*)constants[a0].content==r)
          {
            //match
            return constants+a0;
          }
        }
        //rookie
        constants[constantsCursor].type = TYP_INT;
        constants[constantsCursor].content = malloc(sizeof(long));
        *(long*)constants[constantsCursor].content = i;
        constantsCursor++;
        return constants+constantsCursor-1;
        break;

      case CONSTANT_OCT:
          //
          sscanf(str,"%lo",&i);
          for(a0=0;a0<constantsCursor;a0++)
          {
            //check
            if(constants[a0].type==TYP_INT &&
              *(long*)constants[a0].content==r)
            {
              //match
              return constants+a0;
            }
          }
          //rookie
          constants[constantsCursor].type = TYP_INT;
          constants[constantsCursor].content = malloc(sizeof(long));
          *(long*)constants[constantsCursor].content = i;
          constantsCursor++;
          return constants+constantsCursor-1;
          break;

    case TYP_CHAR:
      //
      sscanf(str,"%c",&c);
      for(a0=0;a0<constantsCursor;a0++)
      {
        //check
        if(constants[a0].type==TYP_CHAR &&
          *(char*)constants[a0].content==c)
        {
          //match
          return constants+a0;
        }
      }
      //rookie
      constants[constantsCursor].type = TYP_CHAR;
      constants[constantsCursor].content = malloc(sizeof(char));
      *(char*)constants[constantsCursor].content = c;
      constantsCursor++;
      return constants+constantsCursor-1;
      break;
    case CONSTANT_STRING:
      //copy it directly
      constants[constantsCursor].content = malloc(strlen(str)+1);
      strcpy((char*)constants[constantsCursor].content,str);
      constants[constantsCursor].type = TYP_STRING;
      constantsCursor++;
      return constants+constantsCursor-1;
      break;
    default:
      return NULL;
  }
}
void debug01()
{
  int a0;
  printf("\n++++++++DEBUG START+++++++++\n");
  for(a0=identifiersCursor;a0;a0--)
  {
    printf("%d/%d %s\n",identifiers[a0-1].type,identifiers[a0-1].scope,identifiers[a0-1].name);
  }
  printf("========DEBUG ENDED=========\n");
}
