#ifndef DATA_H_INCLUDE
#define DATA_H_INCLUDE

#include <iostream>
#include <fstream>
using std::istream;
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

#include <cluster.h>

class Data{
public:
   Data();
   bool Read(const char* filename); // reads a file and attempts to create cluster data
	inline int& K(){return k;}
	inline vector<Cluster>& Clusters(){return clusters;}
private:
   int k; // K is the target number of clusters
   vector<Cluster> clusters;
};
#endif // DATA_H_INCLUDE
