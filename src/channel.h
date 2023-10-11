#ifndef CHANNEL_H
#define CHANNEL_H

#include <complex>
#include <random>

using namespace std;

class Channel{

    private:
    normal_distribution<> d_q;
    normal_distribution<> d_p;

    public:
    Channel();
    State trasmission(State);
    State trasmissionWithEve(State);
};
 
#endif 