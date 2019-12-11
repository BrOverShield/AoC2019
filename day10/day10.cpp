#include <iostream>
#include <fstream>
#include <vector>
#include <string> // to_string(), stoi()
#include <map>
#include <numeric> // iota
#include <chrono>
#include <math.h> // pow()
#include <algorithm> // vector find()

class Asteroid
{
    public:
        int Score;
        int X;
        int Y;
        std::vector<double> Angles;
};

void polar(int x, int y, float& r, double& theta)
{
    if (x == 0)
    {
        r = abs(y);
        if (y < 0)
        {
            theta = 270.0f;
        }
        else
        {
            theta = 90.0f;
        }
        
    }
    else if (y == 0)
    {
        r = abs(x);
        if (x < 0)
        {
            theta = 180.0f;
        }
        else
        {
            theta = 0.0f;
        }
    }
    else
    {
        const float toDegrees = 180.0/3.141593;
        r = sqrt((pow(x,2))+(pow(y,2)));
        double value = (double)abs(y)/abs(x);
        theta = atan(value) * toDegrees;
        if (x < 0 && y > 0)
        {
            theta = 180 - theta;
        }
        if (x < 0 && y < 0)
        {
            theta = 180 + theta;
        }
        if (x > 0 && y < 0)
        {
            theta = 360 - theta;
        }
    }
    return;
};

int main ()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::string> Lines;
    std::string Line;
    std::ifstream InputFile("C:\\Users\\tmdud\\Documents\\GitHub\\AoC2019\\day10\\input.txt");

    if (InputFile.is_open())
    {
        while (InputFile.good())
        {
            InputFile >> Line;
            Lines.push_back(Line);
        }
        InputFile.close();
    }

    int Width = Lines[0].size();
    int Height = Lines.size();
    std::vector<int> RangeX(Width);
    std::vector<int> RangeY(Height);
    std::vector<Asteroid> map;

    std::iota(RangeX.begin(), RangeX.end(), 0);
    std::iota(RangeY.begin(), RangeY.end(), 0);
    char c;

    for (auto CoordinateY : RangeY)
    {
        for(auto CoordinateX : RangeX)
        {
            c = Lines[CoordinateY].data()[CoordinateX];
            if (c == '#')
            {
                Asteroid asteroid;
                asteroid.Score = 0;
                asteroid.X = CoordinateX;
                asteroid.Y = CoordinateY;
                map.push_back(asteroid);
            }
        }
    }

    double Angle;
    int X;
    int Y;
    float Distance;
    std::vector<Asteroid> Results = map;
    int i = 0;

    for(auto SourceAsteroid : map)
    {
        for (auto TargetAsteroid : map)
        {
            if (SourceAsteroid.X != TargetAsteroid.X || SourceAsteroid.Y != TargetAsteroid.Y)
            {
                X = (TargetAsteroid.X - SourceAsteroid.X);
                Y = (TargetAsteroid.Y - SourceAsteroid.Y);

                polar(X, Y, Distance, Angle);
                if (find(SourceAsteroid.Angles.begin(), SourceAsteroid.Angles.end(), Angle) == SourceAsteroid.Angles.end())
                {
                    Results[i].Score++;
                    SourceAsteroid.Angles.push_back(Angle);
                }
            }
        }
        i++;
    }
    Asteroid BestAsteroid;
    BestAsteroid.Score=0;
    for (auto result : Results)
    {
        if (result.Score > BestAsteroid.Score)
        {
            BestAsteroid = result;
        }
        //std::cout << "X " << result.X << " | Y : " << result.Y << " | " << result.Score << std::endl;
    }

    std::cout << "ANSWER -> X " << BestAsteroid.X << " | Y : " << BestAsteroid.Y << " | " << BestAsteroid.Score << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time is : " << duration.count() << " Milliseconds" << std::endl;
}