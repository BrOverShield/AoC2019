#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::string input;
    std::vector<int> IntCodes;
    std::ifstream file("input.txt");
    if (file.is_open())
    {
        while(file.good())
        {
            file >> input;
        }
        file.close();
    }
    IntCodes = split(input, ",");
    
    IntCodes[1] = 12;
    IntCodes[2] = 2;

    // for (auto IntCode : IntCodes)
    // {
    //     std::cout << IntCode << std::endl;
    // }

    int ProgressionPointer = 0;
    bool IsFinished = false;
    do
    {
        if (IntCodes[ProgressionPointer] != 99)
        {
            int PointerA = IntCodes[ProgressionPointer + 1];
            int PointerB = IntCodes[ProgressionPointer + 2];
            int NumberA = IntCodes[PointerA];
            int NumberB = IntCodes[PointerB];
            int DestinationPointer = IntCodes[ProgressionPointer + 3];
            int Result = 0;
            switch(IntCodes[ProgressionPointer])
            {
                case 1:
                    Result = NumberA + NumberB;
                    break;
                case 2:
                    Result = NumberA * NumberB;
                    break;
                default:
                    std::cout << "ERROR : IntCodes[" << ProgressionPointer << "] = " << IntCodes[ProgressionPointer] << std::endl;
            }
            IntCodes[DestinationPointer] = Result;
        }
        else
        {
            IsFinished = true;
        }
        ProgressionPointer += 4;
    } while (! IsFinished);
    
    std::cout << "ANSWER : " << IntCodes[0] << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time is : " << duration.count() << " Milliseconds" << std::endl;
}