#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "lcd.h"

/******************************************************************************* 
*	Definition
*******************************************************************************/
typedef struct _Entity Entity;
struct _Entity {
	
	char* id;
	
	int16_t x;
	int16_t dx;
	
	int16_t y;
	int16_t dy;
	
	// status bits :
	// bit 0 - is Moving ? 1 : 0
	// bit 1 - is Attacking ? 1 : 0
	// bit 2 - is Facing Right ? 1 : 0
	uint8_t status;
	
	int8_t mot_count;
	int8_t atk_count;
	
	const uint8_t *curr_sprite;
	
	const uint8_t *sprite_base_u;
	const uint8_t *sprite_base_d;
	const uint8_t *sprite_base_l;
	
	const uint8_t *sprite_mot_u;
	const uint8_t *sprite_mot_d;
	const uint8_t *sprite_mot_l;
	
	const uint8_t *sprite_atk_u;
	const uint8_t *sprite_atk_d;
	const uint8_t *sprite_atk_l;
	
};

#define SPRITE_SIZE 24
#define ANIM_FREQ 32
#define ANIM_TRANSITION 16
#define ENTITY_MOVING_STATUS_M 0x1
#define ENTITY_ATKING_STATUS_M 0x2
#define ENTITY_FACING_RIGHT_STATUS_M 0x4

/******************************************************************************* 
*	Constructor
*******************************************************************************/
Entity entity_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void entity_draw(Entity* e, int camPosX, int camPosY);
void entity_rotate90(Entity* e, bool isClkwise);
bool entity_update_sprite(Entity* e);
void entity_set_base_sprite(
	Entity* e,
	const uint8_t *up,
	const uint8_t *down, 
	const uint8_t *left);
void entity_set_mot_sprite(
	Entity* e,
	const uint8_t *up,
	const uint8_t *down, 
	const uint8_t *left);
void entity_set_atk_sprite(
	Entity* e,
	const uint8_t *up,
	const uint8_t *down, 
	const uint8_t *left);

#endif
