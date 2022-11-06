/********************************************************************
  * Description: Base class for the execution of an experiment
  * Author: Fabio Andreozzi Godoy
  * Date: 2020-06-26 | Modified: 2020-06-26
  */

#ifndef EXPERIMENT_H_INCLUDED
#define EXPERIMENT_H_INCLUDED

#include "../Simulations/simulation.h"

class Experiment {
    protected:
        simulations::Simulation* _simulation;
        bool _consoleOnly;
    public:
        Experiment(bool consoleOnly_ = false) {
            _consoleOnly = consoleOnly_;
        }
        
        virtual void execute() = 0;
    
};

#endif // EXPERIMENT_H_INCLUDED
