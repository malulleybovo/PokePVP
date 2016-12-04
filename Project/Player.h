#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "Entity.h"

/******************************************************************************* 
*	Definition
*******************************************************************************/
typedef struct _Player Player;
struct _Player {
	
	int hp;
	int pp;
	
	Entity* body;
	
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
Player* player_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void player_rotate90(Player* player, bool isClkwise);
void player_render(Player* player, 
	int camX, int camY, 
	int camPrevX, int camPrevY);
// TODO other functions

#endif
