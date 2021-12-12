// AdventOfCode2021.cpp : Defines the entry point for the application.
//

#include "windows.h"
#include "BingoSubsystem.h"


#define DEBUG_PLAY 1

template <int N>
BingoSubsystem<N>::BingoSubsystem(string _inputFilename) : inputFilename(_inputFilename) {}

static vector<int> ParseNumbers(const string& str)
{
	vector<int> numbers = vector<int>();
	size_t cursor = 0;
	size_t next_delimiter = 0;
	size_t end = str.length();
	do
	{
		next_delimiter = str.find(',', cursor);
		int val = std::stoi(str.substr(cursor, next_delimiter - cursor));
#if DEBUG_LOAD
		cout << val << ", ";
#endif
		numbers.push_back(val);
		cursor = next_delimiter + 1;
	} while (next_delimiter != string::npos);
	//numbers.push_back(std::stoi(str.substr(cursor, end - cursor)));
	return numbers;
}

template <int N>
bool BingoSubsystem<N>::LoadInput()
{
	ifstream input(inputFilename);
	if (input)
	{
		input >> numbersString;
#if DEBUG_LOAD
		cout << "Numbers input string: " << numbersString << endl;
#endif
		numbersVector = ParseNumbers(numbersString);
		int val;
		Board<N> b{};
		while (input >> val)
		{
			if (b.IsFull())
			{
#if DEBUG_LOAD
				cout << "Loaded board " << boards.size() << endl;
				cout << b << endl;
				cout << "Sum of unmarked " << b.SumOfUnmarkedValues() << endl;
#endif
				b.SetId(boards.size());
				boards.push_back(b);
				b = Board<N>();
			}
			b.LoadNext(val);
		}
		if (!b.IsFull())
		{
			cout << "Error loading input: incomplete board?" << endl;
		}
		else
		{
			boards.push_back(b); // last board
		}
		input.close();
		return true;
	}
	cout << "Unable to open input: " << inputFilename;
	return false;
}

template <int N>
void BingoSubsystem<N>::PlayGame()
{

	for (auto val : numbersVector)
	{
		for (auto& b : boards)
		{
			if (b.Mark(val))
			{
#if DEBUG_PLAY
				cout << "Marking " << b.id << "with " << val << endl;
				cout << b << endl;
#endif
				if (b.IsBingo())
				{
					cout << "We have a winner: " << b << endl;
					cout << "Score: " << b.SumOfUnmarkedValues() * val << endl;
					return;
				}
			}
		}
	}
	cout << "No winner?" << endl;
}


template <int N>
void BingoSubsystem<N>::FindWorstBoard(vector<Board<N>> boards, vector<int> numbers)
{
	if (boards.empty())
	{
		cout << "error empty boards!?" << endl;
		return;
	}

	bool winner = false;
	vector<int>::iterator it;
	for (it = numbers.begin(); it < numbers.end(); it++)
	{
		for (auto& b : boards)
		{
			int val = *it; // deref for legibility
			if (b.Mark(val))
			{
#if DEBUG_PLAY
				cout << "Marking " << b.id << "with " << val << endl;
				cout << b << endl;
#endif
				if (b.IsBingo())
				{
#if DEBUG_PLAY
					cout << "We have a winner: " << b << endl;
					cout << "Score: " << b.SumOfUnmarkedValues() * val << endl;
#endif
					winner = true;

					if (boards.size() == 1)
					{
						Board<N> b = boards.front();
						cout << "Worst board seems to be: " << b.id << endl << b;
						cout << "Score: " << b.SumOfUnmarkedValues() * val << endl;
						return;
					}
					break;

				}
			}
		}
		if (winner) break;
	}

	if (it < numbers.cend())
	{ 
		vector<int> remainingNumbers{};
		std::copy(it, numbers.end(), std::back_inserter(remainingNumbers));

		vector<Board<N>> liveBoards{};
		std::copy_if(boards.cbegin(), boards.cend(), std::back_inserter(liveBoards), [](auto b) { return !b.IsBingo();  });
		return FindWorstBoard(liveBoards, remainingNumbers);
	}
	else
	{
		cout << " Ran out of numbers?? " << endl;
		return;
	}
}



int main(int argc, const char** argv)
{
	//TCHAR Buffer[MAX_PATH];
	//DWORD dwRet;
	//dwRet = GetCurrentDirectory(MAX_PATH, Buffer);
	//std::wcout << Buffer << std::endl;

	BingoSubsystem<5> bs = BingoSubsystem<5>("..\\Day4\\input.txt");
	bs.LoadInput();
	bs.PlayGame();
	bs.FindWorstBoard();


	return 0;
}

