/********************************************************************
  * Description: 
  * Author: Fabio Andreozzi Godoy
  * Date: 2020-06-26 | Modified: 2020-06-26
  */

#include <chrono>
#include <thread>
#include <iomanip>
#include "../Laboratory/freeFallingBall.h"

FreeFallingBall::FreeFallingBall(bool consoleOnly_) 
    : Experiment(consoleOnly_) {
        _simulation = new simulations::FreeFallingBall(1, 0.01f);
};

void FreeFallingBall::executeConsole()
{
    auto start = std::chrono::steady_clock::now();
    std::cout << "T, X, Y, Z, Vx, Vy, Vz, Ax, Ay, Az" << std::endl;
    std::cout << std::setprecision(3) << std::fixed;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    do {
        auto end = std::chrono::steady_clock::now();
        auto milis = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        _simulation->operate(milis);
        std::cout << _simulation->getElapsedTime();
        _simulation->getParticle(0)->pos.print(',', ',', '\0', false);
        _simulation->getParticle(0)->vel.print(',', ',', '\0', false);
        _simulation->getParticle(0)->force.print(',', ',', '\0', true);
        
        start = std::chrono::steady_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
    } while (_simulation->getElapsedTime() < 15);
}


void FreeFallingBall::execute() {
    if (_consoleOnly) executeConsole();
    
    

};

