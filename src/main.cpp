#include "costanti.h"

#include <random>
#include <cmath>
#include <unistd.h>
#include <vector>


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

//SNR
double signalNoiseRatio(){
    
    return ((1.0/MU) * CHANNEL_LOSS * VARIANZA)/(1.0 + ((1.0/MU) * NOISE)); 

}

//calcolo informazione mutua tra Alice e Bob
double mutualInfoAliceBob(){

    return (MU/2) * log2(1.0 + signalNoiseRatio());

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

int main(){
    std::random_device rd;
    
    Alice a;
    Channel c;
    Bob b;
    double sumProd;

    fstream outputFile("coherent_states.csv");
	outputFile << "Q_Mean,P_Mean,Variance;Measured_real;Measured_imag" << std::endl;
    
    for(int i = 0; i<N_ROUND; i++){
        std::default_random_engine generator(rd());
        Stato aliceState = a.chooseState(generator);
        //state = a.chooseState(generator);
        complex<double> bobState = b.measure(c.trasmission(aliceState, generator), generator);

        //somma dei prodotti delle componenti q di alice e bob
        sumProd += (aliceState.qMean *  bobState.real());

        outputFile << aliceState.qMean << ',' << aliceState.pMean << ',' << aliceState.variance << ";" 
                   << bobState.real() << ";" << bobState.imag() << std::endl;

        std::cout << bobState.real() << "," << bobState.imag() << std::endl;
        
    }
    outputFile.close();

    double bPm = (CHANNEL_LOSS / MU) * VARIANZA + 1.0 + (NOISE / MU);

    vector<double> param = estinationParamABC(bPm, sumProd);
    vector<double> ni = niCalc(param[0], param[1], param[2]);

    double chiEveBob = mutInfoEveBob(param[0], param[1], param[2]);
    double infoAliceBob = mutualInfoAliceBob();

    double cEB = sqrt(CHANNEL_LOSS) * sqrt((pow(VARIANZA, 2) + (2 * VARIANZA)));

    std::cout << "Informazione tra Eve e Bob " << chiEveBob << endl; 
    std::cout << "Informazione tra Alice e Bob " << infoAliceBob << endl;
    std::cout << "Rapporto segnale rumore " << signalNoiseRatio() << endl;
    std:: cout << "cEB " << cEB << endl;

    
    return 0;

}
