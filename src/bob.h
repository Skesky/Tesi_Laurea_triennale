#ifndef BOB_H
#define BOB_H

using namespace std;
 
class Bob{

    private:
    normal_distribution<> d_q;
    normal_distribution<> d_p;

    public:
    Bob();
    complex<double> measure(cState state, default_random_engine gen);

    private:
    void gaussianSetting(cState state);
};
 
#endif 