
#include "Entity.h"

Entity entity_new () {
	Entity* newEntity = malloc(sizeof(Entity));
	newEntity->isMoving = true; // So that first draw does not skip the lcd draw
	newEntity->isAtking = false;
	newEntity->draw = entity_draw;
	newEntity->rotate90 = entity_rotate90;
	newEntity->setPosX = entity_set_pos_x;
	newEntity->setPosY = entity_set_pos_y;
	newEntity->setSpdX = entity_set_spd_x;
	newEntity->setSpdY = entity_set_spd_y;
	newEntity->updateSprite = entity_update_sprite;
	newEntity->setBaseSprite = entity_set_base_sprite;
	newEntity->setMotSprite = entity_set_mot_sprite;
	newEntity->setAtkSprite = entity_set_atk_sprite;
	return *newEntity;
}

void entity_draw(Entity* e){
	bool isFacingRight = false;
	
	if (!e->isMoving && e->dx == 0 && e->dy == 0) {
		return;
	}
	
	// Update motion state
	e->isMoving = e->dx || e->dy;
	
	// Clear previous location of entity if it was displayed on screen
	if (e->x <= ROWS + SPRITE_SIZE && e->y <= COLS + SPRITE_SIZE) {
		lcd_clear_rect(
										e->x,                // X Center Point
										SPRITE_SIZE,   // Image Horizontal Width
										e->y,                // Y Center Point
										SPRITE_SIZE,  // Image Vertical Height
										0x57CA
									);
	}
	
	// Update coordinates
	e->x = e->x + e->dx;
	e->y = e->y + e->dy;
	
	// Display entity in new location if it is within the screen limit
	if (e->x <= ROWS + SPRITE_SIZE && e->y <= COLS + SPRITE_SIZE) {
		isFacingRight = e->updateSprite(e);
		lcd_draw_image_64color(
										e->x,                // X Center Point
										SPRITE_SIZE,   // Image Horizontal Width
										e->y,                // Y Center Point
										SPRITE_SIZE,  // Image Vertical Height
										e->curr_sprite,       // Image
										isFacingRight
									);
	}
}
void entity_set_id(Entity* e, char* id){
	e->id = id;
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
void entity_set_pos_x(Entity* e, uint16_t x){
	e->x = x;
}
void entity_set_spd_x(Entity* e, uint16_t dx){
	e->dx = dx;
}
void entity_set_pos_y(Entity* e, uint16_t y){
	e->y = y;
}
void entity_set_spd_y(Entity* e, uint16_t dy){
	e->dy = dy;
}
bool entity_update_sprite(Entity* e){
	int16_t zero = 0;
	
	uint16_t x_len = e->dx;
	uint16_t y_len = e->dy;
	
	if (e->isAtking) {
		// Initialize / update attack animation
		if ((e->atk_count / ANIM_FREQ)) {
			e->isAtking = false;
			e->atk_count = 0;
		}
		else {
			e->atk_count += 1;
		}
	}
	else if (e->isMoving) {
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
