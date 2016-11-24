// Copyright (c) 2015-16, Joe Krachey
// All rights reserved.
//
// Redistribution and use in source or binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in source form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "main.h"

//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
	int a = 0;
	int b = 0;
	int i = 0;
	Entity* curr;
  Entity e1 = entity_new();
	List list;
	
	//PLL_Init();
	
  initialize_serial_debug();
  
  lcd_config_gpio();
  
  lcd_config_screen();
  lcd_clear_screen(0x57CA);
	
	e1.setPosX(&e1, 160);
	e1.setPosY(&e1, 160);
	e1.setSpdY(&e1, 1);
	
	list = linked_list_new();
	list.add_at(&list, &e1, 0);
	while(i < list.len){
		curr = (Entity*)list.get_at(&list, i);
		curr->curr_sprite = sprite_down;
		curr->setBaseSprite(
			curr,
			sprite_up,
			sprite_down,
			sprite_left);
		curr->setMotSprite(
			curr,
			sprite_mot_up,
			sprite_mot_down,
			sprite_mot_left);
		i++;
	}
  // Reach infinite loop
  while(1){
		if (b>>7) {
			e1.rotate90(&e1, true);
			b = 0;
		}
		if (a>50000) {
			i = 0;
			while(i < list.len){
				curr = (Entity*)list.get_at(&list, i);
				curr->draw(curr);
				i++;
			}
			a = 0;
			b++;
		}
		a++;
	};
}
