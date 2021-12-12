// AdventOfCode2021.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <bitset>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include <functional>

using std::string;
using std::cout;
using std::endl;
using std::ostream;
using std::ifstream;
using std::vector;
using std::function;
using std::array;
using std::stringstream;


template <int N>
struct Board
{
	size_t id;

	int entries = 0;
	std::array<std::array<int, N>, N> values{};
	std::array<std::array<bool, N>, N> marked{};

	void SetId(const size_t& _id) { id = _id; }

	bool IsEmpty() { return entries == 0; }

	bool IsFull() { return entries == N * N;  }

	bool LoadNext(const int& val) 
	{  
		if (IsFull())
			return false;
		values[entries / N][entries % N] = val;
		entries++;
		return true;
	}

	bool Mark(const int& number) 
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (values[i][j] == number)
				{
					marked[i][j] = true;
					return true;
				}
			}
		}
		return false;
	}
	
	bool IsBingo()
	{
		for (int i = 0; i < N; i++)
		{
			if (IsBingo(i, true) || IsBingo(i, false)) // checks rows and columns
				return true;
		}
		return false;
	}

	//checks a row or column
	bool IsBingo(const int& n, const bool& row = true)
	{
		for (int i = 0; i < N; i++) 
		{
			if ((row && !marked[n][i]) || (!row & !marked[i][n]))
			{
				return false;
			}
		}
		return true;
	}

	int SumOfUnmarkedValues() const
	{
		int sum = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				sum += marked[i][j] ? 0 : values[i][j];
			}
		}
		return sum;
	}
	friend ostream& operator<<(ostream& os, const Board<N>& b)
	{
		stringstream ss_values;
		stringstream ss_marked;
		for (auto row : b.values)
		{
			for (auto col : row) {
				ss_values << col << " ";
			}
			ss_values << endl;
		}
		for (auto row : b.marked)
		{
			for (auto col : row) {
				ss_marked << col << " ";
			}
			ss_marked << endl;
		}

		return os << "Board Id: " << b.id << ", Entries: " << b.entries << endl << ss_values.str() << endl << ss_marked.str() << endl;
	}
};


template <int N>
class BingoSubsystem {
private:
	string inputFilename;
	string numbersString;
	vector<int> numbersVector;
	vector<Board<N>> boards;

public:

	BingoSubsystem(string inputFile);
		
	bool LoadInput();

	void PlayGame();
	
	// kick off recursion
	void FindWorstBoard() {
		FindWorstBoard(boards, numbersVector);
	}

	void FindWorstBoard(vector<Board<N>> boards, vector<int> numbers);

	friend ostream& operator<<(ostream& os, const BingoSubsystem& bs) {
		
		return os ;
	
	}

};
