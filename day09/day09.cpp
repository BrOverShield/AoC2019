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

typedef std::numeric_limits< double > dbl;

std::vector<double> split(std::string s, std::string delimiter)
{
    size_t pos = 0;
    std::string token;
    std::vector<double> Result;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        double nb = strtol(token.data(), nullptr, 10);
        Result.push_back(nb);
        s.erase(0, pos + delimiter.length());
    }
    double nb = strtol(s.data(), nullptr, 10);
    Result.push_back(nb);
    return Result;
}

std::vector<double> addMemory(std::vector<double> IntCodes, double Index)
{
    int amount = (Index + 1) - IntCodes.size();
    std::vector<double> Range(amount);
    std::iota(Range.begin(), Range.end(), 0);
    for (auto number : Range)
    {
        IntCodes.push_back(0); 
    }
    return IntCodes;
};

int main()
{
    std::cout.precision(dbl::max_digits10);
    auto start = std::chrono::high_resolution_clock::now();
    std::string input;
    std::vector<double> IntCodes;
    double IntCode;
    char c;
    // std::ifstream file("C:\\Users\\tmdud\\Documents\\GitHub\\AoC2019\\day07\\input.txt");
    std::ifstream file("C:\\Users\\PPoucH\\Documents\\GitHub\\AoC2019\\day09\\inputtest1.txt");
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
    double RelativeBase = 0;
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
                if (PointerA + RelativeBase > IntCodes.size())
                {
                    IntCodes = addMemory(IntCodes, PointerA + RelativeBase);
                }
                if (PointerB + RelativeBase > IntCodes.size())
                {
                    IntCodes = addMemory(IntCodes, PointerB + RelativeBase);
                }
                if (Param1Mode == 1)
                {
                    NumberA = PointerA;
                }
                else if (Param1Mode == 2)
                {
                    NumberA = IntCodes[PointerA + RelativeBase];
                }
                else
                {
                    NumberA = IntCodes[PointerA];
                }

                if (Param2Mode == 1)
                {
                    NumberB = PointerB;
                }
                else if (Param2Mode == 2)
                {
                    NumberB = IntCodes[RelativeBase + PointerB];
                }
                else
                {
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
                if (PointerA + RelativeBase > IntCodes.size())
                {
                    IntCodes = addMemory(IntCodes, PointerA + RelativeBase);
                }
                if (PointerB + RelativeBase > IntCodes.size())
                {
                    IntCodes = addMemory(IntCodes, PointerB + RelativeBase);
                }
                if (Param1Mode == 1)
                {
                    NumberA = PointerA;
                }
                else if (Param1Mode == 2)
                {
                    NumberA = IntCodes[RelativeBase + PointerA];
                }
                else
                {
                    NumberA = IntCodes[PointerA];
                }

                if (Param2Mode == 1)
                {
                    NumberB = PointerB;
                }
                else if (Param2Mode == 2)
                {
                    NumberB = IntCodes[RelativeBase + PointerB];
                }
                else
                {
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

                std::cout << Target << std::endl;

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

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time is : " << duration.count() << " Milliseconds" << std::endl;
}