#ifndef COSTANTI
#define COSTANTI
 

#define VARIANZA 0.923
#define MU 1.0
#define CHANNEL_LOSS 0.9
#define NOISE 0.6
#define N_ROUND 100000

enum Component {q, p};

typedef struct Quadrature{
    Component flag;
    double value;
    double variance;
} Quadr;

#endif
