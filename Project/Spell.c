
#include "Spell.h"

Spell spell_new(){
	
	Spell* spell = malloc(sizeof(Spell));
	spell->hasCollided = false;
	
	return *spell;
	
}

void spell_set_body(Spell* spell, Entity* e){
	spell->body = e;
}

void spell_render(Spell* spell, int camPosX, int camPosY) {
	//TODO
}
