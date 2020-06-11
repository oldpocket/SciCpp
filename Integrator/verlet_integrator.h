/*
 * Copyright 2020 Fabio Godoy <aethiopicus@gmail.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef VERLET_INTEGRATOR_H
#define VERLET_INTEGRATOR_H

#include "integrator.h"

/**
 * @todo write docs
 */
template <class T>
class VerletIntegrator : public Integrator<T> {
private:
    T lastDt;                       // Last dt
    Vector3D<T> lastPos;    // Last position in space
public:
    /**
     * Default constructor
     */
    VerletIntegrator(Particle<T> mass_) : Integrator<T>(mass_) {
    }   

    /**
     * Destructor
     */
    ~VerletIntegrator();

    virtual void integrate(T dt_) override {
        Vector3D<T> tmpPos;
        mass.vel += (mass.force)*dt_/(mass.m);
        mass.pos += mass.vel*dt_ + (mass.force)*dt_*dt_/(2*mass.m);
        tmpPos = mass.pos;
        mass.pos += (mass.pos-lastPos)*(dt_/lastDt) + (mass.force)*dt_*dt_/(mass.m);
        mass.vel += (mass.force)*dt_/(mass.m);
        //vel = (pos-lastPos)/(2*dt);
        lastDt  = dt_;
        lastPos = tmpPos;
    }
    
};

#endif // VERLET_INTEGRATOR_H

