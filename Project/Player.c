
#include "Player.h"

Player player_new(){
	
	Player* player = malloc(sizeof(Player));
	
	player->setBody = player_set_body;
	
	return *player;
	
}

void player_set_body(Player* player, Entity* e){
	player->body = e;
}
