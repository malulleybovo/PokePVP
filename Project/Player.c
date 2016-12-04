
#include "Player.h"

Player* player_new(){
	
	Player* player = malloc(sizeof(Player));
	
	return  player;
	
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
	entity_draw(player->body, camX, camY, camPrevX, camPrevY);
}
