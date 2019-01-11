#include <iostream> 
#include <vector>
// #include "QIF2.h"



class hyper{
private:
    std::vector< std::vector< long double > > inner;
    std::vector< long double > outer;

public:
    
    hyper();
    ~hyper();
};

hyper::hyper(){
}

hyper::~hyper()
{
}

int main () {
    hyper A(3, 0);
    printf("%d", A.outer.size());
    for(size_t i = 0; i < A.outer.size(); i++){
        printf("a%Lf", A.outer[i]);
    }
}