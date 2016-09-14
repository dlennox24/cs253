#ifndef HISTOGRAM_H_INCLUDE
#define HISTOGRAM_H_INCLUDE

#include<iostream>
#include<fstream>
using std::istream;
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;

class Histogram{
public:
   Histogram(){
      this->buckets = new double[64];
      this->totalNodes = 0;
   }
   // reads a file anc attempts to create a histogram
   int read(char* filename);

   // Normalizes the historgram
   //** Divides each bucket by the totalNodes to get
   //** the percent of total elements in that bucket
   void normalize();

   // Multiplies hist1[0..63]*hist2[0..63] and adds those
   //** values together
   double multCompare(const Histogram& hist);

   // Prints out the value of each bucket
   bool print(ostream& ostr);

   // Increments the count for buckets[i]
   void increment(int i);

   // Return the value in the bucket[i]
   inline double getBucket(int i) const {return this->buckets[i];}

   // Return the total number of nodes
   inline int getTotalNodes() const {return this->totalNodes;}

   // Set the value in the bucket[i]
   inline void setBucket(int i, double value) {this->buckets[i] = value;}

private:
   // Buckets are [0-3],[4-7], ... ,[252-255]
   //** Each bucket counts the number of values from the input file that were in
   //** the range of the bucket's range.
   double* buckets;

   // Total number of values accross all buckets
   int totalNodes;
};

#endif // HISTOGRAM_H_INCLUDE
