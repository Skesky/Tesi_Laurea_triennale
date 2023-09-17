#ifndef PARAMESTIMATION_H
#define PARAMESTIMATION_H

using namespace std;

class ParamEstimation{

    private:
    int nRound;
    vector<double> parameter;
    double channelLoss;
    double noise;
    vector<double> ni;

    vector<double> aliceQs;
    vector<double> alicePs;
    vector<double> bobQs;
    vector<double> bobPs;

    double mutInfoAB;
    double mutInfoEB;


    public:
    ParamEstimation(int);
    double getChannelLoss();
    double getNoise();
    double getInfoAliceBob();
    double getInfoEveBob();
    double signalNoiseRatio();
    vector<double> getParameter();
    vector<double> getNi();
    vector<double> getAliceQComponents();
    vector<double> getAlicePComponents();
    vector<double> getBobQComponents();
    vector<double> getBobPComponents();
    void parameterEstimation();
    void sifter(pair<double, Component>*, State*);

    private:
    
    double meanSquareValue(vector<double>);
    double meanProdValue(vector<double>, vector<double>);
    double gFuntion(double);
    void niCalc();
    
    void mutualInfoAliceBob();
    void mutInfoEveBob();
   
    
};
 
#endif 