#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::string;
#include <fstream>
using std::ifstream;

#include <image.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		cerr << "Invalid number of arguments!" << endl;
		cerr << "Usage: " << argv[0] << " filename" << endl;
		return -1;
	}

	ifstream istr(argv[1]);
	// Checks that file is accessable and valid
	if(istr.fail()){
		cerr << "Error reading file: "<< argv[1] << endl;
		return -1;
	}
	// Checks that file is not empty
	if(istr.eof()){
		cerr << argv[1] << " is empty!" << endl;
		return -1;
	}

	int numFiles = 0;
	string filename;
	while(true){
		istr >> filename;
		if(istr.eof()){
			break;
		}
		if(istr.fail()){
			cerr << "1: An error occured while reading the file" << endl;
			return -1;
		}
		numFiles++;
	}

	ifstream istr2(argv[1]);
	Image* images = new Image[numFiles];
	cout<<"*********************"<<endl;
	for(int i=0;i<numFiles;i++){
		istr2 >> filename;
		if(istr.eof()){
			break;
		}
		if(istr.fail()){
			cerr << "An error occured while reading the file" << endl;
			return -1;
		}else{
			images[i].read(filename.c_str());
		}
	}
	if(numFiles<2){
		cerr << "There must be at least 2 filenames in " << argv[1] << endl;
		return -1;
	}else{
		for(int i=0;i<numFiles;i++){
			string mostSimilar;
			double similarityError = 0.0;
			for(int j=0;j<numFiles;j++){
				if(i != j){
					double compare = images[i].getHist().addMinCompare(images[j].getHist());
					if(compare >= similarityError){
						mostSimilar = images[j].getFname();
						cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
					}
				}
			}
			cout<<"^^^^^^^^^789789^^^^^^^^^^^^^^^^^^^"<<endl;
		}
	}
	cout<<"----------------------"<<endl;

	// // Free all images data
	// for(unsigned int i=0;i<images.size();i++){
	// 	delete images.at(i);
	// }
	return 0;
}
