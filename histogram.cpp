#include <histogram.h>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::string;
#include <fstream>
using std::ifstream;
#include <math.h>

int Histogram::read(char* filename){
   //Check to ensure the file name is a .txt
   string file(filename); //convert char* to string
   //substring of filename after "." to get the file extention
   string filetype(file.substr(file.find("."),file.length()));
   if(filetype.compare(".txt") != 0){
      cerr << "File must be of the type <.txt>" << endl;
      return -1;
   }

   ifstream istr(filename);
   if(istr.fail()){
      cerr << "Error reading file: "<< filename << endl;
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
         cerr << in << ": All values must be integers!" << endl;
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
      cerr << "File is empty!" << endl;
      return -1;
   }
   return 0;
}

void Histogram::normalize(){
   for(int i=0;i<64;i++){
      double value = this->getBucket(i)/this->getTotalNodes();
      this->setBucket(i,value);
   }
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
