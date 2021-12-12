// AdventOfCode2021.cpp : Defines the entry point for the application.
//

#include "windows.h"
#include "BinaryDiagnostic.h"


template <int N>
BinaryDiagnostic<N>::BinaryDiagnostic(string _inputFilename) : inputFilename(_inputFilename) {}

template <int N>
bool BinaryDiagnostic<N>::LoadInput()
{
	ifstream input(inputFilename);
	if (input) {
		bitset<N> val;
		while (input >> val) {
			binaryData.push_back(val);
		}
		input.close();
		return true;
	}
	cout << "Unable to open input: " << inputFilename;
	return false;
}

template <int N>
static vector<int> SumColumns(vector<bitset<N>> data)
{
	//vector<int> columnSums = std::accumulate(data.cbegin(), data.cend(), vector<int>(N, 0)); // nice idea but need convert bitset <-> vector first
	vector<int> columnSums = vector<int>(N, 0);
	for (bitset<N> bs : data)
	{
		for (int i = 0; i < bs.size(); i++)
		{
			columnSums[i] += bs[i];
		}
	}
	return columnSums;
}

template <int N>
static bitset<N> CreateBitMask(vector<int> _columnSums, std::function<bool(const int&)> criteria ) {
	bitset<N> resultBit = bitset<N>();
	for (int i = 0; i < _columnSums.size(); i++)
	{
		resultBit[i] = criteria(_columnSums[i]);
	}
	return resultBit;
}

template<int N>
void BinaryDiagnostic<N>::CalculateGammaAndDelta() 
{
	binaryGamma = bitset<N>();
	binaryEpsilon = bitset<N>();
	vector<int> columnSums = SumColumns(binaryData);
	const size_t numRows = binaryData.size();
	binaryGamma = CreateBitMask<N>(columnSums, [numRows](int val) -> bool { return val >= numRows / 2;  });
	binaryEpsilon = ~binaryGamma;
	gamma = binaryGamma.to_ulong();
	epsilon= binaryEpsilon.to_ulong();
}

template<int N>
void BinaryDiagnostic<N>::CalculateOxygenAndCO2()
{
	bitset<N> binaryOxygenGeneratorRating = bitset<N>();
	bitset<N> binaryCO2ScrubberRating = bitset<N>();

	binaryOxygenGeneratorRating = FilterByCriteria(binaryData, [](const int& val, const int& numRows) {return val >= numRows/ 2.0; });
	binaryCO2ScrubberRating = FilterByCriteria(binaryData, [](const int& val, const int& numRows) {return val < numRows / 2.0; });

	oxygenGeneratorRating = binaryOxygenGeneratorRating.to_ulong();
	cO2ScrubberRating = binaryCO2ScrubberRating.to_ulong();
}

template<std::size_t N>
static void reverse(std::bitset<N>& b) {
	for (std::size_t i = 0; i < N / 2; ++i) {
		bool t = b[i];
		b[i] = b[N - i - 1];
		b[N - i - 1] = t;
	}
}

template <int N>
bitset<N> BinaryDiagnostic<N>::FilterByCriteria(vector<bitset<N>> data, std::function<bool(const int& A, const int& B)> comp)
{
	int filterIndex = N-1; // start with most significant bit
	while (!data.empty() && data.size() > 1 && filterIndex >= 0)
	{
		vector<int> sumColumns = SumColumns(data);
		//std::reverse(sumColumns.begin(), sumColumns.end());
		bool maskBit = comp(sumColumns[filterIndex], data.size());
		data.erase(std::remove_if(data.begin(), data.end(), [filterIndex, maskBit](bitset<N> bs) -> bool { return bs[filterIndex] != maskBit; }), data.end());
		filterIndex--;
	}
	if (data.size() == 1)
	{
		// cout << data.front() << endl;
		return data.front();
	}
	if (data.empty())
	{
		cout << "Error! Filtered out all values" << endl;
	}
	else
	{
		cout << "Error! Very confused! " << endl;
	}
	return bitset<N>();

}

int main(int argc, const char** argv)
{
	TCHAR Buffer[MAX_PATH];
	DWORD dwRet;
	dwRet = GetCurrentDirectory(MAX_PATH, Buffer);
	std::wcout << Buffer << std::endl;

	BinaryDiagnostic<12> bd = BinaryDiagnostic<12>("..\\Day3\\input.txt");

	if (bd.LoadInput())
	{
		bd.CalculateGammaAndDelta();
		bd.CalculateOxygenAndCO2();
		
		cout << bd << endl;

	}
	else {
		return 1;
	}

	cout << "Parse example" << endl;

	BinaryDiagnostic<5> bdExample = BinaryDiagnostic<5>("..\\Day3\\example_input.txt");
	if (bdExample.LoadInput())
	{
		bdExample.CalculateGammaAndDelta();
		bdExample.CalculateOxygenAndCO2();

		cout << bdExample << endl;

	}
	else {
		return 1;
	}

	return 0;
}

