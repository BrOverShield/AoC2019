#include <iostream>
#include <fstream>
#include <vector>
#include <string> // to_string(), stoi()
#include <map>
#include <numeric> // iota
#include <chrono>
#include <limits>
#include "Main.h"
// #include "NumberlikeArray.hh"
// #include "BigIntegerLibrary.hh"

void Part2()
{

    std::cout.precision(dbl::max_digits10);
    auto start = std::chrono::high_resolution_clock::now();
    std::string input;
    std::vector<double> IntCodes;
    double IntCode;
    char c;
    // std::ifstream file("C:\\Users\\tmdud\\Documents\\GitHub\\AoC2019\\day07\\input.txt");
    std::ifstream file("C:\\Users\\tmdud\\Documents\\GitHub\\AoC2019\\day11_test\\input.txt");
    if (file.is_open())
    {
        while (file.good())
        {
            file >> IntCode;
            IntCodes.push_back(IntCode);
            file >> c;
        }
        file.close();
    }
    double ID = 2;
    double ProgressionPointer = 0;
    bool IsFinished = false;
    double PointerA;
    double PointerB;
    double NumberA;
    double NumberB;
    double DestinationPointer;
    double TargetPointer;
    int OpCode;
    int Code;
    double Param1Mode;
    double Param2Mode;
    double Param3Mode;
    double Target;
    std::string FilledOpCode;
    std::string sCode;
    std::string sOpCode;
    double RelativeBase = UP_DIRECTION;
    bool DataType = false; // false means that the next number to be printed indicates color. true means direction to turn;

    int RobotX = 0;
    int RobotY = 0;
    int RobotDirection = 0;

    std::map<std::string, int> PaintedSurfaces;
    PaintedSurfaces["0,0"] = WHITE_NUMBER;

    do
    {
        if (IntCodes[ProgressionPointer] != 99)
        {
            double Result = 0;
            OpCode = IntCodes[ProgressionPointer];
            sOpCode = std::to_string(OpCode);
            Param1Mode = 0;
            Param2Mode = 0;
            Param3Mode = 0;
            if (sOpCode.length() > 2) // if the number is at least 4 digits
            {
                FilledOpCode = std::string();
                for (double i = sOpCode.length(); i < 5; i++)
                {
                    FilledOpCode += "0";
                }
                FilledOpCode += sOpCode;
                c = FilledOpCode.data()[2];
                Param1Mode = c - '0';
                c = FilledOpCode.data()[1];
                Param2Mode = c - '0';
                c = FilledOpCode.data()[0];
                Param3Mode = c - '0';
                sCode = "";
                sCode.push_back(FilledOpCode.data()[3]);
                sCode.push_back(FilledOpCode.data()[4]);
                Code = stoi(sCode);
            }
            else
            {
                Code = OpCode;
            }
            // std::cout << "Code" << Code << std::endl;
            switch (Code)
            {
            case 1:
                PointerA = IntCodes[ProgressionPointer + 1];
                PointerB = IntCodes[ProgressionPointer + 2];
                
                if (Param1Mode == 1)
                {
                    NumberA = PointerA;
                }
                else if (Param1Mode == 2)
                {
                    if (PointerA + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, PointerA + RelativeBase);
                    }

                    NumberA = IntCodes[PointerA + RelativeBase];
                }
                else
                {
                    if (PointerA + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, PointerA + RelativeBase);
                    }
                    NumberA = IntCodes[PointerA];
                }

                if (Param2Mode == 1)
                {
                    NumberB = PointerB;
                }
                else if (Param2Mode == 2)
                {
                    if (PointerB + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, PointerB + RelativeBase);
                    }
                    NumberB = IntCodes[RelativeBase + PointerB];
                }
                else
                {
                    if (PointerB + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, PointerB + RelativeBase);
                    }
                    NumberB = IntCodes[PointerB];
                }

                if (Param3Mode == 0)
                {
                    DestinationPointer = IntCodes[ProgressionPointer + 3];
                }
                else if (Param3Mode == 2)
                {
                    DestinationPointer = IntCodes[ProgressionPointer + 3] + RelativeBase;
                }
                else
                {
                    std::cout << "ERROR in operation 1. Param1Mode = " << Param3Mode << std::endl;
                }

                if (DestinationPointer + RelativeBase > IntCodes.size())
                {
                    IntCodes = addMemory(IntCodes, DestinationPointer + RelativeBase);
                }
                Result = NumberA + NumberB;
                IntCodes[DestinationPointer] = Result;
                ProgressionPointer += 4;
                break;
            case 2:
                PointerA = IntCodes[ProgressionPointer + 1];
                PointerB = IntCodes[ProgressionPointer + 2];
                if (Param1Mode == 1)
                {
                    NumberA = PointerA;
                }
                else if (Param1Mode == 2)
                {
                    if (PointerA + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, PointerA + RelativeBase);
                    }

                    NumberA = IntCodes[PointerA + RelativeBase];
                }
                else
                {
                    if (PointerA + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, PointerA + RelativeBase);
                    }
                    NumberA = IntCodes[PointerA];
                }

                if (Param2Mode == 1)
                {
                    NumberB = PointerB;
                }
                else if (Param2Mode == 2)
                {
                    if (PointerB + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, PointerB + RelativeBase);
                    }
                    NumberB = IntCodes[RelativeBase + PointerB];
                }
                else
                {
                    if (PointerB + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, PointerB + RelativeBase);
                    }
                    NumberB = IntCodes[PointerB];
                }

                if (Param3Mode == 0)
                {
                    DestinationPointer = IntCodes[ProgressionPointer + 3];
                }
                else if (Param3Mode == 2)
                {
                    DestinationPointer = IntCodes[ProgressionPointer + 3] + RelativeBase;
                }
                else
                {
                    std::cout << "ERROR in operation 2. Param1Mode = " << Param3Mode << std::endl;
                }

                if (DestinationPointer + RelativeBase > IntCodes.size())
                {
                    IntCodes = addMemory(IntCodes, DestinationPointer + RelativeBase);
                }
                Result = NumberA * NumberB;
                IntCodes[DestinationPointer] = Result;
                ProgressionPointer += 4;
                break;
            case 3:
                if (Param1Mode == 0)
                {
                    DestinationPointer = IntCodes[ProgressionPointer + 1];
                }
                else if (Param1Mode == 2)
                {
                    DestinationPointer = IntCodes[ProgressionPointer + 1] + RelativeBase;
                }
                else
                {
                    std::cout << "ERROR in operation 3. Param1Mode = " << Param1Mode << std::endl;
                }
                if (DestinationPointer + RelativeBase > IntCodes.size())
                {
                    IntCodes = addMemory(IntCodes, DestinationPointer + RelativeBase);
                }

                ID = getColour(RobotX, RobotY, PaintedSurfaces);

                IntCodes[DestinationPointer] = ID;
                ProgressionPointer += 2;

                break;
            case 4:
                if (Param1Mode == 1)
                {
                    Target = IntCodes[ProgressionPointer + 1];
                }
                else if (Param1Mode == 2)
                {
                    TargetPointer = IntCodes[ProgressionPointer + 1] + RelativeBase;
                    if (TargetPointer + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, TargetPointer + RelativeBase);
                    }
                    Target = IntCodes[TargetPointer];
                }
                else
                {
                    TargetPointer = IntCodes[ProgressionPointer + 1];
                    if (TargetPointer + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, TargetPointer + RelativeBase);
                    }
                    Target = IntCodes[TargetPointer];
                }

                //std::cout << Target << std::endl;
                if (!DataType) // color to paint
                {
                    paint(Target, RobotX, RobotY, PaintedSurfaces);
                    DataType = true;
                    //std::cout << "PAINT COLOR : " << Target << std::endl;
                }
                else // turn direction
                {
                    moveRobot(Target, RobotX, RobotY, RobotDirection);
                    DataType = false;
                    //std::cout << "TURN : " << Target << std::endl;
                }

                ProgressionPointer += 2;
                break;
            case 5:
                if (Param1Mode == 1)
                {
                    Target = IntCodes[ProgressionPointer + 1];
                }
                else if (Param1Mode == 2)
                {
                    TargetPointer = IntCodes[ProgressionPointer + 1] + RelativeBase;
                    if (TargetPointer + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, TargetPointer + RelativeBase);
                    }
                    Target = IntCodes[TargetPointer];
                }
                else
                {
                    TargetPointer = IntCodes[ProgressionPointer + 1];
                    if (TargetPointer + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, TargetPointer + RelativeBase);
                    }
                    Target = IntCodes[TargetPointer];
                }
                if (Target != 0)
                {
                    if (Param2Mode == 1)
                    {
                        ProgressionPointer = IntCodes[ProgressionPointer + 2];
                    }
                    else if (Param2Mode == 2)
                    {
                        TargetPointer = IntCodes[ProgressionPointer + 2] + RelativeBase;
                        if (TargetPointer + RelativeBase > IntCodes.size())
                        {
                            IntCodes = addMemory(IntCodes, TargetPointer + RelativeBase);
                        }
                        ProgressionPointer = IntCodes[TargetPointer];
                    }
                    else
                    {
                        TargetPointer = IntCodes[ProgressionPointer + 2];
                        if (TargetPointer + RelativeBase > IntCodes.size())
                        {
                            IntCodes = addMemory(IntCodes, TargetPointer + RelativeBase);
                        }
                        ProgressionPointer = IntCodes[TargetPointer];
                    }
                }
                else
                {
                    ProgressionPointer += 3;
                }
                break;
            case 6:
                if (Param1Mode == 1)
                {
                    Target = IntCodes[ProgressionPointer + 1];
                }
                else if (Param1Mode == 2)
                {
                    TargetPointer = IntCodes[ProgressionPointer + 1] + RelativeBase;
                    if (TargetPointer + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, TargetPointer + RelativeBase);
                    }
                    Target = IntCodes[TargetPointer];
                }
                else
                {
                    TargetPointer = IntCodes[ProgressionPointer + 1];
                    if (TargetPointer + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, TargetPointer + RelativeBase);
                    }
                    Target = IntCodes[TargetPointer];
                }
                if (Target == 0)
                {
                    if (Param2Mode == 1)
                    {
                        ProgressionPointer = IntCodes[ProgressionPointer + 2];
                    }
                    else if (Param2Mode == 2)
                    {
                        TargetPointer = IntCodes[ProgressionPointer + 2] + RelativeBase;
                        if (TargetPointer + RelativeBase > IntCodes.size())
                        {
                            IntCodes = addMemory(IntCodes, TargetPointer + RelativeBase);
                        }
                        ProgressionPointer = IntCodes[TargetPointer];
                    }
                    else
                    {
                        TargetPointer = IntCodes[ProgressionPointer + 2];
                        if (TargetPointer + RelativeBase > IntCodes.size())
                        {
                            IntCodes = addMemory(IntCodes, TargetPointer + RelativeBase);
                        }
                        ProgressionPointer = IntCodes[TargetPointer];
                    }
                }
                else
                {
                    ProgressionPointer += 3;
                }

                break;
            case 7:
                if (Param1Mode == 1)
                {
                    NumberA = IntCodes[ProgressionPointer + 1];
                }
                else if (Param1Mode == 2)
                {
                    PointerA = IntCodes[ProgressionPointer + 1] + RelativeBase;
                    if (PointerA + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, PointerA + RelativeBase);
                    }
                    NumberA = IntCodes[PointerA];
                }
                else
                {
                    PointerA = IntCodes[ProgressionPointer + 1];
                    if (PointerA + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, PointerA + RelativeBase);
                    }
                    NumberA = IntCodes[PointerA];
                }
                if (Param2Mode == 1)
                {
                    NumberB = IntCodes[ProgressionPointer + 2];
                }
                else if (Param2Mode == 2)
                {
                    PointerB = IntCodes[ProgressionPointer + 2] + RelativeBase;
                    if (PointerB + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, PointerB + RelativeBase);
                    }
                    NumberB = IntCodes[PointerB];
                }
                else
                {
                    PointerB = IntCodes[ProgressionPointer + 2];
                    if (PointerB + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, PointerB + RelativeBase);
                    }
                    NumberB = IntCodes[PointerB];
                }
                if (Param3Mode == 0)
                {
                    DestinationPointer = IntCodes[ProgressionPointer + 3];
                }
                else if (Param3Mode == 2)
                {
                    DestinationPointer = IntCodes[ProgressionPointer + 3] + RelativeBase;
                }
                else
                {
                    std::cout << "ERROR in operation 7. Param3Mode = " << Param3Mode << std::endl;
                }
                if (DestinationPointer + RelativeBase > IntCodes.size())
                {
                    IntCodes = addMemory(IntCodes, DestinationPointer + RelativeBase);
                }
                if (NumberA < NumberB)
                {
                    IntCodes[DestinationPointer] = 1;
                }
                else
                {
                    IntCodes[DestinationPointer] = 0;
                }
                ProgressionPointer += 4;
                break;
            case 8:
                if (Param1Mode == 1)
                {
                    NumberA = IntCodes[ProgressionPointer + 1];
                }
                else if (Param1Mode == 2)
                {
                    PointerA = IntCodes[ProgressionPointer + 1] + RelativeBase;
                    if (PointerA + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, PointerA + RelativeBase);
                    }
                    NumberA = IntCodes[PointerA];
                }
                else
                {
                    PointerA = IntCodes[ProgressionPointer + 1];
                    if (PointerA + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, PointerA + RelativeBase);
                    }
                    NumberA = IntCodes[PointerA];
                }
                if (Param2Mode == 1)
                {
                    NumberB = IntCodes[ProgressionPointer + 2];
                }
                else if (Param2Mode == 2)
                {
                    PointerB = IntCodes[ProgressionPointer + 2] + RelativeBase;
                    if (PointerB + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, PointerB + RelativeBase);
                    }
                    NumberB = IntCodes[PointerB];
                }
                else
                {
                    PointerB = IntCodes[ProgressionPointer + 2];
                    if (PointerB + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, PointerB + RelativeBase);
                    }
                    NumberB = IntCodes[PointerB];
                }
                if (Param3Mode == 0)
                {
                    DestinationPointer = IntCodes[ProgressionPointer + 3];
                }
                else if (Param3Mode == 2)
                {
                    DestinationPointer = IntCodes[ProgressionPointer + 3] + RelativeBase;
                }
                else
                {
                    std::cout << "ERROR in operation 8. Param3Mode = " << Param3Mode << std::endl;
                }
                if (DestinationPointer + RelativeBase > IntCodes.size())
                {
                    IntCodes = addMemory(IntCodes, DestinationPointer + RelativeBase);
                }
                if (NumberA == NumberB)
                {
                    IntCodes[DestinationPointer] = 1;
                }
                else
                {
                    IntCodes[DestinationPointer] = 0;
                }
                ProgressionPointer += 4;
                break;
            case 9:
                if (Param1Mode == 1)
                {
                    Target = IntCodes[ProgressionPointer + 1];
                }
                else if (Param1Mode == 2)
                {
                    TargetPointer = IntCodes[ProgressionPointer + 1] + RelativeBase;
                    if (TargetPointer + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, TargetPointer + RelativeBase);
                    }
                    Target = IntCodes[TargetPointer];
                }
                else
                {
                    TargetPointer = IntCodes[ProgressionPointer + 1];
                    if (TargetPointer + RelativeBase > IntCodes.size())
                    {
                        IntCodes = addMemory(IntCodes, TargetPointer + RelativeBase);
                    }
                    Target = IntCodes[TargetPointer];
                }
                RelativeBase += Target;
                ProgressionPointer += 2;
                break;
            default:
                std::cout << "ERROR : IntCodes[" << ProgressionPointer << "] = " << IntCodes[ProgressionPointer] << std::endl;
                IsFinished = true;
            }
        }
        else
        {
            IsFinished = true;
        }
    } while (!IsFinished);

    int MaxX = 0;
    int MaxY = 0;
    int MinX = 1000;
    int MinY = 1000;
    std::map<int, std::map<int, int>> Dictionary;
    for (auto Painted : PaintedSurfaces)
    {
        std::vector<double> coords = split(Painted.first, ",");
        int X = coords[0];
        int Y = coords[1];
        if (X > MaxX)
        {
            MaxX = X;
        }
        if (Y > MaxY)
        {
            MaxY = Y;
        }
        if (X < MinX)
        {
            MinX = X;
        }
        if (Y < MinY)
        {
            MinY = Y;
        }
    }

    std::cout << "MinX : " << MinX << " | MaxX : " << MaxX << " | MinY : " << MinY << " | MaxY : " << MaxY << std::endl;

    int OffsetX = MinX * -1;
    int OffsetY = MinY * -1;

    for (auto Painted : PaintedSurfaces)
    {
        std::vector<double> coords = split(Painted.first, ",");
        int X = coords[0] + OffsetX;
        int Y = coords[1] + OffsetY;
        Dictionary[Y][X] = Painted.second;
    }

    int Width = MaxX - MinX + 1;
    int Height = MaxY - MinY + 1;

    std::cout << "Width : " << Width << " | Height : " << Height << std::endl;

    std::vector<int> WidthIterator(Width);
    std::vector<int> HeightIterator(Height);
    std::iota(WidthIterator.begin(), WidthIterator.end(), 0);
    std::iota(HeightIterator.begin(), HeightIterator.end(), 0);

    std::ofstream WriteFile;
    WriteFile.open("image.txt", std::ofstream::out | std::ofstream::trunc);

    bool NextCharacter = false;
    for (auto LineNumber : HeightIterator)
    {
        for (auto ColumnNumber : WidthIterator)
        {
            if (Dictionary.find(LineNumber) != Dictionary.end())
            {
                if (Dictionary[LineNumber].find(ColumnNumber) != Dictionary[LineNumber].end())
                {
                    switch (Dictionary[LineNumber][ColumnNumber])
                    {
                        case BLACK_NUMBER:
                            WriteFile << DRAW_BLACK_CHARACTER;
                            break;
                        case WHITE_NUMBER:
                            WriteFile << DRAW_WHITE_CHARACTER;
                            break;
                        default:
                            std::cout << "UNEXPECTED NUMBER : " << Dictionary[LineNumber][ColumnNumber] << std::endl;
                            break;
                    }
                }
            }
        }
        WriteFile << '\n';
    }

    WriteFile.close();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time is : " << duration.count() << " Milliseconds" << std::endl;
}