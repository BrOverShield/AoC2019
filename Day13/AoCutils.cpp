#include "AoCutils.h"

std::chrono::time_point<std::chrono::steady_clock> start;
std::chrono::time_point<std::chrono::steady_clock> stop;

int ctoi(char c)
{
	return c - '0';
}

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

void DisplayAnswer(double Answer)
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

std::vector<double> split(std::string s, std::string delimiter)
{
	size_t pos = 0;
	std::string token;
	std::vector<double> Result;
	while ((pos = s.find(delimiter)) != std::string::npos)
	{
		token = s.substr(0, pos);
		int nb = strtol(token.data(), nullptr, 10);
		Result.push_back(nb);
		s.erase(0, pos + delimiter.length());
	}
	int nb = strtol(s.data(), nullptr, 10);
	Result.push_back(nb);
	return Result;
}

std::vector<double> IntCodeParser(std::string path)
{
	std::vector<double> IntCodes;
	std::string input;
	std::ifstream file(path);
	if (file.is_open())
	{
		while (file.good())
		{
			file >> input;
		}
		file.close();
	}
	IntCodes = split(input, ",");
	return IntCodes;
}

bool RunIntCode(std::vector<double> &IntCodes, double &Pointer, bool &EndProgram, double &RelativeBase, double Input, double &Output)
{
	int OpCode;
	int ParameterMode1;
	int ParameterMode2;
	int ParameterMode3;
	double Parameter1;
	double Parameter2;
	double Parameter3;
	double NumberA = -1;
	double NumberB = -1;
	double DestinationPointer;
	int FullOpCode;
	double Result;
	FullOpCode = IntCodes[Pointer];
	OpCode = ExtractOpCode(FullOpCode);

	if (OpCode == 1 || OpCode == 2 || OpCode == 7 || OpCode == 8)
	{
		FetchParameters(IntCodes, Parameter1, Parameter2, Parameter3, Pointer);
		FetchParameterModes(FullOpCode, ParameterMode1, ParameterMode2, ParameterMode3);
		NumberA = GetNumbersByMode(IntCodes, ParameterMode1, Parameter1, RelativeBase);
		NumberB = GetNumbersByMode(IntCodes, ParameterMode2, Parameter2, RelativeBase);
		DestinationPointer = GetPointerByMode(IntCodes, ParameterMode3, Parameter3, RelativeBase);
	}
	else if (OpCode == 3 || OpCode == 4 || OpCode == 9)
	{
		FetchParameters(IntCodes, Parameter1, Pointer);
		FetchParameterModes(FullOpCode, ParameterMode1);
	}
	else if (OpCode == 5 || OpCode == 6)
	{
		FetchParameters(IntCodes, Parameter1, Parameter2, Pointer);
		FetchParameterModes(FullOpCode, ParameterMode1, ParameterMode2);
		NumberA = GetNumbersByMode(IntCodes, ParameterMode1, Parameter1, RelativeBase);
		NumberB = GetNumbersByMode(IntCodes, ParameterMode2, Parameter2, RelativeBase);
	}
	
	switch (OpCode)
	{
	case 1:
		Result = NumberA + NumberB;
		IntCodes[DestinationPointer] = Result;
		break;
	case 2:
		Result = NumberA * NumberB;
		IntCodes[DestinationPointer] = Result;
		break;
	case 3:
		DestinationPointer = GetPointerByMode(IntCodes, ParameterMode1, Parameter1, RelativeBase);
		IntCodes[DestinationPointer] = Input;
		break;
	case 4:
		NumberA = GetNumbersByMode(IntCodes, ParameterMode1, Parameter1, RelativeBase);
		Output = NumberA;
		break;
	case 5:
		if (NumberA != 0)
		{
			IntCodes = VerifyMemoryLength(IntCodes, NumberB);
			Pointer = NumberB;
		}
		else
		{
			Pointer += 3;
		}
		break;
	case 6:
		if (NumberA == 0)
		{
			IntCodes = VerifyMemoryLength(IntCodes, NumberB);
			Pointer = NumberB;
		}
		else
		{
			Pointer += 3;
		}
		break;
	case 7:
		if (NumberA < NumberB)
		{
			IntCodes[DestinationPointer] = 1;
		}
		else
		{
			IntCodes[DestinationPointer] = 0;
		}
		break;
	case 8:
		if (NumberA == NumberB)
		{
			IntCodes[DestinationPointer] = 1;
		}
		else
		{
			IntCodes[DestinationPointer] = 0;
		}
		break;
	case 9:
		NumberA = GetNumbersByMode(IntCodes, ParameterMode1, Parameter1, RelativeBase);
		RelativeBase += NumberA;
		break;
	case 99:
		EndProgram = true;
		break;
	default:
		std::cout << "ERROR | Bad OpCode : " << OpCode << std::endl;
		break;
	}
	
	if (OpCode == 1 || OpCode == 2 || OpCode == 7 || OpCode == 8)
	{
		Pointer += 4;
	}
	else if (OpCode == 3 || OpCode == 4 || OpCode == 9)
	{
		Pointer += 2;
	}
	else
	{
		if (OpCode != 99 && OpCode != 5 && OpCode != 6)
		{
			std::cout << "ERROR | Did not increment Pointer. OpCode is : " << OpCode << std::endl;
		}
	}
	if (OpCode == 4)
	{
		return true;
	}
	else
	{
		return false;
	}
}

double GetPointerByMode(std::vector<double> &IntCodes, int ParameterMode, double Parameter, double RelativeBase)
{
	if (ParameterMode == POSITION_MODE)
	{
		IntCodes = VerifyMemoryLength(IntCodes, Parameter);
		return Parameter;
	}
	else if (ParameterMode == RELATIVE_BASE_MODE)
	{
		IntCodes = VerifyMemoryLength(IntCodes, Parameter + RelativeBase);
		return Parameter + RelativeBase;
	}
	else
	{
		std::cout << "ERROR | Bad Pointer Parameter : " << ParameterMode << std::endl;
		return NULL;
	}
}

double GetNumbersByMode(std::vector<double> &IntCodes, int ParameterMode, double Parameter, double RelativeBase)
{
	if (ParameterMode == POSITION_MODE)
	{
		IntCodes = VerifyMemoryLength(IntCodes, Parameter);
		return IntCodes[Parameter];
	}
	else if (ParameterMode == IMMEDIATE_MODE)
	{
		return Parameter;
	}
	else if (ParameterMode == RELATIVE_BASE_MODE)
	{
		double Pointer = Parameter + RelativeBase;
		IntCodes = VerifyMemoryLength(IntCodes, Pointer);
		return IntCodes[RelativeBase + Parameter];
	}
	else
	{
		std::cout << "ERROR | Wrong Parameter Mode : " << ParameterMode << std::endl;
		return NULL;
	}
}

std::vector<double> VerifyMemoryLength(std::vector<double> IntCodes, double Position)
{
	if (IntCodes.size() < Position + 1)
	{
		for (double i = IntCodes.size(); i <= Position + 1; i++)
		{
			IntCodes.push_back(0);
		}
	}
	return IntCodes;
}

void FetchParameters(std::vector<double> IntCodes, double &Parameter1, double Pointer)
{
	Parameter1 = IntCodes[Pointer + 1];
}

void FetchParameters(std::vector<double> IntCodes, double &Parameter1, double &Parameter2, double Pointer)
{
	Parameter1 = IntCodes[Pointer + 1];
	Parameter2 = IntCodes[Pointer + 2];
}

void FetchParameters(std::vector<double> IntCodes, double &Parameter1, double &Parameter2, double &Parameter3, double Pointer)
{
	Parameter1 = IntCodes[Pointer + 1];
	Parameter2 = IntCodes[Pointer + 2];
	Parameter3 = IntCodes[Pointer + 3];
}

void FetchParameterModes(double FullOpCode, int &ParameterMode1)
{
	ParameterMode1 = FetchParameterMode(FullOpCode, PARAMETER_NUMBER_1);
}

void FetchParameterModes(double FullOpCode, int& ParameterMode1, int& ParameterMode2)
{
	ParameterMode1 = FetchParameterMode(FullOpCode, PARAMETER_NUMBER_1);
	ParameterMode2 = FetchParameterMode(FullOpCode, PARAMETER_NUMBER_2);
}

void FetchParameterModes(double FullOpCode, int& ParameterMode1, int& ParameterMode2, int& ParameterMode3)
{
	ParameterMode1 = FetchParameterMode(FullOpCode, PARAMETER_NUMBER_1);
	ParameterMode2 = FetchParameterMode(FullOpCode, PARAMETER_NUMBER_2);
	ParameterMode3 = FetchParameterMode(FullOpCode, PARAMETER_NUMBER_3);
}

int FetchParameterMode(double OpCode, int ParameterNumber)
{
	std::string FullOpCode;
	int ParameterMode;
	char c;
	FullOpCode = std::to_string((int)OpCode);
	if (FullOpCode.size() < (2 + ParameterNumber))
	{
		ParameterMode = 0;
	}
	else
	{
		c = FullOpCode.at(FullOpCode.size() - (2 + ParameterNumber));
		ParameterMode = ctoi(c);
	}
	return ParameterMode;
}

int ExtractOpCode(double OpCode)
{
	std::string Code;
	int OpCodeLength;
	std::string sOpCode;
	Code = std::to_string((int)OpCode);
	OpCodeLength = Code.size();
	if (OpCodeLength <= 2)
	{
		return (int)OpCode;
	}
	else
	{
		sOpCode = Code.at(OpCodeLength - 1);
		sOpCode = std::string() + Code.at(OpCodeLength - 2) + Code.at(OpCodeLength - 1);
		OpCode = stoi(sOpCode);
		return OpCode;
	}
	
}