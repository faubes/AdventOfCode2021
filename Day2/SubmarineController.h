// AdventOfCode2021.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using std::string;
using std::cout;
using std::endl;
using std::ostream;
using std::ifstream;
using std::vector;
using std::wstring;

struct Position {
	int x;
	int y;

	Position(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	Position operator+(Position other) { return Position(x + other.x, y + other.y); }
	Position operator-(Position other) { return Position(x - other.x, y - other.y); }

	friend ostream& operator<<(ostream& os, const Position& pos) { return os << "(" << pos.x << "," << pos.y << ")"; }
};

struct Command {
	string cmd;
	int n;
	Command(string _cmd, int _n) : cmd(_cmd), n(_n) {};
};

class SubmarineController 
{
private:
	Position pos;
	vector<Command> directions;
public:
	SubmarineController();
	vector<Command> GetDirections() { return directions; }
	void LoadInput(string fileName);
	void GoForward(int n);
	void GoBackward(int n);
	void GoDown(int n);
	void GoUp(int n);

	void ExecuteCommands();
	Position GetPosition() { return pos; };
	int GetDepth() const { return -pos.y; }


};