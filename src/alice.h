#ifndef ALICE_H
#define ALICE_H

#include <iostream>
#include <random>
#include <complex>
#include <array>
#include <fstream>
#include <cmath>

#include "costanti.h"

typedef struct CoherentState{
    State q;
    State p;
} chrntState;
 
class Alice{

    private:
    //std::complex<double> *states;
    std::normal_distribution<> distribution;

    public: 
    Alice();
    double discrete(double n);
    chrntState chooseState(std::default_random_engine gen);
};
 
#endif 