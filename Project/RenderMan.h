#ifndef __RENDER_MAN_H__
#define __RENDER_MAN_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "Scene.h"
#include "Camera.h"

/******************************************************************************* 
*	Definition
*******************************************************************************/
typedef struct _RenderMan RenderMan;
struct _RenderMan {
	
	Scene* scene;
	Camera* camera;
	
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
RenderMan render_man_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void render_man_render(RenderMan* renderman);

#endif
