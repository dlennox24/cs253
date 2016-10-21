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

int main(int argc, char* argv[]){
	if(argc != 4){
		cerr << "Invalid number of arguments!" << endl;
		cerr << "Usage: " << argv[0] << " <filename> <k> <compareType>" << endl;
		return -1;
	}
	if(atoi(argv[2]) < 1){
		cerr<<"K must be >0"<<endl;
		return -1;
	}
	if(atoi(argv[3])<1 || atoi(argv[3])>3){
		cerr<<"Invalid compareType: "<<argv[3]<<endl;
		return -1;
	}

	Data data;
	data.K() = atoi(argv[2]);
	if(!data.Read(argv[1], atoi(argv[2]))){
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
				switch (atoi(argv[3])) {
					case 1:
					compare = data.ClusterAt(i).Hist().SumMinCompare(data.ClusterAt(j).Hist());
					break;
					case 2:
					compare = data.ClusterAt(i).Hist().SumMinCompare(data.ClusterAt(j).Hist());
					break;
					case 3:
					compare = data.ClusterAt(i).Hist().SumMinCompare(data.ClusterAt(j).Hist());
				}
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
		// data.ClusterAt(from).Print();
		// cout<<"MERGE: "<<in<<","<<from<<"\tdiff: "<<difference
		// <<"\n  size: "<<data.Clusters().size()<<"\tk: "<<data.K()
		// <<"\n================================="<<endl;
		data.Merge(in,from);
	}

	data.Print();
	return 0;
}
