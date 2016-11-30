
#include "RenderMan.h"

RenderMan render_man_new(void) {
	RenderMan* renderman = malloc(sizeof(RenderMan));
	return *renderman;
}

void render_man_render(RenderMan* renderman) {
	ListIterator* itr;
	
	// Render main player (user's player)
	player_render(renderman->scene->mainPlayer, renderman->camera->x, renderman->camera->y);
	
	// Render other players currently on map
	itr = linked_list_iterator_new(&renderman->scene->players);
	while(linked_list_iterator_has_next(itr)) {
		Player* curr = (Player*) linked_list_iterator_next(itr);
		player_render(curr, renderman->camera->x, renderman->camera->y);
	}
	linked_list_iterator_free(itr);
	
	// Render spells currently on map
	itr = linked_list_iterator_new(&renderman->scene->spells);
	while(linked_list_iterator_has_next(itr)) {
		Spell* curr = (Spell*) linked_list_iterator_next(itr);
		spell_render(curr, renderman->camera->x, renderman->camera->y);
	}
	linked_list_iterator_free(itr);
}
