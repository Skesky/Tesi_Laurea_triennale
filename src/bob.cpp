#include <iostream>
#include <complex>
#include <random>
#include <utility>
#include <bitset>
#include <string>

#include "alice.h"
#include "bob.h"
#include "costanti.h"

using namespace std;

Bob::Bob() : distribution(0,1){
    cout << "Sono Bob \n";
}

void Bob::gaussianSetting(State state){

    d_q = normal_distribution<double>{ state.q.value, sqrt(state.q.variance)};
    d_p = normal_distribution<double>{ state.p.value, sqrt(state.p.variance)};
}

//se coin e' uguale ad 1 viene misurata la q mentre viene misurata la p se uguale a 0
pair<double, Component> Bob::measure(State state, default_random_engine gen){

    gaussianSetting(state);

    pair<double, Component> measured;

    if(distribution(gen)){
        measured.first = d_q(gen); 
        measured.second = q;
              
     }
    else{
        measured.first = d_p(gen);
        measured.second = p;
    }

    return measured; 

}

bitset<K> Bob::genBitString(default_random_engine gen){
    string bitString;

    for(int i = 0; i < K; i++){
        if(distribution(gen))
            bitString.append("1");
        else 
            bitString.append("0");
    }

    bitset<K> b{bitString};

    cout << "Stringa di bit Random stampata da Bob :" << bitString << endl;

    return b;
}