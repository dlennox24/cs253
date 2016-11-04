#include <iostream>
#include <cstdlib>
using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::string;
#include <fstream>
using std::ifstream;

#include <image.h>
#include <histogram.h>
#include <data.h>
#include <perceptron.h>

int classNum(string fname){
	string classNum = "";
	const char* fnameChar = fname.c_str();
	unsigned int start = 0;
	unsigned int stop = 0;
	unsigned int i=0;
	if(fnameChar[0] == 'c' && fnameChar[1] == 'l' && fnameChar[2] == 'a'
	&& fnameChar[3] == 's' && fnameChar[4] == 's'){
		start = 5;
		i=5;
		while(fnameChar[i] != '_' || fname.size() > i){
			if(fnameChar[i] == '_'){
				stop = i;
				break;
			}
			i++;
		}
		if(start > stop){
			cerr<<"Invalid image filename"<<endl;
			return -1;
		}
		i=start;
		while(i<stop){
			classNum += fnameChar[i];
			i++;
		}
		return atoi(classNum.c_str());
	}
	cerr<<"Invalid image filename"<<endl;
	return -1;
}

int main(int argc, char* argv[]){
	if(argc != 3){
		cerr << "Invalid number of arguments!" << endl;
		cerr << "Usage: " << argv[0] << " <filename> <n>" << endl;
		return -1;
	}
	if(atoi(argv[2]) < 0){
		cerr<<"N must be > -1"<<endl;
		return -1;
	}
	// if(atoi(argv[3])<1 || atoi(argv[3])>4){
	// 	cerr<<"Invalid compareType: "<<argv[3]<<endl;
	// 	return -1;
	// }

	vector<Image*>* images = new vector<Image*>();
	//*********************************
	// Read
	ifstream istr(argv[1]);
	if(istr.fail()){
		cerr << "Error reading file: "<< argv[1] << endl;
		return false;
	}
	// Check that file is not empty
	if(istr.eof()){
		cerr << argv[1] << " is empty!" << endl;
		return -1;
	}

	string in;
	while(true){
		istr >> in;
		if(istr.eof()){
			break;
		}
		if(istr.fail()){
			cerr << argv[1] <<": Error reading data " << endl;
			return -1;
		}else{
			images->push_back(new Image());
			if(!images->at(images->size()-1)->Read(in.c_str())){
				return -1;
			}
		}
	}
	// Data data;
	// if(!data.Read(argv[1])){
	// 	return -1;
	// }
	// cout<<"testMAIN"<<endl;
	//
	Perceptron* robot = new Perceptron();
	for(unsigned int j=0;j<100;j++){
		for(unsigned int i=0;i<images->size();i++){
			int fname = classNum(images->at(i)->Fname());
			int d = -1;
			if(fname == atoi(argv[2])){
				d = 1;
			}
			robot->Update(images->at(i)->Hist(),d);
		}
	}
	robot->Print();
	images->clear();
	delete robot;
	// for(unsigned int i=0;i<images->size();i++){
	// 	delete images->at(i);
	// }
	delete images;
	return 0;
}
