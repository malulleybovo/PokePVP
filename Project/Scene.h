#ifndef __SCENE_H__
#define __SCENE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "LinkedList.h"
#include "Entity.h"

/******************************************************************************* 
*	Definition
*******************************************************************************/
typedef struct _Scene Scene;
struct _Scene {
	
	List players;
	List spells;
	
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
Scene scene_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void scene_add_player(Scene* scene, Entity* entity);
void scene_remove_player(Scene* scene, Entity* entity);
void scene_add_spell(Scene* scene, Entity* entity);
void scene_remove_spell(Scene* scene, Entity* entity);

#endif
