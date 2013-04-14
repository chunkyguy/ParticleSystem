//
//  ParticleEnv.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

// Update the environment to reflect changes in the particles at run time.

#ifndef ParticleSystem_ParticleEnv_h
#define ParticleSystem_ParticleEnv_h
#include <GLKit/GLKMath.h>

struct ParticleEnv_{
	GLKVector2 box[2];
	double life_span[2];
	double death_rate[2];
	double birth_delay[2];
	double birth_rate[2];
	GLKVector2 velocity[2];
};
typedef struct ParticleEnv_ ParticleEnv;
ParticleEnv *ParticleEnv_create(GLKVector2 *box, double *life_span, double *death_rate, double *birth_delay, double *birth_rate, GLKVector2 *vel);
void ParticleEnv_destroy(ParticleEnv *penv);


#endif
