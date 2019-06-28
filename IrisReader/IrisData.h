#ifndef IRIS_DATA_H
#define IRIS_DATA_H

#include <string>
#include <fstream>
#include <vector>
#include <cassert>
#include <iostream>
#include <iomanip>
using namespace std;

const int NF = 4;

typedef struct tagFeature
{
	double value[NF];
}Feature;

class IrisData
{
public:
	IrisData(string& fileName);
	int LoadData(void);
	int Count() const;
	int GetFeatureNum() const;
	Feature MetaAt(const int i);
	int LabelAt(const int i);

private:
	string fileName;
	vector<Feature> meta;
	vector<int> label;
	int count;
};

void printfFeature(Feature f);

#endif