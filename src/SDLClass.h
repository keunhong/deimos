/*********************************************
*** SDL Functions
*** Functions to make life easier
*** and some basic definitions like screen
*** and event
***
*** SDL_ are defined by SDL
*** sdl_ are defined by me
***
*** way to go for conventions
*********************************************/

#ifndef SDL_FUNCTIONS_H_
#define SDL_FUNCTIONS_H_


// [ set SDL surface pointers
	SDL_Surface *screen = NULL;
// set SDL surface pointers ]

// [ SDL event
	SDL_Event event;
// SDL events ]

class SDL{
	public:
		/********************************************
		*** Function for loading images
		********************************************/
		static SDL_Surface * load_image( std::string filename ){
			// set pointer for original image
			SDL_Surface *original_image = NULL;

			// set pointer for optimized image
			SDL_Surface *optimized_image = NULL;

			// load image
			original_image = IMG_Load( filename.c_str() );

			// skip if image was not successfully loaded
			if(original_image != NULL){
				optimized_image = SDL_DisplayFormatAlpha(original_image); // optimize
				SDL_FreeSurface( original_image );
			}

			return optimized_image;
		}

		/********************************************
		*** Function for applying surfaces
		********************************************/
		template<class T>
		static void apply_surface(T x_offset, T y_offset, SDL_Surface* source, SDL_Surface* destination){
			// temporary rectangle for holding the offsets
			SDL_Rect offset;

			// set offsets
			offset.x = int(x_offset);
			offset.y = int(y_offset);

			// blit surface
			SDL_BlitSurface(source, NULL, destination, &offset);
		}
		/********************************************/

		/****************************************
		*** Function for Initializing SDL
		****************************************/
		static bool init(){
			// initialize all SDL subsystems
			if(SDL_Init( SDL_INIT_EVERYTHING ) == -1){
				return false;
			}

			// setup up screen
			// screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
			//screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN );
			screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF );

			if(screen == NULL){ return false; }

			// initialize SDL TTF font system
			if(TTF_Init() == -1){ return false; }

			// hide cursor
			SDL_ShowCursor(SDL_DISABLE);

			//If everything initialized fine
			return true;
		}
		/***************************************/
};

#endif /* SDL_FUNCTIONS_H_ */
