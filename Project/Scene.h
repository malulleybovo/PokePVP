#ifndef __SCENE_H__
#define __SCENE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "LinkedList.h"
#include "LinkedListIterator.h"
#include "Player.h"
#include "Spell.h"

/******************************************************************************* 
*	Definition
*******************************************************************************/
typedef struct _Scene Scene;
struct _Scene {
	
	Player* mainPlayer;
	List* players;
	List* spells;
	
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
Scene* scene_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void scene_add_player(Scene* scene, Player* player);
void scene_remove_player(Scene* scene, Player* player);
void scene_add_spell(Scene* scene, Spell* spell);
void scene_remove_spell(Scene* scene, Spell* spell);

#endif
