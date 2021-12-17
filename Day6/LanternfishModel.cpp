// AdventOfCode2021.cpp : Defines the entry point for the application.
//

#include "LanternfishModel.h"

#define DEBUG 0
const int MAX_DAY = 80;
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


uint64_t static CalculateNumberAfter(const LanternfishState& initial, int days)
{
	int sum = 0;
	for (Lanternfish lf : initial.data)
	{
	// simplify: suppose all fish have same timer
		sum = std::pow(2, days/6);

	}
	return sum;
}

uint64_t static NewFishGrowth(const int& initialFish, int days)
{
	uint64_t sum = 0;
	if (days < 8)
	{
		return 0;
	}
	if (days >= 8 && (days - 8) / 6 < 1 ) {
		return 1;
	}
	return 1 + initialFish * std::pow(2, days / 6);
}

int main(int argc, const char** arv)
{
	LanternfishModel lfm = LanternfishModel("..\\Day6\\test_input.txt");

	/*Input test{};
	std::cin >> test;
	*/

	lfm.LoadInput();
	int day = 0;
	for (int day = 1; day <= MAX_DAY; day++) {
		//lfm.SimulateDay();

		if (day % 2 == 0)
		{
			cout << "Calculation: " << CalculateNumberAfter(lfm.GetState(), day) <<  endl;
			cout << day << endl;
		}
	}
	cout << lfm << endl;
	

	return 0;
}