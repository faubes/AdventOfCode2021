// AdventOfCode2021.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <unordered_map>


using std::string;
using std::cout;
using std::endl;
using std::ostream;
using std::ifstream;
using std::vector;
//using std::wstring;
using std::set;
using std::unordered_map;


struct Position 
{
	int x;
	int y;

	Position(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	
	int Distance(Position other) 
	{
		return std::abs(y - other.y) + std::abs(x - other.x);
	}

	Position StepVector(Position other)
	{
		Position stepVector{};
		stepVector.x = other.x == x ? 0 : (other.x - x < 0 ? -1 : 1);
		stepVector.y = other.y == y ? 0 : (other.y - y < 0 ? -1 : 1);
		return stepVector;
	}

	
	Position operator+(Position other) { return Position(x + other.x, y + other.y); }
	Position operator-(Position other) { return Position(x - other.x, y - other.y); }

	
	bool operator<(Position other) const
	{
		if (x == other.x)
		{
			return y < other.y;
		}
		return x < other.x;
	}
	
	bool operator==(Position other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(Position other) const
	{
		return !operator==(other);
	}

	struct hashFunctor
	{
		std::size_t operator()(Position const& s) const noexcept
		{
			std::size_t h1 = std::hash<int>{}(s.x);
			std::size_t h2 = std::hash<int>{}(s.y);
			return h1 ^ (h2 << 1); // or use boost::hash_combine
		}
	};


	friend ostream& operator<<(ostream& os, const Position& pos) { return os << "(" << pos.x << "," << pos.y << ")"; }
};

struct Line 
{
	Position a, b;
	set<Position> GetIntermediatePoints();

	bool HorizontalOrVertical()
	{
		return a.x == b.x || a.y == b.y;
	}

	bool operator==(const Line& other) const {
		return a == other.a && b == other.b;
	}
};

class HydroThermalVentScanner
{
private:
	string inputFilename;
	vector<Line> lines;
	unordered_map<Position, int, Position::hashFunctor> intersectionMap{};

public:

	HydroThermalVentScanner(string _inputFilename) : inputFilename(_inputFilename) {}
	
	bool LoadInput();

	void CalculateIntersections();

	set<Position> GetIntersectionPoints();

	void PrintIntersectionMap();
};