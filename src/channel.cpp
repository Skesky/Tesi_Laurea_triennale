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

    s.q.variance = state.q.variance + NOISE;
    s.p.variance = state.p.variance + NOISE;

    return s;

}

State Channel::trasmissionWithEve(State state){

    random_device rd;
    default_random_engine gen(rd());

    d_q = normal_distribution<double>{ state.q.value, sqrt(state.q.variance) + 1};
    d_p = normal_distribution<double>{ state.p.value, sqrt(state.p.variance) + 1};

    State s;

    s.q.flag = q;
    s.q.value = d_q(gen);
    s.q.variance = (sqrt(state.q.variance) + 1);

    s.p.flag = p;
    s.p.value = d_p(gen);
    s.p.variance = (sqrt(state.p.variance) + 1);

    return s;
}
