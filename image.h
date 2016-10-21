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
   ~Image();
   bool Read(const char* filename); // reads a file and attempts to add image data
	inline int& Width(){return width;}
	inline int& Height(){return height;}
	inline int& MaxVal(){return maxVal;}
	inline string& Fname(){return fname;}
   inline void SetFname(string val) {fname=val;}
	inline vector<int>& Pixels(){return *pixels;}
	inline Histogram& Hist(){return *hist;}
   // Add all the squared difference of the pixel values
   // int AvgInvSqDiffCompare(Histogram& hist);
private:
   string fname; // Filename passed from arguments
   // Size of the image data
   int width;
   int height;
   int maxVal;
   vector<int>* pixels; // All the individual pixel values
   Histogram* hist; // historgram of image
};
#endif // IMAGE_H_INCLUDE
