#include <iostream>
#include "alice.h"
#include "channel.h"
#include "costanti.h"

using namespace std;

Channel::Channel(){
    cout << "Sono Channel \n";
}

State Channel::trasmission(State state){

    State s;

    s.q.value = state.q.value * sqrt(CHANNEL_LOSS);
    s.p.value = state.p.value * sqrt(CHANNEL_LOSS);

    s.q.variance = 1 + NOISE;
    s.p.variance = 1 + NOISE;

    return s;

}