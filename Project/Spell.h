#ifndef __SPELL_H__
#define __SPELL_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "Entity.h"

/******************************************************************************* 
*	Definition
*******************************************************************************/
typedef struct _Spell Spell;
struct _Spell {
	
	bool hasCollided;
	
	Entity* body;
	
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
Spell* spell_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void spell_render(Spell* spell, 
	int camX, int camY, 
	int camPrevX, int camPrevY);
// TODO other functions

#endif
