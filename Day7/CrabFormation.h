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


struct InitialState

{
	vector<int> data;

	friend istream& operator>>(istream& in, InitialState &state) 
	{
			string str;
			if (in >> str)
			{
				size_t pos = 0;
				size_t hit = 0;
				while (hit < str.length()) {
					hit = str.find(',', pos);
					state.data.push_back(std::stoi(str.substr(pos, hit)));
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

class CrabFormation
{
private:
	string inputFilename;

public:
	InitialState state;
	CrabFormation(string str) : inputFilename(str) {}
	void LoadInput();

	friend ostream& operator<<(ostream& os, const CrabFormation& cf)
	{
		return os;
	}
};