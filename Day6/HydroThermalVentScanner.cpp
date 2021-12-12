// AdventOfCode2021.cpp : Defines the entry point for the application.
//

#include "HydroThermalVentScanner.h"

#define DEBUG 0


set<Position> Line::GetIntermediatePoints()
{
	set<Position> intermediatePoints{};
	//int distance = a.Distance(b);
	Position p = a;
	do 
	{
		intermediatePoints.insert(p);
		p = p + a.StepVector(b);

	} while (p != b);
	intermediatePoints.insert(p); // end point
	return intermediatePoints;
}

bool HydroThermalVentScanner::LoadInput()
{
	ifstream input(inputFilename);
	if (input)
	{
		int x_1, x_2, y_1, y_2;
		char comma;
		string arrow;
		// lazy parsing
		while (
			input >> x_1 && input >> comma && input >> x_2 && 
			input >> arrow && 
			input >> y_1 && input >> comma && input >> y_2)
		{
			lines.push_back(Line{ Position{x_1, x_2}, Position{y_1, y_2} });
		}

		return true;
	}
	cout << "Error loading input file! " << endl;
	return false;
}

void HydroThermalVentScanner::CalculateIntersections()
{
	for (auto l : lines)
	{
		//if (l.HorizontalOrVertical())
		//{
			for (auto p : l.GetIntermediatePoints())
			{
				std::pair<unordered_map<Position, int>::iterator, bool> result = intersectionMap.insert(std::make_pair(p,1));
				if (result.second == false) // already in hashmap
				{
					intersectionMap[p] += 1;
				}
			}
		//}
	}
}

set<Position> HydroThermalVentScanner::GetIntersectionPoints() {
	set<Position> result{};
	for (auto kv : intersectionMap)
	{
		if (kv.second >= 2) {
			result.insert(kv.first);
		}
	}
	return result;
}
void HydroThermalVentScanner::PrintIntersectionMap()
{
	int maxX = 0;
	int maxY = 0;
	for (auto kv : intersectionMap)
	{
		if (kv.first.x > maxX)
			maxX = kv.first.x;
		if (kv.first.y > maxY)
			maxY = kv.first.y;
	}
	for (int i = 0; i <= maxX; i++) 
	{
		for (int j = 0; j <= maxY; j++)
		{
			try 
			{
				auto result = intersectionMap.at(Position{ i, j });
				cout << result << " ";
			}
			catch (std::out_of_range e)
			{
				cout << ". ";
			}

		}
		cout << endl;

	}

}
int main(int argc, const char** arv)
{
	HydroThermalVentScanner htvs = HydroThermalVentScanner("..\\Day5\\input.txt");
	htvs.LoadInput();
	htvs.CalculateIntersections();
	auto intersectionPoints = htvs.GetIntersectionPoints();
#if DEBUG
	for (auto p : intersectionPoints) {
		cout << p << " ";
	}
#endif
	cout << "There are: " << intersectionPoints.size() << " intersection points!" << endl;
	//htvs.PrintIntersectionMap();
	return 0;
}
