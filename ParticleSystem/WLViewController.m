//
//  WLViewController.m
//  ParticleSystem
//
//  Created by Sid on 14/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#import "WLViewController.h"

#include <assert.h>

#include "ParticleSystem/ParticleSystem.h"
#include "Program.h"


#define BUFFER_OFFSET(i) ((char *)NULL + (i))

//GL_State masks flags
#define kGL_StateUnknown			(1<<0)	//Unknown
#define	kGL_StateInit			(1<<1)	//Init
#define	kGL_StateSetup			(1<<2)	//Setup
#define	kGL_StateRender			(1<<3)	//Ready to render
#define	kGL_StateUpdate			(1<<4)	//Ready to update

ParticleShader *psh;

void bindAttribs(Program *p){
	// Bind attribute locations.
    // This needs to be done prior to linking.
    glBindAttribLocation(p->prog, psh->a_position, "a_position");
}

void bindUniforms(Program *p){
	psh->u_mvp = glGetUniformLocation(p->prog, "u_mvp");
	psh->u_size = glGetUniformLocation(p->prog, "u_size");
	psh->u_clr = glGetUniformLocation(p->prog, "u_clr");
	psh->u_tex = glGetUniformLocation(p->prog, "u_tex");
}

@interface WLViewController () {
	int glState;
	ParticleSystem *ps;
	Program *prog;
}
@property (strong, nonatomic) EAGLContext *context;

- (void)GL_WillSetup;
- (void)GL_DidSetup;
- (void)GL_Destroy;

@end

@implementation WLViewController

- (void)dealloc{
    [self GL_Destroy];
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    [_context release];
    [super dealloc];
}

- (void)viewDidLoad{
    [super viewDidLoad];
    self.context = [[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2] autorelease];
    if (!self.context) {
		[NSException raise:@"Failed to create ES context" format:@""];
    }
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
	
	NSLog(@"State: Unknown");
	glState = kGL_StateUnknown;
    [self GL_WillSetup];
}

- (void)didReceiveMemoryWarning{
    [super didReceiveMemoryWarning];
	
    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        [self GL_Destroy];
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }
}


//Doesn't has right value for screen dimensions
- (void)GL_WillSetup{
    [EAGLContext setCurrentContext:self.context];
	glState |= kGL_StateInit;
	NSLog(@"State: Init");
}

//Could be called multiple times. Do check.
//	We've the screen ready
-(void)GL_DidSetup{
	// already in setup state = do nothing
	if(glState & kGL_StateSetup){
		NSLog(@"State: Already setup");
		return;
	}
	// or is not in ready state = do nothing
	if(!(glState & kGL_StateInit)){
		NSLog(@"State: NOT Init");
		return;
	}
	if(!(glState & kGL_StateRender)){
		NSLog(@"State: NOT Render");
		return;
	}
	if(!(glState &  kGL_StateUpdate)){
		NSLog(@"State: NOT Update");
		return;
	}

	glState |= kGL_StateSetup;
	NSLog(@"State: Setup");
	

	// load shader
	psh = ParticleShader_create();
	
	//load program
	GLchar *vertShaderSource = (GLchar *)[[NSString stringWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"ParticleSh" ofType:@"vertsh"] encoding:NSUTF8StringEncoding error:nil] UTF8String];
    GLchar *fragShaderSource = (GLchar *)[[NSString stringWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"ParticleSh" ofType:@"fragsh"] encoding:NSUTF8StringEncoding error:nil] UTF8String];
	prog = Program_create( vertShaderSource, fragShaderSource, bindAttribs, bindUniforms);
	assert(prog);	//"Program creation failed!\n"

	//load texture
	NSString *texPath = [[NSBundle mainBundle] pathForResource:@"snow_particle" ofType:@"png"];
	UIImage *img = [[UIImage alloc] initWithContentsOfFile:texPath];
	NSError *err = nil;
	GLKTextureInfo *texInfo = [GLKTextureLoader textureWithCGImage:[img CGImage] options:nil error:&err];
	[img release];
	assert(texInfo.name);	//Unable to load image
	
	//load Particle system
	ps = ParticleSystem_create(prog, psh, texInfo.name, 100);
	int res = ParticleSystem_init(ps, self.view.bounds.size.width,self.view.bounds.size.height);
	assert(res);	 //"Unable to init test object"
}

- (void)GL_Destroy{
    [EAGLContext setCurrentContext:self.context];
	glState = kGL_StateUnknown;
	NSLog(@"State: Unknown");
	
	ParticleShader_destroy(psh);
	ParticleSystem_destroy(ps);
	Program_destroy(prog);
}

//Loop
- (void)update{
	//Skip if not in setup state.
	if(!(glState & kGL_StateSetup)){
		glState |= kGL_StateUpdate;
		NSLog(@"State: Update");
		[self GL_DidSetup];
		return;
	}
	ParticleSystem_update(ps, self.timeSinceLastUpdate);
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect{
	//Skip if not in setup state.
	if(!(glState & kGL_StateSetup)){
		glState |= kGL_StateRender;
		NSLog(@"State: Render");
		[self GL_DidSetup];
		return;
	}
	
	glClearColor(0.47, 0.67, 0.78, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	ParticleSystem_render(ps);
}

@end
