#ifndef ALICE_H
#define ALICE_H

#include <iostream>
#include <random>
#include <complex>
#include <array>
#include <fstream>
#include <cmath>

typedef struct CoherentState{
    double qMean;
    double pMean;
    double variance;

} cState;
 
class Alice{

    private:
    //std::complex<double> *states;
    std::normal_distribution<> distribution;

    public: 
    Alice();
    double discrete(double n);
    cState chooseState(std::default_random_engine gen);
};
 
#endif 