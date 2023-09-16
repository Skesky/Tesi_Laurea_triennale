#ifndef CHANNEL_H
#define CHANNEL_H

#include <complex>
#include <random>

using namespace std;

class Channel{

    public:
    Channel();
    State trasmission(State state);
};
 
#endif 