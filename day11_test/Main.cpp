#include "Main.h"

std::string coorToString(int RobotX, int RobotY)
{
    return std::to_string(RobotX) + "," + std::to_string(RobotY);
}

void paint(int Target, int& RobotX, int& RobotY, std::map<std::string, int>& PaintedSurfaces)
{
    std::string text = coorToString(RobotX, RobotY);
    PaintedSurfaces[text] = Target;
};

void moveRobot(int Target, int& RobotX, int& RobotY, int& RobotDirection)
{
    if (Target == TURN_LEFT_NUMBER)
    {
        RobotDirection++;
        if (RobotDirection > RIGHT_DIRECTION)
        {
            RobotDirection = UP_DIRECTION;
        }
    }
    else if (Target == TURN_RIGHT_NUMBER)
    {
        RobotDirection--;
        if (RobotDirection < UP_DIRECTION)
        {
            RobotDirection = RIGHT_DIRECTION;
        }
    }
    else
    {
        std::cout << "ERROR : Bad TURN COMMAND : " << Target << std::endl;
    }

    switch (RobotDirection)
    {
    case UP_DIRECTION:
        RobotX++;
        break;
    case DOWN_DIRECTION:
        RobotX--;
        break;
    case LEFT_DIRECTION:
        RobotY--;
        break;
    case RIGHT_DIRECTION:
        RobotY++;
        break;
    }
};

int getColour(int RobotX, int RobotY, std::map<std::string, int> PaintedSurfaces)
{
    std::string text = coorToString(RobotX, RobotY);
    auto it = PaintedSurfaces.find(text);
    if (it != PaintedSurfaces.end())
    {
        return it->second;
    }
    else
    {
        return BLACK_NUMBER;
    }
};

std::vector<double> split(std::string s, std::string delimiter)
{
    size_t pos = 0;
    std::string token;
    std::vector<double> Result;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        double nb = strtol(token.data(), nullptr, 10);
        Result.push_back(nb);
        s.erase(0, pos + delimiter.length());
    }
    double nb = strtol(s.data(), nullptr, 10);
    Result.push_back(nb);
    return Result;
}

std::vector<double> addMemory(std::vector<double> IntCodes, double Index)
{
    int amount = (Index + 1) - IntCodes.size();
    std::vector<double> Range(amount);
    std::iota(Range.begin(), Range.end(), 0);
    for (auto number : Range)
    {
        IntCodes.push_back(0);
    }
    return IntCodes;
};

int main()
{
	Part2();
}