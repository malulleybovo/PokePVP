#ifndef __ENTITY_MAN_H__
#define __ENTITY_MAN_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "LinkedList.h"

/******************************************************************************* 
*	Definition
*******************************************************************************/
typedef struct _EntityMan EntityMan;
struct _EntityMan {
	
	List entities;
	
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
EntityMan entity_man_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
// TODO other functions

#endif
