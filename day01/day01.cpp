#include <iostream>
#include <fstream>

int main ()
{
    char line[32];
    int answer = 0;
    //std::vector<string> lines;
    //std::ifstream file("inputtest.txt");
    std::ifstream file("input.txt");
    if (file.is_open())
    {
        while (file.getline(line, 256, '\n'))
        {
            int mass = strtol(line, nullptr, 10);
            float fCalculate = mass / 3;
            int iCalculate = (int)fCalculate;
            int fuel = iCalculate - 2;
            answer += fuel;
            std::cout << fuel << " | (" << answer << ")" << std::endl;

        }
        file.close();

        std::cout << "ANSWER : " << answer << std::endl;
    }

    
}