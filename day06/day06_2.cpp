#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm> // vector find

int main()
{
    std::vector<std::string> input;
    std::ifstream file("C:\\Users\\tmdud\\Documents\\GitHub\\AoC2019\\day06\\input.txt");
    std::string string;
    std::map<std::string, std::string> map; // parent, name
    std::string Parent;
    std::string Name;
    std::vector<std::string> NameList;
    if (file.is_open())
    {
        while (file.good())
        {
            file >> string;
            input.push_back(string);
        }
        file.close();
    }

    for (auto orbit : input)
    {
        Parent = orbit.substr(0, 3);
        Name = orbit.substr(4, 3);
        map[Name] = Parent;
        if (std::find(NameList.begin(), NameList.end(),Name)==NameList.end())
        {
            NameList.push_back(Name);
        }
        if (std::find(NameList.begin(), NameList.end(),Parent)==NameList.end())
        {
            NameList.push_back(Parent);
        }
        
    }

    for (auto Name : NameList)
    {
        if (map.find(Name) == map.end())
        {
            map[Name] = "COM";
        }
    }

    std::vector<std::string> SantaMap;
    std::vector<std::string> YouMap;
    std::string EndCondition = "COM";
    Name = std::string() + "YOU";
    while (Name != EndCondition)
    {
        Name = map.find(Name)->second;
        YouMap.push_back(Name);
    }
    Name = std::string() + "SAN";
    while (Name != EndCondition)
    {
        Name = map.find(Name)->second;
        SantaMap.push_back(Name);
    }

    bool IsFinished = false;
    std::string junction = "COM";
    while (! IsFinished)
    {
        for (auto YouOrbit : YouMap)
        {
            for (auto SantaOrbit : SantaMap)
            {
                if (YouOrbit == SantaOrbit)
                {
                    IsFinished = true;
                    junction = YouOrbit;
                }
                if (IsFinished)
                {
                    break;
                }
            }
            if (IsFinished)
            {
                break;
            }
        }
    }

    int Result = 0;
    int YouCounter = 0;
    Name = "YOU";
    while (Name != junction)
    {
        Name = map.find(Name)->second;
        YouCounter ++;
    }
    YouCounter--;
    
    std::cout << "you : " << YouCounter << std::endl;

    int SantaCounter = 0;
    Name = "SAN";
    while (Name != junction)
    {
        Name = map.find(Name)->second;
        SantaCounter ++;
    }
    SantaCounter--;
    
    std::cout << "santa : " << SantaCounter << std::endl;

    Result = YouCounter + SantaCounter;

    std::cout << "ANSWER : " << Result << std::endl;  
}