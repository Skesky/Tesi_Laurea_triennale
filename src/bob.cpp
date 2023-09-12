#include <iostream>
#include <complex>
#include <random>
#include "alice.h"

#include "bob.h"

using namespace std;

Bob::Bob(){
    cout << "Sono Bob \n";
}

void Bob::gaussianSetting(cState state){

    d_q = normal_distribution<double>{state.qMean, state.variance};
    d_p = normal_distribution<double>{state.pMean, state.variance};
}

complex<double> Bob::measure(cState state, default_random_engine gen){

    gaussianSetting(state);

    complex<double> measured;

    //misura dei gli stati ricevuti da Bob
    measured.real(d_q(gen));
    measured.imag(d_p(gen));

    return measured; 

}