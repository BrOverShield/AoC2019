#include <iostream>
#include <fstream>
#include <string>

int main ()
{
    std::string line;
    int answer = 0;
    std::vector<int> lines;
    //std::ifstream file("inputtest_2.txt");
    std::ifstream file("input_2.txt");
    if (file.is_open())
    {
        while(file.good())
        {
            int nb;
            file >> nb;
            lines.push_back(nb);
        }
        for (auto mass : lines)
        {
            do
            {
                float fCalculate = mass / 3;
                int iCalculate = (int)fCalculate;
                int fuel = iCalculate - 2;
                if (fuel > 0)
                {
                    answer += fuel;
                }
                std::cout << fuel << " | (" << answer << ")" << std::endl;
                mass = fuel;
            } while (mass > 0);
        }
        file.close();

        std::cout << "ANSWER : " << answer << std::endl;
    }
}