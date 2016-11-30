
#include "Player.h"

Player player_new(){
	
	Player* player = malloc(sizeof(Player));
	
	return *player;
	
}

void player_set_body(Player* player, Entity* e){
	player->body = e;
}

void player_render(Player* player, int camPosX, int camPosY) {
	//TODO
}
