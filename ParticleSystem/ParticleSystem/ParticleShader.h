//
//  ParticleShader.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

// Directly coupled with Shader code.

#ifndef ParticleSystem_ParticleShader_h
#define ParticleSystem_ParticleShader_h

#include <GLKit/GLKMath.h>
#include <OpenGLES/ES2/gl.h>

struct ParticleShader_{
	//Attribs
	int a_position;
	
	//Uniforms
	GLint u_mvp;
	GLint u_size;
	GLint u_clr;
	GLint u_tex;
};
typedef struct ParticleShader_ ParticleShader;
ParticleShader *ParticleShader_create();
void ParticleShader_destroy(ParticleShader *psh);


#endif
