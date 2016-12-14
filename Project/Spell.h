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
	
	int damage;
	bool hasCollided;
	int16_t lifespan; // number of frames it exists after being cast
	
	Entity* caster; // Body who casted the spell
	Entity* body;
	
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
Spell* spell_new(void);

/******************************************************************************* 
*	Destructor
*******************************************************************************/
void spell_free(Spell* spell);

/******************************************************************************* 
*	Functions
*******************************************************************************/
bool spell_render(Spell* spell, 
	int camX, int camY, 
	int camPrevX, int camPrevY);
// TODO other functions

#endif
