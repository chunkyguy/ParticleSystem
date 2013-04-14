//
//  ParticleSystem.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "ParticleSystem.h"

ParticleSystem *ParticleSystem_create(Program *p, ParticleShader *psh, GLuint tex, int c){
	ParticleSystem *ps = (ParticleSystem *)malloc(sizeof(ParticleSystem));
	ps->p = p;
	ps->psh = psh;
	ps->tex = tex;
	
	GLKVector2 position = GLKVector2Make(0,0);
	GLKVector2 box[2] = {GLKVector2Make(position.x-3, position.y-3), GLKVector2Make(position.x+3, position.y+3)};
	double life_range[2] = {0.1, 0.5};
	double deathrate_range[2] = {0.01, 0.08};
	double birth_delay_range[2] = {0.1, 0.3};
	double birth_rate_range[2] = {0.01, 0.3};
	GLKVector2 vel_range[2] = {GLKVector2Make(-5, 0.1), GLKVector2Make(5, 20)};
	
	ps->env = ParticleEnv_create(box, life_range, deathrate_range, birth_delay_range, birth_rate_range, vel_range);
	ps->particles = Particles_create(c, ps->env);
	return ps;
}

void ParticleSystem_destroy(ParticleSystem *ps){
	Particles_destroy(ps->particles);
	ParticleEnv_destroy(ps->env);
	
	free(ps);
	ps = 0;
}

int ParticleSystem_init(ParticleSystem *ps, double w, double h){
	ps->pMat = GLKMatrix4MakeOrtho(-w/2, w/2, -h/2, h/2, 0.1, 100.0);
	
	glGenVertexArraysOES(1, &ps->vao);
	glBindVertexArrayOES(ps->vao);
	glGenBuffers(1, &ps->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ps->vbo);
	
	glVertexAttribPointer(ps->psh->a_position, 2, GL_FLOAT, GL_FALSE, sizeof(GLKVector2), 0);
	glEnableVertexAttribArray(ps->psh->a_position);
	
	return 1;
}

void ParticleSystem_update(ParticleSystem *ps, double dt){
	GLKMatrix4 tMat = GLKMatrix4MakeTranslation(0, 0, -0.1);
	ps->mvp = GLKMatrix4Multiply(ps->pMat, tMat);
	Particles_update(ps->particles, ps->env, dt);
}

void ParticleSystem_render(ParticleSystem *ps){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glUseProgram(ps->p->prog);
	glBindTexture(GL_TEXTURE_2D, ps->tex);
	glBindVertexArrayOES(ps->vao);
	glBindBuffer(GL_ARRAY_BUFFER, ps->vbo);
	glBufferData(GL_ARRAY_BUFFER, ps->particles->size, ps->particles->data, GL_DYNAMIC_DRAW);
	glUniform4f(ps->psh->u_clr, 1.0, 0.3, 0.4, 0.4);
	glUniformMatrix4fv(ps->psh->u_mvp, 1, GL_FALSE, ps->mvp.m);
	glUniform1i(ps->psh->u_tex, 0);
	glUniform1f(ps->psh->u_size, 15.0);
	
	glDrawArrays(GL_POINTS, 0, ps->particles->count);
}
