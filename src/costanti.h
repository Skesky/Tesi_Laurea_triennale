#ifndef COSTANTI
#define COSTANTI
 
#include <complex>

#include "alice.h"
#include "bob.h"
#include "channel.h"

#define VARIANZA 1.0
#define MU 1.0
#define N_BIN 4.0
#define BIN_DIM 0.0003
#define CHANNEL_LOSS 0.52
#define NOISE 1.0
#define N_ROUND 100000

enum quadratures {qA, pA, qB, pB};

struct State{
    quadratures flag;  
    double component;
    double variance;
};

#endif
