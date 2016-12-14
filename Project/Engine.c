
#include "Engine.h"

Engine* engine_new(void) {
	Engine* engine = malloc(sizeof(Engine));
	return engine;
}

void engine_init(Engine* engine) {
	Player* mainPlayer;
	Scene* scene;
	Camera* camera;
	World* world;
	RenderMan* renderman;
	
	// Initialize Main Player
	mainPlayer = player_new();
	
	// Initialize Scene
	scene = scene_new();
	scene->mainPlayer = mainPlayer; // Link main player to scene
	
	// Initialize Camera
	camera = camera_new();
	
	// Initialize World
	world = world_new();
	world->camera = camera; // Link camera to world
	world->scene = scene; // Link camera to scene
	
	// Initialize Render Manager
	renderman = render_man_new();
	renderman->camera = &world->camera; // Link to camera through world
	renderman->scene = &world->scene; // Link to scene through world
	
	engine->world = world;
	engine->renderMan = renderman;
	
}

void engine_run(Engine* engine) {
	render_man_render(engine->renderMan);
}

Player* engine_setup_main_player(
	Engine* engine,
	
	char* id,
	
	int x, 
	int y, 
	
	int hp,
	int pp,
	
	const uint8_t *b_u, 
	const uint8_t *b_d, 
	const uint8_t *b_l, 
	const uint8_t *m_u, 
	const uint8_t *m_d, 
	const uint8_t *m_l, 
	const uint8_t *a_u,
	const uint8_t *a_d, 
	const uint8_t *a_l) {
	
		Player* mainPlayer;
		Entity* body;
		
		mainPlayer = engine->world->scene->mainPlayer;
		mainPlayer->hp = hp;
		mainPlayer->pp = pp;
		
		body = entity_new();
		body->id = id;
		body->x = x;
		body->y = y;
		body->curr_sprite = b_d;
		entity_set_base_sprite(body, b_u, b_d, b_l);
		entity_set_mot_sprite(body, m_u, m_d, m_l);
		entity_set_atk_sprite(body, a_u, a_d, a_l);
		mainPlayer->body = body;
		
		engine->world->camera->x = x;
		engine->world->camera->y = y;
		engine->world->camera->prev_x = x;
		engine->world->camera->prev_y = y;
		
		linked_list_add(engine->world->scene->players, mainPlayer);
		return mainPlayer;
}
	
Player* engine_new_player(
	Engine* engine,
	
	char* id, 
		
	int x, 
	int y, 
		
	int hp, 
	int pp, 
	
	const uint8_t *b_u, 
	const uint8_t *b_d, 
	const uint8_t *b_l, 
	const uint8_t *m_u, 
	const uint8_t *m_d, 
	const uint8_t *m_l, 
	const uint8_t *a_u,
	const uint8_t *a_d, 
	const uint8_t *a_l) {
		
		Player* newPlayer;
		Entity* body;
		
		newPlayer = player_new();
		newPlayer->hp = hp;
		newPlayer->pp = pp;
		
		body = entity_new();
		body->id = id;
		body->x = x;
		body->y = y;
		body->curr_sprite = b_d;
		entity_set_base_sprite(body, b_u, b_d, b_l);
		entity_set_mot_sprite(body, m_u, m_d, m_l);
		entity_set_atk_sprite(body, a_u, a_d, a_l);
		newPlayer->body = body;
		
		linked_list_add(engine->world->scene->players, newPlayer);
		
		return newPlayer;
}

Spell* engine_new_spell(
	Engine* engine,
	
	Player* caster,
	
	char* id, 
	int16_t lifespan,
	int damage,
	
	const uint8_t *b_u, 
	const uint8_t *b_d, 
	const uint8_t *b_l, 
	const uint8_t *m_u, 
	const uint8_t *m_d, 
	const uint8_t *m_l, 
	const uint8_t *a_u,
	const uint8_t *a_d, 
	const uint8_t *a_l) {
		
		Spell* newSpell;
		Entity* body;
		
		newSpell = spell_new();
		newSpell->caster = caster->body;
		newSpell->lifespan = lifespan;
		newSpell->damage = damage;
		
		body = entity_new();
		body->id = id;
		
		entity_set_base_sprite(body, b_u, b_d, b_l);
		entity_set_mot_sprite(body, m_u, m_d, m_l);
		entity_set_atk_sprite(body, a_u, a_d, a_l);
		newSpell->body = body;
		
		linked_list_add(engine->world->scene->spells, newSpell);
		
		return newSpell;
}
	
Spell* engine_new_bullet_spell(
	Engine* engine,
	
	Player* caster,
	
	char* id, 
	int16_t lifespan,
	int damage,
	
	const uint8_t *b_u, 
	const uint8_t *b_d, 
	const uint8_t *b_l, 
	const uint8_t *m_u, 
	const uint8_t *m_d, 
	const uint8_t *m_l, 
	const uint8_t *a_u,
	const uint8_t *a_d, 
	const uint8_t *a_l){
		Spell* newSpell = engine_new_spell(engine, caster, id, lifespan, damage,
				b_u, b_d, b_l, m_u, m_d, m_l, a_u, a_d, a_l);
		Entity* body = newSpell->body;
	
		body->x = caster->body->x;
		body->curr_sprite = b_l;
		body->status &= ~ENTITY_DIR_STATUS_M;
		body->dx = 0;
		if ((caster->body->status & ENTITY_DIR_STATUS_M) == ENTITY_FACE_RIGHT_STATUS) {
			body->x += 1.5 * SPRITE_SIZE;
			body->status |= ENTITY_FACE_RIGHT_STATUS;
			body->dx = 1;
		}
		else if ((caster->body->status & ENTITY_DIR_STATUS_M) == ENTITY_FACE_LEFT_STATUS) {
			body->x -= 1.5 * SPRITE_SIZE;
			body->status |= ENTITY_FACE_LEFT_STATUS;
			body->dx = -1;
		}
		
		body->y = caster->body->y;
		body->dy = 0;
		if ((caster->body->status & ENTITY_DIR_STATUS_M) == ENTITY_FACE_UP_STATUS) {
			body->y -= 1.5 * SPRITE_SIZE;
			body->curr_sprite = b_u;
			body->status |= ENTITY_FACE_UP_STATUS;
			body->dy = -1;
		}
		else if ((caster->body->status & ENTITY_DIR_STATUS_M) == ENTITY_FACE_DOWN_STATUS) {
			body->y += 1.5 * SPRITE_SIZE;
			body->curr_sprite = b_d;
			body->status |= ENTITY_FACE_DOWN_STATUS;
			body->dy = 1;
		}
		
		return newSpell;
}
	
Player* engine_get_player(Engine* engine, int i) {
	return linked_list_get_at(engine->world->scene->players, i);
}
