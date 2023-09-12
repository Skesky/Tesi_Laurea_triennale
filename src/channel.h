#ifndef CHANNEL_H
#define CHANNEL_H

#include <complex>
#include <random>

using namespace std;
 
class Channel{

    public:
    Channel();
    cState trasmission(cState state, default_random_engine gen);
};
 
#endif 