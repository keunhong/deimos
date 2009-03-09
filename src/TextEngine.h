/*
 * TextEngine.h
 *
 *  Created on: Mar 9, 2009
 *      Author: K
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

struct Text{
	Uint key;
	std::string text;
	TTF_Font 	*font;
	SDL_Color	color;
	int			x_offset;
	int 			y_offset;
	SDL_Surface *surface;
};

class TextEngine : public Engine{
	std::vector< Text* >	*text; // vector for storing text

	public:
		TextEngine(){
			text = new std::vector< Text* >;
		}

		// add Text struct to the text vector
		Uint add_text(std::string _text, TTF_Font *_font, SDL_Color _color, int _x_offset, int _y_offset){
			Text *new_text = new Text;
			new_text->key = text->size();
			new_text->text = _text;
			new_text->font = _font;
			new_text->color = _color;
			new_text->x_offset = _x_offset;
			new_text->y_offset = _y_offset;
			new_text->surface = TTF_RenderText_Blended(_font, _text.c_str(), _color);

			text->push_back(new_text);

			return new_text->key;
		}
		// update text using key
		void update_text( Uint key, std::string _text ){
			Text *current_text = text->at(key);
			current_text->text = _text;
			SDL_FreeSurface( current_text->surface );
			current_text->surface = TTF_RenderText_Blended( current_text->font, _text.c_str(), current_text->color );
		}
		// return Text struct
		std::vector< Text* > * get_text() const{ return text; }


};

#endif /* DISPLAY_H_ */
