#include <cmath>
#include <iostream>
#include <fstream>

#include "decoder.h"
#include "costanti.h"


Decoder::Decoder()
    :Cs(M, vector<int> (N, -1)), 
     Vs(N, vector<int> (M,-1)),
     rMatrix(M, vector<double>(N, 0.0)),
     Q(N, 0.0){
    
}

void Decoder::updateLLR(){

    for(int i = 0; i < Q.size(); i++)
        Q[i] = llr[i] + updateSum(i);
}

void Decoder::checkMessageCalc(vector<int> c, int row){

    for(int i = 0; i < c.size(); i++){
        if(c[i] != -1)
            rMatrix[row][i] = (2 * atanh(argTanh(i, c, row)));
    }
}

vector<double> Decoder::decode(){

    qMatrixInit();

    for(int r = 0; r < DEC_ROUND; r++){
        for(int i = 0; i < rMatrix.size(); i++){
            checkMessageCalc(Cs[i],i);
         }

        for(int i = 0; i < qMatrix.size(); i++){
            updateVariableMessages(Vs[i],  i);
        }
  
        updateLLR();
    }

    return this->Q;

}

vector<vector<int>> Decoder::getCs(){
    return this->Cs;
}

vector<vector<int>> Decoder::getVs(){
    return this->Vs;
}

double Decoder::updateSum(int i){
    
    double temp = 0;
    for(int w = 0; w < Vs[i].size(); w++){
        if(Vs[i][w] != -1)
            temp += rMatrix[w][i];
    }

    return temp;
}

void Decoder::checkVariableNodesCount(string line, int i){

    //identifico posizioni contenti 1 sia per i nodi variabile e i nodi check
    //per la riga i-esima
    
        bitset<N> bit{line};

        for(int j = 0; j < bit.size(); j++){
            if(bit[j]){
                int pos = (abs(j-((int)bit.size())+1));
                Cs[i][pos] = 1; 
                Vs[pos][i] = 1;
            }
        }
}

vector<double> Decoder::getQ(){
    return this->Q;
}

void Decoder::initLlr(vector<double> log){
    this->llr = log;
}

double Decoder::argTanh(int i , vector<int> c , int row){
    double arg = 1;

    for(int w = 0; w < c.size(); w++){
        if(w != i && c[w] != -1){
            arg *= tanh(0.5 * qMatrix[w][row]);
        }
    }
    
    if(arg <= (-0.99))
        return -0.99;
    else if(arg >= 0.99)
        return 0.99;
        
    return arg;
}

void Decoder::updateVariableMessages(vector<int> v, int row){
    for(int j = 0; j < v.size(); j++){
        if(v[j] != -1)
        qMatrix[row][j] = llr[row] + sumCheckMessage(j, v, row);
    }
}

void Decoder::qMatrixInit(){
    for(int i = 0; i < N; i++){
        vector<double> l(M, llr[i]);
        qMatrix.push_back(l);
    }
}

double Decoder::sumCheckMessage(int j, vector<int> v, int row){
    double temp = 0;
    for(int w = 0; w < v.size(); w++){
        if(w != j && v[w] != -1)
            temp += rMatrix[w][row];
    }

    return temp;
}
