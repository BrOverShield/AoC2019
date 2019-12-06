#include <iostream>
#include <fstream>
#include <vector>
#include <string> // to_string(), stoi()

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

int main()
{
    std::string input;
    std::vector<int> IntCodes;
    std::ifstream file("C:\\Users\\tmdud\\Documents\\GitHub\\AoC2019\\day05\\input.txt");
    int ID = 5;
    if (file.is_open())
    {
        while(file.good())
        {
            file >> input;
        }
        file.close();
    }
    IntCodes = split(input, ",");

    // for (auto IntCode : IntCodes)
    // {
    //     std::cout << IntCode << std::endl;
    // }

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
            
            switch(Code)
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
                    IntCodes[DestinationPointer] = ID;
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
                    std::cout << "TEST " << Target << std::endl;
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
    } while (! IsFinished);
}