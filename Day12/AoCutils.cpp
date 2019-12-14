#include "AoCutils.h"

std::chrono::time_point<std::chrono::steady_clock> start;
std::chrono::time_point<std::chrono::steady_clock> stop;

std::vector<std::map<char, int>> Day12FileParser()
{
	std::string string;
	std::vector<std::string> InputVector;
	std::vector<std::map<char, int>> MoonStats;

	std::ifstream InputFilePath("inputtest2.txt");

	if (InputFilePath.is_open())
	{
		while (InputFilePath.good())
		{
			InputFilePath >> string;
			InputVector.push_back(string);
		}

	}
	InputFilePath.close();

	char Axes[] = {'x', 'y', 'z'};
	std::vector<char> charsToRemove = { '<', '>', ',','=','x','y','z' };
	int AxeIntValueFromString;
	int AxeIterator = 0;
	std::map<char, int> map;
	for (auto InputString : InputVector)
	{
		if (AxeIterator == 0)
		{
			map.clear();
		}
		removeCharsFromString(InputString, charsToRemove);
		AxeIntValueFromString = std::stoi(InputString, nullptr, 10);
		map[Axes[AxeIterator]] = AxeIntValueFromString;
		if (AxeIterator == 2)
		{
			MoonStats.push_back(map);
			AxeIterator = 0;
		}
		else
		{
			AxeIterator++;
		}
	}

	return MoonStats;
}

void removeCharsFromString(std::string& str, std::vector<char> charsToRemove)
{
	for (auto character : charsToRemove)
	{
		str.erase(remove(str.begin(), str.end(), character), str.end());
	}
}

void DisplayAnswer(int Answer)
{
	std::cout << "ANSWER : " << Answer << std::endl;
}

void StartTime()
{
	start = std::chrono::high_resolution_clock::now();
}
void StopTime()
{
	stop = std::chrono::high_resolution_clock::now();
}
void DisplayTime()
{
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "Time is : " << duration.count() << " Milliseconds" << std::endl;
}