
#include "NavigationSubsystem.h"

const unordered_map<char, int> NavigationLogEntry::corruptPointsMap = NavigationLogEntry::create_corrupt_points_map();
const unordered_map<char, int> NavigationLogEntry::incompletePointsMap = NavigationLogEntry::create_incomplete_points_map();

int main(int argc, char** argv)
{
	cout << "Hello" << endl;

	ifstream inputFile("..\\Day10\\input.txt");
	NavigationLog nl{};
	inputFile >> nl;
	cout << nl;
	cout << "Corrupt Score: " << nl.CorruptScoreLog() << endl;
	cout << "Incomplete Score: " << nl.IncompleteScoreLog() << endl;
	//cout << nl.CorruptLines() << endl;
	//cout << nl.IncompleteLines() << endl;
	inputFile.close();
	return 0;
}