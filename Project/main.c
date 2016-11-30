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
	uint16_t spdX = 0x7d7;
	uint16_t spdY = 0x7d7;
	Entity* curr;
  Entity e1 = entity_new();
  Entity e2 = entity_new();
  Entity e3 = entity_new();
  Entity e4 = entity_new();
  Entity e5 = entity_new();
	List list;
	
	PLL_Init();
	
  initialize_serial_debug();
  ps2_initialize(); 
  
  lcd_config_gpio();
  
  lcd_config_screen();
  lcd_clear_screen(0x57CA);
	
	e1.x = 160;
	e1.y = 160;
	e2.x = 40;
	e2.y = 40;
	e3.x = 40;
	e3.y = 160;
	e4.x = 160;
	e4.y = 40;
	e5.x = 100;
	e5.y = 100;
	
	list = linked_list_new();
	linked_list_add(&list, &e1);
	linked_list_add(&list, &e2);
	linked_list_add(&list, &e3);
	linked_list_add(&list, &e4);
	linked_list_add(&list, &e5);
	while(i < list.len){
		curr = (Entity*)linked_list_get_at(&list, i);
		curr->curr_sprite = sprite_down;
		if (i%2) {
			curr->curr_sprite = sprite_down;
			entity_set_base_sprite(
				curr,
				sprite_up,
				sprite_down,
				sprite_left);
			entity_set_mot_sprite(
				curr,
				sprite_mot_up,
				sprite_mot_down,
				sprite_mot_left);
		}
		else {
			curr->curr_sprite = sprite_down_2;
			entity_set_base_sprite(
				curr,
				sprite_up_2,
				sprite_down_2,
				sprite_left_2);
			entity_set_mot_sprite(
				curr,
				sprite_mot_up_2,
				sprite_mot_down_2,
				sprite_mot_left_2);
		}
		i++;
	}
  // Reach infinite loop
  while(1){
		if (b>>2) {
			spdX = ps2_get_x();
			spdY = ps2_get_y();
			b = 0;
		}
		if (a>50000) {
			i = 0;
			while(i < list.len){
				curr = (Entity*)linked_list_get_at(&list, i);
				
				curr->dx = 0;
				curr->dy = 0;
				if(spdX > 0xE00){
					curr->dx = 1;
				}
				else if(spdX < 0x100) {
					curr->dx = -1;
				}
				else {
					if(spdY > 0xE00){
						curr->dy = 1;
					}
					else if(spdY < 0x100) {
						curr->dy = -1;
					}
				}
				
				entity_draw(curr, - (ROWS / 2), - (COLS / 2));
				i++;
			}
			a = 0;
			b++;
		}
		a++;
	};
}
