#ifndef COSTANTI
#define COSTANTI
 

#define VARIANZA 0.924444
#define MU 2.0
#define CHANNEL_LOSS 0.7
#define NOISE 0.6
#define N_ROUND 1000

enum Component {q, p};

typedef struct Quadrature{
    Component flag;
    double value;
    double variance;
} Quadr;

#endif
