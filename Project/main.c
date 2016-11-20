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
  Entity e2 = entity_new();
  Entity e3 = entity_new();
  Entity e4 = entity_new();
  Entity e5 = entity_new();
	List list;
	
	//PLL_Init();
  initialize_serial_debug();

  put_string("\n\r");
  put_string("************************************\n\r");
  put_string("ECE353 - GPIO In Class Exercise\n\r");
  put_string("************************************\n\r");
  
  lcd_config_gpio();

    // Run validation code
  if( validate_ice(ICE_GPIO_PORT) == false)
  {
    while(1){
    };
  }
  
  lcd_config_screen();
  lcd_clear_screen(LCD_COLOR_BLACK);
	
	e1.setPosX(&e1, 60);
	e1.setPosY(&e1, 60);
	e1.setSpdX(&e1, 1);
	e1.setSpdY(&e1, 1);
	
	e2.setPosX(&e2, 100);
	e2.setPosY(&e2, 100);
	e2.setSpdY(&e2, 1);
		
	e3.setPosX(&e3, 140);
	e3.setPosY(&e3, 140);
	e3.setSpdX(&e3, 3);
		
	e4.setPosX(&e4, 80);
	e4.setPosY(&e4, 200);
	e4.setSpdX(&e4, 1);
	e4.setSpdY(&e4, 2);
	
	e5.setPosX(&e5, 200);
	e5.setPosY(&e5, 300);
	
	list = linked_list_new();
	list.add_at(&list, &e1, 0);
	list.add_at(&list, &e2, 0);
	list.add_at(&list, &e3, 2);
	list.add_at(&list, &e4, 2);
	list.add_at(&list, &e5, 1);
	while(i < list.len){
		curr = (Entity*)list.get_at(&list, i);
		curr->curr_sprite = sprite_down;
		curr->setBaseSprite(
			curr,
			sprite_left,
			sprite_right,
			sprite_up,
			sprite_down);
		curr->setMotSprite(
			curr,
			sprite_mot_left,
			sprite_mot_right,
			sprite_mot_up,
			sprite_mot_down);
		i++;
	}
  // Reach infinite loop
  while(1){
		if (b>>4) {
			e1.rotate90(&e1, true);
			e2.rotate90(&e2, true);
			e3.rotate90(&e3, false);
			e3.rotate90(&e4, true);
			b = 0;
		}
		if (true) {
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
