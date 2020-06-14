/******************************************************************************/
/*   Function : Interface for integrators                                     */
/*  Developer : Fabio Andreozzi Godoy                                         */
/*       Date : 2020-06-12 - Ultima atualizacao : 2020-06-14                  */
/******************************************************************************/

#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "../PhysLib/particle.h"
#include "euler_integrator.h"
#include "verlet_integrator.h"

enum IntegratorType {
    EULER, VERLET
}; 

template <class T> class Integrator;

/**
 * @todo write docs
 */
template <class T> class EulerIntegrator : public Integrator<T> {
public:
    /**
     * Default constructor
     */
    EulerIntegrator(Particle<T>* particle_) : Integrator<T>(particle_) {
    }   

    /**
     * Destructor
     */
    ~EulerIntegrator();

    virtual void integrate(T dt_) override {
        
        this->particle->vel += (this->particle->force / this->particle->M()) * dt_;
        this->particle->pos += this->particle->vel * dt_; 
    }
    
};

/**
 * @todo write docs
 */
template <class T> class VerletIntegrator : public Integrator<T> {
private:
    T lastDt;                       // Last dt
    Vector3D<T> lastPos;    // Last position in space
public:
    /**
     * Default constructor
     */
    VerletIntegrator(Particle<T>* particle_) : Integrator<T>(particle_) {
    }   

    /**
     * Destructor
     */
    ~VerletIntegrator();

    virtual void integrate(T dt_) override {
        
        Vector3D<T> tmpPos;
        this->particle->vel += (this->particle->force)*dt_/(this->particle->M());
        this->particle->pos += this->particle->vel*dt_ + (this->particle->force)*dt_*dt_/(2*this->particle->M());
        tmpPos = this->particle->pos;
        this->particle->pos += (this->particle->pos-lastPos)*(dt_/lastDt) + (this->particle->force)*dt_*dt_/(this->particle->M());
        this->particle->vel += (this->particle->force)*dt_/(this->particle->M());
        //vel = (pos-lastPos)/(2*dt);
        lastDt  = dt_;
        lastPos = tmpPos;
    }
    
};

/**
 * @todo write docs
 */
template <class T>  class Integrator {
protected:
    Particle<T>* particle;    
public:

    /**
     * Default constructor
     */
    Integrator(Particle<T>* particle_) {
        
       particle = particle_;
    }

    /**
     * Destructor
     */
    ~Integrator();
    
    virtual void integrate(T dt_) = 0;
    
    // Integrator Factory Method
    static Integrator<T>* Create(IntegratorType type_, Particle<T>* particle_) {
    
        if (type_ == EULER) return new EulerIntegrator<T>(particle_);
        if (type_ == VERLET) return new VerletIntegrator<T>(particle_);
        
        return NULL;
            
    }

};



#endif // INTEGRATOR_H
