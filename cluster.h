#ifndef CLUSTER_H_INCLUDE
#define CLUSTER_H_INCLUDE

#include <iostream>
#include <fstream>
using std::istream;
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

#include <histogram.h>
#include <image.h>

class Cluster{
public:
   Cluster();
   ~Cluster();
   inline vector<Image*>& Images(){return *images;}
   inline Image& ImageAt(int i){return *images->at(i);}
   inline Histogram& Hist(){return *hist;}
   void RecalcHist();
   void Print();
private:
   vector<Image*>* images;
   Histogram* hist;
};
#endif // CLUSTER_H_INCLUDE
