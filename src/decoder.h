#ifndef DECODER_H
#define DECODER_H

#include <vector>
#include <string>
#include <bitset>

using namespace std;
 
class Decoder{

    private:
    vector<vector<int>> Cs;
    vector<vector<int>> Vs;

    vector<vector<double>> qMatrix; //variable messages matrix
    vector<vector<double>> rMatrix; //check messages matrix

    vector<double> llr;

    vector<double> Q; //updated LLRs


    public:
    Decoder();
    void checkVariableNodesCount(string, int);
    vector<double> decode();
    vector<vector<int>> getCs();
    vector<vector<int>> getVs();
    vector<double> getQ();
    void initLlr(vector<double>);
    

    private:
    void updateLLR();
    void checkMessageCalc(vector<int>, int);
    void updateVariableMessages(vector<int>, int);
    void qMatrixInit();
    double argTanh(int, vector<int>, int);
    double sumCheckMessage(int , vector<int> , int);
    double updateSum(int);

};
 
#endif 