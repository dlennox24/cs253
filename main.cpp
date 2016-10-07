#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::string;
#include <fstream>
using std::ifstream;

// #include <image.h>

int main(int argc, char* argv[]){
	// if(argc != 2){
	// 	cerr << "Invalid number of arguments!" << endl;
	// 	cerr << "Usage: " << argv[0] << " filename" << endl;
	// 	return -1;
	// }
	//
	// ifstream istr(argv[1]);
	// // Checks that file is accessable and valid
	// if(istr.fail()){
	// 	cerr << "Error reading file: "<< argv[1] << endl;
	// 	return -1;
	// }
	// // Checks that file is not empty
	// if(istr.eof()){
	// 	cerr << argv[1] << " is empty!" << endl;
	// 	return -1;
	// }
	//
	// vector<Image> images;
	// string filename;
	// while(true){
	// 	istr >> filename;
	// 	if(istr.eof()){
	// 		break;
	// 	}
	// 	if(istr.fail()){
	// 		cerr << "An error occured while reading the file" << endl;
	// 		return -1;
	// 	}else{
	// 		Image image;
	// 		// images.push_back(image);
	// 		// image.read(filename.c_str());
	// 	}
	// }
	// if(images.size()<2){
	// 	cerr << "There must be at least 2 filenames in " << argv[1] << endl;
	// 	return -1;
	// }

	return 0;
}
