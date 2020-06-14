/****************************************************************
  * File: simulation.h
  * Description: some classes to be used in physics simulations
  * Author: Fabio Andreozzi Godoy
  * Date: 02/02/2006 - Modified: 02/03/2006
  */

#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "../PhysLib/particle.h"
#include "../Integrator/integrator.h"

// class Simulation is a container object for simulating masses
class Simulation {
    protected:
        Particle<float>** particles;	  // particles of the simulation
        Integrator<float>** integrators;  // each particle must have an integrator associated with it
	public:
		int numOfParticles;			      // number of masses in this container
		
	
		// Constructor creates some masses with mass values m
		Simulation(int numOfParticles_) {
			this->numOfParticles = numOfParticles_;
			particles = new Particle<float>*[numOfParticles_];	// Create an array of pointers
			integrators = new Integrator<float>*[numOfParticles_];
			// Each simulation need to init properly the properties of the particle (mass, charge, etc)
		}
		
		Simulation(int numOfParticles_, float m) : Simulation(numOfParticles_) {

			for (int a = 0; a < numOfParticles_; ++a) {	        // We will step to every pointer in the array
				particles[a] = new Particle<float>(m, 0, 0);	// Create a Mass as a pointer and put it in the array
                integrators[a] = Integrator<float>::Create(IntegratorType::EULER, particles[a]);
            }
        }
		
		// Delete the masses created
		virtual void release() {
			// We will delete all of them
			for (int a = 0; a < numOfParticles; ++a) {
				delete(particles[a]);
				particles[a] = NULL;
			}
			delete(particles);
			particles = NULL;
		}

		// Return a pointer of the mass with the desire index
		Particle<float>* getMass(int index) {
			if (index < 0 || index >= numOfParticles)	// if the index is not in the array
				return NULL;			                // then return NULL

			return particles[index];			        // get the mass at the index
		}
	
        // Calling init(), the simulation we will initialize each particle in the system
		virtual void init() {
            for (int a = 0; a < numOfParticles; ++a)
                // Starting the particle
                particles[a]->init();
		}

		// Solve method MUST be overriden by subclasses. 
		// Subclasses MUST apply the forces interacting with the system here.
		virtual void solve() {
			// in advanced containers, this method will be overrided and some forces will act at particles
		}

		// Iterate the masses by the change in time
		virtual void simulate(float dt_) {
            // We will iterate every particle
			for (int a = 0; a < numOfParticles; ++a)	
                // Iterate the particles and obtain new position and new velocity
				particles[a]->simulate(dt_);	        
		}

		// The complete procedure of simulation
		virtual void operate(float dt_) {
			init();			// Step 1: reset forces to zero
			solve();		// Step 2: apply forces
			simulate(dt_);	// Step 3: iterate the masses by the change in time
		}
};

#endif // SIMULATION_H_INCLUDED
