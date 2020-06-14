#include "../PhysLib/simulation.h"

#define BOX_SIZE 20.0f

class Millikan: public Simulation {
private:
	Vector3D<float> gForce;			// gravitational acceleration
	Vector3D<float> eForce;			// eletric force 
	Vector3D<float> bForce;			// magnetic force
	Vector3D<float> sForce;			// stoke's force
public:
	bool eFieldOn;
	Vector3D<float> eField;			// eletric field
	Vector3D<float> bField;			// magnetic field
	Millikan(const float m, const int maxCharge = 0) : Simulation(7) {
		//Vector3D gravitation, is the gravitational acceleration
		this->gForce = Vector3D<float>(.0f, -9.81f,  .0f);			//set this class's gravitation

		// Create a Mass as a pointer and put it in the array
		// We can create particles with random charge or without it
		int signal[] = {1,-1};
		for (int a = 0; a < numOfParticles; ++a) 
			maxCharge ? particles[a] = 
				new Particle<float>(m, signal[std::rand() % 2] * std::rand() % maxCharge, 0) : particles[a] = new Particle<float>(m, 0, 0);
		restart();		//set position and velocity of the particles
	}
	virtual void solve() {
		//force will be applied therefore we need a "solve" method.
		for (int a = 0; a < numOfParticles; ++a) {
			//we will apply force to all particles
			eForce = eField * particles[a]->Q();
			bForce = (particles[a]->vel ^ bField) * particles[a]->Q();
			sForce =  particles[a]->vel * 20.0f * -1;
			
			particles[a]->applyForce(eForce + bForce + gForce * particles[a]->M() + sForce);
		}
	}
	void restart() {
		eField.setZero();
		bField.setZero();
		eFieldOn = false;
		for (int a = 0; a < numOfParticles; a++) {
			//a mass was created and we randomize his position
			particles[a]->pos.randomize((int)BOX_SIZE, true);
			particles[a]->pos.Y(15); particles[a]->pos.Z(1);
			//we set the mass's velocity to zero
			particles[a]->vel.setZero();
		}

	}
};
