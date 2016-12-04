
#include "Scene.h"

Scene* scene_new(void) {
	Scene* scene = malloc(sizeof(Scene));
	scene->players = linked_list_new();
	scene->spells = linked_list_new();
	return scene;
}

void scene_add_player(Scene* scene, Player* player) {
	linked_list_add(scene->players, player);
}

// Assumes max of one occurrence in list
void scene_remove_player(Scene* scene, Player* player) {
	ListIterator* itr = linked_list_iterator_new(scene->players);
	while(linked_list_iterator_has_next(itr)) {
		Player* curr = (Player*) linked_list_iterator_next(itr);
		if (curr == player) {
			linked_list_remove_at(scene->players, itr->index);
			break;
		}
	}
	linked_list_iterator_free(itr);
}

void scene_add_spell(Scene* scene, Spell* spell) {
	linked_list_add(scene->spells, spell);
}

// Assumes max of one occurrence in list
void scene_remove_spell(Scene* scene, Spell* spell) {
	ListIterator* itr = linked_list_iterator_new(scene->spells);
	while(linked_list_iterator_has_next(itr)) {
		Spell* curr = (Spell*) linked_list_iterator_next(itr);
		if (curr == spell) {
			linked_list_remove_at(scene->spells, itr->index);
			break;
		}
	}
	linked_list_iterator_free(itr);
}
