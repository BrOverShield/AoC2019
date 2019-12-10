#include <iostream>
#include <fstream>
#include <vector>
#include <string> // to_string(), stoi()
#include <map>
#include <numeric> // iota
#include <chrono>

std::vector<int> split(std::string s, std::string delimiter)
{
    size_t pos = 0;
    std::string token;
    std::vector<int> Result;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        int nb = strtol(token.data(), nullptr, 10);
        Result.push_back(nb);
        s.erase(0, pos + delimiter.length());
    }
    int nb = strtol(s.data(), nullptr, 10);
    Result.push_back(nb);
    return Result;
}

class Configuration
{
    public:
        std::vector<int> Phases;
        int Amplifier;
        int Loops;
};

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> Choices(5);
    std::iota(Choices.begin(), Choices.end(), 5);
    std::string input;
    std::vector<int> Phases;
    std::vector<int> IntCodes;
    std::vector<Configuration> Configurations;
    int Phase;
    int IntCode;
    int Amplifier = 0;
    char c;
    //std::ifstream file("C:\\Users\\tmdud\\Documents\\GitHub\\AoC2019\\day07\\input.txt");
    std::ifstream file("input.txt");
    std::ifstream PhaseFile("C:\\Users\\tmdud\\Documents\\GitHub\\AoC2019\\day07\\phasetest1.txt");
    int ID = 0;
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

    if (PhaseFile.is_open())
    {
        while (PhaseFile.good())
        {
            PhaseFile >> input;
        }
        PhaseFile.close();
    }

    Phases = split(input, ",");
    std::vector<std::vector<int>> Possibilities;

    for (auto A : Choices)
    {
        for (auto B : Choices)
        {
            for (auto C : Choices)
            {
                for (auto D : Choices)
                {
                    for (auto E : Choices)
                    {
                        if (A != B && A != C && A != D && A != E && B != C && B != D && B != E && C != D && C != E && D != E)
                        {
                            int PhaseArray[] = {A, B, C, D, E};
                            Phases.assign(PhaseArray, PhaseArray + 5);
                            Possibilities.push_back(Phases);
                        }
                    }
                }
            }
        }
    }

    // for (auto IntCode : IntCodes)
    // {
    //     // std::cout << Phases[0] << Phases[1] << Phases[2] << Phases[3] << Phases[4] << std::endl;
    //     std::cout << IntCode << std::endl;
    // }

    for (auto Phases : Possibilities)
    {
        std::vector<std::vector<int>> Memory = {IntCodes, IntCodes, IntCodes, IntCodes, IntCodes};
        Configuration config;
        config.Phases = Phases;
        Amplifier = 0;
        std::vector<int> ProgressionPointers = {0,0,0,0,0};
        bool IsFinished = false;
        bool IsDone = false;
        int PointerA;
        int PointerB;
        int NumberA;
        int NumberB;
        int DestinationPointer;
        int TargetPointer;
        int OpCode;
        int Code;
        int Param1Mode;
        int Param2Mode;
        int Param3Mode;
        char c;
        int Target;
        std::string FilledOpCode;
        std::string sCode;
        std::string sOpCode;
        int Loops = 0;
        while (!IsDone)
        {
            int i = 0;
            Loops++;
            
            while ( i < 5)
            {
                IsFinished = false;
                bool IsDataSent = false;
                do
                {
                    if (Memory[i][ProgressionPointers[i]] != 99)
                    {
                        int Result = 0;
                        OpCode = Memory[i][ProgressionPointers[i]];
                        sOpCode = std::to_string(OpCode);
                        Param1Mode = 0;
                        Param2Mode = 0;
                        Param3Mode = 0;
                        if (sOpCode.length() > 2) // if the number is at least 4 digits
                        {
                            FilledOpCode = std::string();
                            for (int i = sOpCode.length(); i < 5; i++)
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

                        switch (Code)
                        {
                        case 1:
                            PointerA = Memory[i][ProgressionPointers[i] + 1];
                            PointerB = Memory[i][ProgressionPointers[i] + 2];
                            if (Param1Mode == 1)
                            {
                                NumberA = PointerA;
                            }
                            else
                            {
                                NumberA = Memory[i][PointerA];
                            }

                            if (Param2Mode == 1)
                            {
                                NumberB = PointerB;
                            }
                            else
                            {
                                NumberB = Memory[i][PointerB];
                            }
                            DestinationPointer = Memory[i][ProgressionPointers[i] + 3];
                            Result = NumberA + NumberB;
                            Memory[i][DestinationPointer] = Result;
                            ProgressionPointers[i] += 4;
                            break;
                        case 2:
                            PointerA = Memory[i][ProgressionPointers[i] + 1];
                            PointerB = Memory[i][ProgressionPointers[i] + 2];
                            if (Param1Mode == 1)
                            {
                                NumberA = PointerA;
                            }
                            else
                            {
                                NumberA = Memory[i][PointerA];
                            }

                            if (Param2Mode == 1)
                            {
                                NumberB = PointerB;
                            }
                            else
                            {
                                NumberB = Memory[i][PointerB];
                            }
                            DestinationPointer = Memory[i][ProgressionPointers[i] + 3];
                            Result = NumberA * NumberB;
                            Memory[i][DestinationPointer] = Result;
                            ProgressionPointers[i] += 4;
                            break;
                        case 3:
                            DestinationPointer = Memory[i][ProgressionPointers[i] + 1];
                            if (ProgressionPointers[i] == 0)
                            {
                                Memory[i][DestinationPointer] = Phases[i];
                            }
                            else
                            {
                                Memory[i][DestinationPointer] = Amplifier;
                            }
                            ProgressionPointers[i] += 2;
                            break;
                        case 4:
                            if (Param1Mode == 1)
                            {
                                Target = Memory[i][ProgressionPointers[i] + 1];
                            }
                            else
                            {
                                TargetPointer = Memory[i][ProgressionPointers[i] + 1];
                                Target = Memory[i][TargetPointer];
                            }

                            Amplifier = Target;
                            config.Amplifier = Target;
                            IsDataSent = true;
                            // std::cout << i << " | " << Phases[0] << Phases[1] << Phases[2] << Phases[3] << Phases[4] << " | " << Target << std::endl;
                            ProgressionPointers[i] += 2;
                            break;
                        case 5:
                            if (Param1Mode == 1)
                            {
                                Target = Memory[i][ProgressionPointers[i] + 1];
                            }
                            else
                            {
                                TargetPointer = Memory[i][ProgressionPointers[i] + 1];
                                Target = Memory[i][TargetPointer];
                            }
                            if (Target != 0)
                            {
                                if (Param2Mode == 1)
                                {
                                    ProgressionPointers[i] = Memory[i][ProgressionPointers[i] + 2];
                                }
                                else
                                {
                                    TargetPointer = Memory[i][ProgressionPointers[i] + 2];
                                    ProgressionPointers[i] = Memory[i][TargetPointer];
                                }
                            }
                            else
                            {
                                ProgressionPointers[i] += 3;
                            }
                            break;
                        case 6:
                            if (Param1Mode == 1)
                            {
                                Target = Memory[i][ProgressionPointers[i] + 1];
                            }
                            else
                            {
                                TargetPointer = Memory[i][ProgressionPointers[i] + 1];
                                Target = Memory[i][TargetPointer];
                            }
                            if (Target == 0)
                            {
                                if (Param2Mode == 1)
                                {
                                    ProgressionPointers[i] = Memory[i][ProgressionPointers[i] + 2];
                                }
                                else
                                {
                                    TargetPointer = Memory[i][ProgressionPointers[i] + 2];
                                    ProgressionPointers[i] = Memory[i][TargetPointer];
                                }
                            }
                            else
                            {
                                ProgressionPointers[i] += 3;
                            }

                            break;
                        case 7:
                            if (Param1Mode == 1)
                            {
                                NumberA = Memory[i][ProgressionPointers[i] + 1];
                            }
                            else
                            {
                                PointerA = Memory[i][ProgressionPointers[i] + 1];
                                NumberA = Memory[i][PointerA];
                            }
                            if (Param2Mode == 1)
                            {
                                NumberB = Memory[i][ProgressionPointers[i] + 2];
                            }
                            else
                            {
                                PointerB = Memory[i][ProgressionPointers[i] + 2];
                                NumberB = Memory[i][PointerB];
                            }
                            DestinationPointer = Memory[i][ProgressionPointers[i] + 3];
                            if (NumberA < NumberB)
                            {
                                Memory[i][DestinationPointer] = 1;
                            }
                            else
                            {
                                Memory[i][DestinationPointer] = 0;
                            }
                            ProgressionPointers[i] += 4;
                            break;
                        case 8:
                            if (Param1Mode == 1)
                            {
                                NumberA = Memory[i][ProgressionPointers[i] + 1];
                            }
                            else
                            {
                                PointerA = Memory[i][ProgressionPointers[i] + 1];
                                NumberA = Memory[i][PointerA];
                            }
                            if (Param2Mode == 1)
                            {
                                NumberB = Memory[i][ProgressionPointers[i] + 2];
                            }
                            else
                            {
                                PointerB = Memory[i][ProgressionPointers[i] + 2];
                                NumberB = Memory[i][PointerB];
                            }
                            DestinationPointer = Memory[i][ProgressionPointers[i] + 3];
                            if (NumberA == NumberB)
                            {
                                Memory[i][DestinationPointer] = 1;
                            }
                            else
                            {
                                Memory[i][DestinationPointer] = 0;
                            }
                            ProgressionPointers[i] += 4;
                            break;
                        default:
                            std::cout << "ERROR : Memory[i][" << ProgressionPointers[i] << "] = " << Memory[i][ProgressionPointers[i]] << std::endl;
                        }
                    }
                    else
                    {
                        IsFinished = true;
                        if (i == 4)
                        {
                            IsDone = true;
                        }
                    }
                    if (IsDataSent)
                    {
                        break;
                    }
                } while (!IsFinished);
                i++;
            }
        }
        config.Loops = Loops;
        Configurations.push_back(config);
    }
    int max = 0;
    int maxLoops = 0;
    int Loop;
    for (auto config : Configurations)
    {
        if (config.Amplifier > max)
        {
            max = config.Amplifier;
            Phases = config.Phases;
            // Loop = config.Loops;
            // std::cout << "NEW MAX : " << max << " | PHASES : " << Phases[0] << Phases[1] << Phases[2] << Phases[3] << Phases[4] << std::endl;
        }
        // if (config.Loops > maxLoops)
        // {
        //     maxLoops = config.Loops;
        // }
    }

    std::cout << "ANSWER : " << max << " | " << Loop << std::endl;
    // std::cout << "MAX LOOP : " << maxLoops << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time is : " << duration.count() << " Milliseconds" << std::endl;
}