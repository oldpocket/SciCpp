/****************************************************************
  * File: physics.h
  * Description: some classes to be used in physics simulations
  * Author: Fabio Andreozzi Godoy
  * Date: 01/02/2006 - Modified: 24/06/2006
  */

#include "general.h"

// class Vector3D is a general vector with some rotines to work in a 3D space
template <class T> class Vector3D {
	private:
		T x;
		T y;
		T z;
	public:
		// Constructor
		Vector3D() : x(0), y(0), z(0) {}
		Vector3D(T x, T y, T z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}
		// Create a random vector
		Vector3D(const int limit, const bool bsig) {
			randomize(limit, bsig);
		}
		// Access (read and write) to private members
		void X(T _x) { x = _x; }
		T X() { return x; }
		void Y(T _y) { y = _y; }
		T Y() { return y; }
		void Z(T _z) { z = _z; }
		T Z() { return z; }
		void set(T _x, T _y, T _z) { x = _x; y = _y; z = _z; }
		void setZero() { x = y = z = 0; }
		// Overloding a set of useful operators
		Vector3D& operator= (Vector3D v) {
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}
		Vector3D operator+ (const Vector3D<T> v) { return Vector3D(x + v.x, y + v.y, z + v.z); }
		Vector3D operator- (const Vector3D<T> v) { return Vector3D(x - v.x, y - v.y, z - v.z); }
 		// cross product
		Vector3D operator^ (const Vector3D<T> v) { return Vector3D(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
		Vector3D operator* (T value) { return Vector3D(x * value, y * value, z * value); }
		Vector3D operator/ (T value) { return Vector3D(x / value, y / value, z / value); }
		Vector3D& operator+= (Vector3D v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}
		Vector3D& operator-= (Vector3D v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		Vector3D& operator*= (T value) {
			x *= value;
			y *= value;
			z *= value;
			return *this;
		}
		Vector3D& operator/= (T value) {
			x /= value;
			y /= value;
			z /= value;
			return *this;
		}
		// operator-() multiply x, y and z by -1
		Vector3D operator- () { return Vector3D(-x, -y, -z); }
		// Some operations with this vector

		// print() print x, y and z values
		void print() { std::cout << "(" << (T)x << "," << (T)y << "," << (T)z << ")" << std::endl; }
		// length() returns the length of this Vector3D
		float length() { return sqrtf(x*x + y*y + z*z); };
		// unit() returns a new Vector3D (a unitized version of this one)
		Vector3D<T> unit() {
			float length = this->length();
			if (length == .0f) return *this;
			return Vector3D<T>(x / length, y / length, z / length);
		}
		// unitize() normalizes this Vector3D (give the direction)
		void unitize() {
			float length = this->length();
			if (length == .0f) return;
			x /= length;
			y /= length;
			z /= length;
		}
		// randomize() randomize change the components of this vector to a random one
		void randomize(const int limit, const bool bsig) {
			GeneralPurpose randComponent;
			X( (T)randComponent.getRandom(limit, 1, true) );
			Y( (T)randComponent.getRandom(limit, 1, true) );
			Z( (T)randComponent.getRandom(limit, 1, true) );
		}
		// Destructor
		~Vector3D() {}
};
// class Mass discribe a simple particle (or object)
template <class T> class Mass {
	private:
		T m;				// The mass value
		T e;                            // Energy of the mass
		int q;				// The charge value (integer multiple of 'e')
	public:
		// Constructor
		Mass(T m, T e, int q = 0) {
			this->m = m;
			this->e = e;
			this->q = q;
			init();
		}
		// Access (read and write) to private members
		void M(T _m) { m = _m; }        // Set a value to the mass
		T M() { return m; }             // Return the value of the mass
		void E(T _e) { e = _e; }        // Set a value to the energy of the particle
		T E() { return e; }             // Return the energy of the mass
		void Q(int _q) { q = _q; }      // Set a value to the charge of the particle
		int Q() { return q; }           // Return the value of the charge
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
			//euler
			vel += (force / m) * dt;
			pos += vel * dt;
		}
};

