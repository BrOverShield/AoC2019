#include "Part1.h"

double Part1()
{
	std::cout.precision(dbl::max_digits10);
	double RelativeBase = 0;
	std::vector<double> IntCodes;
	double Pointer = 0;
	bool Endprogram = false;
	double Answer;
	IntCodes = IntCodeParser("inputDay9.txt");
	double Input = 2;
	double Output = NULL;
	bool NewOutput = false;
	while (!Endprogram)
	{
		if (NewOutput)
		{
			std::cout << Output << std::endl;
		}
		NewOutput = RunIntCode(IntCodes, Pointer, Endprogram, RelativeBase, Input, Output);
	}
	Answer = Output;
	std::cout << "AYE : " << Output << std::endl;
	return Answer;
}