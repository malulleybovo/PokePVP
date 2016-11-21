#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "RenderMan.h"

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
Engine engine_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void engine_init(void);
void engine_run(void);

#endif
