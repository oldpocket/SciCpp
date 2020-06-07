/****************************************************************
  * File: main.cpp
  * Description: Main loop for our simulations
  * Author: Fabio Andreozzi Godoy
  * Date: 2020-06-06 - Modified: 2020-06-06
  */

#include <iostream>
#include "GUI/Simple_window.h"
#include "Simulations/millikan.cpp"

std::string getCmdOption(int argc, char* argv[], const std::string& option) {
    std::string cmd;
    for( int i = 0; i < argc; ++i) {
        std::string arg = argv[i];
        
        if(arg.find(option) == 0) {
            cmd = arg.substr(option.length());
            return cmd;
        }
    }
    return cmd;
}

int main(int argc,char* argv[]) {
    
    // Example:
    // $ ./scicpp -simulation=millikan
    std::string simulation = getCmdOption(argc, argv, "-simulation=");
    
    // We don't have a simulation with the given name. Let's finish the program and inform the user.
    if (simulation.empty()) {
        std::cout << "Simulation name is mandatory" << std::endl;
        return 1;
    }
    
    // We found the simulation that user asked. Let's start it.
    std::cout << "Starting system with simulation: " << simulation << std::endl;
    
    // In the future I'll change it with some kindo of IoC or Factory
    if (!simulation.compare("millikan")) {
    
        Millikan* millikan = new Millikan(3.0f, 10);
    }
    
    // GUI should receive the simulation class together. Or I should create the correct simulation GUI
    GUI::Simple_window win {640,480,"An empty window"};
    win.show();
    return Fl::run();
}
