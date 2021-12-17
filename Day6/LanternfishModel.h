// AdventOfCode2021.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
//#include <set>
//#include <unordered_map>


using std::string;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;
using std::ifstream;
using std::vector;

//using std::wstring;
//using std::set;
//using std::unordered_map;

//each lanternfish creates a new lanternfish once every 7 days.
struct Lanternfish
{
	static int NEW_FISH_TIMER;
	static int OLD_FISH_TIMER;
	//the number of days until it creates a new lanternfish.
	int timer = 6;
	
	friend ostream& operator<<(ostream & os, Lanternfish lf) { return os << lf.timer << " "; }
	bool reproduce() { return timer < 0; }
	Lanternfish simulate() { return Lanternfish{ --timer }; };

};

struct LanternfishState
{
	// example:
	// 3, 4, 3, 1, 2
	string input;
	vector<Lanternfish> data;
	LanternfishState() {}
	LanternfishState(string str) : input(str) {  }

	LanternfishState& simulate() 
	{
		LanternfishState oldState{};
		LanternfishState newState{};

		for (auto lf : data)
		{
			Lanternfish next_lf = lf.simulate(); // for each lanternfish advance the day
			if (next_lf.reproduce())
			{
				oldState << Lanternfish{ Lanternfish::OLD_FISH_TIMER };
				newState << Lanternfish{ Lanternfish::NEW_FISH_TIMER };
			}
			else 
			{
				oldState << next_lf;
			}
		}
		// preserve order by adding new fish at the end
		data.clear();
		data.insert(data.end(), oldState.data.begin(), oldState.data.end());
		data.insert(data.end(), newState.data.begin(), newState.data.end());
		return *this;
	}
	
	friend ostream& operator<<(ostream& out, const LanternfishState& i)
	{
		out << "Size: " << i.data.size() << " [";
		for (auto val : i.data)
		{
			out << val << " ";
		}
		return out << "]";
	}

	void operator<<(Lanternfish lf) 
	{
		data.push_back(lf);
	}

	friend istream& operator>>(istream& in, LanternfishState& i) 
	{
		string str;
		if (in >> str) 
			{
			size_t pos = 0;
			size_t hit = 0;
			while (hit < str.length()) {
				hit = str.find(',', pos);
				Lanternfish lf { std::stoi(str.substr(pos, hit)) };
				i.data.push_back(lf);
				pos = hit + 1;
			}
		}
		else
		{
			cout << " couldn't extract Input from string? " << endl;
		}
		return in;
	}
};

class LanternfishModel
{
private:
	string inputFilename;
	LanternfishState state;
	int MEASUREMENT_DAY = 18;
	int MAX_DAY= 80;
	int day = 0;

public:
	LanternfishModel(string _inputFile) : inputFilename(_inputFile) {}
	void LoadInput();
	LanternfishState GetState() const;
	void SimulateDay();
	//uint64_t CalculateNumberAfter(int days);
	friend ostream& operator<<(ostream& os, const LanternfishModel& lfm)
	{
		return os << "Day " << lfm.day << " there are " << lfm.state.data.size() << " lanternfish";
	}
};