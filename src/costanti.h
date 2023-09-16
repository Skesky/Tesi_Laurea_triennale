#ifndef COSTANTI
#define COSTANTI
 

#define VARIANZA 4.0
#define MU 1.0
#define N_BIN 4.0
#define BIN_DIM 0.0003
#define CHANNEL_LOSS 0.52
#define NOISE 1.0
#define N_ROUND 1000000

enum Component {q, p};

typedef struct Quadrature{
    Component flag;
    double value;
    double variance;
} Quadr;

#endif
