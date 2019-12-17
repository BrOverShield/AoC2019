#pragma once

#include <vector>
#include <string> // stoi
#include <map>
#include <fstream>
#include <iostream> // cout, endl
#include <algorithm> // replace
#include <chrono>

const std::string InputFilePath = "input.txt";
const int POSITION_MODE = 0;
const int IMMEDIATE_MODE = 1;
const int RELATIVE_BASE_MODE = 2;

const int PARAMETER_NUMBER_1 = 1;
const int PARAMETER_NUMBER_2 = 2;
const int PARAMETER_NUMBER_3 = 3;

typedef std::numeric_limits< double > dbl;

std::vector<std::map<char, int>> Day12FileParser();
void removeCharsFromString(std::string& str, std::vector<char> charsToRemove);
void DisplayAnswer(double Answer);
void StartTime();
void StopTime();
void DisplayTime();

// INTCODE COMPUTER
bool RunIntCode(std::vector<double>& IntCodes, double& Pointer, bool& EndProgram, double& RelativeBase, double Input, double& Output);
std::vector<double> IntCodeParser(std::string path);
std::vector<double> split(std::string s, std::string delimiter);
int ctoi(char c);
int ExtractOpCode(double OpCode);
int FetchParameterMode(double OpCode, int ParameterNumber);
void FetchParameterModes(double OpCode, int& ParameterMode1, int& ParameterMode2, int& ParameterMode3);
void FetchParameterModes(double OpCode, int& ParameterMode1, int& ParameterMode2);
void FetchParameterModes(double OpCode, int& ParameterMode1);
void FetchParameters(std::vector<double> FullOpCode, double& Parameter1, double& Parameter2, double& Parameter3, double Pointer);
void FetchParameters(std::vector<double> FullOpCode, double& Parameter1, double& Parameter2, double Pointer);
void FetchParameters(std::vector<double> FullOpCode, double& Parameter1, double Pointer);
std::vector<double> VerifyMemoryLength(std::vector<double> IntCodes, double Position);
double GetNumbersByMode(std::vector<double>& IntCodes, int ParameterMode, double Parameter1, double RelativeBase);
double GetPointerByMode(std::vector<double>& IntCodes, int ParameterMode, double Parameter, double RelativeBase);