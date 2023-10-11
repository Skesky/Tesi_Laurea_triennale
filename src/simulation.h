#ifndef SIMULATION_H
#define SIMULATION_H

using namespace std;

class Simulation{

    private:
    Alice alice;
    Bob bob;
    Channel channel;
    int nRound;
    ofstream outputFile;
    random_device rd;
    State* aliceStates;
    pair<double, Component> *bobMeasures;
    bool eve;

    public:
    Simulation(int, string, bool);
    State* getAliceStates();
    pair<double, Component>* getBobMeasures();
    void freeMem();
    void startSimulation();
    Bob getBob();
    
};
 
#endif 