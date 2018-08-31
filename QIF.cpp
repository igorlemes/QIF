#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <limits>

bool isDistribution(std::vector<long double> numberVector){
    long double totalSum = 0;
    for (size_t i = 0; i < numberVector.size(); i++){
        totalSum += numberVector[i];
        printf("Iterate\n");
    }   
    if (totalSum <= (long double) 1.0000000000000001 and totalSum >= (long double) 0.9999999999999999){
        return true;
    } else {
        return false;
    }
}

int main(){
    std::vector<long double> probability = {1.0/3.0, 1.0/3.0, 1.0/3.0};
    typedef std::numeric_limits< double > dbl;
    std::cout.precision(dbl::max_digits10);
    
    std::cout << "Probability 1:" <<  probability[0] << std::fixed << "\tProbability 2:" << probability[1] << std::fixed <<  std::endl;
    if (isDistribution(probability)) {
        printf("Is probability\n");
    } else {
        printf("Is not a probability\n");
    }
    
}