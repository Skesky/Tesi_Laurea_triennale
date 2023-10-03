#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include <bitset>

#include "alice.h"
#include "bob.h"
#include "channel.h"
#include "costanti.h"
#include "simulation.h"

using namespace std;

Simulation::Simulation(int round, string fileName){
    this->nRound = round;
    this->outputFile.open(fileName + ".csv"); 
    this->aliceStates = (State*) malloc(N_ROUND * sizeof(State));
    this->bobMeasures = (pair<double, Component>*) malloc(N_ROUND * sizeof(pair<double, Component>));
}


State* Simulation::getAliceStates(){
    return this->aliceStates;
}

pair<double, Component>* Simulation::getBobMeasures(){
    return this->bobMeasures;
}


void Simulation::startSimulation(){

    if(!outputFile.is_open()){
        cout << "Fallimento nell'apertura del file";
        exit(0);
    }

    outputFile << "Q_Mean,P_Mean,Variance;Measured_real;Measured_imag" << endl;

    for(int i = 0; i<nRound; i++){
        std::default_random_engine generator(this->rd());

        aliceStates[i] = alice.chooseState(generator);
        
        bobMeasures[i] = bob.measure(channel.trasmission(aliceStates[i]), generator);

        outputFile << aliceStates[i].q.value << ';' << aliceStates[i].p.value << ';' << aliceStates[i].p.value << ";" 
                   << bobMeasures[i].first << ";" << bobMeasures[i].second << endl;

        //cout << i << "--"<< bobMeasures[i].first << "," << bobMeasures[i].second << endl;
        
    }
    std::default_random_engine generator(this->rd());
    
    outputFile.close();
}

void Simulation::freeMem(){
    free(aliceStates);
    free(bobMeasures);
}

Bob Simulation::getBob(){
    return this->bob;
}
