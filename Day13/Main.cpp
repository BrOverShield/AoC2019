#include "Part1.h"

int main(int argc, char* argv[])
{
	StartTime();
	double Answer = Part1();
	std::cout << "AYE : " << Answer << std::endl;
	DisplayAnswer(Answer);
	StopTime();
	DisplayTime();
	return 0;
}