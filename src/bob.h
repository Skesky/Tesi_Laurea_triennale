#ifndef BOB_H
#define BOB_H

using namespace std;
 
class Bob{

    private:
    normal_distribution<> d_q;
    normal_distribution<> d_p;
    uniform_int_distribution<> distribition;
    public:
    Bob();
    double measure(cState state, default_random_engine gen);
    int selectMeasure();

    private:
    void gaussianSetting(cState state);
};
 
#endif 