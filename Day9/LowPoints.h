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

};