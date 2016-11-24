
#include "Entity.h"

Entity entity_new () {
	Entity* newEntity = malloc(sizeof(Entity));
	newEntity->isMoving = true; // So that first draw does not skip the lcd draw
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
	if (!e->isMoving && e->dx == 0 && e->dy == 0) {
		return;
	}
	
	e->isMoving = e->dx || e->dy;
	
	// Clear previous location of entity if it was displayed on screen
	if (e->x <= ROWS + SPRITE_SIZE && e->y <= COLS + SPRITE_SIZE) {
		lcd_draw_image(
										e->x,                // X Center Point
										SPRITE_SIZE,   // Image Horizontal Width
										e->y,                // Y Center Point
										SPRITE_SIZE,  // Image Vertical Height
										e->curr_sprite,       // Image
										LCD_COLOR_BLACK,      // Foreground Color
										LCD_COLOR_BLACK     // Background Color
									);
	}
	
	// Update coordinates
	e->x = e->x + e->dx;
	e->y = e->y + e->dy;
	
	// Display entity in new location if it is within the screen limit
	if (e->x <= ROWS + SPRITE_SIZE && e->y <= COLS + SPRITE_SIZE) {
		e->updateSprite(e);
		lcd_draw_image(
										e->x,                // X Center Point
										SPRITE_SIZE,   // Image Horizontal Width
										e->y,                // Y Center Point
										SPRITE_SIZE,  // Image Vertical Height
										e->curr_sprite,       // Image
										LCD_COLOR_GREEN,      // Foreground Color
										LCD_COLOR_BLACK     // Background Color
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
void entity_update_sprite(Entity* e){
	uint16_t x_len = e->dx;
	uint16_t y_len = e->dy;
	if (!e->dx && !e->dy) {
		e->action_mask &= ~MOT_ACTION_M;
		return;
	}
	
	if (!(e->action_mask & MOT_ACTION_M)) {
		e->action_mask |= MOT_ACTION_M;
	}
	else {
		e->action_mask -= MOT_ACTION_M_STEP;
	}
	
	if (e->dx > 0x7ff) {
		x_len= ~x_len + 1;
	}
	if (e->dy > 0x7ff) {
		y_len= ~y_len + 1;
	}
	if (x_len >= y_len) {
		if (e->dx > 0x7ff) {
			if (e->action_mask & ACTV_ATK_ACTION_M){
				e->action_mask -= ATK_ACTION_M_STEP;
				
				e->curr_sprite = e->sprite_atk_r;
			}
			else if (e->action_mask & ACTV_MOT_ACTION_M){
				e->curr_sprite = e->sprite_mot_r;
			}
			else {
				e->curr_sprite = e->sprite_base_r;
			}
		}
		else {
			if (e->action_mask & ACTV_ATK_ACTION_M){
				e->action_mask -= ATK_ACTION_M_STEP;
				
				e->curr_sprite = e->sprite_atk_l;
			}
			else if (e->action_mask & ACTV_MOT_ACTION_M){
				e->curr_sprite = e->sprite_mot_l;
			}
			else {
				e->curr_sprite = e->sprite_base_l;
			}
		}
	}
	else {
		if (e->dy > 0x7ff) {
			if (e->action_mask & ACTV_ATK_ACTION_M){
				e->action_mask -= ATK_ACTION_M_STEP;
				
				e->curr_sprite = e->sprite_atk_d;
			}
			else if (e->action_mask & ACTV_MOT_ACTION_M){
				e->curr_sprite = e->sprite_mot_d;
			}
			else {
				e->curr_sprite = e->sprite_base_d;
			}
		}
		else {
			if (e->action_mask & ACTV_ATK_ACTION_M){
				e->action_mask -= ATK_ACTION_M_STEP;
				
				e->curr_sprite = e->sprite_atk_u;
			}
			else if (e->action_mask & ACTV_MOT_ACTION_M){
				e->curr_sprite = e->sprite_mot_u;
			}
			else {
				e->curr_sprite = e->sprite_base_u;
			}
		}
	}
}
void entity_set_base_sprite(
	Entity* e, 
	const uint8_t *left,
	const uint8_t *right,
	const uint8_t *up,
	const uint8_t *down){
	e->sprite_base_l = left;
	e->sprite_base_r = right;
	e->sprite_base_u = up;
	e->sprite_base_d = down;
}
void entity_set_mot_sprite(
	Entity* e, 
	const uint8_t *left,
	const uint8_t *right,
	const uint8_t *up,
	const uint8_t *down){
	e->sprite_mot_l = left;
	e->sprite_mot_r = right;
	e->sprite_mot_u = up;
	e->sprite_mot_d = down;
}
void entity_set_atk_sprite(
	Entity* e, 
	const uint8_t *left,
	const uint8_t *right,
	const uint8_t *up,
	const uint8_t *down){
	e->sprite_atk_l = left;
	e->sprite_atk_r = right;
	e->sprite_atk_u = up;
	e->sprite_atk_d = down;
}
