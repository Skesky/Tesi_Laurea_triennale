#include <random>
#include <cmath>
#include <unistd.h>
#include <vector>
#include <iostream>

#include "costanti.h"
#include "alice.h"
#include "bob.h"
#include "channel.h"

using namespace std;

double gFuntion(double ni){

    
    double a = ((ni + 1)/2);
    double b = ((ni - 1)/2);
        
    return (a * log2(a)) - (b * log2(b));

}


double mutInfoEveBob(double ni1, double ni2, double ni3){

    return ((gFuntion(ni1) + gFuntion(ni2)) - gFuntion(ni3)); // tra parentesi abbiamo l'entropia congiunta tra A e b 
                                                              // mentre g3 e' l'entropia di A condizionato B
}

//calcolo dei tre valori per ni
vector<double> niCalc(double a, double b, double c){
    vector<double> ni;
    double z = sqrt(pow((a + b), 2) - 4 * pow(c, 2));

    ni.push_back(0.5 * (z +(b - a)));       //ni1
    ni.push_back(0.5 * (z -(b - a)));       //ni2
    ni.push_back(a - (pow(c, 2)/(b + 1)));  //ni3

    return ni;

}

//calcolo della media del prodotto tra la componente q di Alice 
//e quella misurata da Bob
double meanQstate(double sp){
    
    std::cout << "MeanQState: " << sp/N_ROUND << endl;

    return sp / N_ROUND;

}

//stima dei parametri a, b, c per il calcolo dei ni
vector<double> estinationParamABC(double bPm, double sp){
    vector<double> param;
    
    param.push_back(VARIANZA + 1); // a
    param.push_back(MU * bPm - MU + 1); //b 
    param.push_back(sqrt((VARIANZA + 2) / VARIANZA) * sqrt(MU) * meanQstate(sp)); // c
    
    return param;

}

/*
*
*
*
*
*   Parameter Estimation
*
*
*
*
*/

//SNR
double signalNoiseRatio(double channelLoss, double noise){
    
    return ((1.0/MU) * channelLoss * VARIANZA)/(1.0 + ((1.0/MU) * noise)); 

}

//calcolo informazione mutua tra Alice e Bob -------
double mutualInfoAliceBob(double channelLoss, double noise){

    return (MU/2) * log2(1.0 + signalNoiseRatio(channelLoss, noise));

}

//calcolo valor quadratico medio
double meanSquareValue(double* comp){

    double msv;
    int dim = sizeof(comp) / sizeof(double);

    for(int i = 0; i < dim; i++){
        msv += pow(comp[i],2);
    }

    return msv / (double)N_ROUND;
}

//calcolo del valor medio dei prodotti delle componenti
double meanProdValue(double* compA, double* compB){

    double msp;

    int dim = sizeof(compA) / sizeof(double);

    for(int i = 0; i < dim; i++){
        msp += compA[i] * compB[i];
    }


    return msp / (double)N_ROUND;
}
void parameterEstimation(double *parameter, double *noise, double *channelLoss, State *aliceSifted, State *bobStates, 
                            double* aliceQs, double* alicePs, double* bobQs, double* bobPs){

    //stima parametro a
    double vMod = VARIANZA * 4.0;
    parameter[1] = vMod + 1.0;

    //stima parametro b
    double msvqBob = meanSquareValue(bobQs);
    double msvpBob = meanSquareValue(bobPs);
    parameter[2] = (msvpBob + msvpBob) / 2.0;

    //stima parametro c
    double mpValueq = meanProdValue(aliceQs, bobQs);
    double mpValuep = meanProdValue(alicePs, bobPs);
    parameter[3] = sqrt((vMod + 2.0)/vMod) * ((mpValueq + mpValuep) / 2.0);

    //stima trasmittanza
    *channelLoss = pow(parameter[3], 2) / (pow(vMod, 2) + 2.0 * vMod);

    //stima rumore
    *noise = parameter[2] - ((*channelLoss) * vMod) - 1.0;
}

/*
*
*
*
*
*   Sifting
*
*
*
*
*/

void sifter(State *aSitfed, State *bob, chrntState *alice, double* aliceQs, double* alicePs, double* bobQs, double* bobPs){

    int qCount = 1;
    int pCount = 1;

    for(int i = 0; i < N_ROUND; i++){
        if(bob[i].flag == q){
            bobQs = (double*)realloc(bobQs, qCount * sizeof(double));
            bobQs[i] = bob[i].component; 

            aliceQs = (double*)realloc(aliceQs, qCount * sizeof(double));
            aliceQs[i] = alice[i].q.component; 

            aSitfed[i].component = alice[i].q.component;
            aSitfed[i].variance = alice[i].q.variance;
            aSitfed[i].flag = q;

            qCount ++;
        } else{
            bobPs = (double*)realloc(bobPs, qCount * sizeof(double));
            bobPs[i] = bob[i].component; 

            alicePs = (double*)realloc(alicePs, qCount * sizeof(double));
            alicePs[i] = alice[i].p.component; 

            aSitfed[i].component = alice[i].p.component;
            aSitfed[i].variance = alice[i].p.variance;
            aSitfed[i].flag = p;

            pCount++;
        }
    }
}
int main(){
    std::random_device rd;
    
    Alice a;
    Channel c;
    Bob b;
    double sumProd;

    chrntState *aliceStates = (chrntState*) malloc(N_ROUND * sizeof(chrntState));
    State *bobStates = (State*) malloc(N_ROUND * sizeof(State));

    fstream outputFile("coherent_states.csv");
	outputFile << "Q_Mean,P_Mean,Variance;Measured_real;Measured_imag" << std::endl;
    
    for(int i = 0; i<N_ROUND; i++){
        std::default_random_engine generator(rd());

        chrntState aliceState = a.chooseState(generator);
        aliceStates[i] = aliceState;
        
        State bobState = b.measure(c.trasmission(aliceState), generator);
        bobStates[i] = bobState;

        outputFile << aliceState.q.component << ',' << aliceState.p.component << ',' << aliceState.p.variance << ";" 
                   << bobState.component << ";" << bobState.variance << std::endl;

        std::cout << bobState.component << "," << bobState.variance << ',' << bobState.flag << std::endl;
        
    }
    outputFile.close();

    State *aliceSifted = (State*) malloc(N_ROUND * sizeof(State));

    double *aliceQs = (double*) malloc(sizeof(double));
    double *alicePs = (double*) malloc(sizeof(double));
    double *bobQs = (double*) malloc(sizeof(double));
    double *bobPs = (double*) malloc(sizeof(double));

    sifter(aliceSifted, bobStates, aliceStates, aliceQs, alicePs, bobQs, bobPs);

    for(int i = 0; i < N_ROUND; i++){
        cout << aliceSifted[i].component << ' ' << bobStates[i].component << endl;
        cout <<aliceSifted[i].flag<< "==" << bobStates[i].flag << endl;
    }

    double *parameter = (double*) malloc(3 * sizeof(double));
    double *noise;
    double *channelLoss;


    parameterEstimation(parameter, noise, channelLoss, aliceSifted, bobStates, aliceQs, alicePs, bobQs, bobPs);

    /*double bPm = (CHANNEL_LOSS / MU) * VARIANZA + 1.0 + (NOISE / MU);

    vector<double> param = estinationParamABC(bPm, sumProd);
    vector<double> ni = niCalc(param[0], param[1], param[2]);

    double chiEveBob = mutInfoEveBob(param[0], param[1], param[2]);
    double infoAliceBob = mutualInfoAliceBob(*channelLoss, *noise);

    double cEB = sqrt(CHANNEL_LOSS) * sqrt((pow(VARIANZA, 2) + (2 * VARIANZA)));*/

    //std::cout << "Informazione tra Eve e Bob " << chiEveBob << endl; 
    //std::cout << "Informazione tra Alice e Bob " << infoAliceBob << endl;
    std::cout << "Rapporto segnale rumore " << signalNoiseRatio(*channelLoss, *noise) << endl;
    //std:: cout << "cEB " << cEB << endl;

    
    return 0;

}
