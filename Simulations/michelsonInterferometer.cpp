#include "../PhysLib/simulation.h"

Vector3D<float> aether(.0f, .0f, .0f);

class MichelsonInterferometer: public Simulation {
	private:
	public:
		//Constructor firstly constructs its super class with 1 mass and 1 kg
		MichelsonInterferometer() : Simulation(2, 1.0f) {
			restartFoton();
		}
		// restartFoton() put the foton on origin of the lab coordenates
		void restartFoton() {
			for (int a = 0; a < numOfMasses; a++) {
				//a mass was created and we set its position to the origin
				particles[a]->pos.set(-20.0f, .0f, .0f);
				//we set the mass's velocity to (1.0f, 0.0f, 0.0f)
				particles[a]->vel.set(+10.0f, .0f, .0f);
			}
		}
		// pbc() verify "periodic boundary conditions" to our problem
		void pcb() {
			for (int i = 0; i < numOfMasses; i++) {
				Vector3D<float>* pos = &particles[i]->pos;
				// verify bound conditions - splitter and mirror for each particle
				// particle 0 change Y direction on the splitter and particle 1 go ahead
				switch (i) {
					case 0:
						if (pos->Y() > 19.0f) particles[i]->vel.Y(-particles[i]->vel.Y());
						if (std::abs(pos->Y()-pos->X()) < .02f) {
							if (particles[i]->vel.X() > .0f) {
								particles[i]->vel.set(.0f, particles[i]->vel.X(), .0f);
								particles[i]->pos.X(.0f);
								break;
							}
							if (particles[i]->vel.Y() < .0f) {
								particles[i]->vel.set(particles[i]->vel.Y(), .0f, .0f);
								particles[i]->pos.Y(.0f);
								break;
							}
						}
						break;
					case 1:
						if (pos->X() > 19.0f) particles[i]->vel.X(-particles[i]->vel.X());
						break;
					default:
						break;
				}
				if (pos->X() < -20.0f) particles[i]->vel.set(.0f, .0f, .0f);
			}
		}
		// solve() is overriden because we have forces to be applied
		virtual void solve() {
			for (int a = 0; a < numOfMasses; a++)
				particles[a]->applyForce(aether); 
		}
		// operate() is orverriden because we need to include pcb check
		virtual void operate(float dt) {
			Simulation::operate(dt);
			pcb();
		}

};
