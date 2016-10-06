#include <histogram.h>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::string;
#include <fstream>
using std::ifstream;
#include <math.h>

Histogram::Histogram(){
   buckets = new double[64];
   for(int i=0;i<64;i++){
      buckets[i]=0;
   }
}
Histogram::~Histogram(){
   delete buckets [];
	buckets = NULL;
}

void Histogram::normalize(){
   for(int i=0;i<64;i++){
      // cout<<"--------------------"<<i<<"--------------------"<<endl;
      // cout<<"Bucket: "<<getBucket(i)<<"\t"
      // <<"totalNodes: "<<getTotalNodes()<<"\t"
      // <<"b/tN: "<<getBucket(i)/getTotalNodes()<<endl;
      setBucket(i,getBucket(i)/getTotalNodes());
   }
}

int Histogram::sqDiffCompare(const Histogram& hist){
   int sqSum = 0;
   for(int i=0;i<int(getPixelsSize());i++){
      sqSum += pow((getPixel(i) - hist.getPixel(i)),2);
   }
   return sqSum;
}

double Histogram::multCompare(const Histogram& hist){
   double compareValue = 0.0;
   // cout<<hist.getBucket(18)<<endl;
   for(int i=0;i<64;i++){
      compareValue += (getBucket(i)*hist.getBucket(i));
   }
   return compareValue;
}

double Histogram::addMinCompare(const Histogram& hist){
   double compareValue = 0.0;
   for(int i=0;i<64;i++){
      if(getBucket(i)>hist.getBucket(i)){
         compareValue += hist.getBucket(i);
      }else{
         compareValue += getBucket(i);
      }
   }
   return compareValue;
}

bool Histogram::print(ostream& ostr){
   if(ostr.fail()){
      return false;
   }
   for(int i=0;i<64;i = i+4){
      cout << getBucket(i) << "\t" << getBucket(i+1) << "\t"
      << getBucket(i+2) << "\t" << getBucket(i+3) << endl;
   }
   return true;
}

void Histogram::increment(int i){
   buckets[i]++;
   totalNodes++;
}
