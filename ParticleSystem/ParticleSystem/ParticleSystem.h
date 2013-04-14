//
//  ParticleSystem.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

//	Start here

#ifndef ParticleSystem_ParticleSystem_h
#define ParticleSystem_ParticleSystem_h

#include <GLKit/GLKMath.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#include "Program.h"
#include "ParticleShader.h"
#include "ParticleEnv.h"
#include "Particles.h"

struct ParticleSystem_{
	Program *p;
	ParticleShader *psh;
	Particles *particles;
	ParticleEnv *env;
	
	GLuint vao;
	GLuint vbo;
	GLuint tex;
	
	GLKMatrix4 pMat;
	GLKMatrix4 mvp;
};
typedef struct ParticleSystem_ ParticleSystem;

ParticleSystem *ParticleSystem_create(Program *p, ParticleShader *psh, GLuint tex, int c);
void ParticleSystem_destroy(ParticleSystem *ps);

int ParticleSystem_init(ParticleSystem *ps, double w, double h);
void ParticleSystem_update(ParticleSystem *ps, double dt);
void ParticleSystem_render(ParticleSystem *ps);

#endif