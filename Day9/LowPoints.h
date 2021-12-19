#pragma once

#include "../utils/myutils.h"
#include <cassert>

typedef vector<vector<int>> map;
typedef vector<string> string_vec;

struct MapReader
{
	string_vec inputStrings;
	map array;

	friend istream& operator>>(istream& is, MapReader& mr)
	{
		string line;
		while (getline(is, line) && !line.empty())
		{
			mr.inputStrings.push_back(line);
			vector<int> row;
			std::for_each(line.begin(), line.end(), [&row](char c) { row.push_back(stoi(string{ c })); });
			mr.array.push_back(row);
			//cout << line << endl;
		}
		return is;
	}

	friend ostream& operator<<(ostream & os, const MapReader & mr) 
	{
		if (!mr.inputStrings.empty())
		{
			for (auto row : mr.inputStrings)
			{
				os << row << endl;
			}
		}
		return os;
	}


	// low points
	// need neighborhoods on a goddamn grid graph again
	// that means boundary checking I guess
	// Or graph construction ?
	// that would be fancier but maybe longer?

	// or we could just find min points in 1d array rows
	// then check if they are also mins in 1d col?
	// that's easier let's do that first

	//need a way to get row of map.. by copy should suffice
	vector<int> GetColumn(const size_t j)
	{
		assert(!array.empty());
		vector<int> col;
		std::for_each(array.begin(), array.end(), [&j, &col](auto& v) { col.push_back(v[j]); });
		return col;
	}

	// find a way to get index of local min
	// just do find if with a predicate?
	struct is_local_min
	{
		bool operator()(vector<int> v, size_t index) 
		{
			if (index == 0) // first elem
			{
				if (v[0] < v[1])
				{
					return true;
				}
				return false;
			}
			if (index == v.size() - 1) // last elem
			{
				if (v[index] < v[index - 1])
				{
					return true;
				}
				return false;
			}
			return v[index] < v[index - 1] && v[index] < v[index + 1];
		};

	};

	vector<std::pair<size_t, size_t>> FindLowPoints()
	{
		vector<std::pair<size_t, size_t>> lowPoints{};

		if (array.empty())
		{
			cout << "array empty?" << endl;
			return lowPoints;
		}
		size_t rownum = array.size();
		size_t colnum = array[0].size();
		
		for (size_t i = 0; i < rownum; i++) {

			for (size_t j = 0; j < colnum; j++)
			{
				auto testfunc = is_local_min{};
				if (testfunc(array[i], j))
				{
					//cout << "Found local 1-d min in row " << "0" << " column " << j << endl;
					auto row = GetColumn(j);
					if (testfunc(row, i))
					{
						cout << "Found low point in row " << i << " column " << j << endl;
						lowPoints.push_back(std::make_pair(i, j));
					}
				}
			}


		}
		return lowPoints;
	}

	int CalculateRiskSum(vector<std::pair<size_t, size_t>> points)
	{
		if (array.empty())
		{
			cout << "array empty?" << endl;
			return 0;
		}

		int sum = 0;
		for (auto& p : points)
		{
			sum += array[p.first][p.second] + 1;
		}
		return sum;
	}

	struct out_of_bounds
	{
		size_t rows;
		size_t columns;
		bool operator()(const std::pair<size_t, size_t> &p)
		{
			size_t i = p.first;
			size_t j = p.second;
			return (i < 0 || i >= rows) || (j < 0 || j >= columns );
		}
	};

	enum direction { UP, DOWN, LEFT, RIGHT};

	int RecursiveBasinSearch(const std::pair<size_t, size_t>& p, direction d, set <std::pair<size_t, size_t>> &explored)
	{
		int result = 0;

		auto check = out_of_bounds{ array.size(), array[0].size() };
		if (check(p))
			return result;
		if (explored.contains(p))
		{
			return result;
		}
		explored.insert(p);
		size_t i = p.first;
		size_t j = p.second;
		
		if (array[i][j] == 9) 
		{
			return 0;
		}

		result++;
		switch (d)
		{
		case(LEFT):
			result += RecursiveBasinSearch(std::make_pair(i - 1, j ), UP, explored);
			result += RecursiveBasinSearch(std::make_pair(i + 1, j), DOWN, explored);
			result += RecursiveBasinSearch(std::make_pair(i, j - 1), LEFT, explored);
			break;
		case(RIGHT):
			result += RecursiveBasinSearch(std::make_pair(i - 1, j), UP, explored);
			result += RecursiveBasinSearch(std::make_pair(i + 1, j), DOWN, explored);
			result += RecursiveBasinSearch(std::make_pair(i, j + 1), RIGHT, explored);
			break;
		case(UP):
			result += RecursiveBasinSearch(std::make_pair(i, j - 1), LEFT, explored);
			result += RecursiveBasinSearch(std::make_pair(i, j + 1), RIGHT, explored);
			result += RecursiveBasinSearch(std::make_pair(i - 1, j), UP, explored);
			break;
		case(DOWN):
			result += RecursiveBasinSearch(std::make_pair(i, j - 1), LEFT, explored);
			result += RecursiveBasinSearch(std::make_pair(i, j + 1), RIGHT, explored);
			result += RecursiveBasinSearch(std::make_pair(i + 1, j), DOWN, explored);
			break;
		}
		return result;
	}

	int FindBasinFromLowPoint(const std::pair<size_t, size_t>& p)
	{
		int result = 0;
		auto check = out_of_bounds{ array.size(), array[0].size() };
		if (check(p))
			return result;
		size_t i = p.first;
		size_t j = p.second;

		if (array[i][j] == 9)
		{
			return 0;
		}
		result++;
		set <std::pair<size_t, size_t>> explored{p};
		result += RecursiveBasinSearch(std::make_pair(i, j - 1), LEFT, explored);
		result += RecursiveBasinSearch(std::make_pair(i, j + 1), RIGHT, explored);
		result += RecursiveBasinSearch(std::make_pair(i - 1, j), UP, explored);
		result += RecursiveBasinSearch(std::make_pair(i + 1, j), DOWN, explored);
		return result;

	}

	int MultiplySizesOfBasins(const vector<std::pair<size_t, size_t>> &lowPoints) 
	{
		vector<int> MaxThree{};
		for (auto p : lowPoints)
		{
			int next = FindBasinFromLowPoint(p);
			auto it = std::min_element(MaxThree.begin(), MaxThree.end());
			if (MaxThree.size() < 3)
			{
				MaxThree.emplace_back(next);
			}
			else if (*it < next)
			{
				*it = next;
			}
		}
		int result = 1;
		for (auto i : MaxThree)
		{
			result *= i;
		}

		return result;
	}
};