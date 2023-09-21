#include <vector>
#include <utility>

#include "costanti.h"
#include "alice.h"
#include "paramEstimation.h"


using namespace std;

ParamEstimation::ParamEstimation(int round){
    this->nRound = round;
}


void ParamEstimation::parameterEstimation(){

    //stima parametro a
    parameter.push_back(VARIANZA + 1.0);

    //stima parametro b
    double msvqBob = meanSquareValue(this->bobQs);
    double msvpBob = meanSquareValue(this->bobPs);
    parameter.push_back((msvqBob + msvpBob) / 2.0);

    //stima parametro c
    double mpValueq = meanProdValue(this->aliceQs, this->bobQs);
    double mpValuep = meanProdValue(this->alicePs, this->bobPs);
    parameter.push_back(sqrt((VARIANZA + 2.0)/VARIANZA) * ((mpValueq + mpValuep) / 2.0));

    //stima trasmittanza
    this->channelLoss = pow(parameter[2], 2) / (pow(VARIANZA, 2) + 2.0 * VARIANZA);

    //stima rumore
    this->noise = parameter[1] - ((this->channelLoss) * VARIANZA) - 1.0;

    niCalc();

    mutualInfoAliceBob();
    mutInfoEveBob();

}

void ParamEstimation::sifter(pair<double, Component>* bob, State* alice){
    
    for(int i = 0; i < nRound; i++){
        if(bob[i].second == q){
            this->bobQs.push_back(bob[i].first);

            this->aliceQs.push_back(alice[i].q.value);

        } else{
            this->bobPs.push_back(bob[i].first);

            this->alicePs.push_back(alice[i].p.value); 

        }
    }
}

void ParamEstimation::niCalc(){

    double z = sqrt(pow((parameter[0] + parameter[1]), 2) - 4 * pow(parameter[2], 2));

    this->ni.push_back(0.5 * (z +(parameter[1] - parameter[0])));       //ni1
    this->ni.push_back(0.5 * (z -(parameter[1] - parameter[0])));       //ni2
    //this->ni.push_back(parameter[0] - (pow(parameter[2], 2)/(parameter[1] + 1.0)));  
    this->ni.push_back(sqrt(parameter[0] * (parameter[0] - (pow(parameter[2],2) / parameter[1])))); //ni3
}

//calcolo valor quadratico medio
double ParamEstimation::meanSquareValue(vector<double> comp){
    
    double msv = 0;

    for(int i = 0; i < (int)comp.size(); i++){
        msv += pow(comp[i],2);
    }

    return msv / (double)/*nRound*/comp.size();
}

//calcolo del valor medio dei prodotti delle componenti
double ParamEstimation::meanProdValue(vector<double> compA, vector<double> compB){

    double msp = 0;

    for(int i = 0; i < (int)compA.size(); i++){
        msp += compA[i] * compB[i];
    }

    return msp / (double)/*nRound**/compA.size();
}

//SNR
double ParamEstimation::signalNoiseRatio(){
    
    //return ((1.0/MU) * this->channelLoss * sqrt(VARIANZA))/(1.0 + ((1.0/MU) * this->noise));
    return ((1.0/MU) * CHANNEL_LOSS * VARIANZA)/(1.0 + ((1.0/MU) * NOISE)); 

}

//calcolo informazione mutua tra Alice e Bob -------
void ParamEstimation::mutualInfoAliceBob(){

    this->mutInfoAB = (MU/2.0) * log2(1.0 + signalNoiseRatio());

}

double ParamEstimation::gFuntion(double ni){

    
    double a = ((ni + 1)/2.0);
    double b = ((ni - 1)/2.0);
        
    return (a * log2(a)) - (b * log2(b));

}

void ParamEstimation::mutInfoEveBob(){

    this->mutInfoEB = ((gFuntion(this->ni[0]) + gFuntion(this->ni[1])) - gFuntion(this->ni[2])); // tra parentesi abbiamo l'entropia congiunta tra A e b 
                                                              // mentre g3 e' l'entropia di A condizionato B
}

double ParamEstimation::getChannelLoss(){
    
    return this->channelLoss;

}

double ParamEstimation::getNoise(){

    return this->noise;

}
    
double ParamEstimation::getInfoAliceBob(){

    return this->mutInfoAB;

}

double ParamEstimation::getInfoEveBob(){

    return this->mutInfoEB;

}
    
vector<double> ParamEstimation::getParameter(){

    return this->parameter;

}

vector<double> ParamEstimation::getNi(){

    return this->ni;

}

vector<double> ParamEstimation::getAliceQComponents(){

    return this->aliceQs;

}
vector<double> ParamEstimation::getAlicePComponents(){

    return this->alicePs;

}

vector<double> ParamEstimation::getBobQComponents(){

    return this->bobQs;

}

vector<double> ParamEstimation::getBobPComponents(){

    return this->bobPs;

}
