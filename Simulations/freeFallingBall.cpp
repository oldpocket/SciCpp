#include "../PhysLib/simulation.h"
#include "../Integrator/integrator.h"

#define BOX_SIZE2 20

class FreeFallingBall: public Simulation {
private:
	Vector3D<float> gForce;			// gravitational acceleration
public:
	FreeFallingBall() : Simulation(1) {
		//Vector3D gravitation, is the gravitational acceleration
		this->gForce = Vector3D<float>(.0f, -9.81f,  .0f);			//set this class's gravitation

		// Create a Mass as a pointer and put it in the array
		for (int a = 0; a < numOfParticles; ++a) {
            particles[a] = new Particle<float>(1, 0, 0);
        }
		restart();		//set position and velocity of the masses
	}
	virtual void solve() {
		//force will be applied therefore we need a "solve" method.
		for (int a = 0; a < numOfParticles; ++a) {
			//we will apply force to all masses
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

