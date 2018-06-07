compiler:
	lex proc.l
	bison -y -d proc.y
	gcc main.c compiler.c symbol.c y.tab.c lex.yy.c codegen.c ../PCoreIR.c -o Compiler_V0.1
run:
	./Compiler_V0.1 example.procs <example.p
