// AdventOfCode2021.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <fstream>
#include <bitset>
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
using std::bitset;

class BinaryDiagnostic {
private:
	string inputFilename;
	vector<bitset<12>> binaryData;

	unsigned long gamma = 0; 
	unsigned long epsilon = 0;

public:

	BinaryDiagnostic(string inputFile);
		
	bool LoadInput();

	void CalculateGammaAndDelta();
	
	friend ostream& operator<<(ostream& os, const BinaryDiagnostic& bd) { return os << bd.gamma * bd.epsilon; }

};
