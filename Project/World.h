#ifndef __WORLD_H__
#define __WORLD_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "Camera.h"
#include "Scene.h"

/******************************************************************************* 
*	Definition
*******************************************************************************/
typedef struct _World World;
struct _World {
	
	Camera* camera;
	Scene* scene;
	
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
World world_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void world_set_camera(World* world, Camera* camera);
void world_set_scene(World* world, Scene* scene);

#endif
