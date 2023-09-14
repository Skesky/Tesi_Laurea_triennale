#ifndef CHANNEL_H
#define CHANNEL_H

#include <complex>
#include <random>

using namespace std;
 
class Channel{

    public:
    Channel();
    chrntState trasmission(chrntState state);
};
 
#endif 