
#include "RenderMan.h"

RenderMan* render_man_new(void) {
	RenderMan* renderman = malloc(sizeof(RenderMan));
	return renderman;
}

void render_man_render(RenderMan* renderman) {
	ListIterator* itr;
	ListIterator* itr2;
	Player* mainPlayer = (*renderman->scene)->mainPlayer;
	int dead_spell_index = -1; // For removing dead spells from list
	int player_killed_index = -1;
	int spell_hit_index = -1;
	
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
			bool p_coll = false;
			bool s_coll = false;
			Spell* curr2 = (Spell*) linked_list_iterator_next(itr2);
			p_coll = entity_has_collided(curr->body, curr2->body);
			s_coll = entity_has_collided(curr2->body, curr->body);
			if (p_coll || s_coll){
				curr->hp -= curr2->damage;
				if (curr->hp <= 0) {
					player_killed_index = itr->index;
				}
				curr2->lifespan = 0;
				spell_hit_index = itr2->index;
			}
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
		bool success = true;
		Spell* curr = (Spell*) linked_list_iterator_next(itr);
		success = spell_render(curr, 
			(*renderman->camera)->x, (*renderman->camera)->y,
			(*renderman->camera)->prev_x, (*renderman->camera)->prev_y);
		if (!success) { // Found depleted spell 
			dead_spell_index = itr->index;
		}
	}
	linked_list_iterator_free(itr);
	// Remove killed players(if any)
	if (player_killed_index != -1) {
		linked_list_remove_at((*renderman->scene)->players, player_killed_index);
	}
	// Remove spells that hit players (if any)
	if (spell_hit_index != -1) {
		linked_list_remove_at((*renderman->scene)->spells, spell_hit_index);
	}
	// Remove any spell that has run out of energy
	else if (dead_spell_index != -1) {
		linked_list_remove_at((*renderman->scene)->spells, dead_spell_index);
	}
}
