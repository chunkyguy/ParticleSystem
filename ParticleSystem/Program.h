//
//  Program.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef ParticleSystem_Program_h
#define ParticleSystem_Program_h
#include <OpenGLES/ES2/gl.h>

struct Program_{
	GLuint prog;
    GLuint vertShader, fragShader;
};
typedef struct Program_ Program;

typedef void( *Program_callback)(Program *p);

Program *Program_create(
						const GLchar *vertShaderSrc,
						const GLchar *fragShaderSrc,
						Program_callback bindAttribLoc,
						Program_callback bindUniformLoc
						);

void Program_destroy(Program *p);
#endif
