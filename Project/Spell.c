
#include "Spell.h"

Spell spell_new(){
	
	Spell* spell = malloc(sizeof(Spell));
	spell->hasCollided = false;
	
	spell->setBody = spell_set_body;
	
	return *spell;
	
}

void spell_set_body(Spell* spell, Entity* e){
	spell->body = e;
}
