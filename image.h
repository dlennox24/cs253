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
   // Image(const Image &imageObj);
   ~Image();
   // reads a file and attempts to add image data
   int read(const char* filename);
	inline int& width(){return width;}
	inline int& height(){return height;}
	inline int& maxVal(){return maxVal;}
	inline string& fname(){return fname;}
	inline vector<int>& pixels(){return pixels;}
	inline Histogram& hist(){return Hist;}
   inline int getPixel(int i) const {return pixels.at(i);}
   inline void addPixel(int pixel) {pixels.push_back(pixel);}
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
