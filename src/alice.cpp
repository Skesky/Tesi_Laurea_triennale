#include <iostream>
#include <random>
#include <complex>
#include <array>
#include <fstream>
#include <cmath>

#include "costanti.h"
#include "alice.h"

using namespace std;

Alice::Alice() : distribution(0, VARIANZA * 4){
    cout << "Sono Alice \n";
}

/*double Alice::discrete(double a){
    double num = 0;
    double n = abs(a);
    cout << n << endl;
 
    
        
    while(num < n){

        if((num + BIN_DIM) > n)
            return num;

        num = num + BIN_DIM;
        cout << num << endl;
    }
    
    return num;

}*/

cState Alice::chooseState(default_random_engine gen){
    
    cState state;
    //state.real(discrete(distribution(gen)));
    //state.imag(discrete(distribution(gen)));



    state.qMean = distribution(gen);
    state.pMean = distribution(gen);
    state.variance = 1.0;

    return state;
}