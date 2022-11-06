/****************************************************************
  * File: general.h
  * Description: general purpose rotines within a class
  * Author: Fabio Andreozzi Godoy
  * Date: 24/06/2006 - Modified: 24/06/2006
  */

#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

#include <iostream>
#include <cmath>

class GeneralPurpose {
	public:
		GeneralPurpose() {}
		~GeneralPurpose() {}
		// getRandom() return a random number that can be positive,
		//             negative, integer or float
		// limit   : max_random value 
		// decimal_: 'numero de casas decimais'
		// signal_ : random signal or not
		static float getRandom(const int limit, const int decimal_, const bool signal_) {
		        int decimal = 1;
		        short int signal = 1;
		        if (decimal_ > 0) decimal = (int)pow(10, decimal_);
		        if (signal_)      signal  = std::rand() % 2 ? -1 : 1;
		        return (float)(std::rand() % (limit * decimal) * signal)/decimal;
		}
	
        // Return the value of a given command received from the command line
		static std::string getCmdOption(int argc, char* argv[], const std::string& option) {
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
};


#endif // GENERAL_H_INCLUDED
