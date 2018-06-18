assembler:
	gcc PAssembler.c PFile.c PCoreIR.c PVMAPILib.c -o PAssembler
pvm:
	gcc PCoreIR.c PVMAPILib.c PFile.c PVM.c PVMmain.c -lpthread -lGL -lGLU -lglut -o PVM
2pvm:
	gcc PCoreIR.c PVMAPILib.c PFile.c PVM.c PVMmain.c -lpthread -lGL -lGLU -lglut -o PVM_2
4pvm:
	gcc PCoreIR.c PVMAPILib.c PFile.c PVM.c PVMmain.c -lpthread -lGL -lGLU -lglut -o PVM_4
compiler:
	gcc PCompilermain.c PCompiler.c -o PCompiler
