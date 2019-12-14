#include "Part1.h"
#include "AoCutils.h"

int Part1()
{
	std::vector<std::map<char, int>> ParsedInput;
	std::vector<Moon> Moons;
	int TotalEnergy;
	int TimeStep = 0;
	
	ParsedInput = Day12FileParser();
	Moons = CreateMoonVector(ParsedInput);

	while (TimeStep < TargetTimeStep)
	{
		Moons = UpdateVelocity(Moons);
		Moons = ApplyVelocity(Moons);
		TimeStep++;
	}
	TotalEnergy = CalculateAllMoonEnergy(Moons);

	return TotalEnergy;
}

std::vector<Moon> ApplyVelocity(std::vector<Moon> Moons)
{
	std::vector<Moon> UpdatedMoons = Moons;
	int SourceIterator = 0;
	for (auto TargetMoon : Moons)
	{
		UpdatedMoons[SourceIterator].PositionX += UpdatedMoons[SourceIterator].VelocityX;
		UpdatedMoons[SourceIterator].PositionY += UpdatedMoons[SourceIterator].VelocityY;
		UpdatedMoons[SourceIterator].PositionZ += UpdatedMoons[SourceIterator].VelocityZ;
		SourceIterator++;
	}
	return UpdatedMoons;
}

std::vector<Moon> UpdateVelocity(std::vector<Moon> Moons)
{
	std::vector<Moon> UpdatedMoons = Moons;
	int SourceIterator = 0;
	for (auto SourceMoon : Moons)
	{
		for (auto TargetMoon : Moons)
		{
			if (SourceMoon.Name != TargetMoon.Name)
			{
				// Update X
				if (SourceMoon.PositionX < TargetMoon.PositionX)
				{
					UpdatedMoons[SourceIterator].VelocityX++;
				}
				else if (SourceMoon.PositionX > TargetMoon.PositionX)
				{
					UpdatedMoons[SourceIterator].VelocityX--;
				}

				// Update Y
				if (SourceMoon.PositionY < TargetMoon.PositionY)
				{
					UpdatedMoons[SourceIterator].VelocityY++;
				}
				else if (SourceMoon.PositionY > TargetMoon.PositionY)
				{
					UpdatedMoons[SourceIterator].VelocityY--;
				}

				// Update Z
				if (SourceMoon.PositionZ < TargetMoon.PositionZ)
				{
					UpdatedMoons[SourceIterator].VelocityZ++;
				}
				else if (SourceMoon.PositionZ > TargetMoon.PositionZ)
				{
					UpdatedMoons[SourceIterator].VelocityZ--;
				}
			}
		}
		SourceIterator++;
	}
	return UpdatedMoons;
}

int CalculateKineticEnergy(Moon TargetMoon)
{
	return abs(TargetMoon.VelocityX) + abs(TargetMoon.VelocityY) + abs(TargetMoon.VelocityZ);
}

int CalculatePotentialEnergy(Moon TargetMoon)
{
	return abs(TargetMoon.PositionX) + abs(TargetMoon.PositionY) + abs(TargetMoon.PositionZ);
}

int CalculateMoonEnergy(Moon TargetMoon)
{
	return CalculatePotentialEnergy(TargetMoon) * CalculateKineticEnergy(TargetMoon);
}

int CalculateAllMoonEnergy(std::vector<Moon> Moons)
{
	int Sum = 0;
	for (auto TargetMoon : Moons)
	{
		Sum += CalculateMoonEnergy(TargetMoon);
	}
	return Sum;
}

std::vector<Moon> CreateMoonVector(std::vector<std::map<char, int>> ParsedInput)
{
	std::vector<Moon> Moons;
	std::string MoonNames[] = { "Io", "Europa", "Ganymede", "Callisto" };
	int MoonIterator = 0;
	for (auto MoonAxes : ParsedInput)
	{
		Moon NewMoon(MoonNames[MoonIterator]);

		NewMoon.PositionX = MoonAxes.at('x');
		NewMoon.PositionY = MoonAxes.at('y');
		NewMoon.PositionZ = MoonAxes.at('z');
		Moons.push_back(NewMoon);
		MoonIterator++;
	}
	return Moons;
}