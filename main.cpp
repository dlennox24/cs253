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

	vector<Image*> images;
	string filename;
	while(true){
		istr >> filename;
		if(istr.eof()){
			break;
		}
		if(istr.fail()){
			cerr << "An error occured while reading the file" << endl;
			return -1;
		}else{
			Image* image = new Image;
			images.push_back(image);
			if(image->read(filename.c_str())==-1){
				return -1;
			}
		}
	}

	if(images.size()<2){
		cerr << "There must be at least 2 filenames in " << argv[1] << endl;
		return -1;
	}else{
		for(unsigned int i=0;i<images.size();i++){
			string mostSimilar;
			double similarityError = 0.0;
			for(unsigned int j=0;j<images.size();j++){
				if(i != j){
					double compare = images.at(i)->getHist().addMinCompare(images.at(j)->getHist());
					if(compare >= similarityError){
						mostSimilar = images.at(j)->getFname();
						similarityError = compare;
					}
				}
			}
			cout<<images.at(i)->getFname()<<" "<<mostSimilar<<" "<<similarityError<<endl;
		}
	}

	// // Free all images data
	// for(unsigned int i=0;i<images.size();i++){
	// 	delete images.at(i);
	// }
	return 0;
}
