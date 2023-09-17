#include <random>
#include <cmath>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <utility>
#include <string>

#include "costanti.h"
#include "alice.h"
#include "bob.h"
#include "channel.h"
#include "simulation.h"
#include "paramEstimation.h"

using namespace std;

double gFuntion(double ni){

    
    double a = ((ni + 1)/2.0);
    double b = ((ni - 1)/2.0);
        
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
    ni.push_back(a - (pow(c, 2)/(b + 1.0)));  //ni3

    return ni;

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

    return (MU/2.0) * log2(1.0 + signalNoiseRatio(channelLoss, noise));

}

//calcolo valor quadratico medio
double meanSquareValue(vector<double> comp){

    double msv;

    for(int i = 0; i < (int)comp.size(); i++){
        msv += pow(comp[i],2);
    }

    return msv / (double)N_ROUND;
}

//calcolo del valor medio dei prodotti delle componenti
double meanProdValue(vector<double> compA, vector<double> compB){

    double msp;

    for(int i = 0; i < (int)compA.size(); i++){
        msp += compA[i] * compB[i];
    }

    return msp / (double)N_ROUND;
}
void parameterEstimation(double *parameter, double *noise, double *channelLoss, vector<vector<double>> sifted){

    //stima parametro a
    parameter[0] = VARIANZA + 1.0;
     cout << "Parametro a: "<< parameter[0] << endl;

    //stima parametro b
    double msvqBob = meanSquareValue(sifted[2]);
    double msvpBob = meanSquareValue(sifted[3]);
    parameter[1] = (msvqBob + msvpBob) / 2.0;
     cout << "Parametro b: "<< parameter[1] << endl;

    //stima parametro c
    double mpValueq = meanProdValue(sifted[0], sifted[2]);
    double mpValuep = meanProdValue(sifted[1], sifted[3]);
    parameter[2] = sqrt((VARIANZA + 2.0)/VARIANZA) * ((mpValueq + mpValuep) / 2.0);
    cout << "Parametro c: "<< parameter[2] << endl;

    //stima trasmittanza
    *channelLoss = pow(parameter[2], 2) / (pow(VARIANZA, 2) + 2.0 * VARIANZA);

    //stima rumore
    *noise = parameter[1] - ((*channelLoss) * VARIANZA) - 1.0;
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

vector<vector<double>> sifter(pair<double, Component> *bob, State *alice){

    vector<double> aliceQs;
    vector<double> alicePs;
    vector<double> bobQs;
    vector<double> bobPs;

    for(int i = 0; i < N_ROUND; i++){
        if(bob[i].second == q){
            bobQs.push_back(bob[i].first);

            aliceQs.push_back(alice[i].q.value);

        } else{
            bobPs.push_back(bob[i].first);

            alicePs.push_back(alice[i].p.value); 

        }
    }
    vector<vector<double>> sifted;
    sifted.push_back(aliceQs);
    sifted.push_back(alicePs);
    sifted.push_back(bobQs);
    sifted.push_back(bobPs);

    return sifted;
}
int main(){

    Simulation sim(N_ROUND, "coherent_states");
    ParamEstimation param(N_ROUND);

    sim.startSimulation();

    param.sifter(sim.getBobMeasures(), sim.getAliceStates());
    param.parameterEstimation();

    /*vector<vector<double>> sifted = sifter(sim.getBobMeasures(), sim.getAliceStates());


    double *parameter = (double*) malloc(3 * sizeof(double));
    double *noise = (double*) malloc(sizeof(double));
    double *channelLoss = (double*) malloc(sizeof(double));


    parameterEstimation(parameter, noise, channelLoss, sifted);


    cout << "Paramentro b: " << parameter[1] << " Valore che ci aspettiamo: " << *channelLoss * VARIANZA + 1.0 + *noise << endl;

    vector<double> ni = niCalc(parameter[0], parameter[1], parameter[2]);

    double chiEveBob = mutInfoEveBob(ni[0], ni[1], ni[2]);
    double infoAliceBob = mutualInfoAliceBob(*channelLoss, *noise);*/

    cout << "Paramentro b: " << param.getParameter()[1] << " Valore che ci aspettiamo: " << param.getChannelLoss() * VARIANZA + 1.0 + param.getNoise() << endl;

    std::cout << "Informazione tra Eve e Bob " << param.getInfoEveBob() << endl; 
    std::cout << "Informazione tra Alice e Bob " << param.getInfoAliceBob() << endl;
    std::cout << "Rapporto segnale rumore " << param.signalNoiseRatio() << endl;
    
    return 0;

}
