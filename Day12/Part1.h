#pragma once
#include <vector>
#include <string>
#include <map>

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

int Part1();
std::vector<Moon> ApplyVelocity(std::vector<Moon> Moons);
std::vector<Moon> UpdateVelocity(std::vector<Moon> Moons);
int CalculatePotentialEnergy(Moon TargetMoon);
int CalculatePotentialEnergy(Moon TargetMoon);
int CalculateMoonEnergy(Moon TargetMoon);
int CalculateAllMoonEnergy(std::vector<Moon> Moons);
std::vector<Moon> CreateMoonVector(std::vector<std::map<char, int>> ParsedInput);

const int TargetTimeStep = 1000;

