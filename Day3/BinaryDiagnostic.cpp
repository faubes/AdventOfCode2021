// AdventOfCode2021.cpp : Defines the entry point for the application.
//

#include "windows.h"
#include "BinaryDiagnostic.h"


BinaryDiagnostic::BinaryDiagnostic(string _inputFilename = "input.txt") : inputFilename(_inputFilename) {}

bool BinaryDiagnostic::LoadInput()
{
	ifstream input(inputFilename);
	if (input) {
		bitset<12> val;
		while (input >> val) {
			binaryData.push_back(val);
		}
		input.close();
		return true;
	}
	cout << "Unable to open input: " << inputFilename;
	return false;
}

void BinaryDiagnostic::CalculateGammaAndDelta() 
{
	vector<int> columnSums = vector<int>(12, 0);
	for (bitset<12> bs : binaryData) 
	{
		for (int i = 0; i < bs.size(); i++)
		{
			columnSums[i] += bs[i];
		}
	}
	bitset<12> binaryGamma = bitset<12>();
	bitset<12> binaryEpsilon = bitset<12>();
	for (int i = 0; i < columnSums.size(); i++) 
	{
		binaryGamma[i] = columnSums[i] >= binaryData.size() / 2;
	}
	binaryEpsilon = ~binaryGamma;
	gamma = binaryGamma.to_ulong();
	epsilon= binaryEpsilon.to_ulong();

}

int main(int argc, const char** argv)
{
	TCHAR Buffer[MAX_PATH];
	DWORD dwRet;
	dwRet = GetCurrentDirectory(MAX_PATH, Buffer);
	std::wcout << Buffer << std::endl;

	BinaryDiagnostic bd = BinaryDiagnostic("..\\Day3\\input.txt");

	if (bd.LoadInput())
	{
		bd.CalculateGammaAndDelta();
		cout << bd << endl;
	}
	else {
		return 1;
	}
	return 0;
}

