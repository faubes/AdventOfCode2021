// AdventOfCode2021.cpp : Defines the entry point for the application.
//

#include "SubmarineControllerMark2.h"
#include "windows.h"
int main(int argc, const char** arv) {
	TCHAR Buffer[MAX_PATH];
	DWORD dwRet;
	dwRet = GetCurrentDirectory(MAX_PATH, Buffer);
	std::wcout << Buffer << std::endl;

	cout << "Begin voyage" << endl;
	SubmarineControllerMark2 sc = SubmarineControllerMark2();
	cout << "Loading directions from HQ!" << endl;
	sc.LoadInput("..\\Day2\\input.txt");
	if (sc.GetDirections().size() <= 0) {
		cout << "Direction's don't make sense!" << endl;
	}
	sc.ExecuteCommands();
	cout << sc.GetPosition() << endl;
	cout << sc.GetPosition().x * sc.GetDepth() << endl;

	return 0;
}


SubmarineControllerMark2::SubmarineControllerMark2(){}

void SubmarineControllerMark2::LoadInput(string fileName)
{
	ifstream inputFile(fileName);
	if (inputFile) {
		directions = vector<Command>();
		string command;
		int n;
		while (inputFile >> command && inputFile >> n) 
		{
			directions.push_back(Command(command, n));
		}
	}
	else
	{
		cout << "Couldn't load directions!" << endl;
	}
}

void SubmarineControllerMark2::GoForward(int n)
{
	pos.x += n;
	pos.y -= aim * n;
}

void SubmarineControllerMark2::GoBackward(int n)
{
	pos.x -= n;
}

void SubmarineControllerMark2::GoDown(int n)
{
	aim += n;
}

void SubmarineControllerMark2::GoUp(int n)
{
	aim -= n;
}

void SubmarineControllerMark2::ExecuteCommands() {

	for (auto it = directions.cbegin(); it < directions.cend(); it++)
	{
		Command next = *it;
		if (next.cmd.compare("forward") == 0) {
			GoForward(next.n);
		}
		else if (next.cmd.compare("up") == 0) {
			GoUp(next.n);
		}
		else if (next.cmd.compare("down") == 0) {
			GoDown(next.n);
		}
	}
}