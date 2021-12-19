
#include "LowPoints.h"

int main(int argc, char** argv)
{
	cout << "Hello" << endl;

	ifstream inputFile("..\\Day9\\example_input.txt");
	MapReader mr;
	inputFile >> mr;
	if (!mr.array.empty())
	{
		cout << mr << endl;
		mr.FindLowPoints();
	}

	return 0;
}