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
   while(true){
      istr >> in;
      if(istr.eof()){
         break;
      }

      if(istr.fail()){
         cerr << in << "All values must be integers!" << endl;
         return -1;
      }else if(in > 255 || in < 0){
         cerr << in << ": All values must be in the range 0-255!" << endl;
         return -1;
      }else{
         cout << "Value: [" << in << "]" << endl;
         cout << "-----------" << endl;
      }
   }

   return 0;
}
