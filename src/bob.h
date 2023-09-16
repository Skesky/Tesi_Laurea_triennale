#ifndef BOB_H
#define BOB_H

using namespace std;
 
class Bob{

    private:
    normal_distribution<> d_q;
    normal_distribution<> d_p;
    uniform_int_distribution<> distribution;
    public:
    Bob();
    pair<double, Component> measure(State state, default_random_engine gen);

    private:
    void gaussianSetting(State state);
};
 
#endif 