#include <random>
#include <cmath>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <utility>
#include <string>
#include <bitset>
#include <fstream>

#include "costanti.h"
#include "alice.h"
#include "bob.h"
#include "channel.h"
#include "simulation.h"
#include "paramEstimation.h"
#include "reconciliation.h"


int main(){

    Simulation sim(N_ROUND, "coherent_states");
    ParamEstimation param(N_ROUND);
    Reconciliation recon;

    sim.startSimulation();

    param.sifter(sim.getBobMeasures(), sim.getAliceStates());
    param.parameterEstimation();

    //Reconciliation fase
    bitset<K> randomBits /*= recon.genBitString()*/;

    ifstream parityCheckMatrix("ParityCheckMatrix.txt");

    if(!parityCheckMatrix){
        cout << "Non e' stato possibile aprire il file" << endl;
        exit(0);
    }

    vector < bitset<K> > matrixP;
    string tmp; 

    do{
        parityCheckMatrix >> tmp;
        string line = "";
        for(int i = 0; i < K; i++)
            line += tmp[i+M];
        bitset<K> column{line};
        matrixP.push_back(column);

    }while(!parityCheckMatrix.eof());

    string codeString = randomBits.to_string() += recon.prdMatrix(randomBits, matrixP);

    //Codeword used to modulate Bob measurement
    bitset<K> codeWord{recon.prdMatrix(randomBits, matrixP)};



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
