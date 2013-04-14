//
//  Particle.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "Particle.h"

#include "ParticleConstants.h"

static double randf(){
	return (double)(rand()) / (double)RAND_MAX;
}
static double double_rand(double a, double b){
	return a + (b - a) * randf();
}
static GLKVector2 GLKVector2_rand(GLKVector2 a, GLKVector2 b){
	return GLKVector2Make(double_rand(a.x, b.x), double_rand(a.y, b.y));
}
static void Particle_init(Particle *p, ParticleEnv *env){
	p->isDead = 0;
	p->position = GLKVector2_rand(env->box[0], env->box[1]);
	p->life_span = double_rand(env->life_span[0], env->life_span[1]);
	p->death_rate = double_rand(env->death_rate[0], env->death_rate[1]);
	p->birth_delay = double_rand(env->birth_delay[0],env->birth_delay[1]);
	p->birth_rate = double_rand(env->birth_rate[0], env->birth_rate[1]);
	p->velocity = GLKVector2_rand(env->velocity[0], env->velocity[1]);
}

void Particle_destroy(Particle *p){
	free(p);
	p = 0;
}

Particle *Particle_create(ParticleEnv *env){
	Particle *p = (Particle *)malloc(sizeof(Particle));
	Particle_init(p, env);
	return p;
}

void Particle_update(Particle *p, ParticleEnv *env, double dt){
	if(p->isDead && p->birth_rate > 0.0){	//dead + rebirth possible
		p->birth_delay -= (dt * p->birth_rate);
		p->isDead = (p->birth_delay > 0.0) ? 1: 0;
		if(!p->isDead){
			Particle_init(p, env);
		}
	}else if(!p->isDead){	// living normally
		p->life_span -= (dt * p->death_rate);
		p->isDead = (p->life_span < 0.0);
		if(!p->isDead){
			p->position = GLKVector2Add(p->position, GLKVector2MultiplyScalar(p->velocity, dt));
		}
	}
}

