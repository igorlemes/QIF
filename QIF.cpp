#include <iostream>
#include <vector>
#include <string>
#include <array>

// Biblioteca necessária para imprimir a precisão dos long double
#include <limits>

// Biblioteca para facilitar as operaçoes utilizando matrizes
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

// Definindo um tipo de dado para a imprimir a precisão
typedef std::numeric_limits< double > dbl;
// Definindo um tipo de dado de matriz
boost::numeric::ublas::matrix< long double >  MATRIZ;
// Definindo um tipo de dado de vetor
std::vector< long double > VETOR;


 
bool isChannel( MATRIZ m ){
    long double totalSum = 0;
    int rows = 0;
    for(size_t i = 0; i < m.size1 (); i++){
        totalSum = 0;
        for (size_t i = 0; i < m.size2(); i++){
            totalSum += m (i, j);
            printf("Iterate\n");
        }
        if (totalSum <= (long double) 1.0000000000000001 and totalSum >= (long double) 0.9999999999999999){
            rows += 1;
        } else {
            return false;
        }
    }
    if(rows == m.size1()){
        return true;
    }
}


bool isDistribution( VETOR numberVector){
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
    VETOR probability = {1.0/3.0, 1.0/3.0, 1.0/3.0};
    
    std::cout.precision(dbl::max_digits10);
    
    std::cout << "Probability 1:" <<  probability[0] << std::fixed << "\tProbability 2:" << probability[1] << std::fixed <<  std::endl;
    if (isDistribution(probability)) {
        printf("Is probability\n");
    } else {
        printf("Is not a probability\n");
    }
    
}