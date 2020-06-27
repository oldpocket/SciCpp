/********************************************************************
  * Description: Implementation of the experiment of a Free Balling Ball
  * Author: Fabio Andreozzi Godoy
  * Date: 2020-06-26 | Modified: 2020-06-26
  */

#ifndef FREEFALLINGBALL_H_INCLUDED
#define FREEFALLINGBALL_H_INCLUDED

#include "../Laboratory/experiment.h"
#include "../Simulations/freeFallingBall.cpp"

class FreeFallingBall: public Experiment {
private:
    
public:
    FreeFallingBall(bool consoleOnly_);
    
    virtual void execute();
    
};

#endif // FREEFALLINGBALL_H_INCLUDED

