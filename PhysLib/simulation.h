/********************************************************************
  * Description: Simulation base class to be used in the experiments
  * Author: Fabio Andreozzi Godoy
  * Date: 2006-02-02 | Modified: 2020-06-14
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
        
        // The basic Simulation live cicle is composed of the 3 methods bellow
        
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

		// Evolve the particles considering the change in time
		virtual void simulate(float dt_) {
            // We will iterate every particle
			for (int a = 0; a < numOfParticles; ++a)	
                // Iterate the particles and obtain new position and new velocity
				particles[a]->simulate(dt_);	        
		}        
        
	public:
		int numOfParticles;			      // number of particles in this container
		
		// Basic Constructor, creates some particles but do not initialize it
		Simulation(int numOfParticles_) {
			this->numOfParticles = numOfParticles_;
			particles = new Particle<float>*[numOfParticles_];	// Create an array of pointers
			integrators = new Integrator<float>*[numOfParticles_];
			// Each simulation need to init properly the properties of the particle (mass, charge, etc)
		}
		
		// Create the array with particles, but also initialize them with the given mass.
		Simulation(int numOfParticles_, float m_) : Simulation(numOfParticles_) {

			for (int a = 0; a < numOfParticles_; ++a) {	        // We will step to every pointer in the array
				particles[a] = new Particle<float>(m_, 0, 0);	// Create a Mass as a pointer and put it in the array
                integrators[a] = Integrator<float>::Create(IntegratorType::EULER, particles[a]);
            }
        }
		
		// Delete the particles created
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
		Particle<float>* getMass(int index_) {
			if (index_ < 0 || index_ >= numOfParticles)	// if the index is not in the array
				return NULL;			                // then return NULL

			return particles[index_];			        // get the mass at the index
		}
	
		// A complete simulation operation or iteration is composed of the calls on this method
		virtual void operate(float dt_) {
			init();			// Step 1: reset forces to zero
			solve();		// Step 2: apply forces
			simulate(dt_);	// Step 3: iterate the masses by the change in time
		}
};

#endif // SIMULATION_H_INCLUDED
