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

   Histogram hist1;
   Histogram hist2;
   // Read files and check for errors
   if(hist1.read(argv[1]) == -1 || hist2.read(argv[2]) == -1){
      return -1;
   }

   // Check that total pixels == w*h for both files
   if(hist1.getPixelsSize() != (hist1.getWidth()*hist1.getHeight())
   || hist2.getPixelsSize() != (hist2.getWidth()*hist2.getHeight())){
      cerr << "Number of pixels does not match size parameters: " << endl;
      cerr << "File 1: " << hist1.getPixelsSize() << " ?= " << hist1.getWidth()*hist1.getHeight() << endl;
      cerr << "File 2: " << hist2.getPixelsSize() << " ?= " << hist2.getWidth()*hist2.getHeight() << endl;
      return -1;
   }

   // Check w*h is the same for both files
   if((hist1.getWidth()*hist1.getHeight()) != (hist2.getWidth()*hist2.getHeight())){
      cerr << "Files are of different sizes" << endl;
      cerr << (hist1.getWidth()*hist1.getHeight()) << " != " << (hist2.getWidth()*hist2.getHeight()) << endl;
      return -1;
   }

   hist1.normalize();
   hist2.normalize();

   // Compare the Histograms
   double compare = hist1.addMinCompare(hist2);
   int sqDiff = hist1.sqDiffCompare(hist2);
   cout << compare << " " << sqDiff << endl;

   return 0;
}
