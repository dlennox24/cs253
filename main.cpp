#include <histogram.h>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::string;
#include <fstream>
using std::ifstream;

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

   int in;
   istr >> in;
   if(istr.fail()){
      cerr << "Non-integer value found in input file!" << endl;
      cerr << "All values must be integers!" << endl;
      return -1;
   }

   return 0;
}
