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
    std::cout << "Perdita stimata del canale " << param.getChannelLoss() << endl;
    std::cout << "Rumore stimato del canale " << param.getNoise() << endl;
    
    return 0;

}
