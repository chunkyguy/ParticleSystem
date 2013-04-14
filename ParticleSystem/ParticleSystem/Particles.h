//
//  Particles.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

//	A collection of Particles.
//	Keeps updated data ready to be pushed in to a OpenGL vbo.
#ifndef ParticleSystem_Particles_h
#define ParticleSystem_Particles_h

#include <OpenGLES/ES2/gl.h>
#include "Particle.h"

struct Particles_{
	int count;
	Particle **particles;
	GLfloat *data;
	size_t size;
};
typedef struct Particles_ Particles;
Particles *Particles_create(int c, ParticleEnv *env);
void Particles_destroy(Particles *particles);
void Particles_update(Particles *particles, ParticleEnv *env, double dt);

#endif
