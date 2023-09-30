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
    

    sim.startSimulation();

    param.sifter(sim.getBobMeasures(), sim.getAliceStates());
    param.parameterEstimation();

    //Reconciliation fase
    Reconciliation recon(param.getAliceData(), param.getBobData(), param.getParameter()[1]);
    Bob bob = sim.getBob();
    random_device rd;
    default_random_engine generator(rd());;
    
    bitset<K> randomBits = bob.genBitString(generator);


    ifstream parityCheckMatrix("ParityCheckMatrix.txt");

    if(!parityCheckMatrix.is_open()){
        cout << "Non e' stato possibile aprire il file" << endl;
        exit(0);
    }

    vector < bitset<K> > matrixP;
    string tmp; 


    //Reading P matrix from parity check matrix ad traspose it 
    while(1){
        parityCheckMatrix >> tmp;
        if(parityCheckMatrix.eof())
            break;
        string line = "";
        for(int i = 0; i < K; i++){
            line += tmp[i+M];
        }
            
        bitset<K> column{line};
        matrixP.push_back(column);
    }



    string codeString = randomBits.to_string().append(recon.prdMatrix(randomBits, matrixP));

    //Codeword used to modulate Bob measurement
    bitset<N> codeWord{codeString};


    //Sign modulation of bob's normalized data
    vector<double> modulated = recon.signModulation(codeWord);
    recon.dMessage(modulated);



    cout << "Paramentro b: " << param.getParameter()[1] << " Valore che ci aspettiamo: " << CHANNEL_LOSS * VARIANZA + 1.0 + NOISE << endl;
    cout << "Paramentro c: " << param.getParameter()[2] << " Valore che ci aspettiamo: " << sqrt(CHANNEL_LOSS * VARIANZA * (VARIANZA + 2)) << endl;

    std::cout << "Informazione tra Eve e Bob " << param.getInfoEveBob() << endl; 
    std::cout << "Informazione tra Alice e Bob " << param.getInfoAliceBob() << endl;
    std::cout << "Rapporto segnale rumore " << param.signalNoiseRatio() << endl;
    std::cout << "Perdita stimata del canale " << param.getChannelLoss() << endl;
    std::cout << "Rumore stimato del canale " << param.getNoise() << endl;
    
    std::cout << "Stringa codificata: " << codeString << endl;
    std::cout << "La lunghezza della stringa codificata e': " << codeString.size() << endl;
    
    return 0;

}
