/********************************************************************
  * Description: 
  * Author: Fabio Andreozzi Godoy
  * Date: 2020-06-26 | Modified: 2020-06-26
  */

#include <chrono>
#include <thread>
#include "../Laboratory/freeFallingBall.h"

FreeFallingBall::FreeFallingBall(bool consoleOnly_) 
    : Experiment(consoleOnly_) {
        _simulation = new simulations::FreeFallingBall();
};

void FreeFallingBall::execute() {
    
    auto start = std::chrono::steady_clock::now();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    do {
        std::cout << "-------" << std::endl;
        auto end = std::chrono::steady_clock::now();
        auto milis = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        _simulation->operate(milis);
        std::cout << _simulation->getElapsedTime() << std::endl;
        std::cout << milis << std::endl;
        std::cout << "POS "; _simulation->getParticle(0)->pos.print();
        std::cout << "VEL "; _simulation->getParticle(0)->vel.print();
        std::cout << "FOR "; _simulation->getParticle(0)->force.print();
        
        start = std::chrono::steady_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
    } while (_simulation->getElapsedTime() < 15);
};

