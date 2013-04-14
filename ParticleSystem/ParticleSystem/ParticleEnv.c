//
//  ParticleEnv.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "ParticleEnv.h"

ParticleEnv *ParticleEnv_create(GLKVector2 *box, double *life_span, double *death_rate, double *birth_delay, double *birth_rate, GLKVector2 *vel){
	ParticleEnv *env = (ParticleEnv *)malloc(sizeof(ParticleEnv));
	for(int i = 0; i < 2; ++i){
		env->box[i] = box[i];
		env->life_span[i] = life_span[i];
		env->death_rate[i] = death_rate[i];
		env->birth_delay[i] = birth_delay[i];
		env->birth_rate[i] = birth_rate[i];
		env->velocity[i] = vel[i];
	}
	return env;
}
void ParticleEnv_destroy(ParticleEnv *penv){
	free(penv);
	penv = 0;
}
