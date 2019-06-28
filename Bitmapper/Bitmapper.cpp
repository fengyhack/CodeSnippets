/*
 * Bitmapper.cpp
 *
 *  Created on: 2014Äê12ÔÂ18ÈÕ
 *      Author: fengyhack
 */
#include "Bitmapper.h"

void printType(const int t)
{
	printf("\tCompress type: ");
	switch (t)
	{
	case 0:
		printf("UNCOMPRESSED");
		break;
	case 1:
		printf("BI_RLE8");
		break;
	case 2:
		printf("BI_RLE4");
		break;
	default:
		break;
	}
	printf("\n");
}

void ShowBitmapInfo(BITMAPHEADER* pBitmapHeader)
{
	printf("\n------------------- INFORMATION -------------------\n");
	printf("\tFile volume : %d Bytes\n", pBitmapHeader->bfSize);
	printf("\tContent volume : %d Bytes\n", pBitmapHeader->biSizeImage);
	printf("\tImage size : %d*%d (pixel)\n", pBitmapHeader->biWidth, pBitmapHeader->biHeight);
	printf("\tNumber of color used: %d\n", pBitmapHeader->biClrUsed);
	printf("\tNumber of bit per pixel: %d\n", pBitmapHeader->biBitCount);
	//printf("Compress type: %d\n", pBitmapHeader->biCompression);
	printType(pBitmapHeader->biCompression);
	printf("----------------------------------------------------\n");
}

BOOL OpenBitmapFile(const char* szFileName, FILE** ppFile)
{
	*ppFile = fopen(szFileName, "rb");
	if (*ppFile == NULL)
	{
		printf(">>>ERROR:\nFailed to open file %s\n", szFileName);
		return FALSE;
	}
	return TRUE;
}

BOOL ReadHeaderInfo(FILE* pFile, BITMAPHEADER* pBitmapHeader, BOOL dumpInfo)
{
	fread(pBitmapHeader, sizeof(BITMAPHEADER), 1, pFile);
	
	if(BM_WORD!=pBitmapHeader->bfType)
	{
		printf(">>>INVALID:\nThis is not a valid bitmap.\n");
		return FALSE;	
	}
	
	if (dumpInfo)
	{
		ShowBitmapInfo(pBitmapHeader);
	}

	return TRUE;
}

BOOL ReadImageData(FILE* pFile, BITMAPHEADER* pBitmapHeader, BYTE** ppBuffer, BUFFERDIMS* pBufferDims)
{
	pBufferDims->width = pBitmapHeader->biWidth;
	pBufferDims->height = pBitmapHeader->biHeight;
	pBufferDims->depth = (pBitmapHeader->biBitCount) >> 3;
	if (pBufferDims->depth == 1)
	{
		printf("This is a grayscale image\n");
	}
	else if (pBufferDims->depth == 3)
	{
		printf("This is a RGB colored image\n");
	}
	else
	{
		printf(">>>INVALID:\nThis is not a 8/24 bit image.\n");
		return FALSE;
	}

	if (pBufferDims->depth == 1)
	{
		RGBQUAD palette[256];
		int i;
		for (/*int */i = 0; i<pBitmapHeader->biClrUsed; ++i)
		{
			fread(&palette[i], sizeof(RGBQUAD), 1, pFile);
		}
	}

	const int nLineBytes = ((pBitmapHeader->biWidth)* (pBitmapHeader->biBitCount) + 31) / 8;
	const size_t bufferSize = nLineBytes*(pBitmapHeader->biHeight);
	printf("Trying to allocate %d bytes memory...",bufferSize);
	*ppBuffer = (BYTE*)malloc(bufferSize);
	if (*ppBuffer == NULL)
	{
		printf("Failed.\n");
		printf(">>>ERROR:\nFailed to allocate memory.\n");
		return FALSE;
	}

	printf("OK.\nPrepare to load image data...\n");
	fread(*ppBuffer, bufferSize, 1, pFile);
	printf("Image data loaded.\n");

	return TRUE;
}

BOOL ReadBitmapFile(const char* szFileName, BYTE** ppBuffer, BUFFERDIMS* pBufferDims, BOOL dumpInfo)
{
	FILE* pFile = NULL;
	BITMAPHEADER bmh;
	//memset(&bmh, 0, sizeof(BITMAPHEADER));
	BOOL status = FALSE;

	if(OpenBitmapFile(szFileName, &pFile))
	{
		if(ReadHeaderInfo(pFile, &bmh,dumpInfo))
		{
			status=ReadImageData(pFile, &bmh, ppBuffer,pBufferDims);
			if (status)
			{
				fclose(pFile);
			}
		}
	}

	return status;
}
