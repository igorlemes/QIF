#include <iostream>
#include <vector>
#include <string>
#include <array>

bool isDistribution(long double numberVector[]){
    long double totalSum = 0;
    int numberElements = sizeof(*numberVector);
    printf("numberElements1: %i \n", numberElements);

    numberElements = long double(numberElements) / sizeof(long double);
    printf("numberElements2: %i \n", numberElements);
    for (size_t i = 0; i < numberElements; i++){
        totalSum += numberVector[i];
        printf("Iterate");
    }   
    if (totalSum == 1.000000000000000){
        return true;
    } else {
        return false;
    }
}
int main(){
    long double probability[3];
    probability[1] = 1/3;
    probability[2] = 1/3;
    probability[3] = 1/3;

    printf("Probability 1: %i, Probabilty 2: %i \n", probability[0], probability[1]);
    if (isDistribution(probability)) {
        printf("Is probability\n");
    } else {
        printf("Is not a probability\n");
    }
    
}