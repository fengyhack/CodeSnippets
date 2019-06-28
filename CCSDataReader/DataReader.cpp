#include "DataReader.h"

#pragma warning(disable:4996)

BOOL ReadData(const char* datFile, double** ppData, int* pN)
{
	FILE* fp = fopen(datFile, "r");
	if (fp == NULL)
	{
		printf("Failed to open file \'%s\'\n", datFile);
		return FALSE;
	}
	int i, count = 0, tmp;
	for (i = 0; i < 5; ++i)
	{
		// "Eat" DAT HEADER: 1651 2  0 1 0
		if (fscanf(fp, "%d", &tmp)<=0)
		{
			printf("Invalid input dat file!\n");
			fclose(fp);
			return FALSE;
		}
	}
	long pos = ftell(fp);
	double value;
	while (!feof(fp))
	{
		fscanf(fp, "%f", &value);
		++count;
	}
	*pN = count;
	*ppData = (double*)malloc(count*sizeof(double));
	if (*ppData == NULL)
	{
		printf("Failed to allocate memory!\n");
		fclose(fp);
		return FALSE;
	}

	fseek(fp, pos, SEEK_SET);
	for (i = 0; i < count; ++i)
	{
		fscanf(fp, "%f", &((*ppData)[i]));
	}

	fclose(fp);

	return TRUE;
}