#include <iostream>
#include <fstream>
using std::istream;
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;
#include <cstdlib>
#include <sstream>
using std::stringstream;
using std::string;

#include <data.h>

Data::Data(){
	clusters = new vector<Cluster*>();
	k = 0;
}

Data::~Data(){
	// cout<<"DESTROYING DATA"<<endl;
	for(unsigned int i=0;i<clusters->size();i++){
		delete clusters->at(i);
	}
	delete clusters;
	clusters = NULL;
}

bool Data::Read(const char* filename, int k){
	ifstream istr(filename);
	if(istr.fail()){
		cerr << "(Data::Read) Error reading file(data.cpp): "<< filename << endl;
		return false;
	}

	// Check that file is not empty
	if(istr.eof()){
		cerr << filename << " is empty!" << endl;
		return false;
	}

	string in;
	while(true){
		istr >> in;
		if(istr.eof()){
			break;
		}
		if(istr.fail()){
			cerr << filename <<": Error reading data " << endl;
			return false;
		}else{
			// this->Images().push_back(new Image());
			// cout<<"testDATA"<<endl;
			// return this->ImageAt(this->Images().size()-1).Read(filename);
			// Add a new cluster to the data object
			this->Clusters().push_back(new Cluster());
			// Get that new cluster and add an image to it
			this->Clusters().at(this->Clusters().size()-1)->Images().push_back(new Image());
			// Read the image file data into the image object; return false if image failed
			if(!this->Clusters().at(this->Clusters().size()-1)->Images().at(0)->Read(in.c_str())){
				return false;
			}
			// Re/Calc the histagram average
			this->Clusters().at(this->Clusters().size()-1)->RecalcHist();
		}
	}
	if((unsigned)k > this->Clusters().size()){
		cerr<<"K cannot be larger than the number of input files! K:"<<k;
		cerr<<" Files:"<<this->Clusters().size()<<endl;
		return false;
	}
	return true;
}

void Data::Merge(int in, int from){
	// cout<<this->Clusters().size()<<" (-1) ";
	for(unsigned int i=0;i<this->ClusterAt(from).Images().size();i++){
		this->ClusterAt(in).Images().push_back(&this->ClusterAt(from).ImageAt(i));
	}
	this->Clusters().erase(this->Clusters().begin()+from);
	// cout<<this->Clusters().size()<<endl;
}

void Data::Print(){
	for(unsigned int i=0;i<this->Clusters().size();i++){
		this->ClusterAt(i).Print();
	}
}

void Data::Quality(){
	double total = 0.0;
	double correct = 0.0;
	for(unsigned int i=0;i<this->Clusters().size();i++){
		vector<int> classes;
		vector<int> counts;
		for(unsigned int j=0;j<this->ClusterAt(i).Images().size();j++){
			string fname = this->ClusterAt(i).ImageAt(j).Fname();
			stringstream iss(fname);
			getline(iss, fname, '_');
			int classNum = fname.back() - '0';

			int pos = -1;
			for(unsigned int k=0;k<classes.size();k++){
				if(classes.at(k) == classNum){
					pos = k;
					// cout<<"pos:"<<pos<<endl;
					break;
				}
			}
			if(pos == -1){
				classes.push_back(classNum);
				counts.push_back(1);
			}else{
				counts.at(pos) = counts.at(pos) +1;
			}
		}

		int high = -1;
		for(unsigned int j=0;j<counts.size();j++){
			if(counts.at(j) > high){
				high = counts.at(j);
			}
			total += counts.at(j);
		}
		correct += high;
		// cout<<pos<<endl;
		// cout<<high<<endl<<"---"<<endl;
	}
	// cout<<"***************"<<endl;
	// cout<<total<<endl<<correct<<endl;
	double qual = correct/total;
	cout<<qual<<endl;
}
