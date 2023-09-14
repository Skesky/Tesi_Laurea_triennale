#include <iostream>
#include "alice.h"
#include "channel.h"
#include "costanti.h"

using namespace std;

Channel::Channel(){
    cout << "Sono Channel \n";
}

chrntState Channel::trasmission(chrntState state){

    chrntState s;

    s.q.component = state.q.component * sqrt(CHANNEL_LOSS);
    s.p.component = state.p.component * sqrt(CHANNEL_LOSS);

    s.q.variance = 1 + NOISE;
    s.p.variance = 1 + NOISE;

    return s;

}