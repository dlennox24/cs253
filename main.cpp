#include <Histogram.h>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::string;
#include <fstream>
using std::ifstream;
#include <math.h>

int main(int argc, char* argv[]){
   if(argc != 2){
      cerr << "Invalid number of arguments!" << endl;
      cerr << "Usage: " << argv[0] << " filename" << endl;
      return -1;
   }

   ifstream istr(argv[1]);
   if(istr.fail()){
      cerr << "Error reading file: "<< argv[1] << endl;
      return -1;
   }

   //Check to ensure the file name is a .txt
   string filename(argv[1]); //convert char* to string
   //substring of filename after "."
   string filetype(filename.substr(filename.find("."),filename.length()));
   if(filetype.compare(".txt") != 0){
      cerr << "File must be of the type .txt" << endl;
      return -1;
   }

   int in;
   bool emptyFile = true;
   Histogram valueCount;
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
         valueCount.increment(floor(in/4));
         // cout << "Value: [" << in << "]" << endl;
         // cout << "-----------" << endl;
      }
   }

   if(emptyFile){
      cerr << "File is empty!" << endl;
      return -1;
   }

   valueCount.print(cout);

   return 0;
}
