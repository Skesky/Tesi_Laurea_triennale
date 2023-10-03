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
#include "decoder.h"




int main(){

    Simulation sim(N_ROUND, "coherent_states");
    ParamEstimation param(N_ROUND);
    

    sim.startSimulation();

    param.sifter(sim.getBobMeasures(), sim.getAliceStates());
    param.parameterEstimation();

    //Reconciliation fase
    Reconciliation recon(param.getAliceData(), param.getBobData(), param.getParameter()[1]);
    Decoder dec;
    random_device rd;
    default_random_engine generator(rd());;
    
    bitset<K> randomBits = sim.getBob().genBitString(generator);


    ifstream parityCheckMatrix("ParityCheckMatrix.txt");

    if(!parityCheckMatrix.is_open()){
        cout << "Non e' stato possibile aprire il file" << endl;
        exit(0);
    }

    vector < bitset<K> > matrixP;
     

    //Reading P matrix from parity check matrix ad traspose it 
    for(int i = 0; i < M; i++){
        string tmp;
        parityCheckMatrix >> tmp;
        dec.checkVariableNodesCount(tmp, i);
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
    vector<double> llr = recon.getLlr();

    dec.initLlr(recon.getLlr());
    vector<double> Q = dec.decode();



    cout << "Paramentro b: " << param.getParameter()[1] << " Valore che ci aspettiamo: " << CHANNEL_LOSS * VARIANZA + 1.0 + NOISE << endl;
    cout << "Paramentro c: " << param.getParameter()[2] << " Valore che ci aspettiamo: " << sqrt(CHANNEL_LOSS * VARIANZA * (VARIANZA + 2)) << endl;

    std::cout << "Informazione tra Eve e Bob " << param.getInfoEveBob() << endl; 
    std::cout << "Informazione tra Alice e Bob " << param.getInfoAliceBob() << endl;
    std::cout << "Rapporto segnale rumore " << param.signalNoiseRatio() << endl;
    std::cout << "Perdita stimata del canale " << param.getChannelLoss() << endl;
    std::cout << "Rumore stimato del canale " << param.getNoise() << endl;
    
    std::cout << "Stringa codificata: " << codeString << endl;
    std::cout << "La lunghezza della stringa codificata e': " << codeString.size() << endl;

    cout << "Updated LLR: " << endl;
    for(int i = 0; i < dec.getQ().size(); i++){
        cout << dec.getQ()[i] << " ";
    }
    cout << endl;
    cout << endl;
    cout << "Initial LLR: " << endl;
    for(int i = 0; i < recon.getLlr().size(); i++){
        cout << recon.getLlr()[i] << " ";
    }
    
    return 0;

}
