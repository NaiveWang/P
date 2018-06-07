#ifndef PVMAPILIB_H
#define PVMAPILIB_H
/**
 * This library contains system call of this VM
 **/
#include "PCoreBase.h"
#include <stdio.h>
#include <string.h>
typedef struct referencesOfAssembler
{
  unsigned short apiNumber;
  unsigned short apiNumberL;
  char key[28];
}APIIR;
void basicIO_Buffer(PBase* p);
void basicIO_File(PBase* p);
//decoder
void APIHandler(PBase* p);
int fetchAPI(char* target);
#endif
