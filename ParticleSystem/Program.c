//
//  Program.c
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "Program.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int compileShader(GLuint *shader, GLenum type, const GLchar *source){
    GLint status;
	assert(source); //"Failed to load shader";
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        fprintf(stderr,"Shader compile log:\n%s", log);
        free(log);
    }
#endif
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        glDeleteShader(*shader);
        return 0;
    }
    
    return 1;
}

int linkProgram(GLuint prog){
    GLint status;
    glLinkProgram(prog);
    
#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        fprintf(stderr,"Program link log:\n%s", log);
        free(log);
    }
#endif
    
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status == 0) {
        return 0;
    }
    
    return 1;
}

int validateProgram(GLuint prog){
    GLint logLength, status;
    
    glValidateProgram(prog);
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(prog, logLength, &logLength, log);
        fprintf(stderr,"Program validate log:\n%s", log);
        free(log);
    }
    
    glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
    if (status == 0) {
        return 0;
    }
    
    return 1;
}

Program *Program_create(const GLchar *vertShaderSrc,	 const GLchar *fragShaderSrc, Program_callback bindAttribLoc, Program_callback bindUniformLoc){

	Program *p = (Program *)malloc(sizeof(Program));

	// Create shader program.
	p->prog = glCreateProgram();
	
	// Create and compile vertex shader.
    if (!compileShader(&p->vertShader,GL_VERTEX_SHADER,vertShaderSrc)) {
        fprintf(stderr,"Failed to compile vertex shader");
        return 0;
    }
    
    // Create and compile fragment shader.
    if (!compileShader(&p->fragShader,GL_FRAGMENT_SHADER,fragShaderSrc)) {
		fprintf(stderr,"Failed to compile fragment shader");
        return 0;
    }
    
    // Attach vertex shader to program.
    glAttachShader(p->prog, p->vertShader);
    
    // Attach fragment shader to program.
    glAttachShader(p->prog, p->fragShader);

	// Bind attribute locations.
    // This needs to be done prior to linking.
	bindAttribLoc(p);
	
	// Link program.
    if (!linkProgram(p->prog)) {
      fprintf(stderr,"Failed to link program: %d", p->prog);
        
        if (p->vertShader) {
            glDeleteShader(p->vertShader);
            p->vertShader = 0;
        }
        if (p->fragShader) {
            glDeleteShader(p->fragShader);
            p->fragShader = 0;
        }
        if (p->prog) {
            glDeleteProgram(p->prog);
            p->prog = 0;
        }
        
        return 0;
    }

	// Get uniform locations.
	bindUniformLoc(p);
	
    // Release vertex and fragment shaders.
    if (p->vertShader) {
        glDetachShader(p->prog, p->vertShader);
        glDeleteShader(p->vertShader);
    }
    if (p->fragShader) {
        glDetachShader(p->prog, p->fragShader);
        glDeleteShader(p->fragShader);
    }
    
	return p;
}

void Program_destroy(Program *p){
	free(p);
	p = 0;
}