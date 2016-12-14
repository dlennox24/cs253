#include <perceptron.h>

Perceptron::Perceptron(){
	weights = new double[64];
	for(int i=0;i<64;i++){
		weights[i]=0.0;
	}
	bias = 0.0;
}

Perceptron::~Perceptron(){
	delete [] weights;
   weights = NULL;
}

double Perceptron::ComputeY(Histogram& imageHist){
	// y = b + sum0-63(w[i]*h[i])
	double y = 0.0;
	for(unsigned int i=0;i<64;i++){
		y += WeightAt(i) * imageHist.Bucket(i);
	}
	y += Bias();
	return y;
}

void Perceptron::Update(Histogram& imageHist, int d){
	// y = b + sum0-63(w[i]*h[i])
	double y = ComputeY(imageHist);

	for(unsigned int i=0;i<64;i++){
		// wi = wi + (d - y) * hi
		SetWeight(i,WeightAt(i)+((d-y)*imageHist.Bucket(i)));
	}
	// b = b + (d - y)
	SetBias(Bias()+(d-y));
}

void Perceptron::Print(){
	for(unsigned int i=0;i<64;i++){
		cout<<this->WeightAt(i)<<" ";
	}
	cout<<this->bias<<endl;
}
