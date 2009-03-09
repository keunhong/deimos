/*
 * SpriteEngine.h
 *
 *  Created on: Mar 9, 2009
 *      Author: K
 */

#ifndef SPRITEENGINE_H_
#define SPRITEENGINE_H_

struct Sprite{
	Uint key;
	std::string	file;
	int 		x_offset;
	int			y_offset;
	SDL_Surface *surface;
};


class SpriteEngine{
	std::vector< Sprite* > *sprites; // vector for storing sprite structs

	// destructor iterator
	void delete_sprite(Sprite *_sprite){ delete _sprite; }

	public:
		SpriteEngine(){
			sprites = new std::vector< Sprite* >;
		}

		~SpriteEngine(){
			for(Uint i = 0; i < sprites->size(); i++){
				delete sprites->at(i);
			}
			delete sprites;
		}

		// add Text struct to the text vector
		//    offset values not needed if is dependent on object
		//     -1 means not set
		Uint add_sprite( std::string _file, int _x_offset = -1, int _y_offset = -1 ){
			Sprite *new_sprite = new Sprite;
			new_sprite->key = sprites->size();
			new_sprite->file = _file;
			new_sprite->x_offset = _x_offset;
			new_sprite->y_offset = _y_offset;
			new_sprite->surface = SDL::load_image( _file );

			sprites->push_back(new_sprite);

			return new_sprite->key;
		}
		// update sprite with key
		//    same here, -1 means not set for offsets
		//     "" (empty) means do not reset file
		void update_sprite( Uint key, int _x_offset = -1, int _y_offset = -1, std::string _file = "" ){
			Sprite *current_sprite = sprites->at(key);
			if(_x_offset != -1){
				current_sprite->x_offset = _x_offset;
			}
			if(_y_offset != -1){
				current_sprite->y_offset = _y_offset;
			}
			if(_file != ""){
				SDL_FreeSurface( current_sprite->surface );

				current_sprite->file = _file;
				current_sprite->surface = SDL::load_image(_file);
			}
		}

		// return Text struct
		std::vector< Sprite* > * get_sprites() const{ return sprites; }
		Sprite * get_sprite(Uint key) const{ return sprites->at(key); }
		SDL_Surface * get_sprite_surface(Uint key) const{ return sprites->at(key)->surface; }
};

#endif /* SPRITEENGINE_H_ */
