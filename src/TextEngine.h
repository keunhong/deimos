/*
 * TextEngine.h
 *
 *  Created on: Mar 9, 2009
 *      Author: K
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

template<class T>
struct Text{
	Uint key;
	std::string text;
	TTF_Font 	*font;
	SDL_Color	color;
	T 			x_offset;
	T 			y_offset;
	SDL_Surface *surface;
};

template<class T>
class TextEngine : public Engine<T>{
	std::vector< Text<T>* >	*text; // vector for storing text

	public:
		TextEngine(){
			text = new std::vector< Text<T>* >;
		}

		// add Text struct to the text vector
		Uint add_text(std::string _text, TTF_Font *_font, SDL_Color _color, T _x_offset, T _y_offset){
			Text<T> *new_text = new Text<T>;
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
			Text<T> *current_text = text->at(key);
			current_text->text = _text;
			SDL_FreeSurface( current_text->surface );
			current_text->surface = TTF_RenderText_Blended( current_text->font, _text.c_str(), current_text->color );
		}
		// return Text struct
		std::vector< Text<T>* >	* get_text() const{ return text; }


};

#endif /* DISPLAY_H_ */
