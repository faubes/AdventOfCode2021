// AdventOfCode2021.cpp : Defines the entry point for the application.
//
#define DEBUG 1

#include "SevenSegmentDisplay.h"


// oof this long is long
const unordered_map<int, std::bitset<7>> SevenSegmentDisplay::segmentMap = SevenSegmentDisplay::create_map();
// part 1

//void SevenSegmentDisplay::LoadInput()
//{
//	ifstream input(inputFilename);
//	if (!(input >> state))
//	{
//		cout << "couldn't read data!" << endl;
//	}
//	input.close();
//}
//
//
int main(int argc, const char** arv)
{
	//SevenSegmentDisplay s{ 7 };

	//for (const std::pair<int, bitset<7>> p : s.segmentMap)
	//{
	//	cout << p.first << endl;
	//	cout << p.second << endl;

	//}
	//for (int i = 0; i < 10; i++) {
	//	cout << SevenSegmentDisplay(i) << endl;
	//	cout << SevenSegmentDisplay(i).GetBitSet() << endl;
	//	cout << endl;

	//}
	//cout << SevenSegmentDisplay(12) << endl;
	//cout << SevenSegmentDisplay(11).GetBitSet() << endl;
	//cout << endl;

	SignalPattern sp;
	sp.LoadInput("..\\Day8\\example_input.txt");
	//sp.ParseInput();
	sp.IdentifySignalPatterns();

	return 0;
}