#include <iostream>
#include <complex>
#include <random>
#include "alice.h"

#include "bob.h"

using namespace std;

Bob::Bob() : distribution(0,1){
    cout << "Sono Bob \n";
}

void Bob::gaussianSetting(chrntState state){

    d_q = normal_distribution<double>{sqrt(CHANNEL_LOSS) * state.q.component, state.q.variance + NOISE};
    d_p = normal_distribution<double>{sqrt(CHANNEL_LOSS) * state.p.component, state.p.variance + NOISE};
}

/*int Bob::selectMeasure(default_random_engine gen){

    return distribition(gen); // estrae 0 o 1 con probalita' uniforme
    
}*/

//se coin e' uguale ad 1 viene misurata la q mentre viene misurata la p se uguale a 0
State Bob::measure(chrntState state, default_random_engine gen){

    gaussianSetting(state);

    State measured;

    if(distribution(gen)){
        measured.flag = q;
        measured.component = d_q(gen);
        measured.variance = state.q.variance; // dato che canale aggiunge gia' rumore 
                                              // verificare se cosi' va bene o va aggiunto di nuovo
     }
    else{
        measured.flag = p;
        measured.component = d_p(gen);
        measured.variance = state.p.variance;
    }

    return measured; 

}