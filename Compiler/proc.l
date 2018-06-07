D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			([Ee][+-]?{D}+)
P     ([Pp][+-]?{D}+)
FS		(f|F|l|L)
IS    ((u|U)|(u|U)?(u|U))
%{
#include "y.tab.h"
#include "symbol.h"
void yyerror (char *s);
int yylex();
void count(void);
%}
%%
"processor"               {count();return PROCESSOR;}

"int"                     {count();return INT;}
"real"                    {count();return REAL;}
"char"          	        {count();return CHAR;}

"reboot"                  {count();return _REBOOT;}
"halt"                    {count();return _HALT;}
"suspend"                 {count();return _SUSPEND;}
"return"          	      {count();return RETURN;}

"if"          	          {count();return IF;}
"else"          	        {count();return ELSE;}
"while"          	        {count();return WHILE;}
"for"          	      	  {count();return FOR;}
"continue"          	    {count();return CONTINUE;}
"break"          	        {count();return BREAK;}
"static"    							{count();return STATIC;}

{L}({L}|{D})*		          {strcpy(yylval.name,yytext);count();return ID; }

0[xX]{H}+{IS}?						{ sscanf(yytext,"%lx",&yylval.vt.vali);count(); return(CONSTANT_INT); }
0[0-7]*{IS}?							{ sscanf(yytext,"%lo",&yylval.vt.vali);count(); return(CONSTANT_INT); }
[1-9]{D}*{IS}?						{ sscanf(yytext,"%ld",&yylval.vt.vali);count(); return(CONSTANT_INT); }

{D}+{E}{FS}?							{ sscanf(yytext,"%lf",&yylval.vt.valr);count(); return(CONSTANT_REAL); }
{D}*"."{D}+{E}?{FS}?			{ sscanf(yytext,"%lf",&yylval.vt.valr);count(); return(CONSTANT_REAL); }
{D}+"."{D}*{E}?{FS}?			{ sscanf(yytext,"%lf",&yylval.vt.valr);count(); return(CONSTANT_REAL); }
0[xX]{H}+{P}{FS}?					{ sscanf(yytext,"%lf",&yylval.vt.valr);count(); return(CONSTANT_REAL); }
0[xX]{H}*"."{H}+{P}{FS}?  { sscanf(yytext,"%lf",&yylval.vt.valr);count(); return(CONSTANT_REAL); }
0[xX]{H}+"."{H}*{P}{FS}?  { sscanf(yytext,"%lf",&yylval.vt.valr);count(); return(CONSTANT_REAL); }
L?\"(\\.|[^\\"\n])*\"			{ strcpy(yylval.name,yytext);count(); return(CONSTANT_STRING); }
L?'(\\.|[^\\'\n])+'	{ yylval.vt.valc = yytext[1];count(); return(CONSTANT_CHAR); }
">>>="			{ count(); return(ASSAR); }
">>="			{ count(); return(ASSHR); }
"<<="			{ count(); return(ASSHL); }
"+="			{ count(); return(ASADD); }
"-="			{ count(); return(ASSUB); }
"*="			{ count(); return(ASMUL); }
"/="			{ count(); return(ASDIV); }
"%="			{ count(); return(ASMOD); }
"&="			{ count(); return(ASAND); }
"^="			{ count(); return(ASEOR); }
"|="			{ count(); return(ASOR); }
">>>"			{ count(); return(SAR); }
">>"			{ count(); return(SHR); }
"<<"			{ count(); return(SHL); }
"++"			{ count(); return(INC); }
"--"			{ count(); return(DEC); }
"&&"			{ count(); return(RAND); }
"||"			{ count(); return(ROR); }
"<="			{ count(); return(LESEQU); }
">="			{ count(); return(GRTEQU); }
"=="			{ count(); return(EQUAL); }
"!="			{ count(); return(DIFF); }

";"			{ count(); return(';'); }
"{"		{ count(); return('{'); }
"}"		{ count(); return('}'); }
","			{ count(); return(','); }
":"			{ count(); return(':'); }
"="			{ count(); return('='); }
"("			{ count(); return('('); }
")"			{ count(); return(')'); }
"["		{ count(); return('['); }
"]"		{ count(); return(']'); }
"."			{ count(); return('.'); }
"&"			{ count(); return('&'); }
"!"			{ count(); return('!'); }
"~"			{ count(); return('~'); }
"-"			{ count(); return('-'); }
"+"			{ count(); return('+'); }
"*"			{ count(); return('*'); }
"/"			{ count(); return('/'); }
"%"			{ count(); return('%'); }
"<"			{ count(); return('<'); }
">"			{ count(); return('>'); }
"^"			{ count(); return('^'); }
"|"			{ count(); return('|'); }
[ \t\v\n\f]								{count();}
.
%%
int yywrap(void)
{
	return 1;
}
void comment(void)
{
	char c, prev = 0;

	while ((c = input()) != 0)      /* (EOF maps to 0) */
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	printf("unterminated comment");
}


int column = 0;

void count(void)
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

	ECHO;
}
