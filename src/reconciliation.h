#ifndef RECONCILIATION_H
#define RECONCILIATION_H

using namespace std;
 
class Reconciliation{

    private:
    /*normal_distribution<> d_q;
    normal_distribution<> d_p;
    uniform_int_distribution<> distribution;*/

    public:
    Reconciliation();
    string prdMatrix(bitset<K>, vector< bitset<K> >);
    string andBaB(bitset<K>);
    vector<double> signModulation(vector<double>, bitset<K>);
    vector<double> demodulation(vector<double>, vector<double> );
    //bitset<K> genBitString(default_random_engine);
};
 
#endif 