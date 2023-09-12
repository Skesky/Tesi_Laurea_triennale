#include <iostream>
#include "alice.h"
#include "channel.h"
#include "costanti.h"

using namespace std;

Channel::Channel(){
    cout << "Sono Channel \n";
}

cState Channel::trasmission(cState state, default_random_engine gen){

    cState s;

    s.qMean = state.qMean * sqrt(CHANNEL_LOSS);
    s.pMean = state.pMean * sqrt(CHANNEL_LOSS);
    s.variance = (state.variance * CHANNEL_LOSS ) + NOISE * (state.variance - CHANNEL_LOSS);

    return s;

}