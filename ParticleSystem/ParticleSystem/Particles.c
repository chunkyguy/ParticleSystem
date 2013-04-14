//
//  Particles.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "Particles.h"
#include "ParticleConstants.h"

Particles *Particles_create(int c, ParticleEnv *env){
	Particles *particles = (Particles *)malloc(sizeof(Particles));
	particles->count = c;
	particles->size = sizeof(GLfloat) * 2 * c;
	particles->data = (GLfloat *)malloc(particles->size);
	particles->particles = (Particle **)malloc(sizeof(Particle *) * c);
	
	GLfloat *dataptr = particles->data;
	for(int i = 0; i < particles->count; ++i){
		particles->particles[i] = Particle_create(env);
		*dataptr++ = 0.0;
		*dataptr++ = 0.0;
	}
	
	return particles;
}
void Particles_destroy(Particles *particles){
	for(int i = 0; i < particles->count; ++i){
		Particle_destroy(particles->particles[i]);
	}
	free(particles->particles);
	free(particles->data);
	free(particles);
	particles = 0;
}
void Particles_update(Particles *particles, ParticleEnv *env, double dt){
	GLfloat *dataptr = particles->data;
	for(int i = 0; i < particles->count; ++i){
		Particle_update(particles->particles[i], env, dt);
		*dataptr++ = particles->particles[i]->position.x;
		*dataptr++ = particles->particles[i]->position.y;
	}
}
