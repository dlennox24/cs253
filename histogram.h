#ifndef HISTOGRAM_H_INCLUDE
#define HISTOGRAM_H_INCLUDE

#include <iostream>
#include <fstream>
using std::istream;
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;
#include <vector>
using std::vector;

class Histogram{
public:
   Histogram();
   ~Histogram();

   // reads a file anc attempts to create a histogram
   int read(char* filename);
   // Normalizes the historgram
   //** Divides each bucket by the totalNodes to get
   //** the percent of total elements in that bucket
   void normalize();
   // Add all the squared difference of the pixel values
   int sqDiffCompare(const Histogram& hist);
   // Multiplies hist1[0..63]*hist2[0..63] and adds those
   //** values together
   double multCompare(const Histogram& hist);
   // Adds all the least number between hist1[0..63] and hist2[0..63]
   double addMinCompare(const Histogram& hist);
   // Prints out the value of each bucket
   bool print(ostream& ostr);
   // Increments the count for buckets[i]
   void increment(int i);
   // Return the value in the bucket[i]
   inline double getBucket(int i) const {return buckets[i];}
   // Return the total number of nodes
   inline int getTotalNodes() const {return totalNodes;}
   // Return the width of the image data
   inline int getWidth() const {return width;}
   // Return the height of the image data
   inline int getHeight() const {return height;}
   // Gets the max legal pixel value
   inline int getMaxVal() const {return maxVal;}
   // Gets the whole pixels vector
   inline vector<int> getPixels() const {return pixels;}
   // Gets a single pixel at index i from pixels vector
   inline int getPixel(int i) const {return pixels.at(i);}
   // Gets the size of the pixels vector
   inline int getPixelsSize() const {return pixels.size();}
   // Set the value in the bucket[i]
   inline void setBucket(int i, double value) {buckets[i] = value;}
   // Add a pixel to the vector pixels
   inline void addPixel(int pixel) {pixels.push_back(pixel);}
   // Set the width of the image data
   inline void setWidth(int val) {width = val;}
   // Set the height of the image data
   inline void setHeight(int val) {height = val;}
   // Set the max legal pixel value
   inline void setMaxVal(int val) {maxVal = val;}

private:
   // Buckets are [0-3],[4-7], ... ,[252-255]
   //** Each bucket counts the number of values from the input file that were in
   //** the range of the bucket's range.
   double* buckets;
   // Total number of values accross all buckets
   int totalNodes;
   // All the individual pixel values
   vector<int> pixels;
   // Size of the image data
   int width;
   int height;
   int maxVal;
};
#endif // HISTOGRAM_H_INCLUDE
