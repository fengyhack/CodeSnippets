#include "DataReader.h"

int main(void)
{
	char* fileName = "F:\\input.dat";
	double* data = NULL;
	int count = 0;
	if (ReadData(fileName, &data, &count))
	{
		printf("Loaded %d elements.\n", count);
		free(data);
	}

	system("pause");
	return 0;
}