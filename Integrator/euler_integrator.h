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

#ifndef EULER_INTEGRATOR_H
#define EULER_INTEGRATOR_H

#include "integrator.h"

/**
 * @todo write docs
 */
template <class T>
class EulerIntegrator : public Integrator<T> {
public:
    /**
     * Default constructor
     */
    EulerIntegrator(Mass<T> mass_) : Integrator<T>(mass_) {
    }   

    /**
     * Destructor
     */
    ~EulerIntegrator();

    virtual void integrate(T dt_) override {
        mass.vel += (mass.force / mass.m) * dt_;
        mass.pos += mass.vel * dt_;
    }
    
};

#endif // EULER_INTEGRATOR_H
