#include <iostream>
#include <vector>
#include <numeric> // iota
#include <string>

int main()
{
    int NumberA = 172851;
    int NumberB = 675869;
    int Difference = NumberB - NumberA;
    std::vector<int> Range(Difference);
    std::iota(Range.begin(), Range.end(), 1);
    int LastDigit;
    int Digit;
    bool HasDoubleDigit = false;
    bool NeverDecreases = true;
    int Result = 0;
    // std::vector<int> test;
    // test.push_back(122345);
    // test.push_back(111123);
    // test.push_back(135679);
    // test.push_back(111111);
    // test.push_back(223450);
    // test.push_back(123789);
    for (auto number : Range)
    {
        std::string sNumber = std::to_string(number);
        LastDigit = -1;
        HasDoubleDigit = false;
        NeverDecreases = true;
        for (auto cDigit : sNumber)
        {
            Digit = (int)cDigit;
            if (LastDigit != -1)
            {
                if (LastDigit == Digit)
                {
                    HasDoubleDigit = true;
                }
                if (LastDigit > Digit)
                {
                    NeverDecreases = false;
                }
            }
            LastDigit = Digit;
        }
        if (NeverDecreases && HasDoubleDigit)
        {
            Result++;
            std::cout << number << " | " << Result << std::endl;
        }
    }

    std::cout << "ANSWER : " << Result << std::endl;
}