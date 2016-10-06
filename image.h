#ifndef IMAGE_H_INCLUDE
#define IMAGE_H_INCLUDE

#include <iostream>
#include <fstream>
using std::istream;
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
#include <vector>;
using std::vector;
#include <histogram.h>

class Image{
public:
   Image();
   ~Image();
	// reads a file and attempts to add image data
   int read(char* filename);
   // Return the width of the image data
   inline int getWidth() const {return width;}
   // Return the height of the image data
   inline int getHeight() const {return height;}
   // Gets the max legal pixel value
   inline int getMaxVal() const {return maxVal;}
   // Gets the whole pixels vector
   inline vector<int> getPixels() const {return pixels;}
	// Gets the whole pixels vector
   inline Histogram getHist() const {return hist;}
   // Gets a single pixel at index i from pixels vector
   inline int getPixel(int i) const {return pixels.at(i);}
   // Add a pixel to the vector pixels
   inline void addPixel(int pixel) {pixels.push_back(pixel);}
   // Set the width of the image data
   inline void setWidth(int val) {width = val;}
   // Set the height of the image data
   inline void setHeight(int val) {height = val;}
   // Set the max legal pixel value
   inline void setMaxVal(int val) {maxVal = val;}
private:
   // Filename passed from arguments
	string fname;
	// Size of the image data
   int width;
   int height;
   int maxVal;
   // All the individual pixel values
   vector<int> pixels;
	// historgram of image
	Histogram hist;
};
#endif // IMAGE_H_INCLUDE
