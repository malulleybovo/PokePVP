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
	
	bool isMoving;
	bool isAtking;
	int8_t mot_count;
	int8_t atk_count;
	
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
	bool (*updateSprite) (Entity* e);
	void (*setBaseSprite) (
		Entity* e,
		const uint8_t *up,
		const uint8_t *down, 
		const uint8_t *left);
	void (*setMotSprite) (
		Entity* e, 
		const uint8_t *up,
		const uint8_t *down, 
		const uint8_t *left);
	void (*setAtkSprite) (
		Entity* e, 
		const uint8_t *up,
		const uint8_t *down, 
		const uint8_t *left);
	
};

#define SPRITE_SIZE 24
#define ANIM_FREQ 32
#define ANIM_TRANSITION 16

/******************************************************************************* 
*	Constructor
*******************************************************************************/
Entity entity_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void entity_draw(Entity* e);
void entity_rotate90(Entity* e, bool isClkwise);
void entity_set_id(Entity* e, char* id);
void entity_set_pos_x(Entity* e, uint16_t x);
void entity_set_spd_x(Entity* e, uint16_t dx);
void entity_set_pos_y(Entity* e, uint16_t y);
void entity_set_spd_y(Entity* e, uint16_t dy);
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
