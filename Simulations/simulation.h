/********************************************************************
  * Description: Simulation base class to be used in the experiments
  * Author: Fabio Andreozzi Godoy
  * Date: 2006-02-02 | Modified: 2020-06-17
  */

#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "../PhysLib/particle.h"
#include "../Integrator/integrator.h"

namespace simulations {

// class Simulation is a container object for simulating masses
class Simulation {
    private:
        float _elapsedTime = 0;
        float _slowMotionRatio = 0;
     
    protected:
        // Particles of the simulation
        Particle<float>** particles;
        // Each particle must have an integrator associated with it
        Integrator<float>** integrators;
        
        
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
		virtual void simulate(int numOfIterations, float dt_) {
            // We will iterate every particle by the number of iteractions
            for (int b = 0; b < numOfIterations; ++b)
                for (int a = 0; a < numOfParticles; ++a) {
                    
                    // Iterate the integrators and obtain new position and velocity for the related particle
                   integrators[a]->integrate(dt_);
                }
		}        
        
	public:
        // Number of particles in this container
		int numOfParticles;
        
		// Basic Constructor, creates some particles but do not initialize it
		Simulation(int numOfParticles_, float slowMotionRatio_ = 1) {
            _slowMotionRatio = slowMotionRatio_;
            
			this->numOfParticles = numOfParticles_;
			particles = new Particle<float>*[numOfParticles_];	// Create an array of pointers
			integrators = new Integrator<float>*[numOfParticles_];
			// Each simulation need to init properly the properties of the particle (mass, charge, etc)
		}
		
		// Create the array with particles, but also initialize them with the given mass.
		Simulation(int numOfParticles_, float m_, float slowMotionRatio_) 
        : Simulation(numOfParticles_, slowMotionRatio_) {

            // We will step to every pointer in the array
			for (int a = 0; a < numOfParticles_; ++a) {	        
                
                // Create a Particle as a pointer and put it in the array
				particles[a] = new Particle<float>(m_, 0, 0);
                
                // Each particle need an Integrator to solve the moviment equations
                integrators[a] = Integrator<float>::Create(IntegratorType::EULER, particles[a]);
            }
        }
		
		// Delete the created particles
		virtual void release() {
			// We will delete all of them
			for (int a = 0; a < numOfParticles; ++a) {
				
                delete(integrators[a]);
                integrators[a] = NULL;
                particles[a] = NULL;
			}
			delete(particles);
			particles = NULL;
            
            delete(integrators);
            integrators = NULL;
		}
		
		// Return the total elapsed time from the simulation
		float getElapsedTime() {
            return _elapsedTime;
        }

		// Return a pointer of the particle with the desire index
		Particle<float>* getParticle(int index_) {
            // If the index is not in the array the return NULL
			if (index_ < 0 || index_ >= numOfParticles)	
				return NULL;

            // The particle at the given index
			return particles[index_];
		}
	
		// A complete simulation operation or iteration is composed of the calls on this method
        // milliseconds_ should be calculated like: 
        // int milliseconds_ = currentTime_ - lastTime_;
        // milliseconds_ must be in Milliseconds
		virtual void operate(int milliseconds_) {
			init();			// Step 1: reset forces to zero
			solve();		// Step 2: apply forces
            
            // Let's convert milliseconds to seconds
            float dt = milliseconds_ / 1000.0f;
            
            // Divide dt by slowMotionRatio to obtain normalized dt
            dt /= _slowMotionRatio;			
            
            // Add it to the simulation's total elapsed time
            _elapsedTime += dt;
           
            // Maximum possible dt Is 0.1 seconds
            // This is needed so we do not pass over a non precise dt value
            float maxPossible_dt = 1.0f;
            
            // Calculate Number Of Iterations To Be Made At This Update Depending On maxPossible_dt And dt
            int numOfIterations = (int)(dt / maxPossible_dt);
            
            // dt Should Be Updated According To numOfIterations
            if (numOfIterations != 0) dt = dt / numOfIterations;	
             
			simulate(numOfIterations, dt);	// Step 3: iterate the masses by the change in time
		}
};

}

#endif // SIMULATION_H_INCLUDED
