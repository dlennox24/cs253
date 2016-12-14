#include <iostream>
#include <cstdlib>
using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::string;
#include <fstream>
using std::ifstream;
#include <sstream>
#include <algorithm>
using std::find;
#include <cmath>

#include <image.h>
#include <histogram.h>
#include <data.h>
#include <perceptron.h>

int extractClassNum(string fname){
	const char* fnameChar = fname.c_str();
	unsigned int i=0;
	while(i<fname.length()){
		if(fnameChar[i] == 'c'){
			i++;
			if(fnameChar[i] == 'l'){
				i++;
				if(fnameChar[i] == 'a'){
					i++;
					if(fnameChar[i] == 's'){
						i++;
						if(fnameChar[i] == 's'){
							i++;
							string classNum = "";
							while(i<fname.length()){
								classNum += fnameChar[i];
								i++;
								if(fnameChar[i] == '_'){
									break;
								}
							}
							return atoi(classNum.c_str());
						}
					}
				}
			}
		}
		i++;
	}
	cerr<<"Invalid image filename: "<<fname<<endl;
	return -1;
}

int main(int argc, char* argv[]){
	if(argc != 4){
		cerr << "Invalid number of arguments!" << endl;
		cerr << "Usage: " << argv[0] << " <filename> <filename> <k>" << endl;
		return -1;
	}

	if(atoi(argv[3]) < 1){
		cerr<<"K must be > 1"<<endl;
		return -1;
	}

	vector<Image*>* images = new vector<Image*>();
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

	vector<Perceptron*>* robots = new vector<Perceptron*>();
	vector<int>* classes = new vector<int>();
	for(unsigned int i=0; i<images->size();i++){
		int classNum = extractClassNum(images->at(i)->Fname());
		if(find(classes->begin(),classes->end(), classNum) != classes->end()){
			// perceptron for that class already exists
		}else{
			robots->push_back(new Perceptron());
			robots->at(robots->size()-1)->SetClassNum(classNum);
		}
	}

	if(robots->size()<2){
		cerr<<"Training file must contain 2 distinct classes"<<endl;
		return -1;
	}

	for(unsigned int k = 0; k < robots->size(); k++) {
		for(unsigned int j=0;j<100;j++){
			for(unsigned int i=0;i<images->size();i++){
				int classNum = extractClassNum(images->at(i)->Fname());
				if(classNum == -1){
					return -1;
				}
				int d = -1;
				if(classNum == robots->at(k)->ClassNum()){
					d = 1;
				}
				// cout<<d<<endl;
				robots->at(k)->Update(images->at(i)->Hist(),d);
			}
		}
	}
	Data data;
	data.K() = atoi(argv[3]);
	if(!data.Read(argv[2], atoi(argv[3]))){
		return -1;
	}

	while(data.Clusters().size()>(unsigned)data.K()){
		int in = -1;
		int from = -1;
		double difference = -1.0;
		for(unsigned int i=0;i<data.Clusters().size();i++){
			unsigned int j=i+1;
			while(j<data.Clusters().size()){
				double compare = -1.0;
				for(unsigned int k=0; k<robots->size();k++){
					compare += 1/pow((robots->at(k)->ComputeY(data.ClusterAt(i).Hist()) - robots->at(k)->ComputeY(data.ClusterAt(j).Hist())),2);
				}
				// cout<<"\t"<<compare<<endl;
				if(compare > difference){
					in = i;
					from = j;
					difference = compare;
				}
				// cout<<i<<"--"<<j<<":"<<compare<<endl;
				j++;
			}
		}
		// cout<<"================================="<<endl;
		// data.ClusterAt(in).Print();
		// cout<<"^"<<endl;
		// data.ClusterAt(from).Print();
		// cout<<"MERGE: "<<in<<","<<from<<"\tdiff: "<<difference
		// <<"\n  size: "<<data.Clusters().size()<<"\tk: "<<data.K()
		// <<"\n================================="<<endl;
		data.Merge(in,from);
	}

	data.Print();

	images->clear();
	robots->clear();
	classes->clear();
	delete robots;
	delete classes;
	delete images;
	return 0;
}
