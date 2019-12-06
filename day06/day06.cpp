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

    int Result = 0;
    int counter = 0;
    std::string EndCondition = "COM";
    for (auto Name : NameList)
    {
        counter = 0;
        
        while (Name != EndCondition)
        {
            Name = map.find(Name)->second;
            counter ++;
        }
        Result += counter;
        std::cout << counter << " | " << Result << std::endl;  
    }

    std::cout << "ANSWER : " << Result << std::endl;  
}