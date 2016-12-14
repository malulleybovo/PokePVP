#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "RenderMan.h"
#include "World.h"

/******************************************************************************* 
*	Definition
*******************************************************************************/
typedef struct _Engine Engine;
struct _Engine {
	
	RenderMan* renderMan;
	World* world;
	
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
Engine* engine_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void engine_init(Engine* engine);
void engine_run(Engine* engine);

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
	const uint8_t *a_l);

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
	const uint8_t *a_l);
	
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
	const uint8_t *a_l);
	
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
	const uint8_t *a_l);
	
Player* engine_get_player(Engine* engine, int i);

#endif
