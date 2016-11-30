
#include "Engine.h"

Engine engine_new(void) {
	Engine* engine = malloc(sizeof(Engine));
	return *engine;
}
