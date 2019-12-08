#include <iostream>
#include <fstream>
#include <vector>
#include <numeric> // iota

class Layer
{
    public:
        int Zeros = 0;
        int Ones = 0;
        int Twos = 0;
        std::vector<std::vector<int>> Lines;
};

int ctoi (char c)
{
    return (int)c - '0';
};

int main()
{
    std::vector<int> Input;
    std::vector<Layer> Image;
    char c;
    int i;
    int w;
    int h;
    

    int Width = 25;
    int Height = 6;
    // std::ifstream file("C:\\Users\\tmdud\\Documents\\GitHub\\AoC2019\\day08\\input.txt");
    std::ifstream file("input.txt");
    if (file.is_open())
    {
        while(file.good())
        {
            file >> c;
            i = ctoi(c);
            Input.push_back(i);
        }
        file.close();
    }

    int PixelsPerLayer = Width * Height;
    int NumberOfLayers = Input.size() / PixelsPerLayer;

    std::vector<int> WidthIterator(Width);
    std::vector<int> HeightIterator(Height);
    std::vector<int> LayerIterator(NumberOfLayers);

    std::iota(WidthIterator.begin(), WidthIterator.end(), 0);
    std::iota(HeightIterator.begin(), HeightIterator.end(), 0);
    std::iota(LayerIterator.begin(), LayerIterator.end(), 0);

    i = 0;
    for (auto LayerNumber : LayerIterator)
    {
        Layer layer;
        for (auto LineNumber : HeightIterator)
        {
            std::vector<int> Line;
            for (auto ColumnNumber : WidthIterator)
            {
                Line.push_back(Input[i]);
                switch(Input[i])
                {
                    case 0:
                        layer.Zeros++;
                        break;
                    case 1:
                        layer.Ones++;
                        break;
                    case 2:
                        layer.Twos++;
                        break;
                    default:
                        std::cout << "UNEXPECTED VALUE : " << Input[i] << std::endl;
                        break;
                }
                i++;
            }
            layer.Lines.push_back(Line);
        }
        Image.push_back(layer);
    }

    int MinZeros = PixelsPerLayer;
    int TargetOnes = -1;
    int TargetTwos = -1;
    for (auto layer : Image)
    {
        if (layer.Zeros < MinZeros)
        {
            MinZeros = layer.Zeros;
            TargetOnes = layer.Ones;
            TargetTwos = layer.Twos;
            std::cout << "NEW MIN : " << MinZeros << " | ONES : " << TargetOnes << " | TWOS : " << TargetTwos << std::endl;
        }
    }

    std::cout << "ANSWER : " << TargetOnes * TargetTwos << std::endl;
    
    
}