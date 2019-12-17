#pragma once
#include "AoCutils.h"
#include "Block.h"

const int EMPTY_NUMBER = 0;
const int WALL_NUMBER = 1;
const int BLOCK_NUMBER = 2;
const int PADDLE_NUMBER = 3;
const int BALL_NUMBER = 4;

const int JOYSTICK_LEFT = -1;
const int JOYSTICK_RIGHT = 1;
const int JOYSTICK_NEUTRAL = 0;

double Part1();
void SaveBlockToMap(std::map<int, std::map<int, int>>& Map, Block NewBlock, int& BlockCounter);
