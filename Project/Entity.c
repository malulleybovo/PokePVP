
#include "Entity.h"

Entity entity_new () {
	Entity* newEntity = malloc(sizeof(Entity));
	// set isMoving bit so that first draw does not skip the lcd draw
	newEntity->status = 0x1;
	return *newEntity;
}

void entity_draw(Entity* e, int camPosX, int camPosY){
	
	if (!(e->status & ENTITY_MOVING_STATUS_M) && e->dx == 0 && e->dy == 0) {
		return;
	}
	
	// Update motion state
	if (e->dx || e->dy) {
		e->status |= ENTITY_MOVING_STATUS_M;
	}
	else {
		e->status &= ~ENTITY_MOVING_STATUS_M;
	}
	
	// Clear previous location of entity if it was displayed on screen
	if ((e->x - camPosX) <= ROWS + SPRITE_SIZE && (e->y - camPosY) <= COLS + SPRITE_SIZE) {
		lcd_clear_rect(
										e->x - camPosX,       // X Center Point
										SPRITE_SIZE,   				// Image Horizontal Width
										e->y - camPosY,       // Y Center Point
										SPRITE_SIZE,  				// Image Vertical Height
										0x57CA
									);
	}
	
	// Update coordinates
	e->x = e->x + e->dx;
	e->y = e->y + e->dy;
	
	// Display entity in new location if it is within the screen limit
	if ((e->x - camPosX) <= ROWS + SPRITE_SIZE && (e->y - camPosY) <= COLS + SPRITE_SIZE) {
		if (e->status & ENTITY_MOVING_STATUS_M) {
			if (entity_update_sprite(e)) {
				e->status |= ENTITY_FACING_RIGHT_STATUS_M;
			}
			else {
				e->status &= ~ENTITY_FACING_RIGHT_STATUS_M;
			}
		}
		lcd_draw_image_64color(
										e->x - camPosX,       // X Center Point
										SPRITE_SIZE,   				// Image Horizontal Width
										e->y - camPosY,       // Y Center Point
										SPRITE_SIZE,  				// Image Vertical Height
										e->curr_sprite,       // Image
										e->status & ENTITY_FACING_RIGHT_STATUS_M
									);
	}
}

void entity_rotate90(Entity* e, bool isClkwise){
	uint16_t tmp = e->dx;
	if (isClkwise) {
		e->dx = ~e->dy + 1;
		e->dy = tmp;
	}
	else {
		e->dx = e->dy;
		e->dy = ~tmp + 1;
	}
}
bool entity_update_sprite(Entity* e){
	int16_t zero = 0;
	
	uint16_t x_len = e->dx;
	uint16_t y_len = e->dy;
	
	if (e->status & ENTITY_ATKING_STATUS_M) {
		// Initialize / update attack animation
		if ((e->atk_count / ANIM_FREQ)) {
			e->status &= ~ENTITY_ATKING_STATUS_M;
			e->atk_count = 0;
		}
		else {
			e->atk_count += 1;
		}
	}
	else if (e->status & ENTITY_MOVING_STATUS_M) {
		// Initialize / update motion animation
		if ((e->mot_count / ANIM_FREQ)) {
			e->mot_count = 0;
		}
		else {
			e->mot_count += 1;
		}
	}
	else {
		// Reset animation while stationary
		e->mot_count = 0;
		e->atk_count = 0;
		return false;
	}
	
	if (e->dx < zero) {
		x_len= ~x_len + 1;
	}
	if (e->dy < zero) {
		y_len= ~y_len + 1;
	}
	if (x_len >= y_len) {
		if ((e->atk_count / ANIM_TRANSITION)){
			e->curr_sprite = e->sprite_atk_l;
		}
		else if ((e->mot_count / ANIM_TRANSITION)){
			e->curr_sprite = e->sprite_mot_l;
		}
		else {
			e->curr_sprite = e->sprite_base_l;
		}
		
		// Return true if player is facing right
		if (e->dx >= zero) {
			return true;
		}
	}
	else {
		if (e->dy < zero) {
			if ((e->atk_count / ANIM_TRANSITION)){
				e->curr_sprite = e->sprite_atk_u;
			}
			else if ((e->mot_count / ANIM_TRANSITION)){
				e->curr_sprite = e->sprite_mot_u;
			}
			else {
				e->curr_sprite = e->sprite_base_u;
			}
		}
		else {
			if ((e->atk_count / ANIM_TRANSITION)){
				e->curr_sprite = e->sprite_atk_d;
			}
			else if ((e->mot_count / ANIM_TRANSITION)){
				e->curr_sprite = e->sprite_mot_d;
			}
			else {
				e->curr_sprite = e->sprite_base_d;
			}
		}
	}
	return false;
}
void entity_set_base_sprite(
	Entity* e, 
	const uint8_t *up,
	const uint8_t *down, 
	const uint8_t *left){
	e->sprite_base_u = up;
	e->sprite_base_d = down;
	e->sprite_base_l = left;
}
void entity_set_mot_sprite(
	Entity* e, 
	const uint8_t *up,
	const uint8_t *down, 
	const uint8_t *left){
	e->sprite_mot_u = up;
	e->sprite_mot_d = down;
	e->sprite_mot_l = left;
}
void entity_set_atk_sprite(
	Entity* e, 
	const uint8_t *up,
	const uint8_t *down, 
	const uint8_t *left){
	e->sprite_atk_u = up;
	e->sprite_atk_d = down;
	e->sprite_atk_l = left;
}
