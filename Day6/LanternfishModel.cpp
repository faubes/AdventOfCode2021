// AdventOfCode2021.cpp : Defines the entry point for the application.
//

#include "LanternfishModel.h"

#define DEBUG 0
const int MAX_DAY = 256;
const int MEASUREMENT_DAY = 18;

int Lanternfish::NEW_FISH_TIMER = 8;
int Lanternfish::OLD_FISH_TIMER = 6;


LanternfishState LanternfishModel::GetState() const
{
	return state;
}

void LanternfishModel::SimulateDay()
{
	day += 1;
	state = state.simulate();
}

void LanternfishModel::LoadInput()
{
	ifstream input(inputFilename);
	if (!(input >> state))
	{
		cout << "couldn't read data!" << endl;
	}
	input.close();
}

int main(int argc, const char** arv)
{
	LanternfishModel lfm = LanternfishModel("..\\Day6\\input.txt");

	/*Input test{};
	std::cin >> test;
	*/

	lfm.LoadInput();
	int day = 0;
	for (int day = 1; day <= MAX_DAY; day++) {
		lfm.SimulateDay();
		if (day == MEASUREMENT_DAY || day % 50 == 0)
		{
			cout << lfm << endl;
		}
	}


	return 0;
}