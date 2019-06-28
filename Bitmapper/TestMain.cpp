#include "Bitmapper.h"

#define FILE_NAME_LEN 256

int main(void)
{
	char szFileName[FILE_NAME_LEN] = { 0 };
	printf("Input file name:");
	scanf("%s", szFileName);

	BYTE* buffer = NULL;
	BUFFERDIMS dims;
	//memset(&dims, 0, sizeof(BUFFERDIMS));

	BOOL status = ReadBitmapFile(szFileName, &buffer, &dims, TRUE);

	if (status)
	{
		free(buffer);
		buffer = NULL;
		printf("Buffer released.\n");
	}

	system("pause");
	return 0;
}