
#include "RenderMan.h"

RenderMan* render_man_new(void) {
	RenderMan* renderman = malloc(sizeof(RenderMan));
	return renderman;
}

void render_man_render(RenderMan* renderman) {
	ListIterator* itr;
	ListIterator* itr2;
	Player* mainPlayer = (*renderman->scene)->mainPlayer;
	
	// Check collisions on players
	itr = linked_list_iterator_new((*renderman->scene)->players);
	while(linked_list_iterator_has_next(itr)) {
		Player* curr = (Player*) linked_list_iterator_next(itr);
		
		itr2 = linked_list_iterator_new((*renderman->scene)->players);
		while(linked_list_iterator_has_next(itr2)) {
			Player* curr2 = (Player*) linked_list_iterator_next(itr2);
			entity_has_collided(curr->body, curr2->body);
		}
		linked_list_iterator_free(itr2);
		
		itr2 = linked_list_iterator_new((*renderman->scene)->spells);
		while(linked_list_iterator_has_next(itr2)) {
			Spell* curr2 = (Spell*) linked_list_iterator_next(itr2);
			entity_has_collided(curr->body, curr2->body);
		}
		linked_list_iterator_free(itr2);
	}
	linked_list_iterator_free(itr);
	
	// Check collisions on spells
	itr = linked_list_iterator_new((*renderman->scene)->spells);
	while(linked_list_iterator_has_next(itr)) {
		Spell* curr = (Spell*) linked_list_iterator_next(itr);
		
		itr2 = linked_list_iterator_new((*renderman->scene)->spells);
		while(linked_list_iterator_has_next(itr2)) {
			Spell* curr2 = (Spell*) linked_list_iterator_next(itr2);
			entity_has_collided(curr->body, curr2->body);
		}
		linked_list_iterator_free(itr2);
	}
	linked_list_iterator_free(itr);
	
	// Update Camera Position
	camera_update_pos((*renderman->camera), 
		mainPlayer->body->x, 
		mainPlayer->body->y);
	
	// Render main player (user's player)
	player_render(mainPlayer, 
			(*renderman->camera)->x, (*renderman->camera)->y,
			(*renderman->camera)->prev_x, (*renderman->camera)->prev_y);
	
	// Render other players currently on map
	itr = linked_list_iterator_new((*renderman->scene)->players);
	while(linked_list_iterator_has_next(itr)) {
		Player* curr = (Player*) linked_list_iterator_next(itr);
		player_render(curr, 
			(*renderman->camera)->x, (*renderman->camera)->y,
			(*renderman->camera)->prev_x, (*renderman->camera)->prev_y);
	}
	linked_list_iterator_free(itr);
	
	// Render spells currently on map
	itr = linked_list_iterator_new((*renderman->scene)->spells);
	while(linked_list_iterator_has_next(itr)) {
		Spell* curr = (Spell*) linked_list_iterator_next(itr);
		spell_render(curr, 
			(*renderman->camera)->x, (*renderman->camera)->y,
			(*renderman->camera)->prev_x, (*renderman->camera)->prev_y);
	}
	linked_list_iterator_free(itr);
}
