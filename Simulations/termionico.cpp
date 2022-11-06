/****************************************************************
  * File: thermionic.h
  * Description: Thermionic effect simulation
  * Author: Fabio Andreozzi Godoy
  * Date: 05/05/2006 - Modified: 29/06/2006
  */

#include "../Simulations/simulation.h"

#define BOX_SIZE 20.0f
#define NUM_OF_PARTICLES 10000

namespace simulations {

class ThermionicEmission: public Simulation {
private:
	float temperature;	// actual temperature of the system
	float workFunction;
	float energy;
	int   goCounter;	// number of actives particles on the system
	int   ctime;
public:
	int   current;
	bool  goParticle[NUM_OF_PARTICLES];
	void  setTemperature(const float temp_) { if (temp_ > -1) temperature = temp_; }
	float getTemperature() { return temperature; }
	Vector3D<float> eField;			// eletric field
	// constructor
	ThermionicEmission(const float m, const int maxEnergy = .0f) : Simulation(NUM_OF_PARTICLES) {
		// Create a Mass as a pointer and put it in the array
		// We can create particles with random energy or without it
		for (int a = 0; a < numOfParticles; ++a) 
			maxEnergy ? particles[a] = 
				new Particle<float>(m, (float)(std::rand() % maxEnergy), 1) : particles[a] = new Particle<float>(m, .0f, 1);
		restart();		//set initial condition of the particles
	}
	// sort a number of particles proportional to subList and probability arguments
	void sort(float energy) {
		int tmpCounter = goCounter;
		int sort, trySort = 0;
		int flux = (int)(mbDistribution(energy) * (numOfParticles/2));   // max number of particles to be sort

		if (energy < workFunction) return;
		for (int i = 0; i < flux; i++) {
			do {
				sort = std::rand() % numOfParticles;
				trySort++;
			} while ((goParticle[sort]) && (trySort < numOfParticles)); 
			if (trySort < numOfParticles) {
				goParticle[sort] = true;
				particles[sort]->vel.Y(sqrt(2*energy));
				particles[sort]->pos.Y(.1f);
				goCounter++;
			} else i = flux;
		}
		//printf(">>e = %.2f p = %.4f #tot = %d  now = %d #\n", energy, probability, goCounter, goCounter-tmpCounter);
	}
	//force will be applied therefore we need a "solve" method.
	virtual void solve() {
		// apply the forces
		sort(std::rand()%100);
		for (int a = 0; a < numOfParticles; ++a) {
			//we'll apply force to all particles
			if (goParticle[a]==true) {
				if ((particles[a]->pos.Y() < 0) || (particles[a]->pos.Y() > 20)) {
					goParticle[a] = false;
					goCounter--;
					if (particles[a]->pos.Y() > 20) current++;
				} else {
					float distY = particles[a]->pos.Y();
					float imgForce = .001*(goCounter); ///(distY*distY);
					particles[a]->force += (eField + Vector3D<float>(.0f, -imgForce, .0f) );
				}
			}
		}
	}
	// operate is override because we need to show the current	
	virtual void operate(float dt) {
		Simulation::operate(dt);
		amperemeter();
	} 
	// restart all the system
	void restart() {
		eField.setZero();
		temperature = 30.0f;
		energy = workFunction = 15.0f;
		goCounter  = 0;
		ctime      = 0;
		current    = 0;
		for (int a = 0; a < numOfParticles; a++) {
			goParticle[a] = false;
			//a mass was created and we randomize his position
			particles[a]->pos.randomize((int)BOX_SIZE, true);
			particles[a]->pos.Y(0); particles[a]->pos.Z(0);
			//we set the mass's velocity to zero
			particles[a]->vel.setZero();
		}

	}
	// return the probability according Maxwell-Boltzman distribution probability of one energy
	float mbDistribution(float energy){
		float k=1;
		//return 200*2*sqrt(energy/(3.14*pow((k*temperature),3)))*exp(-energy/(k*temperature));
		return sqrt(1/(2*3.14*temperature))*exp(-energy/(k*temperature));
	}
	// show the current
	void amperemeter(void) {
		ctime++;
		if (!(ctime % 60)) {
			printf("%.2f\t%d\n", eField.Y(), current);
			eField += Vector3D<float>(.0f, .2f, .0f);
			current = ctime = 0;
			if (eField.Y() > 200) exit(0);
		}
	}
};

}
