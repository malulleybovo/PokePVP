
#include "EntityMan.h"

EntityMan entity_man_new(){
	
	EntityMan* entityMan = malloc(sizeof(EntityMan));
	entityMan->entities = linked_list_new();
	return *entityMan;
	
}
