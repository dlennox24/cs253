#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::string;
#include <fstream>
using std::ifstream;

#include <image.h>
#include <histogram.h>

int main(int argc, char* argv[]){
	cout << "test.cpp-" << endl;
	cout << endl;

	Image image;
	image.Read(argv[1]);
	cout << image.Pixel(1000) << endl;
	image.Hist().Print(cout);
	return 0;
}
