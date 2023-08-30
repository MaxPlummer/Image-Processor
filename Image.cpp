#include <iostream>
#include "Image.h"
#include <vector>

Image::Image(char _idLength, char _colorMapType, char _dataTypeCode, short _colorMapOrigin, short _colorMapLength,
             char _colorMapDepth, short _xOrigin, short _yOrigin, short _width, short _height, char _bitsPerPixel,
             char _imageDescriptor)
{
    idLength = _idLength;
    colorMapType = _colorMapType;
    dataTypeCode = _dataTypeCode;
    colorMapOrigin = _colorMapOrigin;
    colorMapLength = _colorMapLength;
    colorMapDepth = _colorMapDepth;
    xOrigin = _xOrigin;
    yOrigin = _yOrigin;
    width = _width;
    height = _height;
    bitsPerPixel = _bitsPerPixel;
    imageDescriptor = _imageDescriptor;
}

Image::Pixels::Pixels(unsigned char r, unsigned char g, unsigned char b)
{
    red = r;
    green = g;
    blue = b;
}

vector<Image::Pixels> &Image::GetPixelVector()
{
    return pixelsImage;
}
void Image::Multiply(vector<Pixels>& image1, vector<Pixels>& image2)
{
    for(unsigned int i = 0; i < image1.size(); i++)
    {
        float _r1 = (float)image1[i].red / 255;
        float _r2 = (float)image2[i].red / 255;
        float redProduct = (_r1 * _r2) * 255;
        redProduct += 0.5f;
        unsigned char red = (char)redProduct;
        float _g1 = (float)image1[i].green / 255;
        float _g2 = (float)image2[i].green / 255;
        float greenProduct = (_g1 * _g2) * 255;
        greenProduct += 0.5f;
        unsigned char green = (char)greenProduct;
        float _b1 = (float)image1[i].blue / 255;
        float _b2 = (float)image2[i].blue / 255;
        float blueProduct = (_b1 * _b2) * 255;
        blueProduct += 0.5f;
        unsigned char blue = (char)blueProduct;
        Image::Pixels currentPixel = Image::Pixels(red, green, blue);
        this -> pixelsImage.push_back(currentPixel);
    }
}
int Image::Clamp(int x, int y, int z) {
    if(x < y) {
        x = y;
    }
    else if (x > z) {
        x = z;
    }
    return x;
}
void Image::Screen(vector<Pixels> &image1, vector<Pixels> &image2) {
    for(unsigned int i = 0; i < image1.size(); i++) {
        float _r1 = (float)image1[i].red / 255;
        float _r2 = (float)image2[i].red / 255;
        float redProduct = 1 - ((1 - _r1) * (1 - _r2));
        redProduct *= 255;
        redProduct += 0.5f;
        unsigned char red = (char)redProduct;
        float _g1 = (float)image1[i].green / 255;
        float _g2 = (float)image2[i].green / 255;
        float greenProduct = 1 - ((1 - _g1) * (1 - _g2));
        greenProduct *= 255;
        greenProduct += 0.5f;
        unsigned char green = (char)greenProduct;
        float _b1 = (float)image1[i].blue / 255;
        float _b2 = (float)image2[i].blue / 255;
        float blueProduct = 1 - ((1 - _b1) * (1 - _b2));
        blueProduct *= 255;
        blueProduct += 0.5f;
        unsigned char blue = (char)blueProduct;
        Image::Pixels currentPixel = Image::Pixels(red, green, blue);
        this -> pixelsImage.push_back(currentPixel);
    }
}
void Image::Overlay(vector<Pixels> &image1, vector<Pixels> &image2) {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    for(unsigned int i = 0; i < image1.size(); i++) {
        //gets the new red value
        if(((float)image2[i].red / 255) <= 0.5) {
            float _r1 = (float)image1[i].red / 255;
            float _r2 = (float)image2[i].red / 255;
            float redProduct = 2 * ((_r1) * (_r2));
            redProduct *= 255;
            redProduct += 0.5f;
            red = (char)redProduct;
        }
        else {
            float _r1 = (float)image1[i].red / 255;
            float _r2 = (float)image2[i].red / 255;
            float redProduct = 1 - 2 * ((1 - _r1) * (1 - _r2));
            redProduct *= 255;
            redProduct += 0.5f;
            red = (char)redProduct;
        }
        if(((float)image2[i].green / 255) <= 0.5) {
            float _g1 = (float)image1[i].green / 255;
            float _g2 = (float)image2[i].green / 255;
            float greenProduct = 2 * ((_g1) * (_g2));
            greenProduct *= 255;
            greenProduct += 0.5f;
            green = (char)greenProduct;
        }
        else {
            float _g1 = (float)image1[i].green / 255;
            float _g2 = (float)image2[i].green / 255;
            float greenProduct = 1 - 2 * ((1 - _g1) * (1 - _g2));
            greenProduct *= 255;
            greenProduct += 0.5f;
            green = (char)greenProduct;
        }
        if(((float)image2[i].blue / 255) <= 0.5) {
            float _b1 = (float)image1[i].blue / 255;
            float _b2 = (float)image2[i].blue / 255;
            float blueProduct = 2 * ((_b1) * (_b2));
            blueProduct *= 255;
            blueProduct += 0.5f;
            blue = (char)blueProduct;
        }
        else {
            float blueGreen1 = (float)image1[i].blue / 255;
            float blueGreen2 = (float)image2[i].blue / 255;
            float blueProduct = 1 - 2 * ((1 - blueGreen1) * (1 - blueGreen2));
            blueProduct *= 255;
            blueProduct += 0.5f;
            blue = (char)blueProduct;
        }
        Image::Pixels currentPixel = Image::Pixels(red, green, blue);
        this->pixelsImage.push_back(currentPixel);
    }
}
void Image::Scale(vector<Pixels> &image1, string color, float scale) {
    if(color == "red") {
        for(auto & i : image1) {
            float temp = (float)i.red / 255;
            temp *= scale;
            temp *= 255;
            temp += 0.5f;
            int temp2 = int(temp);
            temp2 = Clamp(temp2, 0, 255);
            i.red = (char)temp2;
        }
    }
    else if(color == "green") {
        for(auto & i : image1) {
            float temp = (float)i.green / 255;
            temp *= scale;
            temp *= 255;
            temp += 0.5f;
            int temp2 = int(temp);
            temp2 = Clamp(temp2, 0, 255);
            i.green = (char)temp2;
        }
    }
    else if(color == "blue") {
        for(auto & i : image1) {
            float temp = (float)i.blue / 255;
            temp *= scale;
            temp *= 255;
            temp += 0.5f;
            int temp2 = int(temp);
            temp2 = Clamp(temp2, 0, 255);
            i.blue = (char)temp2;
        }
    }
}
void Image::CreateChannel(vector<Image>& images, string color) {
    if(color == "red") {
        for(unsigned int i = 0; i < images[0].GetPixelVector().size(); i++) {
            unsigned char r = (int)images[0].GetPixelVector()[i].red;
            unsigned char g = (int)images[0].GetPixelVector()[i].red;
            unsigned char b = (int)images[0].GetPixelVector()[i].red;
            Image::Pixels currentPixel = Image::Pixels(r, g, b);
            images[1].GetPixelVector().push_back(currentPixel);
        }
    }
    else if(color == "green") {
        for(unsigned int i = 0; i < images[0].GetPixelVector().size(); i++) {
            unsigned char r = (int)images[0].GetPixelVector()[i].green;
            unsigned char g = (int)images[0].GetPixelVector()[i].green;
            unsigned char b = (int)images[0].GetPixelVector()[i].green;
            Image::Pixels currentPixel = Image::Pixels(r, g, b);
            images[1].GetPixelVector().push_back(currentPixel);
        }
    }
    else if(color == "blue") {
        for(unsigned int i = 0; i < images[0].GetPixelVector().size(); i++) {
            unsigned char r = (int)images[0].GetPixelVector()[i].blue;
            unsigned char g = (int)images[0].GetPixelVector()[i].blue;
            unsigned char b = (int)images[0].GetPixelVector()[i].blue;
            Image::Pixels currentPixel = Image::Pixels(r, g, b);
            images[1].GetPixelVector().push_back(currentPixel);
        }
    }
}
void Image::CombineChannel(vector<Image> &images) {
    for(unsigned int i = 0; i < images[0].GetPixelVector().size(); i++) {
        unsigned char r = images[0].GetPixelVector()[i].red;
        unsigned char g = images[1].GetPixelVector()[i].green;
        unsigned char b = images[2].GetPixelVector()[i].blue;
        Image::Pixels currentPixel = Image::Pixels(r, g, b);
        images[3].GetPixelVector().push_back(currentPixel);
    }
}
void Image::Flip180Degrees(vector<Image> &images) {
    int index = (int)images[0].GetPixelVector().size();
    for(int i = index - 1; i >= 0; i--) {
        unsigned char r = images[0].GetPixelVector()[i].red;
        unsigned char g = images[0].GetPixelVector()[i].green;
        unsigned char b = images[0].GetPixelVector()[i].blue;
        Image::Pixels currentPixel = Image::Pixels(r, g, b);
        images[1].GetPixelVector().push_back(currentPixel);
    }
}
