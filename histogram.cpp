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
   totalNodes = 0;
   buckets = new double[64];
   for(int i=0;i<64;i++){
      buckets[i]=0;
   }
}
Histogram::~Histogram(){
   delete [] buckets;
	buckets = NULL;
}

void Histogram::Normalize(){
   for(int i=0;i<64;i++){
      this->SetBucket(i,this->Bucket(i)/this->TotalNodes());
   }
}

// int Histogram::sqDiffCompare(const Histogram& hist){
//    int sqSum = 0;
//    for(int i=0;i<int(getPixelsSize());i++){
//       sqSum += pow((getPixel(i) - hist.getPixel(i)),2);
//    }
//    return sqSum;
// }

double Histogram::MultCompare(Histogram& hist){
   double compareValue = 0.0;
   for(int i=0;i<64;i++){
      compareValue += (this->Bucket(i)*hist.Bucket(i));
   }
   return compareValue;
}

double Histogram::AddMinCompare(Histogram& hist){
   double compareValue = 0.0;
   for(int i=0;i<64;i++){
      if(this->Bucket(i)>hist.Bucket(i)){
         compareValue += hist.Bucket(i);
      }else{
         compareValue += this->Bucket(i);
      }
   }
   return compareValue;
}

bool Histogram::Print(ostream& ostr){
   if(ostr.fail()){
      return false;
   }
   for(int i=0;i<64;i = i+4){
      cout << this->Bucket(i) << "\t" << this->Bucket(i+1) << "\t"
      << this->Bucket(i+2) << "\t" << this->Bucket(i+3) << endl;
   }
   return true;
}

void Histogram::Increment(int i){
   buckets[i]++;
   this->TotalNodes() += 1;
}
