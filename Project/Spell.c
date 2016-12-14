
#include "Spell.h"

Spell* spell_new(){
	
	Spell* spell = malloc(sizeof(Spell));
	spell->hasCollided = false;
	
	return spell;
	
}

void spell_free(Spell* spell){
	entity_free(spell->body);
	free(spell);
}

void spell_set_body(Spell* spell, Entity* e){
	spell->body = e;
}

bool spell_render(Spell* spell,
	int camX, int camY, 
	int camPrevX, int camPrevY) {
	// Check if spell has enough energy for attack (1 Animation Period)
	if(spell->lifespan < ANIM_FREQ) {
		// Spell energy has depleted
		entity_clear(spell->body, camX, camY, camPrevX, camPrevY);
		return false;
	}
	entity_draw(spell->body, camX, camY, camPrevX, camPrevY);
	spell->lifespan--;
	return true;
}
