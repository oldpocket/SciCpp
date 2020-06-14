/****************************************************************
  * File: mass.h
  * Description: Represents a Particle, to be used in physics simulations
  * Author: Fabio Andreozzi Godoy
  * Date: 01/02/2006 - Modified: 24/06/2006
  */

#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include "../Util/general.h"
#include "../MathLib/vector_3d.h"

// class Particle discribe a simple particle (or object)
template <class T> class Particle {
	private:
		T m;				// The mass value
		T e;                // Energy of the mass
		T q;				// The charge value (integer multiple of 'e')
	public:
		// Constructor
		Particle(T m_, T e_, T q_) {
			this->m = m_;
			this->e = e_;
			this->q = q_;

			init();
		}
		// Access (read and write) to private members
		void M(T m_) { m = m_; }        // Set a value to the mass
		T M() { return m; }             // Return the value of the mass
		void E(T e_) { e = e_; }        // Set a value to the energy of the particle
		T E() { return e; }             // Return the energy of the mass
		void Q(T q_) { q = q_; }      // Set a value to the charge of the particle
		T Q() { return q; }           // Return the value of the charge
		Vector3D<T> pos;		// Position in space
		Vector3D<T> vel;		// Velocity
		Vector3D<T> force;		// Force applied on this mass at an instance
	  	// void applyForce(Vector3D force) method is used to add external force to the mass.
		void applyForce(Vector3D<T> force) {
			this->force += force;
		}
	  	// void init() method sets the force values to zero
		void init() { force.set(.0f, .0f, .0f); }
	  	// void simulate(T dt) method calculates the new velocity and new position of
	  	// the mass according to change in time (dt). The Euler or Verlet Method is used.
		void simulate(T dt) {
			//Vector3D<T> tmpPos;
			//euler
			vel += (force / m) * dt;
			pos += vel * dt;
			//verlet
			//vel += (force)*dt/(m);
			//pos += vel*dt + (force)*dt*dt/(2*m);
			/*tmpPos = pos;
			pos += (pos-lastPos)*(dt/lastDt) + (force)*dt*dt/(m);
			vel += (force)*dt/(m);
			//vel = (pos-lastPos)/(2*dt);
			lastDt  = dt;
			lastPos = tmpPos;*/
			
		}
};


#endif // PARTICLE_H_INCLUDED
