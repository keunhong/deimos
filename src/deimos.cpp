/****************************************
*** Includes
****************************************/
	// [ default includes
		#include <string>
		#include <sstream>
		#include <vector>
		#include <cmath>
	// default includes ]

	// [ SDL includes (in the src directory)
		#include "SDL/SDL.h"
		#include "SDL/SDL_image.h"
		#include "SDL/SDL_ttf.h"
		#include "SDL/SDL_mixer.h"
	// SDL include ]

	// [ definition includes
		#include "common.h"
	// definition includes ]

	// [ class includes
		#include "Timer.h"
		#include "Engine.h"
		#include "TextEngine.h"
		#include "SoundEngine.h"
		#include "World.h"
		#include "Spawn.h"
		#include "Entity.h"
		#include "Player.h"
		#include "Bullet.h"
		#include "Enemy.h"
	// class includes ]

	// [ function includes
		#include "SDLClass.h"
	// function includes ]
/***************************************/


/****************************************
*** Frame Rate Regulator
****************************************/
	Timer fps_regulate;
	Timer fps_update;
	Timer fps_measure;
	Uint frames;
/***************************************/


/****************************************
*** Main Function
****************************************/
int main(int argc, char* args[]){

	// set program termination variable
	bool terminate_program = false;

	// initialize SDL
	if(SDL::init() == false){ return 1; }

	// [ load font data
		TTF_Font *font = NULL;
		font = TTF_OpenFont( "ttf/FreeSans.ttf", 14 );
		SDL_Color font_color = {255,255,255};
	// load font data ]


	/******************************************
	*** Load Images
	******************************************/
		// [ load background images

			SDL_Surface *bg1,*bg2,*bg3 = NULL;

			bg1 = SDL::load_image("images/bg_space.gif");
			bg2 = SDL::load_image("images/bg2.png");
			bg3 = SDL::load_image("images/bg3.png");

			int bg1_x_offset = 0;
			int bg1_y_offset = SCREEN_HEIGHT - bg1->h;
			int bg2_x_offset = 0;
			int bg2_y_offset = SCREEN_HEIGHT - bg2->h;
			int bg3_x_offset = 0;
			int bg3_y_offset = SCREEN_HEIGHT - bg3->h;
		// load background images ]

		// [ load player sprite
			SDL_Surface *player_sprite = NULL;
			player_sprite = SDL::load_image("images/player.png");
		// load player sprite ]

		// [ load bullet sprite
			SDL_Surface *bullet_sprite = NULL;
			bullet_sprite = SDL::load_image("images/bullet.png");
		// load bullet sprite ]

		// [ load enemy sprite
			SDL_Surface *enemy_sprite = NULL;
			enemy_sprite = SDL::load_image("images/enemy.png");
		// load enemy sprite ]

		// [ load explosion sprite
			SDL_Surface *explosion_sprite = NULL;
			explosion_sprite = SDL::load_image("images/explosion.png");
		// load explosion sprite ]

	/****************************************
	*** INITIALIZE STUFF
	****************************************/
		// [ initialize engine
			//Engine<float>* engine = new Engine<float>();
		// initialize engine ]

		// [ initilize display engine
			TextEngine<float>* text_engine = new TextEngine<float>();
		// initialize display engine ]

		// [ initilize sound engine
			SoundEngine<float>* sound_engine = new SoundEngine<float>("sounds/bg_music1.mp3","sounds/laser.wav");

			sound_engine->play_bg_music();
		// initialize sound engine ]

		// [ initialize world
			World<float>* world = new World<float>();
		// initialize world ]

		// [ initialize player
			Player<float>* player = Spawn<float>::player(
					world,
					player_sprite,  // sprite
					3,				// min_speed
					7,				// max_speed
					1,				// acceleration
					100,			// x_offset
					100,			// y_offset
					bullet_sprite,	// bullet_sprite
					10,				// bullet_speed
					10,				// bullet_power
					300				// bullet_delay
			);
		// initialize player ]



			// [ debug
				Spawn<float>::enemy(
					world,				// world
					enemy_sprite,		// sprite
					10,					// min speed
					10,					// max speed
					0,					// accel
					false,				// can_shoot
					SCREEN_WIDTH / 2,	// x_offset
					SCREEN_HEIGHT / 2	// y_offset
				);

				Spawn<float>::enemy(
					world,
					enemy_sprite,
					10,
					10,
					0,
					false,
					SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2 - 50
				);
			// debug ]

	/***************************************/

		std::stringstream points_info_sstream;
		std::stringstream shield_info_sstream;
		std::stringstream stream_info_sstream;
		std::stringstream caption;

		// [ Set up player information for drawing
			std::stringstream health_info_sstream;
			health_info_sstream << "Health: " << player->get_health();
			Uint health_info_key = text_engine->add_text( health_info_sstream.str(), font, font_color, 5 , 5 );
			points_info_sstream << "Points: " << player->get_points();
			Uint points_info_key = text_engine->add_text( points_info_sstream.str(), font, font_color, 5 , 22 );

			shield_info_sstream << "Shield: " << player->get_shield();
			Uint shield_info_key = text_engine->add_text( shield_info_sstream.str(), font, font_color, 5 , 39 );

			stream_info_sstream << "Bullet Streams: " << player->get_streams();
			if(player->get_streams() == 48){ stream_info_sstream << " (MAX)"; }
			Uint stream_info_key = text_engine->add_text( stream_info_sstream.str(), font, font_color, 5 , 56 );
		// Set up player info for drawing ]

	/******************************************
	*** Start Loop
	******************************************/
		fps_measure.start(); // start timer for FPS measurement
		fps_update.start(); // start timer for FPS measurement frequency

		// set null pointer to store key state
		Uint8 *key = SDL_GetKeyState( NULL );
		while(terminate_program == false){
			// start FPS regulatiion timer
			fps_regulate.start();

			// fill screen with black surface to clear
			//SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );

			// [ background scrolling
				if(bg1_x_offset <= -bg1->w){ bg1_x_offset = 0; }
				SDL::apply_surface( bg1_x_offset, bg1_y_offset, bg1, screen );
				SDL::apply_surface( bg1_x_offset + bg1->w, bg1_y_offset, bg1, screen );
				SDL::apply_surface( bg1_x_offset + 2 * bg1->w, bg1_y_offset, bg1, screen );

				if(bg2_x_offset <= -bg2->w){ bg2_x_offset = 0; }
				SDL::apply_surface( bg2_x_offset, bg2_y_offset, bg2, screen );
				SDL::apply_surface( bg2_x_offset + bg2->w, bg2_y_offset, bg2, screen );

				if(bg3_x_offset <= -bg3->w){ bg3_x_offset = 0; }
				SDL::apply_surface( bg3_x_offset, bg3_y_offset, bg3, screen );
				SDL::apply_surface( bg3_x_offset + bg3->w, bg3_y_offset, bg3, screen );

				bg1_x_offset -= 1;
				bg2_x_offset -= 3;
				bg3_x_offset -= 5;
			// background scrolling ]

			while(SDL_PollEvent(&event)){
				if(event.type == SDL_QUIT){
					terminate_program = true;
				}
				if(event.type == SDL_KEYDOWN){
					if(event.key.keysym.sym == SDLK_PAGEUP){

						// update streams
						player->update_streams(0);	// add streams`

						// update status text
						stream_info_sstream.clear(); stream_info_sstream.str("");
						stream_info_sstream << "Bullet Streams: " << player->get_streams();
						if(player->get_streams() == 36){ stream_info_sstream << " (MAX)"; }
						text_engine->update_text( stream_info_key, stream_info_sstream.str() );

						break;

					}
					if(event.key.keysym.sym == SDLK_PAGEDOWN){

						// update streams
						player->update_streams(1);	// subtract streams

						// update status text
						stream_info_sstream.clear(); stream_info_sstream.str("");
						stream_info_sstream << "Bullet Streams: " << player->get_streams();
						text_engine->update_text( stream_info_key, stream_info_sstream.str() );

						break;

					}
					if(event.key.keysym.sym == SDLK_m){
						sound_engine->set_muted_status( sound_engine->get_muted_status()? false : true );
					}
				}
			}

			// [ handle key strokes
				// quit
				if(key[SDLK_q]){ terminate_program = true; }

				// move
				if(key[SDLK_UP]){ player->move_up(); }
				if(key[SDLK_DOWN]){ player->move_down(); }
				if(key[SDLK_LEFT]){ player->move_left(); }
				if(key[SDLK_RIGHT]){ player->move_right(); }

				// shoot
				if(key[SDLK_z]){
					if(player->can_shoot() == true){
						sound_engine->play_shoot_sound();
						player->shoot();
					}
				}
			// handle key strokes ]


			// [ show enemies
				if(world->get_enemies()->empty() == false){
					for(Uint i = 0; i < world->get_enemies()->size(); i++){
						if(world->get_enemies()->at(i)->check_collision(player) == true){
							SDL_WM_SetCaption( "Player and Enemy Collision!", NULL );
						}else{
							SDL_WM_SetCaption( "Idle", NULL );
						}
						SDL::apply_surface( int( world->get_enemies()->at(i)->get_x_offset() ), int( world->get_enemies()->at(i)->get_y_offset() ), enemy_sprite, screen );
					}
				}
			// show enemies ]

			// [ shoot existing bullets
				if(world->get_bullets()->empty() == false){
					// loop through all elements
					 for(Uint i = 0; i < world->get_bullets()->size(); i++){
						world->get_bullets()->at(i)->move();

						for( Uint j = 0; j < world->get_enemies()->size(); j++ ){
							if(world->get_bullets()->at(i)->check_collision( world->get_enemies()->at(j)) == true ){

								SDL::apply_surface(
										int( world->get_enemies()->at(j)->get_x_offset() + ( enemy_sprite->w - explosion_sprite->w )  / 2 ),
										int( world->get_enemies()->at(j)->get_y_offset() + ( enemy_sprite->h - explosion_sprite->h ) / 2 ),
										explosion_sprite,screen
								);

								delete world->get_bullets()->at(i);
								world->get_bullets()->erase(world->get_bullets()->begin() + i);

								delete world->get_enemies()->at(j);
								world->get_enemies()->erase(world->get_enemies()->begin() + j);
							}
						}
					 }

					 // Feb 13, 2009: separated deletion loop
					 // because the elements were pulled forwards
					 // before all the elements were off the screen
					 // causing some lag in the first bullet.
					 for(Uint i = 0; i < world->get_bullets()->size(); i++){
						 // if bullet is off screen erase it
						if(world->get_bullets()->at(i)->get_x_offset() > SCREEN_WIDTH
							 || world->get_bullets()->at(i)->get_y_offset() > SCREEN_HEIGHT
							 || world->get_bullets()->at(i)->get_x_offset() - world->get_bullets()->at(i)->get_width() < 0
							 || world->get_bullets()->at(i)->get_y_offset() - world->get_bullets()->at(i)->get_height() < 0
						)
						{
							delete world->get_bullets()->at(i);
							world->get_bullets()->erase(world->get_bullets()->begin() + i);
						}
					 }
				}
			// draw the bullets
				for(Uint i = 0; i < world->get_bullets()->size(); i++){
					SDL::apply_surface( int( world->get_bullets()->at(i)->get_x_offset() ), int( world->get_bullets()->at(i)->get_y_offset() ), bullet_sprite, screen );
				}
			// shoot existing bullets ]


			// [ apply player sprite to screen
				SDL::apply_surface( int(player->get_x_offset()), int(player->get_y_offset()), player_sprite, screen );
			// apply player sprite to screen ]

			// [ apply player info to screen
				for( Uint i = 0; i < text_engine->get_text()->size(); i++ ){
					SDL::apply_surface(
							text_engine->get_text()->at(i)->x_offset,
							text_engine->get_text()->at(i)->y_offset,
							text_engine->get_text()->at(i)->surface,
							screen
					);
				}
				/*SDL::apply_surface(5, 5, health_info_s, screen);
				SDL::apply_surface(5, 22, points_info_s, screen);
				SDL::apply_surface(5, 39, shield_info_s, screen);
				SDL::apply_surface(5, 56, stream_info_s, screen);*/

			// apply info to screen]


			// [ update screen
				if( SDL_Flip( screen ) == -1 ){
					return 1;
				}
			// update screen ]


			// [ calculate FPS
				if( fps_update.get_ticks() > 10000 ){
					fps_update.start();
					frames = 0;
				}
				/*if( fps_update.get_ticks() > 1000 ){
					caption.clear();;
					caption.str("");
					caption << "Average Frames Per Second: " << frames / ( fps_measure.get_ticks() / 1000.f );
					SDL_WM_SetCaption( caption.str().c_str(), NULL );
					fps_update.start();
				}*/ // commented to test collision
			// calculate FPS ]

			// [ regulate FPS
				frames++;
				if( (1000 / FRAMES_PER_SECOND) > fps_regulate.get_ticks() ){
					SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps_regulate.get_ticks() );
				}
			// regulate FPS ]
		}
	/***************************************/

	// clean up
	// free surface
	SDL_FreeSurface( bg1 );
	SDL_FreeSurface( bg2 );
	SDL_FreeSurface( bg3 );

	SDL_FreeSurface( player_sprite );
	SDL_FreeSurface( bullet_sprite );
	SDL_FreeSurface( enemy_sprite );

	// quit SDL
	SDL_Quit();

	return 0;
}
