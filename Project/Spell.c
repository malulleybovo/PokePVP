
#include "Spell.h"

Spell* spell_new(){
	
	Spell* spell = malloc(sizeof(Spell));
	spell->hasCollided = false;
	
	return spell;
	
}

void spell_set_body(Spell* spell, Entity* e){
	spell->body = e;
}

void spell_render(Spell* spell,
	int camX, int camY, 
	int camPrevX, int camPrevY) {
	entity_draw(spell->body, camX, camY, camPrevX, camPrevY);
}
