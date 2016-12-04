#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "Entity.h"

/******************************************************************************* 
*	Definition
*******************************************************************************/
typedef struct _Sprite Sprite;
struct _Sprite {
	
	const uint8_t *base_u;
	const uint8_t *base_d;
	const uint8_t *base_l;
	
	const uint8_t *mot_u;
	const uint8_t *mot_d;
	const uint8_t *mot_l;
	
	const uint8_t *atk_u;
	const uint8_t *atk_d;
	const uint8_t *atk_l;
	
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
Sprite* sprite_new(
	const uint8_t *b_u, 
	const uint8_t *b_d, 
	const uint8_t *b_l, 
	const uint8_t *m_u, 
	const uint8_t *m_d, 
	const uint8_t *m_l, 
	const uint8_t *a_u,
	const uint8_t *a_d, 
	const uint8_t *a_l);

/******************************************************************************* 
*	Functions
*******************************************************************************/

#endif
