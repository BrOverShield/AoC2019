#include <iostream>
#include <fstream>
#include <chrono>

int main ()
{
    auto start = std::chrono::high_resolution_clock::now();
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

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time is : " << duration.count() << " Milliseconds" << std::endl;
}