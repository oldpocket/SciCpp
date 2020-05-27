#include "simulation.h"

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
		// We can create masses with random charge or without it
		int signal[] = {1,-1};
		for (int a = 0; a < numOfMasses; ++a) 
			maxCharge ? masses[a] = 
				new Mass<float>(m, signal[std::rand() % 2] * std::rand() % maxCharge) : masses[a] = new Mass<float>(m);
		restart();		//set position and velocity of the masses
	}
	virtual void solve() {
		//force will be applied therefore we need a "solve" method.
		for (int a = 0; a < numOfMasses; ++a) {
			//we will apply force to all masses
			eForce = eField * masses[a]->Q();
			bForce = (masses[a]->vel ^ bField) * masses[a]->Q();
			sForce =  masses[a]->vel * 20.0f * -1;
			
			masses[a]->applyForce(eForce + bForce + gForce * masses[a]->M() + sForce);
		}
	}
	void restart() {
		eField.setZero();
		bField.setZero();
		eFieldOn = false;
		for (int a = 0; a < numOfMasses; a++) {
			//a mass was created and we randomize his position
			masses[a]->pos.randomize((int)BOX_SIZE, true);
			masses[a]->pos.Y(15); masses[a]->pos.Z(1);
			//we set the mass's velocity to zero
			masses[a]->vel.setZero();
		}

	}
};
