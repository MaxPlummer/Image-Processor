#ifndef MAXPROJECT2_IMAGE_H
#define MAXPROJECT2_IMAGE_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Image
{
    struct Pixels
    {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        Pixels(unsigned char r, unsigned char g, unsigned char b);

    };
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
    vector<Pixels> pixelsImage;

    Image(char _idLength, char _colorMapType, char _dataTypeCode, short _colorMapOrigin, short _colorMapLength,
          char _colorMapDepth, short _xOrigin, short _yOrigin, short _width, short _height, char _bitsPerPixel,
          char _imageDescriptor);

    vector<Pixels>& GetPixelVector();

    void Multiply(vector<Pixels>& image1, vector<Pixels>& image2);
    int Clamp(int a, int b, int c);
    void Screen(vector<Pixels>& image1, vector<Pixels>& image2);
    void Overlay(vector<Pixels>& image1, vector<Pixels>& image2);
    void Scale(vector<Pixels>& image1, string color, float scale);
    void CreateChannel(vector<Image>& images, string color);
    void CombineChannel(vector<Image>& images);
    void Flip180Degrees(vector<Image>& images);
};

#endif //MAXPROJECT2_IMAGE_H
