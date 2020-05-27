#include "simulation.h"

class michelsonInterferometer: public Simulation {
	private:
	public:
		//Constructor firstly constructs its super class with 1 mass and 1 kg
		michelsonInterferometer() : Simulation(2, 1.0f) {
			restartFoton();
		}
		// restartFoton() put the foton on origin of the lab coordenates
		void restartFoton() {
			for (int a = 0; a < numOfMasses; a++) {
				//a mass was created and we set its position to the origin
				masses[a]->pos.set(-20.0f, .0f, .0f);
				//we set the mass's velocity to (1.0f, 0.0f, 0.0f)
				masses[a]->vel.set(+10.0f, .0f, .0f);
			}
		}
		// pbc() verify "periodic boundary conditions" to our problem
		void pcb() {
			for (int i = 0; i < numOfMasses; i++) {
				Vector3D<float>* pos = &masses[i]->pos;
				// verify bound conditions - splitter and mirror for each particle
				// particle 0 change Y direction on the splitter and particle 1 go ahead
				switch (i) {
					case 0:
						if (pos->Y() > 19.0f) masses[i]->vel.Y(-masses[i]->vel.Y());
						if (std::abs(pos->Y()-pos->X()) < .02f) {
							if (masses[i]->vel.X() > .0f) {
								masses[i]->vel.set(.0f, masses[i]->vel.X(), .0f);
								masses[i]->pos.X(.0f);
								break;
							}
							if (masses[i]->vel.Y() < .0f) {
								masses[i]->vel.set(masses[i]->vel.Y(), .0f, .0f);
								masses[i]->pos.Y(.0f);
								break;
							}
						}
						break;
					case 1:
						if (pos->X() > 19.0f) masses[i]->vel.X(-masses[i]->vel.X());
						break;
					default:
						break;
				}
				if (pos->X() < -20.0f) masses[i]->vel.set(.0f, .0f, .0f);
			}
		}
		// solve() is overriden because we have forces to be applied
		virtual void solve() {
			for (int a = 0; a < numOfMasses; a++)
				masses[a]->applyForce(aether); 
		}
		// operate() is orverriden because we need to include pcb check
		virtual void operate(float dt) {
			Simulation::operate(dt);
			pcb();
		}

};
