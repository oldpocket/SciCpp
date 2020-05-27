/****************************************************************
  * File: simulation.h
  * Description: some classes to be used in physics simulations
  * Author: Fabio Andreozzi Godoy
  * Date: 02/02/2006 - Modified: 02/03/2006
  */

#include "physics.h"

// class Simulation is a container object for simulating masses
class Simulation {
	public:
		int numOfMasses;				// number of masses in this container
		Mass<float>** masses;				// masses are held by pointer to pointer
	
		// Constructor creates some masses with mass values m
		Simulation(int numOfMasses) {
			this->numOfMasses = numOfMasses;
			masses = new Mass<float>*[numOfMasses];	// Create an array of pointers
			// Each simulation need to init properly mass and charge 
		}
		// delete the masses created
		virtual void release() {
			// we will delete all of them
			for (int a = 0; a < numOfMasses; ++a) {
				delete(masses[a]);
				masses[a] = NULL;
			}
			delete(masses);
			masses = NULL;
		}
		// return a pointer of the mass with the desire index
		Mass<float>* getMass(int index) {
			if (index < 0 || index >= numOfMasses)	// if the index is not in the array
				return NULL;			// then return NULL

			return masses[index];			// get the mass at the index
		}
		// this method will call the init() method of every mass
		virtual void init() {
		for (int a = 0; a < numOfMasses; ++a)		// We will init() every mass
			masses[a]->init();			// call init() method of the mass
		}

		// no implementation because no forces are wanted in this basic container
		virtual void solve() {
			// in advanced containers, this method will be overrided and some forces will act on masses
		}

		// Iterate the masses by the change in time
		virtual void simulate(float dt) {
			for (int a = 0; a < numOfMasses; ++a)	// We will iterate every mass
				masses[a]->simulate(dt);	// Iterate the mass and obtain new position and new velocity
		}

		// The complete procedure of simulation
		virtual void operate(float dt) {
			init();					// Step 1: reset forces to zero
			solve();				// Step 2: apply forces
			simulate(dt);				// Step 3: iterate the masses by the change in time
		}

};

