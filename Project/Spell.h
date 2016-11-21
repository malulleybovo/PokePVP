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
	
	int x;
	int y;
	
	bool hasCollided;
	
	Entity* body;
	
	void (*setBody) (Spell* spell, Entity* e);
	
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
Spell spell_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void spell_set_body(Spell* spell, Entity* e);
// TODO other functions

#endif
