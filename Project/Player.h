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
	
	int x;
	int y;
	
	int hp;
	int pp;
	
	Entity* body;
	
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
Player player_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void player_render(Player* player, int camPosX, int camPosY);
// TODO other functions

#endif
