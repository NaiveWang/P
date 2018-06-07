%{
void yyerror (char const *s);
int yylex();
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include "symbol.h"
#include "y.tab.h"
#include "codegen.h"
//#define SIZE_NAME 128

extern char* yytext;
extern int currentScope;
void typeCheck(struct value_and_type,struct value_and_type);
void typeErrNotFound();
void typeErrRedeclared();
void typeErrMismatch();
id* temp;
%}
%union
{
char name[128];
struct value_and_type
{
	int type;
	char isID;
	long vali;
	double valr;
	char valc;
} vt;
}
%token PROCESSOR
%token IF ELSE WHILE FOR
%token CONTINUE BREAK
%token _REBOOT RETURN _HALT _SUSPEND
%token INT
%token REAL
%token CHAR
%token STRING
%token STATIC VOID
%token EQUAL DIFF GRTEQU LESEQU RAND ROR
%token <vt>CONSTANT_REAL
%token <vt>CONSTANT_CHAR
%token <name>CONSTANT_STRING
%token <vt>CONSTANT_HEX
%token <vt>CONSTANT_OCT
%token SHL SHR SAR INC DEC
%token ASSAR ASSHL ASSHR ASADD ASSUB ASDIV ASMOD ASMUL ASAND ASOR ASEOR

%token <vt>CONSTANT_INT
%token <name>ID

%type <vt>expression assignment_expression primary_expression postfix_expression
%type <vt>unary_expression cast_expression
%type <vt>multiplicative_expression additive_expression shift_expression relational_expression
%type <vt>equality_expression
%type <vt>and_expression exclusive_or_expression inclusive_or_expression
%type <vt>logical_or_expression logical_and_expression
%type <vt>type_specifier declaration_specifiers
%type <vt>init_declarator init_declarator_list
%start translation_unit
%%
primary_expression
	: ID
		{
			temp=findID($1);
			if(temp)
			{
			$$.type=temp->type;
			$$.isID=1;
			gen7(temp->type,"PUSH0",temp->seg,temp->ofst);
			}
			else
			{
			typeErrNotFound();
			}
		}
	| CONSTANT_INT
	{
	$$.type=TYP_INT;
	$$.isID=0;
	genImmI("PUSH0I8 I ",$1.vali);
	}
	| CONSTANT_REAL
	{
	$$.type=TYP_REAL;
	$$.isID=0;
	genImmR("PUSH0I8 R ",$1.valr);
	}
	| CONSTANT_CHAR
	{
	$$.type=TYP_CHAR;
	$$.isID=0;
	genImmC("PUSH0I1 ",$1.valc);
	}
	| STRING
	| '(' expression ')'
	{
	$$=$2;
	}
	;

postfix_expression
	: primary_expression
		{$$=$1;}
	| postfix_expression INC
		{$$=$1;gen2OP("INC",$1.type);}
	| postfix_expression DEC
		{$$=$1;gen2OP("DEC",$1.type);}
	;


unary_expression
	: postfix_expression
		{$$=$1;}
	| INC unary_expression
		{$$=$2;}
	| DEC unary_expression
		{$$=$2;}
	| unary_operator cast_expression
		{$$=$2;gen2OP_1($2.type);}
	;

unary_operator
	: '&' {gen2OP_0("AND");}
	| '*' {gen2OP_0("MUL");}
	| '+' {gen2OP_0("ADD");}
	| '-' {gen2OP_0("SUB");}
	| '~' {gen2OP_0("NOT");}
	| '!' {gen2OP_0("?");}
	;

cast_expression
	: unary_expression
		{$$=$1;}
	| '(' type_specifier ')' cast_expression
		{$$=$2;}
	;

multiplicative_expression
	: cast_expression
		{$$=$1;}
	| multiplicative_expression '*' cast_expression
		{typeCheck($1,$3);$$=$1;gen2OP("MUL",$1.type);}
	| multiplicative_expression '/' cast_expression
	 	{typeCheck($1,$3);$$=$1;gen2OP("DIV",$1.type);}
	| multiplicative_expression '%' cast_expression
		{typeCheck($1,$3);$$=$1;gen2OP("DIV",$1.type);}
	;

additive_expression
	: multiplicative_expression
		{$$=$1;}
	| additive_expression '+' multiplicative_expression
	 	{typeCheck($1,$3);$$=$1;gen2OP("ADD",$1.type);}
	| additive_expression '-' multiplicative_expression
	 	{typeCheck($1,$3);$$=$1;gen2OP("SUB",$1.type);}
	;

shift_expression
	: additive_expression
		{$$=$1;}
	| shift_expression SHL additive_expression
		{typeCheck($1,$3);$$=$1;gen2OP("SHL",$1.type);}
	| shift_expression SHR additive_expression
		{typeCheck($1,$3);$$=$1;gen2OP("SHR",$1.type);}
	;

relational_expression
	: shift_expression
		{$$=$1;}
	| relational_expression '<' shift_expression
		{typeCheck($1,$3);$$=$1;}
	| relational_expression '>' shift_expression
		{typeCheck($1,$3);$$=$1;}
	| relational_expression LESEQU shift_expression
		{typeCheck($1,$3);$$=$1;}
	| relational_expression GRTEQU shift_expression
		{typeCheck($1,$3);$$=$1;}
	;

equality_expression
	: relational_expression
		{$$=$1;}
	| equality_expression EQUAL relational_expression
		{typeCheck($1,$3);$$=$1;}
	| equality_expression DIFF relational_expression
		{typeCheck($1,$3);$$=$1;}
	;

and_expression
	: equality_expression
		{$$=$1;}
	| and_expression '&' equality_expression
		{typeCheck($1,$3);$$=$1;gen2OP("AND",$1.type);}
	;

exclusive_or_expression
	: and_expression
		{$$=$1;}
	| exclusive_or_expression '^' and_expression
		{typeCheck($1,$3);$$=$1;gen2OP("XOR",$1.type);}
	;

inclusive_or_expression
	: exclusive_or_expression
		{$$=$1;}
	| inclusive_or_expression '|' exclusive_or_expression
		{typeCheck($1,$3);$$=$1;gen2OP("OR",$1.type);}
	;

logical_and_expression
	: inclusive_or_expression
		{$$=$1;}
	| logical_and_expression RAND inclusive_or_expression
		{typeCheck($1,$3);$$=$1;}
	;

logical_or_expression
	: logical_and_expression
		{$$=$1;}
	| logical_or_expression ROR logical_and_expression
		{typeCheck($1,$3);$$=$1;}
	;

assignment_expression
	: logical_or_expression
		{$$=$1;}
	| ID '=' assignment_expression
		{
		//check id
		temp=findID($1);
		if(temp)
			{
			//check type
			if(temp->type==$3.type)
				{
				//assign value
				//copy the top stack to the target
				gen12($3.type,"MOV",POINTER_STACK0,$3.type==TYP_CHAR?-1:-8,temp->seg,temp->ofst);
				}
			else
				{
				//typeErrMismatch
				typeErrMismatch();
				}
			}
		else
			{
			typeErrNotFound();
			}
		}
	| ID assignment_operator assignment_expression
	;

assignment_operator
	: ASMUL
	| ASDIV
	| ASMOD
	| ASADD
	| ASSUB
	| ASSHL
	| ASSHR
	| ASAND
	| ASEOR
	| ASOR
	;

expression
	: assignment_expression
	{
	//reset fast stack
	$$=$1;
	//gen12(TYP_INT,"MOV",BASE_DATA,BASE_STACK0,BASE_DATA,POINTER_STACK0);
	}
	| expression ',' assignment_expression
	;

declaration
	: declaration_specifiers init_declarator_list ';'
		{
		typeCheck($1,$2);
		setMetaType($1.type);
		}
	;
declaration_specifiers
	: STATIC type_specifier {$$=$2;}
	| type_specifier {$$=$1;}
	;
init_declarator_list
	: init_declarator
		{$$=$1;}
	| init_declarator_list ',' init_declarator
		{typeCheck($1,$3);$$=$1.type>$3.type?$1:$3;}
	;

init_declarator
	: direct_declarator {$$.type=TYP_META;}
	| direct_declarator '=' assignment_expression{$$=$3;}
	;


type_specifier
	: CHAR {$$.type=TYP_CHAR;}
	| REAL {$$.type=TYP_REAL;}
	| INT {$$.type=TYP_INT;}
	;


direct_declarator
	: ID
		{
		temp=addID(TYP_META,$1);
		if(!temp)
			typeErrRedeclared();
		}
	| direct_declarator '[' assignment_expression ']'{if($3.type!=TYP_INT) typeErrMismatch();}
	| direct_declarator '[' ']'
	;

statement
  :
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
  | control_statement
	;
control_statement
  : _HALT  ';' {gen2(_HALT);}
  | _REBOOT ';' {gen2(_REBOOT);}
	| _SUSPEND ';' {gen2(_SUSPEND);}
  ;

compound_statement
	: '{' {currentScope++;} block_item_list '}' {leaveScope();}
	;

block_item_list
	: block_item
	| block_item_list block_item
	;

block_item
	: declaration
	| statement
	;

expression_statement
	: ';'
	| expression ';'
	{
	{
	//reset fast stack
	gen12(TYP_INT,"MOV",BASE_DATA,BASE_STACK0,BASE_DATA,POINTER_STACK0);
	}
	}
	;

selection_statement
	: IF '(' expression ')'
	{
	//here is the branch operation section
	genFlagRelated("JMPC <flag> ",flagMarker);
	fStackPush(flagMarker,TYP_BRANCH_FALSE);
	flagMarker++;
	}
	statement
	{
	//recover the flag
	genFlagRelated("#",fStackPop());
	}
	| IF '(' expression ')'
	statement ELSE
	statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| FOR '(' expression_statement expression_statement ')'  statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	: CONTINUE ';'
	| BREAK ';'
	;

translation_unit
	: processor_declaration
	| translation_unit processor_declaration
	;

processor_declaration
	: PROCESSOR ID '(' CONSTANT_INT ',' CONSTANT_INT ',' CONSTANT_INT ')'
		{
		//check first
		temp = addID(TYP_PROC,$2);
		if(!temp)
			typeErrRedeclared();
		genPHeader($2,$4.vali,$6.vali,$8.vali);
		gen(".code;start\n");
		}
		compound_statement
		{
		gen(";ended");
		}
	;

%%
#include <stdio.h>
//#include "symbol.h"
//extern char yytext[];
extern int column;

void yyerror(char const *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
void typeCheck(struct value_and_type l,struct value_and_type r)
{
printf("$%d#%d$",l.type,r.type);
if(l.type==TYP_META || r.type==TYP_META || l.type==r.type) return;
	printf("type checking failure:%d/%d/",l.type,r.type);
	yyerror(yytext);
	exit(-1);
}

void typeErrNotFound()
{
	printf("type error : cannot find declaration.");
	yyerror(yytext);
	exit(-1);
}
void typeErrRedeclared()
{
	printf("type error : identifier name override.");
	yyerror(yytext);
	exit(-1);
}
void typeErrMismatch()
{
	printf("type error : type mismatch.");
	yyerror(yytext);
	exit(-1);
}
