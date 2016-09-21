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
   totalNodes = 0;
   width = 0;
   height = 0;
   maxVal = 0;

   for(int i=0;i<64;i++){
      buckets[i]=0;
   }
}
Histogram::~Histogram(){
   delete buckets;
}

int Histogram::read(char* filename){
   ifstream istr(filename);
   if(istr.fail()){
      cerr << "Error reading file: "<< filename << endl;
      return -1;
   }

   // Check that file is not empty
   if(istr.eof()){
      cerr << filename << " is empty!" << endl;
      return -1;
   }

   // Check that format of first line is
   // P2 <height> <width> <maxLegalPixelValue>
   char charP, char2;
   int w, h, maxVal;
   istr.get(charP);
   istr.get(char2);
   if(istr.fail() || charP != 'P' || char2 != '2'){
      cerr << filename << ": The first two values of the file must be P2" << endl;
      return -1;
   }
   istr >> w >> h >> maxVal;
   if(istr.fail() || w < 1 || h < 1 || maxVal != 255){
      cerr << filename << ": Must have a width and height greater than 0 followed" << endl
      << "by the max pixel value of 255" << endl
      << "\twidth: " << w << endl
      << "\theight: " << h << endl
      << "\tmaxVal: " << maxVal << endl;
      return -1;
   }else{
      setWidth(w);
      setHeight(h);
      setMaxVal(maxVal);
   }
   // cout << filename << endl << charP << char2 << " " << w << " " << h << " " << maxVal << endl;
   int in;
   while(true){
      istr >> in;
      if(istr.eof()){
         break;
      }
      if(istr.fail()){
         cerr << "All pixel values must be integers!" << endl;
         return -1;
      }else if(in > 255 || in < 0){
         cerr << in << ": All pixel values must be in the range 0-255!" << endl;
         return -1;
      }else{
         //increment the count of the bucket with the index floor(in/4)
         increment(floor(in/4));
         addPixel(in);
      }
   }
   return 0;
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
