#ifndef RECONCILIATION_H
#define RECONCILIATION_H

using namespace std;
 
class Reconciliation{

    private:
    vector<double> normalizedAliceData;
    vector<double> normalizedBobData;
    //vector<double> awgnVariances;
    vector<double> dummyMessage;
    vector<double> llr;

    public:
    Reconciliation(vector<double>, vector<double>, double);
    string prdMatrix(bitset<K>, vector< bitset<K> >);
    string andBaB(bitset<K>);
    vector<double> signModulation(bitset<N>);
    void dMessage(vector<double>);
    vector<double> getNormalizedAliceData();
    vector<double> getLlr();
    //bitset<K> genBitString(default_random_engine);

    private:
    void normalizeBob(vector<double>, double);
    void normalizeAlice(vector<double>);
    void computeLlr();
};
 
#endif 