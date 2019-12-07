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
};

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> Choices(5);
    std::iota(Choices.begin(), Choices.end(), 0);
    std::string input;
    std::vector<int> Phases;
    std::vector<int> IntCodes;
    std::vector<Configuration> Configurations;
    int Phase;
    int IntCode;
    int Amplifier = 0;
    char c;
    std::ifstream file("C:\\Users\\tmdud\\Documents\\GitHub\\AoC2019\\day07\\input.txt");
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

    for (auto Phases : Possibilities)
    {
        std::cout << Phases[0] << Phases[1] << Phases[2] << Phases[3] << Phases[4] << std::endl;
    }
    
    for (auto Phases : Possibilities)
    {
        Configuration config;
        Amplifier = 0;
        for (int i = 0; i < 5; i++)
        {
            bool FirstInput = true;
            int ProgressionPointer = 0;
            bool IsFinished = false;
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
            do
            {
                if (IntCodes[ProgressionPointer] != 99)
                {
                    int Result = 0;
                    OpCode = IntCodes[ProgressionPointer];
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
                        PointerA = IntCodes[ProgressionPointer + 1];
                        PointerB = IntCodes[ProgressionPointer + 2];
                        if (Param1Mode == 1)
                        {
                            NumberA = PointerA;
                        }
                        else
                        {
                            NumberA = IntCodes[PointerA];
                        }

                        if (Param2Mode == 1)
                        {
                            NumberB = PointerB;
                        }
                        else
                        {
                            NumberB = IntCodes[PointerB];
                        }
                        DestinationPointer = IntCodes[ProgressionPointer + 3];
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
                        else
                        {
                            NumberA = IntCodes[PointerA];
                        }

                        if (Param2Mode == 1)
                        {
                            NumberB = PointerB;
                        }
                        else
                        {
                            NumberB = IntCodes[PointerB];
                        }
                        DestinationPointer = IntCodes[ProgressionPointer + 3];
                        Result = NumberA * NumberB;
                        IntCodes[DestinationPointer] = Result;
                        ProgressionPointer += 4;
                        break;
                    case 3:
                        DestinationPointer = IntCodes[ProgressionPointer + 1];
                        if (FirstInput)
                        {
                            IntCodes[DestinationPointer] = Phases[i];
                            FirstInput = false;
                        }
                        else
                        {
                            IntCodes[DestinationPointer] = Amplifier;
                        }
                        ProgressionPointer += 2;
                        break;
                    case 4:
                        if (Param1Mode == 1)
                        {
                            Target = IntCodes[ProgressionPointer + 1];
                        }
                        else
                        {
                            TargetPointer = IntCodes[ProgressionPointer + 1];
                            Target = IntCodes[TargetPointer];
                        }

                        Amplifier = Target;
                        if (i == 4)
                        {
                            std::cout << Phases[0] << Phases[1] << Phases[2] << Phases[3] << Phases[4] << " | " << Target << std::endl;
                            config.Phases = Phases;
                            config.Amplifier = Target;
                            Configurations.push_back(config);
                        }
                        ProgressionPointer += 2;
                        break;
                    case 5:
                        if (Param1Mode == 1)
                        {
                            Target = IntCodes[ProgressionPointer + 1];
                        }
                        else
                        {
                            TargetPointer = IntCodes[ProgressionPointer + 1];
                            Target = IntCodes[TargetPointer];
                        }
                        if (Target != 0)
                        {
                            if (Param2Mode == 1)
                            {
                                ProgressionPointer = IntCodes[ProgressionPointer + 2];
                            }
                            else
                            {
                                TargetPointer = IntCodes[ProgressionPointer + 2];
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
                        else
                        {
                            TargetPointer = IntCodes[ProgressionPointer + 1];
                            Target = IntCodes[TargetPointer];
                        }
                        if (Target == 0)
                        {
                            if (Param2Mode == 1)
                            {
                                ProgressionPointer = IntCodes[ProgressionPointer + 2];
                            }
                            else
                            {
                                TargetPointer = IntCodes[ProgressionPointer + 2];
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
                        else
                        {
                            PointerA = IntCodes[ProgressionPointer + 1];
                            NumberA = IntCodes[PointerA];
                        }
                        if (Param2Mode == 1)
                        {
                            NumberB = IntCodes[ProgressionPointer + 2];
                        }
                        else
                        {
                            PointerB = IntCodes[ProgressionPointer + 2];
                            NumberB = IntCodes[PointerB];
                        }
                        DestinationPointer = IntCodes[ProgressionPointer + 3];
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
                        else
                        {
                            PointerA = IntCodes[ProgressionPointer + 1];
                            NumberA = IntCodes[PointerA];
                        }
                        if (Param2Mode == 1)
                        {
                            NumberB = IntCodes[ProgressionPointer + 2];
                        }
                        else
                        {
                            PointerB = IntCodes[ProgressionPointer + 2];
                            NumberB = IntCodes[PointerB];
                        }
                        DestinationPointer = IntCodes[ProgressionPointer + 3];
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
                    default:
                        std::cout << "ERROR : IntCodes[" << ProgressionPointer << "] = " << IntCodes[ProgressionPointer] << std::endl;
                    }
                }
                else
                {
                    IsFinished = true;
                }
            } while (!IsFinished);
        }
    }
    int max = 0;
    for (auto config : Configurations)
    {
        if (config.Amplifier > max)
        {
            max = config.Amplifier;
            Phases = config.Phases;
            std::cout << "NEW MAX : " << max << " | PHASES : " << Phases[0] << Phases[1] << Phases[2] << Phases[3] << Phases[4] << std::endl;
        }
    }

    std::cout << "ANSWER : " << max << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time is : " << duration.count() << " Milliseconds" << std::endl;
}