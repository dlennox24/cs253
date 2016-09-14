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

int Histogram::read(char* filename){
   ifstream istr(filename);
   if(istr.fail()){
      cerr << "Error reading file: "<< filename << endl;
      return -1;
   }

   //Check to ensure the file name is a .txt
   string file(filename); //convert char* to string
   //substring of filename after "." to get the file extention
   string filetype(file.substr(file.find("."),file.length()));
   if(filetype.compare(".txt") != 0){
      cerr << filename <<" must be of the type <.txt>" << endl;
      return -1;
   }

   int in;
   bool emptyFile = true;
   while(true){
      istr >> in;
      if(istr.eof()){
         break;
      }

      if(istr.fail()){
         cerr << ": All values must be integers!" << endl;
         return -1;
      }else if(in > 255 || in < 0){
         cerr << in << ": All values must be in the range 0-255!" << endl;
         return -1;
      }else{
         emptyFile = false;
         //increment the count of the bucket with the index floor(in/4)
         this->increment(floor(in/4));
      }
   }

   if(emptyFile){
      cerr << filename << " is empty!" << endl;
      return -1;
   }
   return 0;
}

void Histogram::normalize(){
   double value;
   for(int i=0;i<64;i++){
      // cout<<"------"<<i<<"----------"<<endl;
      // cout<<this->getBucket(i)<<endl;
      // cout<<this->getTotalNodes()<<endl;
      // cout<<this->getBucket(i)/this->getTotalNodes()<<endl;
      // cout<<"----------------"<<endl;
      value = this->getBucket(i)/this->getTotalNodes();
      // cout<<i<<": "<<value<<endl;
      this->setBucket(i,value);
   }
   cout<<" ";
}

double Histogram::multCompare(const Histogram& hist){
   double compareValue = 0.0;
   // cout<<hist.getBucket(18)<<endl;
   for(int i=0;i<64;i++){
      if(i==18){
         // cout<<"------id: "<<i<<" --------"<<endl;
         // cout << this->getBucket(i) << endl;
         // cout << hist.getBucket(i) << endl;
         // cout << (this->getBucket(i)*hist.getBucket(i)) << endl;
         // cout << compareValue + (this->getBucket(i)*hist.getBucket(i)) << endl;
         // cout<<"--------------"<<endl;
      }
      compareValue += (this->getBucket(i)*hist.getBucket(i));
   }
   return compareValue;
}

bool Histogram::print(ostream& ostr){
   if(ostr.fail()){
      return false;
   }
   for(int i=0;i<64;i = i+4){
      cout << this->getBucket(i) << "\t" << this->getBucket(i+1) << "\t"
      << this->getBucket(i+2) << "\t" << this->getBucket(i+3) << endl;
   }
   return true;
}

void Histogram::increment(int i){
   buckets[i]++;
   totalNodes++;
}
