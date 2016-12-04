
#include "Sprite.h"

Sprite* sprite_new(
	const uint8_t *b_u, 
	const uint8_t *b_d, 
	const uint8_t *b_l, 
	const uint8_t *m_u, 
	const uint8_t *m_d, 
	const uint8_t *m_l, 
	const uint8_t *a_u,
	const uint8_t *a_d, 
	const uint8_t *a_l) {
		Sprite* sprite = malloc(sizeof(Sprite));
		sprite->base_u = b_u;
		sprite->base_d = b_d;
		sprite->base_l = b_l;
		sprite->mot_u = m_u;
		sprite->mot_d = m_d;
		sprite->mot_l = m_l;
		sprite->atk_u = a_u;
		sprite->atk_d = a_d;
		sprite->atk_l = a_l;
		return sprite;
}
