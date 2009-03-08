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
		#include "World.h"
		#include "Spawn.h"
		#include "Entity.h"
		#include "Player.h"
		#include "Bullet.h"
		#include "Enemy.h"
	// class includes ]

	// [ function includes
		#include "SDL_functions.h"
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
	if(sdl::init() == false){ return 1; }

	// set window manager title
	SDL_WM_SetCaption("Ultimate Shooting Game", NULL);

	// [ load font data
		TTF_Font *font = NULL;
		SDL_Surface *text,				// _s stands for surface, to not confuse later on
					*health_info_s,
					*points_info_s,
					*shield_info_s,
					*stream_info_s
					= NULL;
		font = TTF_OpenFont( "ttf/FreeSans.ttf", 14 );
		SDL_Color font_color = {255,255,255};
	// load font data ]

	// [ load music data
		Mix_Music *bg_music = NULL;
		Mix_Chunk *laser = NULL;

		Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);

		bg_music = Mix_LoadMUS("sounds/bg_music1.mp3");
		laser = Mix_LoadWAV("sounds/laser.wav");
		Mix_PlayMusic(bg_music,-1);

	// load music data ]


	/******************************************
	*** Load Images
	******************************************/
		// [ load background images

			SDL_Surface *bg1,*bg2,*bg3 = NULL;

			bg1 = sdl::load_image("images/bg_space.gif");
			bg2 = sdl::load_image("images/bg2.png");
			bg3 = sdl::load_image("images/bg3.png");

			int bg1_x_offset = 0;
			int bg1_y_offset = SCREEN_HEIGHT - bg1->h;
			int bg2_x_offset = 0;
			int bg2_y_offset = SCREEN_HEIGHT - bg2->h;
			int bg3_x_offset = 0;
			int bg3_y_offset = SCREEN_HEIGHT - bg3->h;
		// load background images ]

		// [ load player sprite
			SDL_Surface *player_sprite = NULL;
			player_sprite = sdl::load_image("images/player.png");
		// load player sprite ]

		// [ load bullet sprite
			SDL_Surface *bullet_sprite, *pretzel_sprite = NULL;
			bullet_sprite = sdl::load_image("images/bullet.png");
			pretzel_sprite = sdl::load_image("images/pretzel.png");
		// load bullet sprite ]

	/****************************************
	*** INITIALIZE STUFF
	****************************************/
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
	/***************************************/


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

			// [ FPS test text
				std::stringstream lol;
				lol << frames;
				text = TTF_RenderText_Blended( font, lol.str().c_str(),  font_color);
			// FPS test text ]

			// [ Set up player information for drawing
				std::stringstream health_info;
				std::stringstream points_info;
				std::stringstream shield_info;
				std::stringstream stream_info;

				health_info << "Health: " << player->get_health();
				health_info_s = TTF_RenderText_Blended(font, health_info.str().c_str(), font_color);

				points_info << "Points: " << player->get_points();
				points_info_s = TTF_RenderText_Blended(font, points_info.str().c_str(), font_color);

				shield_info << "Shield: " << player->get_shield();
				shield_info_s = TTF_RenderText_Blended(font, shield_info.str().c_str(), font_color);

				stream_info << "Bullet Streams: " << player->get_streams();
				if(player->get_streams() == 48){ stream_info << " (MAX)"; }
				stream_info_s = TTF_RenderText_Blended(font, stream_info.str().c_str(), font_color);

			// Set up player info for drawing ]

			// [ background scrolling
				if(bg1_x_offset <= -bg1->w){ bg1_x_offset = 0; }
				sdl::apply_surface( bg1_x_offset, bg1_y_offset, bg1, sdl::screen );
				sdl::apply_surface( bg1_x_offset + bg1->w, bg1_y_offset, bg1, sdl::screen );
				sdl::apply_surface( bg1_x_offset + 2 * bg1->w, bg1_y_offset, bg1, sdl::screen );

				if(bg2_x_offset <= -bg2->w){ bg2_x_offset = 0; }
				sdl::apply_surface( bg2_x_offset, bg2_y_offset, bg2, sdl::screen );
				sdl::apply_surface( bg2_x_offset + bg2->w, bg2_y_offset, bg2, sdl::screen );

				if(bg3_x_offset <= -bg3->w){ bg3_x_offset = 0; }
				sdl::apply_surface( bg3_x_offset, bg3_y_offset, bg3, sdl::screen );
				sdl::apply_surface( bg3_x_offset + bg3->w, bg3_y_offset, bg3, sdl::screen );

				bg1_x_offset -= 1;
				bg2_x_offset -= 3;
				bg3_x_offset -= 5;
			// background scrolling ]

			while(SDL_PollEvent(&sdl::event)){
				if(sdl::event.type == SDL_QUIT){
					terminate_program = true;
				}
				if(sdl::event.type == SDL_KEYDOWN){
					if(sdl::event.key.keysym.sym == SDLK_PAGEUP){
						player->update_streams(0);	// add streams`
						break;
					}
					if(sdl::event.key.keysym.sym == SDLK_PAGEDOWN){
						player->update_streams(1);	// subtract streams
						break;
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
						player->shoot();
						Mix_PlayChannel(-1,laser,0);
					}
				}
			// handle key strokes ]


			// [ shoot existing bullets
				if(world->get_bullets()->empty() == false){
					// loop through all elements
					 for(Uint i = 0; i < world->get_bullets()->size(); i++){
						 world->get_bullets()->at(i)->move();
					 }

					 // Feb 13, 2009: separated deletion loop
					 // because the elements were pulled forwards
					 // before all the elements were off the sdl::screen
					 // causing some lag in the first bullet.
					 for(Uint i = 0; i < world->get_bullets()->size(); i++){
						 // if bullet is off sdl::screen erase it
						if(world->get_bullets()->at(i)->get_x_offset() >= SCREEN_WIDTH
							 || world->get_bullets()->at(i)->get_y_offset() >= SCREEN_HEIGHT
							 || world->get_bullets()->at(i)->get_x_offset() - world->get_bullets()->at(i)->get_width() <= 0
							 || world->get_bullets()->at(i)->get_y_offset() - world->get_bullets()->at(i)->get_height() <= 0
						)
						{
							delete world->get_bullets()->at(i);
							world->get_bullets()->erase(world->get_bullets()->begin() + i);
						}
					 }
				}
				// draw the bullets
				for(Uint i = 0; i < world->get_bullets()->size(); i++){
					sdl::apply_surface( int( world->get_bullets()->at(i)->get_x_offset() ), int( world->get_bullets()->at(i)->get_y_offset() ), bullet_sprite, sdl::screen );
				}
			// shoot existing bullets ]

			// [ apply player sprite to sdl::screen
				sdl::apply_surface( int(player->get_x_offset()), int(player->get_y_offset()), player_sprite, sdl::screen );
			// apply player sprite to sdl::screen ]

			// [ apply player info to sdl::screen
				sdl::apply_surface(5, 5, health_info_s, sdl::screen);
				sdl::apply_surface(5, 22, points_info_s, sdl::screen);
				sdl::apply_surface(5, 39, shield_info_s, sdl::screen);
				sdl::apply_surface(5, 56, stream_info_s, sdl::screen);

			// apply info to sdl::screen]


			// [ update sdl::screen
				if( SDL_Flip( sdl::screen ) == -1 ){
					return 1;
				}
			// update sdl::screen ]


			// [ calculate FPS
				if( fps_update.get_ticks() > 10000 ){
					fps_update.start();
					frames = 0;
				}
				if( fps_update.get_ticks() > 1000 ){
					std::stringstream caption;
					caption << "Average Frames Per Second: " << frames / ( fps_measure.get_ticks() / 1000.f );
					SDL_WM_SetCaption( caption.str().c_str(), NULL );
					fps_update.start();
				}
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
	SDL_FreeSurface( pretzel_sprite);
	SDL_FreeSurface( bullet_sprite );

	SDL_FreeSurface( text );
	SDL_FreeSurface( health_info_s );
	SDL_FreeSurface( points_info_s );
	SDL_FreeSurface( shield_info_s );
	SDL_FreeSurface( stream_info_s );

	// quit SDL
	SDL_Quit();

	return 0;
}
