
#include "Player.h"

Player* player_new(){
	
	Player* player = malloc(sizeof(Player));
	
	return  player;
	
}

void player_free(Player* player){
	entity_free(player->body);
	free(player);
}

void player_attack(Player* player) {
	entity_attack(player->body);
}

void player_set_body(Player* player, Entity* e){
	player->body = e;
}

void player_rotate90(Player* player, bool isClkwise) {
	entity_rotate90(player->body, isClkwise);
}

void player_render(Player* player, 
	int camX, int camY,
	int camPrevX, int camPrevY) {
	// Check if spell has enough energy for attack (1 Animation Period)
	if(player->hp <= 0) {
		// Spell energy has depleted
		entity_clear(player->body, camX, camY, camPrevX, camPrevY);
		return;
	}
	entity_draw(player->body, camX, camY, camPrevX, camPrevY);
}
