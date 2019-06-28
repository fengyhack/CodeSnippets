#include <stdio.h>
#include <stdlib.h>

typedef int BOOL;
#define NULL 0
#define TRUE 1
#define FALSE 0

BOOL ReadData(const char* datFile, double** ppData,int* pN);