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
#include <vector>
using std::vector;
#include <histogram.h>

class Image{
public:
   Image();
   bool Read(const char* filename); // reads a file and attempts to add image data
	inline int& Width(){return width;}
	inline int& Height(){return height;}
	inline int& MaxVal(){return maxVal;}
	inline string& Fname(){return fname;}
	inline vector<int>& Pixels(){return pixels;}
	inline Histogram& Hist(){return hist;}
   inline int Pixel(int i) const {return pixels.at(i);}
   inline void AddPixel(int pixel) {pixels.push_back(pixel);}
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
