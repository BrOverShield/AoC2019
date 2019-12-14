#pragma once
#include <vector>
#include <string>
#include <map>
#include <numeric> // accumulate

class Moon
{
public:
	int PositionX;
	int PositionY;
	int PositionZ;
	int VelocityX = 0;
	int VelocityY = 0;
	int VelocityZ = 0;
	std::string Name;
	Moon(std::string SuppliedName)
	{
		Name = SuppliedName;
	}
};

int Part2();
std::vector<Moon> ApplyVelocity(std::vector<Moon> Moons);
std::vector<Moon> UpdateVelocity(std::vector<Moon> Moons);
int CalculatePotentialEnergy(Moon TargetMoon);
int CalculatePotentialEnergy(Moon TargetMoon);
int CalculateMoonEnergy(Moon TargetMoon);
int CalculateAllMoonEnergy(std::vector<Moon> Moons);
std::vector<Moon> CreateMoonVector(std::vector<std::map<char, int>> ParsedInput);
bool CompareState(std::vector<Moon> Moons, std::vector<std::vector<Moon>> States);
bool CompareInitialState(std::vector<Moon> Moons, std::vector<Moon> InitialState);
void SaveIfInitialState(std::vector<Moon> InitialState, std::vector<Moon> Moons, std::vector<std::vector<int>>& SavedTiming, std::vector<bool>& PeriodFound, std::vector<int>& Periods, int Steps);
void ValidatePeriod(std::vector<std::vector<int>>& SavedTiming, int MoonIterator, std::vector<int>& Periods, std::vector<bool>& PeriodFound, int StepDifference);
int gcd(int a, int b);
int lcm(int a, int b);

const int TargetTimeStep = 1000;

