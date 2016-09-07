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
      buckets = new int[64];
   }

   //Prints out the value of each bucket
   bool print(ostream& ostr);
   //Increments the count for buckets[i]
   void increment(int i);
   //Return the value in the bucket
   inline int bucket(int i) {return buckets[i];}

private:
   //Buckets are [0-3],[4-7], ... ,[252-255]
   // Each bucket counts the number of values from the input file that were in
   // the range of the bucket's range.
   int* buckets;
};

#endif // HISTOGRAM_H_INCLUDE
