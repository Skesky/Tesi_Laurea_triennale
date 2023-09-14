#include <iostream>
#include <complex>
#include <random>
#include "alice.h"

#include "bob.h"

using namespace std;

Bob::Bob() :: distribition(0,1){
    cout << "Sono Bob \n";
}

void Bob::gaussianSetting(cState state){

    d_q = normal_distribution<double>{sqrt(CHANNEL_LOSS) * state.qMean, 1 + NOISE};
    d_p = normal_distribution<double>{sqrt(CHANNEL_LOSS) * state.qMean, 1 + NOISE};
}

int Bob::selectMeasure(default_random_engine gen){

    return distribition(gen); // estrae 0 o 1 con probalita' uniforme
    
}
//se coin e' uguale ad 1 viene misurata la q mentre viene misurata la p se uguale a 0
double Bob::measure(cState state, default_random_engine gen, int coin){

    gaussianSetting(state);

    double measured;

    if(coin){
        measured = d_q(gen);
    }
    else{
        measured = d_p(gen);
    }

    //misura dei gli stati ricevuti da Bob
    measured.real(d_q(gen));
    measured.imag(d_p(gen));

    return measured; 

}