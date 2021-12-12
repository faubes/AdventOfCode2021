// AdventOfCode2021.cpp : Defines the entry point for the application.
//

#include "SubmarineController.h"
#include "windows.h"
int main(int argc, const char** arv) {
	TCHAR Buffer[MAX_PATH];
	DWORD dwRet;
	dwRet = GetCurrentDirectory(MAX_PATH, Buffer);
	std::wcout << Buffer << std::endl;

	cout << "Begin voyage" << endl;
	SubmarineController sc = SubmarineController();
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


SubmarineController::SubmarineController(){}

void SubmarineController::LoadInput(string fileName)
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

void SubmarineController::GoForward(int n)
{
	pos.x += n;
}

void SubmarineController::GoBackward(int n)
{
	pos.x -= n;
}

void SubmarineController::GoDown(int n)
{
	pos.y -= n;
}

void SubmarineController::GoUp(int n)
{
	pos.y += n;
}

void SubmarineController::ExecuteCommands() {

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