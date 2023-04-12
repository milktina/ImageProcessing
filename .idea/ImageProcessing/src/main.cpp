#include <iostream>
#include "Image.h"
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <math.h>

using namespace std;

void readFile(string filename, Image::imageData &headerObject, vector<Image::pixelData> &pixels) {
    ifstream tgaFile(filename, ios_base::binary);

    tgaFile.read(&headerObject.idLength, sizeof(headerObject.idLength));
    tgaFile.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    tgaFile.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    tgaFile.read((char *)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    tgaFile.read((char *)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    tgaFile.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    tgaFile.read((char *)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
    tgaFile.read((char *)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
    tgaFile.read((char *)&headerObject.width, sizeof(headerObject.width));
    tgaFile.read((char *)&headerObject.height, sizeof(headerObject.height));
    tgaFile.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    tgaFile.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

//    cout << "ID Length: " << (int)headerObject.idLength << endl;
//    cout << "Color Map Type: " << (int)headerObject.colorMapType << endl;
//    cout << "Data Type Code: " << (int)headerObject.dataTypeCode << endl;
//    cout << "Color Map Origin: " << headerObject.colorMapOrigin << endl;
//    cout << "Color Map Length: " << headerObject.colorMapLength << endl;
//    cout << "Color Map Depth: " << (int)headerObject.colorMapDepth << endl;
//    cout << "X Origin: " << headerObject.xOrigin << endl;
//    cout << "Y Origin: " << headerObject.yOrigin << endl;
//    cout << "Width: " << headerObject.width << endl;
//    cout << "Height: " << headerObject.height << endl;
//    cout << "Bits Per Pixel: " << (int)headerObject.bitsPerPixel << endl;
//    cout << "Image Descriptor: " << (int)headerObject.imageDescriptor << endl;

    unsigned int imageSize = headerObject.width * headerObject.height;

    Image::pixelData pixelObject;

    for (int i = 0; i < imageSize; i++) {
            tgaFile.read((char *)&pixelObject.blue, sizeof(pixelObject.blue));
            tgaFile.read((char *)&pixelObject.green, sizeof(pixelObject.green));
            tgaFile.read((char *)&pixelObject.red, sizeof(pixelObject.red));
//            cout << "Blue: " << pixelObject.blue << endl;
//            cout << "Green: " << pixelObject.green << endl;
//            cout << "Red: " << pixelObject.red << endl;

            pixels.push_back(pixelObject);
    }
}

void writeOutFile (string filename, Image::imageData &headerObject, vector<Image::pixelData> &pixels) {
    ofstream outputFile(filename, ios_base::binary);

    if (outputFile.is_open()) {
        outputFile.write(&headerObject.idLength, sizeof(headerObject.idLength));
        outputFile.write(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
        outputFile.write(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
        outputFile.write((char *) &headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
        outputFile.write((char *) &headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
        outputFile.write(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
        outputFile.write((char *) &headerObject.xOrigin, sizeof(headerObject.xOrigin));
        outputFile.write((char *) &headerObject.yOrigin, sizeof(headerObject.yOrigin));
        outputFile.write((char *) &headerObject.width, sizeof(headerObject.width));
        outputFile.write((char *) &headerObject.height, sizeof(headerObject.height));
        outputFile.write(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
        outputFile.write(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
    }

    for (int i = 0; i < pixels.size(); i++) {
        outputFile.write((char *) &pixels[i].blue, sizeof(pixels[i].blue));
        outputFile.write((char *) &pixels[i].green, sizeof(pixels[i].green));
        outputFile.write((char *) &pixels[i].red, sizeof(pixels[i].red));
    }

    outputFile.close();
 }

    void multiply(vector<Image::pixelData> &picture1, vector<Image::pixelData> &picture2) {
        for (unsigned int i = 0; i < picture1.size(); i++) {
            picture1[i].blue =  ((((float)picture1[i].blue * (float)picture2[i].blue) / 255) + 0.5f);
            picture1[i].green = ((((float)picture1[i].green * (float)picture2[i].green) / 255) + 0.5f);
            picture1[i].red =  ((((float)picture1[i].red * (float)picture2[i].red) / 255) + 0.5f);
        }
    }

    void subtract(vector<Image::pixelData> &picture1, vector<Image::pixelData> &picture2) {
        for (unsigned int i = 0; i < picture1.size(); i++) {
            int blue = (int)picture1[i].blue - (int)picture2[i].blue;
            int green = (int)picture1[i].green - (int)picture2[i].green;
            int red = (int)picture1[i].red - (int)picture2[i].red;

            if (blue > 255) {
                blue = 255;
            }
            if (green > 255) {
                green = 255;
            }
            if (red > 255) {
                red = 255;
            }


            if (blue < 0) {
                blue = 0;
            }
            if (green < 0) {
                green = 0;
            }
            if (red < 0) {
                red = 0;
            }

            picture1[i].blue = blue;
            picture1[i].green = green;
            picture1[i].red = red;
        }
    }

    void screen(vector<Image::pixelData> &picture1, vector<Image::pixelData> &picture2) {
        for (unsigned int i = 0; i < picture1.size(); i++) {
            // blue
            float result1Blue = (255 - picture1[i].blue);
            float result2Blue = (255 - picture2[i].blue);
            picture1[i].blue = (int) (255 - ((result1Blue * result2Blue)/255) + 0.5f);

            // green
            float result1Green = (255 - picture1[i].green);
            float result2Green = (255 - picture2[i].green);
            picture1[i].green = (int) (255 - ((result1Green * result2Green)/255) + 0.5f);

            // red
            float result1Red = (255 - picture1[i].red);
            float result2Red = (255 - picture2[i].red);
            picture1[i].red = (int) (255 - ((result1Red * result2Red)/255) + 0.5f);
        }
    }

    void overlay(vector<Image::pixelData> &picture1, vector<Image::pixelData> &picture2) {

        for (unsigned int i = 0; i < picture1.size(); i++) {

            if(((picture2[i].blue)/255.0) > 0.5) {
                float result1Blue = (255 - picture1[i].blue);
                float result2Blue = (255 - picture2[i].blue);
                float result3Blue = ((result1Blue * result2Blue)/255);
                picture1[i].blue = (int) ((255-(2*result3Blue)) + 0.5f);
            }
            else {
                float result1Blue = picture1[i].blue;
                float result2Blue = picture2[i].blue;
                float result3Blue = ((result1Blue * result2Blue)/255);
                picture1[i].blue = (int) ((2*result3Blue) + 0.5f);
//                picture1[i].blue = pixel.blue;
            }

            if(((picture2[i].green)/255.0) > 0.5) {
                float result1Green = (255 - picture1[i].green);
                float result2Green = (255 - picture2[i].green);
                float result3Green = ((result1Green*result2Green)/255);
                picture1[i].green = (int)((255-(2*result3Green)) + 0.5f);
//                picture1[i].blue = pixel.blue;
            }
            else {
                float result1Green = picture1[i].green;
                float result2Green = picture2[i].green;
                float result3Green = ((result1Green * result2Green)/255);
                picture1[i].green = (int) ((2*result3Green) + 0.5f);
            }

            if(((picture2[i].red)/255.0) > 0.5) {
                float result1Red = (255 - picture1[i].red);
                float result2Red = (255 - picture2[i].red);
                float result3Red = ((result1Red*result2Red)/255);
                picture1[i].red = (int) ((255-(2*result3Red)) + 0.5f);
            }
            else {
                float result1Red= picture1[i].red;
                float result2Red = picture2[i].blue;
                float result3Red = ((result1Red * result2Red)/255);
                picture1[i].red = (int) ((2*result3Red) + 0.5f);
            }
        }
    }

void addToChannel(vector<Image::pixelData> &picture, string colorChannel, int value) {

    if (colorChannel == "blue") {
        for (unsigned int i = 0; i < picture.size(); i++) {
            if ((picture[i].blue + value) > 255) {
                picture[i].blue = 255;
            } else if ((picture[i].blue + value) <= 255) {
                picture[i].blue += value;
            }
        }
    }

    if (colorChannel == "green") {
        for (unsigned int i = 0; i < picture.size(); i++) {
            if ((picture[i].green + value) > 255) {
                picture[i].green = 255;
            } else if ((picture[i].green + value) <= 255) {
                picture[i].green += value;
            }
        }
    }

    if (colorChannel == "red") {
        for (unsigned int i = 0; i < picture.size(); i++) {
            if ((picture[i].red + value) > 255) {
                picture[i].red = 255;
            } else if ((picture[i].red + value) <= 255) {
                picture[i].red += value;
            }
        }
    }
}

void scale(vector<Image::pixelData> &picture, string colorChannel, int scaleFactor) {
    if (colorChannel == "blue") {
        for (unsigned int i = 0; i < picture.size(); i++) {
          if ((picture[i].blue * scaleFactor) > 255) {
              picture[i].blue = 255;
          }
          else if ((picture[i].blue * scaleFactor) <= 255) {
              picture[i].blue *= scaleFactor;
          }
        }
    }

    if (colorChannel == "red") {
        for (unsigned int i = 0; i < picture.size(); i++) {
            if ((picture[i].red * scaleFactor) > 255) {
                picture[i].red = 255;
            }
            else if ((picture[i].red * scaleFactor) <= 255) {
                picture[i].red *= scaleFactor;
            }
        }
    }

    if (colorChannel == "green") {
        for (unsigned int i = 0; i < picture.size(); i++) {
            if ((picture[i].green * scaleFactor) > 255) {
                picture[i].green = 255;
            }
            else if ((picture[i].green * scaleFactor) <= 255){
                picture[i].green *= scaleFactor;
            }
        }
    }
}

void separateFiles(vector<Image::pixelData> &picture, string colorChannel) {

    if (colorChannel == "blue") {
        for (unsigned int i = 0; i < picture.size(); i++) {
            picture[i].green = picture[i].blue;
            picture[i].red = picture[i].blue;
        }
    }
    else if (colorChannel == "green") {
        for (unsigned int i = 0; i < picture.size(); i++) {
            picture[i].blue = picture[i].green;
            picture[i].red = picture[i].green;
        }
    }
    else if (colorChannel == "red") {
        for (unsigned int i = 0; i < picture.size(); i++) {
            picture[i].blue = picture[i].red;
            picture[i].green = picture[i].red;
        }
    }
}

    void combine(vector<Image::pixelData> &picture1, vector<Image::pixelData> &picture2,
                 vector<Image::pixelData> &picture3) {
        for (unsigned int i = 0; i < picture1.size(); i++) {
            picture1[i].green = picture2[i].green;
            picture1[i].blue = picture3[i].blue;
        }
    }

    void rotate(vector<Image::pixelData> &picture) {
        reverse(picture.begin(), picture.end());
    }

    // test case
    bool same(Image::imageData pictureHeader, vector<Image::pixelData> picture, Image::imageData exampleHeader, vector<Image::pixelData> example) {

        bool same = true;

        if (pictureHeader.idLength != exampleHeader.idLength) {
            same = false;
            cout << "ID Length Diff" << endl;
        }
        if (pictureHeader.colorMapType != exampleHeader.colorMapType) {
            same = false;
            cout << "Color Map Type Diff" << endl;
        }
        if (pictureHeader.dataTypeCode != exampleHeader.dataTypeCode) {
            same = false;
            cout << "Data Type Code Diff" << endl;
        }
        if (pictureHeader.colorMapOrigin != exampleHeader.colorMapOrigin) {
            same = false;
            cout << "Color Map Origin Diff" << endl;
        }
        if (pictureHeader.colorMapLength != exampleHeader.colorMapLength) {
            same = false;
            cout << "Color Map Length Diff" << endl;
        }
        if (pictureHeader.colorMapDepth != exampleHeader.colorMapDepth) {
            same = false;
            cout << "Color Map Depth Diff" << endl;
        }
        if (pictureHeader.xOrigin != exampleHeader.idLength) {
            same = false;
            cout << "xOrigin Diff" << endl;
        }
        if (pictureHeader.yOrigin != exampleHeader.yOrigin) {
            same = false;
            cout << "yOrigin Diff" << endl;
        }
        if (pictureHeader.width != exampleHeader.width) {
            same = false;
            cout << "Width Diff" << endl;
        }
        if (pictureHeader.height != exampleHeader.height) {
            same = false;
            cout << "Height Diff" << endl;
        }
        if (pictureHeader.bitsPerPixel != exampleHeader.bitsPerPixel) {
            same = false;
            cout << "Bits Per Pixel Diff" << endl;
        }
        if (pictureHeader.imageDescriptor != exampleHeader.imageDescriptor) {
            same = false;
            cout << "Image Descriptor Diff" << endl;
        }

        for (unsigned int i = 0; i < 5; i++) {
            if (picture[i].blue != example[i].blue) {
                same = false;
                cout << "Blue Diff" << endl;
            }
            if (picture[i].green != example[i].green) {
                same = false;
                cout << "Green Diff" << endl;
                cout << "Mine: " << (int) picture[i].green << endl;
                cout << "Example: " << (int) example[i].green << endl;
            }
            if (picture[i].red != example[i].red) {
                same = false;
                cout << "Red Diff" << endl;
            }
        }
        return same;
    }

    int main() {
        Image::imageData layer1Header;
        vector<Image::pixelData> layer1Pixels;
        readFile("input/layer1.tga", layer1Header, layer1Pixels);

        Image::imageData layer2Header;
        vector<Image::pixelData> layer2Pixels;
        readFile("input/layer2.tga", layer2Header, layer2Pixels);

        Image::imageData layer_redHeader;
        vector<Image::pixelData> layer_redPixels;
        readFile("input/layer_red.tga", layer_redHeader, layer_redPixels);

        Image::imageData layer_blueHeader;
        vector<Image::pixelData> layer_bluePixels;
        readFile("input/layer_blue.tga", layer_blueHeader, layer_bluePixels);

        Image::imageData layer_greenHeader;
        vector<Image::pixelData> layer_greenPixels;
        readFile("input/layer_green.tga", layer_greenHeader, layer_greenPixels);

        Image::imageData pattern1Header;
        vector<Image::pixelData> pattern1Pixels;
        readFile("input/pattern1.tga", pattern1Header, pattern1Pixels);

        Image::imageData pattern2Header;
        vector<Image::pixelData> pattern2Pixels;
        readFile("input/pattern2.tga", pattern2Header, pattern2Pixels);

        Image::imageData carHeader;
        vector<Image::pixelData> carPixels;
        readFile("input/car.tga", carHeader, carPixels);

        Image::imageData circlesHeader;
        vector<Image::pixelData> circlesPixels;
        readFile("input/circles.tga", circlesHeader, circlesPixels);

        Image::imageData textHeader;
        vector<Image::pixelData> textPixels;
        readFile("input/text.tga", textHeader, textPixels);

        Image::imageData text2Header;
        vector<Image::pixelData> text2Pixels;
        readFile("input/text2.tga", text2Header, text2Pixels);

        // part 1: multiply
        Image::imageData part1Header = layer1Header;
        vector<Image::pixelData> part1Pixels = layer1Pixels;
        multiply(part1Pixels, pattern1Pixels);
        writeOutFile("output/part1.tga", part1Header, part1Pixels);

        // part 2: subtract
        Image::imageData part2Header = carHeader;
        vector<Image::pixelData> part2Pixels = carPixels;
        subtract(part2Pixels, layer2Pixels);
        writeOutFile("output/part2.tga", part2Header, part2Pixels);

        // part 3: multiply and screen
        Image::imageData part3Header = layer1Header;
        vector<Image::pixelData> part3Pixels = layer1Pixels;
        multiply(part3Pixels, pattern2Pixels);
        screen(part3Pixels, textPixels);
        writeOutFile("output/part3.tga", part3Header, part3Pixels);

        // part 4: multiply and subtract
        Image::imageData part4Header = layer2Header;
        vector<Image::pixelData> part4Pixels = layer2Pixels;
        multiply(part4Pixels, circlesPixels);
        subtract(part4Pixels, pattern2Pixels);
        writeOutFile("output/part4.tga", part4Header, part4Pixels);

        // part 5: overlay
        Image::imageData part5Header = layer1Header;
        vector<Image::pixelData> part5Pixels = layer1Pixels;
        overlay(part5Pixels, pattern1Pixels);
        writeOutFile("output/part5.tga", part5Header, part5Pixels);

        // part 6: add 200 to green channel
        vector<Image::pixelData> part6Pixels = carPixels;
        addToChannel(part6Pixels, "green", 200);
        writeOutFile("output/part6.tga", carHeader, part6Pixels);

        // part 7: scaling channels
        Image::imageData part7Header;
        vector<Image::pixelData> part7Pixels;
        readFile("input/car.tga", part7Header, part7Pixels);
        scale(part7Pixels, "red", 4);
        scale(part7Pixels, "blue", 0);
        writeOutFile("output/part7.tga", part7Header, part7Pixels);

        // part 8: separating files by color channel
        Image::imageData part8Header = carHeader;
        vector<Image::pixelData> part8PixelsBlue = carPixels;
        separateFiles(part8PixelsBlue, "blue");
        writeOutFile("output/part8_b.tga", part8Header, part8PixelsBlue);

        vector<Image::pixelData> part8PixelsGreen = carPixels;
        separateFiles(part8PixelsGreen, "green");
        writeOutFile("output/part8_g.tga", part8Header, part8PixelsGreen);

        vector<Image::pixelData> part8PixelsRed = carPixels;
        separateFiles(part8PixelsRed, "red");
        writeOutFile("output/part8_r.tga", part8Header, part8PixelsRed);

        // part 9: combining files
        combine(layer_redPixels, layer_greenPixels, layer_bluePixels);
        writeOutFile("output/part9.tga", layer_redHeader, layer_redPixels);

        // part 10:
        rotate(text2Pixels);
        writeOutFile("output/part10.tga", text2Header, text2Pixels);


        // testing
        Image::imageData part1HeaderEx;
        vector<Image::pixelData> part1PixelsEx;
        readFile("ImageProcessing/examples/EXAMPLE_part1.tga", part1HeaderEx, part1PixelsEx);

        Image::imageData part2HeaderEx;
        vector<Image::pixelData> part2PixelsEx;
        readFile("ImageProcessing/examples/EXAMPLE_part2.tga", part2HeaderEx, part2PixelsEx);

        Image::imageData part3HeaderEx;
        vector<Image::pixelData> part3PixelsEx;
        readFile("ImageProcessing/examples/EXAMPLE_part3.tga", part3HeaderEx, part3PixelsEx);

        Image::imageData part4HeaderEx;
        vector<Image::pixelData> part4PixelsEx;
        readFile("ImageProcessing/examples/EXAMPLE_part4.tga", part4HeaderEx, part4PixelsEx);

        Image::imageData part5HeaderEx;
        vector<Image::pixelData> part5PixelsEx;
        readFile("ImageProcessing/examples/EXAMPLE_part5.tga", part5HeaderEx, part5PixelsEx);

        Image::imageData part6HeaderEx;
        vector<Image::pixelData> part6PixelsEx;
        readFile("ImageProcessing/examples/EXAMPLE_part6.tga", part6HeaderEx, part6PixelsEx);

        Image::imageData part7HeaderEx;
        vector<Image::pixelData> part7PixelsEx;
        readFile("ImageProcessing/examples/EXAMPLE_part7.tga", part7HeaderEx, part7PixelsEx);

        Image::imageData part8_bHeaderEx;
        vector<Image::pixelData> part8_bPixelsEx;
        readFile("ImageProcessing/examples/EXAMPLE_part8_b.tga", part8_bHeaderEx, part8_bPixelsEx);

        Image::imageData part8_gHeaderEx;
        vector<Image::pixelData> part8_gPixelsEx;
        readFile("ImageProcessing/examples/EXAMPLE_part8_g.tga", part8_gHeaderEx, part8_gPixelsEx);

        Image::imageData part8_rHeaderEx;
        vector<Image::pixelData> part8_rPixelsEx;
        readFile("ImageProcessing/examples/EXAMPLE_part8_r.tga", part8_rHeaderEx, part8_rPixelsEx);


        Image::imageData part9HeaderEx;
        vector<Image::pixelData> part9PixelsEx;
        readFile("ImageProcessing/examples/EXAMPLE_part9.tga", part9HeaderEx, part9PixelsEx);

        Image::imageData part10HeaderEx;
        vector<Image::pixelData> part10PixelsEx;
        readFile("ImageProcessing/examples/EXAMPLE_part10.tga", part10HeaderEx, part10PixelsEx);

        // part 1:
        if (same(part1Header, part1Pixels, part1HeaderEx, part1PixelsEx) == true) {
            cout << "Part 1 Passed" << endl;
        }
        else if (same(part1Header, part1Pixels, part1HeaderEx, part1PixelsEx) == false) {
            cout << "Part 1 Failed" << endl;
        }

        // part 2:
        if (same(part2Header, part2Pixels, part2HeaderEx, part2PixelsEx) == true) {
            cout << "Part 2 Passed" << endl;
        }
        else if (same(part2Header, part2Pixels, part2HeaderEx, part2PixelsEx) == false) {
            cout << "Part 2 Failed" << endl;
        }

        // part 3:
        if (same(part3Header, part3Pixels, part3HeaderEx, part3PixelsEx) == true) {
            cout << "Part 3 Passed" << endl;
        }
        else if (same(part3Header, part3Pixels, part3HeaderEx, part3PixelsEx) == false) {
            cout << "Part 3 Failed" << endl;
        }

        // part 4:
        if (same(part4Header, part4Pixels, part4HeaderEx, part4PixelsEx) == true) {
            cout << "Part 4 Passed" << endl;
        }
        else if (same(part4Header, part4Pixels, part4HeaderEx, part4PixelsEx) == false) {
            cout << "Part 4 Failed" << endl;
        }

        // part 5:
        if (same(part5Header, part5Pixels, part5HeaderEx, part5PixelsEx) == true) {
            cout << "Part 5 Passed" << endl;
        }
        else if (same(part5Header, part5Pixels, part5HeaderEx, part5PixelsEx) == false) {
            cout << "Part 5 Failed" << endl;
        }

        // part 6:
        if (same(carHeader, part6Pixels, part6HeaderEx, part6PixelsEx) == true) {
            cout << "Part 6 Passed" << endl;
        }
        else if (same(carHeader, part6Pixels, part6HeaderEx, part6PixelsEx) == false) {
            cout << "Part 6 Failed" << endl;
        }

        // part 7:
        if (same(part7Header, part7Pixels, part7HeaderEx, part7PixelsEx) == true) {
            cout << "Part 7 Passed" << endl;
        }
        else if (same(part7Header, part7Pixels, part7HeaderEx, part7PixelsEx) == false) {
            cout << "Part 7 Failed" << endl;
        }

        // part 8:
        // blue:
        if (same(part8Header, part8PixelsBlue, part8_bHeaderEx, part8_bPixelsEx) == true) {
            cout << "Part 8 Blue Passed" << endl;
        }
        else if (same(part8Header, part8PixelsBlue, part8_bHeaderEx, part8_bPixelsEx) == false) {
            cout << "Part 8 Blue Failed" << endl;
        }

        // green:
        if (same(part8Header, part8PixelsGreen, part8_gHeaderEx, part8_gPixelsEx) == true) {
            cout << "Part 8 Green Passed" << endl;
        }
        else if (same(part8Header, part8PixelsGreen, part8_gHeaderEx, part8_gPixelsEx) == false) {
            cout << "Part 8 Green Failed" << endl;
        }

        // red:
        if (same(part8Header, part8PixelsRed, part8_rHeaderEx, part8_rPixelsEx) == true) {
            cout << "Part 8 Red Passed" << endl;
        }
        else if (same(part8Header, part8PixelsRed, part8_rHeaderEx, part8_rPixelsEx) == false) {
            cout << "Part 8 Red Failed" << endl;
        }

        // part 9:
        if (same(layer_redHeader, layer_redPixels, part9HeaderEx, part9PixelsEx) == true) {
            cout << "Part 9 Passed" << endl;
        }
        else if (same(part8Header, part8PixelsBlue, part9HeaderEx, part9PixelsEx) == false) {
            cout << "Part 9 Failed" << endl;
        }

        // part 10:
        if (same(text2Header, text2Pixels, part10HeaderEx, part10PixelsEx) == true) {
            cout << "Part 10 Passed" << endl;
        }
        else if (same(text2Header, text2Pixels, part10HeaderEx, part10PixelsEx) == false) {
            cout << "Part 10 Failed" << endl;
        }
}