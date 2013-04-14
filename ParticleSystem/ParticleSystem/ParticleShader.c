//
//  ParticleShader.h
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "ParticleShader.h"
#include "ParticleConstants.h"

ParticleShader *ParticleShader_create(){
	ParticleShader *psh = (ParticleShader *)malloc(sizeof(ParticleShader));
	psh->a_position = 0;
	return psh;
}
void ParticleShader_destroy(ParticleShader *psh){
	free(psh);
	psh = 0;
}

