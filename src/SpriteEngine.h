/*
 * SpriteEngine.h
 *
 *  Created on: Mar 9, 2009
 *      Author: K
 */

#ifndef SPRITEENGINE_H_
#define SPRITEENGINE_H_

class SpriteEngine{
	std::vector< SDL_Surface* > *sprites; // vector for storing sprite structs

	// destructor iterator

	public:
		SpriteEngine(){
			sprites = new std::vector< SDL_Surface* >;
		}

		~SpriteEngine(){
			for(Uint i = 0; i < sprites->size(); i++){
				SDL_FreeSurface( sprites->at(i) );
			}
			delete sprites;
		}

		// add Text struct to the text vector
		//    offset values not needed if is dependent on object
		//     -1 means not set
		Uint add_sprite( std::string _file, int _x_offset = -1, int _y_offset = -1 ){
			SDL_Surface *new_sprite = new SDL_Surface;
			new_sprite = SDL::load_image( _file );

			sprites->push_back(new_sprite);

			return sprites->size() - 1;
		}

		// return Text struct
		std::vector< SDL_Surface* > * get_sprites() const{ return sprites; }
		SDL_Surface * get_sprite(Uint key) const{ return sprites->at(key); }
		SDL_Surface * get_sprite_surface(Uint key) const{ return sprites->at(key); }
};

#endif /* SPRITEENGINE_H_ */
