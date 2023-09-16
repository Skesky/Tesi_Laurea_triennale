#ifndef ALICE_H
#define ALICE_H

#include <iostream>
#include <random>
#include <complex>
#include <array>
#include <fstream>
#include <cmath>

#include "costanti.h"

struct State{
    Quadr q;
    Quadr p;
};
 
class Alice{

    private:
    std::normal_distribution<> distribution;

    public: 
    Alice();
    State chooseState(std::default_random_engine gen);
};
 
#endif 