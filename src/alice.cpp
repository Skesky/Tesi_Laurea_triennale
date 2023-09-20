#include <iostream>
#include <random>
#include <complex>
#include <array>
#include <fstream>
#include <cmath>

#include "costanti.h"
#include "alice.h"

using namespace std;

Alice::Alice() : distribution(0, sqrt(VARIANZA)){
    cout << "Sono Alice \n";
}

State Alice::chooseState(default_random_engine gen){
    
    State s;

    //inizializzazione componente q
    s.q.flag = q;
    s.q.value = distribution(gen);
    s.q.variance = 1;

    //inizializzazione componente p
    s.p.flag = p;
    s.p.value = distribution(gen);
    s.p.variance = 1;
    

    return s;
}