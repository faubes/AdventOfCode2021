// AdventOfCode2021.cpp : Defines the entry point for the application.
//

#include "SonarSweep.h"


SonarSweep::SonarSweep(string _inputFilename = "input.txt") : inputFilename(_inputFilename) {}

bool SonarSweep::loadInput()
{
	ifstream input(inputFilename);
	if (input) {
		int val;
		while (input >> val) {
			data.push_back(val);
		}
		input.close();
		return true;
	}
	cout << "Unable to open input: " << inputFilename;
	return false;
}

SonarSweep::SonarSweep(vector<int> _data) : data(_data) {};

int SonarSweep::countIncreasing() const
{
	int count = 0;
	auto it = std::adjacent_find(data.cbegin(), data.cend(),
		[](auto prev, auto next) -> bool { return prev < next; });
	
	while (it < data.end())
	{
		it++;
		count++;
		it = std::adjacent_find(it, data.cend(), [](auto prev, auto next) -> bool { return prev < next; });
	}

	return count;
}

ostream& operator<<(ostream& os, const SonarSweep& ss)
{
	return os << ss.countIncreasing();
}

template<int N>
inline int SonarSweepAverage<N>::countIncreasing() const
{
	vector<int> rollingAverages = vector<int>(data.size());

	for (auto it = data.cbegin(); it < data.cend() - N; it++) 
	{
		int sum = 0;
		rollingAverages.push_back(
			std::accumulate(it, it + N, sum)
		);
	}
	return SonarSweep(rollingAverages).countIncreasing();
}


int main(int argc, const char** argv)
{
	SonarSweep sonarSweep = SonarSweep();
	if (sonarSweep.loadInput())
	{
		cout << sonarSweep << endl;
		
	}
	else {
		return 1;
	}
	SonarSweepAverage<3> sonarSweepAverage = SonarSweepAverage<3>(sonarSweep.GetData());
	cout << sonarSweepAverage.countIncreasing() << endl;
	
	return 0;
}

