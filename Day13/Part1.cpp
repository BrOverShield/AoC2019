#include "Part1.h"

double Part1()
{
	std::cout.precision(dbl::max_digits10);
	double RelativeBase = 0;
	std::vector<double> IntCodes;
	double Pointer = 0;
	bool Endprogram = false;
	double Answer;
	IntCodes = IntCodeParser("input.txt");
	IntCodes[0] = 2;
	double Input = 2;
	double Output = NULL;
	bool NewOutput = false;
	int OutputDataCounter = 0;
	std::map<int, std::map<int, int>> Map;
	Block NewBlock;
	Block Ball;
	Block Paddle;
	double HighScore = 0;
	int BlockCounter = 0;
	bool StopCountingBlocks = false;
	bool InitialBallValuesSaved = false;
	while (BlockCounter != 0 || !StopCountingBlocks || !Endprogram)
	{
		if (Ball.PositionX != Paddle.PositionX)
		{
			if (Ball.PositionX < Paddle.PositionX)
			{
				Input = JOYSTICK_LEFT;
			}
			else
			{
				Input = JOYSTICK_RIGHT;
			}
		}
		else
		{
			Input = JOYSTICK_NEUTRAL;
		}
		NewOutput = RunIntCode(IntCodes, Pointer, Endprogram, RelativeBase, Input, Output);
		if (NewOutput)
		{
			if (OutputDataCounter == 0)
			{
				NewBlock.PositionX = Output;
				OutputDataCounter++;
			}
			else if (OutputDataCounter == 1)
			{
				NewBlock.PositionY = Output;
				OutputDataCounter++;
			}
			else if (OutputDataCounter == 2) // Troisieme numero
			{
				OutputDataCounter = 0;
				NewBlock.BlockType = Output;
				if (Output != EMPTY_NUMBER && Output != WALL_NUMBER && Output != BLOCK_NUMBER && Output != PADDLE_NUMBER && Output != BALL_NUMBER)
				{
					if (HighScore < Output)
					{
						HighScore = Output;
						std::cout << "New High Score : " << HighScore << std::endl;
					}
					else
					{
						std::cout << "HighScore got Lowered! : " << HighScore << " doit etre plus petit que " << Output << std::endl;
					}
				}
				else
				{
					if (Output == BALL_NUMBER)
					{
						Ball = NewBlock;
						if (InitialBallValuesSaved)
						{
							StopCountingBlocks = true;
							//std::cout << "Number of blocks to break : " << BlockCounter << std::endl;
						}
						InitialBallValuesSaved = true;
					}
					else if (Output == PADDLE_NUMBER)
					{
						Paddle = NewBlock;
					}
					else if (Output == BLOCK_NUMBER)
					{
						if (!StopCountingBlocks)
						{
							BlockCounter++;
						}
					}
					SaveBlockToMap(Map, NewBlock, BlockCounter);
					//std::cout << NewBlock.PositionX << "|" << NewBlock.PositionY << "|" << NewBlock.BlockType << std::endl;
				}
			}
			else
			{
				std::cout << "ERROR | Wrong OutputDataCounter Number : " << std::endl;
			}
			//std::cout << Output << std::endl;
		}
	}
	Answer = HighScore;
	return Answer;
}

void SaveBlockToMap(std::map<int, std::map<int, int>>& Map, Block NewBlock, int& BlockCounter)
{
	if (NewBlock.BlockType == EMPTY_NUMBER)
	{
		if (Map.find(NewBlock.PositionX) != Map.end())
		{
			if (Map[NewBlock.PositionX].find(NewBlock.PositionY) != Map[NewBlock.PositionX].end())
			{
				if (Map[NewBlock.PositionX][NewBlock.PositionY] == BLOCK_NUMBER)
				{
					BlockCounter--;
					std::cout << "Block Count : " << BlockCounter << std::endl;
				}
			}
		}
	}
	Map[NewBlock.PositionX][NewBlock.PositionY] = NewBlock.BlockType;
}
