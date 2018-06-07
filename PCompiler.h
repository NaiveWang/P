#ifndef PCOMPILER_H
#define PCOMPILER_H
/** no fuss **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/** macro of tokenlizer **/
#define LENGTH_OF_LINE_BUFFER 2048
#define LENGTH_OF_TOKEN_BUFFER 1024

#define LENGTH_OF_IDENTIFIER 128
#define SIZE_OF_SYMBOL_TABLE 512
#define SIZE_OF_INSTANT_LIST 1024

#define TOKEN_PROCESSOR 'P'
#define TOKEN_IF 'F'//if
#define TOKEN_ELSE 'E'//else
#define TOKEN_WHILE 'W'//while
#define TOKEN_FOR 'O'//for
#define TOKEN_SWITCH 'S'//switch
#define TOKEN_CONTINUE 'N'//continue
#define TOKEN_BREAK 'B'//break
#define TOKEN_REBOOT 'T'//reboot
#define TOKEN_RETURN 'U'//return
#define TOKEN_HALT 'H'//halt
#define TOKEN_INT 'I'//int
#define TOKEN_REAL 'R'//real
#define TOKEN_CHAR 'C'//char
#define TOKEN_EQUAL 'Q'//==
#define TOKEN_DIFF 'D'//!=
#define TOKEN_GRTEQU 'G'//>=
#define TOKEN_LESEQU 'L'//<=
#define TOKEN_RAND 'A'//&&
#define TOKEN_ROR 'o'//||
#define TOKEN_ID 'd'//<_/alphabet><...>
#define TOKEN_INSTANT_REAL 'r'//<exist one ./e>
#define TOKEN_INSTANT_INT 'i'//all number
#define TOKEN_INSTANT_CHAR 'c'//'?'
#define TOKEN_INSTANT_STRING 's'//"?"
#define TOKEN_SHL 'l'
#define TOKEN_SHR 'r'
#define TOKEN_SAR 'a'
//reserved
#define TOKEN_DOT '.'
#define TOKEN_COMMA ','
#define TOKEN_SEMI ';'
#define TOKEN_OPEN_PAREN '('
#define TOKEN_CLOSE_PAREN ')'
#define TOKEN_OPEN_BRACE '{'
#define TOKEN_CLOSE_BRACE '}'
#define TOKEN_OPEN_BRACKET '['
#define TOKEN_CLOSE_BRACKET ']'
#define TOKEN_PLUS '+'
#define TOKEN_ASSIGN '='
#define TOKEN_BAR '-'
#define TOKEN_STAR '*'
#define TOKEN_SLASH '/'
#define TOKEN_PERCENT '%'
#define TOKEN_LAND '&'
#define TOKEN_LOR '|'
#define TOKEN_LEOR '^'
#define TOKEN_LNOT '~'
#define TOKEN_RNOT '!'
#define TOKEN_GRT '>'
#define TOKEN_LES '<'
//string
#define TOKEN_GROUPA 14
#define TOKEN_STR_PROCESSOR "processor"
#define TOKEN_STR_CONTINUE "continue"
#define TOKEN_STR_REBOOT "reboot"
#define TOKEN_STR_RETURN "return"
#define TOKEN_STR_SWITCH "switch"
#define TOKEN_STR_WHILE "while"
#define TOKEN_STR_BREAK "break"
#define TOKEN_STR_ELSE "else"
#define TOKEN_STR_HALT "halt"
#define TOKEN_STR_REAL "real"
#define TOKEN_STR_CHAR "char"
#define TOKEN_STR_FOR "for"
#define TOKEN_STR_INT "int"
#define TOKEN_STR_IF "if"

#define TOKEN_GROUPB 31
#define TOKEN_STR_EQUAL "=="
#define TOKEN_STR_DIFF "!="
#define TOKEN_STR_GRTEQU ">="
#define TOKEN_STR_SHL "<<"
#define TOKEN_STR_SAR ">>>"
#define TOKEN_STR_SHR ">>"
#define TOKEN_STR_LESEQU "<="
#define TOKEN_STR_RAND "&&"
#define TOKEN_STR_ROR "||"

#define COMMENT_SINGLELINE "//"
#define COMMENT_START "/*"
#define COMMENT_END "*/"
/** global data of the whole compiler **/
int errno;
/** tokenlizer type **/
typedef struct instantListELement
{
  char type;
  void* content;
}instant;
typedef struct identifierListElement
{
  char type;
  char name[LENGTH_OF_IDENTIFIER];
}symbol;
typedef struct tokenElement
{
  char type;
  void* content;
}token;
#define RESERVED_TOKEN_MAX_LENGTH 16
typedef struct reservedTokenConvertingList
{
  char val;
  char matchingString[RESERVED_TOKEN_MAX_LENGTH];
}reserved;
/** tokenlizer global data **/
//some sole arguments
int lineCursor;//line of the file
#define TOKENLIZER_STATUS_CONTENT 0
#define TOKENLIZER_STATUS_COMMENT 1
char tokenlizerStatus;//content/comment
FILE *input;
//some list arguments
instant instantList[SIZE_OF_INSTANT_LIST];
int instantListCursor;
symbol symbolTable[SIZE_OF_SYMBOL_TABLE];
int symbolTableCursor;
char lineBuffer[LENGTH_OF_LINE_BUFFER];
int lineBufferCursor;
char tokenBuffer[LENGTH_OF_TOKEN_BUFFER];
int tokenBufferCursor;
/** Tokenlizer functions **/
void openFile(char *s);
char readLine();
void skipWhitespace();
symbol* addIdentifier();
instant* addInstant();
token* getToken();
/** functions of the compiler **/
void errorNotifier();
#endif // PCOMPILER_H
