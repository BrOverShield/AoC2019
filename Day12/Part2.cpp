#include "Part2.h"
#include "AoCutils.h"

int Part2()
{
	std::vector<std::map<char, int>> ParsedInput;
	std::vector<Moon> Moons;
	std::vector<std::vector<int>> SavedTiming = { {},{},{},{} };
	std::vector<bool> PeriodFound = { false, false, false, false };
	std::vector<int> Periods = { -1, -1, -1, -1 };
	int TotalEnergy;
	double TimeStep = 0;
	std::vector<std::vector<Moon>> States;
	bool IsFound = false;
	bool IsReady = false;
	
	ParsedInput = Day12FileParser();
	Moons = CreateMoonVector(ParsedInput);
	auto InitialState = Moons;

	while (!PeriodFound[0] || !PeriodFound[1] || !PeriodFound[2] || !PeriodFound[3])
	{
		//States.push_back(Moons);
		Moons = UpdateVelocity(Moons);
		Moons = ApplyVelocity(Moons);
		TimeStep++;
		//IsFound = CompareState(Moons, States);
		SaveIfInitialState(InitialState, Moons, SavedTiming, PeriodFound, Periods, TimeStep);
	}

	for (auto SavedInfo : SavedTiming)
	{
		std::cout << "MOON" << std::endl;
		for (auto number : SavedInfo)
		{
			std::cout << number << std::endl;
		}
	}

	std::cout << "PERIODS" << std::endl;

	for (auto period : Periods)
	{
		std::cout << period << std::endl;
	}

	std::vector<double> Results;

	for (int i = 0; i < Moons.size(); i++)
	{
		Results.push_back(0);
		for (int j = 0; j < Periods[i]; j++)
		{
			Results[i] += SavedTiming[i][j];
		}
	}

	std::cout << "RESULTS" << std::endl;
	for (auto result : Results)
	{
		std::cout << result << std::endl;
	}

	std::vector<double> v;
	double* aResults = &Results[0];

	double result = std::accumulate(aResults, aResults + 4, 1, lcm);

	return result;
}

void SaveIfInitialState(std::vector<Moon> InitialState, std::vector<Moon> Moons, std::vector<std::vector<int>>& SavedTiming, std::vector<bool> &PeriodFound, std::vector<int> &Periods, int Steps)
{
	int Middle;
	int CharacterPosition;
	int PeriodIteration;
	int PeriodIterations;
	int StepDifference;
	for (int MoonIterator = 0; MoonIterator < InitialState.size(); MoonIterator++) // For each moon
	{
		if (Moons[MoonIterator].PositionX == InitialState[MoonIterator].PositionX && Moons[MoonIterator].PositionY == InitialState[MoonIterator].PositionY && Moons[MoonIterator].PositionZ == InitialState[MoonIterator].PositionZ && Moons[MoonIterator].VelocityX == InitialState[MoonIterator].VelocityX && Moons[MoonIterator].VelocityY == InitialState[MoonIterator].VelocityY && Moons[MoonIterator].VelocityZ == InitialState[MoonIterator].VelocityZ) // if initial state
		{
			StepDifference = Steps - std::accumulate(SavedTiming[MoonIterator].begin(), SavedTiming[MoonIterator].end(), 0);
			std::cout << "Steps : " << StepDifference << " | Moon : " << MoonIterator << std::endl;
			if (SavedTiming[MoonIterator].size() % 2 == 1) // odd
			{
				if (Periods[MoonIterator] == -1) // No period found
				{
					SavedTiming[MoonIterator].push_back(StepDifference);
					Middle = SavedTiming[MoonIterator].size() / 2;
					PeriodFound[MoonIterator] = true;
					for (CharacterPosition = 0; CharacterPosition < Middle; CharacterPosition++)
					{
						if (SavedTiming[MoonIterator][CharacterPosition] != SavedTiming[MoonIterator][CharacterPosition + Middle])
						{
							PeriodFound[MoonIterator] = false;
							break;
						}
					}

					if (PeriodFound[MoonIterator])
					{
						Periods[MoonIterator] = Middle;
					}
				}
				else // Period found
				{
					ValidatePeriod(SavedTiming, MoonIterator, Periods, PeriodFound, StepDifference);
					SavedTiming[MoonIterator].push_back(StepDifference);
				}
			}
			else // pair
			{
				if (Periods[MoonIterator] != -1) // period found
				{
					ValidatePeriod(SavedTiming, MoonIterator, Periods, PeriodFound, StepDifference);
				}
				SavedTiming[MoonIterator].push_back(StepDifference);
			}
		}
	}
}

int gcd(int a, int b)
{
	for (;;)
	{
		if (a == 0) return b;
		b %= a;
		if (b == 0) return a;
		a %= b;
	}
}

int lcm(int a, int b)
{
	int temp = gcd(a, b);

	return temp ? (a / temp * b) : 0;
}

void ValidatePeriod(std::vector<std::vector<int>> &SavedTiming, int MoonIterator, std::vector<int> & Periods, std::vector<bool> & PeriodFound, int StepDifference)
{
	int CharacterPosition;
	int PeriodIterations;
	int PeriodIteration;
	CharacterPosition = SavedTiming[MoonIterator].size() % Periods[MoonIterator];
	PeriodIterations = SavedTiming[MoonIterator].size() / Periods[MoonIterator];

	for (PeriodIteration = 0; PeriodIteration < PeriodIterations; PeriodIteration++)
	{
		if (SavedTiming[MoonIterator][PeriodIteration * Periods[MoonIterator] + CharacterPosition] != StepDifference)
		{
			Periods[MoonIterator] = -1;
			PeriodFound[MoonIterator] = false;
			break;
		}
	}
}

bool CompareInitialState(std::vector<Moon> Moons, std::vector<Moon> InitialState)
{
	int MoonIterator = 0;
	bool IsGood = true;
	for (auto TargetMoon : Moons)
	{
		if (Moons[MoonIterator].PositionX != InitialState[MoonIterator].PositionX || Moons[MoonIterator].PositionY != InitialState[MoonIterator].PositionY || Moons[MoonIterator].PositionZ != InitialState[MoonIterator].PositionZ || Moons[MoonIterator].VelocityX != InitialState[MoonIterator].VelocityX || Moons[MoonIterator].VelocityY != InitialState[MoonIterator].VelocityY || Moons[MoonIterator].VelocityZ != InitialState[MoonIterator].VelocityZ)
		{
			IsGood = false;
			break;
		}
		MoonIterator++;
	}
	return IsGood;
}

bool CompareState(std::vector<Moon> Moons, std::vector<std::vector<Moon>> States)
{
	int MoonIterator;
	bool IsGood = false;
	for (auto State : States)
	{
		MoonIterator = 0;
		IsGood = true;
		for (auto TargetMoon : Moons)
		{
			if (Moons[MoonIterator].PositionX != State[MoonIterator].PositionX || Moons[MoonIterator].PositionY != State[MoonIterator].PositionY || Moons[MoonIterator].PositionZ != State[MoonIterator].PositionZ || Moons[MoonIterator].VelocityX != State[MoonIterator].VelocityX || Moons[MoonIterator].VelocityY != State[MoonIterator].VelocityY || Moons[MoonIterator].VelocityZ != State[MoonIterator].VelocityZ)
			{
				IsGood = false;
				break;
			}
		}
		if (IsGood)
		{
			break;
		}
	}
	return IsGood;
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