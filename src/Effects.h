/*
 * Effects.h
 *
 *  Created on: 09-Mar-2009
 *      Author: Rafal
 *
 *     The purpose of this is to generate explosion effects
 *
 *
 */
#include "SDLClass.h"
#include <stdlib.h>

#ifndef EFFECTS_H_
#define EFFECTS_H_

	struct Frame{
		SDL_Surface *surface;
	};


class Explode{
	std::vector<Frame> *movie;
	Uint size;
	std::string location;
	std::string file_end;
public:
	Explode(){
		movie = new std::vector<Frame>;
		location = "images/explosion/";
		file_end = ".tga";
		size = 75;
	}

	// doesn't work

	// go to line 320 in deimos.cpp for hwo i would want to implement this. HELP ME
	// line 120 in deimos.cpp initliazes the thing....

	void explode(float x_offset,float y_offset){
	for(Uint i = 1; i <= size; i++){
		Frame *new_frame = new Frame;
		std::stringstream buffer;
		buffer << location << i << file_end;
		std::string temp = buffer.str();
		new_frame->surface = SDL::load_image(const_cast<char *>(temp.c_str()));
		SDL::apply_surface(x_offset,y_offset,new_frame->surface,screen);
	}
	}

};




#endif /* EFFECTS_H_ */
