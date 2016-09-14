#include <histogram.h>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::string;

int main(int argc, char* argv[]){
   if(argc != 3){
      cerr << "Invalid number of arguments!" << endl;
      cerr << "Usage: " << argv[0] << " filename1 filename2" << endl;
      return -1;
   }

   //determine if read failed so main can return -1;
   int success;
   //Proccess first file
   Histogram hist1;
   success = hist1.read(argv[1]);
   if(success == -1){
      return -1;
   }
   // hist1.print(cout);
   hist1.normalize();
   // hist1.print(cout);

   //Proccess second file
   Histogram hist2;
   success = hist2.read(argv[2]);
   if(success == -1){
      return -1;
   }
   hist2.normalize();
   // hist2.print(cout);
   double compare = hist1.multCompare(hist2);
   cout << compare << endl;

   return 0;
}
