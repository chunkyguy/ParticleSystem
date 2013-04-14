//
//  Particle.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

//	Keep living and dying.

#ifndef ParticleSystem_Particle_h
#define ParticleSystem_Particle_h

#include <GLKit/GLKMath.h>
#include "ParticleEnv.h"

struct Particle_{
	double life_span;
	double death_rate;
	double birth_delay;
	double birth_rate;
	GLKVector2 position;
	GLKVector2 velocity;
	int isDead;
};
typedef struct Particle_ Particle;
Particle *Particle_create(ParticleEnv *env);
void Particle_destroy(Particle *p);
void Particle_update(Particle *p, ParticleEnv *env, double dt);

#endif