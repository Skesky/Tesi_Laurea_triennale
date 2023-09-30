#ifndef COSTANTI
#define COSTANTI
 

#define VARIANZA 5.226
#define MU 1.0
#define CHANNEL_LOSS 0.1
#define NOISE 0.005
#define N_ROUND 1000
#define N 50
#define M (N-(int)(N*0.3))
#define K (N-M)

enum Component {q, p};

typedef struct Quadrature{
    Component flag;
    double value;
    double variance;
} Quadr;

#endif
