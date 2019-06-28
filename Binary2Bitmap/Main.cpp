#include "Bitmapper.h"
#include <stdio.h>
#include <string.h>

#pragma warning(disable:4996)

#define MAX_NAME_LEN 256

int main(int argc, char** argv)
{
	if (argc<2)
	{
		printf("Usage: <Command> <FileName>");
		return -1;
	}

	printf("====== Bin to Bitmap ====== \n\n");

	char fn[MAX_NAME_LEN] = { 0 };
	int width, height, size;

	for (int c = 1; c < argc; ++c)
	{
		memset(fn, 0, MAX_NAME_LEN);
		strcpy(fn, argv[c]);

		printf("Current: %s ...", fn);

		FILE* fp = fopen(fn, "rb");

		if (fp == NULL)
		{
			printf("FAILED\n");
			continue;
		}

		fread(&width, sizeof(int), 1, fp);
		fread(&height, sizeof(int), 1, fp);

		size = width*height;
		byte* data = new byte[size];

		fread(data, size, 1, fp);

		int len = strlen(fn);
		fn[len - 2] = 'm';
		fn[len - 1] = 'p';

		SaveAsBMP(data, width, height, fn);

		printf("Done.\n");

		delete[] data;
		fclose(fp);
	}

	printf("\n====== Bin to Bitmap ======\n\n");
	return 0;
}