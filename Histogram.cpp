#include <Histogram.h>


bool Histogram::print(ostream& ostr){
   if(ostr.fail()){
      return false;
   }
   for(int i=0;i<64;i = i+4){
      cout << bucket(i) << " " << bucket(i+1) << " "
      << bucket(i+2) << " " << bucket(i+3) << endl;
   }
   return true;
}

void Histogram::increment(int i){
   // std::cout << "print :" << bucket(i) << std::endl;
   buckets[i]++;
}
