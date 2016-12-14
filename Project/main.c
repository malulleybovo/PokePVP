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


typedef enum 
{
  DEBOUNCE_ONE,
  DEBOUNCE_1ST_ZERO,
  DEBOUNCE_2ND_ZERO,
  DEBOUNCE_PRESSED
} DEBOUNCE_STATES;
bool sw1_debounce_fsm(void)
{
  static DEBOUNCE_STATES state = DEBOUNCE_ONE;
  int i = 10000;
  bool pin_logic_level;
  
  pin_logic_level = lp_io_read_pin(SW1_PIN);
  
  switch (state)
  {
    case DEBOUNCE_ONE:
    {
      if(pin_logic_level)
      {
        state = DEBOUNCE_ONE;
      }
      else
      {
        state = DEBOUNCE_1ST_ZERO;
      }
      break;
    }
    case DEBOUNCE_1ST_ZERO:
    {
      if(pin_logic_level)
      {
        state = DEBOUNCE_ONE;
      }
      else
      {
        state = DEBOUNCE_2ND_ZERO;
      }
      break;
    }
    case DEBOUNCE_2ND_ZERO:
    {
      if(pin_logic_level)
      {
        state = DEBOUNCE_ONE;
      }
      else
      {
        state = DEBOUNCE_PRESSED;
      }
      break;
    }
    case DEBOUNCE_PRESSED:
    {
      if(pin_logic_level)
      {
        state = DEBOUNCE_ONE;
      }
      else
      {
        state = DEBOUNCE_PRESSED;
      }
      break;
    }
    default:
    {
      while(1){};
    }
  }
  
  if(state == DEBOUNCE_2ND_ZERO )
  {
    return true;
  }
  else
  {
    return false;
  }
}


//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
	int a = 0;
	int b = 0;
	int i = 0;
	int bo = 0;
	uint16_t spdX = 0x7d7;
	uint16_t spdY = 0x7d7;
	bool is_sw1_pressed = false;
	bool i2 = true;
	Player* curr;
	Player* enemy;
	Player* enemy2;
	Spell* spell0;
	Engine* engine = engine_new();
	
	PLL_Init();
	
  initialize_serial_debug();
  ps2_initialize(); 
  lp_io_init();
  
  lcd_config_gpio();
  
  lcd_config_screen();
  lcd_clear_screen(0x57CA);
	
	engine_init(engine);
	curr = engine_setup_main_player(engine, 
		"P1", 
		40, // x
		40, // y
		40, // hp
		10, // pp
		sprite_up_2,
		sprite_down_2,
		sprite_left_2,
		sprite_mot_up_2,
		sprite_mot_down_2,
		sprite_mot_left_2,
		sprite_atk_up_2,
		sprite_atk_down_2,
		sprite_atk_left_2);
		
	enemy = engine_new_player(engine, 
		"P2", 
		20, 
		-40, 
		40, 
		10, 
		sprite_up_2,
		sprite_down_2,
		sprite_left_2,
		sprite_mot_up_2,
		sprite_mot_down_2,
		sprite_mot_left_2,
		NULL,
		NULL,
		NULL);
	enemy2 = engine_new_player(engine, 
		"P3", 
		80, 
		-40, 
		40, 
		10, 
		sprite_up_2,
		sprite_down_2,
		sprite_left_2,
		sprite_mot_up_2,
		sprite_mot_down_2,
		sprite_mot_left_2,
		NULL,
		NULL,
		NULL);
	
  // Reach infinite loop
  while(1){
		if (b>>2) {
			spdX = ps2_get_x();
			spdY = ps2_get_y();
			is_sw1_pressed = sw1_debounce_fsm();
			b = 0;
		}
		if (i>>6) {
			i = 0; i2 = true;
			enemy = scene_find_player_by_id(engine->world->scene, "P2");
			enemy2 = scene_find_player_by_id(engine->world->scene, "P3");
			player_rotate90(enemy2, false);
			player_rotate90(enemy, true);
			if (bo == 4) {
				enemy->body->dy = 1;
				enemy2->body->dy = 1;
				bo = 0;
			}
			bo++;
		}
		if (a>5000) {
			
			curr->body->dx = 0;
			curr->body->dy = 0;
			if(spdX > 0xE00){
				curr->body->dx = 1;
			}
			else if(spdX < 0x100) {
				curr->body->dx = -1;
			}
			else {
				if(spdY > 0xE00){
					curr->body->dy = 1;
				}
				else if(spdY < 0x100) {
					curr->body->dy = -1;
				}
			}
			engine_run(engine);
			a = 0;
			b++;
			i++;
			
			lp_io_clear_pin(RED_PIN);
			if(is_sw1_pressed) {
					lp_io_set_pin(RED_PIN);
				player_attack(curr);
				if(i2) {
				spell0 = engine_new_bullet_spell(engine, curr, "spell0", 100, 10,
					sprite_spc_atk_2,
					sprite_spc_atk_2,
					sprite_spc_atk_2,
					sprite_spc_atk_mot_2,
					sprite_spc_atk_mot_2,
					sprite_spc_atk_mot_2,
					NULL,
					NULL,
					NULL);
					i2 = false;
				}
			}
		}
		a++;
	};
}
