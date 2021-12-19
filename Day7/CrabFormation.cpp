// AdventOfCode2021.cpp : Defines the entry point for the application.
//

#include "CrabFormation.h"

#define DEBUG 0

// part 1


void CrabFormation::LoadInput()
{
	ifstream input(inputFilename);
	if (!(input >> state))
	{
		cout << "couldn't read data!" << endl;
	}
	input.close();
}


static int OptimalFuelAverage(vector<int> data)
{
	int sum = std::accumulate(data.begin(), data.end(), 0);
	float average = sum / (float)data.size();
	return (int)std::floor(average);
}

static int OptimalFuelMedian(vector<int> data)
{
	vector<int>::iterator it = data.begin() + data.size() / 2;
	std::nth_element(data.begin(), it, data.end());
	return *it;
	
}


static int CostOfMove(vector<int> data, int movePos)
{
	return std::accumulate(data.begin(), data.end(), 0, [movePos](int acc, int& next ) {return acc + std::abs(next - movePos); });
}


static int CostofMoveLinear(vector<int> data, int movePos)
{
	// each data[i]
	// take the difference absolute (data[i] - movePos)
	// the difference is number of "burns" required to get to movePos
	// the cost of a burn of length L = sum_i=1^l i = i*(i-1)/2
	//
	return std::accumulate(data.begin(), data.end(), 0,
		[movePos](int acc, int &next) { 
			//cost of burn
			int length = std::abs(next - movePos);
			return acc + length*(length+1)/2; }
	);

}


int main(int argc, const char** arv)
{
	CrabFormation cf = CrabFormation("..\\Day7\\input.txt");

	cf.LoadInput();

#ifdef PART1
	cout << "Optimal fuel Median: " << OptimalFuelMedian(cf.state.data) << endl;
	cout << "Cost of Median move: " << CostOfMove(cf.state.data, OptimalFuelMedian(cf.state.data)) << endl;

	cout << "Optimal fuel Average: " << OptimalFuelAverage(cf.state.data) << endl;
	cout << "Cost of Average Move: " << CostOfMove(cf.state.data, OptimalFuelAverage(cf.state.data)) << endl;
#endif

	vector<int> results;
	for (int i = 0; i < 1000; i++) {
		//cout << "Cost of move to " << i << " under linear model: " << CostofMoveLinear(cf.state.data, i) << endl;
		results.push_back(CostofMoveLinear(cf.state.data, i));
	}
	
	cout << "Minimum cost is: " << *std::min_element(results.begin(), results.end()) << endl;
	cout << cf << endl;

	return 0;
}