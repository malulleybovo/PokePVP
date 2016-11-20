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
	
	uint16_t x;
	uint16_t dx;
	
	uint16_t y;
	uint16_t dy;
	
	uint8_t action_mask;
	
	const uint8_t *curr_sprite;
	
	const uint8_t *sprite_base_l;
	const uint8_t *sprite_base_r;
	const uint8_t *sprite_base_u;
	const uint8_t *sprite_base_d;
	
	const uint8_t *sprite_mot_l;
	const uint8_t *sprite_mot_r;
	const uint8_t *sprite_mot_u;
	const uint8_t *sprite_mot_d;
	
	const uint8_t *sprite_atk_l;
	const uint8_t *sprite_atk_r;
	const uint8_t *sprite_atk_u;
	const uint8_t *sprite_atk_d;
	
	void (*draw) (Entity* e);
	void (*rotate90) (Entity* e, bool isClkwise);
	void (*setPosX) (Entity* e, uint16_t x);
	void (*setSpdX) (Entity* e, uint16_t dx);
	void (*setPosY) (Entity* e, uint16_t y);
	void (*setSpdY) (Entity* e, uint16_t dy);
	void (*update_sprite) (Entity* e);
	void (*setBaseSprite) (
		Entity* e, 
		const uint8_t *left,
		const uint8_t *right,
		const uint8_t *up,
		const uint8_t *down);
	void (*setMotSprite) (
		Entity* e, 
		const uint8_t *left,
		const uint8_t *right,
		const uint8_t *up,
		const uint8_t *down);
	void (*setAtkSprite) (
		Entity* e, 
		const uint8_t *left,
		const uint8_t *right,
		const uint8_t *up,
		const uint8_t *down);
	
};

#define SPRITE_SIZE 24
#define ATK_ACTION_M 0xf0
#define ACTV_ATK_ACTION_M 0x80
#define ATK_ACTION_M_STEP 0x10
#define MOT_ACTION_M 0x0f
#define ACTV_MOT_ACTION_M 0x08
#define MOT_ACTION_M_STEP 0x01

/******************************************************************************* 
*	Constructor
*******************************************************************************/
Entity entity_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void entity_draw(Entity* e);
void entity_rotate90(Entity* e, bool isClkwise);
void entity_setPosX(Entity* e, uint16_t x);
void entity_setSpdX(Entity* e, uint16_t dx);
void entity_setPosY(Entity* e, uint16_t y);
void entity_setSpdY(Entity* e, uint16_t dy);
void entity_update_sprite(Entity* e);
void entity_setBaseSprite(
	Entity* e, 
	const uint8_t *left,
	const uint8_t *right,
	const uint8_t *up,
	const uint8_t *down);
void entity_setMotSprite(
	Entity* e, 
	const uint8_t *left,
	const uint8_t *right,
	const uint8_t *up,
	const uint8_t *down);
void entity_setAtkSprite(
	Entity* e, 
	const uint8_t *left,
	const uint8_t *right,
	const uint8_t *up,
	const uint8_t *down);

#endif
