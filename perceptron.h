#ifndef PERCEPTRON_H_INCLUDE
#define PERCEPTRON_H_INCLUDE

#include <histogram.h>

class Perceptron{
public:
   Perceptron();
   ~Perceptron();
   double ComputeY(Histogram& imageHist);
   void Update(Histogram& imageHist, int d);
   inline double WeightAt(int i) {return weights[i];}
   inline void SetWeight(int i, double value) {weights[i] = value;}
   inline double Bias(){return bias;}
   inline void SetBias(double value){bias = value;}
   inline int ClassNum(){return classNum;}
   inline void SetClassNum(int value){classNum = value;}
   void Print();
private:
   double bias;
   double* weights;
   int classNum;
};
#endif // PERCEPTRON_H_INCLUDE
