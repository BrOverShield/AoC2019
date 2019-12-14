#include "Part2.h"
#include "AoCutils.h"

int main(int argc, char* argv[])
{
	StartTime();
	int TotalEnergy = Part2();
	DisplayAnswer(TotalEnergy);
	StopTime();
	DisplayTime();
	return 0;
}