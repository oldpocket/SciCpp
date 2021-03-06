/******************************************************************************/
/*   Function : Implementation of a free falling particle experiment          */
/*  Developer : Fabio Andreozzi Godoy                                         */
/*       Date : 2020-06-11 - Ultima atualizacao : 2020-06-17                  */
/******************************************************************************/

#include "../Simulations/simulation.h"
#include "../Integrator/integrator.h"

#define BOX_SIZE2 20

namespace simulations {

class FreeFallingBall: public Simulation {
private:
    // Gravitational acceleration
	Vector3D<float> gForce;

public:
	
    FreeFallingBall(float m_, float precision_) : Simulation(1, m_, 1, precision_) {
        
		//Defining direction and magnitude of gravitational acceleration
		this->gForce = Vector3D<float>(.0f, -9.81f,  .0f);

		// Base constructor will generate the particles 

        // Set position and velocity of the particles
		restart();		
	}
	
	virtual void solve() {
		// Applying the forces from our system. In this case, we need only gravitational force.
		for (int a = 0; a < numOfParticles; ++a) {
			// Force need to be applied to all particles individualy.
            
			// Falling Ball -> F =  m * a
            particles[a]->force = gForce * particles[a]->M();
		}
	}
	
	void restart() {
		for (int a = 0; a < numOfParticles; ++a) {
			// Randomize the possition 
            // (actually we want only Y, so we correct X and Z later)
			particles[a]->pos.randomize((int)BOX_SIZE2, false);
			// Midlle of the screen
            particles[a]->pos.X(15); 
            // 2D simulation, Z is not important
            particles[a]->pos.Z(1);
			//we set the mass's velocity to zero
			particles[a]->vel.setZero();
		}

	}
};

}
