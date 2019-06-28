/*
* Bitmapper.c
*
*  Created on: 2014Äê12ÔÂ18ÈÕ
*      Author: fengyhack
*/

#ifndef BITMAPPER_H
#define BITMAPPER_H

#include <stdio.h>
#include <stdlib.h>
//#include <memory.h>

#pragma warning(disable:4996)

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef long LONG;
typedef int BOOL;

#define TRUE 1
#define FALSE 0

#ifndef NULL
#define NULL 0
#endif

#define BM_WORD 0x4D42

#pragma pack(push,1)

typedef struct tagBitmapHeader
{
	WORD bfType; //Constant = 0x424D or ¡°BM¡±
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
	////////////////////////////////////////////////
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes; //Constant = 1
	WORD biBitCount;  // 8 for grayscale or 24 for RGB
	DWORD  biCompression;
	DWORD  biSizeImage;
	LONG  biXPelsPerMeter;
	LONG  biYPelsPerMeter;
	DWORD  biClrUsed;
	DWORD  biClrImportant;
}BITMAPHEADER;

#pragma pack(pop)

typedef struct tagRGBQUAD // Grayscale ONLY
{
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
}RGBQUAD;

typedef struct tagC3RGB
{
	BYTE red;
	BYTE green;
	BYTE blue;
}C3RGB;

typedef struct tagBufferDims
{
	int width;
	int height;
	int depth;
}BUFFERDIMS;

extern void printType(const int t);

extern void ShowBitmapInfo(BITMAPHEADER* pBitmapHeader);

extern BOOL OpenBitmapFile(const char* szFileName, FILE** ppFile);

extern BOOL ReadHeaderInfo(FILE* pFile, BITMAPHEADER* pBitmapHeader, BOOL dumpInfo);

extern BOOL ReadImageData(FILE* pFile, BITMAPHEADER* pBitmapHeader, BYTE** ppBuffer, BUFFERDIMS* pBufferDims);

extern BOOL ReadBitmapFile(const char* szFileName, BYTE** ppBuffer, BUFFERDIMS* pBufferDims, BOOL dumpInfo);

#endif
