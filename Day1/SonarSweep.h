// AdventOfCode2021.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using std::string;
using std::cout;
using std::endl;
using std::ostream;
using std::ifstream;
using std::vector;

class SonarSweep {
private:

	string inputFilename;

protected:
	vector<int> data;
	int num_increasing = 0;

public:

	SonarSweep(string inputFile);
	SonarSweep(vector<int> data);
	
	bool loadInput();
	int countIncreasing() const;
	vector<int> GetData() const { return data; }

	friend ostream& operator<<(ostream& os, const SonarSweep& ss);

};

template <int N>
class SonarSweepAverage : public SonarSweep {

public:

	SonarSweepAverage(string _inputFile) : SonarSweep(_inputFile) {};
	SonarSweepAverage(vector<int> _data) : SonarSweep(_data) {};

	int countIncreasing() const ;

	friend ostream& operator<<(ostream& os, const SonarSweep& ss);

};

