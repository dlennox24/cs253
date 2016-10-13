#ifndef HISTOGRAM_H_INCLUDE
#define HISTOGRAM_H_INCLUDE

#include <iostream>
#include <fstream>
using std::istream;
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;

class Histogram{
public:
   Histogram();
   ~Histogram();

   // Normalizes the historgram
   //** Divides each bucket by the totalNodes to get
   //** the percent of total elements in that bucket
   void Normalize();
   // // Add all the squared difference of the pixel values
   // int sqDiffCompare(const Histogram& hist);
   // Multiplies hist1[0..63]*hist2[0..63] and adds those
   //** values together
   double MultCompare(Histogram& hist);
   // Adds all the minimum number between hist1[0..63] and hist2[0..63]
   // hist1 and hist2 must be normalized
   double AddMinCompare(Histogram& hist);
   // Prints out the value of each bucket
   bool Print(ostream& ostr);
   // Increments the count for buckets[i]
   void Increment(int i);
   // Return the value in the bucket[i]
   inline double& Bucket(int i) {return buckets[i];}
	// Set the value in the bucket[i]
	inline void SetBucket(int i, double value) {buckets[i] = value;}
   inline int& TotalNodes() {return totalNodes;}

private:
   // Buckets are [0-3],[4-7], ... ,[252-255]
   //** Each bucket counts the number of values from the input file that were in
   //** the range of the bucket's range.
   double* buckets;
	// Total number of values accross all buckets
   int totalNodes;
};
#endif // HISTOGRAM_H_INCLUDE
