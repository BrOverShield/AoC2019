#pragma once
#include "Part1.h"
#include "Part2.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string> // to_string(), stoi()
#include <map>
#include <numeric> // iota
#include <chrono>
#include <limits>
// #include "NumberlikeArray.hh"
// #include "BigIntegerLibrary.hh"

std::string coorToString(int RobotX, int RobotY);
void paint(int Target, int& RobotX, int& RobotY, std::map<std::string, int>& PaintedSurfaces);
void moveRobot(int Target, int& RobotX, int& RobotY, int& RobotDirection);
int getColour(int RobotX, int RobotY, std::map<std::string, int> PaintedSurfaces);
std::vector<double> split(std::string s, std::string delimiter);
std::vector<double> addMemory(std::vector<double> IntCodes, double Index);

typedef std::numeric_limits< double > dbl;

const int BLACK_NUMBER = 0;
const int WHITE_NUMBER = 1;

const int TURN_LEFT_NUMBER = 0; // 90 degrees
const int TURN_RIGHT_NUMBER = 1; // 90 degrees

const char DRAW_BLACK_CHARACTER = '.';
const char DRAW_WHITE_CHARACTER = '#';

const int UP_DIRECTION = 0;
const int LEFT_DIRECTION = 1;
const int DOWN_DIRECTION = 2;
const int RIGHT_DIRECTION = 3;

