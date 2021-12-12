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
#include <functional>

using std::string;
using std::cout;
using std::endl;
using std::ostream;
using std::ifstream;
using std::vector;
using std::bitset;
using std::function;

template <int N>
class BinaryDiagnostic {
private:
	string inputFilename;
	vector<bitset<N>> binaryData;

	bitset<N> binaryGamma;
	bitset<N> binaryEpsilon;

	unsigned long gamma = 0; 
	unsigned long epsilon = 0;

	unsigned long oxygenGeneratorRating = 0;
	unsigned long cO2ScrubberRating = 0;

public:

	

	BinaryDiagnostic(string inputFile);
		
	bool LoadInput();

	void CalculateGammaAndDelta();
	void CalculateOxygenAndCO2();

	bitset<N> BinaryDiagnostic<N>::FilterByCriteria(vector<bitset<N>> data, std::function<bool(const int& A, const int& B)> comp);

	friend ostream& operator<<(ostream& os, const BinaryDiagnostic& bd) { 
		
		return os << "Power Consumption: " << bd.gamma * bd.epsilon << endl 
			<< "Life Support Rating: " << bd.oxygenGeneratorRating * bd.cO2ScrubberRating;
	
	}

	
	bitset<N> GetBinaryGamma() { return binaryGamma;  }
	bitset<N> GetBinaryEpsilon() { return binaryEpsilon; }
	vector<bitset<N>> GetBinaryData() { return binaryData;  }

};
