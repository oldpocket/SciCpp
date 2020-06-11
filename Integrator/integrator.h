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

#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "../PhysLib/particle.h"
#include "euler_integrator.h"
#include "verlet_integrator.h"

enum IntegratorType {
    EULER, VERLET
}; 

/**
 * @todo write docs
 */
template <class T> 
class Integrator {
protected:
    Particle<T> particle;
public:
    /**
     * Default constructor
     */
    Integrator(Particle<T>& particle_) {
    
        particle = particle_;
    }

    /**
     * Destructor
     */
    ~Integrator();
    
    virtual void integrate(T dt_) = 0;
    
    static Integrator* Create(IntegratorType type_) {
    
        if (type_ == EULER) return new EulerIntegrator<T>();
        if (type_ == VERLET) return new VerletIntegrator<T>();
        
        return NULL;
            
    }

};

#endif // INTEGRATOR_H
