
#include "Camera.h"

Camera camera_new(void) {
	Camera* camera = malloc(sizeof(Camera));
	return *camera;
}

void camera_update_pos(Camera* c, int x, int y) {
	c->x = x;
	c->y = y;
}
