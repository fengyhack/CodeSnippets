#include "IrisData.h"

IrisData::IrisData(string& fileName)
{
	this->fileName = fileName;
	count = 0;
}

int IrisData::LoadData(void)
{
	ifstream input(fileName);
	if (!input.is_open())
	{
		return 0;
		//throw(string("Failed to open file: ") + fileName);
	}
	Feature f;
	int k;
	while (!input.eof())
	{
		for (int i = 0; i < NF; ++i)
		{
			input >> f.value[i];
		}
		input >> k;
		meta.push_back(f);
		label.push_back(k);
		++count;
	}
	input.close();

	return count;
}

int IrisData::Count() const
{
	return count;
}

int IrisData::GetFeatureNum() const
{
	return NF;
}

Feature IrisData::MetaAt(const int i)
{
	assert(i < count);
	return meta[i];
}

int IrisData::LabelAt(const int i)
{
	assert(i < count);
	return label[i];
}

void printfFeature(Feature f)
{
	cout << "\tFeature = (";
	for (int i = 0; i < NF; ++i)
	{
		cout <<setw(5)<< f.value[i] << " ";
	}
	cout << ")\t";
}