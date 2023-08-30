#include <iostream>
#include "Image.h"
#include <vector>
#include <fstream>

void ReadImage(string filePath, vector<Image>& images, int index) {
    ifstream inFile(filePath, ios_base::binary);

    char idLength;
    inFile.read((char *) &idLength, sizeof(idLength));
    char colorMapType;
    inFile.read((char *) &colorMapType, sizeof(colorMapType));
    char dataTypeCode;
    inFile.read((char *) &dataTypeCode, sizeof(dataTypeCode));
    short colorMapOrigin;
    inFile.read((char *) &colorMapOrigin, sizeof(colorMapOrigin));
    short colorMapLength;
    inFile.read((char *) &colorMapLength, sizeof(colorMapLength));
    char colorMapDepth;
    inFile.read((char *) &colorMapDepth, sizeof(colorMapDepth));
    short xOrigin;
    inFile.read((char *) &xOrigin, sizeof(xOrigin));
    short yOrigin;
    inFile.read((char *) &yOrigin, sizeof(yOrigin));
    short width;
    inFile.read((char *) &width, sizeof(width));
    short height;
    inFile.read((char *) &height, sizeof(height));
    char bitsPerPixel;
    inFile.read((char *) &bitsPerPixel, sizeof(bitsPerPixel));
    char imageDescriptor;
    inFile.read((char *) &imageDescriptor, sizeof(imageDescriptor));

    Image image(idLength, colorMapType, dataTypeCode, colorMapOrigin, colorMapLength, colorMapDepth, xOrigin,
                yOrigin, width, height, bitsPerPixel, imageDescriptor);
    images.push_back(image);

    int numOfPixels = width * height;

    for(unsigned int n = 0; n < numOfPixels; n++) {
        unsigned char blue;
        inFile.read((char*) &blue, sizeof(blue));

        unsigned char green;
        inFile.read((char*) &green, sizeof(green));

        unsigned char red;
        inFile.read((char*) &red, sizeof(red));

        Image::Pixels currentPixel = Image::Pixels(red, green, blue);
        images[index].GetPixelVector().push_back(currentPixel);
    }
}

Image ReadTracked(string filePath)
{
    ifstream inFile(filePath, ios_base::binary);

    char idLength;
    inFile.read((char *) &idLength, sizeof(idLength));
    char colorMapType;
    inFile.read((char *) &colorMapType, sizeof(colorMapType));
    char dataTypeCode;
    inFile.read((char *) &dataTypeCode, sizeof(dataTypeCode));
    short colorMapOrigin;
    inFile.read((char *) &colorMapOrigin, sizeof(colorMapOrigin));
    short colorMapLength;
    inFile.read((char *) &colorMapLength, sizeof(colorMapLength));
    char colorMapDepth;
    inFile.read((char *) &colorMapDepth, sizeof(colorMapDepth));
    short xOrigin;
    inFile.read((char *) &xOrigin, sizeof(xOrigin));
    short yOrigin;
    inFile.read((char *) &yOrigin, sizeof(yOrigin));
    short width;
    inFile.read((char *) &width, sizeof(width));
    short height;
    inFile.read((char *) &height, sizeof(height));
    char bitsPerPixel;
    inFile.read((char *) &bitsPerPixel, sizeof(bitsPerPixel));
    char imageDescriptor;
    inFile.read((char *) &imageDescriptor, sizeof(imageDescriptor));

    Image image(idLength, colorMapType, dataTypeCode, colorMapOrigin, colorMapLength, colorMapDepth, xOrigin,
                yOrigin, width, height, bitsPerPixel, imageDescriptor);

    int numOfPixels = width * height;

    for(unsigned int i = 0; i < numOfPixels; ++i)
    {
        unsigned char blue;
        inFile.read((char*) &blue, sizeof(blue));

        unsigned char green;
        inFile.read((char*) &green, sizeof(green));

        unsigned char red;
        inFile.read((char*) &red, sizeof(red));

        Image::Pixels currentPixel = Image::Pixels(red, green, blue);
        image.GetPixelVector().push_back(currentPixel);
    }
    return image;
}

void WriteImage(string filePath, Image& image) {
    ofstream outFile(filePath, ios_base::binary);

    outFile.write((char *) &image.idLength, sizeof(image.idLength));
    outFile.write((char *) &image.colorMapType, sizeof(image.colorMapType));
    outFile.write((char *) &image.dataTypeCode, sizeof(image.dataTypeCode));
    outFile.write((char *) &image.colorMapOrigin, sizeof(image.colorMapOrigin));
    outFile.write((char *) &image.colorMapLength, sizeof(image.colorMapLength));
    outFile.write((char *) &image.colorMapDepth, sizeof(image.colorMapDepth));
    outFile.write((char *) &image.xOrigin, sizeof(image.xOrigin));
    outFile.write((char *) &image.yOrigin, sizeof(image.yOrigin));
    outFile.write((char *) &image.width, sizeof(image.width));
    outFile.write((char *) &image.height, sizeof(image.height));
    outFile.write((char *) &image.bitsPerPixel, sizeof(image.bitsPerPixel));
    outFile.write((char *) &image.imageDescriptor, sizeof(image.imageDescriptor));

    for(auto & n : image.GetPixelVector()) {
        outFile.write((char*) &n.blue, sizeof(n.blue));

        outFile.write((char*) &n.green, sizeof(n.green));

        outFile.write((char*) &n.red, sizeof(n.red));

    }
    outFile.close();
}

bool CheckOutFileName(string name) {
    if (name.size() < 5) {
        return false;
    }
    string letters;
    string temp;
    temp = name.at(name.size()-4);
    letters.append(temp);
    temp = name.at(name.size()-3);
    letters.append(temp);
    temp = name.at(name.size()-2);
    letters.append(temp);
    temp = name.at(name.size()-1);
    letters.append(temp);

    if (letters == ".tga") {
        return true;
    }
    else {
        cout << "Invalid file name." << endl;
        return false;
    }
}
bool CheckFileName(string name) {
    if (name.size() < 5) {
        return false;
    }
    string letters;
    string temp;
    temp = name.at(name.size()-4);
    letters.append(temp);
    temp = name.at(name.size()-3);
    letters.append(temp);
    temp = name.at(name.size()-2);
    letters.append(temp);
    temp = name.at(name.size()-1);
    letters.append(temp);

    if (letters != ".tga") {
        cout << "Invalid file name." << endl;
        return false;
    }

    ifstream fin(name);
    if (!fin.good()) {
        cout << "File does not exist." << endl;
        return false;
    }
    fin.close();

    return true;
}
bool CheckMethodFile(string name) {
    if (name.size() < 5) {
        return false;
    }
    string letters;
    string temp;
    temp = name.at(name.size()-4);
    letters.append(temp);
    temp = name.at(name.size()-3);
    letters.append(temp);
    temp = name.at(name.size()-2);
    letters.append(temp);
    temp = name.at(name.size()-1);
    letters.append(temp);

    if (letters != ".tga") {
        cout << "Invalid argument, invalid file name." << endl;
        return false;
    }

    ifstream fin(name);
    if (!fin.good()) {
        cout << "Invalid argument, file does not exist." << endl;
        return false;
    }
    fin.close();

    return true;
}

bool isNumeric(string str) {
    for (char n : str) {
        if (isdigit(n) == false) {
            cout << "Invalid argument, expected number." << endl;
            return false;
        }
    }
    return true;
}
bool isNumericNegative(string str) {
    if (str[0] == '-') {
        str.erase(str.begin());
    }
    for (char n : str) {
        if (isdigit(n) == false) {
            cout << "Invalid argument, expected number." << endl;
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    vector<Image> images;

    if (argc < 2) {
        cout << "Project 2: Image Processing, Spring 2023\n\n"
        << "Usage:\n"
        << "\t./project2.out [output] [firstImage] [method] [...] " << endl;
        return 0;
    }
    else if ((string)argv[1] == "--help") {
        cout << "Project 2: Image Processing, Spring 2023\n\n"
        << "Usage:\n"
        << "\t./project2.out [output] [firstImage] [method] [...] " << endl;
        return 0;
    }
    else if (argc == 2) {
        cout << "Invalid file name." << endl;
        return 0;
    }
    string outFile;
    string sourceName;
    string file2;
    string file3;
    int toAdd;
    int toScale;
    float temp;
    int temp2;
    outFile = (string)argv[1];
    if (!CheckOutFileName(outFile)) {
        return 0;
    }
    sourceName = (string)argv[2];
    if (!CheckFileName(sourceName)) {
        return 0;
    }
    Image tracked = ReadTracked(sourceName);

    images.push_back(tracked);
    if (argc == 3) {
        cout << "Invalid method name." << endl;
        return 0;
    }
    for (int i = 3; i < argc; ++i) {
        if ((string)argv[i] == "multiply") {
            if (argc == i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }
            file2 = (string)argv[i+1];
            if (!CheckMethodFile(file2)) {
                return 0;
            }
            ReadImage(file2, images, 1);
            Image image(images[0].idLength, images[0].colorMapType, images[0].dataTypeCode,
                        images[0].colorMapOrigin,images[0].colorMapLength,
                        images[0].colorMapDepth, images[0].xOrigin, images[0].yOrigin,
                        images[0].width, images[0].height, images[0].bitsPerPixel,
                        images[0].imageDescriptor);
            images.push_back(image);

            cout << "Multiplying " << sourceName << " and " << file2 << "..." << endl;
            images[2].Multiply(images[0].GetPixelVector(), images[1].GetPixelVector());
            cout << "...and saving output to " << outFile << "!" << endl;
            WriteImage(outFile, images[2]);
            images.pop_back();
            images.pop_back();
            tracked = ReadTracked(outFile);
            images[0] = tracked;
            ++i;
        }
        else if ((string)argv[i] == "subtract") {
            if (argc == i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }
            file2 = (string)argv[i+1];
            if (!CheckMethodFile(file2)) {
                return 0;
            }
            ReadImage(file2, images, 1);

            for (int j = 0; j < images[0].GetPixelVector().size(); ++j) {
                if ((images[0].GetPixelVector().at(j).red - images[1].GetPixelVector().at(j).red) < 0) {
                    images[0].GetPixelVector().at(j).red = 0;
                }
                else if ((images[0].GetPixelVector().at(j).red - images[1].GetPixelVector().at(j).red) > 255) {
                    images[0].GetPixelVector().at(j).red = 255;
                }
                else {
                    images[0].GetPixelVector().at(j).red = images[0].GetPixelVector().at(j).red
                                                           - images[1].GetPixelVector().at(j).red;
                }
                if ((images[0].GetPixelVector().at(j).green - images[1].GetPixelVector().at(j).green) < 0) {
                    images[0].GetPixelVector().at(j).green = 0;
                }
                else if ((images[0].GetPixelVector().at(j).green - images[1].GetPixelVector().at(j).green) > 255) {
                    images[0].GetPixelVector().at(j).green = 255;
                }
                else {
                    images[0].GetPixelVector().at(j).green = images[0].GetPixelVector().at(j).green
                                                             - images[1].GetPixelVector().at(j).green;
                }
                if ((images[0].GetPixelVector().at(j).blue - images[1].GetPixelVector().at(j).blue) < 0) {
                    images[0].GetPixelVector().at(j).blue = 0;
                }
                else if ((images[0].GetPixelVector().at(j).blue - images[1].GetPixelVector().at(j).blue) > 255) {
                    images[0].GetPixelVector().at(j).blue = 255;
                }
                else {
                    images[0].GetPixelVector().at(j).blue = images[0].GetPixelVector().at(j).blue
                                                            - images[1].GetPixelVector().at(j).blue;
                }
            }

            cout << "Subtracting " << sourceName << " and " << file2 << "..." << endl;
            cout << "...and saving output to " << outFile << "!" << endl;
            WriteImage(outFile, images[0]);
            images.pop_back();
            tracked = ReadTracked(outFile);
            images[0] = tracked;
            ++i;
        }
        else if ((string)argv[i] == "overlay") {
            if (argc == i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }
            file2 = (string)argv[i+1];
            if (!CheckMethodFile(file2)) {
                return 0;
            }
            ReadImage(file2, images, 1);
            Image image(images[0].idLength, images[0].colorMapType, images[0].dataTypeCode,
                        images[0].colorMapOrigin,images[0].colorMapLength,
                        images[0].colorMapDepth, images[0].xOrigin, images[0].yOrigin,
                        images[0].width, images[0].height, images[0].bitsPerPixel,
                        images[0].imageDescriptor);
            images.push_back(image);

            cout << "Overlaying " << sourceName << " and " << file2 << "..." << endl;
            images[2].Overlay(tracked.GetPixelVector(), images[1].GetPixelVector());
            cout << "...and saving output to " << outFile << "!" << endl;
            WriteImage(outFile, images[2]);
            images.pop_back();
            images.pop_back();
            tracked = ReadTracked(outFile);
            images[0] = tracked;
            ++i;
        }
        else if ((string)argv[i] == "screen") {
            if (argc == i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }
            file2 = (string)argv[i+1];
            if (!CheckMethodFile(file2)) {
                return 0;
            }
            ReadImage(file2, images, 1);
            Image image(images[0].idLength, images[0].colorMapType, images[0].dataTypeCode,
                        images[0].colorMapOrigin,images[0].colorMapLength,
                        images[0].colorMapDepth, images[0].xOrigin, images[0].yOrigin,
                        images[0].width, images[0].height, images[0].bitsPerPixel,
                        images[0].imageDescriptor);
            images.push_back(image);

            cout << "Screening " << sourceName << " and " << file2 << "..." << endl;
            images[2].Screen(tracked.GetPixelVector(), images[1].GetPixelVector());
            cout << "...and saving output to " << outFile << "!" << endl;
            WriteImage(outFile, images[2]);
            images.pop_back();
            images.pop_back();
            tracked = ReadTracked(outFile);
            images[0] = tracked;
            ++i;
        }
        else if ((string)argv[i] == "combine") {
            if ((argc == i + 1) | (argc == i + 2)) {
                cout << "Missing argument." << endl;
                return 0;
            }
            file2 = (string)argv[i+1];
            if (!CheckMethodFile(file2)) {
                return 0;
            }
            file3 = (string)argv[i+2];
            if (!CheckMethodFile(file3)) {
                return 0;
            }
            ReadImage(file2, images, 1);
            ReadImage(file3, images, 2);
            Image image(images[0].idLength, images[0].colorMapType, images[0].dataTypeCode,
                        images[0].colorMapOrigin,images[0].colorMapLength,
                        images[0].colorMapDepth, images[0].xOrigin, images[0].yOrigin,
                        images[0].width, images[0].height, images[0].bitsPerPixel,
                        images[0].imageDescriptor);
            images.push_back(image);

            cout << "Combining " << sourceName << " and " << file2 << " and " << file3 << "..." << endl;
            image.CombineChannel(images);
            cout << "...and saving output to " << outFile << "!" << endl;
            WriteImage(outFile, images[3]);
            images.erase(images.begin()+1);
            images.erase(images.begin()+1);
            images.erase(images.begin()+1);
            tracked = ReadTracked(outFile);
            images[0] = tracked;
            i += 2;
        }
        else if ((string)argv[i] == "flip") {
            Image image(images[0].idLength, images[0].colorMapType, images[0].dataTypeCode,
                        images[0].colorMapOrigin,images[0].colorMapLength,
                        images[0].colorMapDepth, images[0].xOrigin, images[0].yOrigin,
                        images[0].width, images[0].height, images[0].bitsPerPixel,
                        images[0].imageDescriptor);
            images.push_back(image);

            cout << "Flipping " << sourceName << "..." << endl;
            images[0].Flip180Degrees(images);
            cout << "...and saving output to " << outFile << "!" << endl;
            WriteImage(outFile, images[1]);
            images.pop_back();
            tracked = ReadTracked(outFile);
            images[0] = tracked;
        }
        else if ((string)argv[i] == "onlyred") {
            Image image(images[0].idLength, images[0].colorMapType, images[0].dataTypeCode,
                        images[0].colorMapOrigin,images[0].colorMapLength,
                        images[0].colorMapDepth, images[0].xOrigin, images[0].yOrigin,
                        images[0].width, images[0].height, images[0].bitsPerPixel,
                        images[0].imageDescriptor);
            images.push_back(image);

            cout << "Retrieving red channel from " << sourceName << "..." << endl;
            images[0].CreateChannel(images, "red");
            cout << "...and saving output to " << outFile << "!" << endl;
            WriteImage(outFile, images[1]);
            images.pop_back();
            tracked = ReadTracked(outFile);
            images[0] = tracked;
        }
        else if ((string)argv[i] == "onlygreen") {
            Image image(images[0].idLength, images[0].colorMapType, images[0].dataTypeCode,
                        images[0].colorMapOrigin,images[0].colorMapLength,
                        images[0].colorMapDepth, images[0].xOrigin, images[0].yOrigin,
                        images[0].width, images[0].height, images[0].bitsPerPixel,
                        images[0].imageDescriptor);
            images.push_back(image);

            cout << "Retrieving green channel from " << sourceName << "..." << endl;
            images[0].CreateChannel(images, "green");
            cout << "...and saving output to " << outFile << "!" << endl;
            WriteImage(outFile, images[1]);
            images.pop_back();
            tracked = ReadTracked(outFile);
            images[0] = tracked;
        }
        else if ((string)argv[i] == "onlyblue") {
            Image image(images[0].idLength, images[0].colorMapType, images[0].dataTypeCode,
                        images[0].colorMapOrigin,images[0].colorMapLength,
                        images[0].colorMapDepth, images[0].xOrigin, images[0].yOrigin,
                        images[0].width, images[0].height, images[0].bitsPerPixel,
                        images[0].imageDescriptor);
            images.push_back(image);

            cout << "Retrieving blue channel from " << sourceName << "..." << endl;
            images[0].CreateChannel(images, "blue");
            cout << "...and saving output to " << outFile << "!" << endl;
            WriteImage(outFile, images[1]);
            images.pop_back();
            tracked = ReadTracked(outFile);
            images[0] = tracked;
        }
        else if ((string)argv[i] == "addred") {
            if (argc == i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }
            if (!isNumericNegative((string)argv[i+1])) {
                return 0;
            }
            toAdd = stoi(argv[i+1]);
            for (auto & j : images[0].GetPixelVector()) {
                if ((j.red + toAdd) > 255) {
                    j.red = 255;
                }
                else if ((j.red + toAdd) < 0) {
                    j.red = 0;
                }
                else {
                    j.red += toAdd;
                }
            }
            cout << "Adding " << toAdd << " to red channel of " << sourceName << "..." << endl;
            cout << "...and saving output to " << outFile << "!" << endl;
            WriteImage(outFile, images[0]);
            tracked = ReadTracked(outFile);
            images[0] = tracked;
            ++i;
        }
        else if ((string)argv[i] == "addgreen") {
            if (argc == i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }
            if (!isNumericNegative((string)argv[i+1])) {
                return 0;
            }
            toAdd = stoi(argv[i+1]);
            for (auto & j : images[0].GetPixelVector()) {
                if ((j.green + toAdd) > 255) {
                    j.green = 255;
                }
                else if ((j.green + toAdd) < 0) {
                    j.green = 0;
                }
                else {
                    j.green += toAdd;
                }
            }
            cout << "Adding " << toAdd << " to green channel of " << sourceName << "..." << endl;
            cout << "...and saving output to " << outFile << "!" << endl;
            WriteImage(outFile, images[0]);
            tracked = ReadTracked(outFile);
            images[0] = tracked;
            ++i;
        }
        else if ((string)argv[i] == "addblue") {
            if (argc == i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }
            if (!isNumericNegative((string)argv[i+1])) {
                return 0;
            }
            toAdd = stoi(argv[i+1]);
            for (auto & j : images[0].GetPixelVector()) {
                if ((j.blue + toAdd) > 255) {
                    j.blue = 255;
                }
                else if ((j.blue + toAdd) < 0) {
                    j.blue = 0;
                }
                else {
                    j.blue += toAdd;
                }
            }
            cout << "Adding " << toAdd << " to blue channel of " << sourceName << "..." << endl;
            cout << "...and saving output to " << outFile << "!" << endl;
            WriteImage(outFile, images[0]);
            tracked = ReadTracked(outFile);
            images[0] = tracked;
            ++i;
        }
        else if ((string)argv[i] == "scalered") {
            if (argc == i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }
            if (!isNumeric((string)argv[i+1])) {
                return 0;
            }
            toScale = stoi(argv[i+1]);
            images[0].Scale(images[0].GetPixelVector(), "red", (float)toScale);

            cout << "Scaling red channel of " << sourceName << " by " << toScale << "..." << endl;
            cout << "...and saving output to " << outFile << "!" << endl;
            WriteImage(outFile, images[0]);
            tracked = ReadTracked(outFile);
            images[0] = tracked;
            ++i;
        }
        else if ((string)argv[i] == "scalegreen") {
            if (argc == i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }
            if (!isNumeric((string)argv[i+1])) {
                return 0;
            }
            toScale = stoi(argv[i+1]);
            images[0].Scale(images[0].GetPixelVector(), "green", (float)toScale);

            cout << "Scaling green channel of " << sourceName << " by " << toScale << "..." << endl;
            cout << "...and saving output to " << outFile << "!" << endl;
            WriteImage(outFile, images[0]);
            tracked = ReadTracked(outFile);
            images[0] = tracked;
            ++i;
        }
        else if ((string)argv[i] == "scaleblue") {
            if (argc == i + 1) {
                cout << "Missing argument." << endl;
                return 0;
            }
            if (!isNumeric((string)argv[i+1])) {
                return 0;
            }
            toScale = stoi(argv[i+1]);
            images[0].Scale(images[0].GetPixelVector(), "blue", (float)toScale);

            cout << "Scaling blue channel of " << sourceName << " by " << toScale << "..." << endl;
            cout << "...and saving output to " << outFile << "!" << endl;
            WriteImage(outFile, images[0]);
            tracked = ReadTracked(outFile);
            images[0] = tracked;
            ++i;
        }
        else {
            cout << "Invalid method name." << endl;
            return 0;
        }
    }
    return 0;
}
