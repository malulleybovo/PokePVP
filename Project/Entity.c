
#include "Entity.h"

Entity* entity_new () {
	Entity* newEntity = malloc(sizeof(Entity));
	// set isMoving bit so that first draw does not skip the lcd draw
	newEntity->status = 0x1;
	return newEntity;
}

void entity_draw(Entity* e, int camX, int camY, int camPrevX, int camPrevY){
	
	
	// Update motion state
	if (e->dx || e->dy) {
		e->status |= ENTITY_MOVING_STATUS_M;
	}
	else {
		e->status &= ~ENTITY_MOVING_STATUS_M;
	}
	
	// Clear previous location of entity if it was displayed on screen
	if ((e->x - camPrevX - ((-ROWS + SPRITE_SIZE) / 2)) >= 0
		&& (e->x - camPrevX - ((ROWS - SPRITE_SIZE) / 2)) < 0
		&& (e->y - camPrevY - ((-COLS + SPRITE_SIZE) / 2)) >= 0
		&& (e->y - camPrevY - ((COLS - SPRITE_SIZE) / 2)) < 0) {
			
		lcd_clear_rect(
										e->x - camPrevX + (ROWS / 2), // X Center Point
										SPRITE_SIZE,   				// Image Horizontal Width
										e->y - camPrevY + (COLS / 2), // Y Center Point
										SPRITE_SIZE,  				// Image Vertical Height
										0x57CA
									);
	}
	
	// Update coordinates
	e->x = e->x + e->dx;
	e->y = e->y + e->dy;
	
	// Display entity in new location if it is within the screen limit
	if ((e->x - camX - ((-ROWS + SPRITE_SIZE) / 2)) >= 0
		&& (e->x - camX - ((ROWS - SPRITE_SIZE) / 2)) < 0 
		&& (e->y - camY - ((-COLS + SPRITE_SIZE) / 2)) >= 0
		&& (e->y - camY - ((COLS - SPRITE_SIZE) / 2)) < 0) {
			
		if (e->status & ENTITY_MOVING_STATUS_M) {
			if (entity_update_sprite(e)) {
				e->status |= ENTITY_FACING_RIGHT_STATUS_M;
			}
			else {
				e->status &= ~ENTITY_FACING_RIGHT_STATUS_M;
			}
		}
		lcd_draw_image_64color(
										e->x - camX + (ROWS / 2), // X Center Point
										SPRITE_SIZE,   				// Image Horizontal Width
										e->y - camY + (COLS / 2), // Y Center Point
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

bool entity_has_collided(Entity* e1, Entity* e2) {
	int x1_min;
	int x1_max;
	int y1_min;
	int y1_max;
	int x2_min;
	int x2_max;
	int y2_min;
	int y2_max;
	bool x_touch;
	bool y_touch;
	
	if (e1 == e2) {
		return false; // Cannot collide with itself
	}

	x1_min = e1->x + e1->dx - (SPRITE_SIZE/2);
	x1_max = e1->x + e1->dx + (SPRITE_SIZE/2);
	y1_min = e1->y + e1->dy - (SPRITE_SIZE/2);
	y1_max = e1->y + e1->dy + (SPRITE_SIZE/2);
	x2_min = e2->x + e2->dx - (SPRITE_SIZE/2);
	x2_max = e2->x + e2->dx + (SPRITE_SIZE/2);
	y2_min = e2->y + e2->dy - (SPRITE_SIZE/2);
	y2_max = e2->y + e2->dy + (SPRITE_SIZE/2);
	x_touch = (x1_min <= x2_max) && (x1_max >= x2_min);
	y_touch = ((y1_min <= y2_max) && (y1_max >= y2_min));
	
	// Check if any vertex collides with other sprite
	if (((x1_min < x2_max) && (x1_min > x2_min) && (y1_min < y2_max) && (y1_min > y2_min))
		|| ((x1_min < x2_max) && (x1_min > x2_min) && (y1_max < y2_max) && (y1_max > y2_min))
		|| ((x1_max < x2_max) && (x1_max > x2_min) && (y1_min < y2_max) && (y1_min > y2_min))
		|| ((x1_max < x2_max) && (x1_max > x2_min) && (y1_max < y2_max) && (y1_max > y2_min))) {
		
		e1->dx = 0;
		e1->dy = 0;
		
		return true;	// Collision detected
	}
	
	// Check if entities are next to each other vertically
	if (((x1_min == x2_min) || (x1_max == x2_max)) && y_touch) {
		e1->dy = 0;
	}
	
	// Check if entities are next to each other horizontally
	if (((y1_min == y2_min) || (y1_max == y2_max)) && x_touch) {
		e1->dx = 0;
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
