#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/******************************************************************************* 
*	Definition
*******************************************************************************/
typedef struct _Camera Camera;
struct _Camera {
	
	int x;
	int y;	
	
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
Camera camera_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void camera_set_x(Camera* camera, int x);
void camera_set_y(Camera* camera, int y);

#endif
