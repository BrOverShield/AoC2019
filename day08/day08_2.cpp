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
    const char WHITE_CHARACTER = '#';
    const char BLACK_CHARACTER = ' ';

    const int BLACK_NUMBER = 0;
    const int WHITE_NUMBER = 1;
    const int TRANSPARENT_NUMBER = 2;

    std::vector<int> Input;
    std::vector<Layer> Image;
    char c;
    int i;
    int w;
    int h;
    

    int Width = 25;
    int Height = 6;
    // int Width = 2;
    // int Height = 2;
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
    
    std::ofstream WriteFile;
    WriteFile.open("image.txt", std::ofstream::out | std::ofstream::trunc);

    bool NextCharacter = false;
    for (auto LineNumber : HeightIterator)
    {
        for (auto ColumnNumber : WidthIterator)
        {
            NextCharacter = false;
            for (auto layer : Image)
            {
                if (layer.Lines[LineNumber][ColumnNumber] != TRANSPARENT_NUMBER)
                {
                    switch(layer.Lines[LineNumber][ColumnNumber])
                    {
                        case BLACK_NUMBER:
                            WriteFile << BLACK_CHARACTER;
                            break;
                        case WHITE_NUMBER:
                            WriteFile << WHITE_CHARACTER;
                            break;
                        default:
                            std::cout << "UNEXPECTED NUMBER : " << layer.Lines[LineNumber][ColumnNumber] << std::endl;
                            break;
                    }
                    NextCharacter = true;
                }
                if (NextCharacter)
                {
                    break;
                }
            }
        }
        WriteFile << '\n';
    }

    WriteFile.close();
    
}