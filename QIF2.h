#ifndef HEADER_FILE
#define HEADER_FILE

#include <iostream>
#include <vector>

class distribution {
    private:
        std::vector< long double > values;
    public:
        ~distribution();
        distribution(int size, long double value){
            values(size, value);
        }
        void pushValue(long double value);
        bool isDistribution(void);
};
distribution::~distribution(){

}
void distribution::pushValue(long double value){

}
bool distribution::isDistribution(void){
    long double totalSum = 0;
    for (size_t i = 0; i < this->values.size(); i++){
        totalSum += this->values[i];
        // printf("Iterate\n");
    }   
    if (totalSum <= (long double) 1.0000000000000001 and totalSum >= (long double) 0.9999999999999999){
        return true;
    } else {
        return false;
    }
}

#endif