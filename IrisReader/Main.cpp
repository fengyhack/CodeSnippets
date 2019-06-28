#include "IrisData.h"

int main(void)
{
	cout << "Please input data source filename:";
	string fileName;
	cin >> fileName;

	IrisData irisData(fileName);
	int count = irisData.LoadData();
	const int N = irisData.GetFeatureNum();
	Feature f;
	if (count>0)
	{
		cout << "Total Count = " << count << endl;
		for (int i = 0; i < count;++i)
		{
			cout << "[" <<setw(3)<< i + 1 << "]";
			printfFeature(irisData.MetaAt(i));
			cout << " Label = " << irisData.LabelAt(i);
			cout << endl;
		}
	}
	else
	{
		cout << fileName << " is a invalid input file!" << endl;
	}

	system("pause");
	return 0;
}