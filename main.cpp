/****************************************************************
  * File: main.cpp
  * Description: Main loop for our simulations
  * Author: Fabio Andreozzi Godoy
  * Date: 2020-06-06 - Modified: 2020-06-27
  */

#ifndef MAIN_SOURCE
#define MAIN_SOURCE

#include <iostream>
#include "Util/general.h"
#include "Laboratory/freeFallingBall.h"

int main(int argc,char* argv[]) {
    
    // Example:
    // $ ./scicpp -simulation=millikan
    std::string simulation = GeneralPurpose::getCmdOption(argc, argv, "-simulation="); 
    
    // We don't have a simulation with the given name. Let's finish the program and inform the user.
    if (simulation.empty()) {
        std::cout << "Simulation name is mandatory" << std::endl;
        return 1;
    }
    
    // We found the simulation that user asked. Let's start it.
    std::cout << "Starting system with simulation: " << simulation << std::endl;
    
    // In the future I'll change it with some kindo of IoC or Factory
    if (!simulation.compare("millikan"))                std::cout << "To be done..." << std::endl;
    if (!simulation.compare("michelsonInterferometer")) std::cout << "To be done..." << std::endl;
    if (!simulation.compare("thermionicEmission"))      std::cout << "To be done..." << std::endl;
    if (!simulation.compare("freeFallingBall")) {
        FreeFallingBall* f = new FreeFallingBall(false);
        f->execute();
    }

    return 0;
}

#endif // MAIN_SOURCE
