#include <cluster.h>

Cluster::Cluster(){
	images = new vector<Image*>();
	hist = new Histogram();
}

Cluster::~Cluster(){
	// cout<<"DESTROYING CLUSTER"<<endl;
	for(unsigned int i=0;i<images->size();i++){
		delete images->at(i);
	}
	delete images;
	images = NULL;
	delete hist;
	hist = NULL;
}

void Cluster::RecalcHist(){
	for(unsigned int i=0;i<64;i++){
		double clusterBucketSumAvg = 0.0;
		for(unsigned int j=0;j<this->Images().size();j++){
			clusterBucketSumAvg += this->ImageAt(j).Hist().Bucket(i);
		}
		this->Hist().SetBucket(i,(clusterBucketSumAvg/this->Images().size()));
	}
}

void Cluster::Print(){
	for(unsigned int i=0;i<this->Images().size();i++){
		cout<<this->ImageAt(i).Fname()<<" ";
	}
	cout<<endl;
}
