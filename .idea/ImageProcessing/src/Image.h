//
// Created by Christina Nguyen on 10/30/22.
//
#include <string>
#ifndef PROJECT2IMAGEPROCESSING_IMAGE_H
#define PROJECT2IMAGEPROCESSING_IMAGE_H

using namespace std;

class Image {
 public:
    struct imageData {
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
    };

    struct pixelData {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
    };

//    vector<Image::pixelData> pixels;

//    Image();
//    Image(string);

//    Image(char idLength, char colorMapType, char dataTypeCode, short colorMapOrigin, short colorMapLength,
//    char colorMapDepth, short xOrigin, short yOrigin, short width, short height, char bitsPerPixel,
//    char imageDescriptor)
//    : idLength(idLength), colorMapType(colorMapType), dataTypeCode(dataTypeCode), colorMapOrigin(colorMapOrigin),
//    colorMapLength(colorMapLength), colorMapDepth(colorMapDepth), xOrigin(xOrigin), yOrigin(yOrigin), width(width),
//    height(height), bitsPerPixel(bitsPerPixel), imageDescriptor(imageDescriptor)
//    {}
};

#endif //PROJECT2IMAGEPROCESSING_IMAGE_H
