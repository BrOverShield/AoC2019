#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <numeric> // atoi
#include <algorithm> // min_element

int main()
{
    std::vector<int> ForRange = {0,1,2};
    std::vector<char> CableADirections;
    std::vector<int> CableAAmount;
    std::vector<char> CableBDirections;
    std::vector<int> CableBAmount;
    std::vector<int> CrossingDistances;
    char c;
    int i;
    std::ifstream file("input.txt");
    if (file.is_open())
    {
        do
        {
            file >> c;
            CableADirections.push_back(c);
            file >> i;
            CableAAmount.push_back(i);
            file >> c;
        } while (c == ',');

        bool first = true;

        do
        {
            if (!first)
            {
                file >> c;
            }
            first = false;
            CableBDirections.push_back(c);
            file >> i;
            CableBAmount.push_back(i);
            //std::cout << c << i << std::endl;
            file >> c;
        } while (file.good());

    }
        
    std::map<int, std::map<int, std::map<char, int>>> map;

    int PointerX = 0;
    int PointerY = 0;
    int Index = 0;
    map[0][0]['o'] = PointerX + PointerY;
    for (auto direction : CableADirections)
    {
        std::vector<int> Range(CableAAmount[Index]);
        std::iota(Range.begin(), Range.end(), 1);
        if (direction == 'U')
        {
            for (auto cell : Range)
            {
                map[PointerX][PointerY + cell]['A'] = abs(PointerX) + abs(PointerY + cell);
            }
            PointerY += CableAAmount[Index];
        }
        else if (direction == 'D')
        {
            for (auto cell : Range)
            {
                map[PointerX][PointerY - cell]['A'] = abs(PointerX) + abs(PointerY - cell);
            }
            PointerY -= CableAAmount[Index];
        }
        else if (direction == 'R')
        {
            for (auto cell : Range)
            {
                map[PointerX + cell][PointerY]['A'] = abs(PointerX + cell) + abs(PointerY);
            }
            PointerX += CableAAmount[Index];
        }
        else if (direction == 'L')
        {
            for (auto cell : Range)
            {
                map[PointerX - cell][PointerY]['A'] = abs(PointerX - cell) + abs(PointerY);
            }
            PointerX -= CableAAmount[Index];
        }
        Index ++;
    }

    PointerX = 0;
    PointerY = 0;
    Index = 0;
    for (auto direction : CableBDirections)
    {
        std::vector<int> Range(CableBAmount[Index]);
        std::iota(Range.begin(), Range.end(), 1);
        if (direction == 'U')
        {
            for (auto cell : Range)
            {
                PointerY++;
                if (map.count(PointerX))
                {
                    if (map[PointerX].count(PointerY))
                    {
                        if (map[PointerX][PointerY].count('A'))
                        {
                            std::cout << "X : " << PointerX << " | Y : " << PointerY << " | distance : " << map[PointerX][PointerY]['A'] << std::endl;
                            CrossingDistances.push_back(map[PointerX][PointerY]['A']);
                        }
                    }
                }
            }
        }
        else if (direction == 'D')
        {
            for (auto cell : Range)
            {
                PointerY--;
                if (map.count(PointerX))
                {
                    if (map[PointerX].count(PointerY))
                    {
                        if (map[PointerX][PointerY].count('A'))
                        {
                            std::cout << "X : " << PointerX << " | Y : " << PointerY << " | distance : " << map[PointerX][PointerY]['A'] << std::endl;
                            CrossingDistances.push_back(map[PointerX][PointerY]['A']);
                        }
                    }
                }
            }
        }
        else if (direction == 'R')
        {
            for (auto cell : Range)
            {
                PointerX++;
                if (map.count(PointerX))
                {
                    if (map[PointerX].count(PointerY))
                    {
                        if (map[PointerX][PointerY].count('A'))
                        {
                            std::cout << "X : " << PointerX << " | Y : " << PointerY << " | distance : " << map[PointerX][PointerY]['A'] << std::endl;
                            CrossingDistances.push_back(map[PointerX][PointerY]['A']);
                        }
                    }
                }
            }
        }
        else if (direction == 'L')
        {
            for (auto cell : Range)
            {
                PointerX--;
                if (map.count(PointerX))
                {
                    if (map[PointerX].count(PointerY))
                    {
                        if (map[PointerX][PointerY].count('A'))
                        {
                            std::cout << "X : " << PointerX << " | Y : " << PointerY << " | distance : " << map[PointerX][PointerY]['A'] << std::endl;
                            CrossingDistances.push_back(map[PointerX][PointerY]['A']);
                        }
                    }
                }
            }
        }
        Index ++;
    }
    auto min_value = *std::min_element(CrossingDistances.begin(),CrossingDistances.end());

    std::cout << "ANSWER : " << min_value << std::endl;

    // for(auto &x : map)
    // {
    //     for(auto &y : x.second)
    //     {
    //         for(auto& values : y.second)
    //         {
    //             std::cout << "x:" << x.first << " | y:" << y.first << " | []:" << values.first << " | d:" << values.second << std::endl;
    //         }
    //     }
    // }
}