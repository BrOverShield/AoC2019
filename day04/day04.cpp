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
    std::iota(Range.begin(), Range.end(), 172851);
    int LastDigit;
    int Digit;
    int ThirdDigit;
    bool HasDoubleDigit = false;
    int DoubleDigitNumber = -1;
    bool NeverDecreases = true;
    int Result = 0;
    // std::vector<int> test;
    // test.push_back(112233);
    // test.push_back(123444);
    // test.push_back(111122);
    for (auto number : Range)
    {
        std::string sNumber = std::to_string(number);
        LastDigit = -1;
        ThirdDigit = -1;
        HasDoubleDigit = false;
        NeverDecreases = true;
        DoubleDigitNumber = -1;
        for (auto cDigit : sNumber)
        {
            Digit = (int)cDigit;
            if (LastDigit != -1)
            {
                if (!HasDoubleDigit)
                {
                    if (Digit == LastDigit && LastDigit != ThirdDigit)
                    {
                        HasDoubleDigit = true;
                        DoubleDigitNumber = Digit;
                    }
                }
                else
                {
                    if (DoubleDigitNumber == Digit && Digit == ThirdDigit)
                    {
                        HasDoubleDigit = false;
                    }
                }
                
                
                if (LastDigit > Digit)
                {
                    NeverDecreases = false;
                }
            }
            ThirdDigit = LastDigit;
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