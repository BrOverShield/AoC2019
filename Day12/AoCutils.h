#pragma once

#include <vector>
#include <string> // stoi
#include <map>
#include <fstream>
#include <iostream> // cout, endl
#include <algorithm> // replace
#include <chrono>

std::vector<std::map<char, int>> Day12FileParser();
void removeCharsFromString(std::string& str, std::vector<char> charsToRemove);
void DisplayAnswer(int Answer);
void StartTime();
void StopTime();
void DisplayTime();