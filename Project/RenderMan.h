#ifndef __RENDER_MAN_H__
#define __RENDER_MAN_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "World.h"

/******************************************************************************* 
*	Definition
*******************************************************************************/
typedef struct _RenderMan RenderMan;
struct _RenderMan {
	
	World* world;
	
	void (*setWorld) (RenderMan* renderMan, World* world);
	void (*render) (void);
	
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
RenderMan render_man_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void render_man_set_world(RenderMan* renderMan, World* world);
void render_man_render(void);

#endif
