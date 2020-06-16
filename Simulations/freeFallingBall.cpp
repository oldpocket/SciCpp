#include "../PhysLib/simulation.h"
#include "../Integrator/integrator.h"

#define BOX_SIZE2 20

class FreeFallingBall: public Simulation {
private:
    // Gravitational acceleration
	Vector3D<float> gForce;

public:
	
    FreeFallingBall() : Simulation(1) {
        
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
			particles[a]->applyForce(gForce * particles[a]->M());
		}
	}
	
	void restart() {
		for (int a = 0; a < numOfParticles; a++) {
			// Randomize the possition 
            // (actually we want only Y, so we correct X and Z later)
			particles[a]->pos.randomize((int)BOX_SIZE2, true);
			// Midlle of the screen
            particles[a]->pos.X(15); 
            // 2D simulation, Z is not important
            particles[a]->pos.Z(1);
			//we set the mass's velocity to zero
			particles[a]->vel.setZero();
		}

	}
};

