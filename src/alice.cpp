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

chrntState Alice::chooseState(default_random_engine gen){
    
    chrntState s;
    //state.real(discrete(distribution(gen)));
    //state.imag(discrete(distribution(gen)));

    //inizializzazione componente q
    s.q.flag = q;
    s.q.component = distribution(gen);
    s.q.variance = 1;

    //inizializzazione componente p
    s.p.flag = p;
    s.p.component = distribution(gen);
    s.p.variance = 1;
    

    return s;
}