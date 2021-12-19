
#include "LowPoints.h"

int main(int argc, char** argv)
{
	cout << "Hello" << endl;

	ifstream inputFile("..\\Day9\\input.txt");
	MapReader mr;
	inputFile >> mr;
	if (!mr.array.empty())
	{
		cout << mr << endl;
		cout << "Risk is: " << mr.CalculateRiskSum(mr.FindLowPoints()) << endl;
	}

	return 0;
}