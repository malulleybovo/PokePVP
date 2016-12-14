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
	// bit 3~2 - facing: up = b11, down = b10, left = b01, right = b00
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
#define ENTITY_DIR_STATUS_M 0xC
#define ENTITY_FACE_UP_STATUS 0xC
#define ENTITY_FACE_DOWN_STATUS 0x8
#define ENTITY_FACE_LEFT_STATUS 0x4
#define ENTITY_FACE_RIGHT_STATUS 0x0

/******************************************************************************* 
*	Constructor
*******************************************************************************/
Entity* entity_new(void);

/******************************************************************************* 
*	Destructor
*******************************************************************************/
void entity_free(Entity* e);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void entity_attack(Entity* e);
void entity_draw(Entity* e,
	int camX, int camY,
	int camPrevX, int camPrevY);
void entity_clear(Entity* e,
	int camX, int camY,
	int camPrevX, int camPrevY);
void entity_rotate90(Entity* e, bool isClkwise);
bool entity_has_collided(Entity* e1, Entity* e2);
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
