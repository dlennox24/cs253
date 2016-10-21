#include <iostream>
#include <fstream>
using std::istream;
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;

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
		cerr << "Error reading file(data.cpp): "<< filename << endl;
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
