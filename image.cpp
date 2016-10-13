#include <image.h>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::string;
#include <fstream>
using std::ifstream;
#include <math.h>

Image::Image(){
	width = 0;
	height = 0;
	maxVal = 0;
}

bool Image::Read(const char* filename){
	this->Fname() = filename;
	ifstream istr(filename);
	if(istr.fail()){
		cerr << "Error reading file: "<< filename << endl;
		return false;
	}

	// Check that file is not empty
	if(istr.eof()){
		cerr << filename << " is empty!" << endl;
		return false;
	}

	// Check that format of first line is
	// P2 <height> <width> <maxLegalPixelValue>
	char charP, char2;
	int w, h, maxVal;
	istr.get(charP);
	istr.get(char2);
	if(istr.fail() || charP != 'P' || char2 != '2'){
		cerr << filename << ": The first two values of the file must be P2" << endl;
		return false;
	}

	// Populate dimensions of image
	istr >> w >> h >> maxVal;
	if(istr.fail() || w < 1 || h < 1 || maxVal != 255){
		cerr << filename << ": Must have a width and height greater than 0 followed" << endl
		<< "by the max pixel value of 255" << endl
		<< "\twidth: " << w << endl
		<< "\theight: " << h << endl
		<< "\tmaxVal: " << maxVal << endl;
		return false;
	}else{
		this->Width() = w;
		this->Height() = h;
		this->MaxVal() = maxVal;
	}

	int in;
	while(true){
		istr >> in;
		if(istr.eof()){
			break;
		}
		if(istr.fail()){
			cerr << filename <<": All pixel values must be integers!" << endl;
			return false;
		}else if(in > 255 || in < 0){
			cerr << in << ": All pixel values must be in the range 0-255!" << endl;
			return false;
		}else{
			// Increment the count of the bucket in the histogram of the image
			hist.Increment(floor(in/4));
			// Add pixel to the pixels vector
			this->AddPixel(in);
		}
	}
	hist.Normalize();
	return true;
}
